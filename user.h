#pragma once
#include <string>
#include <vector>
#include "book.h"

class user
{
private:
    unsigned int _userID;

    int _borrowedBookCount;
    std::vector<unsigned long> _borrowedBooks;

public:
    user(unsigned int userID);

    unsigned int getUserID();

    bool borrowBook(unsigned long isbn);
    bool returnBook(unsigned long isbn);

    std::vector<unsigned long> getBorrowedBooks();
};
