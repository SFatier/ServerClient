#pragma once

#include "Define.h"
#include <SFML\Network\Packet.hpp>

class  Message
{
public:
	 Message();
	~ Message();

	//& évite la recopie
	//MessageWelcome getMessagewelcome();
	const char* MakeMessage(const char* str, int id);
	const char* MakeReceptionCoup(int id, int x, int y);
	//void ResponsePseudo(const std::string str);
	//void DemandePseudo();
	//void JeuComplet(const std::string str);
	//void DemandeTour();

};

