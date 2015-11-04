#include <lib/app/inc/core/PeriodicTimer.h>

/*
 * Külön szálon futva azonos idõközönként meghívja a leszármaztatott
 * oszályban megvalósított, virtuális periodicOperation metódust.
 */
void PeriodicTimer::loop() {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	while(active && period > 0) {
		if(condition.wait_for(lock, std::chrono::milliseconds(period)) == std::cv_status::timeout) {
			periodicOperation();
		}
	}
}

/*
 * Az oszály alapértelmezett konstruktora.
 */
PeriodicTimer::PeriodicTimer() : period(0), active(false) {}

/*
 * Az osztály virtuális destruktora.
 */
PeriodicTimer::~PeriodicTimer() {
	stop();
}

/*
 * Elindítja a mûveletek ismétlõdõ végrehajtását végzõ szálat.
 */
void PeriodicTimer::start() {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	if(period > 0) {
		active = true;
		timerThread = std::thread(&PeriodicTimer::loop, this);
	}
}

/*
 * Leállítja a mûveletek ismétlõdõ végrehajtását végzõ szálat.
 */
void PeriodicTimer::stop() {
	std::unique_lock<std::recursive_mutex> joinLock(joinMutex);
	{
		std::unique_lock<std::recursive_mutex> lock(mutex);
		
		/* A mûveletek ismétlõdõ végrehajtását végzõ szál
		deaktiválása és felébresztése a	várakozásból a megfelelõ
		leállás érdekében. */
		active = false;
		condition.notify_all();
	}

	/* A mûveletek ismétlõdõ végrehajtását végzõ szál leállásának
	kivárása. */
	if(timerThread.joinable())
		timerThread.join();
}

/*
 * Beállítja az ismétlõdõ végrehajtások közötti szüneteltetés
 * idõtartamát.
 */
void PeriodicTimer::setPeriod(long _period) {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	period = _period;
	condition.notify_all();
}
