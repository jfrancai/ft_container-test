#include <algorithm>
#include <gtest/gtest.h>
#include "../include/map.hpp"
#include <list>
#include <map>

/*
 * [ google test v1.8.1 in use for compatibility reasons ]
 *
 * Usefull links :
 * Reference Testing	: https://google.github.io/googletest/reference/testing.html
 * Reference Assertions : https://google.github.io/googletest/reference/assertions.html
 */

namespace {

	TEST(MapBasicTest, DefaultConstructor)
	{
		ft::map< std::string, int > myMap;
		std::map< std::string, int > stdMap;

		EXPECT_TRUE((myMap.empty() == true) == (stdMap.empty() == true));
		EXPECT_EQ(myMap.size(), stdMap.size());
		EXPECT_TRUE(myMap.get_allocator() == stdMap.get_allocator());
		EXPECT_EQ(myMap.count(""), stdMap.count(""));
	}

	TEST(MapBasicTest, DISABLED_SegfaultTest)
	{
		ft::map< std::string, int > myMap;
		EXPECT_EXIT({
			 std::cout << (*myMap.find("")).first;
		 }, testing::KilledBySignal(SIGSEGV), ".*");
	}

	TEST(MapBasicTest, InsertMethod1)
	{
		ft::map< int, int > myMap;
		std::map< int, int > stdMap;
		myMap.insert(std::make_pair(42, 42));
		stdMap.insert(std::make_pair(42, 42));

		myMap.insert(std::make_pair(42, 42));
		stdMap.insert(std::make_pair(42, 42));

		myMap.insert(std::make_pair(43, 43));
		stdMap.insert(std::make_pair(43, 43));

		myMap.insert(std::make_pair(44, 44));
		stdMap.insert(std::make_pair(44, 44));

		EXPECT_TRUE(myMap.get_allocator() == stdMap.get_allocator());
		EXPECT_TRUE(myMap.empty() == stdMap.empty());
		EXPECT_EQ(myMap.size(), stdMap.size());
		EXPECT_EQ(myMap.max_size(), stdMap.max_size());
		for (int i = 42; i < 45; ++i)
		{
			EXPECT_EQ(myMap.count(i), stdMap.count(i));
			EXPECT_EQ(*myMap.find(i), *stdMap.find(i));
		}
		EXPECT_EQ(*(--myMap.find(404)), *(--stdMap.find(404)));
		EXPECT_EQ(myMap.count(404), stdMap.count(404));

		EXPECT_EQ(*myMap.begin(), *stdMap.begin());
		EXPECT_EQ(*(--myMap.end()), *(--stdMap.end()));
		EXPECT_EQ(*myMap.rbegin(), *stdMap.rbegin());
		EXPECT_EQ(*(--(myMap.rend())), *(--stdMap.rend()));
		EXPECT_TRUE((myMap == myMap) ==  (stdMap == stdMap));
		EXPECT_TRUE((myMap != myMap) ==  (stdMap != stdMap));
		EXPECT_TRUE((myMap < myMap) ==  (stdMap < stdMap));
		EXPECT_TRUE((myMap <= myMap) ==  (stdMap <= stdMap));
		EXPECT_TRUE((myMap > myMap) ==  (stdMap > stdMap));
		EXPECT_TRUE((myMap >= myMap) ==  (stdMap >= stdMap));
	}

	TEST(MapBasicTest, Comparators)
	{
		ft::map< int, int > m0;
		ft::map< int, int > m1;

		EXPECT_TRUE(m0 == m1);
		EXPECT_FALSE(m0 != m1);
		EXPECT_FALSE(m0 < m1);
		EXPECT_FALSE(m0 > m1);
		EXPECT_TRUE(m0 >= m1);
		EXPECT_TRUE(m0 <= m1);

		m0.insert(std::make_pair(0, 42));

		EXPECT_FALSE(m0 == m1);
		EXPECT_TRUE(m0 != m1);
		EXPECT_FALSE(m0 < m1);
		EXPECT_TRUE(m0 > m1);
		EXPECT_TRUE(m0 >= m1);
		EXPECT_FALSE(m0 <= m1);

		EXPECT_FALSE(m1 == m0);
		EXPECT_TRUE(m1 != m0);
		EXPECT_TRUE(m1 < m0);
		EXPECT_FALSE(m1 > m0);
		EXPECT_FALSE(m1 >= m0);
		EXPECT_TRUE(m1 <= m0);


		m1.insert(std::make_pair(0, 42));

		EXPECT_TRUE(m0 == m1);
		EXPECT_FALSE(m0 != m1);
		EXPECT_FALSE(m0 < m1);
		EXPECT_FALSE(m0 > m1);
		EXPECT_TRUE(m0 >= m1);
		EXPECT_TRUE(m0 <= m1);

		m0.insert(std::make_pair(1, 43));
		m1.insert(std::make_pair(1, 42));

		EXPECT_FALSE(m0 == m1);
		EXPECT_TRUE(m0 != m1);
		EXPECT_FALSE(m0 < m1);
		EXPECT_TRUE(m0 > m1);
		EXPECT_TRUE(m0 >= m1);
		EXPECT_FALSE(m0 <= m1);

		ft::map< int, int > m2;
		ft::map< int, int > m3;

		m2.insert(std::make_pair(2, 42));
		m3.insert(std::make_pair(2, 43));

		EXPECT_FALSE(m2 == m3);
		EXPECT_TRUE(m2 != m3);
		EXPECT_TRUE(m2 < m3);
		EXPECT_FALSE(m2 > m3);
		EXPECT_FALSE(m2 >= m3);
		EXPECT_TRUE(m2 <= m3);
	}


	TEST(MapBasicTest, Iterators)
	{

		ft::map< int, int > myMap;
		std::map< int, int > stdMap;

		for (int i = 0; i < 5; ++i)
		{
			myMap.insert(std::make_pair(i, 42));
			stdMap.insert(std::make_pair(i, 42));
		}

		ft::map< int, int >::iterator myIt(myMap.begin());
		std::map< int, int >::iterator stdIt(stdMap.begin());


		EXPECT_EQ(*myMap.begin(), *stdMap.begin());

		myIt = myMap.end();
		stdIt = stdMap.end();


		for (int i = 5; i < 10; ++i)
		{
			myMap.insert(std::make_pair(i, 43));
			stdMap.insert(std::make_pair(i, 43));
		}
		EXPECT_EQ(*(--myIt), *(--stdIt));

		ft::map< int, int >::iterator myIt2(--myMap.end());
		std::map< int, int >::iterator stdIt2(--stdMap.end());

		EXPECT_EQ(*myIt, *stdIt);
		EXPECT_EQ(*myIt2, *stdIt2);
	}

	// Example module 97 key compare function
	struct ModCmp {
		bool operator()(const int lhs, const int rhs) const
		{
			return (lhs % 97) < (rhs % 97);
		}
	};

	TEST(MapBasicTest, valueComp)
	{
		ft::map<int, char, ModCmp> cont;

		cont.insert(std::make_pair(1, 'a'));
		cont.insert(std::make_pair(2, 'b'));
		cont.insert(std::make_pair(3, 'c'));
		cont.insert(std::make_pair(4, 'd'));
		cont.insert(std::make_pair(5, 'e'));

		ft::map< int, char, ModCmp >::value_compare comp_val = cont.value_comp();
		ft::map< int, char, ModCmp >::key_compare comp_key = cont.key_comp();

		const std::pair<int, char> val = std::make_pair(100, 'a');

		ft::map< int, char, ModCmp >::iterator it = cont.begin();
		EXPECT_TRUE(comp_key(it->first, 100));
		EXPECT_TRUE(comp_val(*it++, val));

		EXPECT_TRUE(comp_key(it->first, 100));
		EXPECT_TRUE(comp_val(*it++, val));

		EXPECT_FALSE(comp_key(it->first, 100));
		EXPECT_FALSE(comp_val(*it++, val));

		EXPECT_FALSE(comp_key(it->first, 100));
		EXPECT_FALSE(comp_val(*it++, val));

		EXPECT_FALSE(comp_key(it->first, 100));
		EXPECT_FALSE(comp_val(*it, val));
	}
}  // namespace
