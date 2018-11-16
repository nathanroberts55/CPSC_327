/*
 * FileReader.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include "../327_proj3_test/includes/FileIO.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;

//trys to open filename, and return its contents in contents
//it will strip out only \n's (char return\line feed)
//returns:
//SUCCESS all worked, contents string contains all in the file
//COULD_NOT_OPEN_FILE_TO_READ contents string is cleared
int KP_FileIO::getFileContents(const std::string &filename,
		std::string &contents) {
	ifstream example;

	example.open(filename.c_str());


	if (!example.is_open()) {
		return COULD_NOT_OPEN_FILE_TO_READ;
	}

//	stringstream sstream;
	string line;


	while(!example.eof()){
		getline(example,line);
		contents += line;
	}


	return SUCCESS;
}

//trys to open filename, and serialize  myEntryVector contents to it
//returns:
//SUCCESS all worked, filename contains myEntryVector strings
//COULD_NOT_OPEN_FILE_TO_WRITE
int KP_FileIO::writeVectortoFile(const std::string filename,
		std::vector<std::string> &myEntryVector) {

	ofstream example;

	example.open(filename.c_str());

	if(!example.is_open()){
		return COULD_NOT_OPEN_FILE_TO_WRITE;
	}

	for(unsigned int i = 0; i < myEntryVector.size(); i++){
		example << myEntryVector[i];
	}


	if(example.is_open()){
		example.close();
	}

	return SUCCESS;
}

