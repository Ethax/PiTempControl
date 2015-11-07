#ifndef INC_SENSORINTERFACE_H_
#define INC_SENSORINTERFACE_H_

#include <lib/app/inc/common.h>

/**
 * @class SensorInterface
 * @brief A érzékelõ komponens interfésze.
 *
 * A érzékelõknek ebbõl az interfészbõl kell származniuk,
 * megvalósítva ennek minden egyes virtuális metódusát.
 */
class SensorInterface {
public:
	/**
	 * @brief Az interfész alapértelmezett konstruktora.
	 */
	SensorInterface() {}

	/**
	 * @brief Az intefész virtuális destruktora.
	 */
	virtual ~SensorInterface() {}

	/**
	 * @brief Inicializálja a hõmérséklet érzékelõ komponenst és
	 * felállítja a kommunikációt a hõmérõ eszközzel.
	 */
	virtual void initialize() = 0;

	/**
	 * @brief Lekérdezi a hõmérõtõl az aktuális hõmérsékletet.
	 *
	 * @return A mért hõmérséklet.
	 */
	virtual float getTemperature() = 0;

	/**
	 * @brief Lezárja az érzékelõ komponenst.
	 */
	virtual void close() = 0;
};

#endif /* INC_SENSORINTERFACE_H_ */