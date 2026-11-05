#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdint.h>
#define handle_error(msg) \
    do { \
        char fmtmsg[256]; \
        snprintf(fmtmsg, sizeof(fmtmsg), "server_config: %s", msg); \
        perror(msg); \
    }  while(0)

int server_config(const char* ip, uint16_t port, int backlog);
