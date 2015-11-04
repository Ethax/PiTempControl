#ifndef INC_STATE_H_
#define INC_STATE_H_

#include <lib/app/inc/common.h>

/**
 * @class State
 * @brief Az alkalmazás belsõ állapotait tároló singleton osztály.
 */
class State {
	/**
	 * A hõmérséklet aktuális értéke.
	 */
	float ACTUAL_TEMPERATURE;

	/**
	 * A ventilátor állapota.
	 */
	bool FAN_STATE;

	/**
	 * A fûtõszál állapota.
	 */
	bool HEATER_STATE;
	
	/**
	 * Az utoljára beállított alapjel.
	 */
	float SETPOINT;

	/**
	* A több szálról való egyidejû hozzáférést kizáró adattag.
	*/
	std::recursive_mutex mutex;

public:
	/**
	 * @brief Visszaadja a State osztály egyetlen példányát.
	 *
	 * @return Az egyetlen State típusú objektum.
	 */
	static State& getInstance() {
		static State instance;
		return instance;
	}

	/**
	 * @brief Beállítja a hõmérséklet aktuális értékét. 
	 *
	 * @param _temperature A beállítani kívánt érték.
	 */
	void setActualTemperature(float _temperature) {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		ACTUAL_TEMPERATURE = _temperature;
	}

	/**
	 * @brief Lekérdezi a hõmérséklet aktuális értékét.
	 *
	 * @return A lekérdezett érték.
	 */
	float getActualTemperature() {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		return ACTUAL_TEMPERATURE;
	}

	/**
	 * @brief Beállítja a ventilátor állapotát.
	 *
	 * @param _state A beállítani kívánt állapot.
	 */
	void setFanState(bool _state) {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		FAN_STATE = _state;
	}

	/**
	 * @brief Lekérdezi a ventilátor állapotát.
	 *
	 * @return A lekérdezett állapot.
	 */
	bool getFanState() {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		return FAN_STATE;
	}

	/**
	 * @brief Beállítja a fûtõszál állapotát.
	 *
	 * @param _state A beállítani kívánt állapot.
	 */
	void setHeaterState(bool _state) {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		HEATER_STATE = _state;
	}

	/**
	 * @brief Lekérdezi a fûtõszál állapotát.
	 *
	 * @return A lekérdezett állapot.
	 */
	bool getHeaterState() {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		return HEATER_STATE;
	}

	/**
	 * @brief Beállítja az alapjel értékét.
	 *
	 * @param _value A beállítani kívánt érték.
	 */
	void setSetpoint(float _value) {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		SETPOINT = _value;
	}

	/**
	 * @brief Lekérdezi az alapjel értékét.
	 *
	 * @return A lekérdezett érték.
	 */
	float getSetpoint() {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		return SETPOINT;
	}

private:
	/**
	 * @brief Az oszály alapértelmezett konstruktora.
	 */
	State() : ACTUAL_TEMPERATURE(0.0f), FAN_STATE(false), HEATER_STATE(false), SETPOINT(0.0f) {}

	/**
	 * @brief Az osztály másoló konstruktorának tiltása.
	 */
	State(State const&) = delete;

	/**
	 * @brief Az osztály értékadó operátorának tiltása.
	 */
	State& operator=(State const&) = delete;
};

#endif /* INC_STATE_H_ */