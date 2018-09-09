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

void Message::MakeWelcomeMessage(const std::string str) {
	_packet.clear();
	_packet << (int)MSG_WELCOME << str;
}

void Message::ResponsePseudo(const std::string str) {
	_packet.clear();
	_packet << (int)MSG_RESPONSE_PSEUDO << str;
}

void Message::JeuComplet(const std::string str) {
	_packet.clear();
	_packet << (int)MSG_START;
}

void Message::DemandePseudo() {
	_packet.clear();
	_packet << (int)MSG_DEMANDE_PSEUDO;
}