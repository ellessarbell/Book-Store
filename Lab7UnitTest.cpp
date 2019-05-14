#include "book.h"
#include "bookstore.h"

#include <cassert>
#include <iostream>
#include <sstream>

using std::cerr;
using std::cout;
using std::endl;
using std::stringstream;


int main() {
	cerr << "---------- LAB 7 UNIT TESTS ----------" << endl;
	cerr << "--------------------------------------" << endl << endl;

	cerr << "Test 1 : Book Operations" << endl;
	Book aBook("", "");
	assert(aBook.GetISBN() == "");
	assert(aBook.GetName() == "");
	assert(aBook.GetQuantity() == 0);
	assert(!aBook.ContainsAuthor("John"));
	assert(aBook.AddAuthor("John Lennon"));
	assert(aBook.AddAuthor("Ringo Star"));
	assert(aBook.AddAuthor("George Harrison"));
	assert(!aBook.AddAuthor("Paul McCartney"));
	assert(aBook.ContainsAuthor("John"));
	assert(aBook.ContainsAuthor("Star"));
	assert(aBook.ContainsAuthor("George"));
	assert(!aBook.ContainsAuthor("Paul"));
	assert(!aBook.DecreaseQuantity());
	aBook.IncreaseQuantity();
	assert(aBook.GetQuantity() == 1);
	assert(aBook.DecreaseQuantity());
	assert(aBook.GetQuantity() == 0);
	
	cerr << "\t" << " ____ " << endl;
	cerr << "\t" << "/_   |" << endl;
	cerr << "\t" << " |   |" << endl;
	cerr << "\t" << " |   |" << endl;
	cerr << "\t" << " |___|" << endl;
	cerr << endl;
	cerr << "Passed Test 1 - 1 - 1 - 1 - 1 - 1" << endl;
	cerr << " ---- Book Operations Test ---- " << endl;

	cerr << "Test 2 : Bookstore Operations" << endl;
	cerr << "	2.1 : Initial State" << endl;
	BookStore* store;
	store = new BookStore(10);
	assert(store->GetBookCount() == 0);
	assert(!store->IsFull());
	assert(store->FindByISBN("1234567890123") == -1);
	assert(store->FindByName("") == -1);
	assert(store->Get(0) == nullptr);


	cerr << "\t" << "________      ____ " << endl;
	cerr << "\t" << "\\_____  \\    /_   |" << endl;
	cerr << "\t" << " /  ____/     |   |" << endl;
	cerr << "\t" << "/       \\     |   |" << endl;
	cerr << "\t" << "\\_______ \\ /\\ |___|" << endl;
	cerr << "\t" << "        \\/ \\/      " << endl;

	cerr << "Passed Test 2.1 - 2.1 - 2.1 - 2.1" << endl;
	cerr << " -- Book Store Initial State -- " << endl;

	cerr << "	2.2 : Book Operations Test" << endl;
	assert(store->AddBook(Book("0123456789123", "The Lord of the Rings")));
	assert(store->AddBook(Book("0123456789128", "The Lord of the Clouds")));
	assert(store->AddBook(Book("0123456789127", "The Lord of the Earth")));
	assert(store->AddBook(Book("0123456789129", "The Lord of the Heavens")));
	assert(store->AddBook(Book("0123456789121", "The King of Mars")));
	assert(store->AddBook(Book("0123456789122", "The Lord of the Sun")));
	assert(store->AddBook(Book("0123456789133", "The Lord of the Wind")));
	assert(store->AddBook(Book("0123456789124", "The Lord of the Sea")));
	assert(store->AddBook(Book("0123456789125", "The Lord of Life")));
	assert(store->AddBook(Book("0123456789126", "The Lord of the Land")));
	assert(!store->AddBook(Book("0123456789111", "No Lord")));

	assert(store->FindByISBN("0123456789123") == 0);
	assert(store->FindByISBN("0123456789126") == 9);
	assert(store->FindByName("Sea") == 7);
	assert(store->FindByName("Lord") == 0);
	assert(store->FindByName("Lord", 1) == 1);
	assert(store->FindByName("Lord", 2) == 2);
	assert(store->FindByName("Lord", 3) == 3);
	assert(store->FindByName("Lord", 4) == 5);
	assert(store->FindByName("Lord", 6) == 6);
	assert(store->FindByName("Lord", 7) == 7);
	assert(store->FindByName("Lord", 8) == 8);
	assert(store->FindByName("Lord", 9) == 9);
	assert(store->FindByName("Emperor") == -1);
	assert(store->IsFull());
	assert(store->GetBookCount() == 10);
	assert(store->Get(0)->GetISBN() == "0123456789123");
	assert(store->Get(2)->GetISBN() == "0123456789127");
	assert(store->Get(4)->GetISBN() == "0123456789121");
	assert(store->Get(6)->GetISBN() == "0123456789133");
	assert(store->Get(1)->GetName() == "The Lord of the Clouds");
	assert(store->Get(3)->GetName() == "The Lord of the Heavens");
	assert(store->Get(5)->GetName() == "The Lord of the Sun");
	assert(store->Get(7)->GetName() == "The Lord of the Sea");
	assert(store->Get(9)->GetName() != "Something or Other");
	assert(store->Get(12) == nullptr);
	cerr << "		Remove Related Operations =======" << endl;
	assert(store->RemoveBook(2));
	assert(store->Get(0)->GetISBN() == "0123456789123");
	assert(store->Get(2)->GetISBN() == "0123456789129");
	assert(store->Get(4)->GetISBN() == "0123456789122");
	assert(store->Get(6)->GetISBN() == "0123456789124");
	assert(store->GetBookCount() == 9);
	assert(!store->RemoveBook(9));
	assert(store->RemoveBook(8));
	assert(store->GetBookCount() == 8);
	assert(store->Get(7)->GetISBN() == "0123456789125");
	cerr << "		Successfully Passed Remove Related" << endl
		 << "		Operations" << endl;



	cerr << "\t" << "________      ________  " << endl;
	cerr << "\t" << "\\_____  \\     \\_____  \\ " << endl;
	cerr << "\t" << "/  ____/      /  ____/ " << endl;
	cerr << "\t" << "/       \\     /       \\ " << endl;
	cerr << "\t" << "\\_______ \\ /\\ \\_______ \\" << endl;
	cerr << "\t" << "        \\/ \\/         \\/" << endl;

	cerr << "Passed Test 2.2 - 2.2 - 2.2 - 2.2" << endl;
	cerr << " -- Book Store Operations --- " << endl;
	delete store;


	cerr << "	2.3 : Book Operations I/O" << endl;
	store = new BookStore(10);

	stringstream strBuffer1;
	strBuffer1.str(
		"9783161484100 5 The_Lord_of_the_Rings 3 JRR_Tolkien Jennifer_Lopez Jim_Morrison\n"
		"1402894627217 0 The_Lord_of_the_Clouds 1 Jimmy_Hendrix\n"
		"9781402894621 4 Naruto_Unleashed 0\n"
		"4892247100011 1 How_to_become_Hokage 1 Uzumaki_Naruto\n"
		"7445899439510 8 Life_after_Midnite 1 Angus_Young\n"
		"7884226911045 1 The_DNA_Explained 0\n"
		"0488845222113 0 Jesus_Loves_you 0\n"
		"9781861972712 2 The_Wild_Child 1 Bruce_Dickinson\n"
	);
	assert(store->Read(strBuffer1) == 0);
	assert(store->GetBookCount() == 8);
	assert(!store->IsFull());
	store->Sort();
	assert(store->Get(0)->GetName() == "Jesus Loves you");
	assert(store->Get(1)->GetName() == "The Lord of the Clouds");
	assert(store->Get(2)->GetName() == "How to become Hokage");
	assert(store->Get(3)->GetName() == "Life after Midnite");
	assert(store->Get(4)->GetName() == "The DNA Explained");
	assert(store->Get(5)->GetName() == "Naruto Unleashed");
	assert(store->Get(6)->GetName() == "The Wild Child");
	assert(store->Get(7)->GetName() == "The Lord of the Rings");
	assert(store->Get(0)->GetISBN() == "0488845222113");
	assert(store->Get(1)->GetISBN() == "1402894627217");
	assert(store->Get(2)->GetISBN() == "4892247100011");
	assert(store->Get(3)->GetISBN() == "7445899439510");
	assert(store->Get(4)->GetISBN() == "7884226911045");
	assert(store->Get(5)->GetISBN() == "9781402894621");
	assert(store->Get(6)->GetISBN() == "9781861972712");
	assert(store->Get(7)->GetISBN() == "9783161484100");

	assert(store->AddBook(Book("0001113337418", "An Additional Adventure", "Emma Winger")));
	assert(store->AddBook(Book("9991113337418", "Philosophy of Mind", "Karla Minch")));
	assert(!store->AddBook(Book("0002223337418", "Life in Seattle", "Umma Dunne")));
	assert(store->IsFull());
	assert(store->GetBookCount() == 10);

	assert(store->FindByISBN("1402894627217") == 1);
	assert(store->FindByName("Lord", 0) == 1);
	assert(store->FindByName("Lord", 2) == 7);

	cerr << "\t" << "________      ________  " << endl;
	cerr << "\t" << "\\_____  \\     \\_____  \\ " << endl;
	cerr << "\t" << "/  ____/       _(__  < " << endl;
	cerr << "\t" << "/       \\      /       \\" << endl;
	cerr << "\t" << "\\_______ \\ /\\ /______  /" << endl;
	cerr << "\t" << "        \\/ \\/        \\/ " << endl;


	cerr << "Passed Test 2.3 - 2.3 - 2.3 - 2.3" << endl;
	cerr << " -- Book Store I/O --- " << endl;
	delete store;


	cerr << "	2.4 : Book Operations I/O (2)" << endl;
	store = new BookStore(10);

	stringstream strBuffer2;
	strBuffer2.str(
		"9783161484100 5 The_Lord_of_the_Rings 3 JRR_Tolkien Jennifer_Lopez Jim_Morrison\n"
		"1402894627217 0 The_Lord_of_the_Clouds 1 Jimmy_Hendrix\n"
		"9781402894621 4 Naruto_Unleashed 0\n"
		"4892247100011 1 How_to_become_Hokage 1 Uzumaki_Naruto\n"
		"7445899439510 8 Life_after_Midnite 1 Angus_Young\n"
		"7884226911045 1 The_DNA_Explained 0\n"
		"0488845222113 0 Jesus_Loves_you 0\n"
		"9781861972712 2 The_Wild_Child 1 Bruce_Dickinson\n"
		"1472583690258 1 Another_Day 1 Nicholas_Cage\n"
		"2583691234560 15 Following_the_Path 0\n"
		"7894563697410 2 Memories 1 Peter_Frampton\n"
	);
	assert(store->Read(strBuffer2) == 1);
	assert(store->GetBookCount() == 10);
	assert(store->IsFull());

	cerr << "\t" << "________         _____  " << endl;
	cerr << "\t" << "\\_____  \\       /  |  | " << endl;
	cerr << "\t" << "/  ____/       /   |  |_" << endl;
	cerr << "\t" << "/       \\     /    ^   /" << endl;
	cerr << "\t" << "\\_______ \\ /\\ \\____   | " << endl;
	cerr << "\t" << "        \\/ \\/      |__| " << endl;

	cerr << "Passed Test 2.4 - 2.4 - 2.4 - 2.4" << endl;
	cerr << " -- Book Store I/O (2) --- " << endl;

	delete store;

	cerr << "	2.5 : Book Operations Empty File" << endl;
	store = new BookStore(10);

	stringstream strBuffer3;
	strBuffer3.str();
	assert(store->Read(strBuffer1) == 0);
	assert(store->GetBookCount() == 0);
	assert(!store->IsFull());
	assert(store->Get(0) == nullptr);

	cerr << "\t" << "________       .________" << endl;
	cerr << "\t" << "\\_____  \\      |   ____/" << endl;
	cerr << "\t" << "/  ____/       |____  \\ " << endl;
	cerr << "\t" << "/       \\      /       \\" << endl;
	cerr << "\t" << "\\_______ \\ /\\ /______  /" << endl;
	cerr << "\t" << "        \\/ \\/        \\/ " << endl;

	cerr << "Passed Test 2.5 - 2.5 - 2.5 - 2.5" << endl;
	cerr << " -- Book Operations Empty File --- " << endl;


	cerr << "- - - - - - - - - - - - - - - - - - - - -" << endl << endl;
	cerr << "A L L  T E S T S  S U C C E S S F U L L Y" << endl;
	cerr << "                P A S S E D" << endl << endl << endl;

	delete store;
	return 0;
}