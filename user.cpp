/**
 * @author Leonid Antipov
 * @author Alyona Buyukli
 * @author Karol Czopek
 * @author Levin Palm
 */

#include <algorithm>
#include <iostream>

#include "user.h"
#include "constants.h"

user::user(unsigned int userID, std::string name, std::string address)
{
    // copy the attributes
    _userID = userID;
    _name = name;
    _address = address;
    
    // a freshly registered user has no books borrowed
    _borrowedBookCount = 0;
}

bool user::borrowBook(book *bookToBorrow)
{
    // check if the borrowing limit is reached
    if(_borrowedBookCount == MAX_BORROWED_BOOKS)
    {
        // if yes: no more books for this user
        return false;
    }
    
    if(bookToBorrow->borrow(_userID) == false) 
    {
        // if the book cant be borrowed return false
        return false;
    }

    // increment the book counter
    _borrowedBookCount++;
    
    // and add the book to this user
    _borrowedBooks.push_back(*bookToBorrow);

    // success
    return true;
}

bool user::returnBook(book *bookToReturn)
{
    // search for the book
    std::vector<book>::iterator iterator = std::find(
                _borrowedBooks.begin(), 
                _borrowedBooks.end(), 
                *bookToReturn);

    if(iterator == _borrowedBooks.end())
    {
        // if this user does not have this book, return false
        return false;
    }

    if(bookToReturn->bringBack() == false)
    {
        // if this book cant be returned because its 
        // not borrowed return also false
        return false;
    }

    // remove the book from this user
    _borrowedBooks.erase(iterator);

    // and decrement book counter
    _borrowedBookCount--;

    // success
    return true;
}

std::vector<book> user::getBorrowedBooks()
{
    // create a hard copy of the books
    return std::vector<book>(_borrowedBooks);
}
