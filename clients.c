#include"clients.h"

static void error_msg(const char* msg){
    char errmsg[256];
    snprintf(errmsg, sizeof(errmsg), "client: %s", msg);
    perror(errmsg);

    return;
}

int init_index_cache(const char* filepath){
	FILE* f = fopen(filepath, "rb");

	if(!f){
		char msg[256] = {};
		snprintf(msg, sizeof(msg), "Erro ao abrir arquivo %s", filepath); 
		error_msg(msg);
		return -1;
	}
	struct stat st;
	if(stat(filepath, &st) < 0){
		fclose(f);
		return -1;
	}
	char header[256] = {};
}


void* handle_client(void* args){
    int32_t client_socket = *((int32_t*)args);

    free(args);

    if(client_socket == -1 || !client_socket)
        return error_msg("handle_client argumento invalido");

    char buffer[1024] = {};
    char ret_msg[256] = {};
    ssize_t bytes_recvd;

    while(1){
        
        bytes_recvd = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

        if(bytes_recvd < 0){
            error_msg("erro ao receber dados do cliente");
            break;
        } else if(bytes_recvd == 0){
            printf("cliente desconectou\n");
            break;
        }

	char* substr = strstr(buffer, "GET /");
	
       	if(substr){
		printf("Requisitou GET: %s\n", substr);
		strncpy(ret_msg, "", sizeof(ret_msg));
		send(client_socket, ret_msg, sizeof(ret_msg), 0);
	}
	else if(substr == buffer){
		printf("Mensagem vazia\n");
		strncpy(ret_msg, "Not Found", sizeof(ret_msg));
		send(client_socket, ret_msg, sizeof(ret_msg), 0);
	}
	else {
		printf("Requisicao nao reconhecida (404)\n");
		strncpy(ret_msg, "404: Not Found", sizeof(ret_msg));
		send(client_socket, ret_msg, sizeof(ret_msg), 0);
	}
	memset(ret_msg, 0, sizeof(ret_msg));
	memset(buffer, 0, sizeof(buffer));	
    }

    close(client_socket);
    return NULL;
}
