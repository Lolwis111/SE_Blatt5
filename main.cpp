#include "library.h"

#include <string>
#include <iostream>

int main()
{
	library lib1;
    
    book bookWeWishFor("My Favorite Book", "My Favorite Author", 1337);
    
    unsigned int user1 = lib1.registerUser();
    unsigned int user2 = lib1.registerUser();
    unsigned int user3 = lib1.registerUser();
    unsigned int user4 = lib1.registerUser();
    unsigned int user5 = lib1.registerUser();

    unsigned int times = lib1.getTimesWishedFor(bookWeWishFor);
    std::cerr << "getTimesWishedFor: expected 0 got " << times << std::endl;
    
    lib1.wishForABook(lib1.findUserById(user1), bookWeWishFor);
    
    times = lib1.getTimesWishedFor(bookWeWishFor);
    std::cerr << "getTimesWishedFor: expected 1 got " << times << std::endl;
    
    lib1.wishForABook(lib1.findUserById(user2), bookWeWishFor);
    
    times = lib1.getTimesWishedFor(bookWeWishFor);
    std::cerr << "getTimesWishedFor: expected 2 got " << times << std::endl;
    
    lib1.wishForABook(lib1.findUserById(user3), bookWeWishFor);
    
    times = lib1.getTimesWishedFor(bookWeWishFor);
    std::cerr << "getTimesWishedFor: expected 3 got " << times << std::endl;
    
    lib1.wishForABook(lib1.findUserById(user4), bookWeWishFor);
    
    times = lib1.getTimesWishedFor(bookWeWishFor);
    std::cerr << "getTimesWishedFor: expected 4 got " << times << std::endl;
    
    lib1.wishForABook(lib1.findUserById(user5), bookWeWishFor);

    return 0;
}
