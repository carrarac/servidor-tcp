#include"server_config.h"
#include"clients.h"


int main(int argc, char** argv){
    
    char ipv4[INET_ADDRSTRLEN] = "127.0.0.1";
    uint16_t port = 3050;
    
    int fd = server_config(ipv4, port, 5);
    
    if(fd == -1){
        return -1;
    }
    struct sockaddr_in client_address;
    socklen_t client_addresslen = sizeof(client_address);

    printf("Servidor iniciado em %s:%d\n", ipv4, port);

    while(1){

        int32_t client_socket = accept(fd, (struct sockaddr*)&client_address, &client_addresslen);
        if(client_socket){
            perror("erro no accept");
            continue;
        }

        int32_t *new_socket = malloc(sizeof(int32_t));

        if(!new_socket){
            perror("erro ao alocar memoria para o socket");
            close(client_socket);
            continue;
        }
        *new_socket = client_socket;

        pthread_t thread_id;

        if(pthread_create(&thread_id, NULL, handle_client, (void*)new_socket) != 0) {
            perror("Erro ao criar thread\n");
            free(new_socket);
            close(client_socket);
            continue;
        }

        pthread_detach(thread_id);
    }

    close(fd);
    return 0;
}
