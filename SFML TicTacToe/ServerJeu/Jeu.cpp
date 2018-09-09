#include "Jeu.h"

using namespace std;
using namespace sf;

//attendrejoueur
void Jeu::AttendreJoueur() {
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

				std::string welcomeMessage = " TicTacToe Server 1.0";

				//c_str = convertie le string en char*
				sf::Socket::Status status = client->send(welcomeMessage.c_str(), welcomeMessage.size());
				if (status != sf::Socket::Done)
					return;

				if (_joueurs.size() == 2) {
					string MessageClient = "La partie est complète. Le jeu peut commencer.";
					client->send(MessageClient.c_str(), MessageClient.size());
					int i = 0;
					while (i < _joueurs.size())
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
	}


	



}

Jeu::Jeu(){

}

Jeu::~Jeu(){}