#include <string>
#include "book.h"
#include "user.h"
#include "library.h"
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
 * registers a new user and returns the
 * id that new user will have
 */
unsigned long library::registerUser()
{
    user newUser(_userCount + 1);
    _users.push_back(newUser);

    _userCount++;

    return newUser.getUserID();
}

void library::wishForABook(user u, book b)
{
    /** TODO: keep a map of books and vector<user> where the vector
     *  describes the list of users who which for the book
     *  the users have to be different from each other
     *  - if the book is already in the database and was retired before, we add the book
     *    after 2 users wished for this book
     *  - if the book is not in the database and has not beed retired before, add the book if 5 users
     *    wish for this book
     *  - if the book is already n the database ignore this request (maybe even return false)
     */

    // std::map<book,std::vector< user> >::iterator position = _wishList.find(b);
    //if(position == _wishList.end())
    //{
        //std::vector<user> users;
        // users.push_back();
        // _wishList.insert(std::pair<book, std::vector<user>>(u, users));
    //}
}
