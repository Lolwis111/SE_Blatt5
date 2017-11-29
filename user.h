#pragma once
#include <string>
#include <vector>
#include "book.h"

class user
{
private:
    unsigned int _userID;

    int _borrowedBookCount;
    std::vector<book*> _borrowedBooks;

public:
    user(unsigned int userID);

	unsigned int getUserID() const { return _userID; }

    bool borrowBook(book *book);
    bool returnBook(book *book);

    std::vector<book*> getBorrowedBooks();
};
