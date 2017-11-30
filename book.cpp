#include "book.h"
#include <string>
#include <iostream>

/**
 * Create a new book object
 * 
 * @param title The title of the book
 * @param author The author of the book
 * @param isbn The unique isb number of the book
 */
book::book(std::string title, std::string author, unsigned long isbn)
{
    _borrowedByUserID = 0;
    _author = author;
    _title = title;
    _isbn = isbn;

    _isRetired = false; // a new book is new and therefore not retiered
    _isBorrowed = false; // on  creation a book is not borrowed to anyone
    _timesBorrowed = 0; // a new book has never been borrowed before
    _borrowedByUserID = 0;
}

/**
 * borrow this book
 * this will set the internal variables to indicate that this book is borrowed
 * this will also update the times this is borrowed and retieres the book if needed
 * 
 * @param userID the ID of the user who wants to borrow this book
 * @return true if the borrowing was successful, false if the book is already borrowed or retired
 */
bool book::borrow(unsigned long userID)
{
    if(_isBorrowed == true || _isRetired == true)
    {
        return false;
    }
    
    _isBorrowed = true;

    _borrowedByUserID = userID;

    _timesBorrowed++;
    
    return true;
}

/**
 * bring this book back
 * this will set the internal status to not borrowed
 * will also manage the retirement process
 * 
 * @return true on success, false if the book is currently not borrowed
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

    _borrowedByUserID = 0;
    _isBorrowed = false;

    return true;
}

/**
 * Creates a string representation of this book
 * 
 * @return String in form [author]: [title] ([isbn])
 */
std::string book::toString()
{
    return _author + ": " + _title + " (" + std::to_string(_isbn) + ")";
}
