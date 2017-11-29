#include "book.h"
#include <string>

/**
 * create a new book with title, author and isbn number
 * warning: the isb numbers sigature wont get verified
 */
book::book(std::string title, std::string author, unsigned long isbn)
{
    _author = author;
    _title = title;
    _isbn = isbn;
    
    _isRetired = false; // a new book is new and therefore not retiered
    _isBorrowed = false; // on  creation a book is not borrowed to anyone
    _timesBorrowed = 0; // a new book has never been borrowed before
}

/**
 * borrow this book
 * this will set the internal variables to indicate that this book is borrowed
 * this will also update the times this is borrowed and retieres the book if needed
 */
bool book::borrow()
{
    if(_timesBorrowed == 50)
    {
        _isRetired = true;

        return false;
    }

    if(_isBorrowed == true || _isRetired == true)
    {
        return false;
    }

    _isBorrowed = true;

    _timesBorrowed++;
    
    return true;
}

std::string book::toString()
{
    return _author + ": " + _title + " (" + std::to_string(_isbn) + ")";
}

/** begin of public property section */
std::string book::getTitle()
{
    return _title;
}

std::string book::getAuthor()
{
    return _author;
}

unsigned long book::getISBN()
{
    return _isbn;
}
/** end of public property section */
