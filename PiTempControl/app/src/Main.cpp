#include <iostream>
#include <string>
#include <lib/app/inc/core/TemperatureControllerApplication.h>

#include <lib/comp_mock/inc/regulator/RegulatorMock.h>
#include <lib/comp_mock/inc/sensor/SensorMock.h>
#include <lib/comp_mock/inc/actuator/ActuatorMock.h>
#include <lib/comp_mock/inc/display/DisplayMock.h>

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
#else
	RegulatorImpl regulator;
	SensorImpl sensor;
	ActuatorImpl actuator;
	DisplayImpl display;
#endif
	float setpoint;

	/* A haszn�lati s�g� ki�rat�sa a konzol k�perny�re, ha a megadott
	parancssori argumentumok sz�ma nem megfelel�. */
	if(argc != 3) {
		cout << "Usage: tempcontrol -s <setpoint>" << endl;
		cin.get();
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
					cin.get();
					exit(0);
				}
			}
			else {
				cout << "Not enough or invalid arguments." << endl;
				cin.get();
				exit(0);
			}
		}
		catch(exception& e) {
			cout << "An exception is thrown: " << e.what() << endl;
			cin.get();
			exit(0);
		}
	}
	
	/* H�m�rs�kletszab�lyoz� objektum l�rtrehoz�sa a kor�bban l�trehozott
	komponensekkel, majd a h�m�rs�kletszab�lyoz� elindt�sa. */
	TemperatureControllerApplication application(regulator, sensor, actuator, display, setpoint, 1.0f);
	cout << "Application started." << endl;
	application.start();
	cin.get();
	
	/* A h�m�rs�kletszab�lyoz� le�ll�t�sa �s az alkalmaz�s fut�s�nak
	befejez�se. */
	cout << endl << "Application stopped." << endl;
	application.stop();
	return 0;
}