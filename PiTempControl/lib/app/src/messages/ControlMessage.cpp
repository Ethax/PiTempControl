#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az üzenet típusát jelzõ konstansok kezdõértékeinek beállítása.
 */
const int ControlMessage::FAN_CONTROL = 1;
const int ControlMessage::HEATER_CONTROL = 2;

/*
 * Átadja az ebbõl az osztályból példányosított objektumot az
 * üzenetet fogadó objektumnak feldolgozásra.
 */
void ControlMessage::send(MessageReceiver& receiver) const {
	receiver.receiveMessage(*this);
}

/*
 * Az oszály konstruktora.
 */
ControlMessage::ControlMessage(const int type, const bool val) : BaseMessage(), messageType(type), value(val) {}

/*
 * Az osztály virtuális destruktora.
 */
ControlMessage::~ControlMessage() {}

/*
 * Lekéri az üzenet típusát.
 */
int ControlMessage::getMessageType() const {
	return messageType;
}

/*
 * Lekéri az üzenetben tárolt beavatkozó jelet.
 */
bool ControlMessage::getControlValue() const {
	return value;
}