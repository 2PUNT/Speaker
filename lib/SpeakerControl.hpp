#ifndef SPEAKERCONTROL_HPP
#define SPEAKERCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "Speaker.hpp"
#include "note.hpp"

extern note* GameOverSound;
extern note* ShootSound;
extern note* HitSound;
//void createSounds();

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
	///@fn SpeakerControl::SpeakerControl(const unsigned int priority, const char* taskName, Speaker & _speaker)
    ///@brief The constructor for the SpeakerControl class.
    ///@details This constructor creates a SpeakerControl object.
	///@param priority The priority of the speaker.
	///@param name The name of the speaker.
	///@param _speaker A @c Speaker object.
	SpeakerControl(const unsigned int priority, const char* taskName, Speaker & _speaker):
		task(priority, taskName), soundPool("SoundPool"), newSoundFlag(this, "NewSoundFlag"),
		NoteDurationTimer(this, "NoteDurationTimer"), NoteHalfPeriodTimer(this, "NoteHalfPeriodTimer"),
		speaker(_speaker){masterState = Idle; subState = MakingSound;}
	
	///@fn void SpeakerControl::MakeSound(note* Sound)
    ///@brief Plays sound.
    ///@details This method plays a sound.
	///@param Sound A @c note* object. These notes are defined in the @c note class.
	void MakeSound(note* Sound);
	
	///@fn void Speaker::main()
    ///@brief The main of the Speaker task.
	void main();
	
};

#endif
