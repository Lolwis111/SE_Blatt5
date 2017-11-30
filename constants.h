/** @file
 * @author Leonid Antipov
 * @author Alyona Buyukli
 * @author Karol Czopek
 * @author Levin Palm
 */
#pragma once

/**
 * This constant will return a invalid user id.
 * It can be used to indicate that a given id is currently invalid
 * and should not be accessed.
 */
const unsigned int INVALID_USER_ID = 0;

/**
 * This constant indicates how many times a book
 * can be borrowed before it retires.
 */
const unsigned int MAX_TIMES_BORROWED = 50;

/**
 * This constant indicates how many users have to wish for a book
 * that is completlly new to the library, in order to add this book
 * to the library.
 */
const unsigned int WISHES_NEEDED_NEW_BOOK = 5;

/**
 * This constant indicates how many users have to wish for a book
 * that was in this library before but is now retired.
 */
const unsigned int WISHES_NEEDED_RETIRED_BOOK = 5;

/**
 * This constant indicates how many books one user can borrow at a time.
 */
const unsigned int MAX_BORROWED_BOOKS = 10;
