#pragma once

#include "Define.h"
#include <SFML\Network\Packet.hpp>

class  Message
{
public:
	 Message();
	~ Message();

	//& �vite la recopie
	sf::Packet& getPacket();
	void MakeWelcomeMessage(const std::string str);
	void ResponsePseudo(const std::string str);
	void DemandePseudo();

private:
	sf::Packet _packet;
};

