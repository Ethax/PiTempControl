#include <lib/comp_impl/inc/sensor/SensorImpl.h>
#include <lib/app/inc/core/AppException.h>

/*
 * Az utánzat alapértelmezett konstruktora.
 */
SensorImpl::SensorImpl() {}

/*
 * Az utánzat virtuális destruktora.
 */
SensorImpl::~SensorImpl() {}

/*
 * Jelzést ad az inicializáló metódus meghívásáról.
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
 * Szimulálja a hõmérséklet változását az aklamazás állapotaitól
 * függõen.
 */
float SensorImpl::getTemperature() {
	// Request Temperature measurement
	if(!sensor.measureStart(SHT7xComm::MEASURE_TEMPERATURE))
		throw AppException("Cannot start the temperature measurement.");

	float temperature = sensor.getMeasureValue();

	return temperature * 0.01f - 39.7f;
}
