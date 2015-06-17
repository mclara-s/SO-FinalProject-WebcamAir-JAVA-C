#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

/* Pacote a ser enviado para o cliente ! */
extern u8 serverPacket[50];
extern int packet_count = 0; // contador dos pacotes


/* Pacotes do Cliente/Servidor */

enum PACKET_SERVER {
    SERVER_PACKET_UNK        = 0xFFFEFEFF,
    SERVER_PACKET_LOGIN_AUTH = 0x000000E7,
    SERVER_PACKET_GOOD_PASS  = 0x00000000, // Todo o pacote é 0, apenas o último byte é 0x55, provavelmente checksum !
    SERVER_PACKET_BAD_PASS   = 0x000000F0  // Pacote tem esse valor, o resto é 0x0, último byte checksum ?
};

enum PACKET_CLIENT {
    CLIENT_PACKET_UNK        = 0xFFFEFEFF,
    CLIENT_PACKET_LOGIN_SEND = 0x000000E7,
};


/* Sistema de Pacotes */

// Limpa os pacotes
void clearPacket();
// Cabeça do Pacote 1
void writeHeader_1(u32 HEADER);
// Cabeça do Pacote 2
void writeHeader_2(u32 HEADER);
// Escreve um byte
void writeByte();
// Escreve 2 bytes
void writeShort();
// Escreve 4 bytes
void writeInt();
// Checksum
void writeChecksum();
// Ler 4 bytes
u32 readInt();
// Ler 2 bytes
u16 readShort();
// Ler 1 byte
u8  readByte();

/* Pacotes de Comunicação entre Cliente/Servidor */
// Pacote para fazer Login
void packet_Login();

/* Analisa cada pacote e sua estrutura para saber como 
tratar cada um */
void packetHandle();