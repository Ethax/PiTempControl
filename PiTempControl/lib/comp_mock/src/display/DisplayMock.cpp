#include <lib/comp_mock/inc/display/DisplayMock.h>
#include <lib/app/inc/core/TextColoring.h>

/*
 * Összeállítja a kiírni kívánt sort és elvégzi a kiíratást a konzol
 * képernyõre.
 */
void DisplayMock::refreshDisplay(void) {
	std::cout << '\r' << setpointIndicator << heaterIndicator << fanIndicator << temperatureIndicator << std::flush;
}

/*
 * Az utánzat alapértelmezett konstruktora.
 */
DisplayMock::DisplayMock() :
	setpointIndicator("[Setpoint:  N/A \xC2\xB0""C]"),
	heaterIndicator("[Heater: N/A]"),
	fanIndicator("[Fan: N/A]"),
	temperatureIndicator("[Temperature:  N/A \xC2\xB0""C]") {}

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
	stream << '[' << color::modifier(color::FG_CYAN) << "Temperature: ";
	stream << color::modifier(color::FG_YELLOW) << std::fixed << std::setw(4) << std::setprecision(1) << _temp;
	stream << color::modifier(color::FG_DEFAULT) << " \xC2\xB0""C]";
	temperatureIndicator = stream.str();
	refreshDisplay();
}

/*
 * Kiírja a konzol képernyõre az alapjel értékét.
 */
void DisplayMock::refreshSetpoint(const float _setpoint) {
	std::stringstream stream;
	stream << '[' << color::modifier(color::FG_CYAN) << "Setpoint: ";
	stream << color::modifier(color::FG_YELLOW) << std::fixed << std::setw(4) << std::setprecision(1) << _setpoint;
	stream << color::modifier(color::FG_DEFAULT) << " \xC2\xB0""C]";
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
	stream << "[" << color::modifier(color::FG_CYAN) << "Fan: ";
	stream << color::modifier(_fan ? color::FG_GREEN : color::FG_RED) << (_fan ? " ON" : "OFF");
	stream << color::modifier(color::FG_DEFAULT) << "]";
	fanIndicator = stream.str();
	refreshDisplay();
}

/*
 * Kiírja a konzol képernyõre a fûtõszál állapotát.
 */
void DisplayMock::refreshHeaterControllingValue(const bool _heater) {
	std::stringstream stream;
	stream << "[" << color::modifier(color::FG_CYAN) << "Heater: ";
	stream << color::modifier(_heater ? color::FG_GREEN : color::FG_RED) << (_heater ? " ON" : "OFF");
	stream << color::modifier(color::FG_DEFAULT) << "]";
	heaterIndicator = stream.str();
	refreshDisplay();
}
