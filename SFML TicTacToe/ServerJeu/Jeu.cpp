#include "Jeu.h"
#include "trayGame.h"

using namespace std;
using namespace sf;


void Jeu::SendPseudoJoueur() {
	Message _message;

	if (_joueurs.size() == 2)
	{
				const char* buf = _message.MakeMessage(_joueurs[0]->getPseudo().c_str(), MSG_ENVOI_PSEUDO);

				sf::Socket::Status status = _joueurs[1]->getSocket().send(buf, sizeof(MessageWelcome));
				if (status != sf::Socket::Done) {
					std::string pseudo_joueur = _joueurs[1]->getPseudo();
					Logger::getInstance().log("Pseudo non envoyé au joueur" + pseudo_joueur);
				}

				delete[] buf;

				buf =_message.MakeMessage(_joueurs[1]->getPseudo().c_str(), MSG_ENVOI_PSEUDO);

				 status = _joueurs[0]->getSocket().send(buf, sizeof(MessageWelcome));
				if (status != sf::Socket::Done) {
					string pseudo_joueur = _joueurs[0]->getPseudo();
					Logger::getInstance().log("Pseudo non envoyé" + pseudo_joueur);
				}

				delete[] buf;
	}
	else {
		Logger::getInstance().log("nombre de joueurs invalide");
	}
}

void Jeu::TourJoueur(Joueur* client, ReceptionCoup* r) {
	Message message;
	const char* buf;

	if (plateau_jeu[r->coordonneeX][r->coordonneeY] == etat_non_utilise && r->coordonneeX < 3
			&& r->coordonneeX >= 0 && r->coordonneeY < 3 && r->coordonneeY >= 0) {
		plateau_jeu[r->coordonneeX][r->coordonneeY] = client->getPion();

		buf =message.MakeMessage("le coup a ete accepte", MSG_ACCEPTER_TOUR);

		if (client->getSocket().send(buf, sizeof(MessageWelcome)) != sf::Socket::Done){
			Logger::getInstance().log("Erreur reception joueur");
		}

		delete[] buf;

		Joueur* adversaire;

		if (client == _joueurs[0])
		{
			adversaire = _joueurs[1];
		}
		else {
			adversaire = _joueurs[0];
		}

		buf = message.MakeReceptionCoup(MSG_ADVERSAIRE_TOUR, r->coordonneeX, r->coordonneeY);

		if (adversaire->getSocket().send(buf, sizeof(MessageWelcome)) != sf::Socket::Done) {
			Logger::getInstance().log("Erreur reception adversaire");
		}
		delete[] buf;

		buf = message.MakeMessage("C'est a votre tour", MSG_DEMANDE_TOURS);
		if (adversaire->getSocket().send(buf, sizeof(MessageWelcome))) {
			Logger::getInstance().log("Erreur reception tour adversaire");
		}
		delete[] buf;
		
		
	}
	else {
		buf = message.MakeMessage("Votre coup est refuse.", MSG_REFUSER_TOUR);
		if (client->getSocket().send(buf, sizeof(MessageWelcome))) {
			Logger::getInstance().log("Erreur tour refuse");
		}
		delete[] buf;
	}
}

void Jeu::Init() {
	Logger::getInstance().log("Connection Serveur");
}

void Jeu::DemandePremierTour(Joueur* client) {
	Message _messageTour;
	bool hasPseudo = CheckPseudoJoueur();
	
	if (hasPseudo) {
		srand((unsigned int)time(0));

		int nb = rand() % 2;
		const char* buff = _messageTour.MakeMessage("A vous de jouer", MSG_DEMANDE_TOURS);
		if (nb == 1) {
			_joueurs[1]->getSocket().send(buff, sizeof(MessageWelcome));
			_joueurs[1]->setPion(etat_x);
			_joueurs[0]->setPion(etat_o);
		}
		else {
			_joueurs[0]->getSocket().send(buff, sizeof(MessageWelcome));
			_joueurs[0]->setPion(etat_x);
			_joueurs[1]->setPion(etat_o);
		}
	}
}

void Jeu::ReponsePseudoJoueur(MessageWelcome* s, Joueur* client) {
	std::string name = s->msg;
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
	sf::Socket::Status status;
	//Logger::getInstance().log();

	// Create a socket to listen to new connection
	sf::TcpListener listener; 
	listener.listen(port);

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
					Logger::getInstance().log("Nouveau client connecte");
									
					if (_joueurs.size() == 2) {
						buf = message.MakeMessage("La partie est complète", MSG_COMPLET);
						status = client->send(buf, sizeof(MessageWelcome));
						if (status != sf::Socket::Done) {
							Logger::getInstance().log("ERROR => Message jeu complet");
						}

						client->disconnect();
						delete client;
					}
					else {
						
						buf = message.MakeMessage("Bienvenu, tu es connecte sur le serveur...", MSG_WELCOME);
						status = client->send(buf,sizeof(MessageWelcome)); //taile de la structure
						if (status != sf::Socket::Done) {
							Logger::getInstance().log("ERROR => Message welcome jeu");
						}
						
						delete[] buf;

						buf = message.MakeMessage("Puis-je avoir votre pseudo ?", MSG_DEMANDE_PSEUDO);
						status = client->send(buf, sizeof(MessageWelcome));
						if (status != sf::Socket::Done) {
							Logger::getInstance().log("ERROR => Message demande pseudo");
						}

						delete[] buf;

						_joueurs.push_back(new Joueur(client));
						selector.add(*client);
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
							int id = buf[0];

							switch (id)
							{
								case MSG_ENVOI_COUP :
								{
									ReceptionCoup* s = (ReceptionCoup*)& buf;
									TourJoueur(client, s);
									break;
								}

								case MSG_RESPONSE_PSEUDO:
								{
									MessageWelcome* s = (MessageWelcome*)& buf;

									ReponsePseudoJoueur(s, client);
									DemandePremierTour(client);
									break;
								}
								case -1:
								default:
									Logger::getInstance().log("id invalide");
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
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			plateau_jeu[i][j] = etat_non_utilise;
		}
	}
}

Jeu::~Jeu(){}