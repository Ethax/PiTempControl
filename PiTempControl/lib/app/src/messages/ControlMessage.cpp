#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az �zenet t�pus�t jelz� konstansok kezd��rt�keinek be�ll�t�sa.
 */
const int ControlMessage::FAN_CONTROL = 1;
const int ControlMessage::HEATER_CONTROL = 2;

/*
 * �tadja az ebb�l az oszt�lyb�l p�ld�nyos�tott objektumot az
 * �zenetet fogad� objektumnak feldolgoz�sra.
 */
void ControlMessage::send(MessageReceiver& receiver) const {
	receiver.receiveMessage(*this);
}

/*
 * Az osz�ly konstruktora.
 */
ControlMessage::ControlMessage(const int type, const bool val) : BaseMessage(), messageType(type), value(val) {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
ControlMessage::~ControlMessage() {}

/*
 * Lek�ri az �zenet t�pus�t.
 */
int ControlMessage::getMessageType() const {
	return messageType;
}

/*
 * Lek�ri az �zenetben t�rolt beavatkoz� jelet.
 */
bool ControlMessage::getControlValue() const {
	return value;
}