#include "hwlib.hpp"
#include "rtos.hpp"

#include "note.hpp"
#include "Speaker.hpp"
#include "SpeakerControl.hpp"

class NoteSenderDummy : public rtos::task<>{
private:
	SpeakerControl& speakerControl;
	note* notesArray;
	
public:
	NoteSenderDummy(const unsigned int priority, const char* taskName, SpeakerControl& _speakerControl, note* _notesArray): task(priority, taskName), speakerControl(_speakerControl), notesArray(_notesArray){}
	
	void main(){
		hwlib::wait_ms(100);
		hwlib::cout << "Sending Data\n";
		speakerControl.MakeSound(notesArray);
		while(true){hwlib::wait_ms(1000000);}
	}
};

int main(void){
	
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms(500);
	//SpeakerControl::createSounds();
	hwlib::cout << "Starting now!0\n";
	hwlib::target::pin_out SpeakerPin = hwlib::target::pin_out(hwlib::target::pins::d12);
	
	hwlib::cout << "Starting now!1\n";
	Speaker speaker = Speaker(SpeakerPin);
	
	hwlib::cout << "Starting now!2\n";
	SpeakerControl speakerControl = SpeakerControl(0, "SpeakerTask", speaker);
	
	hwlib::cout << "Starting now!3\n";
	note notesArray[2] = {note( 1108,  1250000 ),note( -1,  -1 )};
	
	hwlib::cout << "Starting now!4\n";
	NoteSenderDummy Dummy = NoteSenderDummy(1, "SendTask", speakerControl, notesArray);
	hwlib::cout << "Starting now!5\n";
	rtos::run();
	
}
