#ifndef INC_SETUPMESSAGE_H_
#define INC_SETUPMESSAGE_H_

#include <lib/app/inc/common.h>
#include <lib/app/inc/core/BaseMessage.h>

/**
 * @class SetupMessage
 * @brief Be�ll�t� �zenet.
 *
 * A bemeneteket kezel� modul (ebben az esetben maga az alkalmaz�s)
 * ezzel az �zenettel jelzi a param�terek megv�ltoz�s�t.
 */
class SetupMessage : public BaseMessage {
public:
	/**
	 * Az alapjelet megv�ltoztat� �zenetet jel�l� konstans.
	 */
	static const int CHANGE_SETPOINT;

	/**
	 * A megengedett p�lyak�vet�si hib�t megv�ltoztat� �zenetet
	 * jel�l� konstans.
	 */
	static const int CHANGE_ERROR_LIMIT;

private:
	/**
	 * Az �zenet t�pusa.
	 */
	int messageType;

	/**
	 * A be�ll�tand� �j �rt�k.
	 */
	float value;

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
	 * @param temp A be�ll�tand� �j �rt�k.
	 */
	SetupMessage(const int type, const float val);

	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~SetupMessage();

	/**
	 * @brief Lek�ri az �zenet t�pus�t.
	 *
	 * @return Az �zenet t�pus�t jelz� sz�m�rt�k.
	 */
	int getMessageType() const;

	/**
	 * @brief Lek�ri az �zenetben t�rolt be�ll�t�s �rt�k�t.
	 *
	 * @return A be�ll�tand� �j �rt�k.
	 */
	float getSetupValue() const;
};

#endif /* INC_SETUPMESSAGE_H_ */