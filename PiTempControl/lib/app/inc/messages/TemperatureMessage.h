#ifndef INC_TEMPERATUREMESSAGE_H
#define INC_TEMPERATUREMESSAGE_H

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/BaseMessage.h>

/**
 * @class TemperatureMessage
 * @brief H�m�rs�klet �zenet.
 *
 * A h�m�r�l modul ezzel az �zenettel jelzi az aktu�lis h�m�rs�kletet.
 */
class TemperatureMessage : public BaseMessage {
public:
	/**
	 * Az �zenet t�pus�t jelz� konstans.
	 */
	static const int ACTUAL_TEMPERATURE;

private:
	/**
	 * Az �zenet t�pusa.
	 */
	int messageType;

	/**
	 * Az aktu�lis h�m�rs�klet Celsius fokokban.
	 */
	float temperature;

	/**
	 * @brief �tadja az ebb�l az oszt�lyb�l p�ld�nyos�tott objektumot
	 * az �zenetet fogad� objektumnak feldolgoz�sra.
	 *
	 * @param receiver Az �zenetet fogad� objektumra mutat� referencia.
	 */
	virtual void send(MessageReceiver& receiver) const;

public:
	/**
	 * @brief Az osz�ly konstruktora.
	 *
	 * @param type Az �zenet t�pusa.
	 * @param temp A m�rt h�m�rs�klet Celsius fokokban.
	 */
	TemperatureMessage(const int type, const float temp);
	
	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~TemperatureMessage();

	/**
	 * @brief Lek�ri az �zenet t�pus�t.
	 *
	 * @return Az �zenet t�pus�t jelz� sz�m�rt�k.
	 */
	int getMessageType() const;

	/**
	 * @brief Lek�ri az �zenetben t�rolt h�m�rs�kletet.
	 *
	 * @return Az aktu�lis h�m�rs�klet Celsius fokokban. 
	 */
	float getTemperature() const;
};

#endif /* INC_TEMPERATUREMESSAGE_H */