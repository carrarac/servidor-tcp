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

    char buffer[1024];
    size_t bytes_recvd;

    while(1){
        memset(buffer, 0, sizeof(buffer));

        bytes_recvd = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

        if(bytes_recvd < 0){
            perror("erro ao receber dados do cliente");
            break;
        } else if(bytes_recvd == 0){
            printf("cliente desconectou\n");
            break;
        }

        printf("Mensagem recebida: %s", buffer);

        send(client_socket, buffer, bytes_recvd, 0);
    }

    close(client_socket);
    return NULL;
}
