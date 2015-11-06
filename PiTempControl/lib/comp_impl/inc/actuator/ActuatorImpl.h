#ifndef INC_ACTUATORIMPL_H_
#define INC_ACTUATORIMPL_H_

#include <lib/app/inc/actuator/ActuatorInterface.h>
#include <bcm2835.h>

/**
 * @class ActuatorImpl
 * @brief A m�k�dtet� komponenst megval�s�t� oszt�ly.
 *
 * Ez az oszt�ly a f�t�sz�lat �s a ventil�tort ki- �s bekapcsol� rel�ket
 * m�k�dteti a GPIO-kon kereszt�l. El�re be�getett m�don a f�t�sz�lhoz
 * tartoz� rel� tekercs�nek a GPIO 18-ra ventil�torhoz tartoz� rel�
 * tekercs�nek pedig a GPIO 17-re kell csatlakozniuk. (A rel�k tekercseit
 * kiz�r�lag kapcsol��zem� tranzisztorokkal szabad a kimenetekr�l
 * meghajtani.)
 */
class ActuatorImpl : public ActuatorInterface {
	
public:
	/**
	 * @brief Az oszt�ly alap�rtelmezett konstruktora.
	 */
	ActuatorImpl();

	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~ActuatorImpl();

	/**
	 * @brief Inicializ�lja a BCM2835 modult �s az alkalmazott
	 * GPIO-kat.
	 */
	virtual void initialize();

	/**
	 * @brief A megadott �rt�ket kik�ldi a GPIO 18-ra.
	 *
	 * @param state A be�ll�tani k�v�nt �llapot.
	 */
	virtual void setHeaterState(bool state);

	/**
	 * @brief A megadott �rt�ket kik�ldi a GPIO 17-re.
	 *
	 * @param state A be�ll�tani k�v�nt �llapot.
	 */
	virtual void setFanState(bool state);

	/**
	 * @brief Lez�rja a BCM2835 modult.
	 */
	virtual void close();
};

#endif /* INC_ACTUATORIMPL_H_ */