#pragma once
#include <iostream>
#include <string>
#include <SFML\Network.hpp>

class Joueur {

public:
	Joueur(sf::TcpSocket* s);
	~Joueur();

private:
	std::string pseudo;
	sf::TcpSocket* socket;
};