#include <lib/comp_mock/inc/display/DisplayMock.h>
#include <lib/app/inc/core/TextColoring.h>

/*
 * �ssze�ll�tja a ki�rni k�v�nt sort �s elv�gzi a ki�rat�st a konzol
 * k�perny�re.
 */
void DisplayMock::refreshDisplay(void) {
	std::cout << '\r' << setpointIndicator << heaterIndicator << fanIndicator << temperatureIndicator << std::flush;
}

/*
 * Az ut�nzat alap�rtelmezett konstruktora.
 */
DisplayMock::DisplayMock() :
	setpointIndicator("[Setpoint:  N/A \xC2\xB0""C]"),
	heaterIndicator("[Heater: N/A]"),
	fanIndicator("[Fan: N/A]"),
	temperatureIndicator("[Temperature:  N/A \xC2\xB0""C]") {}

/*
 * Az ut�nzat virtu�lis destruktora.
 */
DisplayMock::~DisplayMock() {}

/*
 * Jelz�st ad az inicializ�l� met�dus megh�v�s�r�l.
 */
void DisplayMock::initialize() {}

/*
 * Ki�rja a konzol k�perny�re a m�rt h�m�rs�kletet.
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
 * Ki�rja a konzol k�perny�re az alapjel �rt�k�t.
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
 * Ki�rja a konzol k�perny�re a megengedett p�lyak�vet�si hiba �rt�k�t.
 */
void DisplayMock::refreshErrorLimit(const float _errorLimit) {}

/*
 * Ki�rja a konzol k�perny�re a ventil�tor �llapot�t.
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
 * Ki�rja a konzol k�perny�re a f�t�sz�l �llapot�t.
 */
void DisplayMock::refreshHeaterControllingValue(const bool _heater) {
	std::stringstream stream;
	stream << "[" << color::modifier(color::FG_CYAN) << "Heater: ";
	stream << color::modifier(_heater ? color::FG_GREEN : color::FG_RED) << (_heater ? " ON" : "OFF");
	stream << color::modifier(color::FG_DEFAULT) << "]";
	heaterIndicator = stream.str();
	refreshDisplay();
}
