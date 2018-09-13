#pragma once

#include "Define.h"
#include <SFML\Network\Packet.hpp>

class  Message
{
public:
	 Message();
	~ Message();

	//& évite la recopie
	MessageWelcome getMessagewelcome();
	const char* MakeMessage(const char* str, int id);
	//void ResponsePseudo(const std::string str);
	//void DemandePseudo();
	//void JeuComplet(const std::string str);
	//void DemandeTour();

private:
	//sf::Packet _packet;

	MessageWelcome _msg_welcome;
};

