#include <lib/comp_mock/inc/actuator/ActuatorMock.h>

/*
 * Az ut�nzat alap�rtelmezett konstruktora.
 */
ActuatorMock::ActuatorMock() {}

/*
 * Az ut�nzat virtu�lis destruktora.
 */
ActuatorMock::~ActuatorMock() {}

/*
 * Jelz�st ad az inicializ�l� met�dus megh�v�s�r�l.
 */
void ActuatorMock::initialize() {}

/*
 * Ki�rja a konzol k�perny�re a f�t�sz�l �j �llapot�t.
 */
void ActuatorMock::setHeaterState(bool state) {}

/*
 * Ki�rja a konzol k�perny�re a ventil�tor �j �llapot�t.
 */
void ActuatorMock::setFanState(bool state) {}
