#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/actuator/ActuatorInterface.h>
#include <lib/app/inc/actuator/ActuatorModule.h>

/*
 * Az oszt�ly konstruktora.
 */
ActuatorModule::ActuatorModule(TemperatureControllerApplication& app, ActuatorInterface& component) : application(app), componentInterface(component) {
	app.registerMessageReceiver(*this);
}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
ActuatorModule::~ActuatorModule() {}

/*
 * Elind�tja a modul �temezett m�k�d�s�t.
 */
void ActuatorModule::start() {
	componentInterface.initialize();
	setPeriod(0);
	PeriodicTimer::start();
}

/*
 * Le�ll�tja a modul �temezett m�k�d�s�t.
 */
void ActuatorModule::stop() {
	PeriodicTimer::stop();
}

/*
 * Fogadja �s feldolgozza a h�m�rs�klet t�pus� �zeneteket.
 */
void ActuatorModule::receiveMessage(const ControlMessage& msg) {
	if(msg.getMessageType() == ControlMessage::FAN_CONTROL) {
		componentInterface.setFanState(msg.getControlValue());
		application.getState().setFanState(msg.getControlValue());
	}		
	else if(msg.getMessageType() == ControlMessage::HEATER_CONTROL) {
		componentInterface.setHeaterState(msg.getControlValue());
		application.getState().setHeaterState(msg.getControlValue());
	}
}
