#include "Jeu.h"

using namespace std;
using namespace sf;

//attendrejoueur
/*void Jeu::AttendreJoueur() {
	const unsigned short port = 50001;
	sf::TcpListener listener;
	running = true;
	string MessagePseudo;
	sf::SocketSelector selector;

	// Listen to the given port for incoming connections
	if (listener.listen(port) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

	selector.add(listener);

	while (running) {

		selector.wait();
		if (selector.isReady(listener)) {
			sf::TcpSocket *client = new sf::TcpSocket;

			if (listener.accept(*client) == sf::Socket::Done) {
				std::cout << "Client connected: " << client->getRemoteAddress() << std::endl;

				//std::string welcomeMessage = " TicTacToe Server 1.0";
				Message message_welcome;
				message_welcome.MakeWelcomeMessage(" TicTacToe Server 1.0");

				sf::Socket::Status status = client->send(message_welcome.getPacket());
				if (status != sf::Socket::Done)
					return;

				if (_joueurs.size() == 2) {
					string MessageClient = "La partie est complète. Le jeu peut commencer.";
					client->send(MessageClient.c_str(), MessageClient.size());
					int i = 0;
					/*while (i < _joueurs.size())
					{
						std::cout << "Quel est votre pseudo ? ";
						std::cin >> MessagePseudo;
						_joueurs[i]->setPseudo(MessagePseudo);
					
					}

					client->disconnect();
					delete client; 
				}else {
					_joueurs.push_back(new Joueur(client));
					selector.add(*client);
				}
			}
		}
		else {

		}
	}
	*/


void Jeu::SendPseudoJoueur() {
	Message _message;

	if (_joueurs.size() == 2)
	{
				_message.ResponsePseudo(_joueurs[0]->getPseudo());

				sf::Socket::Status status = _joueurs[1]->getSocket().send(_message.getPacket());
				if (status != sf::Socket::Done) {
					 throw "Pseudo non envoyé au joueur" + _joueurs[1]->getPseudo();
				}

				
				_message.ResponsePseudo(_joueurs[1]->getPseudo());

				 status = _joueurs[0]->getSocket().send(_message.getPacket());
				if (status != sf::Socket::Done) {
					 throw "Pseudo non envoyé" + _joueurs[0]->getPseudo();
				}
	}
	else {
		 throw "nombre de joueurs invalide";
	}
}

void Jeu::TourJoueur() {
	
}

void Jeu::DemandeTourJoueur(Joueur* client) {
	Message _messageTour;
	bool hasPseudo = CheckPseudoJoueur();
	
	if (hasPseudo) {
		srand((unsigned int)time(0));

		int nb = rand() % 2;
		_messageTour.DemandeTour();
		if (nb == 1) {
			_joueurs[1]->getSocket().send(_messageTour.getPacket());
		}
		else {
			_joueurs[0]->getSocket().send(_messageTour.getPacket());
		}
	}
}

void Jeu::ReponsePseudoJoueur(sf::Packet packet, Joueur* client) {
	std::string name;
	packet >> name;

	client->setPseudo(name);

	bool hasPseudo = CheckPseudoJoueur();
	if (hasPseudo) {
		SendPseudoJoueur(); //envoye les pseudos a chaque joueur
	}
}

//boucle du serveur
void Jeu::Loop() {
	Message message;

	// Create a socket to listen to new connection
	sf::TcpListener listener; listener.listen(port);

	// Create a selector
	sf::SocketSelector selector;

	// Add the listener to the selector
	selector.add(listener);

	// Endless loop that waits for new connections
	while (running)
	{
		// Make the selector wait for data on any socket
		if (selector.wait())
		{
			// Test the listener
			if (selector.isReady(listener)) //ecoute les connections qui arrivent sur le socket de serveur
			{
				// The listener is ready: there is a pending connection
				sf::TcpSocket* client = new sf::TcpSocket;
				if (listener.accept(*client) == sf::Socket::Done)
				{
					std::cout << "New client" << std::endl;

				
					if (_joueurs.size() == 2) {
						message.JeuComplet("La partie est complète");
						sf::Socket::Status status = client->send(message.getPacket());
						if (status != sf::Socket::Done) {
							return throw "Le client n'a pas reçu le message.";
						}

						client->disconnect();
						delete client;
					}
					else {
						MessageWelcome _msg_welcome;
						_msg_welcome.id = MSG_WELCOME;
						strcpy(_msg_welcome.msg, "Welcome to my server");

						//message.MakeWelcomeMessage("Welcome to my server");
						const char* buf = (char*)&_msg_welcome;
						client->send(buf,sizeof(MessageWelcome)); //taile de la structure

						_joueurs.push_back(new Joueur(client));

						// Add the new client to the selector so that we will
						// be notified when he sends something
						selector.add(*client);
						message.DemandePseudo();
						client->send(message.getPacket());

					}
				}
				else
				{
					// Error, we won't get a new connection, delete the socket
					delete client;
				}
			}
			else //ecoute des clients
			{
				// The listener socket is not ready, test all other sockets (the clients)
				for (std::vector<Joueur*>::iterator it = _joueurs.begin();
					it != _joueurs.end(); ++it)
				{
					Joueur* client = *it;
					if (selector.isReady(client->getSocket()))
					{
						// The client has sent some data, we can receive it
						sf::Packet packet;
						if (client->getSocket().receive(packet) == sf::Socket::Done)
						{
							/*std::cout << "Recu: "
								<< std::string((const char*)packet.getData(), packet.getDataSize())
								<< " from " << client.getRemoteAddress() << std::endl;*/
							int id = -1;
							packet >> id ;

							switch (id)
							{
								case MSG_RESPONSE_TOURS :
									TourJoueur();
									break;

								case MSG_RESPONSE_PSEUDO:
									ReponsePseudoJoueur(packet, client);
									DemandeTourJoueur(client);
									break;
								case -1:
									throw "id invalide";
									break;
							}

						}
					}
				}



			}
		}
	}


}

bool Jeu::CheckPseudoJoueur() {
	if (_joueurs.size() == 2)
	{
		for (std::vector<Joueur*>::const_iterator it = _joueurs.begin();
			it != _joueurs.end(); ++it) {
			Joueur* client = *it;

			if (client->getPseudo().empty()) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
	}

Jeu::Jeu(int _port){
	port = _port;

}

void Jeu::CreationJeu() {
	int i = 0;
	while (i < 9) {
		plateau_jeu.push_back(non_utilise);
		i++;
	}
}

Jeu::~Jeu(){}