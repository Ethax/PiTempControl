#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/messages/SetupMessage.h>
#include <lib/app/inc/regulator/RegulatorInterface.h>
#include <lib/app/inc/regulator/RegulatorModule.h>

/*
 * Az oszt�ly konstruktora.
 */
RegulatorModule::RegulatorModule(TemperatureControllerApplication& app, RegulatorInterface& component) : application(app), componentInterface(component) {
	app.registerMessageReceiver(*this);
}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
RegulatorModule::~RegulatorModule() {}

/*
 * Elind�tja a modul �temezett m�k�d�s�t.
 */
void RegulatorModule::start() {
	setPeriod(0);
	PeriodicTimer::start();
}

/*
 * Le�ll�tja a modul �temezett m�k�d�s�t.
 */
void RegulatorModule::stop() {
	PeriodicTimer::stop();
}

/*
 * Fogadja �s feldolgozza a h�m�rs�klet t�pus� �zeneteket.
 */
void RegulatorModule::receiveMessage(const TemperatureMessage& msg) {
	/* A ventil�tor �s a f�t�sz�l aktu�lis �llapotainak lek�rdez�se. */
	bool fanCtrl = application.getState().getFanState();
	bool heaterCtrl = application.getState().getHeaterState();
	
	/* Beavatkoz� jelek lek�rdez�se a h�m�rs�kletnek megfelel�en. */
	std::set<ControlSignal> signals = componentInterface.getControlSignal(msg.getTemperature(), fanCtrl, heaterCtrl);
	
	/* A beavatkoz� jelek ki�rt�kel�se. */
	for(ControlSignal signal : signals) {
		switch(signal) {
		case CTRL_SWITCH_ON_THE_FAN:
			fanCtrl = true;
			break;
		case CTRL_SWITCH_OFF_THE_FAN:
			fanCtrl = false;
			break;
		case CTRL_SWITCH_ON_THE_HEATER:
			heaterCtrl = true;
			break;
		case CTRL_SWITCH_OFF_THE_HEATER:
			heaterCtrl = false;
			break;
		}
	}

	/* �zenetek k�ld�se a megv�ltoztat�sra szorul� �llapotokr�l. */
	if(fanCtrl != application.getState().getFanState())
		application.sendMessage(std::make_shared<ControlMessage>(ControlMessage::FAN_CONTROL, fanCtrl));
	if(heaterCtrl != application.getState().getHeaterState())
		application.sendMessage(std::make_shared<ControlMessage>(ControlMessage::HEATER_CONTROL, heaterCtrl));
}

/*
 * Fogadja �s feldolgozza a be�ll�t�s t�pus� �zeneteket.
 */
void RegulatorModule::receiveMessage(const SetupMessage& msg) {
	if(msg.getMessageType() == SetupMessage::CHANGE_SETPOINT)
		componentInterface.setDesiredSetpoint(msg.getSetupValue());
	else if(msg.getMessageType() == SetupMessage::CHANGE_ERROR_LIMIT)
		componentInterface.setPositionErrorLimit(msg.getSetupValue());
}
