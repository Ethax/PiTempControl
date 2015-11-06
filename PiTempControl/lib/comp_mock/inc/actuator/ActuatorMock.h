#ifndef INC_ACTUATORMOCK_H_
#define INC_ACTUATORMOCK_H_

#include <lib/app/inc/actuator/ActuatorInterface.h>

/**
 * @class ActuatorMock
 * @brief A mûködtetõ komponens mûködését utánzó osztály.
 *
 * Ez az osztály tesztelési feladatok ellátására szolgál, a mûködtetõ
 * viselkedését elõre meghatározott módon utánozza.
 */
class ActuatorMock : public ActuatorInterface {
public:
	/**
	 * @brief Az utánzat alapértelmezett konstruktora.
	 */
	ActuatorMock();

	/**
	 * @brief Az utánzat virtuális destruktora.
	 */
	virtual ~ActuatorMock();

	/**
	 * @brief Nem végez semmilyen mûveletet sem.
	 */
	virtual void initialize();

	/**
	 * @brief Nem végez semmilyen mûveletet sem.
	 *
	 * @param state A valóságban beállítani kívánt állapot.
	 */
	virtual void setHeaterState(bool state);

	/**
	 * @brief Nem végez semmilyen mûveletet sem.
	 *
	 * @param state A valóságban beállítani kívánt állapot.
	 */
	virtual void setFanState(bool state);

	/**
	 * @brief Nem végez semmilyen mûveletet sem.
	 */
	virtual void close();
};

#endif /* INC_ACTUATORMOCK_H_ */