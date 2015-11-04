#include <lib/app/inc/core/BaseMessage.h>
#include <lib/app/inc/core/MessageReceiver.h>

/*
 * Az oszály alapértelmezett konstruktora.
 */
BaseMessage::BaseMessage() : created(std::chrono::system_clock::now()), sent(false) {}

/*
 * Az osztály virtuális destruktora.
 */
BaseMessage::~BaseMessage() {}

/*
 * Átadja az ebbõl az osztályból példányosított objektumot az
 * üzenetet fogadó objektumnak feldolgozásra.
 */
void BaseMessage::send(MessageReceiver& receiver) const {
	receiver.receiveMessage(*this);
}

/*
 * Módosítja az üzenet állapotát kézbesítettre.
 */
void BaseMessage::setSent() {
	std::unique_lock<std::mutex> lock(mutex);
	sent = true;
	cv.notify_all();
}

/*
 * Beállítja az üzenet kivételre mutató pointerét az átadott kivétel
 * objektumra.
 */
void BaseMessage::setException(std::exception_ptr _eptr) {
	std::unique_lock<std::mutex> lock(mutex);
	sent = true;
	eptr = _eptr;
}

/*
 * Felfüggeszti a szál futását az üzenet kézbesítéséig.
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
