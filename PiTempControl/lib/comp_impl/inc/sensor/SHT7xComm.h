#ifndef INC_SHT7XCOMM_H_
#define INC_SHT7XCOMM_H_ 

#include <bcm2835.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @class SHT7xComm
 * @brief A SENSIRION SHT7x digitális hõmérséklet és páratartalom
 * érzékelõk kezelését megvalósító osztály.
 *
 * A forrásfájban levõ konstansok módosításával az osztály teljes
 * mértékben használható az SHT1x érzékelõk kezelésére is. A konstansok
 * az adott érzékelõ adatlapjáról kiolvashatóak.
 */
class SHT7xComm {
public:
	/**
	 * A mérhetõ jellemzõk felsorolása.
	 */
	enum MeasureCommands {
		MEASURE_TEMPERATURE = 0x03,
		MEASURE_HUMIDITY = 0x05
	};

private:
	/**
	 * Az ellenõrzõ összeg tárolására szolgáló adattag.
	 */
	unsigned char checksum;

	/**
	 * Az érzékelõ állapotregiszterének tárolására szolgáló adattag.
	 */
	unsigned char statusReg;

	/**
	 * A kommunikációs vonalak beállítottságát tároló jelzõbit.
	 */
	bool isInitialized;

	/**
	 * A soros órajel-kimenet csatlakozójának azonosítóját tároló
	 * adattag.
	 */
	RPiGPIOPin SHT7x_SCK;

	/**
	 * A kétirányú adat-csatlakozó azonosítóját tároló adattag.
	 */
	RPiGPIOPin SHT7x_DATA;

	/**
	 * Az értékelõ beállítás szintû kezeléséhez használható utasítások
	 * felsorolása.
	 */
	enum Commands {
		READ_STATUS = 0x07,
		WRITE_STATUS = 0x06,
		SOFT_RESET = 0x1E
	};

	/**
	 * @brief Beállítja az SCK vonal logikai szintjét.
	 *
	 * @param level A beállítani kívánt logikai szint.
	 */
	inline void setSCKLevel(unsigned char level) {
		bcm2835_gpio_write(SHT7x_SCK, level); delayMicroseconds(2);
	}

	/**
	 * @brief Beállítja a DATA vonal logikai szintjét és adatirányát.
	 *
	 * @param level A beállítani kívánt logikai szint.
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
	 * @brief Lekérdezi a DATA vonal logikai szintjét.
	 *
	 * @return A DATA vonal logikai szintje.
	 */
	inline unsigned char getDATALevel() {
		return bcm2835_gpio_lev(SHT7x_DATA);
	}
	
	/**
	 * @brief Kiszámolja az ellenõzõ összeget és az eredményt eltárolja
	 * az oszály privát adattagjában. A CRC polinomja:
	 * P(x) = x^8 + x^5 + x^4 + x^0
	 *
	 * @param value Az az érték, amire az ellenõrzõ összeg ki lesz
	 * számítva.
	 */
	void calculateChecksum(unsigned char value);

	/**
	 * @brief Tükrözi az átadott bájtot.
	 *
	 * @param A tükrözni kívánt egybájtos érték.
	 * @return A tükrözött egybájtos érték.
	 */
	unsigned char mirrorByte(unsigned char value);

	/**
	 * @brief Inicializálja a kommunikációt az érzékelõvel a Transmission
	 * Start sorozat kiküldésével.
	 */
	void transmissionStart();

	/**
	 * @brief Kiolvas egy egybájtos adatot az érzékelõbõl és a megatott
	 * paramétertõl függõen nyugtázza az olvasást.
	 *
	 * @param send_ack Ha az értéke IGAZ, akkor nyugtázza az olvasást.
	 */
	unsigned char readByte(bool send_ack = true);

	/**
	 * @brief Elküld egy egybájtos adatot az érzékelõnek és visszaadja
	 * az érzékelõtõl érkezõ nyugtát.
	 *
	 * @param value Az elküldeni kívánt adat.
	 * @return Ha az értéke IGAZ, akkor az érzékelõ nyugtázta az adat
	 * fogadását.
	 */
	bool sendByte(unsigned char value);

public:
	/**
	 * @biref Az oszály alapértelmezett konstruktora.
	 */
	SHT7xComm();

	/**
	 * @brief Az osztály destruktora.
	 */
	~SHT7xComm();

	/**
	 * @brief Inicializálja az érzékelõvel összekötött kommunikációs
	 * vonalakat.
	 *
	 * @param _SCK_Pin A soros órajel-kimenet csatlakozójának
	 * azonosítója.
	 * @param _DATA_Pin A kétirányú adat-csatlakozó azonosítója.
	 */
	void initializePins(RPiGPIOPin _SCK_Pin, RPiGPIOPin _DATA_Pin);

	/**
	 * @brief Alaphelyzetbe állítja Az érzékelõt a Connection Reset
	 * sorozat és a Soft Reset utasítás kiküldésével.
	 */
	void reset();

	/**
	 * @brief Utasítája az érzékelõt a megadott jellemzõ (hõmérséklet
	 * vagy páratartalom) megmérésére.
	 *
	 * @param type A mérni kívánt jellemzõ.
	 * @return Ha az értéke IGAZ, akkor az érzékelõ nyugtázta a kérés
	 * fogadását.
	 */
	bool measureStart(MeasureCommands type);

	/**
	 * @biref Kiolvassa a legutóbbi mérés eredményét az érzékelõbõl és
	 * elvégzi az adaton a CRC-t.
	 *
	 * @return Az érzékelõ által mért jellemzõ nyers értéke.
	 */
	unsigned short int getMeasureValue();

	/**
	 * @brief Az érzékelõtõl származó nyers hõmérséklet és páratartalom
	 * értékekbõl kiszámítja azok valós értékeit.
	 *
	 * A számítások 3,3V táplálásra és alapértelmezett felbontásra lettek
	 * beállítva. Amennyiben ezen paraméterek valamelyike is eltér, a
	 * pontos eredmény érdekében módosítani kell a forrásfájlt az érzékelõ
	 * adatlapjáról kiolvasható táblázati értékeknek megfelelõen.
	 *
	 * @param humidity Az átszámítani kívánt páratartalom értékre mutató
	 * referencia.
	 * @param temperature Az átszámítani kívánt hõmérséklet értékre mutató
	 * referencia.
	 */
	void correctMeasuredValues(float& humidity, float& temperature);

	/*
	 * @brief Lezárja a kommunikációt az érzékelõvel.
	 */
	void close();
};

#endif /* INC_SHT7XCOMM_H_ */
