#include"server_config.h"

int server_config(const char* ip, uint16_t port, int backlog){
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(fd == -1){
        handle_error("socket");
        return -1;
    }

    int optval = 1;

    setsockopt(fd, IPPROTO_TCP, SO_REUSEADDR, &optval, sizeof(optval));

    struct sockaddr_in address = {};
    
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    inet_pton(address.sin_family, ip, &address.sin_addr);
    socklen_t addresslen = sizeof(address); 

    int result_of_bind = bind(fd, (struct sockaddr*)&address, addresslen);

    if(result_of_bind == -1){
        handle_error("bind");
	    close(fd);
        return -1;
    }

    int result_of_listen = listen(fd, backlog);

    if(result_of_listen == -1){
    	handle_error("listen");
    	close(fd);
	    return -1;
    }

    return fd;
}