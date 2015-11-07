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
#include <lib/comp_impl/inc/sensor/SensorImpl.h>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

/**
 * @brief Az alkalmaz�s bel�p�si pontja, ami az alkalmaz�s
 * futtat�sakor el�sz�r h�v�dik meg.
 *
 * @return Ha nulla, akkor az alkalmaz�s hib�tlanul lefutott.
 */
int main(int argc, char* argv[]) {
#ifdef _WIN32
	SetConsoleOutputCP(1252);
#endif

	/* A komponensek l�trehoz�sa a ford�t�skor meghat�rozott
	�rt�kt�l f�gg�en. */
#ifdef SUBSTITUTE_HARDWARE
	RegulatorMock regulator;
	SensorMock sensor;
	ActuatorMock actuator;
	DisplayMock display;
	float errorLimit = 1.5f;
#else
	RegulatorMock regulator;
	SensorImpl sensor;
	ActuatorImpl actuator;
	DisplayMock display;
	float errorLimit = 0.25f;
#endif
	float setpoint;

	/* A haszn�lati s�g� ki�rat�sa a konzol k�perny�re, ha a megadott
	parancssori argumentumok sz�ma nem megfelel�. */
	if(argc != 3) {
		cout << "Usage: tempcontrol -s <setpoint>" << endl;
		exit(0);
	}

	/* A megadott parancssori argumentumok feldolgoz�sa �s az �tadott
	�rt�kek let�rol�sa. */
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
	
	/* H�m�rs�kletszab�lyoz� objektum l�rtrehoz�sa a kor�bban l�trehozott
	komponensekkel. */
	TemperatureControllerApplication application(regulator, sensor, actuator, display, setpoint, errorLimit);
#ifdef __linux__
	system("clear");
#endif
	try {
		/* A h�m�rs�kletszab�lyoz� elindt�sa �s futtat�sa valamelyik
		billenty� le�t�s�ig. */
		cout << "Application started." << endl << endl;
		application.start();
		cin.get();
	
		/* A h�m�rs�kletszab�lyoz� le�ll�t�sa �s az alkalmaz�s
		fut�s�nak befejez�se. */
		cout << endl << "Application stopped." << endl;
		application.stop();
	}
	catch(AppException& e) {
		cout << e.getErrorMessage() << endl;
	}
	catch(...) {
		cout << endl << "Application terminated with an unexpected error." << endl;
	}

	/* Az alkalmaz�s fut�s�nak befejez�se. */
	return 0;
}