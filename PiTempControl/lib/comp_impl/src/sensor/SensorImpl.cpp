#include <lib/comp_impl/inc/sensor/SensorImpl.h>
#include <lib/app/inc/core/AppException.h>

/*
 * Az osztály alapértelmezett konstruktora.
 */
SensorImpl::SensorImpl() {}

/*
 * Az osztály virtuális destruktora.
 */
SensorImpl::~SensorImpl() {}

/*
 * Inicializálja a hõmérséklet érzékelõ komponenst és felállítja a
 * kommunikációt a hõmérõ eszközzel.
 */
void SensorImpl::initialize() {
	delay(20);
	sensor.initializePins(RPI_GPIO_P1_16, RPI_GPIO_P1_18);
	sensor.reset();
}

/*
 * Lekérdezi a hõmérõtõl az aktuális hõmérsékletet és visszaadja a
 * Celsius fokokra átszámított értékét.
 */
float SensorImpl::getTemperature() {
	if(!sensor.measureStart(SHT7xComm::MEASURE_TEMPERATURE))
		throw AppException("Cannot start the temperature measurement.");
	float temperature = (float)sensor.getMeasureValue();
	return temperature * 0.01f - 39.7f;
}

/*
 * Lezárja a kommunikációt az érzékelõvel.
 */
void SensorImpl::close() {
	sensor.close();
}
