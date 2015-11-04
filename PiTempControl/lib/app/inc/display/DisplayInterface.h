#ifndef INC_DISPLAYINTERFACE_H_
#define INC_DISPLAYINTERFACE_H_

#include <lib/app/inc/common.h>

/**
 * @class DisplayInterface
 * @brief A kijelz� komponens interf�sze.
 *
 * A kijelz�knek ebb�l az interf�szb�l kell sz�rmazniuk,
 * megval�s�tva ennek minden egyes virtu�lis met�dus�t.
 */
class DisplayInterface {
public:
	/**
	 * @brief Az interf�sz alap�rtelmezett konstruktora.
	 */
	DisplayInterface() {}

	/**
	 * @brief Az intef�sz virtu�lis destruktora.
	 */
	virtual ~DisplayInterface() {}

	/**
	 * @brief Inicializ�lja a kijelz� komponenst.
	 */
	virtual void initialize() = 0;

	/**
	 * @brief Friss�ti a kijelz�n a m�rt h�m�rs�kletet.
	 *
	 * @param _temp A m�rt h�m�rs�klet �rt�ke.
	 */
	virtual void refreshActualTemperature(const float _temp) = 0;

	/**
	 * @brief Friss�ti a kijelz�n az alapjel �rt�k�t.
	 *
	 * @param _setpoint Az alapjel �rt�ke.
	 */
	virtual void refreshSetpoint(const float _setpoint) = 0;

	/**
	 * @brief Friss�ti a kijelz�n a megengedett p�lyak�vet�si hiba
	 * �rt�k�t.
	 *
	 * @param _errorLimit A megengedett p�lyak�vet�si hiba �rt�ke.
	 */
	virtual void refreshErrorLimit(const float _errorLimit) = 0;

	/**
	 * @brief Friss�ti a kijelz�n a ventil�tor �llapot�t.
	 *
	 * @param _fan A ventil�tor aktu�lis �llapota.
	 */
	virtual void refreshFanControllingValue(const bool _fan) = 0;

	/**
	 * @brief Friss�ti a kijelz�n a f�t�sz�l �llapot�t.
	 *
	 * @param _heater A f�t�sz�l aktu�lis �llapota.
	 */
	virtual void refreshHeaterControllingValue(const bool _heater) = 0;
};

#endif /* INC_DISPLAYINTERFACE_H_ */