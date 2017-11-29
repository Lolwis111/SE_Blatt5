#include "library.h"

#include <string>

int main()
{
	library lib1;

	std::string title = "Title";
	std::string author = "Author";

	for (int i = 0; i < 10; i++)
	{
		book book1(title, author, i);

		lib1.addBookToLibrary(book1);
	}



    return 0;
}