#ifndef INC_CONTROLMESSAGE_H_
#define INC_CONTROLMESSAGE_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/BaseMessage.h>

/**
 * @class ControlMessage
 * @brief Vez�rl� �zenet.
 *
 * A vez�rl� modul ezzel az �zenettel jelzi az elv�gzend�
 * m�veleteket a h�m�rs�klet szab�lyoz�s�hoz.
 */
class ControlMessage : public BaseMessage {
public:
	/**
	 * A ventil�tort �rint� �zenetet jel�l� konstans.
	 */
	static const int FAN_CONTROL;

	/**
	 * A f�t�sz�lat �rint� �zenetet jel�l� konstans.
	 */
	static const int HEATER_CONTROL;

private:
	/**
	 * Az �zenet t�pusa.
	 */
	int messageType;

	/**
	 * A beavatkoz� jel �rt�ke.
	 */
	bool value;

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
	 * @param temp A beavatkoz� jel �rt�ke.
	 */
	ControlMessage(const int type, const bool val);
	
	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~ControlMessage();

	/**
	 * @brief Lek�ri az �zenet t�pus�t.
	 *
	 * @return Az �zenet t�pus�t jelz� sz�m�rt�k.
	 */
	int getMessageType() const;

	/**
	 * @brief Lek�ri az �zenetben t�rolt beavatkoz� jelet.
	 *
	 * @return A k�t�llapot� beavatkoz� jel.
	 */
	bool getControlValue() const;
};

#endif /* INC_CONTROLMESSAGE_H_ */