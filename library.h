#pragma once

#include <string>
#include "book.h"
#include "user.h"

#include <vector>
#include <map>

class library
{
private:
    unsigned int _bookCount;
    unsigned int _userCount;

    std::vector<book> _books;
    std::vector<user> _users;

    std::map<book,std::vector<user> > _wishList;

	std::vector<book>::iterator searchByISBN(unsigned long isbn);

public:
    library();

    unsigned long registerUser();
    void wishForABook(user user, book book);
	void addBookToLibrary(book book);

	std::vector<book> getAllBooks(); // welche Buecher der Bestand aktuell umfasst
	user getUserWhoBorrowsBook(book book); // welcher Nutzer ein bestimmtes Buch aktuell ausgeliehen hat
	unsigned int getTimesBorrowed(book book); // wie oft ein bestimmtes Buch bisher ausgliehen wurde
	unsigned int getTimesWishedFor(book book); // wie oft ein bestimmter Beschaffungswunsch bisher geaeussert wurde
};
