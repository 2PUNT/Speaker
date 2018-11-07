#include "hwlib.hpp"

#include "Speaker.hpp"

void Speaker::MakeSound(bool b){
	outputPin.set(b);
}
