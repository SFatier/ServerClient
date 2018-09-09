#pragma once
#include <iostream>
#include <string>
#include <SFML\Network.hpp>

class Joueur {

public:
	Joueur(sf::TcpSocket* s);
	~Joueur();

	void setPseudo(std::string _pseudo);
	std::string getPseudo();

	void setSocket(sf::TcpSocket* _socket);
	sf::TcpSocket* getSocket();

private:
	std::string pseudo;
	sf::TcpSocket* socket;
};