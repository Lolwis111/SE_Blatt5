#pragma once

#include <string>

class user;

/**
 * book provides the representation of a book
 * each book has a title, an author and an isb number
 * the isb number is supposed to be unique
 */
class book
{
private:
    std::string _title;
    std::string _author;
    unsigned long _isbn;

    bool _isBorrowed;
    bool _isRetired;
    unsigned int _timesBorrowed;

    unsigned long _borrowedByUserID;

public:
    book(std::string title, std::string author, unsigned long isbn);

    bool borrow(unsigned long userID);
    bool bringBack();

    std::string getTitle() const { return _title; };
    std::string getAuthor() const { return _author; };
    unsigned long getISBN() const { return _isbn; };

    bool isRetired() const { return _isRetired; };
    bool isBorrowed() const { return _isBorrowed; };

    unsigned int getTimesBorrowed() const { return _timesBorrowed; };
    unsigned long getBorrowingUserID() const { return _borrowedByUserID;  };

    std::string toString();

    /**
     * the < operator is valid on a book
     * a book is smaller than a book if its isb number is smaller
     */
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

    /**
     * the == operator is valid on a book
     * a book is equal to another book if their isb numbers are equal
     */
    bool operator==(const book& other) const
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
