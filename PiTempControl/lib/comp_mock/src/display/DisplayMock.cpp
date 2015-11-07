#include <lib/comp_mock/inc/display/DisplayMock.h>
#include <lib/app/inc/core/TextColoring.h>

/*
 * �ssze�ll�tja a ki�rni k�v�nt sort a c�mk�kb�l �s elv�gzi a ki�rat�st
 * a konzol k�perny�re.
 */
void DisplayMock::refreshDisplay(void) {
	std::cout << cret << setpointIndicator << heaterIndicator << fanIndicator << temperatureIndicator << std::flush;
}

/*
 * Az ut�nzat alap�rtelmezett konstruktora.
 */
DisplayMock::DisplayMock() :
	setpointIndicator("[Setpoint:   N/A \xC2\xB0""C]"),
	heaterIndicator("[Heater: N/A]"),
	fanIndicator("[Fan: N/A]"),
	temperatureIndicator("[Temperature:   N/A \xC2\xB0""C]") {}

/*
 * Az ut�nzat virtu�lis destruktora.
 */
DisplayMock::~DisplayMock() {}

/*
 * Nem v�gez semmilyen m�veletet sem.
 */
void DisplayMock::initialize() {}

/*
 * Friss�ti a h�m�rs�klet-c�mke tartalm�t, ezt k�vet�en pedig a konzol
 * k�perny� tartalm�t.
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
 * Friss�ti az alapjel-c�mke tartalm�t, ezt k�vet�en pedig a konzol
 * k�perny� tartalm�t.
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
 * Nem v�gez semmilyen m�veletet sem.
 */
void DisplayMock::refreshErrorLimit(const float _errorLimit) {}

/*
 * Friss�ti az ventil�tor-c�mke tartalm�t, ezt k�vet�en pedig a konzol
 * k�perny� tartalm�t.
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
 * Friss�ti az f�t�sz�l-c�mke tartalm�t, ezt k�vet�en pedig a konzol
 * k�perny� tartalm�t.
 */
void DisplayMock::refreshHeaterControllingValue(const bool _heater) {
	std::stringstream stream;
	stream << "[" << color::modifier(color::FG_CYAN) << "Heater: ";
	stream << color::modifier(_heater ? color::FG_GREEN : color::FG_RED) << (_heater ? " ON" : "OFF");
	stream << color::modifier(color::FG_DEFAULT) << "]";
	heaterIndicator = stream.str();
	refreshDisplay();
}
