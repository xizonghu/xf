#ifndef __XF_MQTT_H__
#define __XF_MQTT_H__

typedef struct {
    uint32 len;
    void *buffer;
} XFMQTT_Head;

typedef enum MqttError {
    XFMQTT_ERRNO_OK                       = (int16)0,  /**< 成功，无错误*/
    XFMQTT_ERRNO_OUTOFMEMORY              = -1, /**< 内存不足 */
    XFMQTT_ERRNO_ENDOFFILE                = -2, /**< 读数据失败，已到文件结尾*/
    XFMQTT_ERRNO_IO                       = -3, /**< I/O错误 */
    XFMQTT_ERRNO_ILLEGAL_PKT              = -4, /**< 非法的数据包 */
    XFMQTT_ERRNO_ILLEGAL_CHARACTER        = -5, /**< 非法的字符 */
    XFMQTT_ERRNO_NOT_UTF8                 = -6, /**< 字符编码不是UTF-8 */
    XFMQTT_ERRNO_INVALID_PARAMETER        = -7, /**< 参数错误 */
    XFMQTT_ERRNO_PKT_TOO_LARGE            = -8, /**< 数据包过大 */
    XFMQTT_ERRNO_BUF_OVERFLOW             = -9, /**< 缓冲区溢出 */
    XFMQTT_ERRNO_EMPTY_CALLBACK           = -10,/**< 回调函数为空 */
    XFMQTT_ERRNO_INTERNAL                 = -11,/**< 系统内部错误 */
    XFMQTT_ERRNO_NOT_IN_SUBOBJECT         = -12,/**< 调用Mqtt_AppendDPFinishObject，但没有匹配的Mqtt_AppendDPStartObject */
    XFMQTT_ERRNO_INCOMPLETE_SUBOBJECT     = -13,/**< 调用Mqtt_PackDataPointFinish时，包含的子数据结构不完整 */
    XFMQTT_ERRNO_FAILED_SEND_RESPONSE     = -14 /**< 处理publish系列消息后，发送响应包失败 */
} XFMQTT_Errno;

typedef enum MqttConnectFlag {
    XFMQTT_CONNECT_CLEAN_SESSION  = 0x02,
    XFMQTT_CONNECT_WILL_FLAG      = 0x04,
    XFMQTT_CONNECT_WILL_QOS0      = 0x00,
    XFMQTT_CONNECT_WILL_QOS1      = 0x08,
    XFMQTT_CONNECT_WILL_QOS2      = 0x10,
    XFMQTT_CONNECT_WILL_RETAIN    = 0x20,
    XFMQTT_CONNECT_PASSORD        = 0x40,
    XFMQTT_CONNECT_USER_NAME      = 0x80
} XFMQTT_PacketConnectFlag;


typedef enum {
    XFMQTT_PACKET_TYPE_CONNECT = (uint8)0x10,
    XFMQTT_PACKET_TYPE_CONNACK = (uint8)0x20,
    XFMQTT_PACKET_TYPE_PUBLISH = (uint8)0x30,
    XFMQTT_PACKET_TYPE_PUBACK  = (uint8)0x40,
    XFMQTT_PACKET_TYPE_SUBSCRIBE = (uint8)0x80,
    XFMQTT_PACKET_TYPE_SUBACK = 0x90,
    XFMQTT_PACKET_TYPE_UNSUBSCRIBE = 0xA0,
    XFMQTT_PACKET_TYPE_UNSUBACK = 0xB0,
    XFMQTT_PACKET_TYPE_PING = 0xC0,
    XFMQTT_PACKET_TYPE_PINGRSP = 0xD0,
    XFMQTT_PACKET_TYPE_DISCONNECT = 0xE0,
} XFMQTT_PacketType;

typedef enum MqttQosLevel {
    XFMQTT_QOS0,  /**< 最多发送一次 */
    XFMQTT_QOS1,  /**< 最少发送一次  */
    XFMQTT_QOS2   /**< 只发送一次 */
} XFMQTT_QosLevel;

typedef struct {
    uint16 keep_alive;
    const char *id;
    int clean_session;
    const char *will_topic;
    const char *will_msg;
    uint16 msg_len;
    XFMQTT_QosLevel qos;
    int will_retain;
    const char *user;
    const char *password;
    uint16 pswd_len;
} XFMQTT_PacketConnect;

typedef struct {
    uint8 flagAck;
    uint8 retCode;
} XFMQTT_PacketConnack;

typedef struct {
    uint8 ok;
} XFMQTT_PacketDisconnect;

typedef struct {
    uint16 pkt_id;
    char *topic;  //char topic[1];//在按1字节对齐的时候，如果data是个指针，那个该指针只能指向0~255的短地址。
    char *payload;
    uint32 sizePayload;
    XFMQTT_QosLevel qos;
    int retain;
    int own;
} XFMQTT_PacketPublish;

typedef union {
    XFMQTT_PacketConnect connect;
    XFMQTT_PacketPublish publish;
    XFMQTT_PacketConnack connack;
} XFMQTT_PacketData;

typedef struct {
    uint16 size;
    void *buf;
} XFMQTT_PacketData2;

typedef struct {
    XFMQTT_PacketType type;
    uint32 size;
    XFMQTT_PacketData data;
} XFMQTT_Packet;

typedef struct {
    int errno;
} XFMQTT_Exception;

typedef struct {
    const char *host;
    unsigned short port;
    const char *proid;
    const char *devid;
    const char *apikey;
    int dup;
    XFMQTT_QosLevel qos;
} XFMQTT_Config;

typedef struct {
    void (*XFMQTT_EventCallback)(XFMQTT_Packet *packet, XFMQTT_Exception *e);
} XFMQTT_EventHandler;
extern int XFMQTT_ConfigSet(XFMQTT_Config *config);
extern void XFMQTT_EventHandlerSet(void (*XFMQTT_EventCallback)(XFMQTT_Packet *packet, XFMQTT_Exception *e));
extern void *XFMQTT_PacketCreate(XFMQTT_Packet packet, void *arg);
extern void *XFMQTT_PacketDestroy(void *p);
extern uint32 XFMQTT_PacketToBytes(uint8 *b, XFMQTT_Packet packet);
extern uint32 XFMQTT_BytesToPacket(XFMQTT_Packet *packet, uint8 *b);
extern int XFMQTT_Unpacket(uint8 *b);//wrap

#endif
