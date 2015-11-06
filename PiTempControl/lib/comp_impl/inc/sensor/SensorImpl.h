#ifndef INC_SENSORIMPL_H_
#define INC_SENSORIMPL_H_

#include <lib/app/inc/sensor/SensorInterface.h>
#include <lib/comp_impl/inc/sensor/SHT7xComm.h>

/**
* @class SensorMock
* @brief Az �rz�kel� komponens m�k�d�s�t ut�nz� oszt�ly.
*
* Ez az oszt�ly tesztel�si feladatok ell�t�s�ra szolg�l, az �rz�kel�
* viselked�s�t el�re meghat�rozott m�don ut�nozza.
*/
class SensorImpl : public SensorInterface {
	/**
	 * Az �rz�kel�vel kommunik�l� objektum.
	 */
	SHT7xComm sensor;

public:
	/**
	 * @brief Az ut�nzat alap�rtelmezett konstruktora.
	 */
	SensorImpl();
	
	/**
	 * @brief Az ut�nzat virtu�lis destruktora.
	 */
	virtual ~SensorImpl();

	/**
	 * @brief Jelz�st ad az inicializ�l� met�dus megh�v�s�r�l.
	 */
	virtual void initialize();

	/**
	 * @brief Szimul�lja a h�m�rs�klet v�ltoz�s�t az aklamaz�s
	 * �llapotait�l f�gg�en.
	 */
	virtual float getTemperature();
};

#endif /* INC_SENSORIMPL_H_ */