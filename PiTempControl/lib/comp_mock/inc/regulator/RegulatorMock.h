#ifndef INC_REGULATORMOCK_H_
#define INC_REGULATORMOCK_H_

#include <lib/app/inc/regulator/RegulatorInterface.h>

/**
* @class RegulatorMock
* @brief A szab�lyoz� komponens m�k�d�s�t ut�nz� oszt�ly.
*
* Ez az oszt�ly tesztel�si feladatok ell�t�s�ra szolg�l, a szab�lyoz�
* viselked�s�t el�re meghat�rozott m�don ut�nozza.
*/
class RegulatorMock : public RegulatorInterface {
	/**
	 * Az utolj�ra be�ll�tott alapjel.
	 */
	float setpoint;

	/**
	 * Az utolj�ra be�ll�tott megengedett p�lyak�vet�si hiba.
	 */
	float errorlimit;

public:
	/**
	 * @brief Az ut�nzat alap�rtelmezett konstruktora.
	 */
	RegulatorMock();

	/**
	 * @brief Az ut�nzat virtu�lis destruktora.
	 */
	virtual ~RegulatorMock();

	/**
	 * @brief Be�ll�tja a k�v�nt alapjelet.
	 *
	 * @param _setpoint A be�ll�tani k�v�nt alapjel.
	 */
	virtual void setDesiredSetpoint(const float _setpoint);

	/**
	 * @brief Be�ll�tja a megengedett p�lyak�vet�si hib�t.
	 *
	 * @param _errorlimit A be�ll�tani k�v�nt p�lyak�vet�si hiba.
	 */
	virtual void setPositionErrorLimit(const float _errorlimit);

	/**
	 * @brief Meghat�rozza a bevatkoz�jelet az �tadott h�m�rs�klet
	 * f�ggv�ny�ben.
	 *
	 * @param actualTemperature Az aktu�lis h�m�rs�klet.
	 * @param fanState A ventil�tor jelenlegi �llapota.
	 * @param heaterState A f�t�sz�l jelenlegi �llapota.
	 * @return A beavatkoz� jelek k�szlete.
	 */
	virtual std::set<ControlSignal> getControlSignal(const float actualTemperature, const bool fanState, const bool heaterState);
};

#endif /* INC_REGULATORMOCK_H_ */