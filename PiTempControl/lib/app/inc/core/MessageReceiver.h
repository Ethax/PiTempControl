#ifndef INC_MESSAGEHANDLER_H_
#define INC_MESSAGEHANDLER_H_

#include <lib/app/inc/common.h>

class MessageSender;
class BaseMessage;
class TemperatureMessage;
class ControlMessage;
class SetupMessage;

/**
 * @class MessageReceiver
 * @brief Az üzeneteket fogadni képes osztályok õsosztálya.
 *
 * Minden olyan osztály, amelyik megvalósítja valamelyik üzenet fogadását,
 * ebbõl az osztályból származik és felüldefiniálja a megfelelõ üzenetet
 * fogadó virtuális metódust.
 */
class MessageReceiver {
	/**
	 * Teljeskörû hozzáférés biztosítása a privát adattagokhoz és privát
	 * metódusokhoz a MessageSender osztály számára.
	 */
	friend class MessageSender;

	/**
	 * Teljeskörû hozzáférés biztosítása a privát adattagokhoz és privát
	 * metódusokhoz a BaseMessage osztály számára.
	 */
	friend class BaseMessage;

private:
	/**
	 * @brief Az osztály másoló konstruktorának tiltása.
	 */
	MessageReceiver(const MessageReceiver&) = delete;
	
	/**
	 * @brief Az osztály értékadó operátorának tiltása.
	 */
	MessageReceiver& operator=(const MessageReceiver&) = delete;

protected:
	/**
	 * @brief Az oszály alapértelmezett konstruktora.
	 */
	MessageReceiver();
	
	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~MessageReceiver();

public:
	/**
	 * @brief Fogadja és feldolgozza az átadott BaseMessage típusú
	 * üzenetet.
	 *
	 * @param msg A fogadni és feldolgozni kívánt üzenet.
	 */
	virtual void receiveMessage(const BaseMessage& msg);

	/**
	 * @brief Fogadja és feldolgozza az átadott TemperatureMessage
	 * típusú üzenetet.
	 *
	 * @param msg A fogadni és feldolgozni kívánt üzenet.
	 */
	virtual void receiveMessage(const TemperatureMessage& msg);

	/**
	 * @brief Fogadja és feldolgozza az átadott ControlMessage
	 * típusú üzenetet.
	 *
	 * @param msg A fogadni és feldolgozni kívánt üzenet.
	 */
	virtual void receiveMessage(const ControlMessage& msg);

	/**
	 * @brief Fogadja és feldolgozza az átadott SetupMessage
	 * típusú üzenetet.
	 *
	 * @param msg A fogadni és feldolgozni kívánt üzenet.
	 */
	virtual void receiveMessage(const SetupMessage& msg);
};

#endif /* INC_MESSAGEHANDLER_H_ */