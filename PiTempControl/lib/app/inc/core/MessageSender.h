#ifndef INC_MESSAGESENDER_H_
#define INC_MESSAGESENDER_H_

#include <lib/app/inc/common.h>

class BaseMessage;
class MessageReceiver;

/**
 * @class MessageSender
 * @brief Az �zenetek k�zbes�t�s�t lebonyol�t� oszt�ly.
 *
 * Az elk�ldeni k�v�nt �zeneteket egy v�rakoz�si sorba gy�jti, majd
 * azokat a felv�tel sorrendj�ben �tadja a feliratkozott fogad�knak.
 */
class MessageSender {
	/**
	 * Teljesk�r� hozz�f�r�s biztos�t�sa a priv�t adattagokhoz �s priv�t
	 * met�dusokhoz a TemperatureControllerApplication oszt�ly sz�m�ra.
	 */
	friend class TemperatureControllerApplication;

private:
	/**
	 * A feliratkozott fogad�k list�ja.
	 */
	std::list<MessageReceiver*> receivers;

	/**
	 * A elk�ldeni k�v�nt �zenetek v�rakoz�si sora.
	 */
	std::queue<std::shared_ptr<BaseMessage>> messages;

	/**
	 * Az �zeneteket k�zbes�t� sz�l fut�s�nak �llapota.
	 */
	std::atomic_bool active;

	/**
	 * A t�bb sz�lr�l val� egyidej� hozz�f�r�st kiz�r� adattag.
	 */
	std::recursive_mutex mutex;

	/**
	 * Az �zeneteket k�zbes�t� sz�l le�ll�t�sakor haszn�lt k�lcs�n�s
	 * kiz�r�st biztos�t� adattag.
	 */
	std::recursive_mutex joinMutex;

	/**
	 * �j �zenetek �rkez�s�nek kiv�r�s�hoz haszn�lt �llapotv�ltoz�.
	 */
	std::condition_variable_any cv;

	/**
	 * Az �zeneteket k�zbes�t� sz�l kezel�s�t biztos�t� adattag.
	 */
	std::thread thread;

	/**
	 * @brief Az osz�ly alap�rtelmezett konstruktora.
	 */
	MessageSender();

	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~MessageSender();

	/**
	 * @brief Elhelyezi az elk�ldeni k�v�nt �zenetet a v�rakoz�si sorba �s
	 * jelez az �zeneteket k�zbes�t� sz�lnak, hogy folytathatja a v�rakoz�si
	 * sorban lev� �zenetek k�zbes�t�s�t.
	 *
	 * @param message Az elk�ldeni k�v�nt �zenetre mutat� megosztott
	 * pointer.
	 */
	void sendMessage(std::shared_ptr<BaseMessage> message);

	/**
	 * @brief K�zbes�ti az �tadott �zenetet a feliratkozott fogad�knak.
	 *
	 * Az �zenet minden egyes feliratkozott fogad�hoz eljut, de csak az
	 * fogja feldolgozni, amelyik fel�ldefini�lta az �zenet t�pus�nak
	 * megfelel� virtu�lis fogad� met�dust. 
	 *
	 * @param message A k�zbes�teni k�v�nt �zenet.
	 */
	void passMessage(BaseMessage& message);

	/**
	 * @brief Felveszi az �tadott fogad�t a feliratkozott fogad�k k�z�.
	 *
	 * @param receiver A felvenni k�v�nt fogad�.
	 */
	void registerMessageReceiver(MessageReceiver& receiver);

	/**
	 * @brief A futtat� sz�lat felf�ggesztve figyeli a v�rakoz�si sort.
	 * Amennyiben �j �zenetek ker�lnek a v�rakoz�si sorba, k�zbes�ti
	 * azokat, majd folytatja az �j �zenetek �rkez�s�nek figyel�st.
	 */
	void messageHandler();

	/**
	 * @brief Elind�tja a �zeneteket k�zbes�t� sz�lat.
	 */
	void start();

	/**
	 * @brief Le�ll�tja a �zeneteket k�zbes�t� sz�lat.
	 */
	void stop();
};

#endif /* INC_MESSAGESENDER_H_ */

