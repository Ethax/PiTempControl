#include <lib/app/inc/messages/TemperatureMessage.h>
#include <lib/app/inc/sensor/SensorInterface.h>
#include <lib/app/inc/sensor/SensorModule.h>

/*
 * Az osztály konstruktora.
 */
SensorModule::SensorModule(TemperatureControllerApplication & app, SensorInterface & component) : application(app), componentInterface(component) {}

/*
 * Az osztály virtuális destruktora.
 */
SensorModule::~SensorModule() {}

/*
 * Elindítja a modul ütemezett mûködését.
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
 * Leállítja a modul ütemezett mûködését.
 */
void SensorModule::stop() {
	componentInterface.close();
	PeriodicTimer::stop();
}

/*
 * Lekérdezi a konkrét komponenstõl az aktuális hõmérsékletet és
 * üzenetet küld a kapott válasszal.
 */
void SensorModule::periodicOperation() {
	float temperature = componentInterface.getTemperature();
	application.getState().setActualTemperature(temperature);
	application.sendMessage(std::make_shared<TemperatureMessage>(TemperatureMessage::ACTUAL_TEMPERATURE, temperature));
}
