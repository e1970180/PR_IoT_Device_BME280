#ifndef PR_IoT_Device_BME280_h
#define PR_IoT_Device_BME280_h

    #include <arduino.h>
    #include <PR_IoT.h>

	#include <Wire.h>
	#include "BlueDot_BME280.h"
	
	#ifndef	BME280_TEMP_PRECISION
		#define	BME280_TEMP_PRECISION	9		//
	#endif
	
	
class PR_IoT_BME280 : public PR_IoT_DeviceClass {
        public:
            PR_IoT_BME280(String name) : PR_IoT_DeviceClass(name) {}; 
			
            //virtual void 	announce();			//could be overloaded here from base class
            void 			update();
            virtual void 	inMsgCallback(); 
            virtual void 	setupHW(uint8_t pinSDA, uint8_t pinSCL, uint8_t I2CAddress = 0x76);
			virtual void	loopHW()			{}
			
			float 			getTemp()			{	return _lastMeasuredTemp;	}
			uint8_t			getHumid()			{	return _lastMeasuredHumid;	}
			
        protected:
			BlueDot_BME280 	sensor;

			float 			_lastMeasuredTemp;
			uint8_t			_lastMeasuredHumid;
	};
	
#endif