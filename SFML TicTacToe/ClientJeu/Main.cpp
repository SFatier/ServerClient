#include "SFML\Network.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace sf;

int main() 
{
	sf::IpAddress server;
	sf::TcpSocket socket;
	char in[128];
	std::size_t received;
	const unsigned short port = 50001;
	const char out[] = "Erreur connection! ";


	server = "127.0.0.1";

	if (socket.connect(server, port) != sf::Socket::Done){
		return  -1;
	}

	while (true) {
		
		if (socket.receive(in, sizeof(in), received) != sf::Socket::Done) {
			return -1;
		}

		std::cout << "Serveur : \"" << in << "\"" << std::endl;

		const char out[] = "Salut je suis un nouveau joueur ";
		if (socket.send(out, sizeof(out)) != sf::Socket::Done)
		{
			return -1;
		}
		std::cout << "Réponse: \"" << out << "\"" << std::endl;
	}

	return 0;

}