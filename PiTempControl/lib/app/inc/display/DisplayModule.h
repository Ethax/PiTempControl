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
 * @brief A kijelzõ modul.
 *
 * Fogadja az összes üzenettípust és a kijelzõ komponens
 * implementációjától függõen megjeleníti a megjelenítõ eszközön
 * az alkalmazásban forgalmazott adatokat.
 */
class DisplayModule : public MessageReceiver, PeriodicTimer {
	/**
	 * Az alkalmazásra mutató referencia.
	 */
	TemperatureControllerApplication& application;

	/**
	 * A kijelzõ modulhoz tartozó kijelzõ komponensre mutató
	 * referencia.
	 */
	DisplayInterface& componentInterface;

	/**
	 * @brief Az oszály alapértelmezett konstruktorának tiltása.
	 */
	DisplayModule() = delete;

	/**
	 * @brief Az osztály másoló konstruktorának tiltása.
	 */
	DisplayModule(const DisplayModule&) = delete;

	/**
	 * @brief Az osztály értékadó operátorának tiltása.
	 */
	DisplayModule& operator=(const DisplayModule&) = delete;

public:
	/**
	 * @brief Az osztály konstruktora.
	 *
	 * @param app A modult magába foglaló alkalmazásra mutató referencia.
	 * @param component A modul által felhasznált konkrét komponensre
	 * mutató referencia.
	 */
	DisplayModule(TemperatureControllerApplication& app, DisplayInterface& component);
	
	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~DisplayModule();

	/**
	 * @brief Elindítja a modul ütemezett mûködését.
	 */
	void start();

	/**
	 * @brief Leállítja a modul ütemezett mûködését.
	 */
	void stop();

	/**
	 * @brief Fogadja és feldolgozza a hõmérséklet típusú üzeneteket.
	 *
	 * A hõmérséklet típusú üzenetekbõl kinyeri a hõmérséklet értéket,
	 * amit a konkrét komponensen keresztül megjelenít a felhasználó
	 * számára.
	 *
	 * @param msg Az üzenetre mutató referencia.
	 */
	virtual void receiveMessage(const TemperatureMessage& msg);

	/**
	* @brief Fogadja és feldolgozza a beállítás típusú üzeneteket.
	*
	* A beállítás típusú üzenetekbõl kinyeri a beállítások fajtáját és
	* azok értékét, amiket a konkrét komponenstõl függõen igény szerint
	* megjeleníthet a felhasználó számára.
	*
	* @param msg Az üzenetre mutató referencia.
	*/
	virtual void receiveMessage(const SetupMessage& msg);

	/**
	 * @brief Fogadja és feldolgozza a vezérlés típusú üzeneteket.
	 *
	 * A vezérlés típusú üzenetekbõl kinyeri a beavatkozó jeleket,
	 * amiket a konkrét komponenstõl függõen igény szerint megjeleníthet
	 * a felhasználó számára.
	 *
	 * @param msg Az üzenetre mutató referencia.
	 */
	virtual void receiveMessage(const ControlMessage& msg);

private:
	/**
	* @brief Az idõszakosan ismétlõdõ mûvelet, ami ennél a modulnál
	* nem végez semmilyen mûveletet sem.
	*/
	virtual void periodicOperation() {}
};

#endif /* INC_DISPLAYMODULE_H_ */