#ifndef INC_SENSORINTERFACE_H_
#define INC_SENSORINTERFACE_H_

#include <lib/app/inc/common.h>

/**
 * @class SensorInterface
 * @brief A �rz�kel� komponens interf�sze.
 *
 * A �rz�kel�knek ebb�l az interf�szb�l kell sz�rmazniuk,
 * megval�s�tva ennek minden egyes virtu�lis met�dus�t.
 */
class SensorInterface {
public:
	/**
	 * @brief Az interf�sz alap�rtelmezett konstruktora.
	 */
	SensorInterface() {}

	/**
	 * @brief Az intef�sz virtu�lis destruktora.
	 */
	virtual ~SensorInterface() {}

	/**
	 * @brief Inicializ�lja a h�m�rs�klet �rz�kel� komponenst �s
	 * fel�ll�tja a kommunik�ci�t a h�m�r� eszk�zzel.
	 */
	virtual void initialize() = 0;

	/**
	 * @brief Lek�rdezi a h�m�r�t�l az aktu�lis h�m�rs�kletet.
	 */
	virtual float getTemperature() = 0;
};

#endif /* INC_SENSORINTERFACE_H_ */