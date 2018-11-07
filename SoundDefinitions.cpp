#include "SpeakerControl.hpp"
#include "note.hpp"
#include "hwlib.hpp"

note* GameOverSound;
note* ShootSound;
note* HitSound;

/* void createSounds(){
	note gameOverSound[] = {note( 1108,  125000 ),note( -1,  -1 )};
	note shootSound[] = {note( 1108,  125000 ),note( -1,  -1 )};
	note hitSound[] = {note( 1108,  125000 ),note( -1,  -1 )};
	
	GameOverSound = gameOverSound;
	ShootSound = shootSound;
	HitSound = hitSound;
	hwlib::cout << "sounds created\n";
} */

/* void SpeakerControl::createSounds(){
	note gameOverSound[] = {note( 1108,  125000 ),note( -1,  -1 )};
	note shootSound[] = {note( 1108,  125000 ),note( -1,  -1 )};
	note hitSound[] = {note( 1108,  125000 ),note( -1,  -1 )};
	
	note* SpeakerControl::GameOverSound = gameOverSound;
	note* SpeakerControl::ShootSound = shootSound;
	note* SpeakerControl::HitSound = hitSound;
}
 */