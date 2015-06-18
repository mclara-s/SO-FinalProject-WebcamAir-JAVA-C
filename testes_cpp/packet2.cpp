#include "packet2.h"

packet::packet(){
	packet_count = 0;
}

packet::~packet(){

}

void packet::getServerPacket(u8 *pack){
	printf("serverPacket: ");
	for (int i = 0; i < packet_count; ++i){
		pack[i] = serverPacket[i];
		fprintf(stderr, " %X", serverPacket[i]);
	}
}

void packet::setServerPacket(u8 *pack){
	for (int i = 0; i < packet_count; ++i)
		serverPacket[i] = pack[i];
}

int packet::getPacketCount(){
	return packet_count;
}

// Limpa os pacotes
void packet::clearPacket(){
	memset(serverPacket, 0x0, 50);
    packet_count = 0;
}

// Cabeça do Pacote 1
void packet::writeHeader_1(u32 HEADER){
	memcpy(serverPacket, &HEADER, sizeof(HEADER));
    packet_count += 4;
}

// Cabeça do Pacote 2
void packet::writeHeader_2(u32 HEADER){
	memcpy(serverPacket + 4, &HEADER, sizeof(HEADER));
    packet_count += 4;
}

// Escreve um byte
void packet::writeByte(u8 b){
	serverPacket[packet_count] = b;
    packet_count++;
}

// Escreve 2 bytes
void packet::writeShort(u16 s){
    memcpy(serverPacket + packet_count, &s, 2);
    packet_count += 2;
}

// Escreve 4 bytes
void packet::writeInt(u32 i){
    memcpy(serverPacket + packet_count, &i, 4);
    packet_count += 4;
}


void packet::writeChecksum(){

}

// Ler 4 bytes
u32 packet::readInt(){
    u32 packet = serverPacket[packet_count];
    packet_count++;
    packet = ((serverPacket[packet_count] << 8)  | packet);
    packet_count++;
    packet = ((serverPacket[packet_count] << 16) | packet);
    packet_count++;
    packet = ((serverPacket[packet_count] << 24) | packet);
    packet_count++;
    return packet;
}

// Ler 2 bytes
u16 packet::readShort(){
    u16 packet = serverPacket[packet_count];
    packet_count++;
    packet = ((serverPacket[packet_count] << 8)  | packet);
    packet_count++;
    return packet;
}

// Ler 1 byte
u8  packet::readByte(){
    u8 packet = serverPacket[packet_count];
    packet_count++;
    return packet;
}

/* Pacotes de Comunicação entre Cliente/Servidor */
// Pacote para fazer Login
void packet::packet_Login(){
    /* Onde o nosso login fica salvo ! */
    char superuser[20];
    /* Limpa a string do login ! */
    memset(superuser, 0, 20);

    printf("Digite a senha do super-user:\n");
    scanf("%s", superuser);
    //printf("%s", superuser);

    /* Pacote com o login do cliente, lembre-se que isso é para super user ! */
    /*OBS (MC): ESSES DADOS SÃO SÓ PARA O LOGIN? AO FINAL DEVO ACRESCENTAR A SENHA QUE ESTÁ ARMAZENADA
    EM SUPERUSER?*/
    writeInt(CLIENT_PACKET_UNK); // Pacote desconhecido, pode ser um head
    writeInt(CLIENT_PACKET_LOGIN_SEND); // Provavelmente o header para Login
    writeByte(0x09);
    writeShort(0x0DBF);
    writeInt(0x65747365);
    writeByte(0x74);
    writeShort(0x0A0D); // Desconhecido
    writeByte(0x1C); // Checksum ?   /*VERIFICAR CODIGO DO CHECKSUM NO JAVA*/ 

}

/* Analisa cada pacote e sua estrutura para saber como 
tratar cada um */
void packet::packetHandle(){
    u32 HEADER_1 = readInt();
    u32 HEADER_2 = readInt();

    switch (HEADER_1) {
        

        default:
            printf("Packet Invalido ou nao implementado: 0x%X\n", HEADER_1);
        break;
    }
}

void packet::setData(u32 temp){
 	/*DESCOBRIR COMO CRIAR O PACOTE COM AS INFORMAÇÕES:
 		--> CODIGO PRA ALTERAR A TEMPERATURA
 		--> VALOR DESEJADO DA TEMPERATURA*/
 }
