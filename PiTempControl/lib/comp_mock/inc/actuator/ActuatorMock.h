#ifndef INC_ACTUATORMOCK_H_
#define INC_ACTUATORMOCK_H_

#include <lib/app/inc/actuator/ActuatorInterface.h>

/**
 * @class ActuatorMock
 * @brief A m�k�dtet� komponens m�k�d�s�t ut�nz� oszt�ly.
 *
 * Ez az oszt�ly tesztel�si feladatok ell�t�s�ra szolg�l, a m�k�dtet�
 * viselked�s�t el�re meghat�rozott m�don ut�nozza.
 */
class ActuatorMock : public ActuatorInterface {
public:
	/**
	 * @brief Az ut�nzat alap�rtelmezett konstruktora.
	 */
	ActuatorMock();

	/**
	 * @brief Az ut�nzat virtu�lis destruktora.
	 */
	virtual ~ActuatorMock();

	/**
	 * @brief Jelz�st ad az inicializ�l� met�dus megh�v�s�r�l.
	 */
	virtual void initialize();

	/**
	 * @brief Ki�rja a konzol k�perny�re a f�t�sz�l �j �llapot�t.
	 *
	 * @param state A val�s�gban be�ll�tani k�v�nt �llapot.
	 */
	virtual void setHeaterState(bool state);

	/**
	 * @brief Ki�rja a konzol k�perny�re a ventil�tor �j �llapot�t.
	 *
	 * @param state A val�s�gban k�v�nt �llapot.
	 */
	virtual void setFanState(bool state);
};

#endif /* INC_ACTUATORMOCK_H_ */