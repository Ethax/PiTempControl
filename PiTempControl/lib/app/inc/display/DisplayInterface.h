#ifndef INC_DISPLAYINTERFACE_H_
#define INC_DISPLAYINTERFACE_H_

#include <lib/app/inc/common.h>

/**
 * @class DisplayInterface
 * @brief A kijelzõ komponens interfésze.
 *
 * A kijelzõknek ebbõl az interfészbõl kell származniuk,
 * megvalósítva ennek minden egyes virtuális metódusát.
 */
class DisplayInterface {
public:
	/**
	 * @brief Az interfész alapértelmezett konstruktora.
	 */
	DisplayInterface() {}

	/**
	 * @brief Az intefész virtuális destruktora.
	 */
	virtual ~DisplayInterface() {}

	/**
	 * @brief Inicializálja a kijelzõ komponenst.
	 */
	virtual void initialize() = 0;

	/**
	 * @brief Frissíti a kijelzõn a mért hõmérsékletet.
	 *
	 * @param _temp A mért hõmérséklet értéke.
	 */
	virtual void refreshActualTemperature(const float _temp) = 0;

	/**
	 * @brief Frissíti a kijelzõn az alapjel értékét.
	 *
	 * @param _setpoint Az alapjel értéke.
	 */
	virtual void refreshSetpoint(const float _setpoint) = 0;

	/**
	 * @brief Frissíti a kijelzõn a megengedett pályakövetési hiba
	 * értékét.
	 *
	 * @param _errorLimit A megengedett pályakövetési hiba értéke.
	 */
	virtual void refreshErrorLimit(const float _errorLimit) = 0;

	/**
	 * @brief Frissíti a kijelzõn a ventilátor állapotát.
	 *
	 * @param _fan A ventilátor aktuális állapota.
	 */
	virtual void refreshFanControllingValue(const bool _fan) = 0;

	/**
	 * @brief Frissíti a kijelzõn a fûtõszál állapotát.
	 *
	 * @param _heater A fûtõszál aktuális állapota.
	 */
	virtual void refreshHeaterControllingValue(const bool _heater) = 0;
};

#endif /* INC_DISPLAYINTERFACE_H_ */