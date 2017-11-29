/* Autoren:   */

#pragma once

#include <string>
#include "book.h"
#include "user.h"

#include <vector>
#include <map>

class library
{
private:
    unsigned int _bookCount;
    unsigned int _userCount;

    std::vector<book> _books;
    std::vector<user> _users;

    std::map<book,std::vector<user> > _wishList;

public:
    library();

    unsigned long registerUser();
    void wishForABook(user u, book b);
};
