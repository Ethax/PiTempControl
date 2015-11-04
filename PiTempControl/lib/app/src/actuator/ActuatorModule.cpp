#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/actuator/ActuatorInterface.h>
#include <lib/app/inc/actuator/ActuatorModule.h>

/*
 * Az osztály konstruktora.
 */
ActuatorModule::ActuatorModule(TemperatureControllerApplication& app, ActuatorInterface& component) : application(app), componentInterface(component) {
	app.registerMessageReceiver(*this);
}

/*
 * Az osztály virtuális destruktora.
 */
ActuatorModule::~ActuatorModule() {}

/*
 * Elindítja a modul ütemezett mûködését.
 */
void ActuatorModule::start() {
	componentInterface.initialize();
	setPeriod(0);
	PeriodicTimer::start();
}

/*
 * Leállítja a modul ütemezett mûködését.
 */
void ActuatorModule::stop() {
	PeriodicTimer::stop();
}

/*
 * Fogadja és feldolgozza a hõmérséklet típusú üzeneteket.
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
