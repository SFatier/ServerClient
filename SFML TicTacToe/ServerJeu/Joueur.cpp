#include "Joueur.h"

//initialise la socket avec la valeur de s
Joueur::Joueur(sf::TcpSocket* s)
:socket(s)
{

}

void Joueur::setPseudo(std::string _pseudo) {
	pseudo = _pseudo;
}

std::string Joueur::getPseudo() {
	return pseudo;
}


void Joueur::setSocket(sf::TcpSocket* _socket) {
	socket = _socket;
}

sf::TcpSocket& Joueur::getSocket() {
	return *socket;
}