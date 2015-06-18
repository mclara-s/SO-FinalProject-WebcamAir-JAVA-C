#include <errno.h>
//Bibliotecas socket
#include <sys/types.h>  //AF_INET
#include <sys/socket.h> //socket
#include <netinet/in.h> //htons
#include <arpa/inet.h> //inet_addr
#include <unistd.h>  //close
#include <iostream>
#include "packet2.h"
using namespace std;

/* configurações do IP e Porta do Servidor, IP do IMD */
static const char LG_IP[] = "10.7.204.2";
#define LG_PORTA 9002
#define DEBUG_MODE 1


/*Abrir arquivo com número de pessoas e calcular temperatura */
void getTemp(int &temp){

}

int main(int argc, char *argv[])
{
      int socketId, temp;
      struct sockaddr_in endereco;
      packet *Pacote = new packet();
      u8 *servP = new u8[50];
      int bytesLidos;

      if (socketId == -1)
      {
         perror("Error socket()\n");
         exit(1);
      }

      endereco.sin_family = AF_INET;
      endereco.sin_port = htons(LG_PORTA);  //MUDAR PARA LG_PORTA
      endereco.sin_addr.s_addr = inet_addr(LG_IP); // MUDAR PARA LG_IP
      bzero( &( endereco.sin_zero ), 8);
 
      if ( connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
      {
         perror("Error connect()\n");
         exit(1);
      }

      Pacote->packet_Login();
      Pacote->getServerPacket(servP);

     /*verificação se a cópia foi correta */
     printf ("\nservP: ");
     for (int i = 0; i < Pacote->getPacketCount(); i++)
        fprintf(stderr, " %X", servP[i]);

      
      int size = Pacote->getPacketCount();
      if ( send (socketId, servP, size, 0) == -1 )
            {
              perror ("Error send\n");
              exit(1);
            }

     while (true){
          //Recebendo um caracter do servidor
          if ( bytesLidos = recv (socketId, servP, size, 0) == -1 )
            {
              perror ("Error recv\n");
              exit(1);
            }

          /*Imprimir pacote recebido */
          for (int i = 0; i < Pacote->getPacketCount(); i++)
            fprintf(stderr, " %X", servP[i]);

          /*Packet Handle*/
          Pacote->packetHandle();

          //getTemp(temp);

          //Pacote->setTemp(temp);
     
          /* Enviar novos dados */  
          if ( send (socketId, servP, size, 0) == -1 )
            {
              perror ("Error send\n");
              exit(1);
            }
          sleep(1);       
      }
      close (socketId);
 
    return 0;
  }