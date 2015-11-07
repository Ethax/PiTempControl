#ifndef INC_REGULATORINTERFACE_H_
#define INC_REGULATORINTERFACE_H_

#include <lib/app/inc/common.h>

/**
 * A szabályozó komponens bevatkozó jelei a hõmérsékletre.
 */
enum ControlSignal {
	CTRL_SWITCH_ON_THE_FAN,
	CTRL_SWITCH_OFF_THE_FAN,
	CTRL_SWITCH_ON_THE_HEATER,
	CTRL_SWITCH_OFF_THE_HEATER
};

/**
 * @class RegulatorInterface
 * @brief A szabályozó komponens interfésze.
 *
 * A szabályozóknak ebbõl az interfészbõl kell származniuk,
 * megvalósítva ennek minden egyes virtuális metódusát.
 */
class RegulatorInterface {
public:
	/**
	 * @brief Az interfész alapértelmezett konstruktora.
	 */
	RegulatorInterface() {}
	
	/**
	 * @brief Az intefész virtuális destruktora.
	 */
	virtual ~RegulatorInterface() {}

	/**
	 * @brief Beállítja a kívánt alapjelet.
	 *
	 * @param _setpoint A beállítani kívánt alapjel.
	 */
	virtual void setDesiredSetpoint(const float _setpoint) = 0;

	/**
	 * @brief Beállítja a megengedett pályakövetési hibát.
	 *
	 * @param _errorlimit A beállítani kívánt pályakövetési hiba.
	 */
	virtual void setPositionErrorLimit(const float _errorlimit) = 0;

	/**
	 * @brief Meghatározza a bevatkozójelet az átadott hõmérséklet
	 * függvényében.
	 *
	 * @param actualTemperature Az aktuális hõmérséklet.
	 * @param fanState A ventilátor jelenlegi állapota.
	 * @param heaterState A fûtõszál jelenlegi állapota.
	 * @return A beavatkozó jelek készlete.
	 */
	virtual std::set<ControlSignal> getControlSignal(const float actualTemperature, const bool fanState, const bool heaterState) = 0;
};

#endif /* INC_REGULATORINTERFACE_H_ */