#ifndef INC_DISPLAYMOCK_H_
#define INC_DISPLAYMOCK_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/display/DisplayInterface.h>

#define cret '\r'

/**
 * @class DisplayMock
 * @brief A kijelzõ komponens mûködését utánzó osztály.
 *
 * Ez az osztály tesztelési feladatok ellátására szolgál, a kijelzõ
 * viselkedését elõre meghatározott módon utánozza.
 */
class DisplayMock : public DisplayInterface {
	/**
	 * Az alapjelre vonatkozó információt megjelenítõ címke puffere.
	 */
	std::string setpointIndicator;

	/**
	 * A fûtõszálra vonatkozó információt megjelenítõ címke puffere.
	 */
	std::string heaterIndicator;
	
	/**
	 * Az ventilárra vonatkozó információt megjelenítõ címke puffere.
	 */
	std::string fanIndicator;

	/**
	 * Az hõmérsékletre vonatkozó információt megjelenítõ címke puffere.
	 */
	std::string temperatureIndicator;

	/**
	 * @brief Összeállítja a kiírni kívánt sort a címkékbõl és
	 * elvégzi a kiíratást a konzol képernyõre.
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
	 * @brief Nem végez semmilyen mûveletet sem.
	 */
	virtual void initialize();

	/**
	 * @brief Frissíti a hõmérséklet-címke tartalmát, ezt követõen
	 * pedig a konzol képernyõ tartalmát.
	 *
	 * @param _temp A mért hõmérséklet értéke.
	 */
	virtual void refreshActualTemperature(const float _temp);

	/**
	 * @brief Frissíti az alapjel-címke tartalmát, ezt követõen
	 * pedig a konzol képernyõ tartalmát.
	 *
	 * @param _setpoint Az alapjel értéke.
	 */
	virtual void refreshSetpoint(const float _setpoint);

	/**
	 * @brief Nem végez semmilyen mûveletet sem.
	 *
	 * @param _errorLimit A megengedett pályakövetési hiba értéke.
	 */
	virtual void refreshErrorLimit(const float _errorLimit);

	/**
	 * @brief Frissíti az ventilátor-címke tartalmát, ezt követõen
	 * pedig a konzol képernyõ tartalmát.
	 *
	 * @param _fan A ventilátor aktuális állapota.
	 */
	virtual void refreshFanControllingValue(const bool _fan);

	/**
	 * @brief Frissíti az fûtõszál-címke tartalmát, ezt követõen
	 * pedig a konzol képernyõ tartalmát.
	 *
	 * @param _heater A fûtõszál aktuális állapota.
	 */
	virtual void refreshHeaterControllingValue(const bool _heater);
};

#endif /* INC_DISPLAYMOCK_H_ */