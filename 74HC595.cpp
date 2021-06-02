#include "74HC595.h"

SHR_74HC595::SHR_74HC595(){
	
	//default device's configuration
	
	pinMode(13, OUTPUT); //Master Reset (active LOW)
    pinMode(12, OUTPUT); //DS (serial data input)
    pinMode(8, OUTPUT); //SH_CP (shift register clock input)
    pinMode(7, OUTPUT); //ST_CP (storale register clock input)
    pinMode(5, OUTPUT); //Output Enable (active LOW)
    DS_pin = 12;
    SH_CP_pin = 8;
    ST_CP_pin = 7;
    MR_pin = 13;
    OE_pin = 5;
	
    del = 100;
    outputs_enabled = false;


}
/*
SHR_74HC595::SHR_74HC595(byte DS = -1, byte SH_CP = -1, byte ST_CP = -1, byte MR = -1, byte OE = -1){

	/*
	set_SerialDataInput(DS_pin, DS);
	set_ShiftRegisterClockInput(SH_CP_pin, SH_CP);
	set_StorageRegisterClockInput(ST_CP_pin, ST_CP);
	set_MasterReset(MR_pin, MR);
	set_OutputEnable(OE_pin, OE);
    set_delay(int 100);
	*/
/*
}
*/
SHR_74HC595::~SHR_74HC595(){
	
}

void SHR_74HC595::set_SerialDataInput(byte pin){

	DS_pin = pin;

}
void SHR_74HC595::set_ShiftRegisterClockInput(byte pin){

	SH_CP_pin = pin;

}
void SHR_74HC595::set_StorageRegisterClockInput(byte pin){

	ST_CP_pin = pin;

}
void SHR_74HC595::set_MasterReset(byte pin){

	MR_pin = pin;

}
void SHR_74HC595::set_OutputEnable(byte pin){

	OE_pin = pin;

}
void SHR_74HC595::set_delay(int val){

	del = val;

}
void SHR_74HC595::write(int val){

   digitalWrite(DS_pin, (val == 1 )? HIGH : LOW);
   delay(del);
   digitalWrite(SH_CP_pin, HIGH);
   delay(del);
   digitalWrite(SH_CP_pin, LOW);
   delay(del);


}

void SHR_74HC595::ConfigureOutputs(int* byte_buffer){

	for(int i = 0; i < 8; i++){

		(*this).write(byte_buffer[i]);

	}

}

void SHR_74HC595::ConfirmOutputs(){
	digitalWrite(ST_CP_pin, HIGH);
    delay(del);
    digitalWrite(ST_CP_pin, LOW);
    delay(del);

}

void SHR_74HC595::EnableOutputs(){

	digitalWrite(OE_pin, LOW);
	outputs_enabled = true;

}

void SHR_74HC595::DisableOutputs(){

	digitalWrite(OE_pin, HIGH);
	outputs_enabled = false;


}

void SHR_74HC595::ToggleOutputsState(){

	if(outputs_enabled){
		(*this).DisableOutputs();
		outputs_enabled = false;
	}
	else{
		(*this).EnableOutputs();
		outputs_enabled = true;
	}


}

bool SHR_74HC595::GetOutputsState(){

	return outputs_enabled;

}

void SHR_74HC595::reset(){

  digitalWrite(MR_pin, LOW);
  delay(del);
  digitalWrite(MR_pin, HIGH);

}