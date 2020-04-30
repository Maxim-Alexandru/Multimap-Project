#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct TElements
{
	pair<string, string> book;
	int next;
}t;

class Iterator;

typedef int(*TFunction)(const string& author, int cap);

class Multimap
{
	private:
		TElements* TElems;
		int cap;
		int firstEmpty;
		TFunction h;
	public:
		Iterator iterator();
		TElements* getTElems() { return this->TElems; }
		int getCapacity() { return this->cap; }
		int getFirstEmpty() { return this->firstEmpty; }
		TFunction getH() { return this->h; }
		void add(string& author, string& title);
		bool remove(string& author, string& title);
		vector<string> search(const string& author);
		void replace(string& author, string& old_title, string& new_title);
		int size();
		Multimap() {};
		Multimap(TFunction h);
		~Multimap();
};

class Iterator
{
	private:
		Multimap& mm;
		int currentElement;
	public:
		Iterator(Multimap& mm);
		~Iterator();
		pair<string, string> getCurrent();
		void next();
		bool valid();
};
