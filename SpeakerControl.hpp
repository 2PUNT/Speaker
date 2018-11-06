#ifndef SPEAKERCONTROL_HPP
#define SPEAKERCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "Speaker.hpp"
#include "note.hpp"

class SpeakerControl : public rtos::task<>{
private:
	rtos::pool<note*> soundPool;
	rtos::flag newSoundFlag;
	rtos::timer NoteDurationTimer;
	rtos::timer NoteHalfPeriodTimer;
	
	enum SpeakerControlMasterState{ Idle,  PlayingNote};
	enum SpeakerControlSubState{ MakingSound, Silent };
	SpeakerControlMasterState masterState;
	SpeakerControlSubState subState;
	
	bool breakSubStateLoop;
	Speaker & speaker;
	int noteIndex;
	note currentNote;
	note* soundNotes;
public:
	SpeakerControl(const unsigned int priority, const char* taskName, Speaker & _speaker):
		task(priority, taskName), soundPool("SoundPool"), newSoundFlag(this, "NewSoundFlag"),
		NoteDurationTimer(this, "NoteDurationTimer"), NoteHalfPeriodTimer(this, "NoteHalfPeriodTimer"),
		speaker(_speaker){masterState = Idle; subState = MakingSound;}
	
	void MakeSound(note* Sound);
	
	void main();
	
	static note* GameOverSound;
	static note* ShootSound;
	static note* HitSound;
	//static void createSounds();
	
};

#endif
