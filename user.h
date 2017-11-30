/**
 * @author Leonid Antipov
 * @author Alyona Buyukli
 * @author Karol Czopek
 * @author Levin Palm
 */
#pragma once

#include <string>
#include <vector>

#include "book.h"

/**
 * This class provides all the information that is needed to 
 * manage a user.
 * Each user is identifed by a name, address information and a 
 * systemwide unique id. To keep the id unique one should use
 * library::registerUser() to generate a user.
 * The user class also holds a list of books this user
 * is currently borrowing.
 */
class user
{
private:
    /**
     * The user id of this user.
     */
    unsigned int _userID;

    /**
     * The full name of this user.
     */
    std::string _name;
    
    /**
     * The address information of this user.
     */
    std::string _address;

    /**
     * Unsigned integer counting how many books this user currently has.
     */
    unsigned int _borrowedBookCount;
    
    /**
     * The list of books this user borrows.
     */
    std::vector<book> _borrowedBooks;
    
public:
    /**
     * Create a new user with a userID.
     * 
     * @param userID The unique id. (for uniqueness this should be assigned 
     *         by library::registerUser())
     * @param name The full name of this user.
     * @param address The address information of this user.
     */
    user(unsigned int userID, std::string name, std::string address);

    /**
     * @return Returns the user id of this user.
     */
    unsigned int getUserID() const { return _userID; }
    
    /**
     * @return Returns the full name of this user.
     */
    std::string getName() const { return _name; }
    
    /**
     * @return Returns the address information of this user.
     */
    std::string getAddress() const { return _address; }
    
    /**
     * This method allows this user to borrow a book.
     * 
     * @param bookToBorrow A pointer to the book this user wants to borrow.
     * @return Returns true on success. Returns if this user has too many 
     *          books or this book is not available.
     */
    bool borrowBook(book *bookToBorrow);
    
    /**
     * This method allows the user to return a book to the library.
     * The method verifies that the book is actually borrowed 
     * and that this book belongs to this library.
     * 
     * @param bookToReturn The book that should be returned.
     * @return Returns true on success. Returns false if this book can not be 
     *          returned because it does not belong here or is not borrowed.
     */
    bool returnBook(book *bookToReturn);

    /**
     * Return all books.
     * 
     * @return A list containing all the books that this user borrows.
     */
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
