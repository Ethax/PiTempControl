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
 * @brief A mûködtetõ modul.
 *
 * A mûködtetõ komponens implementációjától és a beavatkozó jeltõl
 * függõen kikapcsolja vagy bekapcsolja a ventilátort és a
 * fûtõszálat.
 */
class ActuatorModule : public MessageReceiver, PeriodicTimer {
	/**
	 * Az alkalmazásra mutató referencia.
	 */
	TemperatureControllerApplication& application;

	/**
	 * A mûködtetõ modulhoz tartozó mûködtetõ komponensre mutató
	 * referencia.
	 */
	ActuatorInterface& componentInterface;

	/**
	 * @brief Az oszály alapértelmezett konstruktorának tiltása.
	 */
	ActuatorModule() = delete;

	/**
	 * @brief Az osztály másoló konstruktorának tiltása.
	 */
	ActuatorModule(const ActuatorModule&) = delete;

	/**
	 * @brief Az osztály értékadó operátorának tiltása.
	 */
	ActuatorModule& operator=(const ActuatorModule&) = delete;

public:
	/**
	 * @brief Az osztály konstruktora.
	 *
	 * @param app A modult magába foglaló alkalmazásra mutató referencia.
	 * @param component A modul által felhasznált konkrét komponensre
	 * mutató referencia.
	 */
	ActuatorModule(TemperatureControllerApplication& app, ActuatorInterface& component);

	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~ActuatorModule();

	/**
	 * @brief Elindítja a modul ütemezett mûködését.
	 */
	void start();

	/**
	 * @brief Leállítja a modul ütemezett mûködését.
	 */
	void stop();

	/**
	 * @brief Fogadja és feldolgozza a vezérlés típusú üzeneteket.
	 *
	 * A vezérlés típusú üzenetbõl kinyeri a beavatkozó jelet és
	 * elvégzi a beavatkozást.
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

#endif /* INC_ACTUATORMODULE_H_ */