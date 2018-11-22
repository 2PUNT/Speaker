#ifndef SPEAKER_HPP
#define SPEAKER_HPP

#include "hwlib.hpp"

class Speaker{
private:
	hwlib::pin_out & outputPin;
public:
	///@fn Speaker::Speaker(hwlib::pin_out & _outputPin)
    ///@brief The constructor for the Speaker class.
    ///@details This constructor creates a Speaker object.
	///@param _outputPin The output pin to the speaker.
	Speaker(hwlib::pin_out & _outputPin): outputPin(_outputPin){}
	
	///@fn void Speaker::MakeSound(bool b)
    ///@brief Sets output pin.
    ///@details This method sets @c _outputPin high or low.
	///@param b A boolean value. 1 sets @c _outputPin high and 0 sets @c _outputPin low.
	void MakeSound(bool b);
};

#endif
