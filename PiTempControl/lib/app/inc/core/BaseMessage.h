#ifndef INC_MESSAGEBASE_H_
#define INC_MESSAGEBASE_H_

#include <lib/app/inc/common.h>

class MessageReceiver;
class MessageSender;

/**
* @class BaseMessage
* @brief Az üzenetek õsosztálya.
*
* Az alkalmazáson belül a modulok közötti kommunikációt megvalósító üzenetek
* mindegyike ebbõl az osztályból származik.
*/
class BaseMessage {
	/**
	 * Teljeskörû hozzáférés biztosítása a privát adattagokhoz és privát
	 * metódusokhoz a MessageSender osztály számára.
	 */
	friend class MessageSender;

private:
	/**
	 * Az üzenet létrehozásának pillanata.
	 */
	std::chrono::system_clock::time_point created;

	/**
	 * Az üzenet kézbesítésének állapota.
	 */
	std::atomic_bool sent;

	/**
	 * Az üzenet kézbesítésének kivárásához használt állapotváltozó.
	 */
	std::condition_variable cv;

	/**
	 * A több szálról való egyidejû hozzáférést kizáró adattag.
	 */
	std::mutex mutex;

	/**
	 * Hiba esetén a kivétel objektumra mutató pointer, amivel az
	 * objektum átadható akár egy másik szálon futó kivételkezelõnek is.
	 */
	std::exception_ptr eptr;

	/**
	 * @brief Az osztály másoló konstruktorának tiltása.
	 */
	BaseMessage(const BaseMessage&) = delete;

	/**
	 * @brief Az osztály értékadó operátorának tiltása.
	 */
	BaseMessage& operator=(const BaseMessage&) = delete;

protected:
	/**
	 * @brief Az oszály alapértelmezett konstruktora.
	 */
	BaseMessage();

	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~BaseMessage();

private:
	/**
	 * @brief Átadja az ebbõl az osztályból példányosított objektumot
	 * az üzenetet fogadó objektumnak feldolgozásra.
	 *
	 * @param receiver Az üzenetet fogadó objektumra mutató referencia.
	 */
	virtual void send(MessageReceiver& receiver) const;

	/**
	 * @brief Módosítja az üzenet állapotát kézbesítettre.
	 *
	 * Amennyiben az üzenetet kézbesítõ szál várakozik, a metódus meghívása
	 * feloldja a várakozást.
	 */
	void setSent();

	/**
	 * @brief Beállítja az üzenet kivételre mutató pointerét az átadott
	 * kivétel objektumra.
	 *
	 * @param _eptr A kivétel objektumra mutató kivétel pointer.
	 */
	void setException(std::exception_ptr _eptr);

public:
	/**
	 * @brief Felfüggeszti a szál futását az üzenet kézbesítéséig.
	 */
	void waitFor();
};

#endif /* INC_MESSAGEBASE_H_ */

