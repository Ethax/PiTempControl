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
 * Jelzést ad az inicializáló metódus meghívásáról.
 */
void ActuatorMock::initialize() {}

/*
 * Kiírja a konzol képernyõre a fûtõszál új állapotát.
 */
void ActuatorMock::setHeaterState(bool state) {}

/*
 * Kiírja a konzol képernyõre a ventilátor új állapotát.
 */
void ActuatorMock::setFanState(bool state) {}
