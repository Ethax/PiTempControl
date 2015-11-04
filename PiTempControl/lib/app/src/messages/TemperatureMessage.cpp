#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az üzenet típusát jelzõ konstans kezdõértékének beállítása.
 */
const int TemperatureMessage::ACTUAL_TEMPERATURE = 1;

/*
 * Átadja az ebbõl az osztályból példányosított objektumot az
 * üzenetet fogadó objektumnak feldolgozásra.
 */
void TemperatureMessage::send(MessageReceiver & receiver) const {
	receiver.receiveMessage(*this);
}

/*
 * Az oszály konstruktora.
 */
TemperatureMessage::TemperatureMessage(const int type, const float temp) : BaseMessage(), messageType(type), temperature(temp) {}

/*
 * Az osztály virtuális destruktora.
 */
TemperatureMessage::~TemperatureMessage() {}

/*
 * Lekéri az üzenet típusát.
 */
int TemperatureMessage::getMessageType() const {
	return messageType;
}

/*
 * Lekéri az üzenetben tárolt hõmérsékletet.
 */
float TemperatureMessage::getTemperature() const {
	return temperature;
}
