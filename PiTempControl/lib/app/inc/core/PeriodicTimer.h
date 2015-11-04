#ifndef INC_PERIODICTIMER_H_
#define INC_PERIODICTIMER_H_

#include <lib/app/inc/common.h>

/**
 * @class PeriodicTimer
 * @brief P�rhuzamos �s id�szakos m�veletek ism�tl�d� v�grehajt�s�t
 * biztos�t� absztrakt oszt�ly.
 */
class PeriodicTimer {
	/**
	 * A t�bb sz�lr�l val� egyidej� hozz�f�r�st kiz�r� adattag.
	 */
	std::recursive_mutex mutex;

	/**
	 * A m�veletek ism�tl�d� v�grehajt�s�t v�gz� sz�l le�ll�t�sakor
	 * haszn�lt k�lcs�n�s kiz�r�st biztos�t� adattag.
	 */
	std::recursive_mutex joinMutex;

	/**
	 * A m�veletek ism�tl�d� v�grehajt�s�t v�gz� sz�l id�szakos
	 * felf�ggeszt�s�hez haszn�lt �llapotv�ltoz�.
	 */
	std::condition_variable_any condition;

	/**
	 * Az ism�tl�d� v�grehajt�sok k�z�tti sz�neteltet�s id�tartama.
	 */
	long period;

	/**
	 * A m�veletek ism�tl�d� v�grehajt�s�t v�gz� sz�l fut�s�nak
	 * �llapota.
	 */
	std::atomic_bool active;

	/**
	 * A m�veletek ism�tl�d� v�grehajt�s�t v�gz� sz�l kezel�s�t
	 * biztos�t� adattag.
	 */
	std::thread timerThread;

	/**
	 * @brief K�l�n sz�lon futva azonos id�k�z�nk�nt megh�vja a
	 * lesz�rmaztatott osz�lyban megval�s�tott, virtu�lis
	 * periodicOperation met�dust.
	 */
	void loop();

protected:
	/**
	 * @brief Az osz�ly alap�rtelmezett konstruktora.
	 */
	PeriodicTimer();
	
	/**
	 * @brief Az oszt�ly m�sol� konstruktor�nak tilt�sa.
	 */
	PeriodicTimer(PeriodicTimer&) = delete;
	
	/**
	 * @brief Az oszt�ly �rt�kad� oper�tor�nak tilt�sa.
	 */
	PeriodicTimer& operator=(const PeriodicTimer&) = delete;
	
	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~PeriodicTimer();

	/**
	 * @brief Elind�tja a m�veletek ism�tl�d� v�grehajt�s�t v�gz�
	 * sz�lat.
	 */
	void start();

	/**
	 * @brief Le�ll�tja a m�veletek ism�tl�d� v�grehajt�s�t v�gz�
	 * sz�lat.
	 */
	void stop();

	/**
	 * @brief Be�ll�tja az ism�tl�d� v�grehajt�sok k�z�tti sz�neteltet�s
	 * id�tartam�t.
	 *
	 * @param _period A sz�neteltet�s id�tartama milliszekundumokban.
	 */
	void setPeriod(long _period);

	/**
	 * @brief Az id�szakosan ism�tl�d� m�velet, amit a lesz�rmaztatott
	 * oszt�lynak meg kell val�s�tania.
	 */
	virtual void periodicOperation() = 0;
};

#endif /* INC_PERIODICTIMER_H_ */