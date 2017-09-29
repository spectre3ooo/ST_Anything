//******************************************************************************************
//  File: InterruptSensor.cpp
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
//    2025-01-03  Dan & Daniel   Original Creation
//	  2015-03-17  Dan			 Added optional "numReqCounts" constructor argument/capability
//	  2017-09-28  Troy					 Copied InterruptSensor
//
//
//******************************************************************************************

#include "DualInterruptSensor.h"

#include "Constants.h"
#include "Everything.h"

namespace st
{
//private

	//Checks to see if the pin has changed state.  If so calls appropriate function.
	void DualInterruptSensor::checkIfTriggered()
	{
		// pin 1
		if (digitalRead(m_nInterruptPin1) != m_bStatus1) //new interrupt
		{
			m_nCurrentCount1++;
			if (m_nCurrentCount1 >= m_nRequiredCounts)
			{
				m_bStatus1 = true;
				pin1Changed(m_bStatus1);
			}
		}
		else
		{
			//reset the count
			m_nCurrentCount1 = m_nRequiredCounts;
		}

		// pin 2
		if (digitalRead(m_nInterruptPin2) != m_bStatus2) //new interrupt
		{
			m_nCurrentCount2++;
			if (m_nCurrentCount2 >= m_nRequiredCounts)
			{
				m_bStatus2 = true;
				pin2Changed(m_bStatus2);
			}
		}
		else
		{
			//reset the count
			m_nCurrentCount2 = m_nRequiredCounts;
		}	
}

//public
	//constructor
	DualInterruptSensor::DualInterruptSensor(const __FlashStringHelper *name, byte pin1, byte pin2, bool pullup, long numReqCounts) :
		Sensor(name),
		m_bPullup(pullup),
		m_nRequiredCounts(numReqCounts),
		m_nCurrentCount1(numReqCounts),
		m_nCurrentCount2(numReqCounts)
		{
			setInterruptPin1(pin1);
			m_bStatus1 = digitalRead(m_nInterruptPin1);
			pin1Changed(m_bStatus1);

			setInterruptPin2(pin2);
			m_bStatus2 = digitalRead(m_nInterruptPin2);
			pin2Changed(m_bStatus2);


		}
	
	//destructor
	DualInterruptSensor::~DualInterruptSensor()
	{
	
	}
	
	//initialization function
	void DualInterruptSensor::init()
	{
		checkIfTriggered();
	}
	
	//update function 
	void DualInterruptSensor::update()
	{
		checkIfTriggered();
	}

	//handles start of an interrupt - all derived classes should implement this virtual function
	void DualInterruptSensor::pin1Changed(bool state)
	{
		if(debug)
		{
			Everything::sendSmartString(getName()+F(" pin1 triggered ") + (state?F("HIGH"):F("LOW)")));
		}
	}
	void DualInterruptSensor::pin2Changed(bool state)
	{
		if(debug)
		{
			Everything::sendSmartString(getName()+F(" pin2 triggered ") + (state?F("HIGH"):F("LOW)")));
		}
	}
	
	
	//sets the pin to be monitored, and set the Arduino pinMode based on constructor data
	void DualInterruptSensor::setInterruptPin1(byte pin)
	{
		m_nInterruptPin1=pin;
		if(!m_bPullup)
		{
			pinMode(m_nInterruptPin1, INPUT);
		}
		else
		{
			pinMode(m_nInterruptPin1, INPUT_PULLUP);
		}
	}
	void DualInterruptSensor::setInterruptPin2(byte pin)
	{
		m_nInterruptPin2=pin;
		if(!m_bPullup)
		{
			pinMode(m_nInterruptPin2, INPUT);
		}
		else
		{
			pinMode(m_nInterruptPin2, INPUT_PULLUP);
		}
	}
	
	//debug flag to determine if debug print statements are executed (set value in your sketch)
	bool DualInterruptSensor::debug=false;
}