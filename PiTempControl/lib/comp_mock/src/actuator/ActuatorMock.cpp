#include <lib/comp_mock/inc/actuator/ActuatorMock.h>

/*
 * Az utánzat alapértelmezett konstruktora.
 */
ActuatorMock::ActuatorMock() {}

/*
 * Az utánzat virtuális destruktora.
 */
ActuatorMock::~ActuatorMock() {}

/*
 * Nem végez semmilyen mûveletet sem.
 */
void ActuatorMock::initialize() {}

/*
 * Nem végez semmilyen mûveletet sem.
 */
void ActuatorMock::setHeaterState(bool state) {}

/*
 * Nem végez semmilyen mûveletet sem.
 */
void ActuatorMock::setFanState(bool state) {}

/*
 * Nem végez semmilyen mûveletet sem.
 */
void ActuatorMock::close() {}
