#include "xftypedef.h"

#include "xfmqtt.h"

#define NULL    0

static XFMQTT_Config mConfig = {0};
static XFMQTT_EventHandler mEventHandler = {0};


static uint16 mqtt_check_utf8(uint8 *buf, uint16 size) {
    return size;
}
static uint8 mqtt_write_uint8(uint8 *out, uint8 val) {
    *((uint8*)out) = val;
    return sizeof(uint8);
}

static uint8 mqtt_write_uint16(uint8 *out, uint16 val) {
    uint8 *uo = (uint8*)out;
    uo[0] = (uint8)(val >> 8);
    uo[1] = (uint8)(val);
    return sizeof(uint16);
}

static uint8 mqtt_write_uint32(uint8 *out, uint32 val) {
    out[0] = (val>>24) & 0xFF;
    out[1] = (val>>16) & 0xFF;
    out[2] = (val>>8) & 0xFF;
    out[3] = (val>>0) & 0xFF;
    return sizeof(uint32);
}

//static uint8 mqtt_read_uint8(uint8 *out, uint)

static int mqtt_write_bytes(uint8 *out, const uint8 *b, uint16 len) {
    memcpy(out, b, len);
    return len;
}

static int mqtt_write_payload(uint8 *out, const uint8 *b, uint16 len) {
    uint8 pos = mqtt_write_uint16(out, len);
    memcpy(out + pos, b, len);
    return pos + len;
}

static uint8 mqtt_read_lenght(uint32 *len, const uint8 *in, int size) {
    int i;
    uint32 multiplier = 1;

    *len = 0;
    for(i = 0; i < size; ++i) {
        *len += (in[i] & 0x7f) * multiplier;

        if(!(in[i] & 0x80)) {
            return i + 1;
        }

        multiplier *= 128;
        if(multiplier >= 128 * 128 * 128) {
            return 0; // error, out of range
        }
    }

    return 0; // not complete
}

static uint8 mqtt_write_lenght(uint8 *out, uint32 len) {
    int i;
    for(i = 1; i <= 4; ++i) {
        *((uint8*)out) = len % 128;
        len /= 128;
        if(len > 0) {
            *((uint8*)out) |= 128;
            ++out;
        }
        else {
            return i;
        }
    }

    return 0;
}

int XFMQTT_ConfigSet(XFMQTT_Config *cfg) {
    mConfig = *cfg;
    return 0;
}

static uint32 packet_connect(uint8 *b, XFMQTT_PacketConnect *packet, XFMQTT_Exception *e) {
    uint8 *pb = b;
	const uint8 byteVariable[7] = "\x00\x04MQTT\x04";
    int ret;
    uint16 id_len, wt_len, user_len;
    uint32 total_len = 0;
    XFMQTT_PacketConnectFlag flags = 0;

    total_len = 10; // length of the variable header
    id_len = strlen(packet->id);
    if(id_len < 0) {
        e->errno = XFMQTT_ERRNO_ILLEGAL_CHARACTER;
        return 0;
    }
    total_len += id_len + 2;

    if(packet->clean_session) {
        flags |= XFMQTT_CONNECT_CLEAN_SESSION;
    }

    if(packet->will_msg && !packet->will_topic) {
        e->errno = XFMQTT_ERRNO_INVALID_PARAMETER;
        return 0;
    }

    wt_len = 0;
    if(packet->will_topic) {
        flags |= XFMQTT_CONNECT_WILL_FLAG;
        wt_len = strlen(packet->will_topic);
    }

    switch(packet->qos) {
    case XFMQTT_QOS0:
        flags |= XFMQTT_CONNECT_WILL_QOS0;
        break;
    case XFMQTT_QOS1:
        flags |= (XFMQTT_CONNECT_WILL_FLAG | XFMQTT_CONNECT_WILL_QOS1);
        break;
    case XFMQTT_QOS2:
        flags |= (XFMQTT_CONNECT_WILL_FLAG | XFMQTT_CONNECT_WILL_QOS2);
        break;
    default:
        e->errno = XFMQTT_ERRNO_INVALID_PARAMETER;
        return 0;
    }

    if(packet->will_retain) {
        flags |= (XFMQTT_CONNECT_WILL_FLAG | XFMQTT_CONNECT_WILL_RETAIN);
    }

    if(flags & XFMQTT_CONNECT_WILL_FLAG) {
        total_len += 4 + wt_len + packet->msg_len;
    }

    if(!packet->user && packet->password) {
        e->errno = XFMQTT_ERRNO_INVALID_PARAMETER;
        return 0;
    }

    /*must have user + password
     in v2.0
    */
    if(NULL == packet->user ||
        NULL == packet->password){
        e->errno = XFMQTT_ERRNO_INVALID_PARAMETER;
        return 0;
    }


    user_len = 0;
    if(packet->user) {
        flags |= XFMQTT_CONNECT_USER_NAME;
        user_len = strlen(packet->user);
        total_len += user_len + 2;
    }

    if(packet->password) {
        flags |= XFMQTT_CONNECT_PASSORD;
        total_len += packet->pswd_len + 2;
    }

    b += mqtt_write_uint8(b, XFMQTT_PACKET_TYPE_CONNECT);
    if(0 == (ret = mqtt_write_lenght(b, total_len))) {
        e->errno = XFMQTT_ERRNO_PKT_TOO_LARGE;
        return 0;
    } else {
        b += ret;
    }

    b += mqtt_write_bytes(b, byteVariable, sizeof(byteVariable));
    b += mqtt_write_uint8(b, flags);
    b += mqtt_write_uint16(b, packet->keep_alive);
    b += mqtt_write_payload(b, packet->id, id_len);

    if(flags & XFMQTT_CONNECT_WILL_FLAG) {
        if(!packet->will_msg) {
            packet->will_msg = "";
            packet->msg_len = 0;
        }
        b += mqtt_write_bytes(b, packet->will_topic, wt_len);
        b += mqtt_write_bytes(b, packet->will_msg, packet->msg_len);
    }

    if(flags & XFMQTT_CONNECT_USER_NAME) {
        b += mqtt_write_payload(b, packet->user, user_len);
    }

    if(flags & XFMQTT_CONNECT_PASSORD) {
        b += mqtt_write_payload(b, packet->password, packet->pswd_len);
    }

    //if((total_len - 1) != (b - pb - 1)) {
    //    e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
    //    return 0;
    //}

    return (uint32)(b - pb);
}

static uint32 packet_publish(uint8 *b, XFMQTT_PacketPublish *packet, XFMQTT_Exception *e) {
    int ret;
    uint32 topic_len = 0, total_len = 0;
    uint8 headFixed0 = XFMQTT_PACKET_TYPE_PUBLISH;
    uint8 *pb = b;

    if(0 == packet->pkt_id) {
        e->errno = XFMQTT_ERRNO_INVALID_PARAMETER;
        return 0;
    }

    for(topic_len = 0; '\0' != packet->topic[topic_len]; ++topic_len) {
        if(('#' == packet->topic[topic_len]) || ('+' == packet->topic[topic_len])) {
            e->errno = XFMQTT_ERRNO_INVALID_PARAMETER;
            return 0;
        }
    }

    if(mqtt_check_utf8(packet->topic, topic_len) != topic_len) {
        e->errno = XFMQTT_ERRNO_NOT_UTF8;
        return 0;
    }

    if(packet->retain) {
        headFixed0 |= 0x01;
    }

    total_len = topic_len + packet->sizePayload + 2;
    switch(packet->qos) {
    case XFMQTT_QOS0:
        break;
    case XFMQTT_QOS1:
        headFixed0 |= 0x02;
        total_len += 2;
        break;
    case XFMQTT_QOS2:
        headFixed0 |= 0x04;
        total_len += 2;
        break;
    default:
        e->errno = XFMQTT_ERRNO_INVALID_PARAMETER;
        return 0;
    }

    b += mqtt_write_uint8(b, headFixed0);

    if(0 == (ret = mqtt_write_lenght(b, total_len))) {
        e->errno = XFMQTT_ERRNO_PKT_TOO_LARGE;
        return 0;
    } else {
        b += ret;
    }

    b += mqtt_write_uint16(b, (uint16)topic_len);
    b += mqtt_write_bytes(b, packet->topic, topic_len);
    if(XFMQTT_QOS0 != packet->qos) {
        b += mqtt_write_uint16(b, packet->pkt_id);
    }

    if(0 < packet->sizePayload) {
        b += mqtt_write_bytes(b, packet->payload, packet->sizePayload);
    }

    //if((total_len - 1) != (b - pb - 1)) {
    //    e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
    //    return 0;
    //} 
    return (uint32)(b - pb);
}

static uint32 packet_disconnect(uint8 *b, XFMQTT_PacketPublish *packet, XFMQTT_Exception *e) {
    uint8 *pb = b;
    b += mqtt_write_uint8(b, XFMQTT_PACKET_TYPE_DISCONNECT);
    b += mqtt_write_uint8(b, 0);

    return 2;
}

static int unpacket_connack(XFMQTT_PacketConnack *packet, XFMQTT_PacketType type, uint8 *b, uint32 size, XFMQTT_Exception *e) {
    uint8 *pb = b;
    if(2 != size) {
        e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
        return 0;
    }

    b += mqtt_write_uint8(&packet->flagAck, *b);
    b += mqtt_write_uint8(&packet->retCode, *b);

    if(((packet->flagAck & 0x01) && (0 != packet->retCode)) || (packet->retCode > 5)) {
        e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
        return 0;
    }
    return (int)(b - pb);
}

static int unpacket_publish(XFMQTT_PacketPublish *packet, XFMQTT_PacketType type, uint8 *b, uint32 size, XFMQTT_Exception *e)
{
    const char dup = type & 0x08;
    const char qos = ((uint8)type & 0x06) >> 1;
    const char retain = type & 0x01;
    uint16 topic_len, pkt_id = 0;
    uint32 payload_len;

    char *cursor;
    int i = 0;

    if(size < 2) {
        e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
        return 0;
    }

    if(retain) {
        e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
        return 0;
    }

    b += mqtt_write_uint16((uint8*)(&topic_len), *((uint16*)b));
    if(size < (uint32)(2 + topic_len)) {
        e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
        return 0;
    }

    switch(qos) {
    case XFMQTT_QOS0: // qos0 have no packet identifier
        if(0 != dup) {
            e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
            return 0;
        }

        packet->topic = b;
        b += topic_len;

        payload_len = size - 2 - topic_len;
        break;

    case XFMQTT_QOS1:
    case XFMQTT_QOS2:
        packet->topic = b;
        b += topic_len;

        if(topic_len + 4 > size) {
            e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
            return 0;
        }

        b += mqtt_write_uint16((uint8*)(&pkt_id), *((uint16*)b));
        if(0 == pkt_id) {
            e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
            return 0;
        }
        payload_len = size - 4 - topic_len;
        break;

    default:
        e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
        return 0;
    }

    packet->payload = b;
    b += payload_len;
    packet->sizePayload = payload_len;

    //assert(NULL != topic);

    //packet->topic[topic_len] = '\0';

    if(mqtt_check_utf8(packet->topic, topic_len) != topic_len) {
        e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
        return 0;
    }

    cursor = packet->topic;
    for(i = 0; i < topic_len; i++) {
        if(('+' == *cursor) || ('#' == *cursor)) {
            e->errno = XFMQTT_ERRNO_ILLEGAL_PKT;
            return 0;
        }
        ++cursor;
    }

    return 0;
}


uint32 XFMQTT_PacketToBytes(uint8 *b, XFMQTT_Packet packet) {
    XFMQTT_Exception e = {0};
    int ret = 0;
    switch(packet.type) {
        case XFMQTT_PACKET_TYPE_CONNECT: {
            ret = packet_connect(b, &packet.data.connect, &e);
            break;
        }
        case XFMQTT_PACKET_TYPE_PUBLISH: {
            ret = packet_publish(b, &packet.data.publish, &e);
            break;
        }
        case XFMQTT_PACKET_TYPE_DISCONNECT: {
            ret = packet_disconnect(b, &packet.data.publish, &e);
        }
    }

    return ret;
}

uint32 XFMQTT_BytesToPacket(XFMQTT_Packet *packet, uint8 *b) {
    XFMQTT_Exception e = {0};

    b += mqtt_write_uint8(&packet->type, *(uint8*)b);
    b += mqtt_read_lenght(&packet->size, b, 4);

    switch(((uint8)packet->type)) {
    case XFMQTT_PACKET_TYPE_PINGRSP: {
        break;
    }
    case XFMQTT_PACKET_TYPE_CONNACK: {
        unpacket_connack(&packet->data.connack, packet->type, b, packet->size, &e);
        break;
    }
    case XFMQTT_PACKET_TYPE_PUBLISH: {
        unpacket_publish(&packet->data.publish, packet->type, b, packet->size, &e);
        break;
    }
    case XFMQTT_PACKET_TYPE_PUBACK: {
        break;
    }
    case XFMQTT_PACKET_TYPE_SUBACK: {
        break;
    }
    case XFMQTT_PACKET_TYPE_UNSUBACK: {
        break;
    }
    default:
        break;
    }

    return 0;
}

int XFMQTT_Unpacket(uint8 *b) {
    XFMQTT_Packet packet = {0};
    XFMQTT_Exception e = {0};

    b += mqtt_write_uint8(&packet.type, *(uint8*)b);
    b += mqtt_read_lenght(&packet.size, b, 4);

    switch(((uint8)packet.type)) {
    case XFMQTT_PACKET_TYPE_PINGRSP: {
        break;
    }
    case XFMQTT_PACKET_TYPE_CONNACK: {
        unpacket_connack(&packet.data.connack, packet.type, b, packet.size, &e);
        break;
    }
    case XFMQTT_PACKET_TYPE_PUBLISH: {
        unpacket_publish(&packet.data.publish, packet.type, b, packet.size, &e);
        break;
    }
    case XFMQTT_PACKET_TYPE_PUBACK: {
        break;
    }
    /*case XFMQTT_PACKET_TYPE_PUBREC: {
        break;
    }
    case XFMQTT_PACKET_TYPE_PUBREL: {
        break;
    }*/
    //case MQTT_PKT_PUBCOMP: {
    //    break;
    //}
    case XFMQTT_PACKET_TYPE_SUBACK: {
        break;
    }
    case XFMQTT_PACKET_TYPE_UNSUBACK: {
        break;
    }
    default:
        break;
    }

    if(NULL != mEventHandler.XFMQTT_EventCallback) {
        mEventHandler.XFMQTT_EventCallback(&packet, &e);
    }
    return 0;
}

void XFMQTT_EventHandlerSet(void (*XFMQTT_EventCallback)(XFMQTT_Packet *packet, XFMQTT_Exception *e)) {
    mEventHandler.XFMQTT_EventCallback = XFMQTT_EventCallback;
}

