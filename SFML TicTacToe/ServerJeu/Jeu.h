#pragma once
#include <vector>
#include <list>
#include "Joueur.h"
#include "Logger.h"
#include "Singleton.h"
#include <SFML/Network.hpp>
#include "Message.h"
#include <string>
#include <cstdlib>

using namespace sf;
using namespace std;

class Jeu {

public:
	Jeu(int _port);
	~Jeu();
	void Init();
	void Loop();
	void CreationJeu();
	bool CheckPseudoJoueur();
	void SendPseudoJoueur();
	void ReponsePseudoJoueur(MessageWelcome* s, Joueur* client);
	void TourJoueur(Joueur* client, ReceptionCoup* r);
	void DemandePremierTour(Joueur* client);


private :
	int port;
	bool running;
	std::vector<Joueur*> _joueurs; //tab de pointeur
	Etat_case plateau_jeu[3][3];

};