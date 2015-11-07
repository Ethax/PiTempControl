#ifndef INC_DISPLAYMOCK_H_
#define INC_DISPLAYMOCK_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/display/DisplayInterface.h>

#define cret '\r'

/**
 * @class DisplayMock
 * @brief A kijelz� komponens m�k�d�s�t ut�nz� oszt�ly.
 *
 * Ez az oszt�ly tesztel�si feladatok ell�t�s�ra szolg�l, a kijelz�
 * viselked�s�t el�re meghat�rozott m�don ut�nozza.
 */
class DisplayMock : public DisplayInterface {
	/**
	 * Az alapjelre vonatkoz� inform�ci�t megjelen�t� c�mke puffere.
	 */
	std::string setpointIndicator;

	/**
	 * A f�t�sz�lra vonatkoz� inform�ci�t megjelen�t� c�mke puffere.
	 */
	std::string heaterIndicator;
	
	/**
	 * Az ventil�rra vonatkoz� inform�ci�t megjelen�t� c�mke puffere.
	 */
	std::string fanIndicator;

	/**
	 * Az h�m�rs�kletre vonatkoz� inform�ci�t megjelen�t� c�mke puffere.
	 */
	std::string temperatureIndicator;

	/**
	 * @brief �ssze�ll�tja a ki�rni k�v�nt sort a c�mk�kb�l �s
	 * elv�gzi a ki�rat�st a konzol k�perny�re.
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
	 * @brief Nem v�gez semmilyen m�veletet sem.
	 */
	virtual void initialize();

	/**
	 * @brief Friss�ti a h�m�rs�klet-c�mke tartalm�t, ezt k�vet�en
	 * pedig a konzol k�perny� tartalm�t.
	 *
	 * @param _temp A m�rt h�m�rs�klet �rt�ke.
	 */
	virtual void refreshActualTemperature(const float _temp);

	/**
	 * @brief Friss�ti az alapjel-c�mke tartalm�t, ezt k�vet�en
	 * pedig a konzol k�perny� tartalm�t.
	 *
	 * @param _setpoint Az alapjel �rt�ke.
	 */
	virtual void refreshSetpoint(const float _setpoint);

	/**
	 * @brief Nem v�gez semmilyen m�veletet sem.
	 *
	 * @param _errorLimit A megengedett p�lyak�vet�si hiba �rt�ke.
	 */
	virtual void refreshErrorLimit(const float _errorLimit);

	/**
	 * @brief Friss�ti az ventil�tor-c�mke tartalm�t, ezt k�vet�en
	 * pedig a konzol k�perny� tartalm�t.
	 *
	 * @param _fan A ventil�tor aktu�lis �llapota.
	 */
	virtual void refreshFanControllingValue(const bool _fan);

	/**
	 * @brief Friss�ti az f�t�sz�l-c�mke tartalm�t, ezt k�vet�en
	 * pedig a konzol k�perny� tartalm�t.
	 *
	 * @param _heater A f�t�sz�l aktu�lis �llapota.
	 */
	virtual void refreshHeaterControllingValue(const bool _heater);
};

#endif /* INC_DISPLAYMOCK_H_ */