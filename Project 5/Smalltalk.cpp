/*
 * Smalltalk.cpp
 *
 *  Created on: Mar 25, 2018
 *      Author: Nate Roberts
 */

#include "./includes/Smalltalk.h"
#include "./includes/constants.h"
#include "./includes/Watch.h"

using namespace std;
//derived class will set Nationality, iPerson. iPerson is just a counter used to distinguish between objects of the same type
Smalltalk::Smalltalk(std::string myNationality, int iPerson) :
		nationality(myNationality), iPerson(iPerson) {
	current_phrase = 0;
	pWatch = 0;
}

//if pWatch !=0 then be sure to delete what it points to
Smalltalk::~Smalltalk(void) {
	if (pWatch != 0) {
		delete pWatch;
		pWatch = NULL;
	}
}

//cycles through phrases added in populatePhrases. Returns them 1 by 1 starting with the first and ending
//with the last and then it starts over
//takes the form Nationality iPerson: phrase
//for instance the following string comes from an American instance, the 10th iPerson and it is printing AMERICAN_PHRASE_2
//AMERICAN 10:Why yes, I would like to supersize that
std::string Smalltalk::saySomething() {
//	unsigned int counter = 0;
	string talkToMeNice;

	//Formats String like "AMERICAN 10:Why yes, I would like to supersize that"
	talkToMeNice = this->nationality + " " + to_string(this->iPerson) + ":"
			+ this->mySmallTalk.at(this->current_phrase) + "\n";

	//Changes current phrase so that it moves to the next phrase
	this->current_phrase = (this->current_phrase + 1)
			% this->mySmallTalk.size();

	//returns the formatted string with the current phrase
	return talkToMeNice;
}

//returns the time (if pWatch != 0) in the form of THE_CURRENT_TIME_IS: and then the time
//or I_DO_NOT_HAVE_A_WATCH string (if pWatch == 0)
std::string Smalltalk::getTime() {
	//If person doesnt have a watch they say they dont
	if (pWatch == 0) {
		return I_DO_NOT_HAVE_A_WATCH;
	}

	// Otherwise they give you the time
	return THE_CURRENT_TIME_IS + " " + pWatch->getTime();
}

//if this object has a watch it is taken away, otherwise a NULL pointer is returned
//this means return the pointer to the watch so another smalltalker
//can use the watch.  Set this->pWatch =NULL.  This transaction simulates giving up a watch
//this is one of the few times when a shallow copy is appropriate
Watch* Smalltalk::takeWatch() {
	//If they do not have a watch, then they return that same watch so someone else can use it
	if (pWatch == 0) {
		return pWatch;
	}

	//Otherwise they set the current person's watch to null as to take it away
	return this->pWatch = 0;

}

//if already have a watch then return false and dont change pWatch pointer
//otherwise accept watch (return true) and set this->pWatch=pWatch
//this is one of the few times when a shallow copy is appropriate
bool Smalltalk::giveWatch(Watch* pWatch) {
	//If the person has a watch return
	if (this->pWatch != NULL) {
		return false;
	}

	//Give the person the watch and return true
	this->pWatch = pWatch;
	return true;
}

