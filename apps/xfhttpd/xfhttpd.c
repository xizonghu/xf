

#include "xfhttpd.h"

#define NULL 0

typedef enum {
    XF_HTTPD_STATE_NONE = 0,
    XF_HTTPD_STATE_RUN,
} XF_HttpdState;

static XF_HttpdState mState = XF_HTTPD_STATE_NONE;

static XF_HttpdSockIf *mSockIf;
static XF_HttpdFsIf *mFsIf;
static XF_HttpdJsonIf *mJsonIf;

static int get_line(int sock, char *buf, int size) {
    int i = 0;
    char c = '\0';
    int n;
 
    while ((i < size - 1) && (c != '\n')) {
        n = mSockIf->recv(sock, &c, 1);
        if (n > 0) {
            if (c == '\r') {
                n = mSockIf->recv(sock, &c, 1);
                if ((n > 0) && (c == '\n')) mSockIf->recv(sock, &c, 1);
                else c = '\n';
            }
            buf[i] = c;
            i++;
        }
        else c = '\n';
    }
    buf[i] = '\0';

    return(i);
}

void XF_HttpdInit(const XF_HttpdSockIf *sockIf, const XF_HttpdFsIf *fsIf, const XF_HttpdJsonIf *jsonIf) {
    mSockIf = sockIf;
    mFsIf = fsIf;
    mJsonIf = jsonIf;
    mState = XF_HTTPD_STATE_RUN;
}

void XF_HttpdAcceptRequest(XF_HttpSock client) {
    char buf[1024];
    int numchars;
    char method[255];
    char url[255];
    char path[512];

    if(XF_HTTPD_STATE_NONE == mState) return;

    unsigned int i = 0, j = 0;
    int cgi = 0;
    char *query_string = NULL;

    numchars = get_line(client, buf, sizeof(buf));

    while ((' ' != buf[j]) && (i < sizeof(method) - 1)) {
        method[i] = buf[j];
        i++; j++;
    }
    method[i] = '\0';

 if (strcasecmp(method, "GET") && strcasecmp(method, "POST"))
 {
  unimplemented(client);
  return;
 }

 if (strcasecmp(method, "POST") == 0)
  cgi = 1;

 i = 0;
 while (ISspace(buf[j]) && (j < sizeof(buf)))
  j++;
 while (!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf)))
 {
  url[i] = buf[j];
  i++; j++;
 }
 url[i] = '\0';

 if (strcasecmp(method, "GET") == 0)
 {
  query_string = url;
  while ((*query_string != '?') && (*query_string != '\0'))
   query_string++;
  if (*query_string == '?')
  {
   cgi = 1;
   *query_string = '\0';
   query_string++;
  }
 }

 sprintf(path, "htdocs%s", url);
 if (path[strlen(path) - 1] == '/')
  strcat(path, "index.html");
 if (stat(path, &st) == -1) {
  while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
   numchars = get_line(client, buf, sizeof(buf));
  not_found(client);
 }
 else
 {
  if ((st.st_mode & S_IFMT) == S_IFDIR)
   strcat(path, "/index.html");
  if ((st.st_mode & S_IXUSR) ||
      (st.st_mode & S_IXGRP) ||
      (st.st_mode & S_IXOTH)    )
   cgi = 1;
  if (!cgi)
   serve_file(client, path);
  else
   execute_cgi(client, path, method, query_string);
 }

 close(client);
}

