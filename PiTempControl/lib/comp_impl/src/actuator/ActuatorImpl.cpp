#include <lib/comp_impl/inc/actuator/ActuatorImpl.h>
#include <lib/app/inc/core/AppException.h>

/*
 * Az oszt�ly alap�rtelmezett konstruktora.
 */
ActuatorImpl::ActuatorImpl() {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
ActuatorImpl::~ActuatorImpl() {}

/*
 * Inicializ�lja a BCM2835 modult �s az alkalmazott GPIO-kat.
 */
void ActuatorImpl::initialize() {
	if(!bcm2835_init())
		throw AppException("ActuatorImpl: BCM2835 initialization failed.");

	/* A GPIO 17 �s a GPIO 18 be�ll�t�sa kimeneteknek. */
	bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_OUTP);
}

/*
 * A megadott �rt�ket kik�ldi a GPIO 18-ra.
 */
void ActuatorImpl::setHeaterState(bool state) {
	bcm2835_gpio_write(RPI_GPIO_P1_12, state);
}

/*
 * A megadott �rt�ket kik�ldi a GPIO 17-re.
 */
void ActuatorImpl::setFanState(bool state) {
	bcm2835_gpio_write(RPI_GPIO_P1_11, state);
}

/*
 * Lez�rja a BCM2835 modult.
 */
void ActuatorImpl::close() {
	bcm2835_close();
}
