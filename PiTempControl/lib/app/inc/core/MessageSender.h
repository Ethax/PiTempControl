#ifndef INC_MESSAGESENDER_H_
#define INC_MESSAGESENDER_H_

#include <lib/app/inc/common.h>

class BaseMessage;
class MessageReceiver;

/**
 * @class MessageSender
 * @brief Az üzenetek kézbesítését lebonyolító osztály.
 *
 * Az elküldeni kívánt üzeneteket egy várakozási sorba gyûjti, majd
 * azokat a felvétel sorrendjében átadja a feliratkozott fogadóknak.
 */
class MessageSender {
	/**
	 * Teljeskörû hozzáférés biztosítása a privát adattagokhoz és privát
	 * metódusokhoz a TemperatureControllerApplication osztály számára.
	 */
	friend class TemperatureControllerApplication;

private:
	/**
	 * A feliratkozott fogadók listája.
	 */
	std::list<MessageReceiver*> receivers;

	/**
	 * A elküldeni kívánt üzenetek várakozási sora.
	 */
	std::queue<std::shared_ptr<BaseMessage>> messages;

	/**
	 * Az üzeneteket kézbesítõ szál futásának állapota.
	 */
	std::atomic_bool active;

	/**
	 * A több szálról való egyidejû hozzáférést kizáró adattag.
	 */
	std::recursive_mutex mutex;

	/**
	 * Az üzeneteket kézbesítõ szál leállításakor használt kölcsönös
	 * kizárást biztosító adattag.
	 */
	std::recursive_mutex joinMutex;

	/**
	 * Új üzenetek érkezésének kivárásához használt állapotváltozó.
	 */
	std::condition_variable_any cv;

	/**
	 * Az üzeneteket kézbesítõ szál kezelését biztosító adattag.
	 */
	std::thread thread;

	/**
	 * @brief Az oszály alapértelmezett konstruktora.
	 */
	MessageSender();

	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~MessageSender();

	/**
	 * @brief Elhelyezi az elküldeni kívánt üzenetet a várakozási sorba és
	 * jelez az üzeneteket kézbesítõ szálnak, hogy folytathatja a várakozási
	 * sorban levõ üzenetek kézbesítését.
	 *
	 * @param message Az elküldeni kívánt üzenetre mutató megosztott
	 * pointer.
	 */
	void sendMessage(std::shared_ptr<BaseMessage> message);

	/**
	 * @brief Kézbesíti az átadott üzenetet a feliratkozott fogadóknak.
	 *
	 * Az üzenet minden egyes feliratkozott fogadóhoz eljut, de csak az
	 * fogja feldolgozni, amelyik felüldefiniálta az üzenet típusának
	 * megfelelõ virtuális fogadó metódust. 
	 *
	 * @param message A kézbesíteni kívánt üzenet.
	 */
	void passMessage(BaseMessage& message);

	/**
	 * @brief Felveszi az átadott fogadót a feliratkozott fogadók közé.
	 *
	 * @param receiver A felvenni kívánt fogadó.
	 */
	void registerMessageReceiver(MessageReceiver& receiver);

	/**
	 * @brief A futtató szálat felfüggesztve figyeli a várakozási sort.
	 * Amennyiben új üzenetek kerülnek a várakozási sorba, kézbesíti
	 * azokat, majd folytatja az új üzenetek érkezésének figyelést.
	 */
	void messageHandler();

	/**
	 * @brief Elindítja a üzeneteket kézbesítõ szálat.
	 */
	void start();

	/**
	 * @brief Leállítja a üzeneteket kézbesítõ szálat.
	 */
	void stop();
};

#endif /* INC_MESSAGESENDER_H_ */

