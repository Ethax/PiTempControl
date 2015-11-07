#ifndef INC_REGULATORINTERFACE_H_
#define INC_REGULATORINTERFACE_H_

#include <lib/app/inc/common.h>

/**
 * A szab�lyoz� komponens bevatkoz� jelei a h�m�rs�kletre.
 */
enum ControlSignal {
	CTRL_SWITCH_ON_THE_FAN,
	CTRL_SWITCH_OFF_THE_FAN,
	CTRL_SWITCH_ON_THE_HEATER,
	CTRL_SWITCH_OFF_THE_HEATER
};

/**
 * @class RegulatorInterface
 * @brief A szab�lyoz� komponens interf�sze.
 *
 * A szab�lyoz�knak ebb�l az interf�szb�l kell sz�rmazniuk,
 * megval�s�tva ennek minden egyes virtu�lis met�dus�t.
 */
class RegulatorInterface {
public:
	/**
	 * @brief Az interf�sz alap�rtelmezett konstruktora.
	 */
	RegulatorInterface() {}
	
	/**
	 * @brief Az intef�sz virtu�lis destruktora.
	 */
	virtual ~RegulatorInterface() {}

	/**
	 * @brief Be�ll�tja a k�v�nt alapjelet.
	 *
	 * @param _setpoint A be�ll�tani k�v�nt alapjel.
	 */
	virtual void setDesiredSetpoint(const float _setpoint) = 0;

	/**
	 * @brief Be�ll�tja a megengedett p�lyak�vet�si hib�t.
	 *
	 * @param _errorlimit A be�ll�tani k�v�nt p�lyak�vet�si hiba.
	 */
	virtual void setPositionErrorLimit(const float _errorlimit) = 0;

	/**
	 * @brief Meghat�rozza a bevatkoz�jelet az �tadott h�m�rs�klet
	 * f�ggv�ny�ben.
	 *
	 * @param actualTemperature Az aktu�lis h�m�rs�klet.
	 * @param fanState A ventil�tor jelenlegi �llapota.
	 * @param heaterState A f�t�sz�l jelenlegi �llapota.
	 * @return A beavatkoz� jelek k�szlete.
	 */
	virtual std::set<ControlSignal> getControlSignal(const float actualTemperature, const bool fanState, const bool heaterState) = 0;
};

#endif /* INC_REGULATORINTERFACE_H_ */