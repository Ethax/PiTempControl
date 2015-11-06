#include <lib/comp_impl/inc/actuator/ActuatorImpl.h>
#include <lib/app/inc/core/AppException.h>

/*
 * Az osztály alapértelmezett konstruktora.
 */
ActuatorImpl::ActuatorImpl() {}

/*
 * Az osztály virtuális destruktora.
 */
ActuatorImpl::~ActuatorImpl() {}

/*
 * Inicializálja a BCM2835 modult és az alkalmazott GPIO-kat.
 */
void ActuatorImpl::initialize() {
	if(!bcm2835_init())
		throw AppException("ActuatorImpl: BCM2835 initialization failed.");

	/* A GPIO 17 és a GPIO 18 beállítása kimeneteknek. */
	bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_OUTP);
}

/*
 * A megadott értéket kiküldi a GPIO 18-ra.
 */
void ActuatorImpl::setHeaterState(bool state) {
	bcm2835_gpio_write(RPI_GPIO_P1_12, state);
}

/*
 * A megadott értéket kiküldi a GPIO 17-re.
 */
void ActuatorImpl::setFanState(bool state) {
	bcm2835_gpio_write(RPI_GPIO_P1_11, state);
}

/*
 * Lezárja a BCM2835 modult.
 */
void ActuatorImpl::close() {
	bcm2835_close();
}
