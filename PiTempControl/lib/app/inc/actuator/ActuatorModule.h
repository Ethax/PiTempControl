#ifndef INC_ACTUATORMODULE_H_
#define INC_ACTUATORMODULE_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/PeriodicTimer.h>
#include <lib/app/inc/core/MessageReceiver.h>
#include <lib/app/inc/core/TemperatureControllerApplication.h>

class ActuatorInterface;
class ControlMessage;

/**
 * @class ActuatorModule
 * @brief A m�k�dtet� modul.
 *
 * A m�k�dtet� komponens implement�ci�j�t�l �s a beavatkoz� jelt�l
 * f�gg�en kikapcsolja vagy bekapcsolja a ventil�tort �s a
 * f�t�sz�lat.
 */
class ActuatorModule : public MessageReceiver, PeriodicTimer {
	/**
	 * Az alkalmaz�sra mutat� referencia.
	 */
	TemperatureControllerApplication& application;

	/**
	 * A m�k�dtet� modulhoz tartoz� m�k�dtet� komponensre mutat�
	 * referencia.
	 */
	ActuatorInterface& componentInterface;

	/**
	 * @brief Az osz�ly alap�rtelmezett konstruktor�nak tilt�sa.
	 */
	ActuatorModule() = delete;

	/**
	 * @brief Az oszt�ly m�sol� konstruktor�nak tilt�sa.
	 */
	ActuatorModule(const ActuatorModule&) = delete;

	/**
	 * @brief Az oszt�ly �rt�kad� oper�tor�nak tilt�sa.
	 */
	ActuatorModule& operator=(const ActuatorModule&) = delete;

public:
	/**
	 * @brief Az oszt�ly konstruktora.
	 *
	 * @param app A modult mag�ba foglal� alkalmaz�sra mutat� referencia.
	 * @param component A modul �ltal felhaszn�lt konkr�t komponensre
	 * mutat� referencia.
	 */
	ActuatorModule(TemperatureControllerApplication& app, ActuatorInterface& component);

	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~ActuatorModule();

	/**
	 * @brief Elind�tja a modul �temezett m�k�d�s�t.
	 */
	void start();

	/**
	 * @brief Le�ll�tja a modul �temezett m�k�d�s�t.
	 */
	void stop();

	/**
	 * @brief Fogadja �s feldolgozza a vez�rl�s t�pus� �zeneteket.
	 *
	 * A vez�rl�s t�pus� �zenetb�l kinyeri a beavatkoz� jelet �s
	 * elv�gzi a beavatkoz�st.
	 *
	 * @param msg Az �zenetre mutat� referencia.
	 */
	virtual void receiveMessage(const ControlMessage& msg);

private:
	/**
	 * @brief Az id�szakosan ism�tl�d� m�velet, ami enn�l a moduln�l
	 * nem v�gez semmilyen m�veletet sem.
	 */
	virtual void periodicOperation() {}
};

#endif /* INC_ACTUATORMODULE_H_ */