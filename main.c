/************************************************************
** LG ACCS Fake Cliente - Desenvolvido por Lucas P. Stark  **
** O Sistema foi feito para possibilitar a integração com  **
** outros sistemas, como smartphone, embedded system e até **
** para criar um cliente melhor, já que o atual da LG tem  **
** algumas limitações, qualquer duvida: st4rkdev@gmail.com **
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "packet.h"



/* typedef */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

/* configurações do IP e Porta do Servidor, IP do IMD */
static const char LG_IP[] = "10.7.204.2";
#define LG_PORTA 9002
#define DEBUG_MODE 1

/* Pacotes de leitura e escrita que fica no packet.h/packet.c */
extern u8 serverPacket[50];


int main(int argc , char *argv[]) {
    WSADATA SocketData;                     /*SUBSTITUIR PARA O EQUIVALENTE DO LINUX */
    SOCKET clientSocket;                    /*SUBSTITUIR PARA O EQUIVALENTE DO LINUX */
    struct sockaddr_in server;              /*SUBSTITUIR PARA O EQUIVALENTE DO LINUX */
    int recv_size;

    printf("Inicializando conexao...\n");
    if (WSAStartup(MAKEWORD(2,2),&SocketData) != 0) {       /*SUBSTITUIR PARA O EQUIVALENTE DO LINUX */
        printf("Falha no Socket Startup!\n");
        exit(0);
    }

    /*SUBSTITUIR PARA O EQUIVALENTE DO LINUX */
    if((clientSocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {     
        printf("Nao foi possivel criar o socket !\n");
        exit(0);
    }

    /*SUBSTITUIR PARA O EQUIVALENTE DO LINUX */
    server.sin_addr.s_addr = inet_addr(LG_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons( LG_PORTA );

    /* Conectando ao servidor ! */
    if (connect(clientSocket, (struct sockaddr *)&server , sizeof(server)) < 0) {   /*SUBSTITUIR PARA O EQUIVALENTE DO LINUX */
        printf("nao foi possivel conectar ao servidor !\n");
        exit(0);
    }
    
    /* A partir do momento que estamos conectados ao servidor da LG, a gente
    precisa enviar o usuário para o servidor, nesse caso vamos utilizar
    o super user ! */
    printf("Conectado ao servidor da LG !\n");
    /* Primeiro pacote que enviamos para o servior com nossos dados ! */
    packet_Login();
    send(clientSocket, serverPacket, strlen(serverPacket), 0);
    /* Agora vai começar a troca de mensagens entre cliente e servidor, toda a troca
    de mensagens vai ser feita dentro desse loop ! */
    while (1) {


        
        /* Leitura de dados do servidor, escrevemos tudo no pacote serverPacket*/
        recv(clientSocket, serverPacket , 50 , 0);

        /* Verifica se o DEBUG mode está ativo, caso esteja, todos os pacotes recebidos
        será escrito em um arquivo */
#ifdef DEBUG_MODE
        for (i = 0; i < packet_count; i++) {
            printf(stderr," %X", serverPacket[i]);
        }
        fprintf(stderr,"\n");
#endif

        packetHandle();
        /* apenas para testes */
        Sleep(1);

        /* A função packetHandle vai verificar qual pacote estamos tratando, após isso fará
        a escrita de todas as informações necessárias e por fim enviamos o pacote para o servidor */
        send(clientSocket, serverPacket, 50 , 0);

    }

    /* Finaliza a conexão */
    closesocket(clientSocket);
    return 0;
}

