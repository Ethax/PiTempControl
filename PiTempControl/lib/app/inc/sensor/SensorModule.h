#ifndef INC_SENSORMODULE_H_
#define INC_SENSORMODULE_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/PeriodicTimer.h>
#include <lib/app/inc/core/MessageReceiver.h>
#include <lib/app/inc/core/TemperatureControllerApplication.h>

class SensorInterface;

/**
 * @class SensorModule
 * @brief Az érzékelõ modul.
 *
 * Az érzékelõ komponens implementációjától függõen érzékeli a
 * szabályozott helyiség hõmérsékletét és azonos idõközönként üzenetet
 * küld az érzékelés eredményével.
 */
class SensorModule : public MessageReceiver, PeriodicTimer {
	/**
	 * Az alkalmazásra mutató referencia.
	 */
	TemperatureControllerApplication& application;

	/**
	 * Az érzékelõ modulhoz tartozó érzékelõ komponensre mutató
	 * referencia.
	 */
	SensorInterface& componentInterface;

	/**
	 * @brief Az oszály alapértelmezett konstruktorának tiltása.
	 */
	SensorModule() = delete;

	/**
	 * @brief Az osztály másoló konstruktorának tiltása.
	 */
	SensorModule(const SensorModule&) = delete;

	/**
	 * @brief Az osztály értékadó operátorának tiltása.
	 */
	SensorModule& operator=(const SensorModule&) = delete;

public:
	/**
	 * @brief Az osztály konstruktora.
	 *
	 * @param app A modult magába foglaló alkalmazásra mutató referencia.
	 * @param component A modul által felhasznált konkrét komponensre
	 * mutató referencia.
	 */
	SensorModule(TemperatureControllerApplication& app, SensorInterface& component);

	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~SensorModule();

	/**
	 * @brief Elindítja a modul ütemezett mûködését.
	 */
	void start();

	/**
	 * @brief Leállítja a modul ütemezett mûködését.
	 */
	void stop();

private:
	/**
	 * @brief Az idõszakosan ismétlõdõ mûvelet, amivel a modul lekérdezi
	 * a konkrét komponenstõl az aktuális hõmérsékletet és üzenetet küld
	 * a kapott válasszal.
	 */
	virtual void periodicOperation();
};

#endif /* INC_SENSORMODULE_H_ */