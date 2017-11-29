#include "user.h"

#include <algorithm>

/**
 * create a new user with a userID
 * the userID is assigned by the library
 * TODO: add name, contact info etc.
 */
user::user(unsigned int userID)
{
    _userID = userID;
    _borrowedBookCount = 0; // a freshly registered user has no books borrowed
}

unsigned int user::getUserID()
{
    return _userID;
}

bool user::borrowBook(unsigned long isbn)
{
    if(_borrowedBookCount == 10)
    {
        return false;
    }

    _borrowedBookCount++;
    
    _borrowedBooks.push_back(isbn);

    return true;
}

bool user::returnBook(unsigned long isbn)
{
    auto position = std::find(_borrowedBooks.begin(), _borrowedBooks.end(), isbn);
    
    if(position == _borrowedBooks.end())
    {
        return false;
    }

    _borrowedBooks.erase(position);

    _borrowedBookCount--;

    return true;
}

/**
 * returns a vector containing the isbn numbers
 * of the books this user has borrowed
 * !!: the returned vector is a copy of the internal
 * structure to avoid unwanted internal changes
 */
std::vector<unsigned long> user::getBorrowedBooks()
{
    // create a hard copy of the borrowed books
    // to avoid returning references to our internal data structure
    std::vector<unsigned long> copyOfBorrowedBooks(_borrowedBooks);

    return copyOfBorrowedBooks;
}
