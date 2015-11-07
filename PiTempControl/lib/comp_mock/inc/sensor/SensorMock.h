#ifndef INC_SENSORMOCK_H_
#define INC_SENSORMOCK_H_

#include <lib/app/inc/sensor/SensorInterface.h>
#include <lib/app/inc/core/State.h>

/**
* @class SensorMock
* @brief Az �rz�kel� komponens m�k�d�s�t ut�nz� oszt�ly.
*
* Ez az oszt�ly tesztel�si feladatok ell�t�s�ra szolg�l, az �rz�kel�
* viselked�s�t el�re meghat�rozott m�don ut�nozza.
*/
class SensorMock : public SensorInterface {
	/**
	 * A k�rnyezet statikus h�m�rs�klete.
	 */
	static const float ENVIRONMENTAL_TEMPERATURE;

	/**
	 * A szimul�lt h�m�rs�klet.
	 */
	float temperature;

	/**
	 * Az alkalmaz�s �llapotait t�rol� Singleton.
	 */
	State& appState;

public:
	/**
	 * @brief Az ut�nzat alap�rtelmezett konstruktora.
	 */
	SensorMock();
	
	/**
	 * @brief Az ut�nzat virtu�lis destruktora.
	 */
	virtual ~SensorMock();

	/**
	 * @brief Jelz�st ad az inicializ�l� met�dus megh�v�s�r�l.
	 */
	virtual void initialize();

	/**
	 * @brief Szimul�lja a h�m�rs�klet v�ltoz�s�t az aklamaz�s
	 * �llapotait�l f�gg�en.
	 *
	 * @return A szimul�lt h�m�rs�klet Celsius fokokban.
	 */
	virtual float getTemperature();

	/**
	 * @brief Nem v�gez semmilyen m�veletet sem.
	 */
	virtual void close();
};

#endif /* INC_SENSORMOCK_H_ */