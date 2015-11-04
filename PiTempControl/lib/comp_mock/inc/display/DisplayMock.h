#ifndef INC_DISPLAYMOCK_H_
#define INC_DISPLAYMOCK_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/display/DisplayInterface.h>

/**
 * @class DisplayMock
 * @brief A kijelzõ komponens mûködését utánzó osztály.
 *
 * Ez az osztály tesztelési feladatok ellátására szolgál, a kijelzõ
 * viselkedését elõre meghatározott módon utánozza.
 */
class DisplayMock : public DisplayInterface {
	std::string setpointIndicator;
	std::string heaterIndicator;
	std::string fanIndicator;
	std::string temperatureIndicator;

	/**
	 * @brief Összeállítja a kiírni kívánt sort és elvégzi a
	 * kiíratást a konzol képernyõre.
	 */
	void refreshDisplay(void);

public:
	/**
	 * @brief Az utánzat alapértelmezett konstruktora.
	 */
	DisplayMock();
	
	/**
	 * @brief Az utánzat virtuális destruktora.
	 */
	virtual ~DisplayMock();

	/**
	 * @brief Jelzést ad az inicializáló metódus meghívásáról.
	 */
	virtual void initialize();

	/**
	 * @brief Kiírja a konzol képernyõre a mért hõmérsékletet.
	 *
	 * @param _temp A mért hõmérséklet értéke.
	 */
	virtual void refreshActualTemperature(const float _temp);

	/**
	 * @brief Kiírja a konzol képernyõre az alapjel értékét.
	 *
	 * @param _setpoint Az alapjel értéke.
	 */
	virtual void refreshSetpoint(const float _setpoint);

	/**
	 * @brief Kiírja a konzol képernyõre a megengedett pályakövetési
	 * hiba értékét.
	 *
	 * @param _errorLimit A megengedett pályakövetési hiba értéke.
	 */
	virtual void refreshErrorLimit(const float _errorLimit);

	/**
	 * @brief Kiírja a konzol képernyõre a ventilátor állapotát.
	 *
	 * @param _fan A ventilátor aktuális állapota.
	 */
	virtual void refreshFanControllingValue(const bool _fan);

	/**
	 * @brief Kiírja a konzol képernyõre a fûtõszál állapotát.
	 *
	 * @param _heater A fûtõszál aktuális állapota.
	 */
	virtual void refreshHeaterControllingValue(const bool _heater);
};

#endif /* INC_DISPLAYMOCK_H_ */