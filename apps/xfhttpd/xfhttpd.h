#ifndef __XF_HTTPD_H__
#define __XF_HTTPD_H__

typedef int XF_HttpSock;

typedef struct {
    int (*send)(XF_HttpSock sock, void *buf, unsigned int size);
    int (*recv)(XF_HttpSock sock, void *buf, unsigned int size);
    void (*close)(XF_HttpSock sock);
} XF_HttpdSockIf;

typedef struct {
    int (*fopen)(const char *filename, int flag, int mode);
    unsigned int (*fread)(int fd, void *buf, unsigned int size);
    void (*fclose)(int fd);
} XF_HttpdFsIf;

typedef struct {
    unsigned int (*execute)(void *result, unsigned int sizeResult, void *inputStream, unsigned int sizeInputStream);
} XF_HttpdJsonIf;

extern void XF_HttpdInit(const void *webroot, const XF_HttpdSockIf *sockIf, const XF_HttpdFsIf *fsIf, const XF_HttpdJsonIf *jsonIf);
extern void XF_HttpdAcceptRequest(XF_HttpSock client);

#endif
