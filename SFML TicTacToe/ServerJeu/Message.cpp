#include "Message.h"

Message::Message()
{
}

Message::~Message()
{
}

MessageWelcome Message::getMessagewelcome() {
	return _msg_welcome;
}

const char* Message::MakeMessage(const char* str, int id) {
	_msg_welcome.id = id;
	strcpy(_msg_welcome.msg, str);
	return (char*)&_msg_welcome;
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