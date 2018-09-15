#include "Message.h"

Message::Message()
{
}

Message::~Message()
{
}


const char* Message::MakeMessage(const std::string &str, int id) {
	MessageTexte _msg_welcome;
	char* buffer = new char[sizeof(MessageTexte)];
	if (str.size() >= 128) {
		Logger::getInstance().log("MakeMessage => taille message trop long");
		strncpy(buffer, str.c_str(), 128);
	}
	else {
		strcpy(_msg_welcome.msg, str.c_str());
	}

	_msg_welcome.id = id;

	memcpy(buffer,&_msg_welcome, sizeof(MessageTexte));
	return buffer;
}

const char* Message::MakeReceptionCoup(int id, int x, int y) {
	ReceptionCoup _rcp_coup;
	char* buffer = new char[sizeof(ReceptionCoup)];

	_rcp_coup.id = id;
	_rcp_coup.coordonneeX = x;
	_rcp_coup.coordonneeY = y;
	memcpy(buffer, &_rcp_coup, sizeof(ReceptionCoup));

	return buffer;
}

