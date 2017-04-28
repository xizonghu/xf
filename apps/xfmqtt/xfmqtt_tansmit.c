//#pragma pack(1)
#include "stdio.h"
#include "stdlib.h"

#include "socket.h"
#include "cJSON.h"
//#include "xftypedef.h"
#include "define_head.h"
#include "xfudtp.h"
#include "xfmqtt.h"

#define DEV_USER   "83080"
#define DEV_PASSWD "C89346DA4374"
#define DEV_ID     "5096328"

#define TOPIC_UNLOCK_INFO      "UNLOCK_INFO"
#define TOPIC_BATTERY_INFO     "BATTERY_INFO"
#define TOPIC_STORAGE_INFO       "STORAGE_INFO"

const XFMQTT_Packet mpktConnect = {
    XFMQTT_PACKET_TYPE_CONNECT,
	0,
    {
        1200,
        DEV_ID,
        1,
        NULL,
        NULL,
        0,
        XFMQTT_QOS0,
        0,
        DEV_USER,
        DEV_PASSWD,
        sizeof(DEV_PASSWD) - 1,
    },
};
const XFMQTT_Packet mpktDisconnect = {
    XFMQTT_PACKET_TYPE_DISCONNECT,
	0,
};

XFMQTT_Packet mpktPublish = {
    XFMQTT_PACKET_TYPE_PUBLISH,
	0,
    {
        1,
        "$dp",
        NULL,
        0,
        XFMQTT_QOS0,
        0,
        0,
    }
};

//static uint8 mInit = 0;
//static uint8 buff[1024] = {0};
//static uint8 str[1024] = {0};

static uint16 yds_unwrap_data(communication_packet *yds, uint8 *data) {
    data = yds->command_dp;
    return yds->cph.packet_len - sizeof(communication_packet_head) - sizeof(communication_links) - 1;
}

static uint16 yds_wrap_data(communication_packet *yds, uint8 *data, uint16 size) {
    return 0;
}

static uint16 payload_unwrap_data(uint8 *payload, uint16 size, uint8 *data) {
    data = payload;
    return size;
}

static uint16 payload_wrap_data(uint8 *payload, uint8 * dsid, uint8 *data, uint32 size) {
    char dp_type = 0x02 & 0xFF;
    uint32 ds_info_len = 0;
    char *ds_info_str = NULL;
    cJSON *ds_info = cJSON_CreateObject();
    uint32 bin_offset = 0;
    int ret = XFMQTT_ERRNO_OK;
	int32 payload_size;

    cJSON_AddStringToObject(ds_info, "ds_id", dsid);

    ds_info_str = cJSON_Print(ds_info);
    ds_info_len = strlen(ds_info_str);

    //printf("save data type 2(binary),length:%d,\njson:%s\n", ds_info_len, ds_info_str);

    //payload的总长庿 
    payload_size = 1 + 2 + ds_info_len + 4 + size;

    //填充payload
    payload[0] = dp_type;
    payload[1] = (ds_info_len>>8)&0xFF;
    payload[2] = ds_info_len & 0xFF;
    memcpy(payload+3, ds_info_str, ds_info_len);
    bin_offset = 1 + 2 + ds_info_len;
    payload[bin_offset] = (size>>24) & 0xFF;
    payload[bin_offset+1] = (size>>16) & 0xFF;
    payload[bin_offset+2] = (size>>8) & 0xFF;
    payload[bin_offset+3] = size & 0xFF;
    memcpy(payload + bin_offset + 4,
           data, size);

    cJSON_Delete(ds_info);
    return payload_size;
}

int16 mqtt_Connect(int16 sd, const SlSockAddr_t *addr, int16 addrlen) {
    int ret = 0;
    uint8 buf[50] = {0};
    //连接
    if(0 > (ret = sl_Connect(sd, addr, addrlen))) {
        return ret;
    }

    ret = XFMQTT_PacketToBytes(buf, mpktConnect);
    //socket send
    sl_Send(sd, buf, ret, 0);
    return ret;
}

int16 mqtt_Recv(int16 sd, void *pBuf, int16 Len, int16 flags) {
    uint8 buf1[128] = {0};//{0x30, 0x41, 0x00, 0x2A, 0x24, 0x63, 0x72, 0x65, 0x71, 0x2F, 0x31, 0x34, 0x30, 0x62, 0x63, 0x37, 0x62, 0x63, 0x2D, 0x64, 0x35, 0x39, 0x35, 0x2D, 0x35, 0x65, 0x32, 0x66, 0x2D, 0x39, 0x33, 0x32, 0x63, 0x2D, 0x63, 0x62, 0x63, 0x65, 0x38, 0x31, 0x65, 0x33, 0x65, 0x61, 0x66, 0x38, 0x12, 0x7C, 0x5C, 0x28, 0x12, 0x08, 0x08, 0x02, 0x09, 0x03, 0xC5, 0x59, 0x06, 0x25, 0x07, 0x08, 0x01, 0x03, 0x02, 0x01, 0x00};
    uint8 buf2[128] = {0};
    XFMQTT_Packet packet  = {0};
    TOI_Packet *toi = 0;
    communication_packet *yds = 0;
    uint8 *b = 0, *payload = 0;
    SMLOCK_Packet *smlock = 0;
    int16 ret = 0;

    //socket接收
    b = buf1;
    if(0 >= (ret = sl_Recv(sd, b, Len, flags))) {
        return ret;
    }

    //从mqtt序列解包出payload
    XFMQTT_BytesToPacket(&packet, b);
    if(XFMQTT_PACKET_TYPE_PUBLISH != packet.type) {
        return -11;
    }

    //从payload解包出data
	yds = (communication_packet *)packet.data.publish.payload;
	ret = packet.data.publish.sizePayload;
    //payload_unwrap_data(packet.data.publish.payload, packet.data.publish.sizePayload, yds);

    //拷贝
    memcpy(pBuf, yds, ret);
    return ret;
}

int16 mqtt_Send(int16 sd, const void *pBuf, int16 Len, int16 flags) {
    uint8 buf1[128] = {0};
    uint8 buf2[128] = {0};
    TOI_Packet *toi = (TOI_Packet *)buf2;
    communication_packet *yds = (communication_packet *)pBuf;
    SMLOCK_Packet *smlock = 0;
    uint8 *payload = buf1;
    uint8 *topic = 0;
    uint16 ret = 0;
    uint8 type = 0;

    //if(0 == (ret = yds_unwrap_data(yds, toi))) {
    //    return 0;
    //}
    type = *((uint8*)pBuf + sizeof(communication_packet_head) + sizeof(communication_links) + 1 + 4 + 1);
    switch(type) {
        case SMLOCK_PACKET_TYPE_UNLOCK_INFO: {
            topic = TOPIC_UNLOCK_INFO;
            break;
        }
        case SMLOCK_PACKET_TYPE_BATTERY_INFO: {
            topic = TOPIC_BATTERY_INFO;
            break;
        }
        case SMLOCK_PACKET_TYPE_STORAGE_INFO: {
            topic = TOPIC_STORAGE_INFO;
            break;
        }
    }

    //将序列化数组封装成payload
    if(0 == (ret = payload_wrap_data(payload, topic, (uint8*)yds, Len))) {
        return 0;
    }

    //将payload封装成mqtt序列
    mpktPublish.data.publish.payload = payload;
    mpktPublish.data.publish.sizePayload = ret;
    ret = XFMQTT_PacketToBytes(buf2, mpktPublish);

    //socket发送
    ret = sl_Send(sd, buf2, ret, flags);

    return Len;
}