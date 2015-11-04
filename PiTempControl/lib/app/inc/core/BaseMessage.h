#ifndef INC_MESSAGEBASE_H_
#define INC_MESSAGEBASE_H_

#include <lib/app/inc/common.h>

class MessageReceiver;
class MessageSender;

/**
* @class BaseMessage
* @brief Az �zenetek �soszt�lya.
*
* Az alkalmaz�son bel�l a modulok k�z�tti kommunik�ci�t megval�s�t� �zenetek
* mindegyike ebb�l az oszt�lyb�l sz�rmazik.
*/
class BaseMessage {
	/**
	 * Teljesk�r� hozz�f�r�s biztos�t�sa a priv�t adattagokhoz �s priv�t
	 * met�dusokhoz a MessageSender oszt�ly sz�m�ra.
	 */
	friend class MessageSender;

private:
	/**
	 * Az �zenet l�trehoz�s�nak pillanata.
	 */
	std::chrono::system_clock::time_point created;

	/**
	 * Az �zenet k�zbes�t�s�nek �llapota.
	 */
	std::atomic_bool sent;

	/**
	 * Az �zenet k�zbes�t�s�nek kiv�r�s�hoz haszn�lt �llapotv�ltoz�.
	 */
	std::condition_variable cv;

	/**
	 * A t�bb sz�lr�l val� egyidej� hozz�f�r�st kiz�r� adattag.
	 */
	std::mutex mutex;

	/**
	 * Hiba eset�n a kiv�tel objektumra mutat� pointer, amivel az
	 * objektum �tadhat� ak�r egy m�sik sz�lon fut� kiv�telkezel�nek is.
	 */
	std::exception_ptr eptr;

	/**
	 * @brief Az oszt�ly m�sol� konstruktor�nak tilt�sa.
	 */
	BaseMessage(const BaseMessage&) = delete;

	/**
	 * @brief Az oszt�ly �rt�kad� oper�tor�nak tilt�sa.
	 */
	BaseMessage& operator=(const BaseMessage&) = delete;

protected:
	/**
	 * @brief Az osz�ly alap�rtelmezett konstruktora.
	 */
	BaseMessage();

	/**
	 * @brief Az oszt�ly virtu�lis destruktora.
	 */
	virtual ~BaseMessage();

private:
	/**
	 * @brief �tadja az ebb�l az oszt�lyb�l p�ld�nyos�tott objektumot
	 * az �zenetet fogad� objektumnak feldolgoz�sra.
	 *
	 * @param receiver Az �zenetet fogad� objektumra mutat� referencia.
	 */
	virtual void send(MessageReceiver& receiver) const;

	/**
	 * @brief M�dos�tja az �zenet �llapot�t k�zbes�tettre.
	 *
	 * Amennyiben az �zenetet k�zbes�t� sz�l v�rakozik, a met�dus megh�v�sa
	 * feloldja a v�rakoz�st.
	 */
	void setSent();

	/**
	 * @brief Be�ll�tja az �zenet kiv�telre mutat� pointer�t az �tadott
	 * kiv�tel objektumra.
	 *
	 * @param _eptr A kiv�tel objektumra mutat� kiv�tel pointer.
	 */
	void setException(std::exception_ptr _eptr);

public:
	/**
	 * @brief Felf�ggeszti a sz�l fut�s�t az �zenet k�zbes�t�s�ig.
	 */
	void waitFor();
};

#endif /* INC_MESSAGEBASE_H_ */

