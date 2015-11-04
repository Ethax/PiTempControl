#ifndef INC_PERIODICTIMER_H_
#define INC_PERIODICTIMER_H_

#include <lib/app/inc/common.h>

/**
 * @class PeriodicTimer
 * @brief Párhuzamos és idõszakos mûveletek ismétlõdõ végrehajtását
 * biztosító absztrakt osztály.
 */
class PeriodicTimer {
	/**
	 * A több szálról való egyidejû hozzáférést kizáró adattag.
	 */
	std::recursive_mutex mutex;

	/**
	 * A mûveletek ismétlõdõ végrehajtását végzõ szál leállításakor
	 * használt kölcsönös kizárást biztosító adattag.
	 */
	std::recursive_mutex joinMutex;

	/**
	 * A mûveletek ismétlõdõ végrehajtását végzõ szál idõszakos
	 * felfüggesztéséhez használt állapotváltozó.
	 */
	std::condition_variable_any condition;

	/**
	 * Az ismétlõdõ végrehajtások közötti szüneteltetés idõtartama.
	 */
	long period;

	/**
	 * A mûveletek ismétlõdõ végrehajtását végzõ szál futásának
	 * állapota.
	 */
	std::atomic_bool active;

	/**
	 * A mûveletek ismétlõdõ végrehajtását végzõ szál kezelését
	 * biztosító adattag.
	 */
	std::thread timerThread;

	/**
	 * @brief Külön szálon futva azonos idõközönként meghívja a
	 * leszármaztatott oszályban megvalósított, virtuális
	 * periodicOperation metódust.
	 */
	void loop();

protected:
	/**
	 * @brief Az oszály alapértelmezett konstruktora.
	 */
	PeriodicTimer();
	
	/**
	 * @brief Az osztály másoló konstruktorának tiltása.
	 */
	PeriodicTimer(PeriodicTimer&) = delete;
	
	/**
	 * @brief Az osztály értékadó operátorának tiltása.
	 */
	PeriodicTimer& operator=(const PeriodicTimer&) = delete;
	
	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~PeriodicTimer();

	/**
	 * @brief Elindítja a mûveletek ismétlõdõ végrehajtását végzõ
	 * szálat.
	 */
	void start();

	/**
	 * @brief Leállítja a mûveletek ismétlõdõ végrehajtását végzõ
	 * szálat.
	 */
	void stop();

	/**
	 * @brief Beállítja az ismétlõdõ végrehajtások közötti szüneteltetés
	 * idõtartamát.
	 *
	 * @param _period A szüneteltetés idõtartama milliszekundumokban.
	 */
	void setPeriod(long _period);

	/**
	 * @brief Az idõszakosan ismétlõdõ mûvelet, amit a leszármaztatott
	 * osztálynak meg kell valósítania.
	 */
	virtual void periodicOperation() = 0;
};

#endif /* INC_PERIODICTIMER_H_ */