#pragma once

#include <string>

class user;

class book
{
private:
    std::string _title;
    std::string _author;
    unsigned long _isbn;

    bool _isBorrowed;
    bool _isRetired;
    unsigned int _timesBorrowed;

	user *_borrowedBy;

public:
    book(std::string title, std::string author, unsigned long isbn);

    bool borrow(user *user);
	bool bringBack();

	std::string getTitle() const { return _title; };
    std::string getAuthor() const { return _author; };

    unsigned long getISBN() const { return _isbn; };

	bool isRetired() const { return _isRetired; };
	bool isBorrowed() const { return _isBorrowed; };

	unsigned int timesBorrowed() const { return _timesBorrowed; };
	user *getBorrowingUser() const { return _borrowedBy;  };

    std::string toString();

	bool operator<(const book& other) const 
	{ 
		if (other.getISBN() < _isbn)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool operator==(const book& other)
	{
		if (other.getISBN() == _isbn)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
