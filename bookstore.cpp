#include <iostream>	
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include "assert.h"

using namespace std;

#include "bookstore.h"

// bookstore constructor
// Params: size_t item
// Returns: nothing
// Format Error: N/A
BookStore::BookStore(size_t item)
{
	_capacity = item;
	_books = new Book*[_capacity];
	for (unsigned int i = 0; i < _capacity; i++)
	{
		_books[i] = NULL;
	}
	_bookCount = 0;
}

// Adds book using pointers
// Params: a book item
// Returns: true if the array is not full and the actions are followed through, false if not
// Format Error: N/A
bool BookStore::AddBook(const Book& book)
{
	Book* ePointer;

	if (!IsFull())
	{
		ePointer = new Book(book);
		_books[_bookCount] = ePointer;
		_bookCount++;
		return true;
	}
	else
		return false;
}

// Removes book
// Params: a position
// Returns: true if the book is and can be deleted, false if else
// Format Error: N/A
bool BookStore::RemoveBook(size_t pos)
{
	// returns false if pos cannot be found
	if ((pos < 0) || (pos > _capacity) || (pos >= _bookCount) || (_capacity == 0))
	{ 
		return false;
	}
	 
	// deletes the specific book at position specified by pos
	delete _books[pos];

	// shifts the array
	for (size_t i = pos; i < _capacity; i++)
	{
		_books[i] = _books[i + 1];
	}

	// fills empty spot with a NULL value and decrements the book count
	_books[_bookCount - 1] = NULL;
	_bookCount--;
	return true;
}

// Searches for specified ISBN by using a passed in isbn
// Params: specified isbn
// Returns: the position if succesfull, -1 if not
// Format Error: N/A
int BookStore::FindByISBN(const string& isbn)
{
	for (size_t i = 0; i < _bookCount; i++)
	{
		if (isbn == _books[i]->GetISBN())
		{
			return i;
		}
	}
	return -1;
}

// Searches for specified book by using their name
// Params: specified name and start index
// Returns: position of book based on name and -1
// Format Error: N/A
int BookStore::FindByName(const string& name, size_t position)
{
	size_t nameLength = name.length();
	for (size_t i = position; i < _bookCount; i++)
	{
		if (_books[i]->GetName().find(name) != string::npos)
		{
			return i;
		}
	}
	return -1;
}

// Reads through the file and adds books to the array
// Params: istream instance
// Returns: the dropeed count
// Format Error: N/A
int BookStore::Read(istream& readBook)
{
	size_t dropped = 0;
	size_t counter = 0;

	while (!readBook.eof())
	{
		if (counter > _capacity)
			dropped++;

		Book *bPointer = new Book("", "", "", 0);

		bPointer->Read(readBook);
		if (readBook.eof())
			break;

		AddBook(*bPointer);
		counter++;

		delete bPointer;
	}
	return dropped;
}

// Writes book to specified spot in array
// Params: ostream instance
// Returns: the book count
// Format Error: N/A
int BookStore::Write(ostream& writeBook)
{
	for (size_t i = 0; i < _bookCount; i++)
	{
		_books[i]->Write(writeBook);
	}
	return _bookCount;
}

// Checks to see if the database is full or not
// Params: N/A
// Returns: true if it is full, false if not
// Format Error: N/A
bool BookStore::IsFull()
{
	if (_bookCount == _capacity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Gets the book position
// Params: specified position
// Returns: the book position if the position is valid, NULL if not
// Format Error: N/A
Book* BookStore::Get(size_t position)
{
	if (position < _capacity && _books[position] != NULL)
	{
		return _books[position];
	}
	else
		return NULL;
}

// getter
unsigned int BookStore::GetBookCount()
{
	return _bookCount;
}

// Uses binary search to find the specified spot in the database
// Params: specified value
// Returns: the correct position and -1
// Format Error: N/A
int BookStore::BinarySearch(const string& value)
{
	Sort();
	int first = 0;
	int last = _bookCount - 1;

	// binary search
	while (first <= last)
	{
		int mid = (first + last) / 2;

		if (value < _books[mid]->GetISBN())
			last = mid - 1;
		else if (value > _books[mid]->GetISBN())
			first = mid + 1;
		else
			return mid;
	}
	return -1;
}

// Sorts the database correctly
// Params: N/A
// Returns: N/A
// Format Error: N/A
void BookStore::Sort()
{
	bool exchangeMade = true;

	Book *pointer;

	for (size_t pass = 1; pass < _bookCount && exchangeMade; pass++)
	{
		exchangeMade = false;
		// On each pass the range of elements decreases by 1
		for (size_t index = 0; index < _bookCount - pass; index++)
		{
			// If adjacent pair out of order, swap them
			if (_books[index]->GetISBN() > _books[index + 1]->GetISBN())
			{
				pointer = _books[index];
				_books[index] = _books[index + 1];
				_books[index + 1] = pointer;
				exchangeMade = true;
			}
		}
	}
}

// destructor
BookStore::~BookStore()
{
	for (size_t i = 0; i < _bookCount; i++)
	{
		if (_books[i] != NULL)
		{
			delete _books[i];
		}
	}
	delete[] _books;
}
