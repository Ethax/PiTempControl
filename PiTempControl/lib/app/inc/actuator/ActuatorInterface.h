#ifndef INC_ACTUATORINTERFACE_H_
#define INC_ACTUATORINTERFACE_H_

#include <lib/app/inc/common.h>

/**
 * @class DisplayInterface
 * @brief A mûködtetõ komponens interfésze.
 *
 * A mûködtetõknek ebbõl az interfészbõl kell származniuk,
 * megvalósítva ennek minden egyes virtuális metódusát.
 */
class ActuatorInterface {
public:
	/**
	 * @brief Az interfész alapértelmezett konstruktora.
	 */
	ActuatorInterface() {}
	
	/**
	 * @brief Az intefész virtuális destruktora.
	 */
	virtual ~ActuatorInterface() {}

	/**
	 * @brief Inicializálja a mûködtetõ komponenst.
	 */
	virtual void initialize() = 0;

	/**
	 * @brief Beállítja a fûtõszál állapotát.
	 *
	 * @param state A beállítani kívánt állapot.
	 */
	virtual void setHeaterState(bool state) = 0;

	/**
	 * @brief Beállítja a ventilátor állapotát.
	 *
	 * @param state A beállítani kívánt állapot.
	 */
	virtual void setFanState(bool state) = 0;
};

#endif /* INC_ACTUATORINTERFACE_H_ */