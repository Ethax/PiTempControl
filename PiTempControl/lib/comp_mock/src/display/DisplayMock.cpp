#include <lib/comp_mock/inc/display/DisplayMock.h>

/*
 * Összeállítja a kiírni kívánt sort és elvégzi a kiíratást a konzol
 * képernyõre.
 */
void DisplayMock::refreshDisplay(void) {
	std::cout << '\r' << setpointIndicator << heaterIndicator << fanIndicator << temperatureIndicator;
}

/*
 * Az utánzat alapértelmezett konstruktora.
 */
DisplayMock::DisplayMock() :
	setpointIndicator("[Setpoint:  N/A °C]"),
	heaterIndicator("[Heater: N/A]"),
	fanIndicator("[Fan: N/A]"),
	temperatureIndicator("[Temperature:  N/A °C]") {}

/*
 * Az utánzat virtuális destruktora.
 */
DisplayMock::~DisplayMock() {}

/*
 * Jelzést ad az inicializáló metódus meghívásáról.
 */
void DisplayMock::initialize() {}

/*
 * Kiírja a konzol képernyõre a mért hõmérsékletet.
 */
void DisplayMock::refreshActualTemperature(const float _temp) {
	std::stringstream stream;
	stream << "[Temperature: " << std::fixed << std::setw(4) << std::setprecision(1) << _temp << " °C]";
	temperatureIndicator = stream.str();
	refreshDisplay();
}

/*
 * Kiírja a konzol képernyõre az alapjel értékét.
 */
void DisplayMock::refreshSetpoint(const float _setpoint) {
	std::stringstream stream;
	stream << "[Setpoint: " << std::fixed << std::setw(4) << std::setprecision(1) << _setpoint << " °C]";
	setpointIndicator = stream.str();
	refreshDisplay();
}

/*
 * Kiírja a konzol képernyõre a megengedett pályakövetési hiba értékét.
 */
void DisplayMock::refreshErrorLimit(const float _errorLimit) {}

/*
 * Kiírja a konzol képernyõre a ventilátor állapotát.
 */
void DisplayMock::refreshFanControllingValue(const bool _fan) {
	std::stringstream stream;
	stream << "[Fan: " << (_fan ? " ON]" : "OFF]");
	fanIndicator = stream.str();
	refreshDisplay();
}

/*
 * Kiírja a konzol képernyõre a fûtõszál állapotát.
 */
void DisplayMock::refreshHeaterControllingValue(const bool _heater) {
	std::stringstream stream;
	stream << "[Heater: " << (_heater ? " ON]" : "OFF]");
	heaterIndicator = stream.str();
	refreshDisplay();
}
