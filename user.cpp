#include "user.h"

#include <algorithm>

/**
 * create a new user with a userID
 * the userID is assigned by the library
 */
user::user(unsigned int userID, std::string name, std::string address)
{
    _userID = userID;
    _name = name;
    _address = address;
    _borrowedBookCount = 0; // a freshly registered user has no books borrowed
}

bool operator==(const user& u1, const user& u2)
{
	if (u1.getUserID() == u2.getUserID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool user::borrowBook(book *b)
{
    if(_borrowedBookCount == 10)
    {
        return false;
    }

    _borrowedBookCount++;
    
    _borrowedBooks.push_back(b);

    return true;
}

bool user::returnBook(book *b)
{
	std::vector<book*>::iterator iterator = std::find(_borrowedBooks.begin(), _borrowedBooks.end(), b);

    if(iterator == _borrowedBooks.end())
    {
        return false;
    }

	b->bringBack();

    _borrowedBooks.erase(iterator);

    _borrowedBookCount--;

    return true;
}

/**
 * returns a vector containing the isbn numbers
 * of the books this user has borrowed
 * !!: the returned vector is a copy of the internal
 * structure to avoid unwanted internal changes
 */
std::vector<book*> user::getBorrowedBooks()
{
    // create a hard copy of the borrowed books
    // to avoid returning references to our internal data structure
    std::vector<book*> copyOfBorrowedBooks(_borrowedBooks);

    return copyOfBorrowedBooks;
}