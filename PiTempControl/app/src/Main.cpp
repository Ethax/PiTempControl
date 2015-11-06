#include <iostream>
#include <string>
#include <cstdlib>
#include <lib/app/inc/core/TemperatureControllerApplication.h>
#include <lib/app/inc/core/AppException.h>

#include <lib/comp_mock/inc/regulator/RegulatorMock.h>
#include <lib/comp_mock/inc/sensor/SensorMock.h>
#include <lib/comp_mock/inc/actuator/ActuatorMock.h>
#include <lib/comp_mock/inc/display/DisplayMock.h>

#include <lib/comp_impl/inc/actuator/ActuatorImpl.h>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

/**
 * @brief Az alkalmazás belépési pontja, ami az alkalmazás
 * futtatásakor elõször hívódik meg.
 *
 * @return Ha nulla, akkor az alkalmazás hibátlanul lefutott.
 */
int main(int argc, char* argv[]) {
#ifdef _WIN32
	SetConsoleOutputCP(1252);
#endif

	/* A komponensek létrehozása a fordításkor meghatározott
	értéktõl függõen. */
#ifdef SUBSTITUTE_HARDWARE
	RegulatorMock regulator;
	SensorMock sensor;
	ActuatorImpl actuator; // ActuatorMock
	DisplayMock display;
#else
	RegulatorMock regulator;
	SensorImpl sensor;
	ActuatorImpl actuator;
	DisplayMock display;
#endif
	float setpoint;

	/* A használati súgó kiíratása a konzol képernyõre, ha a megadott
	parancssori argumentumok száma nem megfelelõ. */
	if(argc != 3) {
		cout << "Usage: tempcontrol -s <setpoint>" << endl;
		exit(0);
	}

	/* A megadott parancssori argumentumok feldolgozása és az átadott
	értékek letárolása. */
	for(int i = 1; i < argc; i++) {
		try {
			if(string(argv[i]) == "-s") {
				setpoint = stof(string(argv[++i]));
				if(setpoint < 0.0f || setpoint > 99.0f) {
					cout << "Invalid setpoint. The value must be between 0 and 99." << endl;
					exit(0);
				}
			}
			else {
				cout << "Not enough or invalid arguments." << endl;
				exit(0);
			}
		}
		catch(exception& e) {
			cout << "An exception is thrown: " << e.what() << endl;
			exit(0);
		}
	}
	
	/* Hõmérsékletszabályozó objektum lértrehozása a korábban létrehozott
	komponensekkel. */
	TemperatureControllerApplication application(regulator, sensor, actuator, display, setpoint, 1.0f);
#ifdef __linux__
	system("clear");
#endif
	try {
		/* A hõmérsékletszabályozó elindtása és futtatása valamelyik
		billentyû leütéséig. */
		cout << "Application started." << endl << endl;
		application.start();
		cin.get();
	
		/* A hõmérsékletszabályozó leállítása és az alkalmazás
		futásának befejezése. */
		cout << endl << "Application stopped." << endl;
		application.stop();
	}
	catch(AppException& e) {
		cout << e.getErrorMessage() << endl;
	}
	return 0;
}