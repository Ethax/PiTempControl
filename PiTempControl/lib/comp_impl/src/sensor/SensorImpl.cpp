#include <lib/comp_impl/inc/sensor/SensorImpl.h>
#include <lib/app/inc/core/AppException.h>

/*
 * Az ut�nzat alap�rtelmezett konstruktora.
 */
SensorImpl::SensorImpl() {}

/*
 * Az ut�nzat virtu�lis destruktora.
 */
SensorImpl::~SensorImpl() {}

/*
 * Jelz�st ad az inicializ�l� met�dus megh�v�s�r�l.
 */
void SensorImpl::initialize() {
	// Wait at least 11ms after power-up (chapter 3.1)
	delay(20);

	// Set up the SHT1x Data and Clock Pins
	sensor.initializePins(RPI_GPIO_P1_16, RPI_GPIO_P1_18);

	// Reset the SHT1x
	sensor.reset();
}

/*
 * Szimul�lja a h�m�rs�klet v�ltoz�s�t az aklamaz�s �llapotait�l
 * f�gg�en.
 */
float SensorImpl::getTemperature() {
	// Request Temperature measurement
	if(!sensor.measureStart(SHT7xComm::MEASURE_TEMPERATURE))
		throw AppException("Cannot start the temperature measurement.");

	float temperature = sensor.getMeasureValue();

	return temperature * 0.01f - 39.7f;
}
