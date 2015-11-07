#include <lib/comp_impl/inc/sensor/SHT7xComm.h>
#include <lib/app/inc/core/AppException.h>

#include <iostream>

/*
 * Kiszámolja az ellenõzõ összeget és az eredményt eltárolja az oszály
 * privát adattagjában. A CRC polinomja: P(x) = x^8 + x^5 + x^4 + x^0
 */
void SHT7xComm::calculateChecksum(unsigned char value) {
	for(unsigned char i = 8; i; i--) {
		if((checksum ^ value) & 0x80)
			checksum = (checksum << 1) ^ 0x31;
		else
			checksum <<= 1;
		value <<= 1;
	}
}

/*
 * Tükrözi az átadott bájtot.
 */
unsigned char SHT7xComm::mirrorByte(unsigned char value) {
	unsigned char ret = 0;
	for(unsigned char i = 0x80; i; i >>= 1) {
		if(value & 0x01) ret |= i;
		value >>= 1;
	}
	return ret;
}

/*
 * Inicializálja a kommunikációt az érzékelõvel a Transmission Start
 * sorozat kiküldésével.
 */
void SHT7xComm::transmissionStart() {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* A sorozat elküldése a DATA vonal alacsony szinte süllyesztésével, míg
	az SCK magas, majd alacsony impulzus leadásával az SCK vonalon és a DATA
	vonal magas szinre emelésével, míg az SCK magas. */
	setSCKLevel(HIGH);
	setDATALevel(LOW);
	setSCKLevel(LOW);
	setSCKLevel(HIGH);
	setDATALevel(HIGH);
	setSCKLevel(LOW);

	/* A CRC alaphelyzetbe állítása. A kezdõértéke a állapotregiszter
	tartalma lesz. */
	checksum = mirrorByte(statusReg & 0x0F);
}

/*
 * Kiolvas egy egybájtos adatot az érzékelõbõl és a megatott paramétertõl
 * függõen nyugtázza az olvasást.
 */
unsigned char SHT7xComm::readByte(bool send_ack) {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* Adatbitek kiolvasása az SCK vonal váltakoztatásával. */
	unsigned char value = 0;
	for(unsigned char mask = 0x80; mask; mask >>= 1) {
		setSCKLevel(HIGH);
		if(getDATALevel() != 0) value |= mask;
		setSCKLevel(LOW);
	}

	/* Az adatbájt fogadásának nyugtázása, a DATA vonal alacsony szinten
	tartásával és egy magas impulzus kiküldésével az SCK vonalon, ha a
	nyugtázás engedélyezve van. */
	if(send_ack) setDATALevel(LOW);
	setSCKLevel(HIGH);
	setSCKLevel(LOW);
	if(send_ack) setDATALevel(HIGH);

	/* A kiolvasott adatbájt visszaadása. */
	return value;
}

/*
 * Elküld egy egybájtos adatot az érzékelõnek és visszaadja az érzékelõtõl
 * érkezõ nyugtát.
 */
bool SHT7xComm::sendByte(unsigned char value) {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* Adatbitek elküldése az SCK vonal váltakoztatásával. */
	for(unsigned char mask = 0x80; mask; mask >>= 1) {
		setSCKLevel(LOW);
		setDATALevel((value & mask) ? HIGH : LOW);
		setSCKLevel(HIGH);
	}
	setSCKLevel(LOW);

	/* Az DATA vonal irányának visszaállítása bemenetre és az SCK
	magas szintre elemése a nyugta fogadásához. */
	setDATALevel(HIGH);
	setSCKLevel(HIGH);
	
	/* A nyugta letárolása és az SCK vonal visszasüllyesztése alacsony
	szintre. */
	bool ack = (getDATALevel() == LOW) ? true : false;
	setSCKLevel(LOW);

	/* Az elküldött adat ellenõzõ összegének kiszámítása és a nyugta
	visszaadása. */
	calculateChecksum(value);
	return ack;
}

/*
 * Az oszály alapértelmezett konstruktora.
 */
SHT7xComm::SHT7xComm() : checksum(0), statusReg(0), isInitialized(false) {}

/*
 * Az osztály destruktora.
 */
SHT7xComm::~SHT7xComm() {}

/*
 * Inicializálja az érzékelõvel összekötött kommunikációs vonalakat.
 */
void SHT7xComm::initializePins(RPiGPIOPin _SCK_Pin, RPiGPIOPin _DATA_Pin) {
	SHT7x_SCK = _SCK_Pin;
	SHT7x_DATA = _DATA_Pin;
	if(!bcm2835_init())
		throw AppException("BCM2835 initialization failed at Sensor module.");

	/* Az SCK vonal beállítása kimenetnek és kezdõállapotként alacsony
	szintre süllyesztése. */
	bcm2835_gpio_write(SHT7x_SCK, LOW);
	bcm2835_gpio_fsel(SHT7x_SCK, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(SHT7x_SCK, LOW);

	/* A DATA vonal belsõ felhúzóellenállásának tiltása a külsõ felhúzás
	miatt, majd beállítása kimenetnek és kezdõállapotként alacsony
	szintre süllyesztése. */
	bcm2835_gpio_write(SHT7x_DATA, LOW);
	bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_set_pud(SHT7x_DATA, BCM2835_GPIO_PUD_OFF);
	bcm2835_gpio_write(SHT7x_DATA, LOW);

	/* Az inicializáció befejezésének letárolása. */
	isInitialized = true;
}

/*
 * Alaphelyzetbe állítja Az érzékelõt a Connection Reset sorozat és a
 * Soft Reset utasítás kiküldésével.
 */
void SHT7xComm::reset() {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* A DATA vonal átváltása bemenetre, majd kilenc darab magas
	impulzus leadása az SCK vonalon az interfész alaphelyzetbe
	állításához. */
	setDATALevel(HIGH);
	for(unsigned char i = 9; i; i--) {
		setSCKLevel(HIGH);
		setSCKLevel(LOW);
	}

	/* Egy Transmission Start sorozat és egy Soft Reset utasítás küldése
	az érzékelõnek a állapotregiszter törléséhez. */
	transmissionStart();
	sendByte(SOFT_RESET);
}

/*
 * Utasítája az érzékelõt a megadott jellemzõ (hõmérséklet vagy
 * páratartalom) megmérésére.
 */
bool SHT7xComm::measureStart(MeasureCommands type) {
	/* Transmission Start sorozat küldése és a korábban kiszámított
	ellenõrzõ összeg alaphelyzetbe állítása. */
	transmissionStart();

	/* A megadott utasítás elküldése és új ellenõrzõ összeg számítása. */
	return sendByte((unsigned char)type);
}

/*
 * Kiolvassa a legutóbbi mérés eredményét az érzékelõbõl és elvégzi az
 * adaton a CRC-t.
 */
unsigned short int SHT7xComm::getMeasureValue() {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* A mérés befejezõdésének kivárása. Ez 14-bites felbontás mellett
	legfeljebb 320us lehet, a befejezõdését pedig a DATA vonal alacsony
	szintre süllyedése jelzi. */
	unsigned char delayCount = 64;
	while(getDATALevel()) {
		delayMicroseconds(5000);
		if((delayCount--) == 0)
			throw AppException("Measurement timed out.");
	}

	/* A mérés eredményének kiolvasása bájtonként, minden bájtot
	nyugtázva, és a kiolvasott bájtokra az ellenõzõ összeg
	kiszámítása. */
	unsigned short int result = 0;
	unsigned char* resPtr = (unsigned char*)&result;
	*(resPtr + 1) = readByte();
	calculateChecksum(*(resPtr + 1));
	*resPtr = readByte();
	calculateChecksum(*resPtr);

	/* Kivétel dobása, amennyiben a kiszámított és a fogadott
	ellenõrzõösszeg eltér, ellenkezõ esetben a mérés eredményének
	visszaadása. */
	unsigned char _checksum = readByte(false);
	if(mirrorByte(_checksum) != checksum)
		throw AppException("CRC error occurred in measurement validation.");
	return result;
}

/*
 * Az érzékelõtõl származó nyers hõmérséklet és páratartalom értékekbõl
 * kiszámítja azok valós értékeit.
 */
void SHT7xComm::correctMeasuredValues(float& humidity, float& temperature) {
	/* A hõmérséklet átszámítása Celsius fokokra a következõ képlet
	segítségével: t[°C] = d1 + d2 * t[tick] */
	const float D1 = -39.7;
	const float D2 = 0.01;
	float t_real = temperature * D2 + D1;
	
	/* A lineáris páratartalom kiszámítása a következõ képlet segítségével:
	rh_lin[%RH] = c1 + c2 * rh[tick] + c3 * rh[tick]^2 */
	const float C1 = -2.0468;
	const float C2 = 0.0367;
	const float C3 = -0.0000015955;
	float rh_lin = C3 * humidity * humidity + C2 * humidity + C1;
	
	/* A hõmérséklet-kompenzált páratartalom kiszámítása a korábban kiszámított
	hõmérséklet és lineáris páratartalom számértékeinek felhasználásával:
	rh[%RH] = (t[°C] - 25) * (t1 + t2 * rh[tick]) + rh_lin[%RH] */
	const float T1 = 0.01;
	const float T2 = 0.00008;
	float rh_real = (t_real - 25) * (T1 + T2 * humidity) + rh_lin;
	
	/* A páratartalom értékének korrigálása, amennyiben átlépte a fizikailag
	lehetséges tartományt. */
	if(rh_real>100)	rh_real = 100;
	if(rh_real<0.1)	rh_real = 0.1;

	/* Az átszámított értékek visszaírása a megadott változókba. */
	temperature = t_real;
	humidity = rh_real;
}

/*
 * Lezárja a kommunikációt az érzékelõvel.
 */
void SHT7xComm::close() {
	bcm2835_close();
}
