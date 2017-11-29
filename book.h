#pragma once
#include <string>

class book
{
private:
    std::string _title;
    std::string _author;
    unsigned long _isbn;

    bool _isBorrowed;
    bool _isRetired;
    int _timesBorrowed;

public:
    book(std::string title, std::string author, unsigned long isbn);//
    //~book();

    bool borrow();//

    std::string getTitle();//
    std::string getAuthor();//
    unsigned long getISBN();//

    std::string toString();//
};
