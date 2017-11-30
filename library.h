#pragma once

#include <string>
#include "book.h"
#include "user.h"

#include <vector>
#include <map>

/**
 * library provides the main interface.
 * This contains all the books and users. It also allows the API-user
 * to create and manage users as well as books.
 */
class library
{
private:
    unsigned int _bookCount; /**< internal counter of books for faster access */
    unsigned int _userCount; /**< internal counter of users for faster access */

    std::vector<book> _books; /**< the internal structure holding all the books */ 
    std::vector<user> _users; /**< the internal structure holding all the users */

    std::map<book,std::vector<user> > _wishList; /**< internal map to represent which books are wished for by which users */

    std::vector<book>::iterator searchByISBN(unsigned long isbn);
    
    void removeBookFromWishList(book bookToRemove);

public:
    library();

    unsigned int getBookCount() const { return _bookCount; }
    unsigned int getUserCount() const { return _userCount; }

    unsigned int registerUser(std::string name, std::string address);
    user* findUserById(unsigned int userID);
    
    void wishForABook(user wishingUser, book bookWishedFor);
    void addBookToLibrary(book bookToAdd);

    bool borrowBook(book *bookToBorrow, user *borrowingUser);
    bool returnBook(book *bookToReturn, user *borrowingUser);

    std::vector<book> getAllBooks();
    std::vector<user> getAllUsers();

    user* getUserWhoBorrowsBook(book bookToCheck);

    unsigned int getTimesBorrowed(book bookToCheck);
    unsigned int getTimesWishedFor(book bookToCheck);
};
