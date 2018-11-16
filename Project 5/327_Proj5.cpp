
/*
 * SmalltalkBrit.cpp
 *
 *  Created on: Mar 25, 2018
 *      Author: Nate Roberts
 */
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "../../327_Proj5_Lib/includes/Smalltalk.h"
#include "../../327_Proj5_Lib/includes/Smalltalk_Brit.h"
#include "../../327_Proj5_Lib/includes/Smalltalk_American.h"
#include "../../327_Proj5_Lib/includes/ST_American_DonutEnthusiest.h"
#include "../../327_Proj5_Lib/includes/Functions.h"

using namespace std;

int main() {
	//Creates a vector with Varying amount of people I am trying to test and varying amount of watches I am trying to test
	vector<unique_ptr<Smalltalk>> testVector = getPeople(4, 4, 4, 20);

	//Test Vector Size
	cout << testVector.size() << endl;

	//Test watches give the time
	for (unsigned int i = 0; i < testVector.size(); i++) {
		cout << testVector.at(i)->getTime() << endl;
	}

	//Want to take back some watches
	//How many watches I'm taking back
	string numOfTakenWatches = "Taking back " + to_string(testVector.size() / 2)
			+ " watches";
	cout << numOfTakenWatches << endl;

	//Test takeWatch
	//Takes back some watches
	for (unsigned int i = 0; i < (testVector.size() / 2); i++) {
		testVector.at(i)->takeWatch();
	}

	//Test watches give the time
	for (unsigned int i = 0; i < testVector.size(); i++) {
		cout << testVector.at(i)->getTime() << endl;
	}

	//Test saySomething
	//Picks a random talker to test
	int randomTalker = (rand() % testVector.size());
	//calls say something 8 times if the person is a BRIT then 8 will be enough circle back around).
	cout << testVector.at(randomTalker)->saySomething() << endl;
	cout << testVector.at(randomTalker)->saySomething() << endl;
	cout << testVector.at(randomTalker)->saySomething() << endl;
	cout << testVector.at(randomTalker)->saySomething() << endl;
	cout << testVector.at(randomTalker)->saySomething() << endl;
	cout << testVector.at(randomTalker)->saySomething() << endl;
	cout << testVector.at(randomTalker)->saySomething() << endl;
	cout << testVector.at(randomTalker)->saySomething() << endl;

}
