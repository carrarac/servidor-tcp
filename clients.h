#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
typedef struct {
	char* content;
	size_t size;
} CachedResponse;

void* handle_client(void* args);
int init_index_cache(const char* filepath);
