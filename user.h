#pragma once

#include <string>
#include <vector>
#include "book.h"

class user
{
private:
    unsigned int _userID;

    std::string _name;
    std::string _address;

    int _borrowedBookCount;
    std::vector<book*> _borrowedBooks;
    
public:
    
    user(unsigned int userID, std::string name, std::string address);

	unsigned int getUserID() const { return _userID; }
    std::string getName() const { return _name; }
    std::string getAddress() const { return _address; }
    
    bool borrowBook(book *book);
    bool returnBook(book *book);

    std::vector<book*> getBorrowedBooks();

	bool operator==(const user& other)
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
