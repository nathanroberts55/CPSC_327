/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include <cmath>
#include "../327_proj3_test/includes/constants.h"
#include "../327_proj3_test/includes/StringParserClass.h"

using namespace std;
using namespace KP_StringParserClass;

//Don't forget to initialize member variables
StringParserClass::StringParserClass(void) :
		pStartTag(0), pEndTag(0), areTagsSet(false) {
//	pStartTag = 0;
//	pEndTag = 0;
//	areTagsSet = false;
}

//call cleanup to release any allocated memory
StringParserClass::~StringParserClass(void) {
	cleanup();
}

//these are the start tag and the end tags that we want to find,
//presumably the data of interest is between them, please make a
//COPY of what pStartTag and pEndTag point to.  In other words
//DO NOT SET pStartTag = pStart
//returns:
//SUCCESS
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	//ERROR_TAGS_NULL if either pStart or pEnd is null
	if (pStart == 0 || pEnd == 0) {
		return ERROR_TAGS_NULL;
	}

	//COPY of what pStartTag and pEndTag point to.  In other words
	//DO NOT SET pStartTag = pStart
//	unsigned int startLength = strlen(pStart);
//	unsigned int endLength = strlen(pEnd);

	pStartTag = strdup(pStart);
	pEndTag = strdup(pEnd);

//	strncpy(pStartTag, pStart, startLength);
//	strncpy(pEndTag, pEnd, endLength);

	return SUCCESS;
}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that info only to myVector
//returns
//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru,
		std::vector<std::string> &myVector) {
	//First clears myVector
	myVector.clear();

	//ERROR_TAGS_NULL if either pStart or pEnd is null
	if (pStartTag == 0 || pEndTag == 0) {
		return ERROR_TAGS_NULL;
	}

	//ERROR_DATA_NULL pDataToSearchThru is null
	if (pDataToSearchThru == 0) {
		return ERROR_DATA_NULL;
	}
	string test;
	char *stringToken;
	char *pBeginFirstTag = pDataToSearchThru;
	char *pEndingFirstTag = pDataToSearchThru + strlen(pDataToSearchThru);
	char *pBeginSecondTag = pDataToSearchThru;
	char *pEndingSecondTag = pDataToSearchThru + strlen(pDataToSearchThru);
//	char *startDataForVector;
//	char *endDataForVector;
	char *endAllData = pDataToSearchThru + strlen(pDataToSearchThru);

	for (unsigned int i = 0; i < strlen(pDataToSearchThru); i++) {
		char *startDataForVector;
		char *endDataForVector;
//		char *pBeginFirstTag = pDataToSearchThru;
//		char *pEndingFirstTag = pDataToSearchThru + strlen(pDataToSearchThru);
//		char *pBeginSecondTag = pDataToSearchThru;
//		char *pEndingSecondTag = pDataToSearchThru + strlen(pDataToSearchThru);
		//Find Start Tag
		if (findTag(pStartTag, pBeginFirstTag, pEndingFirstTag) == FAIL) {
			return SUCCESS;
		}
		//Set startData to push to vector
		startDataForVector = pEndingFirstTag + 1;
		pDataToSearchThru = startDataForVector;

		//Find the End Tag using startData
		if (findTag(pEndTag, pBeginSecondTag, pEndingSecondTag) == FAIL) {
			return SUCCESS;
		}

		//Set End of Data to begin at end of SecondTag - 1
		endDataForVector = pBeginSecondTag - 1;
		pDataToSearchThru = endDataForVector;

		//StrnDup the data between the tags
		int length = ((strlen(startDataForVector)) - strlen(endDataForVector))
				+ 1;
		stringToken = strndup(startDataForVector, length);
		string token(stringToken);
//	test = pDataToSearchThru.substr(strlen(startDataForVector), strlen(endDataForVector));
		//Push to the vector
		myVector.push_back(token);
//		pBeginFirstTag = pDataToSearchThru;
//		pBeginSecondTag = pDataToSearchThru;
//		pDataToSearchThru = pEndingSecondTag;
	}

//	int startTagLength = strlen(pStartTag);
//	int endTagLength = strlen(pEndTag);
//
//	char *startData = pStartTag + startTagLength;
//	char *endData = pEndTag - 1;
//
//	for (int i = 0; i < strlen(pDataToSearchThru); i++) {
//		data += pDataToSearchThru[i];
//	}
//
////	int start = data.find(pStartTag);
////	int end = data.find(pEndTag);
////	string betweenTags = data.substr(start - end);
//
//	for (unsigned int i = 0;
//			pDataToSearchThru[i] > startData[0]
//					&& pDataToSearchThru[i] > endData[0]; i++) {
////		while (startData != endData) {
////			token += startData;
////			startData++;
////		}
//		if (pDataToSearchThru[i] > startData[0]
//				&& pDataToSearchThru[i] > endData[0]) {
//			token += pDataToSearchThru[i];
//
//		}
//		myVector.push_back(token);
//	}

	return SUCCESS;
}
//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,
		char *&pEnd) {
	if (pStart == 0 || pEnd == 0) {
		return ERROR_TAGS_NULL;
	}

//	if (pEndTag == 0 && pTagToLookFor == 0) {
//		return FAIL;
//	}

	if (pEndTag == 0 && pTagToLookFor == 0) {
		return FAIL;
	}

	int tagLength = strlen(pTagToLookFor);
//	pEnd = pStart + tagLength;

//	int tagArraySize = sizeof(pTagToLookFor) / sizeof(char);

	unsigned int startLength = strlen(pStart);
	char *pIterator = new char[startLength + 1];
	strncpy(pIterator, pStart, startLength);

	for (unsigned int i = 0; i < strlen(pIterator); i++) {

		if (*(pIterator + i) == pTagToLookFor[0]) {

			//Sets pStart to the beginning of the possible tag
			//compare the tag to what I found
			if (strncmp((pIterator + i), pTagToLookFor, tagLength) == 0) {
				//set pEnd to the end of the tag
				pStart = (pIterator + i);
				pEnd = (pIterator + i) + (tagLength - 1);
				return SUCCESS;
			}
		}
	}

	return FAIL;

}

void StringParserClass::cleanup() {

}

