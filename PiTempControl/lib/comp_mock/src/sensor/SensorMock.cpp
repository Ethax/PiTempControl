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
	/* A véletlen szám generálás inicializálása. */
	std::srand((unsigned int)std::time(NULL));

	/* A hõmérséklet lassú igazítása a környezet hõmérsékletéhez,
	amennyibena ventilátor és a fûtõszál kikapcsolt állapotban vannak,
	és a hõmérséklet eltér a környezet hõmérsékletétõl. */
	if(appState.getFanState() == appState.getHeaterState() && temperature != ENVIRONMENTAL_TEMPERATURE) {
		temperature += (float)(std::rand() % 50) / (temperature > ENVIRONMENTAL_TEMPERATURE ? -100.0f : 100.0f);
	}
	/* A hõmérséklet csökkentése, amennyiben a ventilátor be van
	kapcsolva. */
	else if(appState.getFanState() && !appState.getHeaterState()) {
		temperature -= (float)(rand() % 250 + 100) / 100.0f;
	}
	/* A hõmérséklet növelése, amennyiben a fûtõszál be van
	kapcsolva. */
	else if(!appState.getFanState() && appState.getHeaterState()) {
		temperature += (float)(rand() % 250 + 100) / 100.0f;
	}

	/* A szimulált hõmérséklet-érték visszaadása. */
	return temperature;
}

/*
 * Nem végez semmilyen mûveletet sem.
 */
void SensorMock::close() {}