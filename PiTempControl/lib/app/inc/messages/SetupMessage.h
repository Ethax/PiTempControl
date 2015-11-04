#ifndef INC_SETUPMESSAGE_H_
#define INC_SETUPMESSAGE_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/BaseMessage.h>

/**
 * @class SetupMessage
 * @brief Beállító üzenet.
 *
 * A bemeneteket kezelõ modul (ebben az esetben maga az alkalmazás)
 * ezzel az üzenettel jelzi a paraméterek megváltozását.
 */
class SetupMessage : public BaseMessage {
public:
	/**
	 * Az alapjelet megváltoztató üzenetet jelölõ konstans.
	 */
	static const int CHANGE_SETPOINT;

	/**
	 * A megengedett pályakövetési hibát megváltoztató üzenetet
	 * jelölõ konstans.
	 */
	static const int CHANGE_ERROR_LIMIT;

private:
	/**
	 * Az üzenet típusa.
	 */
	int messageType;

	/**
	 * A beállítandó új érték.
	 */
	float value;

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
	 * @param temp A beállítandó új érték.
	 */
	SetupMessage(const int type, const float val);

	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~SetupMessage();

	/**
	 * @brief Lekéri az üzenet típusát.
	 *
	 * @return Az üzenet típusát jelzõ számérték.
	 */
	int getMessageType() const;

	/**
	 * @brief Lekéri az üzenetben tárolt beállítás értékét.
	 *
	 * @return A beállítandó új érték.
	 */
	float getSetupValue() const;
};

#endif /* INC_SETUPMESSAGE_H_ */