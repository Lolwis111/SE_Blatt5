#include "book.h"
#include <string>

/**
 * create a new book with title, author and isbn number
 * warning: the isb numbers sigature wont get verified
 */
book::book(std::string title, std::string author, unsigned long isbn)
{
	_borrowedBy = nullptr;
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
bool book::borrow(user *user)
{
    if(_isBorrowed == true || _isRetired == true)
    {
        return false;
    }

    _isBorrowed = true;

	_borrowedBy = user;

    _timesBorrowed++;
    
    return true;
}

/**
 * bring this book back
 * this will set the internal status to not borrowed
 * returns false if the book is currently not borrowed
 */
bool book::bringBack()
{ 
	if (_isBorrowed == false)
	{
		return false;
	}

	if (_timesBorrowed == 50)
	{
		_isRetired = true;
	}

	_isBorrowed = false;

	return true;
}

std::string book::toString()
{
    return _author + ": " + _title + " (" + std::to_string(_isbn) + ")";
}