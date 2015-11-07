#ifndef INC_SENSORIMPL_H_
#define INC_SENSORIMPL_H_

#include <lib/app/inc/sensor/SensorInterface.h>
#include <lib/comp_impl/inc/sensor/SHT7xComm.h>

/**
* @class SensorMock
* @brief Az �rz�kel� komponenst megval�s�t� oszt�ly.
*
* Ez az oszt�ly egy SENSIRION SHT7x digit�lis h�m�rs�klet �s p�ratartalom
* �rz�kel� seg�ts�g�vel megm�ri a k�rnyezet h�m�rs�klet�t �s visszaadja
* a korrig�lt �rt�ket Celsius fokokban.
*/
class SensorImpl : public SensorInterface {
	/**
	 * Az �rz�kel�vel kommunik�l� objektum.
	 */
	SHT7xComm sensor;

public:
	/**
	 * @brief Az oszt�ly alap�rtelmezett konstruktora.
	 */
	SensorImpl();
	
	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~SensorImpl();

	/**
	 * @brief Inicializ�lja a h�m�rs�klet �rz�kel� komponenst �s
	 * fel�ll�tja a kommunik�ci�t a h�m�r� eszk�zzel.
	 */
	virtual void initialize();

	/**
	 * @brief Lek�rdezi a h�m�r�t�l az aktu�lis h�m�rs�kletet �s
	 * visszaadja a Celsius fokokra �tsz�m�tott �rt�k�t.
	 *
	 * @return A m�rt h�m�rs�klet Celsius fokokban.
	 */
	virtual float getTemperature();

	/**
	 * @brief Lez�rja a kommunik�ci�t az �rz�kel�vel.
	 */
	virtual void close();
};

#endif /* INC_SENSORIMPL_H_ */