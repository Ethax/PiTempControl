#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/messages/SetupMessage.h>
#include <lib/app/inc/display/DisplayInterface.h>
#include <lib/app/inc/display/DisplayModule.h>

/*
 * Az oszt�ly konstruktora.
 */
DisplayModule::DisplayModule(TemperatureControllerApplication& app, DisplayInterface& component) : application(app), componentInterface(component) {
	app.registerMessageReceiver(*this);
}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
DisplayModule::~DisplayModule() {}

/*
 * Elind�tja a modul �temezett m�k�d�s�t.
 */
void DisplayModule::start() {
	componentInterface.initialize();
	componentInterface.refreshFanControllingValue(application.getState().getFanState());
	componentInterface.refreshHeaterControllingValue(application.getState().getHeaterState());
	setPeriod(0);
	PeriodicTimer::start();
}

/*
 * Le�ll�tja a modul �temezett m�k�d�s�t.
 */
void DisplayModule::stop() {
	PeriodicTimer::stop();
}

/*
 * Fogadja �s feldolgozza a h�m�rs�klet t�pus� �zeneteket.
 */
void DisplayModule::receiveMessage(const TemperatureMessage& msg) {
	componentInterface.refreshActualTemperature(msg.getTemperature());
}

/*
 * Fogadja �s feldolgozza a be�ll�t�s t�pus� �zeneteket.
 */
void DisplayModule::receiveMessage(const SetupMessage& msg) {
	if(msg.getMessageType() == SetupMessage::CHANGE_ERROR_LIMIT)
		componentInterface.refreshErrorLimit(msg.getSetupValue());
	else if(msg.getMessageType() == SetupMessage::CHANGE_SETPOINT)
		componentInterface.refreshSetpoint(msg.getSetupValue());
}

/*
 * Fogadja �s feldolgozza a vez�rl�s t�pus� �zeneteket.
 */
void DisplayModule::receiveMessage(const ControlMessage& msg) {
	if(msg.getMessageType() == ControlMessage::FAN_CONTROL)
		componentInterface.refreshFanControllingValue(msg.getControlValue());
	else if(msg.getMessageType() == ControlMessage::HEATER_CONTROL)
		componentInterface.refreshHeaterControllingValue(msg.getControlValue());
}
