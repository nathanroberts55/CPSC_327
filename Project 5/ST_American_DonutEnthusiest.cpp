/*
 * ST_American_DonutEnthusiest.cpp
 *
 *  Created on: Mar 25, 2018
 *      Author: Nate Roberts
 */

#include "includes/ST_American_DonutEnthusiest.h"
#include "./includes/constants.h"

ST_American_DonutEnthusiest::ST_American_DonutEnthusiest(int i) :
		Smalltalk_American(AMERICAN_DE, i) {
}

ST_American_DonutEnthusiest::~ST_American_DonutEnthusiest(void) {
}

void ST_American_DonutEnthusiest::populatePhrases() {
	//Pushes all of the phrases to the vector
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_1);
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_2);
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_3);
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_4);
	mySmallTalk.push_back(AMERICAN_DE_PHRASE_5);
}
