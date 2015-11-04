#include <lib/app/inc/core/MessageReceiver.h>
#include <lib/app/inc/core/BaseMessage.h>
#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/messages/SetupMessage.h>

/*
 * @brief Az osz�ly alap�rtelmezett konstruktora.
 */
MessageReceiver::MessageReceiver() {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
MessageReceiver::~MessageReceiver() {}

/*
 * Fogadja �s feldolgozza az �tadott BaseMessage t�pus� �zenetet.
 */
void MessageReceiver::receiveMessage(const BaseMessage& msg) {}

/*
 * Fogadja �s feldolgozza az �tadott TemperatureMessage t�pus� �zenetet.
 */
void MessageReceiver::receiveMessage(const TemperatureMessage& msg) {
	receiveMessage(static_cast<const BaseMessage&>(msg));
}

/*
 * Fogadja �s feldolgozza az �tadott ControlMessage t�pus� �zenetet.
 */
void MessageReceiver::receiveMessage(const ControlMessage& msg) {
	receiveMessage(static_cast<const BaseMessage&>(msg));
}

/*
 * Fogadja �s feldolgozza az �tadott SetupMessage t�pus� �zenetet.
 */
void MessageReceiver::receiveMessage(const SetupMessage& msg) {
	receiveMessage(static_cast<const BaseMessage&>(msg));
}
