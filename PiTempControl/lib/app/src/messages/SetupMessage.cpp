#include <lib/app/inc/messages/SetupMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az �zenet t�pus�t jelz� konstansok kezd��rt�keinek be�ll�t�sa.
 */
const int SetupMessage::CHANGE_SETPOINT = 1;
const int SetupMessage::CHANGE_ERROR_LIMIT = 2;

/*
 * �tadja az ebb�l az oszt�lyb�l p�ld�nyos�tott objektumot az
 * �zenetet fogad� objektumnak feldolgoz�sra.
 */
void SetupMessage::send(MessageReceiver & receiver) const {
	receiver.receiveMessage(*this);
}

/*
 * Az osz�ly konstruktora.
 */
SetupMessage::SetupMessage(const int type, const float val) : BaseMessage(), messageType(type), value(val) {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
SetupMessage::~SetupMessage() {}

/*
 * Lek�ri az �zenet t�pus�t.
 */
int SetupMessage::getMessageType() const {
	return messageType;
}

/*
 * Lek�ri az �zenetben t�rolt be�ll�t�s �rt�k�t.
 */
float SetupMessage::getSetupValue() const {
	return value;
}