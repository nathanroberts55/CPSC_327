#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>

#include "../includes_usr/library.h"
#include "../includes_usr/datastructures.h"
#include "../includes_usr/fileIO.h"
using namespace std;

//NOTE: please ensure patron and book data are loaded from disk before calling the following
//NOTE: also make sure you save patron and book data to disk any time you make a change to them
//NOTE: for files where data is stored see constants.h BOOKFILE and PATRONFILE
std::vector<book> books;
std::vector<patron> patrons;

/*
 * clear books and patrons containers
 * then reload them from disk 
 */
void reloadAllData() {
	loadBooks(books, BOOKFILE.c_str());
	loadPatrons(patrons, PATRONFILE.c_str());
}

/* checkout a book to a patron
 * first load books and patrons from disk
 * make sure patron enrolled (patronid is assigned to a patron in patrons container)
 * make sure book in collection (bookid is assigned to a book in books container)
 * 
 * see if patron can check out any more books 
 * 	if not return TOO_MANY_OUT patron has the MAX_BOOKS_ALLOWED_OUT
 * 	
 * if so then check the book out to the patron, set the following fields for the book in the
 * books container
 * book.loaned_to_patron_id = patronid;
 * book.state = OUT;
 * 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 *         PATRON_NOT_ENROLLED
 * 		   BOOK_NOT_IN_COLLECTION
 *         TOO_MANY_OUT patron has the max number of books allowed checked out
 */
int checkout(int bookid, int patronid) {
//	//first load books and patrons from disk
//	loadBooks(books, BOOKFILE.c_str());
//	loadPatrons(patrons, PATRONFILE.c_str());

// Now that I know reloadAllData works...
	reloadAllData();

	bool patronInVector = false;
	bool patronHasTooManyBooks = false;
	bool bookInVector = false;

	//Goes through patron vector to find matching ID
	for (unsigned int i = 0; i < patrons.size(); ++i) {
		//If it is found
		if (patronid == patrons[i].patron_id) {
			patronInVector = true;
		}
		if (patrons[i].number_books_checked_out
				== MAX_BOOKS_ALLOWED_OUT) {
			patronHasTooManyBooks = true;
		}
		//if it not found
//		else {
//			patronInVector = false;
//		}
	}

	// Checks to see if book is enrolled and returns  PATRON_NOT_ENROLLED if not.
	if (patronInVector == false) {
		return PATRON_NOT_ENROLLED;
	}

	// Checks to see if the patron has too many books out and returns TOO_MANY_OUT is so
	if (patronHasTooManyBooks == true) {
		return TOO_MANY_OUT;
	}

	//Goes through book vector to see if book is available
	for (unsigned int i = 0; i < books.size(); ++i) {
		//if found
		if (bookid == books[i].book_id) {
			bookInVector = true;
		}
	}

	if(books[bookid].state != IN){
		bookInVector = false;
	}
	// Checks to see if patron is in collection and returns BOOK_NOT_IN_COLLECTION if not.
	if (bookInVector == false) {
		return BOOK_NOT_IN_COLLECTION;
	}
	// if so then check the book out to the patron, set the following fields for the book in the
	// books container
	// book.loaned_to_patron_id = patronid;
	// book.state = OUT;

	books[bookid].state = OUT;
	books[bookid].loaned_to_patron_id = patronid;
	patrons[patronid].number_books_checked_out++;

	//Finally save the contents of the books and patrons containers to disk
	saveBooks(books, BOOKFILE.c_str());
	savePatrons(patrons, PATRONFILE.c_str());

	return SUCCESS;
}

/* check a book back in 
 * first load books and patrons from disk
 * make sure book in collection (bookid is assigned to a book in books container)
 *  	
 * if so find the the patron the book is checked out to and decrement his/hers number_books_checked_out
 * then check the book back in by marking the book.loaned_to_patron_id = NO_ONE and the book.state = IN;
 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 * 		   BOOK_NOT_IN_COLLECTION
 */
int checkin(int bookid) {
//	//first load books and patrons from disk
//	loadBooks(books, BOOKFILE.c_str());
//	loadPatrons(patrons, PATRONFILE.c_str());

	// Now that I know reloadAllData works...
	reloadAllData();

	//make sure book in collection (bookid is assigned to a book in books container)
	//Holds if the book is in the vector
	bool bookInVector = false;

	//Goes through book vector to see if book is available
	for (unsigned int i = 0; i < books.size(); ++i) {
		//if found
		if (bookid == books[i].book_id) {
			bookInVector = true;
		}
		//if not found
//		else {
//			bookInVector = false;
//		}
	}

	// Checks to see if book is in collection and returns BOOK_NOT_IN_COLLECTION if not.
	if (bookInVector == false) {
		return BOOK_NOT_IN_COLLECTION;
	}

	//The ID of the patron holding the book
	int idOfPatron = books[bookid].loaned_to_patron_id;

	//if so find the the patron the book is checked out to and decrement his/hers number_books_checked_out
	patrons[idOfPatron].number_books_checked_out--;

	//then check the book back in by marking the book.loaned_to_patron_id = NO_ONE and the book.state = IN;
	books[bookid].loaned_to_patron_id = NO_ONE;
	books[bookid].state = IN;

	//Finally save the contents of the books and patrons containers to disk
	saveBooks(books, BOOKFILE.c_str());
	savePatrons(patrons, PATRONFILE.c_str());

	return SUCCESS;
}

/*
 * enroll a patron, duplicate names are fine as patrons are uniquely identified by their patronid
 * first load books and patrons from disk
 * create a patron object, initialize its fields as appropriate, assign him/her the nextPatronID
 * then push the patron onto the patrons container
 * save all changes to the patrons container to disk
 * return 
 *    the patron_id of the person added
 */
int enroll(std::string &name) {
//	//load books and patrons from disk
//	loadBooks(books, BOOKFILE.c_str());
//	loadPatrons(patrons, PATRONFILE.c_str());

	// Now that I know reloadAllData works...
	reloadAllData();

	//create a patron object, initialize its fields as appropriate, assign him/her the nextPatronID
	patron testPatron;
	testPatron.name = name;
	testPatron.patron_id = patrons.size();
	testPatron.number_books_checked_out = NONE;

	//push the patron onto the patrons container
	patrons.push_back(testPatron);

	//save all changes to the patrons container to disk
	savePatrons(patrons, PATRONFILE.c_str());

	//return the patron_id of the person added
	return patrons[patrons.size()].patron_id;
}

/*
 * the number of books in the books container
 * (ie. if 3 books returns 3)
 * 
 */
int numbBooks() {
	return books.size();
}

/*
 * the number of patrons in the patrons container
 * (ie. if 3 patrons returns 3)
 */
int numbPatrons() {
	return patrons.size();
}

/*the number of books patron has checked out
 *
 *returns a positive number indicating how many books are checked out 
 *        or PATRON_NOT_ENROLLED         
 */
int howmanybooksdoesPatronHaveCheckedOut(int patronid) {
	//If the patron is in the vector
	bool patronInVector = false;

	//search the vector for the patron
	for (unsigned int i = 0; i < patrons.size(); ++i) {
		//If it is found
		if (patronid == patrons[i].patron_id) {
			patronInVector = true;

		}
		//if it not found
//		else {
//			patronInVector = false;
//		}
	}

	//if patron is not in vector
	if (patronInVector == false) {
		return PATRON_NOT_ENROLLED;
	}

	//returns the number of books checked out by the patron given
	return patrons[patronid].number_books_checked_out;
}

/* search through patrons container to see if patronid is there
 * if so returns the name associated with patronid in the variable name
 * 
 * returns SUCCESS found it and name in name
 *         PATRON_NOT_ENROLLED no patron with this patronid
 */
int whatIsPatronName(std::string &name, int patronid) {
	//If the patron is in the vector
	bool patronInVector = false;
//	bool patronNameInVector = false;

//search the vector for the patron
	for (unsigned int i = 0; i < patrons.size(); ++i) {
		//If patron ID is found
		if (patronid == patrons[i].patron_id) {
			patronInVector = true;

		}
		//if patron ID is not found
		else {
			patronInVector = false;
		}

		//If patron name is found
		if (name == patrons[i].name) {
			patronInVector = true;

		}
		//if patron name is not found
		else {
			patronInVector = false;
		}
	}

	//if patron is not in vector
	if (patronInVector == false) {
		return PATRON_NOT_ENROLLED;
	}

	return SUCCESS;
}

