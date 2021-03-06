#ifndef _NOTE_HPP
#define _NOTE_HPP
#include "hwlib.hpp"
// ===========================================================================
//
// frequencies of standard notes
//
// ===========================================================================

class note {
public:

	// from https://www.seventhstring.com/resources/notefrequencies.html
	static const int A4  = 440;
	static const int A4s = 466;
	static const int B4  = 494;
	static const int C5  = 523;
	static const int C5s = 554;
	static const int D5  = 587;
	static const int D5s = 622;
	static const int E5  = 659;
	static const int F5  = 698;
	static const int F5s = 740;
	static const int G5  = 784;
	static const int G5s = 830;
	static const int A5  = 880;
	static const int A5s = 932;
	static const int B5  = 987;
	
	///The frequency of the note.
	int frequency;
	
	/// Length of a full measure.
	static const int dF = 1'000'000;

	/// Length of a half measure.
	static const int dH = dF / 2;

	/// Lenght of a quarter measure.
	static const int dQ = dF / 4;

	/// The duration of the note.
	int duration;
	
	///@fn note::note()
	///@brief The constructor for the note class.
	///@details This constructor creates a note object.
	note(): frequency(-1), duration(-1){}
	
	///@fn note::note(int _frequency, int _duration)
	///@brief The constructor for the note class.
	///@details This constructor creates a note object.
	///@param _frequency The frequency of the note.
	///@param _duration The duration of the note.
	note(int _frequency, int _duration): frequency(_frequency), duration(_duration){}
	
	///@fn note& note::operator=(const note& rhs)
	///@brief Asign a @c note object to another @c note object.
	///@details This overloaded operator= asigns a @c note object to another @c note object.
	///@param rhs The right hand side parameter, a reference to a const @c note.
	note& operator=(const note& rhs){
		frequency = rhs.frequency;
		duration = rhs.duration;
		return *this;
	}
};

#endif

