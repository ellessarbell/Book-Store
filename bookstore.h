#pragma once
#include <string>
#include <iostream>
using namespace std;
#include "book.h"

class BookStore {

public:
	BookStore(size_t);
	bool AddBook(const Book&);
	bool RemoveBook(size_t);
	int FindByISBN(const string& isbn);
	int FindByName(const string& name, size_t = 0);
	int Read(istream&);
	int Write(ostream&);
	bool IsFull();
	Book* Get(size_t position);
	size_t GetBookCount();
	void Sort();
	~BookStore();

private:
	Book** _books;
	size_t _capacity;
	size_t _bookCount;
	int BinarySearch(const string&);
};
