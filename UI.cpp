#include "UI.h"

void UI::printMenu()
{
	cout << "Welcome to the library! Here are the tools that you need in order to modify the database of the library: \n \n";
	cout << "\t 1) Add a new book to the database. \n";
	cout << "\t 2) Remove a book from the database. \n";
	cout << "\t 3) Given a specific author, get a list with all the books written by that author. \n";
	cout << "\t 4) Get all the books from the database. \n";
	cout << "\t 5) Replace. \n";
	cout << "\t 0) Exit the application. \n \n";
}

void UI::populate()
{
	pair<string, string> book1;
	pair<string, string> book2;
	pair<string, string> book3;
	pair<string, string> book4;
	pair<string, string> book5;
	pair<string, string> book6;
	pair<string, string> book7;
	book1.first = "Ray Bradbury";
	book1.second = "Fahrenheit 451";
	book2.first = "Orson Scott Card";
	book2.second = "Ender's Game";
	book3.first = "George Orwell";
	book3.second = "1984";
	book4.first = "Liviu Rebreanu";
	book4.second = "Ion";
	book5.first = "Liviu Rebreanu";
	book5.second = "Padurea Spanzuratilor";
	book6.first = "Liviu Rebreanu";
	book6.second = "Catastrofa";
	book7.first = "Liviu Rebreanu";
	book7.second = "Ion";
	this->mm.add(book1.first, book1.second);
	this->mm.add(book2.first, book2.second);
	this->mm.add(book3.first, book3.second);
	this->mm.add(book4.first, book4.second);
	this->mm.add(book5.first, book5.second);
	this->mm.add(book6.first, book6.second);
	this->mm.add(book7.first, book6.second);

}

void UI::start()
{
	UI::populate();
	while (true)
	{
		UI::printMenu();
		int option = -1;
		cout << "Please enter an option: ";
		cin >> option;
		getchar();
		cout << endl;
		while (option < 0 || option > 5)
		{
			cout << "Please enter a valid option: ";
			cin >> option;
			getchar();
			cout << endl;
		}
		if (option == 0)
		{
			cout << "Thank you for using our program. \n";
			break;
		}
		switch (option)
		{
		case 1:
		{
			pair<string, string> book = UI::readBook();
			this->mm.add(book.first, book.second);
			break;
		}
		case 2:
		{
			pair<string, string> book = UI::readBook();
			if (this->mm.remove(book.first, book.second) == true)
				cout << "The removal was successful. \n \n";
			else
				cout << "Error! The book you are trying to remove does not exist. \n \n";
			break;
		}
		case 3:
		{
			string author;
			cout << "Please enter an author: "; getline(cin, author);
			vector<string> list = this->mm.search(author);
			if (list.size() == 0)
				cout << "At the moment, we do not have books written by " << author << endl<< endl;
			else
			{
				cout << "Here is a list with the books written by " << author << ": "<< endl<<endl;
				for (auto book : list)
					cout << "\t * [ " << book << " ]" << endl;
			}
			cout << endl;
			break;
		}
		case 4:
		{
			pair<string, string> book;
			Iterator it = mm.iterator();
			try
			{
				while (it.valid())
				{
					book = it.getCurrent();
					if (book.first != "empty")
						cout << "\t * Author: " << book.first << ": " << "[ " << book.second << " ]\n";
					it.next();
				}
			}
			catch (string& exception)
			{
				cout << exception << endl; 
			}
			cout << endl;
			break;
		}
		case 5:
		{
			string author;
			string old_title;
			string new_title;
			cout << "Please give the name of the author: "; getline(cin, author);
			cout << "Please enter the old title of the book written by this author: "; getline(cin, old_title);
			cout << "Please enter the new title of the book written by this author: "; getline(cin, new_title);
			this->mm.replace(author, old_title, new_title);

		}
		case 0:
			break;
		default:
			break;
		}
	}
}

pair<string, string> UI::readBook()
{
	string author;
	string title;
	cout << "Please give the name of the author: "; getline(cin, author);
	cout << "Please enter a book written by this author: "; getline(cin, title);
	pair<string, string> book;
	book.first = author;
	book.second = title;
	return book;
}

UI::~UI() {}
