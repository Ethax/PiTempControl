#include <lib/comp_impl/inc/sensor/SHT7xComm.h>
#include <lib/app/inc/core/AppException.h>

#include <iostream>

/*
 * Kisz�molja az ellen�z� �sszeget �s az eredm�nyt elt�rolja az osz�ly
 * priv�t adattagj�ban. A CRC polinomja: P(x) = x^8 + x^5 + x^4 + x^0
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
 * T�kr�zi az �tadott b�jtot.
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
 * Inicializ�lja a kommunik�ci�t az �rz�kel�vel a Transmission Start
 * sorozat kik�ld�s�vel.
 */
void SHT7xComm::transmissionStart() {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* A sorozat elk�ld�se a DATA vonal alacsony szinte s�llyeszt�s�vel, m�g
	az SCK magas, majd alacsony impulzus lead�s�val az SCK vonalon �s a DATA
	vonal magas szinre emel�s�vel, m�g az SCK magas. */
	setSCKLevel(HIGH);
	setDATALevel(LOW);
	setSCKLevel(LOW);
	setSCKLevel(HIGH);
	setDATALevel(HIGH);
	setSCKLevel(LOW);

	/* A CRC alaphelyzetbe �ll�t�sa. A kezd��rt�ke a �llapotregiszter
	tartalma lesz. */
	checksum = mirrorByte(statusReg & 0x0F);
}

/*
 * Kiolvas egy egyb�jtos adatot az �rz�kel�b�l �s a megatott param�tert�l
 * f�gg�en nyugt�zza az olvas�st.
 */
unsigned char SHT7xComm::readByte(bool send_ack) {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* Adatbitek kiolvas�sa az SCK vonal v�ltakoztat�s�val. */
	unsigned char value = 0;
	for(unsigned char mask = 0x80; mask; mask >>= 1) {
		setSCKLevel(HIGH);
		if(getDATALevel() != 0) value |= mask;
		setSCKLevel(LOW);
	}

	/* Az adatb�jt fogad�s�nak nyugt�z�sa, a DATA vonal alacsony szinten
	tart�s�val �s egy magas impulzus kik�ld�s�vel az SCK vonalon, ha a
	nyugt�z�s enged�lyezve van. */
	if(send_ack) setDATALevel(LOW);
	setSCKLevel(HIGH);
	setSCKLevel(LOW);
	if(send_ack) setDATALevel(HIGH);

	/* A kiolvasott adatb�jt visszaad�sa. */
	return value;
}

/*
 * Elk�ld egy egyb�jtos adatot az �rz�kel�nek �s visszaadja az �rz�kel�t�l
 * �rkez� nyugt�t.
 */
bool SHT7xComm::sendByte(unsigned char value) {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* Adatbitek elk�ld�se az SCK vonal v�ltakoztat�s�val. */
	for(unsigned char mask = 0x80; mask; mask >>= 1) {
		setSCKLevel(LOW);
		setDATALevel((value & mask) ? HIGH : LOW);
		setSCKLevel(HIGH);
	}
	setSCKLevel(LOW);

	/* Az DATA vonal ir�ny�nak vissza�ll�t�sa bemenetre �s az SCK
	magas szintre elem�se a nyugta fogad�s�hoz. */
	setDATALevel(HIGH);
	setSCKLevel(HIGH);
	
	/* A nyugta let�rol�sa �s az SCK vonal visszas�llyeszt�se alacsony
	szintre. */
	bool ack = (getDATALevel() == LOW) ? true : false;
	setSCKLevel(LOW);

	/* Az elk�ld�tt adat ellen�z� �sszeg�nek kisz�m�t�sa �s a nyugta
	visszaad�sa. */
	calculateChecksum(value);
	return ack;
}

/*
 * Az osz�ly alap�rtelmezett konstruktora.
 */
SHT7xComm::SHT7xComm() : checksum(0), statusReg(0), isInitialized(false) {}

/*
 * Az oszt�ly destruktora.
 */
SHT7xComm::~SHT7xComm() {}

/*
 * Inicializ�lja az �rz�kel�vel �sszek�t�tt kommunik�ci�s vonalakat.
 */
void SHT7xComm::initializePins(RPiGPIOPin _SCK_Pin, RPiGPIOPin _DATA_Pin) {
	SHT7x_SCK = _SCK_Pin;
	SHT7x_DATA = _DATA_Pin;
	if(!bcm2835_init())
		throw AppException("BCM2835 initialization failed at Sensor module.");

	/* Az SCK vonal be�ll�t�sa kimenetnek �s kezd��llapotk�nt alacsony
	szintre s�llyeszt�se. */
	bcm2835_gpio_write(SHT7x_SCK, LOW);
	bcm2835_gpio_fsel(SHT7x_SCK, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(SHT7x_SCK, LOW);

	/* A DATA vonal bels� felh�z�ellen�ll�s�nak tilt�sa a k�ls� felh�z�s
	miatt, majd be�ll�t�sa kimenetnek �s kezd��llapotk�nt alacsony
	szintre s�llyeszt�se. */
	bcm2835_gpio_write(SHT7x_DATA, LOW);
	bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_set_pud(SHT7x_DATA, BCM2835_GPIO_PUD_OFF);
	bcm2835_gpio_write(SHT7x_DATA, LOW);

	/* Az inicializ�ci� befejez�s�nek let�rol�sa. */
	isInitialized = true;
}

/*
 * Alaphelyzetbe �ll�tja Az �rz�kel�t a Connection Reset sorozat �s a
 * Soft Reset utas�t�s kik�ld�s�vel.
 */
void SHT7xComm::reset() {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* A DATA vonal �tv�lt�sa bemenetre, majd kilenc darab magas
	impulzus lead�sa az SCK vonalon az interf�sz alaphelyzetbe
	�ll�t�s�hoz. */
	setDATALevel(HIGH);
	for(unsigned char i = 9; i; i--) {
		setSCKLevel(HIGH);
		setSCKLevel(LOW);
	}

	/* Egy Transmission Start sorozat �s egy Soft Reset utas�t�s k�ld�se
	az �rz�kel�nek a �llapotregiszter t�rl�s�hez. */
	transmissionStart();
	sendByte(SOFT_RESET);
}

/*
 * Utas�t�ja az �rz�kel�t a megadott jellemz� (h�m�rs�klet vagy
 * p�ratartalom) megm�r�s�re.
 */
bool SHT7xComm::measureStart(MeasureCommands type) {
	/* Transmission Start sorozat k�ld�se �s a kor�bban kisz�m�tott
	ellen�rz� �sszeg alaphelyzetbe �ll�t�sa. */
	transmissionStart();

	/* A megadott utas�t�s elk�ld�se �s �j ellen�rz� �sszeg sz�m�t�sa. */
	return sendByte((unsigned char)type);
}

/*
 * Kiolvassa a legut�bbi m�r�s eredm�ny�t az �rz�kel�b�l �s elv�gzi az
 * adaton a CRC-t.
 */
unsigned short int SHT7xComm::getMeasureValue() {
	if(!isInitialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* A m�r�s befejez�d�s�nek kiv�r�sa. Ez 14-bites felbont�s mellett
	legfeljebb 320us lehet, a befejez�d�s�t pedig a DATA vonal alacsony
	szintre s�llyed�se jelzi. */
	unsigned char delayCount = 64;
	while(getDATALevel()) {
		delayMicroseconds(5000);
		if((delayCount--) == 0)
			throw AppException("Measurement timed out.");
	}

	/* A m�r�s eredm�ny�nek kiolvas�sa b�jtonk�nt, minden b�jtot
	nyugt�zva, �s a kiolvasott b�jtokra az ellen�z� �sszeg
	kisz�m�t�sa. */
	unsigned short int result = 0;
	unsigned char* resPtr = (unsigned char*)&result;
	*(resPtr + 1) = readByte();
	calculateChecksum(*(resPtr + 1));
	*resPtr = readByte();
	calculateChecksum(*resPtr);

	/* Kiv�tel dob�sa, amennyiben a kisz�m�tott �s a fogadott
	ellen�rz��sszeg elt�r, ellenkez� esetben a m�r�s eredm�ny�nek
	visszaad�sa. */
	unsigned char _checksum = readByte(false);
	if(mirrorByte(_checksum) != checksum)
		throw AppException("CRC error occurred in measurement validation.");
	return result;
}

/*
 * Az �rz�kel�t�l sz�rmaz� nyers h�m�rs�klet �s p�ratartalom �rt�kekb�l
 * kisz�m�tja azok val�s �rt�keit.
 */
void SHT7xComm::correctMeasuredValues(float& humidity, float& temperature) {
	/* A h�m�rs�klet �tsz�m�t�sa Celsius fokokra a k�vetkez� k�plet
	seg�ts�g�vel: t[�C] = d1 + d2 * t[tick] */
	const float D1 = -39.7;
	const float D2 = 0.01;
	float t_real = temperature * D2 + D1;
	
	/* A line�ris p�ratartalom kisz�m�t�sa a k�vetkez� k�plet seg�ts�g�vel:
	rh_lin[%RH] = c1 + c2 * rh[tick] + c3 * rh[tick]^2 */
	const float C1 = -2.0468;
	const float C2 = 0.0367;
	const float C3 = -0.0000015955;
	float rh_lin = C3 * humidity * humidity + C2 * humidity + C1;
	
	/* A h�m�rs�klet-kompenz�lt p�ratartalom kisz�m�t�sa a kor�bban kisz�m�tott
	h�m�rs�klet �s line�ris p�ratartalom sz�m�rt�keinek felhaszn�l�s�val:
	rh[%RH] = (t[�C] - 25) * (t1 + t2 * rh[tick]) + rh_lin[%RH] */
	const float T1 = 0.01;
	const float T2 = 0.00008;
	float rh_real = (t_real - 25) * (T1 + T2 * humidity) + rh_lin;
	
	/* A p�ratartalom �rt�k�nek korrig�l�sa, amennyiben �tl�pte a fizikailag
	lehets�ges tartom�nyt. */
	if(rh_real>100)	rh_real = 100;
	if(rh_real<0.1)	rh_real = 0.1;

	/* Az �tsz�m�tott �rt�kek vissza�r�sa a megadott v�ltoz�kba. */
	temperature = t_real;
	humidity = rh_real;
}

/*
 * Lez�rja a kommunik�ci�t az �rz�kel�vel.
 */
void SHT7xComm::close() {
	bcm2835_close();
}
