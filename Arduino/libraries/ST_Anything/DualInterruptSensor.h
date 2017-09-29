//******************************************************************************************
//  File: InterruptSensor.h
//  Authors: Dan G Ogorchock & Daniel J Ogorchock (Father and Son)
//
//  Summary:  st::DualInterruptSensor is a generic class which inherits from st::Sensor.  This is the
//			  parent class for the st::IS_Motion, IS_Contact, and IS_DoorControl classes.
//			  In general, this file should not need to be modified.   
//
//  Change History:
//
//    Date        Who            What
//    ----        ---            ----
//    2015-01-03  Dan & Daniel   Original Creation
//	  2015-03-17  Dan			 Added optional "numReqCounts" constructor argument/capability
//	  2017-09-28  Troy					 Copied InterruptSensor
//
//
//******************************************************************************************

#ifndef ST_DUALINTERRUPTSENSOR_H
#define ST_DUALINTERRUPTSENSOR_H

#include "Sensor.h"

namespace st
{
	class DualInterruptSensor: public Sensor
	{
		private:
			byte m_nInterruptPin1;	//pin that will be monitored for change of state
			byte m_nInterruptPin2;	//pin that will be monitored for change of state
			bool m_bStatus1;			//true == interrupted
			bool m_bStatus2;			//true == interrupted
			bool m_bPullup;			//true == Internal Pullup resistor required, set in constructor call in your sketch
			long m_nRequiredCounts;	//Number of required counts (checks of the pin) before believing the pin is high/low
			long m_nCurrentCount1;
			long m_nCurrentCount2;

			void checkIfTriggered(); 
			
		public:
			//constructor
			DualInterruptSensor(const __FlashStringHelper *name, byte pin1, byte pin2, bool internalPullup=false, long numReqCounts=0); //(defaults to NOT using internal pullup resistors, and required counts = 0)
			
			//destructor
			virtual ~DualInterruptSensor();
			
			//initialization function
			virtual void init();

			//update function 
			virtual void update();

			//handles what to do when interrupt is triggered - all derived classes should implement this virtual function
			virtual void pin1Changed(bool state);
			virtual void pin2Changed(bool state);
			
			//gets
			inline byte getInterruptPin1() const {return m_nInterruptPin1;}
			inline bool getStatus1() const {return m_bStatus1;}	//whether or not the device is currently interrupted
			inline byte getInterruptPin2() const {return m_nInterruptPin2;}
			inline bool getStatus2() const {return m_bStatus2;}	//whether or not the device is currently interrupted
			
			
			//sets
			void setInterruptPin1(byte pin);
			void setInterruptPin2(byte pin);
			
			//debug flag to determine if debug print statements are executed (set value in your sketch)
			static bool debug;
	
	};
}


#endif