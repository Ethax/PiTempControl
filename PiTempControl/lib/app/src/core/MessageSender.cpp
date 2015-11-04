#include <lib/app/inc/core/MessageSender.h>
#include <lib/app/inc/core/BaseMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az oszály alapértelmezett konstruktora.
 */
MessageSender::MessageSender() : active(false) {}

/*
 * Az osztály virtuális destruktora.
 */
MessageSender::~MessageSender() {}

/*
 * Elhelyezi az elküldeni kívánt üzenetet a várakozási sorba és jelez
 * az üzeneteket kézbesítõ szálnak, hogy folytathatja a várakozási
 * sorban levõ üzenetek kézbesítését
 */
void MessageSender::sendMessage(std::shared_ptr<BaseMessage> message) {
	/* Az üzenet azonnali kézbesítése, amennyiben az üzenetet küldeni
	kívánó szál megegyezik az üzeneteket kézbesítõ szállal. */
	if(std::this_thread::get_id() == thread.get_id()) {
		passMessage(*message);
	}
	/* Minden egyéb esetben az új üzenet elhelyezése a várakozási sorba,
	majd az üzeneteket kézbesítõ szál értesítése és az üzenet
	kézbesítésének kivárása. */
	else {
		{
			std::unique_lock<std::recursive_mutex> lock(mutex);
			messages.push(message);
			cv.notify_all();
		}
		message->waitFor();
	}
}

/*
 * Kézbesíti az átadott üzenetet a feliratkozott fogadóknak.
 */
void MessageSender::passMessage(BaseMessage& message) {
	/* Az üzenet eljuttatásának megkísérlése minden egyes
	feliratkozott fogadónak. */
	try {
		for(std::list<MessageReceiver*>::iterator iter = receivers.begin(); iter != receivers.end(); iter++)
			message.send(**iter);
	}
	/* Hiba esetén a kivétel objektumra mutató pointer elhelyezése
	a kézbesíteni kívánt üzenetben. */
	catch(...) {
		message.setException(std::current_exception());
	}

	/* Az üzenet állapotának beállítása kézbesítettre. */
	message.setSent();
}

/*
 * Felveszi az átadott fogadót a feliratkozott fogadók közé.
 */
void MessageSender::registerMessageReceiver(MessageReceiver& receiver) {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	receivers.push_back(&receiver);
	cv.notify_all();
}

/*
 * A futtató szálat felfüggesztve figyeli a várakozási sort. Amennyiben
 * új üzenetek kerülnek a várakozási sorba, kézbesíti azokat, majd
 * folytatja az új üzenetek érkezésének figyelést.
 */
void MessageSender::messageHandler() {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	while(true) {
		/* A várakozási sorban levõ üzenetek kézbesítése. */
		while(!messages.empty()) {
			auto message = messages.front();
			passMessage(*message);
			messages.pop();
		}

		/* Az új üzenetek érkezésére váró végtelen ciklus megszakítása,
		ha a kézbesítõ nem aktív. */
		if(!active) break;
		
		/* A futtató szál futásának felfüggesztése új üzenetek
		érkezéséig. */
		cv.wait(lock);
	}
}

/*
 * Elindítja a üzeneteket kézbesítõ szálat.
 */
void MessageSender::start() {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	if(active) return;
	
	/* Az üzeneteket kézbesítõ szál aktiválása és elindítása. */
	active = true;
	thread = std::thread(&MessageSender::messageHandler, this);
}

/*
 * Leállítja a üzeneteket kézbesítõ szálat.
 */
void MessageSender::stop() {
	std::unique_lock<std::recursive_mutex> joinLock(joinMutex);
	{
		std::unique_lock<std::recursive_mutex> lock(mutex);
		if(!active)	return;
		
		/* Az üzeneteket kézbesítõ szál deaktiválása és felébresztése a
		várakozásból a megfelelõ leállás érdekében. */
		active = false;
		cv.notify_all();
	}

	/* Az üzeneteket kézbesítõ szál leállásának kivárása. */
	if(thread.joinable())
		thread.join();
}
