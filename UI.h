#pragma once
#include "Multimap.h"

class UI
{
private:
	Multimap& mm;
public:
	UI(Multimap& mm) : mm(mm) {}
	static void printMenu();
	void populate();
	void start();
	static pair<string, string> readBook();
	~UI();
};

