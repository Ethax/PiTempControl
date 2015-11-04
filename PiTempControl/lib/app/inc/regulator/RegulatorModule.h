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
 * @brief A szabályozó modul.
 *
 * A szabályozó komponens implementációjától függõen létrehozza és
 * elküldi a megfelelõ üzeneteket, amikkel a mért hõmérséklet közelebb
 * vihetõ a beállított alapjelhez.
 */
class RegulatorModule : public MessageReceiver, PeriodicTimer {
	/**
	 * Az alkalmazásra mutató referencia.
	 */
	TemperatureControllerApplication& application;

	/**
	 * A szabályozó modulhoz tartozó szabályozó komponensre mutató
	 * referencia.
	 */
	RegulatorInterface& componentInterface;

	/**
	 * @brief Az oszály alapértelmezett konstruktorának tiltása.
	 */
	RegulatorModule() = delete;

	/**
	 * @brief Az osztály másoló konstruktorának tiltása.
	 */
	RegulatorModule(const RegulatorModule&) = delete;

	/**
	 * @brief Az osztály értékadó operátorának tiltása.
	 */
	RegulatorModule& operator=(const RegulatorModule&) = delete;

public:
	/**
	 * @brief Az osztály konstruktora.
	 *
	 * @param app A modult magába foglaló alkalmazásra mutató referencia.
	 * @param component A modul által felhasznált konkrét komponensre
	 * mutató referencia.
	 */
	RegulatorModule(TemperatureControllerApplication& app, RegulatorInterface& component);
	
	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~RegulatorModule();

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
	 * A hõmérséklet típusú üzenetek feldolgozását követõen szabályozás
	 * típusú üzenetet küld, ha az aktuális hõmérséklet beavatkozást
	 * követel.
	 *
	 * @param msg Az üzenetre mutató referencia.
	 */
	virtual void receiveMessage(const TemperatureMessage& msg);

	/**
	 * @brief Fogadja és feldolgozza a beállítás típusú üzeneteket.
	 *
	 * A beállításokat átadja a modul által felhasznált konkrét komponensnek,
	 * ami innentõl kezdve az új értékeknek megfelelõen adja vissza a
	 * beavatkozó jeleketek.
	 *
	 * @param msg Az üzenetre mutató referencia.
	 */
	virtual void receiveMessage(const SetupMessage& msg);

private:
	/**
	 * @brief Az idõszakosan ismétlõdõ mûvelet, ami ennél a modulnál
	 * nem végez semmilyen mûveletet sem.
	 */
	virtual void periodicOperation() {}
};

#endif /* INC_REGULATORMODULE_H_ */