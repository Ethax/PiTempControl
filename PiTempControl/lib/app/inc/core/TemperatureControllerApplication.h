#ifndef INC_TEMPERATURECONTROLLERAPPLICATION_H_
#define INC_TEMPERATURECONTROLLERAPPLICATION_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/MessageSender.h>
#include <lib/app/inc/core/State.h>

class RegulatorModule;
class SensorModule;
class ActuatorModule;
class DisplayModule;

class RegulatorInterface;
class SensorInterface;
class ActuatorInterface;
class DisplayInterface;

/**
 * @class TemperatureControllerApplication
 * @brief H�m�rs�kletszab�lyoz� alkalmaz�s.
 *
 * Ez az alkalmaz�s egy el�re be�ll�tott alapjelet pr�b�l min�l
 * jobban megk�zel�teni az el�re be�ll�tott p�lyak�vez�si hib�n
 * bel�l a ventil�tor �s a f�t�sz�l megfelel� m�k�dtet�s�vel.
 */
class TemperatureControllerApplication {
	/**
	 * Az alkalmaz�son bel�li adatforgalmat lebonyol�t� objektum.
	 */
	MessageSender sender;
	
	/**
	 * Az alkalmaz�s �llapotait t�rol� Singleton.
	 */
	State& appState;

	/**
	 * Az alkalmaz�s fut�s�nak �llapota.
	 */
	std::atomic_bool stopped;

	/**
	 * El�re fix�lt alapjel.
	 */
	const float setpoint;

	/**
	 * El�re fix�lt megengedett p�lyak�vet�si hiba.
	 */
	const float errorLimit;

	/**
	 * A szab�lyoz� modulra mutat� megosztott pointer.
	 */
	std::shared_ptr<RegulatorModule> regulatorModule;

	/**
	 * Az �rz�kel� modulra mutat� megosztott pointer.
	 */
	std::shared_ptr<SensorModule> sensorModule;

	/**
	 * A m�k�dtet� modulra mutat� megosztott pointer.
	 */
	std::shared_ptr<ActuatorModule> actuatorModule;

	/**
	 * A kijelz� modulra mutat� megosztott pointer.
	 */
	std::shared_ptr<DisplayModule> displayModule;

	/**
	 * @brief Az oszt�ly m�sol� konstruktor�nak tilt�sa.
	 */
	TemperatureControllerApplication(const TemperatureControllerApplication&) = delete;

	/**
	 * @brief Az oszt�ly �rt�kad� oper�tor�nak tilt�sa.
	 */
	TemperatureControllerApplication& operator=(const TemperatureControllerApplication&) = delete;
	
public:
	/**
	 * @brief Az oszt�ly konstruktora.
	 *
	 * @param regulator A konkr�t szab�lyoz� komponensre mutat�
	 * referencia.
	 * @param sensor A konkr�t �rz�kel� komponensre mutat� referencia.
	 * @param actuator A konkr�t m�k�dtet� komponensre mutat�
	 * referencia.
	 * @param display A konkr�t kijelz� komponensre mutat� referencia.
	 * @param _setpoint Az alapjel �rt�ke.
	 * @param _errorLimit A megengedett p�lyak�vet�si hiba �rt�ke.
	 */
	TemperatureControllerApplication(
		RegulatorInterface& regulator,
		SensorInterface& sensor,
		ActuatorInterface& actuator,
		DisplayInterface& display,
		const float _setpoint,
		const float _errorLimit
	);

	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~TemperatureControllerApplication();

	/**
	 * @brief Felveszi az �tadott fogad�t a feliratkozott fogad�k k�z�.
	 *
	 * @param receiver A felvenni k�v�nt fogad�.
	 */
	void registerMessageReceiver(MessageReceiver& receiver);

	/**
	 * @brief Elhelyezi az elk�ldeni k�v�nt �zenetet a v�rakoz�si sorba �s
	 * jelez az �zeneteket k�zbes�t� sz�lnak, hogy folytathatja a v�rakoz�si
	 * sorban lev� �zenetek k�zbes�t�s�t.
	 *
	 * @param message Az elk�ldeni k�v�nt �zenetre mutat� megosztott
	 * pointer.
	 */
	void sendMessage(std::shared_ptr<BaseMessage> message);

	/**
	 * @brief Hozz�f�rhet�v� teszi az alkalmaz�s �llapotait
	 * t�rol� objektumot.
	 *
	 * @return Az alkalmaz�s �llapotait t�rol� objektum.
	 */
	State& getState();

	/**
	 * @brief Elind�tja az alkalmaz�s �temezett m�k�d�s�t.
	 */
	void start();

	/**
	 * @brief Le�ll�tja a modul �temezett m�k�d�s�t.
	 */
	void stop();	
};

#endif /* INC_TEMPERATURECONTROLLERAPPLICATION_H_ */
