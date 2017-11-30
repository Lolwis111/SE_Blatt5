/**
 * @author Leonid Antipov
 * @author Alyona Buyukli
 * @author Karol Czopek
 * @author Levin Palm
 */

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#include "book.h"
#include "user.h"
#include "library.h"
#include "constants.h"

library::library()
{
    // at the beginning there are no books and no users
    _userCount = 0;
    _bookCount = 0;
}

std::vector<book>::iterator library::searchByISBN(unsigned long isbn)
{
    // do a simple linear search, check each element
    std::vector<book>::iterator bookIt;
    for(bookIt = _books.begin(); bookIt < _books.end(); ++bookIt)
    {
        if(bookIt->getISBN() == isbn)
        {
            // and return if anything is found
            return bookIt;
        }
    }
    
    // else indicate that nothing is found by returning end()
    return _books.end();
}

unsigned int library::registerUser(std::string name, std::string address)
{
    // create a new user, starting with ID 1
    // and name + address
    user newUser(_userCount + 1, name, address);
    
    // add user to the userlist
    _users.push_back(newUser);

    // increment usercount
    _userCount++;

    // return the id this new user will have
    return newUser.getUserID();
}

user* library::findUserById(unsigned int userID)
{
    // do a linear search on all users
    for(size_t index = 0; index < _userCount; index++)
    {
        // if the id matches
        if(_users[index].getUserID() == userID)
        {
            // return a pointer
            return &_users[index];
        }
    }
    
    // if nothing is found, return nullptr
    return nullptr;
}

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

void library::addBookToLibrary(book bookToAdd)
{
    // check if the book already exists in this library
    auto bookIterator = std::find(_books.begin(), _books.end(), bookToAdd);

    if(bookIterator == _books.end())
    {
        // if no, add it to the list of books
        _books.push_back(bookToAdd);
        
        // and increment the book count
        _bookCount++;
        
        // check if the book is in the wishList
        if(_wishList.find(bookToAdd) != _wishList.end())
        {
            removeBookFromWishList(bookToAdd);
        }
    }
}


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
        if (bookWishedFor.isRetired() == true && _wishList[bookWishedFor].size() == WISHES_NEEDED_RETIRED_BOOK)
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
        else if (_wishList[bookWishedFor].size() == WISHES_NEEDED_NEW_BOOK) // a new book needs 5 wishes
        {
            // insert the book into the library
            addBookToLibrary(bookWishedFor);
            // and remove it from the wishlist
            removeBookFromWishList(bookWishedFor);
        }
    }
    
    // else: user is found: we ignore his request
}

void library::removeBookFromWishList(book bookToRemove)
{
    // find the book
    auto bookIterator = _wishList.find(bookToRemove);
    
    // and delete it
    _wishList.erase(bookIterator);
}

std::vector<user> library::getAllUsers()
{
    // create a hard copy and return that
    return std::vector<user>(_users);
}

std::vector<book> library::getAllBooks()
{
    // create a new list
    std::vector<book> nonRetiredBooks;
    
    for(size_t i = 0; i < _books.size(); i++)
    {
        // find all the books that are not retired
        if(_books[i].isRetired() == true)
        {
            // and add them to the new list
            nonRetiredBooks.push_back(_books[i]);
        }
    }
    
    // return the new list
    return nonRetiredBooks;
}

user* library::getUserWhoBorrowsBook(book borrowedBook)
{
    // get the userID from the book
    unsigned long userID = borrowedBook.getBorrowingUserID();
    
    // return the user belonging to this ID
    return findUserById(userID);
}

unsigned int library::getTimesBorrowed(book bookToCheck)
{
    // return how many times it has been borrowed
    return bookToCheck.getTimesBorrowed();
}

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
