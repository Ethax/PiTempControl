#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/messages/SetupMessage.h>
#include <lib/app/inc/display/DisplayInterface.h>
#include <lib/app/inc/display/DisplayModule.h>

/*
 * Az osztály konstruktora.
 */
DisplayModule::DisplayModule(TemperatureControllerApplication& app, DisplayInterface& component) : application(app), componentInterface(component) {
	app.registerMessageReceiver(*this);
}

/*
 * Az osztály virtuális destruktora.
 */
DisplayModule::~DisplayModule() {}

/*
 * Elindítja a modul ütemezett mûködését.
 */
void DisplayModule::start() {
	componentInterface.initialize();
	componentInterface.refreshFanControllingValue(application.getState().getFanState());
	componentInterface.refreshHeaterControllingValue(application.getState().getHeaterState());
	setPeriod(0);
	PeriodicTimer::start();
}

/*
 * Leállítja a modul ütemezett mûködését.
 */
void DisplayModule::stop() {
	PeriodicTimer::stop();
}

/*
 * Fogadja és feldolgozza a hõmérséklet típusú üzeneteket.
 */
void DisplayModule::receiveMessage(const TemperatureMessage& msg) {
	componentInterface.refreshActualTemperature(msg.getTemperature());
}

/*
 * Fogadja és feldolgozza a beállítás típusú üzeneteket.
 */
void DisplayModule::receiveMessage(const SetupMessage& msg) {
	if(msg.getMessageType() == SetupMessage::CHANGE_ERROR_LIMIT)
		componentInterface.refreshErrorLimit(msg.getSetupValue());
	else if(msg.getMessageType() == SetupMessage::CHANGE_SETPOINT)
		componentInterface.refreshSetpoint(msg.getSetupValue());
}

/*
 * Fogadja és feldolgozza a vezérlés típusú üzeneteket.
 */
void DisplayModule::receiveMessage(const ControlMessage& msg) {
	if(msg.getMessageType() == ControlMessage::FAN_CONTROL)
		componentInterface.refreshFanControllingValue(msg.getControlValue());
	else if(msg.getMessageType() == ControlMessage::HEATER_CONTROL)
		componentInterface.refreshHeaterControllingValue(msg.getControlValue());
}
