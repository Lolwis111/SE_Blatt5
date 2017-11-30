#pragma once

#include <string>
#include <vector>
#include "book.h"

/**
 * this class provides all the information that is needed to 
 * manage a user
 * each user has a name, address information and a systemwide unique id
 * the user class also manages the books the user currently borrows
 */
class user
{
private:
    unsigned int _userID;

    std::string _name;
    std::string _address;

    int _borrowedBookCount;
    std::vector<book> _borrowedBooks;
    
public:
    
    user(unsigned int userID, std::string name, std::string address);

    unsigned int getUserID() const { return _userID; }
    std::string getName() const { return _name; }
    std::string getAddress() const { return _address; }
    
    bool borrowBook(book *bookToBorrow);
    bool returnBook(book *bookToReturn);

    std::vector<book> getBorrowedBooks();

    /**
     * the == operator is valid on users
     * a user is valid to another user if their ids are identical
     */
    bool operator==(const user& other) const
    {
        if (other.getUserID() == _userID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
