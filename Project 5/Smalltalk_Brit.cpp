/*
 * SmalltalkBrit.cpp
 *
 *  Created on: Mar 25, 2018
 *      Author: Nate Roberts
 */

#include "includes/Smalltalk_Brit.h"
#include "./includes/constants.h"

Smalltalk_Brit::Smalltalk_Brit(int i) :
		Smalltalk(BRIT, i) {
}

Smalltalk_Brit::~Smalltalk_Brit(void) {
}

void Smalltalk_Brit::populatePhrases() {
	//Pushes all of the phrases to the vector
	mySmallTalk.push_back(BRIT_1);
	mySmallTalk.push_back(BRIT_2);
	mySmallTalk.push_back(BRIT_3);
	mySmallTalk.push_back(BRIT_4);
	mySmallTalk.push_back(BRIT_5);
	mySmallTalk.push_back(BRIT_6);
	mySmallTalk.push_back(BRIT_7);

}
