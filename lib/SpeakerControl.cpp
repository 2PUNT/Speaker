#include "hwlib.hpp"
#include "rtos.hpp"

#include "Speaker.hpp"
#include "SpeakerControl.hpp"
#include "note.hpp"

void SpeakerControl::MakeSound(note* Sound){
	hwlib::cout << "SpeakerControl: New sound received\n";
	soundPool.write(Sound);
	newSoundFlag.set();
}
	
void SpeakerControl::main(){
	rtos::event combinedEvents = NoteDurationTimer+NoteHalfPeriodTimer+newSoundFlag;
	rtos::event lastEvent = NoteDurationTimer+NoteHalfPeriodTimer+newSoundFlag;
	hwlib::cout << "SpeakerControl: Starting up\n";
	while(true){
		switch(masterState){
			case Idle:{
				hwlib::cout << "SpeakerControl: Now Idle\n";
				speaker.MakeSound(false);
				wait(newSoundFlag);
				soundNotes = soundPool.read();
				noteIndex = 0;
				currentNote = soundNotes[noteIndex];
				masterState = PlayingNote;
				break;}
				
			case PlayingNote:{
				//hwlib::cout << "SpeakerControl: PlayingNote\n";
				NoteDurationTimer.set(currentNote.duration);
				subState = MakingSound;
				breakSubStateLoop = false;
				while(!breakSubStateLoop){
					switch(subState){ // optimization is possible
						case MakingSound:{
							NoteHalfPeriodTimer.set(1000000/(2*currentNote.frequency));
							speaker.MakeSound(true);
							//lastEvent = NoteDurationTimer+NoteHalfPeriodTimer+newSoundFlag;
							lastEvent = wait(combinedEvents);
							if(lastEvent == NoteHalfPeriodTimer) subState = Silent;
							else if(lastEvent == NoteDurationTimer){
								breakSubStateLoop = true;
								noteIndex++;
								currentNote = soundNotes[noteIndex];
								if(currentNote.frequency == -1) {masterState = Idle; break;}
							}else if(lastEvent == newSoundFlag){
								breakSubStateLoop = true;
								soundNotes = soundPool.read();
								noteIndex = 0;
								currentNote = soundNotes[noteIndex];
							}
							break;
						}
						case Silent:{
							NoteHalfPeriodTimer.set(1000000/(2*currentNote.frequency));
							speaker.MakeSound(false);
							//lastEvent = NoteDurationTimer+NoteHalfPeriodTimer+newSoundFlag;
							lastEvent = wait(combinedEvents);
							if(lastEvent == NoteHalfPeriodTimer) subState = MakingSound;
							else if(lastEvent == NoteDurationTimer){
								breakSubStateLoop = true;
								noteIndex++;
								currentNote = soundNotes[noteIndex];
								if(currentNote.frequency == -1) {masterState = Idle; break;}
							}else if(lastEvent == newSoundFlag){
								breakSubStateLoop = true;
								soundNotes = soundPool.read();
								noteIndex = 0;
								currentNote = soundNotes[noteIndex];
							}
							break;
						}
					}
				}
				break;
			}
		}
	}
}

/*
class SpeakerControl : public rtos::task<>{
private:
	rtos::pool<note*> soundPool;
	rtos::flag newSoundFlag;
	rtos::timer NoteDurationTimer;
	rtos::timer NoteHalfPeriodTimer;
	
	enum masterState{ Idle,  PlayingNote};
	enum subState{ MakingSound, Silent };
	bool breakSubStateLoop;
	Speaker & speaker;
	int noteIndex;
	note currentNote;
	note* soundNotes;
public:
	SpeakerControl(const unsigned int priority, const char* taskName, Speaker & _speaker):
		task(priority, taskName), soundPool("SoundPool"), newSoundFlag(this, "NewSoundFlag"),
		NoteDurationTimer(this, "NoteDurationTimer"), NoteHalfPeriodTimer(this, "NoteHalfPeriodTimer"),
		speaker(_speaker){masterState = Idl); subState = MakingSound;}
	
	void MakeSound(note* Sound);
	
	void main();
};

 */
