#include"clients.h"

static void* error_msg(const char* msg){
    char errmsg[256];
    snprintf(errmsg, sizeof(errmsg), "client: %s", msg);
    perror(errmsg);

    return NULL;
}

void* handle_client(void* args){
    int32_t *server_socket = (int32_t*)args;

    if(*server_socket == -1)
        return error_msg("handle_client invalid arg");

    struct sockaddr_in client_address;
    socklen_t client_addresslen = sizeof(struct sockaddr_in);

    int32_t client_socket = accept(*server_socket, (struct sockaddr*)&client_address, &client_addresslen);

    if(client_socket == -1)
        return error_msg("accept client_socket");

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
    char success[256] = {};
    snprintf(success, sizeof(success), "Client connected -> %s:%d", client_ip, ntohs(client_address.sin_port));
    printf("%s\n", success);

    //TODO: client loop

    char msg[256] = {};
    strncpy(msg, "ok", sizeof(msg));
    size_t bytes_sent = send(client_socket, msg, strlen(msg), 0);

    printf("%zu B\n", bytes_sent);

    close(client_socket);
    return NULL;
}
