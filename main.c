#include"server_config.h"
#include"clients.h"

int main(int argc, char** argv){
    
    char ipv4[INET_ADDRSTRLEN] = "127.0.0.1";
    uint16_t port = 3050;

    int fd = server_config(ipv4, port, 5);

    if(fd == -1){
        return -1;
    }

    pthread_t client_thread;
    int thread_ok = pthread_create(&client_thread, NULL, handle_client, (void*)&fd);

    int thread_joined = pthread_join(client_thread, NULL);

    close(fd);
    return 0;
}
