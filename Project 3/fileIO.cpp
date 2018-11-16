#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "../includes_usr/constants.h"
#include "../includes_usr/fileIO.h"
using namespace std;

//Doesn't work
////Checking if the file is empty
//bool is_empty(std::ifstream& pFile) {
//	return pFile.peek() == std::ifstream::traits_type::eof();
//}

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename) {
	books.clear();

	//Creates the fstream to test if the file can open
	ifstream example;

	//Attempts to open the file
	example.open(filename);

	//COULD_NOT_OPEN_FILE if cannot open filename
	if (!example.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

//	bool noBooks = is_empty(example);

//NO_BOOKS_IN_LIBRARY if there are 0 entries in books
//	if (noBooks == true) {
//		return NO_BOOKS_IN_LIBRARY;
//	}

//values needed to read
	string line;
	string token;
	int stateToken;
	stringstream sstream;
	book testBook;
	const char COMMA_TO_SEARCH_FOR = ',';
	std::string::size_type sz;
//	book_checkout_state temp_enum_state;
//	int state;

// Reading from file to vector
	while (!example.eof()) {
		//gets line from the file
		getline(example, line);
		if (line.length() == 0) {
			if (books.size() == 0) {
				return NO_BOOKS_IN_LIBRARY;
			} else {
				continue;
			}
		}
		sstream.str(line);

		//Clears the book data
		testBook.title = "";
		testBook.author = "";
		testBook.loaned_to_patron_id = 0;
		testBook.state = UNKNOWN;
//		testBook.book();

//		temp_enum_state = UNKNOWN;
		//get book ID
		getline(sstream, token, COMMA_TO_SEARCH_FOR);
		testBook.book_id = stoi(token);
		//get the book title
		getline(sstream, token, COMMA_TO_SEARCH_FOR);
		testBook.title = token;
		//get the book author
		getline(sstream, token, COMMA_TO_SEARCH_FOR);
		testBook.author = token;
		//get the book State
		getline(sstream, token, COMMA_TO_SEARCH_FOR);
		//		if (state == 0) {
//			temp_enum_state == UNKNOWN;
//		} else if (state == 1) {
//			temp_enum_state == IN;
//
//		} else {
//			temp_enum_state == OUT;
//		}
//		testBook.state = temp_enum_state;

//		if(token == UNKNOWN || token == 0){
//			testBook.state == UNKNOWN;
//		}
//		else if (token == IN ){
//			testBook.state == IN;
//		}
//		else{
//			testBook.state == OUT;
//		}
//		testBook.state == token;
		stateToken = stoi(token);
		testBook.state = static_cast<book_checkout_state>(stateToken);
		//get the patron ID
		getline(sstream, token, COMMA_TO_SEARCH_FOR);
		testBook.loaned_to_patron_id = stoi(token);

		//add to the vector
		books.push_back(testBook);
		//clear the stream
		sstream.clear();

		//NO_BOOKS_IN_LIBRARY if there are 0 entries in books
		if (books.size() == 0) {
			return NO_BOOKS_IN_LIBRARY;
		}
	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename) {

	//Creates the fstream to test if the file can open
	ofstream example;

	//Attempts to open the file
	example.open(filename);

	//COULD_NOT_OPEN_FILE if cannot open filename
	if (example.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	}

	//NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
	if (books.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	//Writing the books from the file to the vector
	//String with the book info
	string bookInfo;

	//Goes through the vector and prints the patron's info
	for (unsigned int i = 0; i < books.size(); i++) {
		bookInfo = to_string(books[i].book_id) + "," + books[i].title + ","
				+ books[i].author + "," + to_string(books[i].state) + ","
				+ to_string(books[i].loaned_to_patron_id);

		example << bookInfo << endl;
	}

	//if the file is open, close it.
	if (example.is_open() == true) {
		example.close();
	}

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename) {
	//Clears the Patron Vector
	patrons.clear();

	//Creates the fstream to test if the file can open
	ifstream example;

	//Attempts to open the file
	example.open(filename);

	//COULD_NOT_OPEN_FILE if cannot open filename
	if (example.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	}

//	//NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
//	if (patrons.size() == 0) {
//		return NO_PATRONS_IN_LIBRARY;
//	}

	//Variables needed for the reading
	string line;
	string token;
	stringstream sstream;
	patron testPatron;
	const char COMMA_TO_SEARCH_FOR = ',';

	//Reading from the file to the vector
	while (!example.eof()) {
		getline(example, line);
		if (line.length() == 0) {
			if (patrons.size() == 0) {
				return NO_PATRONS_IN_LIBRARY;
			} else {
				continue;
			}
		}
		sstream.str(line);

		//Clearing the test Patron
		testPatron.patron_id = UNINITIALIZED;
		testPatron.name = "";
		testPatron.number_books_checked_out = NONE;

		//Gets the patron id and converts it to a int
		getline(sstream, token, COMMA_TO_SEARCH_FOR);
		testPatron.patron_id = stoi(token);

		//Gets the patrons name
		getline(sstream, token, COMMA_TO_SEARCH_FOR);
		testPatron.name = token;

		//Gets the patrons number of books checked out and convert to an int
		getline(sstream, token, COMMA_TO_SEARCH_FOR);
		testPatron.number_books_checked_out = stoi(token);

		//Puts the testPatron information into the Patron Vector
		patrons.push_back(testPatron);

		//clear the string stream
		sstream.clear();
	}

	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename) {
	//Create an ofstream to test
	ofstream example;

	//Attempt to open it
	example.open(filename);

	//COULD_NOT_OPEN_FILE if cannot open filename
	if (example.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	}

	//NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
	if (patrons.size() == 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	//String with the patrons info
	string patronInfo;

	//Goes through the vector and prints the patron's info
	for (unsigned int i = 0; i < patrons.size(); i++) {
		patronInfo = to_string(patrons[i].patron_id) + "," + patrons[i].name
				+ "," + to_string(patrons[i].number_books_checked_out);

		example << patronInfo << endl;
	}

	//if the file is open, close it.
	if (example.is_open() == true) {
		example.close();
	}

	return SUCCESS;
}
