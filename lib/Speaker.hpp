#ifndef SPEAKER_HPP
#define SPEAKER_HPP

#include "hwlib.hpp"

class Speaker{
private:
	hwlib::pin_out & outputPin;
public:
	Speaker(hwlib::pin_out & _outputPin): outputPin(_outputPin){}
	
	void MakeSound(bool b);
};

#endif
