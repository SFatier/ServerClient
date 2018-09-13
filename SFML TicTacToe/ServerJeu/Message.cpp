#include "Message.h"

Message::Message()
{
}

Message::~Message()
{
}

//MessageWelcome Message::getMessagewelcome() {
//	return _msg_welcome;
//}

const char* Message::MakeMessage(const char* str, int id) {
	MessageWelcome _msg_welcome;
	char* buffer = new char[255];

	_msg_welcome.id = id;
	strcpy(_msg_welcome.msg, str);

	memcpy(buffer,&_msg_welcome, sizeof(MessageWelcome));
	return buffer;
}

const char* Message::MakeReceptionCoup(int id, int x, int y) {
	ReceptionCoup _rcp_coup;
	char* buffer = new char[255];

	_rcp_coup.id = id;
	_rcp_coup.coordonneeX = x;
	_rcp_coup.coordonneeY = y;
	memcpy(buffer, &_rcp_coup, sizeof(ReceptionCoup));

	return buffer;
}

//void Message::ResponsePseudo(const std::string str) {
//	//_packet.clear();
//	//_packet << (int)MSG_RESPONSE_PSEUDO << str;
//
//}
//
//void Message::JeuComplet(const std::string str) {
//	_packet.clear();
//	_packet << (int)MSG_COMPLET;
//}
//
//void Message::DemandeTour() {
//	_packet.clear();
//	_packet << (int)MSG_DEMANDE_TOURS;
//}
//
//void Message::DemandePseudo() {
//	_packet.clear();
//	_packet << (int)MSG_DEMANDE_PSEUDO;
//}