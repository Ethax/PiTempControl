#include <lib/comp_impl/inc/sensor/SensorImpl.h>
#include <lib/app/inc/core/AppException.h>

/*
 * Az oszt�ly alap�rtelmezett konstruktora.
 */
SensorImpl::SensorImpl() {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
SensorImpl::~SensorImpl() {}

/*
 * Inicializ�lja a h�m�rs�klet �rz�kel� komponenst �s fel�ll�tja a
 * kommunik�ci�t a h�m�r� eszk�zzel.
 */
void SensorImpl::initialize() {
	delay(20);
	sensor.initializePins(RPI_GPIO_P1_16, RPI_GPIO_P1_18);
	sensor.reset();
}

/*
 * Lek�rdezi a h�m�r�t�l az aktu�lis h�m�rs�kletet �s visszaadja a
 * Celsius fokokra �tsz�m�tott �rt�k�t.
 */
float SensorImpl::getTemperature() {
	if(!sensor.measureStart(SHT7xComm::MEASURE_TEMPERATURE))
		throw AppException("Cannot start the temperature measurement.");
	float temperature = (float)sensor.getMeasureValue();
	return temperature * 0.01f - 39.7f;
}

/*
 * Lez�rja a kommunik�ci�t az �rz�kel�vel.
 */
void SensorImpl::close() {
	sensor.close();
}
