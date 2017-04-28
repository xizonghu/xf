#ifndef __XF_MQTT_TANSMIT_H__
#define __XF_MQTT_TANSMIT_H__

extern int16 mqtt_Connect(int16 sd, const SlSockAddr_t *addr, int16 addrlen);
extern int16 mqtt_Recv(int16 sd, void *pBuf, int16 Len, int16 flags);
extern int16 mqtt_Send(int16 sd, const void *pBuf, int16 Len, int16 flags);

#endif
