#include <string>
#include "book.h"
#include "user.h"
#include "library.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

/**
 * creates a new library with 0
 * registered users and 0 books
 */
library::library()
{
    _userCount = 0;
    _bookCount = 0;
}

/**
 * internal method to find a book by its isb number
 * @param isbn the number to look for
 * @return an iterator of this book in the internal book structure
 */
std::vector<book>::iterator library::searchByISBN(unsigned long isbn)
{
    std::vector<book>::iterator bookIt;
    for(bookIt = _books.begin(); bookIt < _books.end(); ++bookIt)
    {
        if(bookIt->getISBN() == isbn)
        {
            return bookIt;
        }
    }
    
    return _books.end();
}

/**
 * This method registers a new user in this library
 * 
 * @param name The name the new user has
 * @param address The address the new user has
 * @return the ID the new user will have
 */
unsigned int library::registerUser(std::string name, std::string address)
{
    user newUser(_userCount + 1, name, address);
    
    _users.push_back(newUser);

    _userCount++;

    return newUser.getUserID();
}

/**
 * Search by the user id for a user in the system
 * 
 * @param userID The user id that should be searched
 * @return A pointer to the user with the given id, or nullptr if no user with this id exists
 */
user* library::findUserById(unsigned int userID)
{
    for(size_t index = 0; index < _userCount; index++)
    {
        if(_users[index].getUserID() == userID)
        {
            return &_users[index];
        }
    }
    
    return nullptr;
}

/**
 * This method allows a user to borrow book a from the library
 * The method checks if the user is registerd and if the book is
 * available in this library.
 * 
 * @param bookToBorrow A pointer to the book that should be borrowed
 * @param borrowingUser A pointer to the user that wants to borrow the book
 * @return true if successful, false if book not available or user not registered
 */
bool library::borrowBook(book *bookToBorrow, user *borrowingUser)
{
    // check if the user is registered
    if(findUserById(borrowingUser->getUserID()) == nullptr)
    {
        return false;
    }
    
    // check if the book we want to borrow is available in the library
    if(searchByISBN(bookToBorrow->getISBN()) == _books.end())
    {
        return false;
    }
    
    return borrowingUser->borrowBook(bookToBorrow);
}

/**
 * This method allows a user to give a borrowed book back to the library
 * The method checks if the user is registerd and if the book
 * belongs to this library.
 * 
 * @param bookToReturn A pointer to the book that the user wants to hand in
 * @param borrowingUser A pointer to user that currently borrows this book
 * @return true if successful, false if book does not belong to this
 *         library, or book is not being borrowed or user not registered
 */
bool library::returnBook(book *bookToReturn, user *borrowingUser)
{
    // check if the user is registered
    if(findUserById(borrowingUser->getUserID()) == nullptr)
    {
        return false;
    }
    
    // check if the book we want to hand in actually belongs to this library
    if(searchByISBN(bookToReturn->getISBN()) == _books.end())
    {
        return false;
    }
    
    return borrowingUser->returnBook(bookToReturn);
}

/**
 * This method adds a given book to the library.
 * Books that are already in the library will be ignored
 * 
 * @param bookToAdd the book that should be added to the library
 */
void library::addBookToLibrary(book bookToAdd)
{
    auto bookIterator = std::find(_books.begin(), _books.end(), bookToAdd);

    if(bookIterator == _books.end())
    {
        _books.push_back(bookToAdd);
        _bookCount++;
    }
}

/**
 * This methods allows a user to wish for a certain book to be added to the library
 * 
 * @param wishingUser The user that wishes for the book
 * @param bookWishedFor The book that the user wishes for
 */
void library::wishForABook(user wishingUser, book bookWishedFor)
{
    if (searchByISBN(bookWishedFor.getISBN()) != _books.end() 
                && false == bookWishedFor.isRetired())
    {
        // ignore requests for already existing books that are not retired
        return;
    }
    
    // check if the given user already wished for the given book
    //
    // we dont check if the book exists in the map, because
    // the [] operator of the map will insert the element if it is not found
    // -> a freshly inserted element has a new vector<user> -> therefor will
    // the user not be found 
    auto userIterator = std::find(
                _wishList[bookWishedFor].begin(), 
                _wishList[bookWishedFor].end(), 
                wishingUser);

    // user not found
    if (userIterator == _wishList[bookWishedFor].end())
    {
        // inser the user
        _wishList[bookWishedFor].push_back(wishingUser);

        // a retired book only needs 2 wishes
        if (bookWishedFor.isRetired() == true && _wishList[bookWishedFor].size() == 2)
        {
            // create a new instance of the book that is retired (aka buy a new one)
            book newCopyOfBook(
                        bookWishedFor.getTitle(), 
                        bookWishedFor.getAuthor(), 
                        bookWishedFor.getISBN());

            // find the old book and delete it from the shelf
            auto oldBookIterator = searchByISBN(bookWishedFor.getISBN());
            _books.erase(oldBookIterator);

            // put the newly bought item in the shelf
            addBookToLibrary(newCopyOfBook);
            // and remove it from the wishlist
            removeBookFromWishList(bookWishedFor);
        }
        else if (_wishList[bookWishedFor].size() == 5) // a new book needs 5 wishes
        {
            // insert the book into the library
            addBookToLibrary(bookWishedFor);
            // and remove it from the wishlist
            removeBookFromWishList(bookWishedFor);
        }
    }
    
    // else: user is found: we ignore his request
}

/**
 * internal method to remove a book from the wish list after it has
 * been added to the library. It is not checked if the book
 * is actually in the wishList
 * 
 * @param bookToRemove the book that should be removed from the library
 */
void library::removeBookFromWishList(book bookToRemove)
{
    auto bookIterator = _wishList.find(bookToRemove);
    
    _wishList.erase(bookIterator);
}

/**
 * Return all users
 * 
 * @return a hard copy of the list of users that are currently registered in the library
 */
std::vector<user> library::getAllUsers()
{
    return std::vector<user>(_users);
}

/**
 * Return all books
 * 
 * @return a hard copy of the list of books that are currently available in the library
 */
std::vector<book> library::getAllBooks()
{
    std::vector<book> nonRetiredBooks;
    
    for(int i = 0; i < _books.size(); i++)
    {
        if(_books[i].isRetired() == true)
        {
            nonRetiredBooks.push_back(_books[i]);
        }
    }
    
    return nonRetiredBooks;
}

/**
 * Given a book this will return which user currently borrows this book
 * 
 * @param borrowedBook the book to check this on
 * @return a pointer to the user that currently borrows this book
 */
user* library::getUserWhoBorrowsBook(book borrowedBook)
{
    unsigned long userID = borrowedBook.getBorrowingUserID();
    
    return findUserById(userID);
}

/**
 * check how many times a book has been borrowed
 * 
 * @param bookToCheck the book to check this on
 * @return the number of times the book has been borrowed
 */
unsigned int library::getTimesBorrowed(book bookToCheck)
{
    return bookToCheck.getTimesBorrowed();
}

/**
 * check how many times users wished for a given book
 * 
 * @param bookToCheck The book to check this on
 * @return the number of times individual users wished for this book
 */
unsigned int library::getTimesWishedFor(book bookToCheck)
{
    // try to find the book in the wishlist
    auto wishListIterator = _wishList.find(bookToCheck);

    // if it is not found noone wants this books, therefor we return 0
    if (wishListIterator == _wishList.end())
    {
        return 0;
    }
    else
    {
        // else: return the number of people wishing for this book
        return wishListIterator->second.size();
    }
}
