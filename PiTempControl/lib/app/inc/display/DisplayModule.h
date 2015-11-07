#ifndef INC_DISPLAYMODULE_H_
#define INC_DISPLAYMODULE_H_
#include <lib/app/inc/common.h>
#include <lib/app/inc/core/PeriodicTimer.h>
#include <lib/app/inc/core/MessageReceiver.h>
#include <lib/app/inc/core/TemperatureControllerApplication.h>

class DisplayInterface;
class TemperatureMessage;
class SetupMessage;
class ControlMessage;

/**
 * @class DisplayModule
 * @brief A kijelz� modul.
 *
 * Fogadja az �sszes �zenett�pust �s a kijelz� komponens
 * implement�ci�j�t�l f�gg�en megjelen�ti a megjelen�t� eszk�z�n
 * az alkalmaz�sban forgalmazott adatokat.
 */
class DisplayModule : public MessageReceiver, PeriodicTimer {
	/**
	 * Az alkalmaz�sra mutat� referencia.
	 */
	TemperatureControllerApplication& application;

	/**
	 * A kijelz� modulhoz tartoz� kijelz� komponensre mutat�
	 * referencia.
	 */
	DisplayInterface& componentInterface;

	/**
	 * @brief Az osz�ly alap�rtelmezett konstruktor�nak tilt�sa.
	 */
	DisplayModule() = delete;

	/**
	 * @brief Az oszt�ly m�sol� konstruktor�nak tilt�sa.
	 */
	DisplayModule(const DisplayModule&) = delete;

	/**
	 * @brief Az oszt�ly �rt�kad� oper�tor�nak tilt�sa.
	 */
	DisplayModule& operator=(const DisplayModule&) = delete;

public:
	/**
	 * @brief Az oszt�ly konstruktora.
	 *
	 * @param app A modult mag�ba foglal� alkalmaz�sra mutat� referencia.
	 * @param component A modul �ltal felhaszn�lt konkr�t komponensre
	 * mutat� referencia.
	 */
	DisplayModule(TemperatureControllerApplication& app, DisplayInterface& component);
	
	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~DisplayModule();

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
	 * A h�m�rs�klet t�pus� �zenetekb�l kinyeri a h�m�rs�klet �rt�ket,
	 * amit a konkr�t komponensen kereszt�l megjelen�t a felhaszn�l�
	 * sz�m�ra.
	 *
	 * @param msg Az �zenetre mutat� referencia.
	 */
	virtual void receiveMessage(const TemperatureMessage& msg);

	/**
	* @brief Fogadja �s feldolgozza a be�ll�t�s t�pus� �zeneteket.
	*
	* A be�ll�t�s t�pus� �zenetekb�l kinyeri a be�ll�t�sok fajt�j�t �s
	* azok �rt�k�t, amiket a konkr�t komponenst�l f�gg�en ig�ny szerint
	* megjelen�thet a felhaszn�l� sz�m�ra.
	*
	* @param msg Az �zenetre mutat� referencia.
	*/
	virtual void receiveMessage(const SetupMessage& msg);

	/**
	 * @brief Fogadja �s feldolgozza a vez�rl�s t�pus� �zeneteket.
	 *
	 * A vez�rl�s t�pus� �zenetekb�l kinyeri a beavatkoz� jeleket,
	 * amiket a konkr�t komponenst�l f�gg�en ig�ny szerint megjelen�thet
	 * a felhaszn�l� sz�m�ra.
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

#endif /* INC_DISPLAYMODULE_H_ */