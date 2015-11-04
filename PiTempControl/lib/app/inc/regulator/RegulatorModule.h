#ifndef INC_REGULATORMODULE_H_
#define INC_REGULATORMODULE_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/PeriodicTimer.h>
#include <lib/app/inc/core/MessageReceiver.h>
#include <lib/app/inc/core/TemperatureControllerApplication.h>

class RegulatorInterface;
class TemperatureMessage;
class SetupMessage;

/**
 * @class RegulatorModule
 * @brief A szab�lyoz� modul.
 *
 * A szab�lyoz� komponens implement�ci�j�t�l f�gg�en l�trehozza �s
 * elk�ldi a megfelel� �zeneteket, amikkel a m�rt h�m�rs�klet k�zelebb
 * vihet� a be�ll�tott alapjelhez.
 */
class RegulatorModule : public MessageReceiver, PeriodicTimer {
	/**
	 * Az alkalmaz�sra mutat� referencia.
	 */
	TemperatureControllerApplication& application;

	/**
	 * A szab�lyoz� modulhoz tartoz� szab�lyoz� komponensre mutat�
	 * referencia.
	 */
	RegulatorInterface& componentInterface;

	/**
	 * @brief Az osz�ly alap�rtelmezett konstruktor�nak tilt�sa.
	 */
	RegulatorModule() = delete;

	/**
	 * @brief Az oszt�ly m�sol� konstruktor�nak tilt�sa.
	 */
	RegulatorModule(const RegulatorModule&) = delete;

	/**
	 * @brief Az oszt�ly �rt�kad� oper�tor�nak tilt�sa.
	 */
	RegulatorModule& operator=(const RegulatorModule&) = delete;

public:
	/**
	 * @brief Az oszt�ly konstruktora.
	 *
	 * @param app A modult mag�ba foglal� alkalmaz�sra mutat� referencia.
	 * @param component A modul �ltal felhaszn�lt konkr�t komponensre
	 * mutat� referencia.
	 */
	RegulatorModule(TemperatureControllerApplication& app, RegulatorInterface& component);
	
	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~RegulatorModule();

	/**
	 * @brief Elind�tja a modul �temezett m�k�d�s�t.
	 */
	void start();

	/**
	 * @brief Le�ll�tja a modul �temezett m�k�d�s�t.
	 */
	void stop();

	/**
	 * @brief Fogadja �s feldolgozza a h�m�rs�klet t�pus� �zeneteket.
	 *
	 * A h�m�rs�klet t�pus� �zenetek feldolgoz�s�t k�vet�en szab�lyoz�s
	 * t�pus� �zenetet k�ld, ha az aktu�lis h�m�rs�klet beavatkoz�st
	 * k�vetel.
	 *
	 * @param msg Az �zenetre mutat� referencia.
	 */
	virtual void receiveMessage(const TemperatureMessage& msg);

	/**
	 * @brief Fogadja �s feldolgozza a be�ll�t�s t�pus� �zeneteket.
	 *
	 * A be�ll�t�sokat �tadja a modul �ltal felhaszn�lt konkr�t komponensnek,
	 * ami innent�l kezdve az �j �rt�keknek megfelel�en adja vissza a
	 * beavatkoz� jeleketek.
	 *
	 * @param msg Az �zenetre mutat� referencia.
	 */
	virtual void receiveMessage(const SetupMessage& msg);

private:
	/**
	 * @brief Az id�szakosan ism�tl�d� m�velet, ami enn�l a moduln�l
	 * nem v�gez semmilyen m�veletet sem.
	 */
	virtual void periodicOperation() {}
};

#endif /* INC_REGULATORMODULE_H_ */