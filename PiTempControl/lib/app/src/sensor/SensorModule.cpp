#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/sensor/SensorInterface.h>
#include <lib/app/inc/sensor/SensorModule.h>

/*
 * Az oszt�ly konstruktora.
 */
SensorModule::SensorModule(TemperatureControllerApplication & app, SensorInterface & component) : application(app), componentInterface(component) {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
SensorModule::~SensorModule() {}

/*
 * Elind�tja a modul �temezett m�k�d�s�t.
 */
void SensorModule::start() {
	componentInterface.initialize();
#ifdef SUBSTITUTE_HARDWARE
	setPeriod(1500);
#else
	setPeriod(500);
#endif
	PeriodicTimer::start();
}

/*
 * Le�ll�tja a modul �temezett m�k�d�s�t.
 */
void SensorModule::stop() {
	componentInterface.close();
	PeriodicTimer::stop();
}

/*
 * Lek�rdezi a konkr�t komponenst�l az aktu�lis h�m�rs�kletet �s
 * �zenetet k�ld a kapott v�lasszal.
 */
void SensorModule::periodicOperation() {
	float temperature = componentInterface.getTemperature();
	application.getState().setActualTemperature(temperature);
	application.sendMessage(std::make_shared<TemperatureMessage>(TemperatureMessage::ACTUAL_TEMPERATURE, temperature));
}
