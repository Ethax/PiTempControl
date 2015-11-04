#include <lib/app/inc/core/MessageReceiver.h>
#include <lib/app/inc/core/BaseMessage.h>
#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/messages/SetupMessage.h>

/*
 * @brief Az oszály alapértelmezett konstruktora.
 */
MessageReceiver::MessageReceiver() {}

/*
 * Az osztály virtuális destruktora.
 */
MessageReceiver::~MessageReceiver() {}

/*
 * Fogadja és feldolgozza az átadott BaseMessage típusú üzenetet.
 */
void MessageReceiver::receiveMessage(const BaseMessage& msg) {}

/*
 * Fogadja és feldolgozza az átadott TemperatureMessage típusú üzenetet.
 */
void MessageReceiver::receiveMessage(const TemperatureMessage& msg) {
	receiveMessage(static_cast<const BaseMessage&>(msg));
}

/*
 * Fogadja és feldolgozza az átadott ControlMessage típusú üzenetet.
 */
void MessageReceiver::receiveMessage(const ControlMessage& msg) {
	receiveMessage(static_cast<const BaseMessage&>(msg));
}

/*
 * Fogadja és feldolgozza az átadott SetupMessage típusú üzenetet.
 */
void MessageReceiver::receiveMessage(const SetupMessage& msg) {
	receiveMessage(static_cast<const BaseMessage&>(msg));
}
