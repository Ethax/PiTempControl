#include <lib/comp_mock/inc/sensor/SensorMock.h>

/*
 * A környezet statikus hõmérsékletének beállítása.
 */
const float SensorMock::ENVIRONMENTAL_TEMPERATURE = 25.0f;

/*
 * Az utánzat alapértelmezett konstruktora.
 */
SensorMock::SensorMock() : temperature(ENVIRONMENTAL_TEMPERATURE), appState(State::getInstance()) {}

/*
 * Az utánzat virtuális destruktora.
 */
SensorMock::~SensorMock() {}

/*
 * Jelzést ad az inicializáló metódus meghívásáról.
 */
void SensorMock::initialize() {}

/*
 * Szimulálja a hõmérséklet változását az aklamazás állapotaitól
 * függõen.
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
