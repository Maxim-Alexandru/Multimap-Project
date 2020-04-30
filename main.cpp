#include "Multimap.h"
#include <iostream>
#include "Tests.h"
#include "UI.h"

int h1(const string& author, int cap)
{
	int s = 0;
	for (int i = 0; i < (int)(author.size()); i++)
		s += (int)(author[i]);
	return s % cap;
}

int main()
{
	{
		Test t{};
		t.test_create();
		t.test_size();
		t.test_add();
		t.test_delete();
		t.test_search();
		t.test_iterator();
		Multimap mm{ h1 };
		UI ui{ mm };
		ui.start();
	}
	system("pause");
	_CrtDumpMemoryLeaks();
	return 0;
}