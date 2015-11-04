#include <lib/comp_mock/inc/regulator/RegulatorMock.h>

/*
 * Az ut�nzat alap�rtelmezett konstruktora.
 */
RegulatorMock::RegulatorMock() : setpoint(0.0f), errorlimit(0.0f) {}

/*
 * Az ut�nzat virtu�lis destruktora.
 */
RegulatorMock::~RegulatorMock() {}

/*
 * Be�ll�tja a k�v�nt alapjelet.
 */
void RegulatorMock::setDesiredSetpoint(const float _setpoint) {
	setpoint = _setpoint;
}

/*
 * Be�ll�tja a megengedett p�lyak�vet�si hib�t.
 */
void RegulatorMock::setPositionErrorLimit(const float _errorlimit) {
	errorlimit = _errorlimit;
}

/*
 * Meghat�rozza a bevatkoz�jelet az �tadott h�m�rs�klet f�ggv�ny�ben.
 */
std::set<ControlSignal> RegulatorMock::getControlSignal(const float actualTemperature, const bool fanState, const bool heaterState) {
	std::set<ControlSignal> controlSignals;

	/* A f�t�sz�l kikapcsol�sa �s a ventil�tor bekapcsol�sa, ha a
	h�m�rs�klet t�ll�pte a megengedett p�lyak�vet�si hib�t. */
	if(actualTemperature > (setpoint + errorlimit)) {
		if(!fanState)
			controlSignals.insert(CTRL_SWITCH_ON_THE_FAN);
		if(heaterState)
			controlSignals.insert(CTRL_SWITCH_OFF_THE_HEATER);
	}
	/* A f�t�sz�l �s a ventil�tor kikapcsol�sa, ha a h�m�rs�klet a
	megengedett p�lyak�vet�si hib�n bel�l van. */
	else if(actualTemperature >= (setpoint - errorlimit) && actualTemperature <= (setpoint + errorlimit)) {
		if(fanState)
			controlSignals.insert(CTRL_SWITCH_OFF_THE_FAN);
		if(heaterState)
			controlSignals.insert(CTRL_SWITCH_OFF_THE_HEATER);
	}
	/* A f�t�sz�l bekapcsol�sa �s a ventil�tor kikapcsol�sa, ha a
	h�m�rs�klet a megengedett p�lyak�vet�si hiba al� esett. */
	else if(actualTemperature < (setpoint - errorlimit)) {
		if(fanState)
			controlSignals.insert(CTRL_SWITCH_OFF_THE_FAN);
		if(!heaterState)
			controlSignals.insert(CTRL_SWITCH_ON_THE_HEATER);
	}

	/* A meghat�rozott bevatkoz�jel visszaad�sa. */
	return controlSignals;
}
