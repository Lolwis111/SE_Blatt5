#include <string>
#include "book.h"
#include "user.h"
#include "library.h"

#include <algorithm>
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
    
    // TODO: segmentation fault somewhere in here
    //       code review strongly advised
	/*size_t left = 0;
	size_t right = _books.size() - 1;

	while (left <= right)
	{
		size_t middle = left + ((right - left) / 2);

		if (_books[middle].getISBN() == isbn)
		{
			return _books.begin() + middle;
		}
		else if (_books[middle].getISBN() > isbn)
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
		}
	}

	return _books.end();*/
}

/**
 * registers a new user and returns the
 * id that new user will have
 * TODO: expand if time allows
 */
unsigned int library::registerUser()
{
    user newUser(_userCount + 1);
    
    _users.push_back(newUser);

    _userCount++;

    return newUser.getUserID();
}

user library::findUserById(unsigned int userID)
{
    for(auto userIterator = _users.begin(); userIterator < _users.end(); ++userIterator)
    {
        if(userIterator->getUserID() == userID)
        {
            return *userIterator;
        }
    }
    
    return user(0);
}

void library::addBookToLibrary(book book)
{
	auto bookIterator = _books.begin();

	while (bookIterator != _books.end() && bookIterator->getISBN() < book.getISBN())
	{
		++bookIterator;
	}

	if(bookIterator == _books.end())
	{ 
		_books.push_back(book);	
	}
	else if (bookIterator->getISBN() == book.getISBN())
	{
		// ignore requests for already existing books
		return;
	}
	else
	{
		_books.insert(bookIterator, book);
	}
}

void library::wishForABook(user user, book book)
{
	if (searchByISBN(book.getISBN()) != _books.end() && false == book.isRetired())
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
	auto userIterator = std::find(_wishList[book].begin(), _wishList[book].end(), user);

    // user not found
	if (userIterator == _wishList[book].end())
	{
        // inser the user
		_wishList[book].push_back(user);

        // a retired book only needs 2 wishes
		if (book.isRetired() == true && _wishList[book].size() == 2)
		{
            // create a new instance of the book that is retired (aka buy a new one)
			::book newCopyOfBook(book.getTitle(), book.getAuthor(), book.getISBN());

            // find the old book and delete it from the shelf
			auto oldBookIterator = searchByISBN(book.getISBN());
			_books.erase(oldBookIterator);

            // put the newly bought item in the shelf
			addBookToLibrary(newCopyOfBook);
            // and remove it from the wishlist
            removeBookFromWishList(book);
		}
		else if (_wishList[book].size() == 5) // a new book needs 5 wishes
		{
            // insert the book into the library
			addBookToLibrary(book);
            // and remove it from the wishlist
            removeBookFromWishList(book);
		}
	}
    
    // else: user is found: we ignore his request
}

void library::removeBookFromWishList(book book)
{
    auto bookIterator = _wishList.find(book);
    
    _wishList.erase(bookIterator);
}

std::vector<book> library::getAllBooks()
{
	return std::vector<book>(_books);
}

// TODO: is this even useful?
//       we already have the book, we can call timesBorrowed and getBorrowingUser
//       by ourselfs amirite???
user library::getUserWhoBorrowsBook(book book)
{
	return *book.getBorrowingUser();
}

unsigned int library::getTimesBorrowed(book book)
{
	return book.timesBorrowed();
}

unsigned int library::getTimesWishedFor(book book)
{
    // try to find the book in the wishlist
	auto wishListIterator = _wishList.find(book);

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
