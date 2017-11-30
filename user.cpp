#include "user.h"

#include <algorithm>
#include <iostream>

/**
 * create a new user with a userID
 * @param userID the unique id (for uniqueness this should be assigned by registerUser()
 * @param name the real name of this user
 * @param address the address information of this user
 */
user::user(unsigned int userID, std::string name, std::string address)
{
    _userID = userID;
    _name = name;
    _address = address;
    
    // a freshly registered user has no books borrowed
    _borrowedBookCount = 0;
}

/**
 * This method allows this user to borrow a book
 * 
 * @param bookToBorrow A pointer to the book this user wants to borrow
 * @return true on success, false if this user cant borrow this book
 */
bool user::borrowBook(book *bookToBorrow)
{
    if(_borrowedBookCount == 10)
    {
        return false;
    }
    
    if(bookToBorrow->borrow(_userID) == false) 
    {
        return false;
    }

    _borrowedBookCount++;
    
    _borrowedBooks.push_back(*bookToBorrow);

    return true;
}

/**
 * this method allows the user to return a book to the library
 * it is verified that he borrowed that book and that this book
 * belongs to this library
 * 
 * @param bookToReturn the book that should be returned
 * @return true on success, false if this book can not be returned because it does not belong here or is not borrowed
 */
bool user::returnBook(book *bookToReturn)
{
    std::vector<book>::iterator iterator = std::find(
                _borrowedBooks.begin(), 
                _borrowedBooks.end(), 
                *bookToReturn);

    if(iterator == _borrowedBooks.end())
    {
        return false;
    }

    if(bookToReturn->bringBack() == false)
    {
        return false;
    }

    _borrowedBooks.erase(iterator);

    _borrowedBookCount--;

    return true;
}

/**
 * @return a list containing all the books that this user borrows
 */
std::vector<book> user::getBorrowedBooks()
{
    return std::vector<book>(_borrowedBooks);
}
