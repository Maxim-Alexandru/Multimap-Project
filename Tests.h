#pragma once
#include "Multimap.h"
#include <assert.h>

class Test
{
	public:
		Test() {};
		~Test() {};
		static void test_create();
		static void test_size();
		static void test_add();
		static void test_delete();
		static void test_search();
		static void test_iterator();
};
