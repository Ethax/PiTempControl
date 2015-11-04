#include <lib/comp_mock/inc/sensor/SensorMock.h>

/*
 * A k�rnyezet statikus h�m�rs�klet�nek be�ll�t�sa.
 */
const float SensorMock::ENVIRONMENTAL_TEMPERATURE = 25.0f;

/*
 * Az ut�nzat alap�rtelmezett konstruktora.
 */
SensorMock::SensorMock() : temperature(ENVIRONMENTAL_TEMPERATURE), appState(State::getInstance()) {}

/*
 * Az ut�nzat virtu�lis destruktora.
 */
SensorMock::~SensorMock() {}

/*
 * Jelz�st ad az inicializ�l� met�dus megh�v�s�r�l.
 */
void SensorMock::initialize() {}

/*
 * Szimul�lja a h�m�rs�klet v�ltoz�s�t az aklamaz�s �llapotait�l
 * f�gg�en.
 */
float SensorMock::getTemperature() {
	std::srand((unsigned int)std::time(NULL));

	if(appState.getFanState() == appState.getHeaterState() && temperature != ENVIRONMENTAL_TEMPERATURE) {
		temperature += (float)(std::rand() % 50) / (temperature > ENVIRONMENTAL_TEMPERATURE ? -100.0f : 100.0f);
	}
	else if(appState.getFanState() && !appState.getHeaterState()) {
		temperature -= (float)(rand() % 250 + 100) / 100.0f;
	}
	else if(!appState.getFanState() && appState.getHeaterState()) {
		temperature += (float)(rand() % 250 + 100) / 100.0f;
	}

	return temperature;
}
