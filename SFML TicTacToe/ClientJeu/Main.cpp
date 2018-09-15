#include "SFML\Network.hpp"
#include <iostream>
#include <cstdlib>
#include <Define.h>
#include <string>
#include "Logger.h"
#include <sstream>

using namespace std;
using namespace sf;


void AttenteCoupAdversaire(TcpSocket& socket) {
	char buf[255];
	size_t received;

	if (socket.receive(buf, 255, received) != sf::Socket::Done) {
		Logger::getInstance().log("Erreur lors de la reception du message");
	}
	else
	{
		std::stringstream buffer;
		buffer << ">>" << (int)buf[0];
		Logger::getInstance().log(buffer.str());
	}


	ReceptionCoup* r = (ReceptionCoup*)& buf;
	cout << "[" << r->id << "] L'adversaire a joué en x " << r->coordonneeX << " et en y " << r->coordonneeY << endl;
}

void Joue(TcpSocket* socket )
{
	size_t received;
	bool fini = false;
	MessageTexte* s;

	while (!fini)
	{
		// On envoi le tour du joueur
		ReceptionCoup r;

		cout << "Coordonnee x :" << endl;
		cin >> r.coordonneeX;
		cout << "Coordonnee y:" << endl;
		cin >> r.coordonneeY;
		r.id = MSG_ENVOI_COUP;

		sf::Socket::Status status = socket->send((char*)&r, sizeof(ReceptionCoup));
		if (status != sf::Socket::Done) {
			Logger::getInstance().log("Erreur : Coup non envoye");
		}

		// On attend de savoir si le coup a ete accepte
		char buf[255];
		memset(buf, 0, 255);
		if (socket->receive(buf, 255, received) != sf::Socket::Done) {
			Logger::getInstance().log("Erreur : Coup non accepte");
		}

		s = (MessageTexte*)& buf;

		if (buf[0] == MSG_ACCEPTER_TOUR)
		{
			std::cout << "MSG_ACCEPTER_TOUR " << s->msg << std::endl;
			fini = true;
		}
		else if (buf[0] == MSG_REFUSER_TOUR)
		{
			std::cout << "MSG_REFUSER_TOUR " << s->msg << std::endl;
		}
	}
}

int main()
{

	MessageTexte* s = 0;
	ReceptionCoup* r = 0;
	sf::IpAddress server;
	sf::TcpSocket socket;
	std::string msg_recu, msg_envoye;
	const unsigned short port = 55001;

	server = "127.0.0.1";

	if (socket.connect(server, port) != sf::Socket::Done) {
		return  -1;
	}

	bool rejouer = false;
	char buf[255];
	size_t received;

	if (socket.receive(buf, 255, received) != sf::Socket::Done) {
		return -1;
	}
	else
	{
		std::stringstream buffer;
		buffer << ">>" << (int)buf[0];
		Logger::getInstance().log(buffer.str());
	}


	s = (MessageTexte*)& buf;
	r = (ReceptionCoup*)& buf;

	sf::Socket::Status status;
	char* pseudo_client = "";

	switch (s->id)
	{
	case MSG_WELCOME:
		cout << "[" << s->id << "] " << s->msg << endl;
		break;

	case MSG_COMPLET:
		cout << "La partie est complete appuyez sur une touche pour terminer…" << endl;
		std::cin.ignore();
		return 0;
	}

	//reinitialise le buffer
	memset(buf, 0, 255);

	if (socket.receive(buf, 255, received) != sf::Socket::Done) {
		return -1;
	}
	else
	{
		std::stringstream buffer;
		buffer << ">>" << (int)buf[0];
		Logger::getInstance().log(buffer.str());
	}


	s = (MessageTexte*)& buf;
	string messages;
	if (s->id == MSG_DEMANDE_PSEUDO) {
		cout << "Entrez votre pseudo :" << endl;
		cin >> messages;

		MessageTexte _message;
		_message.id = MSG_RESPONSE_PSEUDO;
		strcpy(_message.msg, messages.c_str());
		status = socket.send((char*)&_message, sizeof(MessageTexte));
		if (status != sf::Socket::Done) {
			throw "Erreur envoie pseudo";
		}
	}

	memset(buf, 0, 255);
	if (socket.receive(buf, 255, received) != sf::Socket::Done) {
		return -1;
	}

	s = (MessageTexte*)& buf;

	if (s->id == MSG_ENVOI_PSEUDO) {
		cout << "Votre adversaire est " << s->msg << endl;
	}

	bool playing = true;
	   	 
	/*memset(buf, 0, 255);
	if (socket.receive(buf, 255, received) != sf::Socket::Done)
	{
		return -1;
	}
	else
	{
		std::stringstream buffer;
		buffer << ">>" << (int)buf[0];
		Logger::getInstance().log(buffer.str());
	}*/




	while (playing) {

		memset(buf, 0, 255);
		if (socket.receive(buf, 255, received) != sf::Socket::Done) {
			return -1;
		}
		else
		{
			std::stringstream buffer;
			buffer << ">>" << (int)buf[0];
			Logger::getInstance().log(buffer.str());
		}

		if (buf[0] == MSG_ADVERSAIRE_TOUR)
		{
			std::cout << "MSG_ADVERSAIRE_TOUR" << std::endl;

			r = (ReceptionCoup*)& buf;
			cout << "Adveraire a joue " << r->coordonneeX << " et " << r->coordonneeY << endl;

		}
		else if (buf[0] == MSG_DEMANDE_TOURS)
		{
			std::cout << "MSG_DEMANDE_TOURS" << std::endl;
			Joue(&socket);
		}
		else if (buf[0] == MSG_SCORE)
		{
			s = (MessageTexte*)& buf;

			cout << "MSG_SCORE " << s->msg << endl;
			playing = false;
		}
	}

	cout << "appuyez sur entrer pour termine" << endl;
	cin.ignore();
	cin.ignore();

	return 0;
}