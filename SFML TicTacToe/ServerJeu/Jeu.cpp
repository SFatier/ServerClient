#include "Jeu.h"

using namespace std;
using namespace sf;


void Jeu::SendPseudoJoueur() {
	Message _message;

	if (_joueurs.size() == 2)
	{
				const char* buf = _message.MakeMessage(_joueurs[0]->getPseudo(), MSG_ENVOI_PSEUDO);

				sf::Socket::Status status = _joueurs[1]->getSocket().send(buf, sizeof(MessageWelcome));
				if (status != sf::Socket::Done) {
					std::string pseudo_joueur = _joueurs[1]->getPseudo();
					Logger::Logger::log("Pseudo non envoyé au joueur" + pseudo_joueur);
				}

				
				buf =_message.MakeMessage(_joueurs[1]->getPseudo(), MSG_ENVOI_PSEUDO);

				 status = _joueurs[0]->getSocket().send(buf, sizeof(MessageWelcome));
				if (status != sf::Socket::Done) {
					string pseudo_joueur = _joueurs[0]->getPseudo();
					Logger::Logger::log("Pseudo non envoyé" + pseudo_joueur);
				}
	}
	else {
		Logger::Logger::log("nombre de joueurs invalide");
	}
}

void Jeu::TourJoueur() {
	
}

void Jeu::Init() {
	Logger::Logger::log("Connection Serveur");
}

void Jeu::DemandeTourJoueur(Joueur* client) {
	Message _messageTour;
	bool hasPseudo = CheckPseudoJoueur();
	
	if (hasPseudo) {
		srand((unsigned int)time(0));

		int nb = rand() % 2;
		const char* buff = _messageTour.MakeMessage("A vous de jouer", MSG_DEMANDE_TOURS);
		if (nb == 1) {
			_joueurs[1]->getSocket().send(buff, sizeof(MessageWelcome));
		}
		else {
			_joueurs[0]->getSocket().send(buff, sizeof(MessageWelcome));
		}
	}
}

void Jeu::ReponsePseudoJoueur(MessageWelcome* s, Joueur* client) {
	const char* name = s->msg;
	client->setPseudo(name);

	bool hasPseudo = CheckPseudoJoueur();
	if (hasPseudo) {
		SendPseudoJoueur(); //envoye les pseudos a chaque joueur
	}
}

//boucle du serveur
void Jeu::Loop() {
	Message message;
	const char* buf = "";

	// Create a socket to listen to new connection
	sf::TcpListener listener; listener.listen(port);

	sf::SocketSelector selector;

	selector.add(listener);

	while (running)
	{
		if (selector.wait())
		{
			if (selector.isReady(listener)) //ecoute les connections qui arrivent sur le socket de serveur
			{
				sf::TcpSocket* client = new sf::TcpSocket;
				if (listener.accept(*client) == sf::Socket::Done)
				{
					Logger::Logger::log("Nouveau client connecté");
									
					if (_joueurs.size() == 2) {
						buf = message.MakeMessage("La partie est complète", MSG_COMPLET);
						sf::Socket::Status status = client->send(buf, sizeof(MessageWelcome));
						if (status != sf::Socket::Done) {
							Logger::Logger::log("Le client n'a pas reçu le message.");
						}

						client->disconnect();
						delete client;
					}
					else {
						
						buf = message.MakeMessage("Welcome to my server", MSG_WELCOME);
						client->send(buf,sizeof(MessageWelcome)); //taile de la structure

						_joueurs.push_back(new Joueur(client));

						selector.add(*client);
						buf = message.MakeMessage("Puis-je avoir votre pseudo ?", MSG_DEMANDE_PSEUDO);
						client->send(buf, sizeof(MessageWelcome));

					}
				}
				else
				{
					delete client;
				}
			}
			else //ecoute des clients
			{
				for (std::vector<Joueur*>::iterator it = _joueurs.begin();
					it != _joueurs.end(); ++it)
				{
					Joueur* client = *it;
					if (selector.isReady(client->getSocket()))
					{
						//sf::Packet packet;
						char buf[255];
						size_t received;
						if (client->getSocket().receive(buf, 255, received) == sf::Socket::Done)
						{
							int id = -1;
							//packet >> id ;
							MessageWelcome* s = (MessageWelcome*)& buf;

							switch (s->id)
							{
								case MSG_RESPONSE_TOURS :
									TourJoueur();
									break;

								case MSG_RESPONSE_PSEUDO:
									ReponsePseudoJoueur(s, client);
									DemandeTourJoueur(client);
									break;
								case -1:
									Logger::Logger::log("id invalide");
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

			if (client->getPseudo() == "") {
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