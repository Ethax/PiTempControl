#ifndef INC_STATE_H_
#define INC_STATE_H_

#include <lib/app/inc/common.h>

/**
 * @class State
 * @brief Az alkalmaz�s bels� �llapotait t�rol� singleton oszt�ly.
 */
class State {
	/**
	 * A h�m�rs�klet aktu�lis �rt�ke.
	 */
	float ACTUAL_TEMPERATURE;

	/**
	 * A ventil�tor �llapota.
	 */
	bool FAN_STATE;

	/**
	 * A f�t�sz�l �llapota.
	 */
	bool HEATER_STATE;
	
	/**
	 * Az utolj�ra be�ll�tott alapjel.
	 */
	float SETPOINT;

	/**
	* A t�bb sz�lr�l val� egyidej� hozz�f�r�st kiz�r� adattag.
	*/
	std::recursive_mutex mutex;

public:
	/**
	 * @brief Visszaadja a State oszt�ly egyetlen p�ld�ny�t.
	 *
	 * @return Az egyetlen State t�pus� objektum.
	 */
	static State& getInstance() {
		static State instance;
		return instance;
	}

	/**
	 * @brief Be�ll�tja a h�m�rs�klet aktu�lis �rt�k�t. 
	 *
	 * @param _temperature A be�ll�tani k�v�nt �rt�k.
	 */
	void setActualTemperature(float _temperature) {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		ACTUAL_TEMPERATURE = _temperature;
	}

	/**
	 * @brief Lek�rdezi a h�m�rs�klet aktu�lis �rt�k�t.
	 *
	 * @return A lek�rdezett �rt�k.
	 */
	float getActualTemperature() {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		return ACTUAL_TEMPERATURE;
	}

	/**
	 * @brief Be�ll�tja a ventil�tor �llapot�t.
	 *
	 * @param _state A be�ll�tani k�v�nt �llapot.
	 */
	void setFanState(bool _state) {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		FAN_STATE = _state;
	}

	/**
	 * @brief Lek�rdezi a ventil�tor �llapot�t.
	 *
	 * @return A lek�rdezett �llapot.
	 */
	bool getFanState() {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		return FAN_STATE;
	}

	/**
	 * @brief Be�ll�tja a f�t�sz�l �llapot�t.
	 *
	 * @param _state A be�ll�tani k�v�nt �llapot.
	 */
	void setHeaterState(bool _state) {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		HEATER_STATE = _state;
	}

	/**
	 * @brief Lek�rdezi a f�t�sz�l �llapot�t.
	 *
	 * @return A lek�rdezett �llapot.
	 */
	bool getHeaterState() {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		return HEATER_STATE;
	}

	/**
	 * @brief Be�ll�tja az alapjel �rt�k�t.
	 *
	 * @param _value A be�ll�tani k�v�nt �rt�k.
	 */
	void setSetpoint(float _value) {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		SETPOINT = _value;
	}

	/**
	 * @brief Lek�rdezi az alapjel �rt�k�t.
	 *
	 * @return A lek�rdezett �rt�k.
	 */
	float getSetpoint() {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		return SETPOINT;
	}

private:
	/**
	 * @brief Az osz�ly alap�rtelmezett konstruktora.
	 */
	State() : ACTUAL_TEMPERATURE(0.0f), FAN_STATE(false), HEATER_STATE(false), SETPOINT(0.0f) {}

	/**
	 * @brief Az oszt�ly m�sol� konstruktor�nak tilt�sa.
	 */
	State(State const&) = delete;

	/**
	 * @brief Az oszt�ly �rt�kad� oper�tor�nak tilt�sa.
	 */
	State& operator=(State const&) = delete;
};

#endif /* INC_STATE_H_ */