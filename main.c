#include"server_config.h"

int main(int argc, char** argv){
    
    char ipv4[INET_ADDRSTRLEN] = "127.0.0.1";
    uint16_t port = 3050;

    int fd = server_config(ipv4, port, 5);

    if(fd < 0){
        return -1;
    }
    
    return 0;
}
