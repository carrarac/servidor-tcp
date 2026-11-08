#include"clients.h"

static void* error_msg(const char* msg){
    char errmsg[256];
    snprintf(errmsg, sizeof(errmsg), "client: %s", msg);
    perror(errmsg);

    return NULL;
}

void* handle_client(void* args){
    int32_t client_socket = *((int32_t*)args);

    free(args);

    if(client_socket == -1)
        return error_msg("handle_client invalid arg");

    char msg[256] = {};
    strncpy(msg, "ok", sizeof(msg));
    size_t bytes_sent = send(client_socket, msg, strlen(msg), 0);

    printf("%zu B\n", bytes_sent);

    close(client_socket);
    return NULL;
}
