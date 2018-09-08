#pragma once
#include <vector>
#include "Joueur.h"
#include <SFML/Network.hpp>

class Jeu {

public:
	Jeu();
	~Jeu();
	void AttendreJoueur();

private :
	bool running;
	std::vector<Joueur*> _joueurs; //tab de pointeur
	
};