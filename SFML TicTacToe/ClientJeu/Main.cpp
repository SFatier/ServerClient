#include "SFML\Network.hpp"
#include <iostream>
#include <cstdlib>
#include <Define.h>

using namespace std;
using namespace sf;

int main() 
{
	sf::IpAddress server;
	sf::TcpSocket socket;
	sf::Packet packet;
	std::string msg_recu, msg_envoye;
	const unsigned short port = 55001;
	
	server = "127.0.0.1";

	if (socket.connect(server, port) != sf::Socket::Done){
		return  -1;
	}
	char buf[255] ;
	size_t received;

	if (socket.receive(buf, 255,received ) != sf::Socket::Done) {
		return -1;
	}

	MessageWelcome* s = (MessageWelcome*)& buf;

	switch (s->id)
	{
		case MSG_WELCOME:
			cout << "[" << s->id << "] " << s->msg<< endl;
			break;
		case MSG_COMPLET:
			cout << "La partie est complete appuyez sur une touche pour terminer…" << endl;
			std::cin.ignore();
			return 0;

	}

		

		/*const char out[] = "Salut je suis un nouveau joueur ";
		if (socket.send(out, sizeof(out)) != sf::Socket::Done)
		{
			return -1;
		}
		std::cout << "Réponse: \"" << out << "\"" << std::endl;*/

	return 0;

}