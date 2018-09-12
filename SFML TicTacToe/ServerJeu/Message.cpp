#include "Message.h"

Message::Message()
{
}

Message::~Message()
{
}

sf::Packet& Message::getPacket() {
	return _packet;
}

void Message::MakeWelcomeMessage(const std::string& str) {
	//sf::Packet packet;
	////_packet.clear();
	//sf::Uint32 id = MSG_WELCOME;
	//packet << id ;
	//std::string s = "test";
	//packet << s;



}

void Message::ResponsePseudo(const std::string str) {
	_packet.clear();
	_packet << (int)MSG_RESPONSE_PSEUDO << str;
}

void Message::JeuComplet(const std::string str) {
	_packet.clear();
	_packet << (int)MSG_COMPLET;
}

void Message::DemandeTour() {
	_packet.clear();
	_packet << (int)MSG_DEMANDE_TOURS;
}

void Message::DemandePseudo() {
	_packet.clear();
	_packet << (int)MSG_DEMANDE_PSEUDO;
}