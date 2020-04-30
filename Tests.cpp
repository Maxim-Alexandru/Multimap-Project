#include "Tests.h"
#include <iostream>

int h(const string& author, int cap)
{
	int s = 0;
	for (int i = 0; i < (int)(author.size()); i++)
		s += (int)(author[i]);
	return s % cap;
}

void Test::test_create()
{
	Multimap mm{h};
	assert(mm.getCapacity() == 120);
	assert(mm.getFirstEmpty() == 0);
}

void Test::test_size()
{
	Multimap mm{h};
	pair<string, string> book1;
	pair<string, string> book2;
	book1.first = "Author1";
	book1.second = "Book1";
	book2.first = "Author2";
	book2.second = "Book2";
	assert(mm.size() == 0);
	mm.add(book1.first, book1.second);
	assert(mm.size() == 1);
	mm.add(book2.first, book2.second);
	assert(mm.size() == 2);
}

void Test::test_add()
{
	Multimap mm{h};
	pair<string, string> book1;
	pair<string, string> book2;
	pair<string, string> book3;
	pair<string, string> book4;
	book1.first = "Author1";
	book1.second = "Book1";
	book2.first = "Author1";
	book2.second = "Book1";
	book3.first = "Author2";
	book3.second = "Book2";
	book4.first = "Author2";
	book4.second = "Book3";
	mm.add(book1.first, book1.second);
	assert(mm.size() == 1);
	mm.add(book2.first, book2.second);
	assert(mm.size() == 1);
	mm.add(book3.first, book3.second);
	assert(mm.size() == 2);
	mm.add(book4.first, book4.second);
	assert(mm.size() == 3);
}

void Test::test_delete()
{
	Multimap mm{h};
	pair<string, string> book1;
	pair<string, string> book2;
	pair<string, string> book3;
	pair<string, string> book4;
	book1.first = "Author1";
	book1.second = "Book1";
	book2.first = "Author1";
	book2.second = "Book1";
	book3.first = "Author2";
	book3.second = "Book2";
	book4.first = "Author2";
	book4.second = "Book3";
	mm.add(book1.first, book1.second);
	mm.add(book2.first, book2.second);
	mm.add(book3.first, book3.second);
	mm.add(book4.first, book4.second);
	assert(mm.remove(book1.first, book1.second) == true);
	assert(mm.remove(book2.first, book2.second) == false);
	assert(mm.remove(book3.first, book3.second) == true);
	assert(mm.remove(book4.first, book4.second) == true);
	assert(mm.remove(book4.first, book4.second) == false);

}

void Test::test_search()
{
	Multimap mm{h};
	pair<string, string> book1;
	pair<string, string> book2;
	pair<string, string> book3;
	pair<string, string> book4;
	pair<string, string> book5;
	book1.first = "Author1";
	book1.second = "Book1";
	book2.first = "Author1";
	book2.second = "Book1";
	book3.first = "Author2";
	book3.second = "Book2";
	book4.first = "Author2";
	book4.second = "Book3";
	book5.first = "Author0";
	book5.second = "Book0";
	mm.add(book1.first, book1.second);
	mm.add(book2.first, book2.second);
	mm.add(book3.first, book3.second);
	mm.add(book4.first, book4.second);
	vector<string> list = mm.search("Author1");
	assert(list.size() == 1);
	list = mm.search("Author2");
	assert(list.size() == 2);
	list = mm.search("Author0");
	assert(list.size() == 0);
}

void Test::test_iterator()
{
	Multimap mm{h};
	Iterator it = mm.iterator();
	try
	{
		while (!it.valid())
		{
			it.getCurrent();
			it.next();
			assert(false);
		}
	}
	catch (...)
	{
		assert(true);
	}
}
