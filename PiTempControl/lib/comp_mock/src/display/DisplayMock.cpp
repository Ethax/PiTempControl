#include <lib/comp_mock/inc/display/DisplayMock.h>
#include <lib/app/inc/core/TextColoring.h>

/*
 * Összeállítja a kiírni kívánt sort a címkékbõl és elvégzi a kiíratást
 * a konzol képernyõre.
 */
void DisplayMock::refreshDisplay(void) {
	std::cout << cret << setpointIndicator << heaterIndicator << fanIndicator << temperatureIndicator << std::flush;
}

/*
 * Az utánzat alapértelmezett konstruktora.
 */
DisplayMock::DisplayMock() :
	setpointIndicator("[Setpoint:   N/A \xC2\xB0""C]"),
	heaterIndicator("[Heater: N/A]"),
	fanIndicator("[Fan: N/A]"),
	temperatureIndicator("[Temperature:   N/A \xC2\xB0""C]") {}

/*
 * Az utánzat virtuális destruktora.
 */
DisplayMock::~DisplayMock() {}

/*
 * Nem végez semmilyen mûveletet sem.
 */
void DisplayMock::initialize() {}

/*
 * Frissíti a hõmérséklet-címke tartalmát, ezt követõen pedig a konzol
 * képernyõ tartalmát.
 */
void DisplayMock::refreshActualTemperature(const float _temp) {
	std::stringstream stream;
	stream << '[' << color::modifier(color::FG_CYAN) << "Temperature: ";
	stream << color::modifier(color::FG_YELLOW) << std::fixed << std::setw(5) << std::setprecision(2) << _temp;
	stream << color::modifier(color::FG_DEFAULT) << " \xC2\xB0""C]";
	temperatureIndicator = stream.str();
	refreshDisplay();
}

/*
 * Frissíti az alapjel-címke tartalmát, ezt követõen pedig a konzol
 * képernyõ tartalmát.
 */
void DisplayMock::refreshSetpoint(const float _setpoint) {
	std::stringstream stream;
	stream << '[' << color::modifier(color::FG_CYAN) << "Setpoint: ";
	stream << color::modifier(color::FG_YELLOW) << std::fixed << std::setw(5) << std::setprecision(2) << _setpoint;
	stream << color::modifier(color::FG_DEFAULT) << " \xC2\xB0""C]";
	setpointIndicator = stream.str();
	refreshDisplay();
}

/*
 * Nem végez semmilyen mûveletet sem.
 */
void DisplayMock::refreshErrorLimit(const float _errorLimit) {}

/*
 * Frissíti az ventilátor-címke tartalmát, ezt követõen pedig a konzol
 * képernyõ tartalmát.
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
 * Frissíti az fûtõszál-címke tartalmát, ezt követõen pedig a konzol
 * képernyõ tartalmát.
 */
void DisplayMock::refreshHeaterControllingValue(const bool _heater) {
	std::stringstream stream;
	stream << "[" << color::modifier(color::FG_CYAN) << "Heater: ";
	stream << color::modifier(_heater ? color::FG_GREEN : color::FG_RED) << (_heater ? " ON" : "OFF");
	stream << color::modifier(color::FG_DEFAULT) << "]";
	heaterIndicator = stream.str();
	refreshDisplay();
}
