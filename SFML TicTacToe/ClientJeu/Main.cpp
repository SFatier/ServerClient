#include "SFML\Network.hpp"
#include <iostream>
#include <cstdlib>
#include <Define.h>
#include <string>
#include "Logger.h"

using namespace std;
using namespace sf;


void JeuJoueur(TcpSocket& socket) {
	ReceptionCoup r;

	cout << "Coordonnee x :" << endl;
	cin >> r.coordonneeX;

	cout << "Coordonnee y:" << endl;
	cin >> r.coordonneeY;

	r.id = MSG_ENVOI_COUP;

	sf::Socket::Status status = socket.send((char*)&r, sizeof(ReceptionCoup));
	if (status != sf::Socket::Done) {
		Logger::getInstance().log("Erreur : Coup non envoye");
	}

}

void AttenteCoupAdversaire(TcpSocket& socket) {
	char buf[255];
	size_t received;

	if (socket.receive(buf, 255, received) != sf::Socket::Done) {
		Logger::getInstance().log("Erreur lors de la reception du message");
	}

	ReceptionCoup* r = (ReceptionCoup*)& buf;
	cout << "[" << r->id << "] L'adversaire a joué en x " << r->coordonneeX<< " et en y " << r->coordonneeY << endl;
}

int main() 
{
	sf::IpAddress server;
	sf::TcpSocket socket;
	std::string msg_recu, msg_envoye;
	const unsigned short port = 55001;
		
	server = "127.0.0.1";

	if (socket.connect(server, port) != sf::Socket::Done){
		return  -1;
	}

	bool rejouer = false;
	char buf[255] ;
	size_t received;

	if (socket.receive(buf, 255, received) != sf::Socket::Done) {
		return -1;
	}

	MessageWelcome* s = (MessageWelcome*)& buf;
	sf::Socket::Status status;
	char* pseudo_client = "";

	switch (s->id)
	{
		case MSG_WELCOME:
			cout << "[" << s->id << "] " << s->msg << endl;
			break;
		/*case MSG_DEMANDE_PSEUDO:
			cout << "[" << s->id << "] " << s->msg << endl;
			cin >> pseudo_client;
			MessageWelcome _message;
			_message.id = MSG_RESPONSE_PSEUDO;
			strcpy(_message.msg, pseudo_client);
			status = socket.send((char*)&_message, sizeof(MessageWelcome));
			if (status != sf::Socket::Done) {
				throw "Erreur envoie pseudo";
			}
			break;*/
	/*	case MSG_DEMANDE_TOURS:
			cout << "[" << s->id << "] " << s->msg << endl;
			break;*/
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

	s = (MessageWelcome*)& buf;
	string messages;
	if (s->id == MSG_DEMANDE_PSEUDO) {
		cout << "Entrez votre pseudo :" << endl;
		cin >> messages;

		MessageWelcome _message;
		_message.id = MSG_RESPONSE_PSEUDO;
		strcpy(_message.msg, messages.c_str());
		status = socket.send((char*)&_message, sizeof(MessageWelcome));
		if (status != sf::Socket::Done) {
			throw "Erreur envoie pseudo";
		}
	}

	memset(buf, 0, 255);
	if (socket.receive(buf, 255, received) != sf::Socket::Done) {
		return -1;
	}

	s = (MessageWelcome*)& buf;
	
	if (s->id == MSG_ENVOI_PSEUDO) {
		cout << "Votre adversaire est " << s->msg << endl;
	}

	bool playing = true;

	while (playing) {
		if (!rejouer) {
			memset(buf, 0, 255);
			if (socket.receive(buf, 255, received) != sf::Socket::Done) {
				return -1;
			}

			s = (MessageWelcome*)& buf;

			if (s->id == MSG_DEMANDE_TOURS) {
				cout << "C'est à votre tour" << endl;
			}
		}

		JeuJoueur(socket);

		memset(buf, 0, 255);
		if (socket.receive(buf, 255, received) != sf::Socket::Done) {
			return -1;
		}
		
		s = (MessageWelcome*)& buf;

		if (s->id == MSG_ACCEPTER_TOUR) {
			//attente du coup de l'adversaire
			rejouer = false;
			AttenteCoupAdversaire(socket);
		}
		else if (s->id == MSG_REFUSER_TOUR) {
			rejouer = true;
		}
	}

	return 0;

}