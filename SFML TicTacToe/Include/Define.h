#pragma once


//server
#define  MSG_WELCOME 0
#define  MSG_DEMANDE_TOURS 1
#define  MSG_DEMANDE_PSEUDO 2
#define  MSG_SCORE 3
#define  MSG_COMPLET 6

//client
#define MSG_RESPONSE_PSEUDO 4
#define MSG_RESPONSE_TOURS 5

#pragma pack(push, 1) 

struct MessageWelcome {
	int id;
	char msg[128];
};

#pragma pack(pop) 