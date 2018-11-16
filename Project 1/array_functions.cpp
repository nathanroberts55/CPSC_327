/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
//============================================================================
#include "array_functions.h"
#include <sstream>
#include <cstring>
#include <locale>
#include <algorithm>
#include "utilities.h"
#include "constants.h"
using namespace std;
using namespace constants;
//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct Entry {
	string words = "";
	int numOfOccurences = 0;
};
//TODO add a global array of entry structs (global to this file)
struct Entry arrayOfEntries[MAX_WORDS];
//TODO add variable to keep track of next available slot in array
int nextAvailableSlot = 0;
//TODO define all functions in header file

//zero out array that tracks words and their occurrences
void clearArray() {

	for (int i = 0; i < nextAvailableSlot; i++) {
		arrayOfEntries[i].words = "";
		arrayOfEntries[i].numOfOccurences = 0;
	}

	nextAvailableSlot = 0;
}

//how many unique words are in array
int getArraySize() {
	return nextAvailableSlot;
}

//get data at a particular location
std::string getArrayWordAt(int i) {
	return arrayOfEntries[i].words;
}

//get data at a particular location
int getArrayWord_NumbOccur_At(int i) {
	return arrayOfEntries[i].numOfOccurences;
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream) {
	string line;
	if (myfstream.is_open()) {
		while (myfstream.eof()) {
			getline(myfstream, line);
			processLine(line);
		}
		myfstream.close();
		return true;
	} else {
		return false;
	}

}

void extractTokensFromLine(std::string &myString) {
	const char CHAR_TO_SEARCH_FOR = ' ';
	stringstream ss(myString);
	string tempToken;

	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {
	myfile.open(myFileName.c_str(), mode);
	return myfile.is_open();
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}

/*Keep track of how many times each token seen*/
void processToken(std::string &token) {
	if (strip_unwanted_chars(token)) {
		bool inArray = false;
		string tkn = token;

		toUpper(tkn);

		for (int i = 0; i < getArraySize(); i++) {
			string currentWord = arrayOfEntries[i].words;

			toUpper(currentWord);

			if (tkn == currentWord) {
				arrayOfEntries[i].numOfOccurences++;
				inArray = true;
			}
		}
		if (inArray == false) {
//			else {
			arrayOfEntries[nextAvailableSlot].words = tkn;
			arrayOfEntries[nextAvailableSlot].numOfOccurences++;
			nextAvailableSlot++;

		}
	}
}

/*take 1 line and extract all the tokens from it
 feed each token to processToken for recording*/
void processLine(std::string &myString) {
	extractTokensFromLine(myString);
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename) {
	//If there is nothing in the file then the next slot will be at the beginning
	if (nextAvailableSlot == 0) {
		return FAIL_NO_ARRAY_DATA;
	}

	//Create a File to test on
	fstream example;

	//Attempt to Open the File
	example.open(outputfilename.c_str(), ios::out);

	if (example.is_open() == false) {
		return FAIL_FILE_DID_NOT_OPEN;
	} else {
		for (int i = 0; i < getArraySize(); i++) {
			example << arrayOfEntries[i].words << " "
					<< arrayOfEntries[i].numOfOccurences << endl;
		}

		example.close();
		return SUCCESS;
	}

}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 * You are provided with a myentry compare function in the cpp file
 */
void sortArray(constants::sortOrder so) {
	switch (so) {
	case NONE:
		break;
	case ASCENDING:
//		sort(arrayOfEntries, arrayOfEntries + nextAvailableSlot);

		for (int i = 0; i < getArraySize(); i++) {
			for (int j = 1; j < getArraySize() - i; j++) {
				string first_word = arrayOfEntries[j].words;
				string second_word = arrayOfEntries[j - 1].words;

//				std::transform(first_word.begin(), first_word.end(),
//						first_word.begin(), ::tolower);
//				std::transform(second_word.begin(), second_word.end(),
//						second_word.begin(), ::tolower);

				toUpper(first_word);
				toUpper(second_word);

//				if (second_word.compare(first_word) > 0) {

				if (second_word > first_word) {
					swap(arrayOfEntries[j - 1], arrayOfEntries[j]);
				}
			}
		}
		break;
	case DESCENDING:
//		for (int i = 0; i < getArraySize(); i++) {
//			for (int j = 0; j < getArraySize() - 1; j++) {
//				string first_word = arrayOfEntries[i].words;
//				string second_word = arrayOfEntries[j - 1].words;
//
//				std::transform(first_word.begin(), first_word.end(),
//						first_word.begin(), ::tolower);
//				std::transform(second_word.begin(), second_word.end(),
//						second_word.begin(), ::tolower);
//
////				toUpper(first_word);
////				toUpper(second_word);
//
//				if (second_word.compare(first_word) < 0) {
//					swap(arrayOfEntries[j - 1], arrayOfEntries[i]);
//				}
//			}
//		}
		break;
	case NUMBER_OCCURRENCES:
		for (int i = 0; i < getArraySize(); i++) {
			for (int j = 0; j < getArraySize() - 1; j++) {
				int wordCountOne = arrayOfEntries[i].numOfOccurences;
				int wordCountTwo = arrayOfEntries[j - 1].numOfOccurences;

				if (wordCountTwo > wordCountOne) {
					swap(arrayOfEntries[j - 1], arrayOfEntries[i]);
				}
			}
		}
		break;
	}
}
