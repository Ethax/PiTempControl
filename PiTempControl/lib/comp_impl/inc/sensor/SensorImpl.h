#ifndef INC_SENSORIMPL_H_
#define INC_SENSORIMPL_H_

#include <lib/app/inc/sensor/SensorInterface.h>
#include <lib/comp_impl/inc/sensor/SHT7xComm.h>

/**
* @class SensorMock
* @brief Az érzékelõ komponenst megvalósító osztály.
*
* Ez az osztály egy SENSIRION SHT7x digitális hõmérséklet és páratartalom
* érzékelõ segítségével megméri a környezet hõmérsékletét és visszaadja
* a korrigált értéket Celsius fokokban.
*/
class SensorImpl : public SensorInterface {
	/**
	 * Az érzékelõvel kommunikáló objektum.
	 */
	SHT7xComm sensor;

public:
	/**
	 * @brief Az osztály alapértelmezett konstruktora.
	 */
	SensorImpl();
	
	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~SensorImpl();

	/**
	 * @brief Inicializálja a hõmérséklet érzékelõ komponenst és
	 * felállítja a kommunikációt a hõmérõ eszközzel.
	 */
	virtual void initialize();

	/**
	 * @brief Lekérdezi a hõmérõtõl az aktuális hõmérsékletet és
	 * visszaadja a Celsius fokokra átszámított értékét.
	 *
	 * @return A mért hõmérséklet Celsius fokokban.
	 */
	virtual float getTemperature();

	/**
	 * @brief Lezárja a kommunikációt az érzékelõvel.
	 */
	virtual void close();
};

#endif /* INC_SENSORIMPL_H_ */