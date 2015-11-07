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
	/* A v�letlen sz�m gener�l�s inicializ�l�sa. */
	std::srand((unsigned int)std::time(NULL));

	/* A h�m�rs�klet lass� igaz�t�sa a k�rnyezet h�m�rs�klet�hez,
	amennyibena ventil�tor �s a f�t�sz�l kikapcsolt �llapotban vannak,
	�s a h�m�rs�klet elt�r a k�rnyezet h�m�rs�klet�t�l. */
	if(appState.getFanState() == appState.getHeaterState() && temperature != ENVIRONMENTAL_TEMPERATURE) {
		temperature += (float)(std::rand() % 50) / (temperature > ENVIRONMENTAL_TEMPERATURE ? -100.0f : 100.0f);
	}
	/* A h�m�rs�klet cs�kkent�se, amennyiben a ventil�tor be van
	kapcsolva. */
	else if(appState.getFanState() && !appState.getHeaterState()) {
		temperature -= (float)(rand() % 250 + 100) / 100.0f;
	}
	/* A h�m�rs�klet n�vel�se, amennyiben a f�t�sz�l be van
	kapcsolva. */
	else if(!appState.getFanState() && appState.getHeaterState()) {
		temperature += (float)(rand() % 250 + 100) / 100.0f;
	}

	/* A szimul�lt h�m�rs�klet-�rt�k visszaad�sa. */
	return temperature;
}

/*
 * Nem v�gez semmilyen m�veletet sem.
 */
void SensorMock::close() {}