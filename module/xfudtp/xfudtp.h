#ifndef __XF_UDTP_H__
#define __XF_UDTP_H__

typedef enum {
    TOI_DEVICE_NONE = (uint8)0,
    TOI_DEVICE_USER,
    TOI_DEVICE_SMART_DEVICE,
    TOI_DEVICE_SMART_GATEWAY,
    TOI_DEVICE_SMART_GATEWAY_WIFI,
    TOI_DEVICE_SMART_GATEWAY_ZIGBEE,
    TOI_DEVICE_SMART_GATEWAY_BLE,
    TOI_DEVICE_SMART_DEVICE_LOCK,
    TOI_DEVICE_CLOUD,
    TOI_DEVICE_SIZE
} TOI_Device;

typedef enum {
    TOI_PACKET_TYPE_NONE = (uint8)0,
    TOI_PACKET_TYPE_COMMAND,
    TOI_PACKET_TYPE_DATA,
    TOI_PACKET_TYPE_AUTHENTICATION,
    TOI_PACKET_TYPE_OK,
    TOI_PACKET_TYPE_ERR,
    TOI_PACKET_TYPE_SIZE
} TOI_PacketType;

typedef struct {
	uint8 size;
	uint8 data[0];
} TOI_Package;

typedef struct {
    uint8 dst;
	uint8 src;
	uint8 type;
} TOI_PacketHead;

typedef struct {
	uint8 size;
	uint8 data[0];
} TOI_PacketBody;

typedef struct {
    TOI_PacketHead head;
	TOI_PacketBody body;
} TOI_Packet;

////////////////////////////////////////////////////////////////////////////////////////////////////
//Ö¸ÎÆËø¶¨Òå
typedef enum {
    SMLOCK_PACKET_MODE_NONE = (uint8)0,
    SMLOCK_PACKET_MODE_RESPONSE,
    SMLOCK_PACKET_MODE_REQUEST,
    SMLOCK_PACKET_MODE_SIZE
} SMLOCK_PacketMode;

typedef enum {
    SMLOCK_PACKET_TYPE_NONE = (uint8)0,
    SMLOCK_PACKET_TYPE_OPEN,
    SMLOCK_PACKET_TYPE_UNLOCK_INFO,
    SMLOCK_PACKET_TYPE_BATTERY_INFO,
    SMLOCK_PACKET_TYPE_STORAGE_INFO,
} SMLOCK_PacketType;

typedef struct {
    uint8 mode;
    uint8 type;
    uint8 size;
    uint8 data[0];
} SMLOCK_Packet;


#endif

