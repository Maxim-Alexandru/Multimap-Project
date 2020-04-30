#include "Multimap.h"
#include <string>

using namespace std;

Iterator Multimap::iterator()
{
	return Iterator(*this);
}

void Multimap::add(string& author, string& title)
{
	pair<string, string> book;
	book.first = author;
	book.second = title;
	int index = this->h(book.first, this->cap);
	if (this->TElems[index].book == book)
		return;
	if (index == firstEmpty)
	{
		this->TElems[index].book = book;
		while (this->TElems[index].book.first != "" && this->TElems[index].book.second != "")
			this->firstEmpty++;
	}
	if (this->TElems[index].book.first == "" && this->TElems[index].book.second == "")
		this->TElems[index].book = book;
	else
	{
		int getNext = this->TElems[index].next;
		if (getNext == -1)
		{
			this->TElems[firstEmpty].book = book;
			this->TElems[index].next = firstEmpty;
		}
		else
		{
			while (this->TElems[getNext].next != -1 and this->TElems[getNext].book != book)
				getNext = this->TElems[getNext].next;
			if (this->TElems[getNext].book == book)
				return;
			this->TElems[firstEmpty].book = book;
			this->TElems[getNext].next = firstEmpty;
		}
		while (this->TElems[this->firstEmpty].book.first != "" && this->TElems[this->firstEmpty].book.second != "")
			this->firstEmpty++;
	}

}

bool Multimap::remove(string& author, string& title)
{
	pair<string, string> book;
	book.first = author;
	book.second = title;
	int i = this->h(book.first, this->cap);
	int j = -1;
	int index = 0;
	while (index < this->cap and j == -1)
		if (this->TElems[index].next == i)
			j = index;
		else
			index++;
	while (i != -1 and this->TElems[i].book.first != author)
	{
		j = i;
		i = this->TElems[i].next;
	}
	if (i == -1)
		return false;
	else
	{
		bool over = false;
		do
		{
			int p = this->TElems[i].next;
			int prev_p = i;
			while (p != -1 and this->h(this->TElems[p].book.first, this->cap) != i)
			{
				prev_p = p;
				p = this->TElems[p].next;
			}
			if (p == -1)
				over = true;
			else
			{
				this->TElems[i] = this->TElems[p];
				j = prev_p;
				i = p;
			}
		} while (!over);
		if (j != -1)
		{
			this->TElems[j].next = this->TElems[i].next;
		}
		this->TElems[i].book.first = "empty";
		this->TElems[i].book.second = "empty";
		this->TElems[i].next = -1;
		if (this->firstEmpty > i)
			this->firstEmpty = i;
	}
	return true;
}

vector<string> Multimap::search(const string& author)
{

	int index = this->h(author, this->cap);
	vector<string> list;
	while (this->TElems[index].next != -1)
	{
		if (this->TElems[index].book.first == author)
			list.push_back(this->TElems[index].book.second);
		index = this->TElems[index].next;
	}
	if (this->TElems[index].book.first == author)
		list.push_back(this->TElems[index].book.second);
	return list;
}

void Multimap::replace(string & author, string & old_title, string & new_title)
{
	int index = this->h(author, cap);
	while (this->TElems[index].next != -1)
	{
		if (this->TElems[index].book.first == author && this->TElems[index].book.second == old_title)
			this->TElems[index].book.second = new_title;
		index = this->TElems[index].next;
	}
	if (this->TElems[index].next == -1)
		if (this->TElems[index].book.first == author && this->TElems[index].book.second == old_title)
			this->TElems[index].book.second = new_title;
}

int Multimap::size()
{
	int size = 0;
	for (int i = 0; i < this->cap; i++)
		if (this->TElems[i].book.first != "" && this->TElems[i].book.second != "" && this->TElems[i].book.first != "empty" && this->TElems[i].book.second != "empty")
			size++;
	return size;
}

Multimap::Multimap(TFunction h)
{
	this->cap = 120;
	this->firstEmpty = 0;
	this->TElems = new TElements[cap];
	for (int i = 0; i < cap; i++)
	{
		TElems[i].book.first = "";
		TElems[i].book.second = "";
		TElems[i].next = -1;
	}
	this->h = h;
}

Multimap::~Multimap() 
{
	delete[] this->TElems;
}

Iterator::Iterator(Multimap& mm) : mm(mm), currentElement(0) {
	if (this->mm.size() == 0)
		currentElement = this->mm.getCapacity();
	else
	{
		while
			(this->currentElement < this->mm.getCapacity() &&
				this->mm.getTElems()[this->currentElement].book.first == "" &&
				this->mm.getTElems()[this->currentElement].book.first == "")
			this->currentElement++;
	}
}

Iterator::~Iterator() {}

pair<string, string> Iterator::getCurrent()
{
	if (this->valid())
		return this->mm.getTElems()[currentElement].book;
	else
	{
		string s = "The cuurent element is no longer valid.";
		throw s;
	}
}

void Iterator::next()
{
	if (!this->valid())
	{
		string s = "Invalid position.";
		throw s;
	}
	this->currentElement++;
	while 
	   (this->currentElement < this->mm.getCapacity() && 
		this->mm.getTElems()[this->currentElement].book.first == "" &&
		this->mm.getTElems()[this->currentElement].book.first == "")
			this->currentElement++;
}

bool Iterator::valid()
{
	if (this->currentElement < this->mm.getCapacity())
		return true;
	return false;
}
 