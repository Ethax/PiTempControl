#ifndef INC_CONTROLMESSAGE_H_
#define INC_CONTROLMESSAGE_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/BaseMessage.h>

/**
 * @class ControlMessage
 * @brief Vezérlõ üzenet.
 *
 * A vezérlõ modul ezzel az üzenettel jelzi az elvégzendõ
 * mûveleteket a hõmérséklet szabályozásához.
 */
class ControlMessage : public BaseMessage {
public:
	/**
	 * A ventilátort érintõ üzenetet jelölõ konstans.
	 */
	static const int FAN_CONTROL;

	/**
	 * A fûtõszálat érintõ üzenetet jelölõ konstans.
	 */
	static const int HEATER_CONTROL;

private:
	/**
	 * Az üzenet típusa.
	 */
	int messageType;

	/**
	 * A beavatkozó jel értéke.
	 */
	bool value;

	/**
	 * @brief Átadja az ebbõl az osztályból példányosított objektumot
	 * az üzenetet fogadó objektumnak feldolgozásra.
	 *
	 * @param receiver Az üzenetet fogadó objektumra mutató referencia.
	 */
	virtual void send(MessageReceiver& receiver) const;

public:
	/**
	 * @brief Az oszály konstruktora.
	 *
	 * @param type Az üzenet típusa.
	 * @param temp A beavatkozó jel értéke.
	 */
	ControlMessage(const int type, const bool val);
	
	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~ControlMessage();

	/**
	 * @brief Lekéri az üzenet típusát.
	 *
	 * @return Az üzenet típusát jelzõ számérték.
	 */
	int getMessageType() const;

	/**
	 * @brief Lekéri az üzenetben tárolt beavatkozó jelet.
	 *
	 * @return A kétállapotú beavatkozó jel.
	 */
	bool getControlValue() const;
};

#endif /* INC_CONTROLMESSAGE_H_ */