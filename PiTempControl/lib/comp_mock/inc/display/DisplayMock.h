#ifndef INC_DISPLAYMOCK_H_
#define INC_DISPLAYMOCK_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/display/DisplayInterface.h>

/**
 * @class DisplayMock
 * @brief A kijelz� komponens m�k�d�s�t ut�nz� oszt�ly.
 *
 * Ez az oszt�ly tesztel�si feladatok ell�t�s�ra szolg�l, a kijelz�
 * viselked�s�t el�re meghat�rozott m�don ut�nozza.
 */
class DisplayMock : public DisplayInterface {
	std::string setpointIndicator;
	std::string heaterIndicator;
	std::string fanIndicator;
	std::string temperatureIndicator;

	/**
	 * @brief �ssze�ll�tja a ki�rni k�v�nt sort �s elv�gzi a
	 * ki�rat�st a konzol k�perny�re.
	 */
	void refreshDisplay(void);

public:
	/**
	 * @brief Az ut�nzat alap�rtelmezett konstruktora.
	 */
	DisplayMock();
	
	/**
	 * @brief Az ut�nzat virtu�lis destruktora.
	 */
	virtual ~DisplayMock();

	/**
	 * @brief Jelz�st ad az inicializ�l� met�dus megh�v�s�r�l.
	 */
	virtual void initialize();

	/**
	 * @brief Ki�rja a konzol k�perny�re a m�rt h�m�rs�kletet.
	 *
	 * @param _temp A m�rt h�m�rs�klet �rt�ke.
	 */
	virtual void refreshActualTemperature(const float _temp);

	/**
	 * @brief Ki�rja a konzol k�perny�re az alapjel �rt�k�t.
	 *
	 * @param _setpoint Az alapjel �rt�ke.
	 */
	virtual void refreshSetpoint(const float _setpoint);

	/**
	 * @brief Ki�rja a konzol k�perny�re a megengedett p�lyak�vet�si
	 * hiba �rt�k�t.
	 *
	 * @param _errorLimit A megengedett p�lyak�vet�si hiba �rt�ke.
	 */
	virtual void refreshErrorLimit(const float _errorLimit);

	/**
	 * @brief Ki�rja a konzol k�perny�re a ventil�tor �llapot�t.
	 *
	 * @param _fan A ventil�tor aktu�lis �llapota.
	 */
	virtual void refreshFanControllingValue(const bool _fan);

	/**
	 * @brief Ki�rja a konzol k�perny�re a f�t�sz�l �llapot�t.
	 *
	 * @param _heater A f�t�sz�l aktu�lis �llapota.
	 */
	virtual void refreshHeaterControllingValue(const bool _heater);
};

#endif /* INC_DISPLAYMOCK_H_ */