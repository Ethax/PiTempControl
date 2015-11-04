#include <lib/comp_mock/inc/regulator/RegulatorMock.h>

/*
 * Az utánzat alapértelmezett konstruktora.
 */
RegulatorMock::RegulatorMock() : setpoint(0.0f), errorlimit(0.0f) {}

/*
 * Az utánzat virtuális destruktora.
 */
RegulatorMock::~RegulatorMock() {}

/*
 * Beállítja a kívánt alapjelet.
 */
void RegulatorMock::setDesiredSetpoint(const float _setpoint) {
	setpoint = _setpoint;
}

/*
 * Beállítja a megengedett pályakövetési hibát.
 */
void RegulatorMock::setPositionErrorLimit(const float _errorlimit) {
	errorlimit = _errorlimit;
}

/*
 * Meghatározza a bevatkozójelet az átadott hõmérséklet függvényében.
 */
std::set<ControlSignal> RegulatorMock::getControlSignal(const float actualTemperature, const bool fanState, const bool heaterState) {
	std::set<ControlSignal> controlSignals;

	/* A fûtõszál kikapcsolása és a ventilátor bekapcsolása, ha a
	hõmérséklet túllépte a megengedett pályakövetési hibát. */
	if(actualTemperature > (setpoint + errorlimit)) {
		if(!fanState)
			controlSignals.insert(CTRL_SWITCH_ON_THE_FAN);
		if(heaterState)
			controlSignals.insert(CTRL_SWITCH_OFF_THE_HEATER);
	}
	/* A fûtõszál és a ventilátor kikapcsolása, ha a hõmérséklet a
	megengedett pályakövetési hibán belül van. */
	else if(actualTemperature >= (setpoint - errorlimit) && actualTemperature <= (setpoint + errorlimit)) {
		if(fanState)
			controlSignals.insert(CTRL_SWITCH_OFF_THE_FAN);
		if(heaterState)
			controlSignals.insert(CTRL_SWITCH_OFF_THE_HEATER);
	}
	/* A fûtõszál bekapcsolása és a ventilátor kikapcsolása, ha a
	hõmérséklet a megengedett pályakövetési hiba alá esett. */
	else if(actualTemperature < (setpoint - errorlimit)) {
		if(fanState)
			controlSignals.insert(CTRL_SWITCH_OFF_THE_FAN);
		if(!heaterState)
			controlSignals.insert(CTRL_SWITCH_ON_THE_HEATER);
	}

	/* A meghatározott bevatkozójel visszaadása. */
	return controlSignals;
}
