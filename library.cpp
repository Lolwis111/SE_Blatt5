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
	size_t left = 0;
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

	return _books.end();
}

/**
 * registers a new user and returns the
 * id that new user will have
 * TODO: expand if time allows
 */
unsigned long library::registerUser()
{
    user newUser(_userCount + 1);
    _users.push_back(newUser);

    _userCount++;

    return newUser.getUserID();
}

void library::addBookToLibrary(book book)
{
	auto bookIterator = _books.begin();

	while (bookIterator->getISBN() < book.getISBN())
	{
		++bookIterator;
	}

	if (bookIterator->getISBN() == book.getISBN())
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
    /** TODO: keep a map of books and vector<user> where the vector
     *  describes the list of users who wish for the book
     *  the users have to be different from each other
     *  - if the book is already in the database and was retired before, we add the book
     *    after 2 users wished for this book
     *  - if the book is not in the database and has not beed retired before, add the book if 5 users
     *    wish for this book
	 *  - after a book is added remove the entry from wish list
     *  - if the book is already n the database ignore this request (maybe even return false)
     */

	if (searchByISBN(book.getISBN()) != _books.end() && false == book.isRetired())
	{
		// ignore requests for already existing books that are not retired
		return;
	}
	
	auto userIterator = std::find(_wishList[book].begin(), _wishList[book].end(), user);

	if (userIterator == _wishList[book].end())
	{
		_wishList[book].push_back(user);

		if (book.isRetired() == true && _wishList[book].size() == 2)
		{
			::book newCopyOfBook(book.getTitle(), book.getAuthor(), book.getISBN());

			auto oldBookIterator = searchByISBN(book.getISBN());
			_books.erase(oldBookIterator);

			addBookToLibrary(newCopyOfBook);
		}
		else if (_wishList[book].size() == 5)
		{
			addBookToLibrary(book);
		}
	}
}

std::vector<book> library::getAllBooks()
{
	return std::vector<book>(_books);
}

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
	auto wishListIterator = std::find(_wishList.begin(), _wishList.end(), book);

	if (wishListIterator == _wishList.end())
	{
		return 0;
	}
	else
	{
		return _wishList[book].size();
	}
}
