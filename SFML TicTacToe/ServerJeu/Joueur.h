#pragma once
#include <iostream>
#include <string>
#include <SFML\Network.hpp>

class Joueur {

public:
	Joueur(sf::TcpSocket* s);
	~Joueur();

	void setPseudo(const char* _pseudo);
	const char* getPseudo();

	void setSocket(sf::TcpSocket* _socket);
	sf::TcpSocket& getSocket();

private:
	const char* pseudo;
	sf::TcpSocket* socket;
};