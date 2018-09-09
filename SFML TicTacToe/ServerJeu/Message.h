#pragma once

#include "Define.h"
#include <SFML\Network\Packet.hpp>

class  Message
{
public:
	 Message();
	~ Message();

	//& évite la recopie
	sf::Packet& getPacket();
	void MakeWelcomeMessage(const std::string str);
	void ResponsePseudo(const std::string str);
	void DemandePseudo();
	void JeuComplet(const std::string str);

private:
	sf::Packet _packet;
};

