#include <lib/app/inc/core/PeriodicTimer.h>

/*
 * K�l�n sz�lon futva azonos id�k�z�nk�nt megh�vja a lesz�rmaztatott
 * osz�lyban megval�s�tott, virtu�lis periodicOperation met�dust.
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
 * Az osz�ly alap�rtelmezett konstruktora.
 */
PeriodicTimer::PeriodicTimer() : period(0), active(false) {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
PeriodicTimer::~PeriodicTimer() {
	stop();
}

/*
 * Elind�tja a m�veletek ism�tl�d� v�grehajt�s�t v�gz� sz�lat.
 */
void PeriodicTimer::start() {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	if(period > 0) {
		active = true;
		timerThread = std::thread(&PeriodicTimer::loop, this);
	}
}

/*
 * Le�ll�tja a m�veletek ism�tl�d� v�grehajt�s�t v�gz� sz�lat.
 */
void PeriodicTimer::stop() {
	std::unique_lock<std::recursive_mutex> joinLock(joinMutex);
	{
		std::unique_lock<std::recursive_mutex> lock(mutex);
		
		/* A m�veletek ism�tl�d� v�grehajt�s�t v�gz� sz�l
		deaktiv�l�sa �s fel�breszt�se a	v�rakoz�sb�l a megfelel�
		le�ll�s �rdek�ben. */
		active = false;
		condition.notify_all();
	}

	/* A m�veletek ism�tl�d� v�grehajt�s�t v�gz� sz�l le�ll�s�nak
	kiv�r�sa. */
	if(timerThread.joinable())
		timerThread.join();
}

/*
 * Be�ll�tja az ism�tl�d� v�grehajt�sok k�z�tti sz�neteltet�s
 * id�tartam�t.
 */
void PeriodicTimer::setPeriod(long _period) {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	period = _period;
	condition.notify_all();
}
