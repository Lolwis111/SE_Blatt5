#include "library.h"

#include <string>
#include <iostream>
#include <vector>

std::string boolToString(bool b)
{
    return (b ? "true" : "false");
}

/**
 * the main function is only used to test this API
 * it does not provide any real world applications
 */
int main()
{
    library lib1;

    unsigned long userID = lib1.registerUser("Hans Mueller", "An der Adresse 1234");

    user *user1 = lib1.findUserById(userID);

    book book1("My Title", "My Author", 1234);

    lib1.addBookToLibrary(book1);
    
    std::cout << "isRetired(): " << boolToString(book1.isRetired()) << std::endl;
    
    for(int i = 0; i <= 50; i++)
    {
        lib1.borrowBook(&book1, user1);
        lib1.returnBook(&book1, user1);
    }
    
    std::cout << "isRetired(): " << boolToString(book1.isRetired()) << std::endl;
    
    return 0;
}
