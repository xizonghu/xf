#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <windows.h>

#include "xftypedef.h"
#include "xfutil.h"
#include "xfioreader.h"

uint16 timeout = 0;

uint16 getTickCount() {
	return GetTickCount();
}

int InitSock2()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	//WSAENETDOWN
	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
	return -1;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		 HIBYTE( wsaData.wVersion ) != 1 ) {
	WSACleanup();
	return -1;
	}

	return 0;
}

int startup(int port)
{
 int httpd = 0;
 struct sockaddr_in name;
unsigned long ul=1;   
  
 httpd = socket(AF_INET, SOCK_STREAM, 0);
 if (httpd == -1)return -1;
 if(0 > ioctlsocket(httpd,FIONBIO,(unsigned long *)&ul)) {//设置成非阻塞模式。
	 int err=WSAGetLastError();
	 return -2;
 }
 memset(&name, 0, sizeof(name));
 name.sin_family = AF_INET;
 name.sin_port = htons(port);
 name.sin_addr.s_addr = htonl(INADDR_ANY);
 if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
  return -3;

 if (listen(httpd, 5) < 0)
  return -4;
 return(httpd);
}

static uint16 sockReadData(int fd, void *buffer, uint16 size) {
    int ret =  recv((int)fd, buffer, size, 0);
	if(ret > 0) 
	{
		printf("sockReadData(%d): ret = %d\n", size, ret);
	} else {
		ret = 0;
	}
	return ret;
}

static uint16 sockGetBodySize(void *head, uint16 size) {
    uint16 len = 0;
    if (*((uint8*)head + len) != 0x7e) return (size + 1);
    for (len = 1; len < size; len++) {
        if (*((uint8*)head + len) == 0x5a) return (len - 4 + 1);
    }

    return (size + 1);
}

static void sockSetTimeout() {
    timeout = getTickCount() + 2000;
    printf("sockSetTimeout(): ======%d\n", timeout);
}

static uint8 sockIsTimeout() {
	//printf("sockIsTimeout(): %d,%d\n", timeout, getTickCount());
	if(timeout < getTickCount()) {
		printf("timeout\n");
		return 1;
	}
    return 0;
}

static void sockProcessData(void *buffer, uint16 size) {
    char buf[100];
    XF_ByteToHex(buf, buffer, size);
    printf("->: %s\n", buf);
}

int main() {
    XF_IOReader testreader = {0};
    XF_IOReaderIf testIf = {
		sockReadData,
        sockGetBodySize,
        sockSetTimeout,
        sockIsTimeout
    };
    XF_IOReaderCb testCb = {
        sockProcessData
    };
    char buffer222[60] = {0};
    char str[10] = {0};
    int size = 0;

	int server_sock = -1;
	 int port = 8888;
	 int client_sock = -1;
	 struct sockaddr_in client_name;
	 int client_name_len = sizeof(client_name);
	 int i = 0;
typedef union{ int ia; char c[4]; short int s[2]; }untest; untest un;  un.c[0]=0xAA;un.c[1]=0xBB; un.c[2]=0xCC;un.c[3]=0xDD; 
printf("%x,%x",un.ia, un.s[0]);
	InitSock2();
	 server_sock = startup(port);
	 printf("port %d\n", port);


    //
	 do {
      client_sock = accept(server_sock,
                       (struct sockaddr *)&client_name,
                       &client_name_len);
      if (client_sock == -1) continue;
	  else break;
	 }while(1);
      printf("client %d\n", client_sock);
      XF_IOReaderInit(&testreader, buffer222, sizeof(buffer222), 4, client_sock, &testIf, &testCb);
	while(1) {
		XF_IOReaderScan(&testreader);
    }
    return 0;
}
