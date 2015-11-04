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
 * Az oszt�ly konstruktora.
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
 * Az oszt�ly virtu�lis destruktora.
 */
TemperatureControllerApplication::~TemperatureControllerApplication() {
	stop();
}

/*
 * Felveszi az �tadott fogad�t a feliratkozott fogad�k k�z�.
 */
void TemperatureControllerApplication::registerMessageReceiver(MessageReceiver& receiver) {
	sender.registerMessageReceiver(receiver);
}

/*
 * Elhelyezi az elk�ldeni k�v�nt �zenetet a v�rakoz�si sorba �s jelez
 * az �zeneteket k�zbes�t� sz�lnak, hogy folytathatja a v�rakoz�si
 * sorban lev� �zenetek k�zbes�t�s�t.
 */
void TemperatureControllerApplication::sendMessage(std::shared_ptr<BaseMessage> message) {
	sender.sendMessage(message);
}

/*
 * Hozz�f�rhet�v� teszi az alkalmaz�s �llapotait t�rol� objektumot.
 */
State& TemperatureControllerApplication::getState() {
	return appState;
}

/*
 * Elind�tja az alkalmaz�s �temezett m�k�d�s�t.
 */
void TemperatureControllerApplication::start() {
	if(!stopped) return;
	stopped = false;
	
	/* Az alkalmaz�s moduljainak elind�t�sa. */
	regulatorModule->start();
	sensorModule->start();
	actuatorModule->start();
	displayModule->start();
	sender.start();

	/* A fix�lt alapjel be�ll�t�sa az alkalmaz�s �llapotait
	t�rol� objektumban �s �j be�ll�t� �zenetek k�ld�se a m�dos�t�sok
	�rv�nybel�ptet�s�hez. */
	appState.setSetpoint(setpoint);
	sendMessage(std::make_shared<SetupMessage>(SetupMessage::CHANGE_ERROR_LIMIT, errorLimit));
	sendMessage(std::make_shared<SetupMessage>(SetupMessage::CHANGE_SETPOINT, setpoint));
}

/*
 * Le�ll�tja a modul �temezett m�k�d�s�t.
 */
void TemperatureControllerApplication::stop() {
	if(stopped)	return;
	stopped = true;

	/* Az alkalmaz�s moduljainak le�ll�t�sa. */
	sender.stop();
	regulatorModule->stop();
	sensorModule->stop();
	actuatorModule->stop();
	displayModule->stop();
}
