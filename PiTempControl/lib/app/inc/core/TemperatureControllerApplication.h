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
 * @brief Hõmérsékletszabályozó alkalmazás.
 *
 * Ez az alkalmazás egy elõre beállított alapjelet próbál minél
 * jobban megközelíteni az elõre beállított pályakövezési hibán
 * belül a ventilátor és a fûtöszál megfelelõ mûködtetésével.
 */
class TemperatureControllerApplication {
	/**
	 * Az alkalmazáson belüli adatforgalmat lebonyolító objektum.
	 */
	MessageSender sender;
	
	/**
	 * Az alkalmazás állapotait tároló Singleton.
	 */
	State& appState;

	/**
	 * Az alkalmazás futásának állapota.
	 */
	std::atomic_bool stopped;

	/**
	 * Elõre fixált alapjel.
	 */
	const float setpoint;

	/**
	 * Elõre fixált megengedett pályakövetési hiba.
	 */
	const float errorLimit;

	/**
	 * A szabályozó modulra mutató megosztott pointer.
	 */
	std::shared_ptr<RegulatorModule> regulatorModule;

	/**
	 * Az érzékelõ modulra mutató megosztott pointer.
	 */
	std::shared_ptr<SensorModule> sensorModule;

	/**
	 * A mûködtetõ modulra mutató megosztott pointer.
	 */
	std::shared_ptr<ActuatorModule> actuatorModule;

	/**
	 * A kijelzõ modulra mutató megosztott pointer.
	 */
	std::shared_ptr<DisplayModule> displayModule;

	/**
	 * @brief Az osztály másoló konstruktorának tiltása.
	 */
	TemperatureControllerApplication(const TemperatureControllerApplication&) = delete;

	/**
	 * @brief Az osztály értékadó operátorának tiltása.
	 */
	TemperatureControllerApplication& operator=(const TemperatureControllerApplication&) = delete;
	
public:
	/**
	 * @brief Az osztály konstruktora.
	 *
	 * @param regulator A konkrét szabályozó komponensre mutató
	 * referencia.
	 * @param sensor A konkrét érzékelõ komponensre mutató referencia.
	 * @param actuator A konkrét mûködtetõ komponensre mutató
	 * referencia.
	 * @param display A konkrét kijelzõ komponensre mutató referencia.
	 * @param _setpoint Az alapjel értéke.
	 * @param _errorLimit A megengedett pályakövetési hiba értéke.
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
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~TemperatureControllerApplication();

	/**
	 * @brief Felveszi az átadott fogadót a feliratkozott fogadók közé.
	 *
	 * @param receiver A felvenni kívánt fogadó.
	 */
	void registerMessageReceiver(MessageReceiver& receiver);

	/**
	 * @brief Elhelyezi az elküldeni kívánt üzenetet a várakozási sorba és
	 * jelez az üzeneteket kézbesítõ szálnak, hogy folytathatja a várakozási
	 * sorban levõ üzenetek kézbesítését.
	 *
	 * @param message Az elküldeni kívánt üzenetre mutató megosztott
	 * pointer.
	 */
	void sendMessage(std::shared_ptr<BaseMessage> message);

	/**
	 * @brief Hozzáférhetõvé teszi az alkalmazás állapotait
	 * tároló objektumot.
	 *
	 * @return Az alkalmazás állapotait tároló objektum.
	 */
	State& getState();

	/**
	 * @brief Elindítja az alkalmazás ütemezett mûködését.
	 */
	void start();

	/**
	 * @brief Leállítja a modul ütemezett mûködését.
	 */
	void stop();	
};

#endif /* INC_TEMPERATURECONTROLLERAPPLICATION_H_ */
