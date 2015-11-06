#ifndef INC_ACTUATORIMPL_H_
#define INC_ACTUATORIMPL_H_

#include <lib/app/inc/actuator/ActuatorInterface.h>
#include <bcm2835.h>

/**
 * @class ActuatorImpl
 * @brief A mûködtetõ komponenst megvalósító osztály.
 *
 * Ez az osztály a fûtõszálat és a ventilátort ki- és bekapcsoló reléket
 * mûködteti a GPIO-kon keresztül. Elõre beégetett módon a fûtõszálhoz
 * tartozó relé tekercsének a GPIO 18-ra ventilátorhoz tartozó relé
 * tekercsének pedig a GPIO 17-re kell csatlakozniuk. (A relék tekercseit
 * kizárólag kapcsolóüzemû tranzisztorokkal szabad a kimenetekrõl
 * meghajtani.)
 */
class ActuatorImpl : public ActuatorInterface {
	
public:
	/**
	 * @brief Az osztály alapértelmezett konstruktora.
	 */
	ActuatorImpl();

	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~ActuatorImpl();

	/**
	 * @brief Inicializálja a BCM2835 modult és az alkalmazott
	 * GPIO-kat.
	 */
	virtual void initialize();

	/**
	 * @brief A megadott értéket kiküldi a GPIO 18-ra.
	 *
	 * @param state A beállítani kívánt állapot.
	 */
	virtual void setHeaterState(bool state);

	/**
	 * @brief A megadott értéket kiküldi a GPIO 17-re.
	 *
	 * @param state A beállítani kívánt állapot.
	 */
	virtual void setFanState(bool state);

	/**
	 * @brief Lezárja a BCM2835 modult.
	 */
	virtual void close();
};

#endif /* INC_ACTUATORIMPL_H_ */