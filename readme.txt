This is a Thermometer based on a Thermistor.
A shift register allows to display the measured temperature in °C using LEDs.
8 leds are used to display temperature.
Since this thermometer was designed assuming a domestic use, the 5 most significant bits are used to display integer part of the measured value (so a range from 0°C to 31°C), while the other 3 bits are used to display the decimal part.
A 9th led is directly connected to Arduino and it is used to notify the case of a 0.9 as decimal part.
A button triggers an interrupt to enable or disable the output (i.e activate or deactivate leds).

ATTENTION: to use the shift register in an easier way, I developed a C++ library that is included in this repository (.h and .cpp files) to be able to use the IC at an higher level of abstraction, even without a perfect knowledge of its datasheet.
The .ino file's code uses this class.  
To use that class in this or future projects, it si adviced to go in /Documents/Arduino/libraries/ and make a directory in which copy the .h and .cpp files.
