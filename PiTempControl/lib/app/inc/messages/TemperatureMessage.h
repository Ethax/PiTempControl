#ifndef INC_TEMPERATUREMESSAGE_H
#define INC_TEMPERATUREMESSAGE_H

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/BaseMessage.h>

/**
 * @class TemperatureMessage
 * @brief Hõmérséklet üzenet.
 *
 * A hõmérõl modul ezzel az üzenettel jelzi az aktuális hõmérsékletet.
 */
class TemperatureMessage : public BaseMessage {
public:
	/**
	 * Az üzenet típusát jelzõ konstans.
	 */
	static const int ACTUAL_TEMPERATURE;

private:
	/**
	 * Az üzenet típusa.
	 */
	int messageType;

	/**
	 * Az aktuális hõmérséklet Celsius fokokban.
	 */
	float temperature;

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
	 * @param temp A mért hõmérséklet Celsius fokokban.
	 */
	TemperatureMessage(const int type, const float temp);
	
	/**
	 * @brief Az osztály virtuális destruktora.
	 */
	virtual ~TemperatureMessage();

	/**
	 * @brief Lekéri az üzenet típusát.
	 *
	 * @return Az üzenet típusát jelzõ számérték.
	 */
	int getMessageType() const;

	/**
	 * @brief Lekéri az üzenetben tárolt hõmérsékletet.
	 *
	 * @return Az aktuális hõmérséklet Celsius fokokban. 
	 */
	float getTemperature() const;
};

#endif /* INC_TEMPERATUREMESSAGE_H */