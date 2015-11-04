#ifndef INC_ACTUATORINTERFACE_H_
#define INC_ACTUATORINTERFACE_H_

#include <lib/app/inc/common.h>

/**
 * @class DisplayInterface
 * @brief A m�k�dtet� komponens interf�sze.
 *
 * A m�k�dtet�knek ebb�l az interf�szb�l kell sz�rmazniuk,
 * megval�s�tva ennek minden egyes virtu�lis met�dus�t.
 */
class ActuatorInterface {
public:
	/**
	 * @brief Az interf�sz alap�rtelmezett konstruktora.
	 */
	ActuatorInterface() {}
	
	/**
	 * @brief Az intef�sz virtu�lis destruktora.
	 */
	virtual ~ActuatorInterface() {}

	/**
	 * @brief Inicializ�lja a m�k�dtet� komponenst.
	 */
	virtual void initialize() = 0;

	/**
	 * @brief Be�ll�tja a f�t�sz�l �llapot�t.
	 *
	 * @param state A be�ll�tani k�v�nt �llapot.
	 */
	virtual void setHeaterState(bool state) = 0;

	/**
	 * @brief Be�ll�tja a ventil�tor �llapot�t.
	 *
	 * @param state A be�ll�tani k�v�nt �llapot.
	 */
	virtual void setFanState(bool state) = 0;
};

#endif /* INC_ACTUATORINTERFACE_H_ */