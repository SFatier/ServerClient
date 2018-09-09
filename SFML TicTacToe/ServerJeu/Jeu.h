#pragma once
#include <vector>
#include <list>
#include "Joueur.h"
#include <SFML/Network.hpp>
#include "Message.h"
#include <string>

using namespace sf;
using namespace std;

enum Etat_case {
	non_utilise,
	etat_o,
	etat_x
};

class Jeu {

public:
	Jeu(int _port);
	~Jeu();
	void Loop();
	void CreationJeu();
	bool CheckPseudoJoueur();
	//void AttendreJoueur();


private :
	int port;
	bool running;
	std::vector<Joueur*> _joueurs; //tab de pointeur
	std::vector<Etat_case> plateau_jeu;
	//std::vector<string*> _pseudoJoueurs; //tab de pseudo des joueurs
	
};