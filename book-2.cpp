#include <iostream>	
#include <string>
#include <cassert>
#include <iomanip>
#include <sstream>
#include "assert.h"

using namespace std;

#include "book.h"

// book constructor
// Params: isbn, name, quantity
// Returns: nothing
// Format Error: N/A
Book::Book(const string& isbn, const string& name, size_t quantity)
{
	_name = name;
	_isbn = isbn;
	_quantity = quantity;
	_authorCount = 0;
}

// book constructor
// Params: isbn, name, author, quantity
// Returns: nothing
// Format Error: N/A
Book::Book(const string& isbn, const string& name, const string& aut, size_t quantity)
{
	_name = name;
	_isbn = isbn;
	_quantity = quantity;
	_authorCount = 0;
	_authors[0] = aut;
}

// Book copy constructor
// Params: a book pointer
// Returns: nothing
// Format Error: N/A
Book::Book(const Book& book)
{
	_name = book.GetName();
	_isbn = book.GetISBN();
	_quantity = book.GetQuantity();
	_authorCount = book.GetAuthorCount();
	for (size_t i = 0; i < _authorCount; i++)
	{
		_authors[i] = book._authors[i];
	}

}

// adds an author to to the array
// Params: author
// Returns: nothing
// Format Error: N/A
bool Book::AddAuthor(const string& author)
{
	if (_authorCount == MAX_AUTHORS)
		return false;
	else
	{
		for (size_t i = 0; i < MAX_AUTHORS; i++)
		{
			if (_authors[i] == "")
			{
				_authors[i] = author;
				_authorCount++;
				return true;
			}
		}
	}
}

// getter
size_t Book::GetAuthorCount() const
{
	return _authorCount;
}

// getter
string Book::GetName() const
{
	return _name;
}

// getter
string Book::GetISBN() const
{
	return _isbn;
}

// getter
int Book::GetQuantity() const
{
	return _quantity;
}

// Turns inputted values into one string
// Params: N/A
// Returns: formatted string
// Format Error: N/A
string Book::ToString()
{
	stringstream e;
	e << left << setw(10) << _isbn << setw(5) << _quantity << setw(10) << _name << setw(5);
	for (size_t i = 0; i < _authorCount; i++)
	{
		e << _authors[i] << "   ";
	}
	e << endl;
	return e.str();
}

// Increase quantity
// Params: n/a
// Returns: nothing
// Format Error: N/A
void Book::IncreaseQuantity()
{
	_quantity++;
}


// Reads the file, and pulls out any info necessary
// Params: istream instance
// Returns: N/A
// Format Error: N/A
void Book::Read(istream& readStream)
{
	readStream >> _isbn >> _quantity >> _name >> _authorCount;

	for (size_t i = 0; i < _authorCount; i++)
	{
		readStream >> _authors[i];
	}

	for (size_t i = 0; i < _authorCount; i++)
	{
		for (size_t j = 0; j < _authors[i].length(); j++)
		{
			if (_authors[i].substr(j, 1) == "_")
				_authors[i].replace(j, 1, " ");
		}
	}

	for (size_t i = 0; i < _name.length(); i++)
	{
		if (_name.substr(i, 1) == "_")
			_name.replace(i, 1, " ");
	}
	
}

// checks if the array contains the author specified
// Params: author
// Returns: true if it is found, false if not
// Format Error: N/A
bool Book::ContainsAuthor(const string& author)
{
	for (size_t i = 0; i < _authorCount; i++)
	{
		if (_authors[i].find(author, 0) != -1)
			return true;
	}

	return false;
}

// decreases quantity
// Params: N/A
// Returns: true if quantity can be lowered, false if not
// Format Error: N/A
bool Book::DecreaseQuantity()
{
	if (_quantity == 0)
	{
		return false;
	}
	else
	{
		_quantity--;
		return true;
	}

}

// Writes to the ostream
// Params: ostream instance
// Returns: nothing
// Format Error: N/A
void Book::Write(ostream& writeStream)
{
	writeStream << "        " << setw(15) << _isbn << setw(4) << _quantity;
	writeStream << setw(30) << left << _name;
	for (size_t i = 0; i < MAX_AUTHORS; i++)
	{
		if (_authors[i] != "")
			writeStream << _authors[i] << "  ";
	}
	writeStream << endl;
}
