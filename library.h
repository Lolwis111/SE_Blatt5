/**
 * @author Leonid Antipov
 * @author Alyona Buyukli
 * @author Karol Czopek
 * @author Levin Palm
 */
#pragma once

#include <string>
#include <vector>
#include <map>

#include "book.h"
#include "user.h"

/**
 * library provides the main interface.
 * This contains all the books and users. It also allows the API-user
 * to create and manage users as well as books.
 */
class library
{
private:
    /**
     * internal counter of books for faster access 
     */
    unsigned int _bookCount;
    
    /**
     * internal counter of users for faster access 
     */
    unsigned int _userCount;

    /**
     * the internal structure holding all the books 
     */ 
    std::vector<book> _books;
    
    /**
     * the internal structure holding all the users 
     */
    std::vector<user> _users;

    /**
     * internal map to represent which books are wished for by which users 
     */
    std::map<book,std::vector<user> > _wishList;

    /**
     * Internal method to find a book by its ISBN.
     * If the given isbn can not be found in the list of books
     * _books.end() is returned.
     * 
     * @param isbn The ISBN to search
     * 
     * @return An iterator of this book in the internal book structure.
     *         _books.end() indicates that the search was not successful. 
     */
    std::vector<book>::iterator searchByISBN(unsigned long isbn);
    
    /**
     * Internal method to remove a book from the wish list. This is called
     * after 5 (or 2 if retired) users wished for a book.
     * This method does not check if the given book is actually in the wishList.
     * 
     * @param bookToRemove the book that should be removed from the library
     */
    void removeBookFromWishList(book bookToRemove);

public:
    /**
     * creates a new library with 0
     * registered users and 0 books
     */
    library();

    /**
     * @return Returns an unsigned integer indicating how many books there 
     *          are in the library. This includes retired books.
     */
    unsigned int getBookCount() const { return _bookCount; }
    
    /**
     * @return Returns an unsigned integer indicating how man users are 
     *          registered in this library.
     */
    unsigned int getUserCount() const { return _userCount; }

    /**
     * This method registers a new user in this library.
     * 
     * @param name The name the new user has.
     * @param address The address the new user has.
     * 
     * @return The unique ID the new user will have.
     */
    unsigned int registerUser(std::string name, std::string address);
    
    /**
     * Search for a user by the user id in the system.
     * 
     * @param userID The user id that should be searched for.
     * 
     * @return A pointer to the user with the given id, or nullptr 
     *         if no user with this id exists.
     */
    user* findUserById(unsigned int userID);
    
    /**
     * This method adds a given book to the library.
     * Books that are already in the library will be ignored.
     * If the same book is currently in the wish list, it will
     * be removed from there.
     * 
     * @param bookToAdd The book that should be added to the library.
     */
    void addBookToLibrary(book bookToAdd);
    
    /**
     * This methods allows a user to wish for a certain book.
     * When enough users wish for a book it gets added to the library.
     * 
     * @param wishingUser The user that wishes for the book.
     * @param bookWishedFor The book that the user wishes for.
     */
    void wishForABook(user wishingUser, book bookWishedFor);

    /**
     * This method allows a user to borrow book a from the library.
     * The method checks if the user is registerd and if the book is
     * available in this library.
     * 
     * @param bookToBorrow A pointer to the book that should be borrowed.
     * @param borrowingUser A pointer to the user that wants to borrow the book.
     * 
     * @return Returns true on success. Returns false if the book is not 
     *          available or retired.
     */
    bool borrowBook(book *bookToBorrow, user *borrowingUser);
    
    /**
     * This method allows a user to give a borrowed book back to the library.
     * The method checks if the user is registerd and if the book
     * belongs to this library.
     * 
     * @param bookToReturn A pointer to the book that the user wants to give back.
     * @param borrowingUser A pointer to the user that currently borrows this book.
     * 
     * @return Returns true on success. Returns false if book does not 
     *          belong to this library or the book is not being borrowed 
     *          or the user is not registered.
     */
    bool returnBook(book *bookToReturn, user *borrowingUser);

    /**
     * Return all users.
     * 
     * @return A hard copy of the list of users that are currently registered in the library.
     */
    std::vector<book> getAllBooks();
    
    /**
     * Return all books.
     * 
     * @return A hard copy of the list of books that are currently available in the library.
     */
    std::vector<user> getAllUsers();

    /**
     * Given a book this will return which the user who currently 
     * borrows this book.
     * 
     * @param borrowedBook The book to check this on.
     * @return A pointer to the user that currently borrows this book.
     */
    user* getUserWhoBorrowsBook(book bookToCheck);

    /**
     * Check how many times a book has been borrowed.
     * 
     * @param bookToCheck The book to check this on.
     * @return The number of times the book has been borrowed.
     */
    unsigned int getTimesBorrowed(book bookToCheck);
    
    /**
     * Check how many times users wished for a given book.
     * 
     * @param bookToCheck The book to check this on.
     * @return the number of times individual users wished for this book.
     */
    unsigned int getTimesWishedFor(book bookToCheck);
};
