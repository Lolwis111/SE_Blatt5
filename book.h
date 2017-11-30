/**
 * @author Leonid Antipov
 * @author Alyona Buyukli
 * @author Karol Czopek
 * @author Levin Palm
 */
#pragma once

#include <string>

class user;

/**
 * book provides the representation of a book.
 * Each book has a title, an author and an ISBN.
 * The ISBN is unique.
 */
class book
{
private:
    /**
     * The title of the book.
     */
    std::string _title;
    
    /**
     * The author of the book.
     */
    std::string _author;
    
    /**
     * The ISBN of the book.
     */
    unsigned long _isbn;

    /**
     * Indicates if this book is currently borrowed to someone
     */
    bool _isBorrowed;
    
    /**
     * Indicates if this book is retired
     */
    bool _isRetired;
    
    /**
     * Counts how many times this book has been borrowed before.
     */
    unsigned int _timesBorrowed;

    /**
     * The ID that currently borrows this book.
     * Is INVALID_USER_ID if isBorrowed is false.
     */
    unsigned long _borrowedByUserID;

public:
    /**
     * Create a new book object.
     * 
     * @param title The title of the book.
     * @param author The author of the book.
     * @param isbn The unique ISBN of the book.
     */
    book(std::string title, std::string author, unsigned long isbn);

    /**
     * Let user with given ID borrow this book.
     * This method will automatically increase timesBorrowed.
     * This method verifies that the book is currently available.
     * After successfully executing this, isBorrowed() will return true.
     * 
     * @param userID The ID of the user who wants to borrow this book.
     * 
     * @return true on success, false if the book is already borrowed or retired
     */
    bool borrow(unsigned long userID);
    
    /**
     * This methods hands the book back to the library after being borrowed.
     * This will check if the is borrowed, if no its an error.
     * After executing this, isBorrowed() will return false.
     * 
     * @return Returns true on success. Returns false if an error occours.
     */
    bool bringBack();

    /**
     * @return Returns the title of this book.
     */
    std::string getTitle() const { return _title; };
    
    /**
     * @return Returns the author of this book.
     */
    std::string getAuthor() const { return _author; };
    
    /**
     * @return Returns the ISBN of this book.
     */
    unsigned long getISBN() const { return _isbn; };

    /**
     * Creates a string representation of this book.
     * 
     * @return String in form [author]: [title] ([isbn])
     */
    std::string toString();

    /**
     * @return Returns a boolean indicating wether or not this book is retired.
     */
    bool isRetired() const { return _isRetired; };
    
    /**
     * @return Returns a boolean indicating wether or not this book is 
     *          borrowed right now.
     */
    bool isBorrowed() const { return _isBorrowed; };

    /**
     * @return Returns an unsigned integer indicating how many times this
     *          books has been borrowed before. 
     */
    unsigned int getTimesBorrowed() const { return _timesBorrowed; };
    
    /**
     * @return Returns the ID of the user who currently borrows this book.
     *          INVALID_USER_ID is returned, if the book is currently not borrowed.
     */
    unsigned long getBorrowingUserID() const { return _borrowedByUserID;  };

    /**
     * The '<' operator is valid on a book.
     * A book b1 is smaller than a book b2, if b1's ISBN is smaller
     * than b2's ISBN.
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
     * The == operator is valid on a book
     * A book b1 is equal to another book b2, if their ISBNs are equal.
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
