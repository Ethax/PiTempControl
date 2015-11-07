#ifndef INC_SHT7XCOMM_H_
#define INC_SHT7XCOMM_H_ 

#include <bcm2835.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @class SHT7xComm
 * @brief A SENSIRION SHT7x digit�lis h�m�rs�klet �s p�ratartalom
 * �rz�kel�k kezel�s�t megval�s�t� oszt�ly.
 *
 * A forr�sf�jban lev� konstansok m�dos�t�s�val az oszt�ly teljes
 * m�rt�kben haszn�lhat� az SHT1x �rz�kel�k kezel�s�re is. A konstansok
 * az adott �rz�kel� adatlapj�r�l kiolvashat�ak.
 */
class SHT7xComm {
public:
	/**
	 * A m�rhet� jellemz�k felsorol�sa.
	 */
	enum MeasureCommands {
		MEASURE_TEMPERATURE = 0x03,
		MEASURE_HUMIDITY = 0x05
	};

private:
	/**
	 * Az ellen�rz� �sszeg t�rol�s�ra szolg�l� adattag.
	 */
	unsigned char checksum;

	/**
	 * Az �rz�kel� �llapotregiszter�nek t�rol�s�ra szolg�l� adattag.
	 */
	unsigned char statusReg;

	/**
	 * A kommunik�ci�s vonalak be�ll�totts�g�t t�rol� jelz�bit.
	 */
	bool isInitialized;

	/**
	 * A soros �rajel-kimenet csatlakoz�j�nak azonos�t�j�t t�rol�
	 * adattag.
	 */
	RPiGPIOPin SHT7x_SCK;

	/**
	 * A k�tir�ny� adat-csatlakoz� azonos�t�j�t t�rol� adattag.
	 */
	RPiGPIOPin SHT7x_DATA;

	/**
	 * Az �rt�kel� be�ll�t�s szint� kezel�s�hez haszn�lhat� utas�t�sok
	 * felsorol�sa.
	 */
	enum Commands {
		READ_STATUS = 0x07,
		WRITE_STATUS = 0x06,
		SOFT_RESET = 0x1E
	};

	/**
	 * @brief Be�ll�tja az SCK vonal logikai szintj�t.
	 *
	 * @param level A be�ll�tani k�v�nt logikai szint.
	 */
	inline void setSCKLevel(unsigned char level) {
		bcm2835_gpio_write(SHT7x_SCK, level); delayMicroseconds(2);
	}

	/**
	 * @brief Be�ll�tja a DATA vonal logikai szintj�t �s adatir�ny�t.
	 *
	 * @param level A be�ll�tani k�v�nt logikai szint.
	 */
	inline void setDATALevel(unsigned char level) {
		if(level == LOW) {
			bcm2835_gpio_write(SHT7x_DATA, LOW);
			bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_OUTP); delayMicroseconds(2);
		}
		else {
			bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_INPT); delayMicroseconds(2);
		}
	}

	/**
	 * @brief Lek�rdezi a DATA vonal logikai szintj�t.
	 *
	 * @return A DATA vonal logikai szintje.
	 */
	inline unsigned char getDATALevel() {
		return bcm2835_gpio_lev(SHT7x_DATA);
	}
	
	/**
	 * @brief Kisz�molja az ellen�z� �sszeget �s az eredm�nyt elt�rolja
	 * az osz�ly priv�t adattagj�ban. A CRC polinomja:
	 * P(x) = x^8 + x^5 + x^4 + x^0
	 *
	 * @param value Az az �rt�k, amire az ellen�rz� �sszeg ki lesz
	 * sz�m�tva.
	 */
	void calculateChecksum(unsigned char value);

	/**
	 * @brief T�kr�zi az �tadott b�jtot.
	 *
	 * @param A t�kr�zni k�v�nt egyb�jtos �rt�k.
	 * @return A t�kr�z�tt egyb�jtos �rt�k.
	 */
	unsigned char mirrorByte(unsigned char value);

	/**
	 * @brief Inicializ�lja a kommunik�ci�t az �rz�kel�vel a Transmission
	 * Start sorozat kik�ld�s�vel.
	 */
	void transmissionStart();

	/**
	 * @brief Kiolvas egy egyb�jtos adatot az �rz�kel�b�l �s a megatott
	 * param�tert�l f�gg�en nyugt�zza az olvas�st.
	 *
	 * @param send_ack Ha az �rt�ke IGAZ, akkor nyugt�zza az olvas�st.
	 */
	unsigned char readByte(bool send_ack = true);

	/**
	 * @brief Elk�ld egy egyb�jtos adatot az �rz�kel�nek �s visszaadja
	 * az �rz�kel�t�l �rkez� nyugt�t.
	 *
	 * @param value Az elk�ldeni k�v�nt adat.
	 * @return Ha az �rt�ke IGAZ, akkor az �rz�kel� nyugt�zta az adat
	 * fogad�s�t.
	 */
	bool sendByte(unsigned char value);

public:
	/**
	 * @biref Az osz�ly alap�rtelmezett konstruktora.
	 */
	SHT7xComm();

	/**
	 * @brief Az oszt�ly destruktora.
	 */
	~SHT7xComm();

	/**
	 * @brief Inicializ�lja az �rz�kel�vel �sszek�t�tt kommunik�ci�s
	 * vonalakat.
	 *
	 * @param _SCK_Pin A soros �rajel-kimenet csatlakoz�j�nak
	 * azonos�t�ja.
	 * @param _DATA_Pin A k�tir�ny� adat-csatlakoz� azonos�t�ja.
	 */
	void initializePins(RPiGPIOPin _SCK_Pin, RPiGPIOPin _DATA_Pin);

	/**
	 * @brief Alaphelyzetbe �ll�tja Az �rz�kel�t a Connection Reset
	 * sorozat �s a Soft Reset utas�t�s kik�ld�s�vel.
	 */
	void reset();

	/**
	 * @brief Utas�t�ja az �rz�kel�t a megadott jellemz� (h�m�rs�klet
	 * vagy p�ratartalom) megm�r�s�re.
	 *
	 * @param type A m�rni k�v�nt jellemz�.
	 * @return Ha az �rt�ke IGAZ, akkor az �rz�kel� nyugt�zta a k�r�s
	 * fogad�s�t.
	 */
	bool measureStart(MeasureCommands type);

	/**
	 * @biref Kiolvassa a legut�bbi m�r�s eredm�ny�t az �rz�kel�b�l �s
	 * elv�gzi az adaton a CRC-t.
	 *
	 * @return Az �rz�kel� �ltal m�rt jellemz� nyers �rt�ke.
	 */
	unsigned short int getMeasureValue();

	/**
	 * @brief Az �rz�kel�t�l sz�rmaz� nyers h�m�rs�klet �s p�ratartalom
	 * �rt�kekb�l kisz�m�tja azok val�s �rt�keit.
	 *
	 * A sz�m�t�sok 3,3V t�pl�l�sra �s alap�rtelmezett felbont�sra lettek
	 * be�ll�tva. Amennyiben ezen param�terek valamelyike is elt�r, a
	 * pontos eredm�ny �rdek�ben m�dos�tani kell a forr�sf�jlt az �rz�kel�
	 * adatlapj�r�l kiolvashat� t�bl�zati �rt�keknek megfelel�en.
	 *
	 * @param humidity Az �tsz�m�tani k�v�nt p�ratartalom �rt�kre mutat�
	 * referencia.
	 * @param temperature Az �tsz�m�tani k�v�nt h�m�rs�klet �rt�kre mutat�
	 * referencia.
	 */
	void correctMeasuredValues(float& humidity, float& temperature);

	/*
	 * @brief Lez�rja a kommunik�ci�t az �rz�kel�vel.
	 */
	void close();
};

#endif /* INC_SHT7XCOMM_H_ */
