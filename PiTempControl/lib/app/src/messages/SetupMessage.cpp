#include <lib/app/inc/messages/SetupMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az üzenet típusát jelzõ konstansok kezdõértékeinek beállítása.
 */
const int SetupMessage::CHANGE_SETPOINT = 1;
const int SetupMessage::CHANGE_ERROR_LIMIT = 2;

/*
 * Átadja az ebbõl az osztályból példányosított objektumot az
 * üzenetet fogadó objektumnak feldolgozásra.
 */
void SetupMessage::send(MessageReceiver & receiver) const {
	receiver.receiveMessage(*this);
}

/*
 * Az oszály konstruktora.
 */
SetupMessage::SetupMessage(const int type, const float val) : BaseMessage(), messageType(type), value(val) {}

/*
 * Az osztály virtuális destruktora.
 */
SetupMessage::~SetupMessage() {}

/*
 * Lekéri az üzenet típusát.
 */
int SetupMessage::getMessageType() const {
	return messageType;
}

/*
 * Lekéri az üzenetben tárolt beállítás értékét.
 */
float SetupMessage::getSetupValue() const {
	return value;
}