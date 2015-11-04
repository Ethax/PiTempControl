#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az �zenet t�pus�t jelz� konstans kezd��rt�k�nek be�ll�t�sa.
 */
const int TemperatureMessage::ACTUAL_TEMPERATURE = 1;

/*
 * �tadja az ebb�l az oszt�lyb�l p�ld�nyos�tott objektumot az
 * �zenetet fogad� objektumnak feldolgoz�sra.
 */
void TemperatureMessage::send(MessageReceiver & receiver) const {
	receiver.receiveMessage(*this);
}

/*
 * Az osz�ly konstruktora.
 */
TemperatureMessage::TemperatureMessage(const int type, const float temp) : BaseMessage(), messageType(type), temperature(temp) {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
TemperatureMessage::~TemperatureMessage() {}

/*
 * Lek�ri az �zenet t�pus�t.
 */
int TemperatureMessage::getMessageType() const {
	return messageType;
}

/*
 * Lek�ri az �zenetben t�rolt h�m�rs�kletet.
 */
float TemperatureMessage::getTemperature() const {
	return temperature;
}
