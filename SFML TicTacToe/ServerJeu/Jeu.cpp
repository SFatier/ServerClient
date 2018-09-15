#include "Jeu.h"
#include "trayGame.h"

using namespace std;
using namespace sf;


void Jeu::SendPseudoJoueur() {
	Message _message;

	if (_joueurs.size() == 2)
	{
				const char* buf = _message.MakeMessage(_joueurs[0]->getPseudo().c_str(), MSG_ENVOI_PSEUDO);

				sf::Socket::Status status = _joueurs[1]->getSocket().send(buf, sizeof(MessageTexte));
				if (status != sf::Socket::Done) {
					std::string pseudo_joueur = _joueurs[1]->getPseudo();
					Logger::getInstance().log("Pseudo non envoyé au joueur" + pseudo_joueur);
				}

				delete[] buf;

				buf =_message.MakeMessage(_joueurs[1]->getPseudo().c_str(), MSG_ENVOI_PSEUDO);

				 status = _joueurs[0]->getSocket().send(buf, sizeof(MessageTexte));
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

		buf =message.MakeMessage("Le coup a ete accepte", MSG_ACCEPTER_TOUR);

		if (client->getSocket().send(buf, sizeof(MessageTexte)) != sf::Socket::Done){
			Logger::getInstance().log("Erreur reception joueur");
		}

		delete[] buf;

		AffichePlateau();

		Etat_case etat =  JeuGagnant();
		
		if (etat == etat_non_utilise)
		{
			Joueur* adversaire;

			if (client == _joueurs[0])
			{
				adversaire = _joueurs[1];
			}
			else {
				adversaire = _joueurs[0];
			}

			
			buf = message.MakeReceptionCoup(MSG_ADVERSAIRE_TOUR, r->coordonneeX, r->coordonneeY);

			if (adversaire->getSocket().send(buf, sizeof(MessageTexte)) != sf::Socket::Done) {
				Logger::getInstance().log("Erreur reception adversaire");
			}
			delete[] buf;

			buf = message.MakeMessage("C'est a votre tour", MSG_DEMANDE_TOURS);
			if (adversaire->getSocket().send(buf, sizeof(MessageTexte))) {
				Logger::getInstance().log("Erreur reception tour adversaire");
			}
			delete[] buf;
		}
		else {
			MakeMessageGagant(etat);
		}
	}
	else {
		buf = message.MakeMessage("Votre coup est refuse.", MSG_REFUSER_TOUR);
		if (client->getSocket().send(buf, sizeof(MessageTexte))) {
			Logger::getInstance().log("Erreur tour refuse");
		}
		delete[] buf;
	}
}

Etat_case Jeu::JeuGagnant() {

	Etat_case pion_gagnant = etat_non_utilise;

	if (plateau_jeu[0][0] == etat_x && plateau_jeu[0][1] == etat_x && plateau_jeu[0][2] == etat_x)
		pion_gagnant = etat_x;
	if (plateau_jeu[1][0] == etat_x && plateau_jeu[1][1] == etat_x && plateau_jeu[1][2] == etat_x)
		pion_gagnant = etat_x;
	if (plateau_jeu[2][0] == etat_x && plateau_jeu[2][1] == etat_x && plateau_jeu[2][2] == etat_x)
		pion_gagnant = etat_x;

	if (plateau_jeu[0][0] == etat_x && plateau_jeu[1][0] == etat_x && plateau_jeu[2][0] == etat_x)
		pion_gagnant = etat_x;
	if (plateau_jeu[0][1] == etat_x && plateau_jeu[1][1] == etat_x && plateau_jeu[2][1] == etat_x)
		pion_gagnant = etat_x;
	if (plateau_jeu[0][2] == etat_x && plateau_jeu[1][2] == etat_x && plateau_jeu[2][2] == etat_x)
		pion_gagnant = etat_x;

	if (plateau_jeu[0][0] == etat_x && plateau_jeu[1][1] == etat_x && plateau_jeu[2][2] == etat_x)
		pion_gagnant = etat_x;
	if (plateau_jeu[2][0] == etat_x && plateau_jeu[1][1] == etat_x && plateau_jeu[0][2] == etat_x)
		pion_gagnant = etat_x;

	if (plateau_jeu[0][0] == etat_o && plateau_jeu[0][1] == etat_o && plateau_jeu[0][2] == etat_o)
		pion_gagnant = etat_o;
	if (plateau_jeu[1][0] == etat_o && plateau_jeu[1][1] == etat_o && plateau_jeu[1][2] == etat_o)
		pion_gagnant = etat_o;
	if (plateau_jeu[2][0] == etat_o && plateau_jeu[2][1] == etat_o && plateau_jeu[2][2] == etat_o)
		pion_gagnant = etat_o;

	if (plateau_jeu[0][0] == etat_o && plateau_jeu[1][0] == etat_o && plateau_jeu[2][0] == etat_o)
		pion_gagnant = etat_o;
	if (plateau_jeu[0][1] == etat_o && plateau_jeu[1][1] == etat_o && plateau_jeu[2][1] == etat_o)
		pion_gagnant = etat_o;
	if (plateau_jeu[0][2] == etat_o && plateau_jeu[1][2] == etat_o && plateau_jeu[2][2] == etat_o)
		pion_gagnant = etat_o;

	if (plateau_jeu[0][0] == etat_o && plateau_jeu[1][1] == etat_o && plateau_jeu[2][2] == etat_o)
		pion_gagnant = etat_o;
	if (plateau_jeu[2][0] == etat_o && plateau_jeu[1][1] == etat_o && plateau_jeu[0][2] == etat_o)
		pion_gagnant = etat_o;

	bool case_non_utilise = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (plateau_jeu[i][j] == etat_non_utilise) {
				case_non_utilise = true;

				break;
			}
		}
	}

	if (case_non_utilise == false) {
		pion_gagnant = etat_egalite;
	}

	return pion_gagnant;
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
			_joueurs[1]->getSocket().send(buff, sizeof(MessageTexte));
			_joueurs[1]->setPion(etat_x);
			_joueurs[0]->setPion(etat_o);
		}
		else {
			_joueurs[0]->getSocket().send(buff, sizeof(MessageTexte));
			_joueurs[0]->setPion(etat_x);
			_joueurs[1]->setPion(etat_o);
		}
	}
}

void Jeu::ReponsePseudoJoueur(MessageTexte* s, Joueur* client) {
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
						status = client->send(buf, sizeof(MessageTexte));
						if (status != sf::Socket::Done) {
							Logger::getInstance().log("ERROR => Message jeu complet");
						}

						client->disconnect();
						delete client;
					}
					else {
						
						buf = message.MakeMessage("Bienvenu, tu es connecte sur le serveur...", MSG_WELCOME);
						status = client->send(buf,sizeof(MessageTexte)); //taile de la structure
						if (status != sf::Socket::Done) {
							Logger::getInstance().log("ERROR => Message welcome jeu");
						}
						
						delete[] buf;

						buf = message.MakeMessage("Puis-je avoir votre pseudo ?", MSG_DEMANDE_PSEUDO);
						status = client->send(buf, sizeof(MessageTexte));
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

				Etat_case pion_gagnant;

				for (std::vector<Joueur*>::iterator it = _joueurs.begin();
					it != _joueurs.end(); ++it)
				{
					Joueur* client = *it;
					if (selector.isReady(client->getSocket()))
					{
					
							char buf[255];
							size_t received;
							if (client->getSocket().receive(buf, 255, received) == sf::Socket::Done)
							{
								int id = buf[0];

								switch (id)
								{
								case MSG_ENVOI_COUP:
								{
									ReceptionCoup* s = (ReceptionCoup*)& buf;
									TourJoueur(client, s);
									
									/*pion_gagnant = JeuGagnant();
									if (pion_gagnant != etat_non_utilise)
									{
										MakeMessageGagant(pion_gagnant);
										//running = true;
									}*/

									break;
								}

								case MSG_RESPONSE_PSEUDO:
								{
									MessageTexte* s = (MessageTexte*)& buf;

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


void Jeu::MakeMessageGagant(Etat_case pion_gagnant) {
	const char* buf;
	Message message;

	if (pion_gagnant != etat_egalite) {
		SendMessageVictoire(pion_gagnant);
	}
	else { 
		SendMessageEgalite();
	}
}

void Jeu::SendMessageEgalite(){
	string buf;
	Message message;

	for (std::vector<Joueur*>::const_iterator it = _joueurs.begin(); it != _joueurs.end(); ++it) {
		Joueur* joueur = *it;
		buf = message.MakeMessage("Egalite !", MSG_SCORE);
		if (joueur->getSocket().send(buf.c_str(), sizeof(MessageTexte)) != sf::Socket::Done) {
			Logger::getInstance().log("Erreur reception score");
		}
	}
}


void Jeu::SendMessageVictoire(Etat_case pion) {
	std::string buf;
	Message message;

	for (std::vector<Joueur*>::const_iterator it = _joueurs.begin(); it != _joueurs.end(); ++it) {
		Joueur* joueur = *it;

		if (joueur->getPion() == pion) {
			buf = message.MakeMessage("Vous avez gagne la partie", MSG_SCORE);
			if (joueur->getSocket().send(buf.c_str(), sizeof(MessageTexte)) != sf::Socket::Done) {
				Logger::getInstance().log("Erreur reception score");
			}
		}
		else {

			buf = message.MakeMessage("vous avez perdu la partie", MSG_SCORE);
			if (joueur->getSocket().send(buf.c_str(), sizeof(MessageTexte)) != sf::Socket::Done) {
				Logger::getInstance().log("Erreur reception score");
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

void Jeu::AffichePlateau() {
	Logger::getInstance().log("\n");

	std::stringstream buf;
	for (int y = 0; y < 3; y++) {
		buf.str("");
		buf << "+ " << drawPos(0, y) << " + " << drawPos(1, y) << "+ " << drawPos(2, y) << "+";
		Logger::getInstance().log(buf.str());
	}
}

char Jeu::drawPos(int x, int y) {
	char rst = ' ';
	if (plateau_jeu[x][y] == etat_o) {
		rst = 'O';
	}
	else if (plateau_jeu[x][y] == etat_x) {
		rst = 'X';
	}

	return rst;
}