#include <stdio.h>
#include <string.h>

#include "xfhttpd.h"

//#define NULL 0
#define SERVER_STRING "Server: xfhttpd/1.0\r\n"
#define strcasecmp strcmp

#define HEADER_RESPONSE_200                          "HTTP/1.0 200 OK\r\n"
#define HEADER_RESPONSE_404                          "HTTP/1.0 404 NOT FOUND\r\n"
#define HEADER_CONTENT_TYPE_TEXT_HTML                "Content-Type: text/html\r\n"
#define HEADER_CONTENT_TYPE_APP_JSON                 "Content-Type: application/json\r\n"
#define HEADER_CONTENT_LENGTH                        "Content-Length: %d\r\n"
#define HTTP_CR_LF                                   "\r\n"
#define HTMLPAGE_NO_FOUND                            "<HTML><TITLE>Not Found</TITLE><BODY><P>unavailable</BODY></HTML>"
#define SIZEOFSTR(str)                               (sizeof(str) - 1)

typedef enum {
    XF_HTTPD_STATE_NONE = 0,
    XF_HTTPD_STATE_RUN,
} XF_HttpdState;

static XF_HttpdState mState = XF_HTTPD_STATE_NONE;

static const void *mWebRoot;
static const XF_HttpdSockIf *mSockIf;
static const XF_HttpdFsIf *mFsIf;
static const XF_HttpdJsonIf *mJsonIf;

static void not_found(int client) {
    char buf[50];
 
    mSockIf->send(client, HEADER_RESPONSE_404, SIZEOFSTR(HEADER_RESPONSE_404));
    mSockIf->send(client, HEADER_CONTENT_TYPE_TEXT_HTML, SIZEOFSTR(HEADER_CONTENT_TYPE_TEXT_HTML));
    sprintf(buf, HEADER_CONTENT_LENGTH, SIZEOFSTR(HTMLPAGE_NO_FOUND));
    mSockIf->send(client, buf, strlen(buf));
    mSockIf->send(client, HTTP_CR_LF, SIZEOFSTR(HTTP_CR_LF));
    mSockIf->send(client, HTMLPAGE_NO_FOUND, SIZEOFSTR(HTMLPAGE_NO_FOUND));
}

static void unimplemented(XF_HttpSock client) {
}

static unsigned int get_file_length(const char *filename) {
    char buf[1024];
    unsigned int size = 0, sum = 0;
    int resource = 0;

    if(0 >= (resource = mFsIf->fopen(filename, 0, 0))) {
        return 0;
    }   

    do {
        size = mFsIf->fread(resource, buf, sizeof(buf) - 1);
        sum += size;
    } while (size > 0);
    mFsIf->fclose(resource);
    return sum;
}

static void response_header_file(int client, const char *filename) {
    char buf[40];
	unsigned int size = 0;

    if(0 == (size = get_file_length(filename))) {
        not_found(client);
        return;
    }

    mSockIf->send(client, HEADER_RESPONSE_200, SIZEOFSTR(HEADER_RESPONSE_200));
    mSockIf->send(client, SERVER_STRING, SIZEOFSTR(SERVER_STRING));
    mSockIf->send(client, HEADER_CONTENT_TYPE_TEXT_HTML, SIZEOFSTR(HEADER_CONTENT_TYPE_TEXT_HTML));
    sprintf(buf, HEADER_CONTENT_LENGTH, size);
    mSockIf->send(client, buf, strlen(buf));
    mSockIf->send(client, HTTP_CR_LF, SIZEOFSTR(HTTP_CR_LF));
}

static void response_header_json(int client, void *json) {
    char buf[40];

    mSockIf->send(client, HEADER_RESPONSE_200, SIZEOFSTR(HEADER_RESPONSE_200));
    mSockIf->send(client, HEADER_CONTENT_TYPE_APP_JSON, SIZEOFSTR(HEADER_CONTENT_TYPE_APP_JSON));
    sprintf(buf, HEADER_CONTENT_LENGTH, strlen(json));
    mSockIf->send(client, buf, strlen(buf));
    mSockIf->send(client, HTTP_CR_LF, SIZEOFSTR(HTTP_CR_LF));
}

static void cat(int client, int resource) {
    char buf[1024];
    unsigned int size = 0;

    do {
        size = mFsIf->fread(resource, buf, sizeof(buf) - 1);
		buf[size] = '\0';
        mSockIf->send(client, buf, size);
    } while (size > 0);
}

static void response_file(int client, const char *filename) {
    int resource = NULL;

    if(0 >= (resource = mFsIf->fopen(filename, 0, 0))) {
        return;
    }

    cat(client, resource);
    mFsIf->fclose(resource);
}

static void response_json(int client, void *json) {
    mSockIf->send(client, json, strlen(json));
}

void XF_HttpdInit(const void *webroot, const XF_HttpdSockIf *sockIf, const XF_HttpdFsIf *fsIf, const XF_HttpdJsonIf *jsonIf) {
    mWebRoot = webroot;
    mSockIf = sockIf;
    mFsIf = fsIf;
    mJsonIf = jsonIf;
    mState = XF_HTTPD_STATE_RUN;
}

void XF_HttpdAcceptRequest(XF_HttpSock client) {
    char buf[1024];
    char result[1024];
    int numchars;
    char method[255];
    char url[255];
    char path[512];
    int fileFd;
    unsigned int pos = 0, i = 0;
    int cgi = 0;
    char *query_string = NULL;
    char *postContent = NULL;
    int sizePostContent = 0;

	if(XF_HTTPD_STATE_NONE == mState) return;
    numchars = mSockIf->recv(client, buf, sizeof(buf));
    buf[numchars] = '\0';

    for(pos = 0; (' ' != buf[pos]) && (pos < sizeof(buf) - 1) && (pos < sizeof(method) - 1); pos++) {
        method[pos] = buf[pos];
    }
    method[pos] = '\0';

    for(pos++, i = 0; (' ' != buf[pos])  && (pos < sizeof(buf) - 1) && (i < sizeof(url) - 1); pos++, i++) {
        url[i] = buf[pos];
    }
    url[i] = '\0';

    if (strcasecmp(method, "GET") == 0) {
        query_string = url;
        while ((*query_string != '?') && (*query_string != '\0')) query_string++;
        if (*query_string == '?') {
            cgi = 1;
            *query_string = '\0';
            query_string++;
        }
    }
    else if (strcasecmp(method, "POST") == 0) {
        if(postContent = (char *)strstr(buf, "\r\n\r\n")) {
            sizePostContent = postContent - buf - 4;
            cgi = 1;
        }
    }
    else {
        unimplemented(client);
    }

    sprintf(path, "%s%s", mWebRoot, url);
    if (path[strlen(path) - 1] == '/') strcat(path, "index.html");

    if (!cgi) {
        response_header_file(client, path);
        response_file(client, path);
    }
    else {
        mJsonIf->execute(result, postContent, sizePostContent);
		response_header_json(client, result);
        response_json(client, result);
    }

    mSockIf->close(client);
}

