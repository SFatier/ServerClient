#include "Joueur.h"

//initialise la socket avec la valeur de s
Joueur::Joueur(sf::TcpSocket* s):socket(s)
{

}

void Joueur::setPseudo(const char* _pseudo) {
	pseudo = _pseudo;
}

const char* Joueur::getPseudo() {
	return pseudo;
}

void Joueur::setSocket(sf::TcpSocket* _socket) {
	socket = _socket;
}

sf::TcpSocket& Joueur::getSocket() {
	return *socket;
}
