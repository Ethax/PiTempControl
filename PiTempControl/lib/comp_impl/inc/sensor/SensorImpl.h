#ifndef INC_SENSORIMPL_H_
#define INC_SENSORIMPL_H_

#include <lib/app/inc/sensor/SensorInterface.h>
#include <lib/comp_impl/inc/sensor/SHT7xComm.h>

/**
* @class SensorMock
* @brief Az érzékelõ komponens mûködését utánzó osztály.
*
* Ez az osztály tesztelési feladatok ellátására szolgál, az érzékelõ
* viselkedését elõre meghatározott módon utánozza.
*/
class SensorImpl : public SensorInterface {
	/**
	 * Az érzékelõvel kommunikáló objektum.
	 */
	SHT7xComm sensor;

public:
	/**
	 * @brief Az utánzat alapértelmezett konstruktora.
	 */
	SensorImpl();
	
	/**
	 * @brief Az utánzat virtuális destruktora.
	 */
	virtual ~SensorImpl();

	/**
	 * @brief Jelzést ad az inicializáló metódus meghívásáról.
	 */
	virtual void initialize();

	/**
	 * @brief Szimulálja a hõmérséklet változását az aklamazás
	 * állapotaitól függõen.
	 */
	virtual float getTemperature();
};

#endif /* INC_SENSORIMPL_H_ */