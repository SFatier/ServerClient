#pragma once
#include <iostream>
#include <string>
#include <SFML\Network.hpp>
#include "Define.h"

class Joueur {

public:
	Joueur(sf::TcpSocket* s);
	~Joueur();

	void setPseudo(std::string _pseudo);
	std::string getPseudo();
	 std::string getPseudo() const;

	void setSocket(sf::TcpSocket* _socket);
	sf::TcpSocket& getSocket();
	sf::TcpSocket& getSocket() const;

	void setPion(Etat_case _pion);
	Etat_case getPion();

private:
	std::string pseudo;
	sf::TcpSocket* socket;
	Etat_case pion;
};