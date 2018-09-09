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
			if (selector.isReady(listener))
			{
				// The listener is ready: there is a pending connection
				sf::TcpSocket* client = new sf::TcpSocket;
				if (listener.accept(*client) == sf::Socket::Done)
				{
					std::cout << "New client" << std::endl;

					//std::string s = "Welcome to my server";
					message.MakeWelcomeMessage("Welcome to my server");
					client->send(message.getPacket());
				
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
			else
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
							std::string name;

							packet >> id >> name;
							
							client->setPseudo(name);

							bool hasPseudo = CheckPseudoJoueur();
							if (hasPseudo) {
								//envoie les id aux 2 joueurs.
								//tour
							}

						}
					}
				}



			}
		}
	}


}

bool Jeu::CheckPseudoJoueur() {
	for (std::vector<Joueur*>::const_iterator it = _joueurs.begin();
		it != _joueurs.end(); ++it) {
		Joueur* client = *it;

		if (client->getPseudo().empty()) {
			return false;
		}
	}
	return true;
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