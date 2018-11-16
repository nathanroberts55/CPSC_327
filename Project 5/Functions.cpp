/*
 * Functions.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: keith
 */

#include "./includes/Functions.h"
#include "./includes/Smalltalk_American.h"
#include "./includes/ST_American_DonutEnthusiest.h"
#include "./includes/Smalltalk_Brit.h"
#include "./includes/Watch.h"
#include "./includes/constants.h"

using namespace std;

//create a vector with appropriate numbers of Smalltalk_Brit,Smalltalk_American and ST_American_DonutEnthusiest
//objects using unique pointers.  Watches are given sequentially starting with first person in the vector until 
//all watches given or everyone has a watch (case where more watches than people)
//Since we are using c++11 returning this vector by value is fine since the 
//compiler will move the vector on return rather than recreate it (this means there is no copy penalty)
std::vector<std::unique_ptr<Smalltalk>> getPeople(int numBrit, int numAmerican,
		int numbAmericanDonutEnthusiest, int numWatches) {

	//create a vector to hold SmallTalk unique pointers
	vector<unique_ptr<Smalltalk>> talkerVector;

	//add brits to vector
	for (int i = 0; i < numBrit; i++) {
		//Creates talkers pointer
		Smalltalk_Brit *br = new Smalltalk_Brit(i);
		//Gives them phrases
		br->populatePhrases();
		//turns the talker pointer into a unique pointer
		unique_ptr<Smalltalk> p(br);
		//pushes unique pointer to vector
		//move() tells the compiler that the pointer might be moved from its
		//initial location
		talkerVector.push_back(move(p));
	}

	//add americans  to vector
	for (int i = 0; i < numAmerican; i++) {
		//Creates talkers pointer
		Smalltalk_American *am = new Smalltalk_American(i);
		//Gives them phrases
		am->populatePhrases();
		//turns the talker pointer into a unique pointer
		unique_ptr<Smalltalk> p(am);
		//pushes unique pointer to vector
		//move() tells the compiler that the pointer msight be moved from its
		//initial location
		talkerVector.push_back(move(p));
	}

	//add american donut enthusiest  to vector
	for (int i = 0; i < numbAmericanDonutEnthusiest; i++) {
		//Creates talkers pointer
		ST_American_DonutEnthusiest *de = new ST_American_DonutEnthusiest(i);
		//Gives them phrases
		de->populatePhrases();
		//turns the talker pointer into a unique pointer
		unique_ptr<Smalltalk> p(de);
		//pushes unique pointer to vector
		//move() tells the compiler that the pointer might be moved from its
		//initial location
		talkerVector.push_back(move(p));
	}

	//create some watches (as long as number watches <= numb people)	
	//then give the watches away to first NUM_WATCHES people in the vector
	//keep in mind that you are responsible for deleting any pointers to 
	//watches allocated on the heap when you are finished using the vector you return 
	//from this function(see Smalltalk header for hints)
	int totalPeople = numAmerican + numBrit + numbAmericanDonutEnthusiest;

	//loops for the number of people and number of watches
	//will break when counter is greater than the number of people or watches
	for (int i = 0; i < numWatches && i < totalPeople; i++) {
		//makes a watch
		Watch *rolex = new Watch();
		//gives the person a watch
		talkerVector.at(i)->giveWatch(rolex);
	}

	//return your vector
	return talkerVector;
}

