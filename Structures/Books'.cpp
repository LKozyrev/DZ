#include <iostream>
#include <string>
using namespace std;
struct AuthorName {
	string FirstName;
	string LastName;
	AuthorName() { FirstName = "Unknown", LastName = "Unknown";};
	AuthorName(string Firstname, string Lastname) { this->FirstName = Firstname; this->LastName = Lastname;};
};
struct Book {
	string name;
	struct AuthorName authorName;
	int year;
	int pages;
	Book(string name, struct AuthorName authorName, int year, int pages) { this->name = name; this->authorName = authorName; this->year = year; this->pages = pages; }
	Book() { name = "Unknown"; authorName = {}; year = 0; pages = 0;};
	void DisplayBook() {
		cout << "Name: " << name << endl;
		cout << "Author: "<<authorName.FirstName<<" "<<authorName.LastName;
		cout << endl << "Year of release: " << year<<endl;
		cout << "Number of pages: " << pages << endl << endl;
	}
};
struct Book CreateBook(string name, string FirstName, string LastName, int year, int pages) {
	struct AuthorName authorname = { FirstName, LastName };
	struct Book book = {name, authorname, year, pages};
	return book;

}
int main()
{
	struct Book books[3] = { CreateBook("Idiot", "Fyodor", "Dostoyevskiy", 1867, 726), CreateBook("The plague", "Albert", "Camus", 1947, 312), CreateBook("Notre-Dame de Paris", "Victor", "Hugo", 1831, 557) };
	for (int i = 0; i < 3; i++) {
		books[i].DisplayBook();
	}
	struct Book UnitializedBook;
	UnitializedBook.DisplayBook();
}