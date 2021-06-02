#ifndef SHR_74HC595_H
#define SHR_74HC595_H

#include "Arduino.h"
class SHR_74HC595{
	
	private:

		byte DS_pin, SH_CP_pin, ST_CP_pin, MR_pin, OE_pin;
		int del; //default delay value is 100;
		bool outputs_enabled;

	public:

		SHR_74HC595();
		//SHR_74HC595(byte DS = -1, byte SH_CP = -1, byte ST_CP = -1, byte MR = -1, byte OE = -1);
		~SHR_74HC595();

		void set_SerialDataInput(byte pin);
		void set_ShiftRegisterClockInput(byte pin);
		void set_StorageRegisterClockInput(byte pin);
		void set_MasterReset(byte pin);
		void set_OutputEnable(byte pin);

		void set_delay(int val); //set a new delay value

		void write(int val); //write a bit through the DS pin
		void ConfigureOutputs(int* byte_buffer);
		void ConfirmOutputs();
		void EnableOutputs();
		void DisableOutputs();
		void ToggleOutputsState();
		bool GetOutputsState(); //return true if outputs are enabled, false if they are disabled
		void reset();


};

#endif