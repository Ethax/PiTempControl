#include <lib/comp_impl/inc/sensor/SHT7xComm.h>
#include <lib/app/inc/core/AppException.h>

/*
 * Kiszámolja az ellenõzõ összeget és az eredményt eltárolja az oszály
 * privát adattagjában. A CRC polinomja: P(x) = x^8 + x^5 + x^4 + x^0
 */
void SHT7xComm::calculateCRC(unsigned char value) {
	for(unsigned char i = 8; i; i--) {
		if((crc ^ value) & 0x80)
			crc = (crc << 1) ^ 0x31;
		else
			crc <<= 1;
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
	if(!initialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* Alacsony szintre sûlyeszti a DATA vonalat, míg az SCK magas. Ezt
	követõen egy alacsony impulzust at le az SCK vonalon és magas szintre
	emeli a DATA vonalat, míg az SCK magas. */
	bcm2835_gpio_write(SHT7x_SCK, HIGH); delayMicroseconds(2);
	bcm2835_gpio_write(SHT7x_DATA, LOW); bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_OUTP);	delayMicroseconds(2);
	bcm2835_gpio_write(SHT7x_SCK, LOW);	delayMicroseconds(2);
	bcm2835_gpio_write(SHT7x_SCK, HIGH); delayMicroseconds(2);
	bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_INPT); delayMicroseconds(2);
	bcm2835_gpio_write(SHT7x_SCK, LOW); delayMicroseconds(2);

	/* A CRC alaphelyzetbe állítása. A kezdõértéke a státuszregiszter
	tartalma lesz. */
	crc = mirrorByte(statusReg & 0x0F);
}

/*
 * Kiolvas egy egybájtos adatot az érzékelõbõl és a megatott paramétertõl
 * függõen nyugtázza az olvasást.
 */
unsigned char SHT7xComm::readByte(bool send_ack) {
	if(!initialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	/* Adatbitek kiolvasása az SCK vonal váltakoztatásával. */
	unsigned char value = 0;
	for(unsigned char mask = 0x80; mask; mask >>= 1) {
		bcm2835_gpio_write(SHT7x_SCK, HIGH); delayMicroseconds(2);
		if(bcm2835_gpio_lev(SHT7x_DATA) != 0)
			value |= mask;
		bcm2835_gpio_write(SHT7x_SCK, LOW); delayMicroseconds(2);
	}

	/* Az adatbájt fogadásának nyugtázása, a DATA vonal alacsony szinten
	tartásával, míg kiküld egy magas impulzust az SCK vonalon, ha a
	nyugtázás engedélyezve van. */
	if(send_ack)
		bcm2835_gpio_write(SHT7x_DATA, LOW); bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_OUTP); delayMicroseconds(2);
	bcm2835_gpio_write(SHT7x_SCK, HIGH); delayMicroseconds(2);
	bcm2835_gpio_write(SHT7x_SCK, LOW); delayMicroseconds(2);
	if(send_ack)
		bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_INPT); delayMicroseconds(2);

	/* A kiolvasott adatbájt visszaadása. */
	return value;
}

bool SHT7xComm::sendByte(unsigned char value) {
	if(!initialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	for(unsigned char mask = 0x80; mask; mask >>= 1) {
		bcm2835_gpio_write(SHT7x_SCK, LOW); delayMicroseconds(2);

		if(value & mask) {
			bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_INPT); delayMicroseconds(2);
		}
		else {
			bcm2835_gpio_write(SHT7x_DATA, LOW); bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_OUTP); delayMicroseconds(2);
		}

		bcm2835_gpio_write(SHT7x_SCK, HIGH); delayMicroseconds(2);  // SCK hi => sensor reads data
	}
	bcm2835_gpio_write(SHT7x_SCK, LOW); delayMicroseconds(2);

	// Release DATA line
	bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_INPT); delayMicroseconds(2);
	bcm2835_gpio_write(SHT7x_SCK, HIGH); delayMicroseconds(2);

	bool ack = !bcm2835_gpio_lev(SHT7x_DATA) ? true : false;

	bcm2835_gpio_write(SHT7x_SCK, LOW); delayMicroseconds(2);

	calculateCRC(value);   // crc calculation

	return ack;
}


SHT7xComm::SHT7xComm() : crc(0), statusReg(0), initialized(false) {}


SHT7xComm::~SHT7xComm() {}

void SHT7xComm::initializePins(RPiGPIOPin _SCK_Pin, RPiGPIOPin _DATA_Pin) {
	SHT7x_SCK = _SCK_Pin;
	SHT7x_DATA = _DATA_Pin;

	// SCK line as output but set to low first
	bcm2835_gpio_write(SHT7x_SCK, LOW);
	bcm2835_gpio_fsel(SHT7x_SCK, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(SHT7x_SCK, LOW);

	// DATA to input. External pull up.
	// Set PORT to 0 => pull data line low by setting port as output
	bcm2835_gpio_set_pud(SHT7x_DATA, BCM2835_GPIO_PUD_OFF);
	bcm2835_gpio_write(SHT7x_DATA, LOW);
	bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_set_pud(SHT7x_DATA, BCM2835_GPIO_PUD_OFF);
	bcm2835_gpio_write(SHT7x_DATA, LOW);

	initialized = true;
}

void SHT7xComm::reset() {
	if(!initialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");

	bcm2835_gpio_fsel(SHT7x_DATA, BCM2835_GPIO_FSEL_INPT);
	delayMicroseconds(2);

	for(unsigned char i = 9; i; i--) {
		bcm2835_gpio_write(SHT7x_SCK, HIGH);
		delayMicroseconds(2);
		bcm2835_gpio_write(SHT7x_SCK, LOW);
		delayMicroseconds(2);
	}
	transmissionStart();
	sendByte(SOFT_RESET);  // Soft reset
}

bool SHT7xComm::measureStart(MeasureCommands type) {
	// send a transmission start and reset crc calculation
	transmissionStart();
	// send command. Crc gets updated!
	return sendByte((unsigned char)type);
}

float SHT7xComm::getMeasureValue() {
	if(!initialized)
		throw AppException("The DATA and SCK pins aren't initialized yet.");


	unsigned char delayCount = 62;  /* delay is 62 * 5ms */
									 /* Wait for measurement to complete (DATA pin gets LOW) */
									 /* Raise an error after we waited 250ms without success (210ms + 15%) */
	while(bcm2835_gpio_lev(SHT7x_DATA)) {
		delayMicroseconds(5000);			// $$$$$$$$$$$$$$$$$$ 1 ms not working $$$$$$$$$$$$$$$$$$$$$$$$
		if((delayCount--) == 0)
			throw AppException("Measurement timed out.");
	}

	union {	unsigned short int ival; float fval; } converter;
	unsigned char* chPtr = (unsigned char*)&converter.ival;
	*(chPtr + 1) = readByte();  // read hi byte
	calculateCRC(*(chPtr + 1));  		// crc calculation
	*chPtr = readByte();    	// read lo byte
	calculateCRC(*chPtr);    			// crc calculation

	unsigned char checksum = readByte(false);   // crc calculation
										// compare it.
	//return SHT1x_Mirrorbyte(checksum) == SHT1x_crc ? TRUE : FALSE;

	if(mirrorByte(checksum) != crc)
		throw AppException("CRC error occurred in measurement validation.");

	converter.fval = (float)converter.ival;
	return converter.fval;
}

void SHT7xComm::correctMeasuredValues(float& humidity, float& temperature) {
	/* The default measurement resolution of 14bit (temperature) and 12bit (humidity) */
	

	// T = d1 + d2 * t

	const float D1 = -39.7; // 3.5V
	const float D2 = 0.01;	// 14-bit

	float t = temperature;          		// t:       Temperature [Ticks] 14 Bit
	float t_C = t*D2 + D1;                  	// calc. temperature from ticks to [C] // t_C   :  Temperature [C]
	
	
	// RH(linear) = c1 + c2 * rh + c3 * rh^2
	// RH = (T - 25) * (t1 + t2 * rh) + RH(linear)
	
	const float C1 = -2.0468;              		// for 12 Bit
	const float C2 = 0.0367;           		// for 12 Bit
	const float C3 = -0.0000015955;        		// for 12 Bit
	const float T1 = 0.01;             		// for 12 Bit
	const float T2 = 0.00008;           		// for 12 Bit
	
	float rh = humidity;             	// rh:      Humidity [Ticks] 12 Bit 
	float rh_lin = C3*rh*rh + C2*rh + C1;     	// calc. humidity from ticks to [%RH] // rh_lin:  Humidity linear
	float rh_true = (t_C - 25)*(T1 + T2*rh) + rh_lin;   // calc. temperature compensated humidity [%RH] // rh_true: Temperature compensated humidity
	if(rh_true>100)	rh_true = 100;       		// cut if the value is outside of
	if(rh_true<0.1)	rh_true = 0.1;       		// the physical possible range

	temperature = t_C;               	// return temperature [C]
	humidity = rh_true;              	// return humidity[%RH]
}
