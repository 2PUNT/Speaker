#ifndef SPEAKERCONTROL_HPP
#define SPEAKERCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "Speaker.hpp"
#include "note.hpp"

note* GameOverSound;
note* ShootSound;
note* HitSound;

enum SpeakerControlMasterState{ Idle,  PlayingNote}; // in class?
enum SpeakerControlSubState{ MakingSound, Silent };

class SpeakerControl : public rtos::task<>{
private:
	rtos::pool<note*> soundPool;
	rtos::flag newSoundFlag;
	rtos::timer NoteDurationTimer;
	rtos::timer NoteHalfPeriodTimer;
	
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
	
	/* static note GameOverSound[];
	static note ShootSound[];
	static note HitSound[]; */
	
	void MakeSound(note* Sound);
	
	void main();
};

#endif
