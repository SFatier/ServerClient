#pragma once

#include "Define.h"
#include <SFML\Network\Packet.hpp>
#include "Logger.h"

class  Message
{
public:
	 Message();
	~ Message();

	//& évite la recopie
	const char* MakeMessage(const std::string &str, int id);
	const char* MakeReceptionCoup(int id, int x, int y);

};

