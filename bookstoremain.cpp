// Author: Dylan Bell
// Lab_07
// Data Structures 1
// 5/30/2018

#include <iostream>	
#include <string>
#include <fstream>

using namespace std;

#include "bookstore.h"

// validation function prototypes
bool CheckSwitch(const int choice);
bool ValidateName(string name);
bool ValidateISBN(string ISBN);
bool ValidateQuantity(size_t quantity);

int main()
{
	// objects and initializers
	bool loopAgain = true;
	int choice = 0, index = 0, index2;
	size_t quantity, authorAmount, capacity;
	string fileName, name, newChoice, newName, isbn, newISBN, author1, author2, author3;
	string bars = "-------------------------------------------------";
	string menu = "1. Load Books from File \n2. Save Books to File \n3. List Books \n4. Add Book \n5. Sell a Book \n6. Sort Books \n7. Find Book (Book Name) \n8. Find Book (ISBN) \n9. Remove Book \n0. Exit";
	ifstream fin;
	BookStore *obj;

	cout << "What is the maximum amount of books available: ";
	cin >> capacity;
	obj = new BookStore(capacity);

	while (loopAgain)
	{
		// prints menu
		cout << bars << endl;
		cout << menu << endl;
		cout << bars << endl;

		cin.clear();
		cout << "Your command: ";
		cin >> choice;

		if (CheckSwitch(choice) == false) // makes sure choice is valid
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Input a value from 1-9" << endl;
			cin >> choice;
		}

		switch (choice) 
		{
			case 1: // asks user for file name and checks to see if it is valid
			{
				cout << "Filename to Load: ";
				cin >> fileName;
				fin.open(fileName);

				// produces error if file cannot be found
				if (fin.fail())
				{
					cerr << "Could not open: " << fileName << endl;
					exit(1);
				}

				obj->Read(fin);
				cout << "File Loaded " << obj->GetBookCount() << " books loaded" << endl;
				cout << obj->Read(fin) << " books dropped from file" << endl;
				fin.close();
				break;
			}
			case 2: // saves book data to file
			{
				string fileName1;
				cout << "File name to save: ";
				cin >> fileName1;
				ofstream fout(fileName1);

				if (fout.fail()) 
				{
					cout << "Cannot open file, please enter new file name: ";
					exit(1);
				}

				cout << "Succesfully written " << obj->Write(fout) << " books to " << fileName1 << endl << endl;
				break;
			}
			case 3: // List all books
			{
				cout << "Books Loaded: " << obj->GetBookCount() << endl << endl;
				obj->Write(cout);
				cout << endl;
				break;
			}
			case 4: // add book
			{
				if (obj->IsFull())
				{
					cout << "Cannot add more records. Bookstore is full" << endl;
				}
				else
				{
					cout << "Please input------------------" << endl;
					cout << "ISBN: ";
					cin >> newISBN;

					while (ValidateISBN(newISBN) == false) // validates and clears
					{
						cin.clear();
						cin.ignore(255, '\n');
						cout << "Input a valid ISBN: " << endl;
						cin >> newISBN;
						break;
					}
					cout << endl;

					cout << "Book Name: ";
					cin.clear();
					cin.ignore(255, '\n');
					getline(cin, newName);
					while (ValidateName(newName) == false) // validates and clears
					{
						cin.clear();
						cin.ignore(255, '\n');
						cout << "Input a valid name: " << endl;
						cin >> newName;
						break;
					}
					cout << endl;

					cout << "Quantity";
					cin >> quantity;
					while (ValidateQuantity(quantity) == false) // validates and clears
					{
						cin.clear();
						cin.ignore(255, '\n');
						cout << "Input a correct Quantity: " << endl;
						cin >> quantity;
						break;
					}
					cout << endl;

					cout << "Number of Authors (Max 3): ";
					cin >> authorAmount;
					if (authorAmount == 1)
					{
						cout << "Author 1: ";
						cin.clear();
						cin.ignore(255, '\n');
						getline(cin, author1);
						while (ValidateName(author1) == false) // validates and clears
						{
							cin.clear();
							cin.ignore(255, '\n');
							cout << "Input a correct author: " << endl;
							cin >> author1;
							break;
						}
						Book item(newISBN, newName, author1, quantity);
						item.AddAuthor(author1);

						obj->AddBook(item); // adds book
						cout << newName << " added successfully" << endl;
					}

					else if (authorAmount == 2)
					{
						cout << "Author 1: ";
						cin.clear();
						cin.ignore(255, '\n');
						getline(cin, author1);
						while (ValidateName(author1) == false) // validates and clears
						{
							cin.clear();
							cin.ignore(255, '\n');
							cout << "Input a correct author: " << endl;
							cin >> author1;
						}
						Book item(newISBN, newName, author1, quantity);
						item.AddAuthor(author1);

						cout << "Author 2: ";
						cin.clear();
						cin.ignore(255, '\n');
						getline(cin, author2);
						while (ValidateName(author2) == false) // validates and clears
						{
							cin.clear();
							cin.ignore(255, '\n');
							cout << "Input a correct author: " << endl;
							cin >> author2;
						}
						item.AddAuthor(author2);
						obj->AddBook(item); // adds book
						cout << newName << " added successfully" << endl;

					}
				
					if (authorAmount == 3)
					{
						cout << "Author 1: ";
						cin.clear();
						cin.ignore(255, '\n');
						getline(cin, author1);

						while (ValidateName(author1) == false) // validates and clears
						{
							cin.clear();
							cin.ignore(255, '\n');
							cout << "Input a correct author: " << endl;
							cin >> author1;
						}
						Book item(newISBN, newName, author1, quantity);
						item.AddAuthor(author1);

						cout << "Author 2: ";
						cin.clear();
						cin.ignore(255, '\n');
						getline(cin, author2);

						while (ValidateName(author2) == false) // validates and clears
						{
							cin.clear();
							cin.ignore(255, '\n');
							cout << "Input a correct author: " << endl;
							cin >> author2;
						}
						item.AddAuthor(author2);

						cout << "Author 3: ";
						cin.clear();
						cin.ignore(255, '\n');
						getline(cin, author3);

						while (ValidateName(author3) == false) // validates and clears
						{
							cin.clear();
							cin.ignore(255, '\n');
							cout << "Input a correct author: " << endl;
							cin >> author3;
						}
						item.AddAuthor(author3);

						obj->AddBook(item); // adds book
						cout << newName << " added successfully" << endl;
					}
				}
				break;
			
			}
			case 5: // Sells a book
			{
				cout << "Book Selling ------------------" << endl;
				cout << "Please input ISBN: ";
				cin >> isbn;
				cout << endl;
				index2 = obj->FindByISBN(isbn);
				cout << obj->Get(index2)->ToString();
				cout << "Available Inventory: " << obj->Get(index2)->GetQuantity() << endl;
				if (obj->Get(index2)->GetQuantity() == 0)
				{
					cout << "Could not sell book. No more copies in inventory." << endl;
					break;
				}
				else
					obj->Get(index2)->DecreaseQuantity();
				cout << "Book Sold" << endl;
				cout << "Current Quantity: " << obj->Get(index2)->GetQuantity() << endl;
				break;

			}
			case 6: // Sorts books
			{
				obj->Sort();
				cout << endl << endl;
				break;
			}
			case 7: // Find Book By Name
			{
				cout << " --- Find By Book Name --- ";
				cout << "Author (No spaces): ";
				cin >> name;
				index2 = obj->FindByName(name);
				if (obj->FindByISBN(isbn) == -1)
				{
					cout << "Please enter a valid name: ";
					cin.clear();
					cin.ignore(255, '\n');
					cin >> isbn;
				}
				cout << obj->Get(index2)->ToString();
				break;
			}
			case 8: // Find Book by ISBN
			{
				cout << "Enter ISBN: ";
				cin >> isbn;
				index2 = obj->FindByISBN(isbn);
				if (obj->FindByISBN(isbn) == -1)
				{
					cout << "Please enter a valid ISBN: ";
					cin.clear();
					cin.ignore(255, '\n');
					cin >> isbn;
				}
				cout << obj->Get(index2)->ToString();
				break;
			}
			case 9: // ends the switch statement and exits out of the program
			{
				char choice;
				string isbn;
				cout << "Please input ISBN of book to erase: " << endl;
				cin >> isbn;
				cout << endl;

				index2 = obj->FindByISBN(isbn);

				if (obj->FindByISBN(isbn) == -1)
				{
					cout << "Please enter a valid ISBN: ";
					cin.clear();
					cin.ignore(255, '\n');
					cin >> isbn;
				}
				cout << obj->Get(index2)->ToString();


				cout << "Really Erase (y/n): " << endl;
				cin >> choice;

				// validates  choice and clears
				if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
				{
					cin.clear();
					cin.ignore(255, '\n');
					cout << "Please enter a correct option. (Y/N)" << endl;
					cin >> newChoice;
					break;
				}

				//if answer is yes
				else if (choice == 'y' || choice == 'Y')
				{
					obj->RemoveBook(index2);
				}

				else if (choice == 'N' || choice == 'n') // exits if user chooses no
				{
					break;
				}
				break;
			}
			case 0: // ends the switch statement and exits out of the program
			{
				loopAgain = false;
				delete obj;
				break;
			}
			default: // defaults if choice is invalid
			{
				cout << "Invalid input, please try again" << endl;
				cin.clear();
				cin.ignore(255, '\n');
				break;
			}
		}
	}
	return 0;
}

// Validates that inputted choice for the switch statement is valid
// Params: any const int that the user enters
// Returns: false if choice is invalid, true if valid
// Format Error: N/A
bool CheckSwitch(const int choice)
{
	if (isalnum(choice) && choice > 0 || choice < 10)
	{
		return true;
	}
	return false;
}

// Validates that inputted string is valid
// Params: any string user enters
// Returns: false if it is invalid, true if valid
// Format Error: N/A
bool ValidateName(string name)
{
	while (name.find_first_of("0123456789") != -1)
	{
		cout << "No digits are allowed in name." << endl;
		cin.clear();
		cin.sync();
		getline(cin, name);
		return false;
	}
	return true;
}

// Validates that inputted id is valid
// Params: any unsigned int user enters
// Returns: false if it is invalid, true if valid
// Format Error: N/A
bool ValidateISBN(string isbn)
{
	for (size_t i = 0; i < isbn.size(); i++) {
		if (!isalpha(isbn[i]) || !isspace(isbn[i]) && isbn.length()>0 && isbn.length() < 14) 
			return true;
	}
	return false;
}

// Validates that inputted salary is valid
// Params: any double that the user enters
// Returns: false if it is invalid, true if valid
// Format Error: N/A
bool ValidateQuantity(size_t quantity)
{
	if (isalnum(quantity) && (quantity >= 0) && (quantity < MAX_BOOKS))
	{
		return true;
	}
	return false;
}