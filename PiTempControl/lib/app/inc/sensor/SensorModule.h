#ifndef INC_SENSORMODULE_H_
#define INC_SENSORMODULE_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/PeriodicTimer.h>
#include <lib/app/inc/core/MessageReceiver.h>
#include <lib/app/inc/core/TemperatureControllerApplication.h>

class SensorInterface;

/**
 * @class SensorModule
 * @brief Az �rz�kel� modul.
 *
 * Az �rz�kel� komponens implement�ci�j�t�l f�gg�en �rz�keli a
 * szab�lyozott helyis�g h�m�rs�klet�t �s azonos id�k�z�nk�nt �zenetet
 * k�ld az �rz�kel�s eredm�ny�vel.
 */
class SensorModule : public MessageReceiver, PeriodicTimer {
	/**
	 * Az alkalmaz�sra mutat� referencia.
	 */
	TemperatureControllerApplication& application;

	/**
	 * Az �rz�kel� modulhoz tartoz� �rz�kel� komponensre mutat�
	 * referencia.
	 */
	SensorInterface& componentInterface;

	/**
	 * @brief Az osz�ly alap�rtelmezett konstruktor�nak tilt�sa.
	 */
	SensorModule() = delete;

	/**
	 * @brief Az oszt�ly m�sol� konstruktor�nak tilt�sa.
	 */
	SensorModule(const SensorModule&) = delete;

	/**
	 * @brief Az oszt�ly �rt�kad� oper�tor�nak tilt�sa.
	 */
	SensorModule& operator=(const SensorModule&) = delete;

public:
	/**
	 * @brief Az oszt�ly konstruktora.
	 *
	 * @param app A modult mag�ba foglal� alkalmaz�sra mutat� referencia.
	 * @param component A modul �ltal felhaszn�lt konkr�t komponensre
	 * mutat� referencia.
	 */
	SensorModule(TemperatureControllerApplication& app, SensorInterface& component);

	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~SensorModule();

	/**
	 * @brief Elind�tja a modul �temezett m�k�d�s�t.
	 */
	void start();

	/**
	 * @brief Le�ll�tja a modul �temezett m�k�d�s�t.
	 */
	void stop();

private:
	/**
	 * @brief Az id�szakosan ism�tl�d� m�velet, amivel a modul lek�rdezi
	 * a konkr�t komponenst�l az aktu�lis h�m�rs�kletet �s �zenetet k�ld
	 * a kapott v�lasszal.
	 */
	virtual void periodicOperation();
};

#endif /* INC_SENSORMODULE_H_ */