#ifndef INC_SENSORMOCK_H_
#define INC_SENSORMOCK_H_

#include <lib/app/inc/sensor/SensorInterface.h>
#include <lib/app/inc/core/State.h>

/**
* @class SensorMock
* @brief Az érzékelõ komponens mûködését utánzó osztály.
*
* Ez az osztály tesztelési feladatok ellátására szolgál, az érzékelõ
* viselkedését elõre meghatározott módon utánozza.
*/
class SensorMock : public SensorInterface {
	/**
	 * A környezet statikus hõmérséklete.
	 */
	static const float ENVIRONMENTAL_TEMPERATURE;

	/**
	 * A szimulált hõmérséklet.
	 */
	float temperature;

	/**
	 * Az alkalmazás állapotait tároló Singleton.
	 */
	State& appState;

public:
	/**
	 * @brief Az utánzat alapértelmezett konstruktora.
	 */
	SensorMock();
	
	/**
	 * @brief Az utánzat virtuális destruktora.
	 */
	virtual ~SensorMock();

	/**
	 * @brief Jelzést ad az inicializáló metódus meghívásáról.
	 */
	virtual void initialize();

	/**
	 * @brief Szimulálja a hõmérséklet változását az aklamazás
	 * állapotaitól függõen.
	 *
	 * @return A szimulált hõmérséklet Celsius fokokban.
	 */
	virtual float getTemperature();

	/**
	 * @brief Nem végez semmilyen mûveletet sem.
	 */
	virtual void close();
};

#endif /* INC_SENSORMOCK_H_ */