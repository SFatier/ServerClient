#include "Joueur.h"

//initialise la socket avec la valeur de s
Joueur::Joueur(sf::TcpSocket* s):socket(s)
{

}

Joueur::~Joueur() {
}

void Joueur::setPseudo(std::string _pseudo) {
	pseudo = _pseudo;
}

std::string Joueur::getPseudo() {
	return pseudo;
}

std::string Joueur::getPseudo() const{
	return pseudo;
}

void Joueur::setSocket(sf::TcpSocket* _socket) {
	socket = _socket;
}

sf::TcpSocket& Joueur::getSocket() {
	return *socket;
}


sf::TcpSocket& Joueur::getSocket() const {
	return *socket;
}

void Joueur::setPion(Etat_case _pion) {
	pion = _pion;
}

Etat_case Joueur::getPion() {
	return pion;
}


