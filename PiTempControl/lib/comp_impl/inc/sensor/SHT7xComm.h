#ifndef INC_SHT7XCOMM_H_
#define INC_SHT7XCOMM_H_ 

#include <bcm2835.h>
#include <unistd.h>
#include <stdio.h>

class SHT7xComm {
public:
	enum MeasureCommands {
		MEASURE_TEMPERATURE = 0x03,
		MEASURE_HUMIDITY = 0x05,
	};

private:
	unsigned char crc;
	unsigned char statusReg;

	bool initialized;

	RPiGPIOPin SHT7x_SCK;

	RPiGPIOPin SHT7x_DATA;

	enum Commands {
		READ_STATUS = 0x07,
		WRITE_STATUS = 0x06,
		SOFT_RESET = 0x1E
	};
	
	void calculateCRC(unsigned char value);

	unsigned char mirrorByte(unsigned char value);

	void transmissionStart();

	unsigned char readByte(bool send_ack = true);

	bool sendByte(unsigned char value);


public:
	SHT7xComm();
	virtual ~SHT7xComm();

	void initializePins(RPiGPIOPin _SCK_Pin, RPiGPIOPin _DATA_Pin);

	void reset();

	bool measureStart(MeasureCommands type);

	float getMeasureValue();

	void correctMeasuredValues(float& humidity, float& temperature);
};

#endif /* INC_SHT7XCOMM_H_ */
