#include "hwlib.hpp"

#include "Speaker.hpp"

void Speaker::MakeSound(bool b){
	hwlib::cout << "making sound?\n";
	outputPin.set(b);
}
