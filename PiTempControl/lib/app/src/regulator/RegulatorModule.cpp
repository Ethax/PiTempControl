#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/messages/ControlMessage.h>
#include <lib/app/inc/messages/SetupMessage.h>
#include <lib/app/inc/regulator/RegulatorInterface.h>
#include <lib/app/inc/regulator/RegulatorModule.h>

/*
 * Az osztály konstruktora.
 */
RegulatorModule::RegulatorModule(TemperatureControllerApplication& app, RegulatorInterface& component) : application(app), componentInterface(component) {
	app.registerMessageReceiver(*this);
}

/*
 * Az osztály virtuális destruktora.
 */
RegulatorModule::~RegulatorModule() {}

/*
 * Elindítja a modul ütemezett mûködését.
 */
void RegulatorModule::start() {
	setPeriod(0);
	PeriodicTimer::start();
}

/*
 * Leállítja a modul ütemezett mûködését.
 */
void RegulatorModule::stop() {
	PeriodicTimer::stop();
}

/*
 * Fogadja és feldolgozza a hõmérséklet típusú üzeneteket.
 */
void RegulatorModule::receiveMessage(const TemperatureMessage& msg) {
	/* A ventilátor és a fûtõszál aktuális állapotainak lekérdezése. */
	bool fanCtrl = application.getState().getFanState();
	bool heaterCtrl = application.getState().getHeaterState();
	
	/* Beavatkozó jelek lekérdezése a hõmérsékletnek megfelelõen. */
	std::set<ControlSignal> signals = componentInterface.getControlSignal(msg.getTemperature(), fanCtrl, heaterCtrl);
	
	/* A beavatkozó jelek kiértékelése. */
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

	/* Üzenetek küldése a megváltoztatásra szoruló állapotokról. */
	if(fanCtrl != application.getState().getFanState())
		application.sendMessage(std::make_shared<ControlMessage>(ControlMessage::FAN_CONTROL, fanCtrl));
	if(heaterCtrl != application.getState().getHeaterState())
		application.sendMessage(std::make_shared<ControlMessage>(ControlMessage::HEATER_CONTROL, heaterCtrl));
}

/*
 * Fogadja és feldolgozza a beállítás típusú üzeneteket.
 */
void RegulatorModule::receiveMessage(const SetupMessage& msg) {
	if(msg.getMessageType() == SetupMessage::CHANGE_SETPOINT)
		componentInterface.setDesiredSetpoint(msg.getSetupValue());
	else if(msg.getMessageType() == SetupMessage::CHANGE_ERROR_LIMIT)
		componentInterface.setPositionErrorLimit(msg.getSetupValue());
}
