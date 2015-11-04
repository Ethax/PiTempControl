#include <lib/app/inc/core/BaseMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az osz�ly alap�rtelmezett konstruktora.
 */
BaseMessage::BaseMessage() : created(std::chrono::system_clock::now()), sent(false) {}

/*
 * Az oszt�ly virtu�lis destruktora.
 */
BaseMessage::~BaseMessage() {}

/*
 * �tadja az ebb�l az oszt�lyb�l p�ld�nyos�tott objektumot az
 * �zenetet fogad� objektumnak feldolgoz�sra.
 */
void BaseMessage::send(MessageReceiver& receiver) const {
	receiver.receiveMessage(*this);
}

/*
 * M�dos�tja az �zenet �llapot�t k�zbes�tettre.
 */
void BaseMessage::setSent() {
	std::unique_lock<std::mutex> lock(mutex);
	sent = true;
	cv.notify_all();
}

/*
 * Be�ll�tja az �zenet kiv�telre mutat� pointer�t az �tadott kiv�tel
 * objektumra.
 */
void BaseMessage::setException(std::exception_ptr _eptr) {
	std::unique_lock<std::mutex> lock(mutex);
	sent = true;
	eptr = _eptr;
}

/*
 * Felf�ggeszti a sz�l fut�s�t az �zenet k�zbes�t�s�ig.
 */
void BaseMessage::waitFor() {
	std::unique_lock<std::mutex> lock(mutex);
	if(sent && !eptr)
		return;
	if(!sent)
		cv.wait(lock);
	if(eptr)
		std::rethrow_exception(eptr);
}
