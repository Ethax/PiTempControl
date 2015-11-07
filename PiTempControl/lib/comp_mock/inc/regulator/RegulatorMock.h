#ifndef INC_REGULATORMOCK_H_
#define INC_REGULATORMOCK_H_

#include <lib/app/inc/regulator/RegulatorInterface.h>

/**
* @class RegulatorMock
* @brief A szabályozó komponens mûködését utánzó osztály.
*
* Ez az osztály tesztelési feladatok ellátására szolgál, a szabályozó
* viselkedését elõre meghatározott módon utánozza.
*/
class RegulatorMock : public RegulatorInterface {
	/**
	 * Az utoljára beállított alapjel.
	 */
	float setpoint;

	/**
	 * Az utoljára beállított megengedett pályakövetési hiba.
	 */
	float errorlimit;

public:
	/**
	 * @brief Az utánzat alapértelmezett konstruktora.
	 */
	RegulatorMock();

	/**
	 * @brief Az utánzat virtuális destruktora.
	 */
	virtual ~RegulatorMock();

	/**
	 * @brief Beállítja a kívánt alapjelet.
	 *
	 * @param _setpoint A beállítani kívánt alapjel.
	 */
	virtual void setDesiredSetpoint(const float _setpoint);

	/**
	 * @brief Beállítja a megengedett pályakövetési hibát.
	 *
	 * @param _errorlimit A beállítani kívánt pályakövetési hiba.
	 */
	virtual void setPositionErrorLimit(const float _errorlimit);

	/**
	 * @brief Meghatározza a bevatkozójelet az átadott hõmérséklet
	 * függvényében.
	 *
	 * @param actualTemperature Az aktuális hõmérséklet.
	 * @param fanState A ventilátor jelenlegi állapota.
	 * @param heaterState A fûtõszál jelenlegi állapota.
	 * @return A beavatkozó jelek készlete.
	 */
	virtual std::set<ControlSignal> getControlSignal(const float actualTemperature, const bool fanState, const bool heaterState);
};

#endif /* INC_REGULATORMOCK_H_ */