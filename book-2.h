#include <string>
#include <iostream>
using namespace std;

#ifndef BOOK_H
#define BOOK_H

class Book {

public:
	Book(const string&, const string&, size_t = 0); // Set quantity default value to 0
	Book(const string&, const string&, const string&, size_t = 0);
	Book(const Book&);
	bool AddAuthor(const string&);
	string ToString();
	void Write(ostream&);
	void Read(istream&);
	bool ContainsAuthor(const string&);
	bool DecreaseQuantity();
	void IncreaseQuantity();
	int GetQuantity() const;
	string GetISBN() const;
	string GetName() const;
	size_t GetAuthorCount() const;

private:
	const static int MAX_AUTHORS = 3;
	string _name;
	string _authors[MAX_AUTHORS];
	string _isbn;
	size_t _authorCount;
	size_t _quantity;
};

#endif //BOOK_H