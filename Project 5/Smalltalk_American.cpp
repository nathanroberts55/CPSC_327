/*
 * SmalltalkAmerican.cpp
 *
 *  Created on: Mar 25, 2018
 *      Author: Nate Roberts
 */

#include "./includes/Smalltalk_American.h"
#include "./includes/constants.h"

using namespace std;

Smalltalk_American::Smalltalk_American(int i) :
		Smalltalk(AMERICAN, i) {
}

Smalltalk_American::Smalltalk_American(std::string myNationality, int i) :
		Smalltalk(AMERICAN, i) {
	current_phrase = 0;
	pWatch = 0;
}

Smalltalk_American::~Smalltalk_American(void) {

}

void Smalltalk_American::populatePhrases() {
	//Pushes all of the phrases to the vector
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_1);
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_2);
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_3);
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_4);
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_5);
}
