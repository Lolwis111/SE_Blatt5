/**
 * @author Leonid Antipov
 * @author Alyona Buyukli
 * @author Karol Czopek
 * @author Levin Palm
 */

#include <string>
#include <iostream>

#include "book.h"
#include "constants.h"

book::book(std::string title, std::string author, unsigned long isbn)
{
    _borrowedByUserID = INVALID_USER_ID; // no one borrows a new book
    _author = author; // copy the three attributes
    _title = title;
    _isbn = isbn;

    _isRetired = false; // a new book is new and therefore not retiered
    _isBorrowed = false; // on  creation a book is not borrowed to anyone
    _timesBorrowed = 0; // a new book has never been borrowed before
}

bool book::borrow(unsigned long userID)
{
    // check if book is currently borrowed or retired
    if(_isBorrowed == true || _isRetired == true)
    {
        // if yes, we can't lend this book.
        return false;
    }
    
    _isBorrowed = true; // set status to borrowed

    _borrowedByUserID = userID; // save which user has this book

    _timesBorrowed++; // increase timesBorrowed
    
    return true; // success
}

bool book::bringBack()
{ 
    // check if the book is borrowed right now
    if (_isBorrowed == false)
    {
        // if not its an error
        return false;
    }

    // if the limit for borrowing is reached
    if (_timesBorrowed == MAX_TIMES_BORROWED)
    {
        // the book gets retired
        _isRetired = true;
    }

    // after bringing it back, it can be borrowed again
    _borrowedByUserID = INVALID_USER_ID;
    _isBorrowed = false;

    // success
    return true;
}

std::string book::toString()
{
    // build the string according to documentation
    return _author + ": " + _title + " (" + std::to_string(_isbn) + ")";
}
