#pragma once


//server
#define  MSG_WELCOME 0
#define  MSG_DEMANDE_TOURS 1
#define  MSG_DEMANDE_PSEUDO 2
#define  MSG_SCORE 3
#define  MSG_COMPLET 6
#define  MSG_ENVOI_PSEUDO 7
#define  MSG_ACCEPTER_TOUR 8
#define MSG_REFUSER_TOUR 9
#define MSG_ADVERSAIRE_TOUR 11

//client
#define MSG_RESPONSE_PSEUDO 4
#define MSG_RESPONSE_TOURS 5
#define MSG_ENVOI_COUP 10

enum Etat_case {
	etat_non_utilise,
	etat_o,
	etat_x,
	etat_egalite
};


#pragma pack(push, 1) 

struct MessageTexte {
	char id;
	char msg[128];
};

struct ReceptionCoup {
	char id;
	int coordonneeX;
	int coordonneeY;
};


#pragma pack(pop) 