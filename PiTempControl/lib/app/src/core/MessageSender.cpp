#include <lib/app/inc/core/MessageSender.h>
#include <lib/app/inc/core/BaseMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az osz�ly alap�rtelmezett konstruktora.
 */
MessageSender::MessageSender() : active(false) {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
MessageSender::~MessageSender() {}

/*
 * Elhelyezi az elk�ldeni k�v�nt �zenetet a v�rakoz�si sorba �s jelez
 * az �zeneteket k�zbes�t� sz�lnak, hogy folytathatja a v�rakoz�si
 * sorban lev� �zenetek k�zbes�t�s�t
 */
void MessageSender::sendMessage(std::shared_ptr<BaseMessage> message) {
	/* Az �zenet azonnali k�zbes�t�se, amennyiben az �zenetet k�ldeni
	k�v�n� sz�l megegyezik az �zeneteket k�zbes�t� sz�llal. */
	if(std::this_thread::get_id() == thread.get_id()) {
		passMessage(*message);
	}
	/* Minden egy�b esetben az �j �zenet elhelyez�se a v�rakoz�si sorba,
	majd az �zeneteket k�zbes�t� sz�l �rtes�t�se �s az �zenet
	k�zbes�t�s�nek kiv�r�sa. */
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
 * K�zbes�ti az �tadott �zenetet a feliratkozott fogad�knak.
 */
void MessageSender::passMessage(BaseMessage& message) {
	/* Az �zenet eljuttat�s�nak megk�s�rl�se minden egyes
	feliratkozott fogad�nak. */
	try {
		for(std::list<MessageReceiver*>::iterator iter = receivers.begin(); iter != receivers.end(); iter++)
			message.send(**iter);
	}
	/* Hiba eset�n a kiv�tel objektumra mutat� pointer elhelyez�se
	a k�zbes�teni k�v�nt �zenetben. */
	catch(...) {
		message.setException(std::current_exception());
	}

	/* Az �zenet �llapot�nak be�ll�t�sa k�zbes�tettre. */
	message.setSent();
}

/*
 * Felveszi az �tadott fogad�t a feliratkozott fogad�k k�z�.
 */
void MessageSender::registerMessageReceiver(MessageReceiver& receiver) {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	receivers.push_back(&receiver);
	cv.notify_all();
}

/*
 * A futtat� sz�lat felf�ggesztve figyeli a v�rakoz�si sort. Amennyiben
 * �j �zenetek ker�lnek a v�rakoz�si sorba, k�zbes�ti azokat, majd
 * folytatja az �j �zenetek �rkez�s�nek figyel�st.
 */
void MessageSender::messageHandler() {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	while(true) {
		/* A v�rakoz�si sorban lev� �zenetek k�zbes�t�se. */
		while(!messages.empty()) {
			auto message = messages.front();
			passMessage(*message);
			messages.pop();
		}

		/* Az �j �zenetek �rkez�s�re v�r� v�gtelen ciklus megszak�t�sa,
		ha a k�zbes�t� nem akt�v. */
		if(!active) break;
		
		/* A futtat� sz�l fut�s�nak felf�ggeszt�se �j �zenetek
		�rkez�s�ig. */
		cv.wait(lock);
	}
}

/*
 * Elind�tja a �zeneteket k�zbes�t� sz�lat.
 */
void MessageSender::start() {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	if(active) return;
	
	/* Az �zeneteket k�zbes�t� sz�l aktiv�l�sa �s elind�t�sa. */
	active = true;
	thread = std::thread(&MessageSender::messageHandler, this);
}

/*
 * Le�ll�tja a �zeneteket k�zbes�t� sz�lat.
 */
void MessageSender::stop() {
	std::unique_lock<std::recursive_mutex> joinLock(joinMutex);
	{
		std::unique_lock<std::recursive_mutex> lock(mutex);
		if(!active)	return;
		
		/* Az �zeneteket k�zbes�t� sz�l deaktiv�l�sa �s fel�breszt�se a
		v�rakoz�sb�l a megfelel� le�ll�s �rdek�ben. */
		active = false;
		cv.notify_all();
	}

	/* Az �zeneteket k�zbes�t� sz�l le�ll�s�nak kiv�r�sa. */
	if(thread.joinable())
		thread.join();
}
