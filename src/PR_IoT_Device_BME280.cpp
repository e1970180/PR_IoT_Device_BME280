#include "PR_IoT_Device_BME280.h"

    #include <arduino.h>    
  
	void 	PR_IoT_BME280::setupHW(uint8_t pinSDA, uint8_t pinSCL, uint8_t I2CAddress) {
		
		Wire.pins(pinSDA, pinSCL);
		
		sensor.parameter.communication = 0;			//I2C communication
		sensor.parameter.I2CAddress = I2CAddress;  	//I2C Address  Connecting SDO to GND results in slave address 1110110 (0x76); 
													//connection it to VDDIO results in slave address 1110111 (0x77), which is the same as BMP280’s I²C address. 
		sensor.parameter.sensorMode = 0b11;     	//In normal mode the sensor measures continually (default value)
    
		//*********************************************************************
		//Great! Now set up the internal IIR Filter
		//The IIR (Infinite Impulse Response) filter suppresses high frequency fluctuations
		//In short, a high factor value means less noise, but measurements are also less responsive
		//In doubt just leave on default

		//bme1.parameter.IIRfilter = 0b000;                   //factor 0 (filter off)
		//bme1.parameter.IIRfilter = 0b001;                   //factor 2
		//bme1.parameter.IIRfilter = 0b010;                   //factor 4
		//bme1.parameter.IIRfilter = 0b011;                   //factor 8
		sensor.parameter.IIRfilter = 0b101;                   //factor 16 (default value)

		//*********************************************************************
		//Next you'll define the oversampling factor for the humidity measurements
		//Again, higher values mean less noise, but slower responses
		//If you don't want to measure humidity, set the oversampling to zero

		//bme1.parameter.humidOversampling = 0b000;            //factor 0 (Disable humidity measurement)
		//bme1.parameter.humidOversampling = 0b001;            //factor 1
		//bme1.parameter.humidOversampling = 0b010;            //factor 2
		//bme1.parameter.humidOversampling = 0b011;            //factor 4
		//bme1.parameter.humidOversampling = 0b100;            //factor 8
		
		sensor.parameter.humidOversampling = 0b101;            //factor 16


		//*********************************************************************
		//Now define the oversampling factor for the temperature measurements
		//You know now, higher values lead to less noise but slower measurements

		//bme1.parameter.tempOversampling = 0b000;              //factor 0 (Disable temperature measurement)
		//bme1.parameter.tempOversampling = 0b001;              //factor 1
		//bme1.parameter.tempOversampling = 0b010;              //factor 2
		//bme1.parameter.tempOversampling = 0b011;              //factor 4
		//bme1.parameter.tempOversampling = 0b100;              //factor 8
		
		sensor.parameter.tempOversampling = 0b101;              //factor 16


		//*********************************************************************
		//Finally, define the oversampling factor for the pressure measurements
		//For altitude measurements a higher factor provides more stable values
		//On doubt, just leave it on default

		//bme1.parameter.pressOversampling = 0b000;             //factor 0 (Disable pressure measurement)
		//bme1.parameter.pressOversampling = 0b001;             //factor 1
		//bme1.parameter.pressOversampling = 0b010;             //factor 2
		//bme1.parameter.pressOversampling = 0b011;             //factor 4
		//bme1.parameter.pressOversampling = 0b100;             //factor 8
		
		sensor.parameter.pressOversampling = 0b101;             //factor 16

		//*********************************************************************

		if (sensor.init() != 0x60) {    
		PR_DBGTLN("Ops! First BME280 Sensor not found!")
		}
		else {
		PR_DBGTLN("First BME280 Sensor detected!")
		}
	
	}   
			
	void	PR_IoT_BME280::update() {	
		
		_lastMeasuredTemp	= sensor.readTempC();
		_lastMeasuredHumid	= sensor.readHumidity();
		
		postMsg("temperature", String(_lastMeasuredTemp, 1) );
		postMsg("humidity", String(_lastMeasuredHumid) );
	}
	
	void	PR_IoT_BME280::inMsgCallback() {

		PR_DBGTLN("MBE280: Msg got")
		PR_DBGVLN(inMsg.payload)
		
		if (inMsg.payload == "ASK")	{
			invoke();
		}
	}
	
