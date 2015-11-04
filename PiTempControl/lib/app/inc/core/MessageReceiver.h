#ifndef INC_MESSAGEHANDLER_H_
#define INC_MESSAGEHANDLER_H_

#include <lib/app/inc/common.h>

class MessageSender;
class BaseMessage;
class TemperatureMessage;
class ControlMessage;
class SetupMessage;

/**
 * @class MessageReceiver
 * @brief Az �zeneteket fogadni k�pes oszt�lyok �soszt�lya.
 *
 * Minden olyan oszt�ly, amelyik megval�s�tja valamelyik �zenet fogad�s�t,
 * ebb�l az oszt�lyb�l sz�rmazik �s fel�ldefini�lja a megfelel� �zenetet
 * fogad� virtu�lis met�dust.
 */
class MessageReceiver {
	/**
	 * Teljesk�r� hozz�f�r�s biztos�t�sa a priv�t adattagokhoz �s priv�t
	 * met�dusokhoz a MessageSender oszt�ly sz�m�ra.
	 */
	friend class MessageSender;

	/**
	 * Teljesk�r� hozz�f�r�s biztos�t�sa a priv�t adattagokhoz �s priv�t
	 * met�dusokhoz a BaseMessage oszt�ly sz�m�ra.
	 */
	friend class BaseMessage;

private:
	/**
	 * @brief Az oszt�ly m�sol� konstruktor�nak tilt�sa.
	 */
	MessageReceiver(const MessageReceiver&) = delete;
	
	/**
	 * @brief Az oszt�ly �rt�kad� oper�tor�nak tilt�sa.
	 */
	MessageReceiver& operator=(const MessageReceiver&) = delete;

protected:
	/**
	 * @brief Az osz�ly alap�rtelmezett konstruktora.
	 */
	MessageReceiver();
	
	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~MessageReceiver();

public:
	/**
	 * @brief Fogadja �s feldolgozza az �tadott BaseMessage t�pus�
	 * �zenetet.
	 *
	 * @param msg A fogadni �s feldolgozni k�v�nt �zenet.
	 */
	virtual void receiveMessage(const BaseMessage& msg);

	/**
	 * @brief Fogadja �s feldolgozza az �tadott TemperatureMessage
	 * t�pus� �zenetet.
	 *
	 * @param msg A fogadni �s feldolgozni k�v�nt �zenet.
	 */
	virtual void receiveMessage(const TemperatureMessage& msg);

	/**
	 * @brief Fogadja �s feldolgozza az �tadott ControlMessage
	 * t�pus� �zenetet.
	 *
	 * @param msg A fogadni �s feldolgozni k�v�nt �zenet.
	 */
	virtual void receiveMessage(const ControlMessage& msg);

	/**
	 * @brief Fogadja �s feldolgozza az �tadott SetupMessage
	 * t�pus� �zenetet.
	 *
	 * @param msg A fogadni �s feldolgozni k�v�nt �zenet.
	 */
	virtual void receiveMessage(const SetupMessage& msg);
};

#endif /* INC_MESSAGEHANDLER_H_ */