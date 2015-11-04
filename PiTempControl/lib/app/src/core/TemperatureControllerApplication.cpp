#include <lib/app/inc/core/TemperatureControllerApplication.h>

#include <lib/app/inc/regulator/RegulatorModule.h>
#include <lib/app/inc/sensor/SensorModule.h>
#include <lib/app/inc/actuator/ActuatorModule.h>
#include <lib/app/inc/display/DisplayModule.h>

#include <lib/app/inc/regulator/RegulatorInterface.h>
#include <lib/app/inc/sensor/SensorInterface.h>
#include <lib/app/inc/actuator/ActuatorInterface.h>
#include <lib/app/inc/display/DisplayInterface.h>

#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/messages/SetupMessage.h>
#include <lib/app/inc/messages/TemperatureMessage.h>

/*
 * Az osztály konstruktora.
 */
TemperatureControllerApplication::TemperatureControllerApplication(RegulatorInterface& regulator, SensorInterface& sensor,
	ActuatorInterface& actuator, DisplayInterface& display, const float _setpoint, const float _errorLimit) :
	appState(State::getInstance()),
	stopped(true), setpoint(_setpoint), errorLimit(_errorLimit),
	regulatorModule(std::make_shared<RegulatorModule>(*this, regulator)),
	sensorModule(std::make_shared<SensorModule>(*this, sensor)),
	actuatorModule(std::make_shared<ActuatorModule>(*this, actuator)),
	displayModule(std::make_shared<DisplayModule>(*this, display)) {}

/*
 * Az osztály virtuális destruktora.
 */
TemperatureControllerApplication::~TemperatureControllerApplication() {
	stop();
}

/*
 * Felveszi az átadott fogadót a feliratkozott fogadók közé.
 */
void TemperatureControllerApplication::registerMessageReceiver(MessageReceiver& receiver) {
	sender.registerMessageReceiver(receiver);
}

/*
 * Elhelyezi az elküldeni kívánt üzenetet a várakozási sorba és jelez
 * az üzeneteket kézbesítõ szálnak, hogy folytathatja a várakozási
 * sorban levõ üzenetek kézbesítését.
 */
void TemperatureControllerApplication::sendMessage(std::shared_ptr<BaseMessage> message) {
	sender.sendMessage(message);
}

/*
 * Hozzáférhetõvé teszi az alkalmazás állapotait tároló objektumot.
 */
State& TemperatureControllerApplication::getState() {
	return appState;
}

/*
 * Elindítja az alkalmazás ütemezett mûködését.
 */
void TemperatureControllerApplication::start() {
	if(!stopped) return;
	stopped = false;
	
	/* Az alkalmazás moduljainak elindítása. */
	regulatorModule->start();
	sensorModule->start();
	actuatorModule->start();
	displayModule->start();
	sender.start();

	/* A fixált alapjel beállítása az alkalmazás állapotait
	tároló objektumban és új beállító üzenetek küldése a módosítások
	érvénybeléptetéséhez. */
	appState.setSetpoint(setpoint);
	sendMessage(std::make_shared<SetupMessage>(SetupMessage::CHANGE_ERROR_LIMIT, errorLimit));
	sendMessage(std::make_shared<SetupMessage>(SetupMessage::CHANGE_SETPOINT, setpoint));
}

/*
 * Leállítja a modul ütemezett mûködését.
 */
void TemperatureControllerApplication::stop() {
	if(stopped)	return;
	stopped = true;

	/* Az alkalmazás moduljainak leállítása. */
	sender.stop();
	regulatorModule->stop();
	sensorModule->stop();
	actuatorModule->stop();
	displayModule->stop();
}
