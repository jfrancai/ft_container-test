#include <algorithm>
#include <gtest/gtest.h>
#include <map.hpp>
#include <list>

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

		EXPECT_TRUE(myMap.empty() == stdMap.empty());
		EXPECT_EQ(myMap.size(), stdMap.size());
		EXPECT_TRUE(myMap.get_allocator() == stdMap.get_allocator());
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

		EXPECT_TRUE(myMap.get_allocator() == stdMap.get_allocator());
		EXPECT_TRUE(myMap.empty() == stdMap.empty());
		EXPECT_EQ(myMap.size(), stdMap.size());
		//EXPECT_EQ(myMap.max_size(), stdMap.max_size());
		EXPECT_EQ(*myMap.begin(), *stdMap.begin());
		EXPECT_EQ(*(myMap.end() - 1), *(stdMap.end() - 1));
		/*
		EXPECT_EQ(*myMap.rbegin(), *stdMap.rbegin());
		EXPECT_EQ(*(myMap.rend() - 1), *(stdMap.rend() - 1));
		EXPECT_TRUE((myMap == myMap) ==  (stdMap == stdMap));
		EXPECT_TRUE((myMap != myMap) ==  (stdMap != stdMap));
		EXPECT_TRUE((myMap < myMap) ==  (stdMap < stdMap));
		EXPECT_TRUE((myMap <= myMap) ==  (stdMap <= stdMap));
		EXPECT_TRUE((myMap > myMap) ==  (stdMap > stdMap));
		EXPECT_TRUE((myMap >= myMap) ==  (stdMap >= stdMap));

		for (ft::vector< int >::size_type i = 0; i < myMap.size(); ++i)
		{
			EXPECT_EQ(myMap[i], stdMap[i]);
			EXPECT_EQ(myMap.at(i), stdMap.at(i));
		}
		*/
	}

	TEST(VectorBasicTest, LegacyRandomAccessIterator)
	{
		/*
		ft::vector< std::string > fruits;

		fruits.push_back("orange");
		fruits.push_back("banane");
		fruits.push_back("pineapple");
		fruits.push_back("mango");
		fruits.push_back("cherry");
		fruits.push_back("apple");

		// Default construct
		ft::vector< std::string >::iterator it0;

		// Copy assignable
		it0 = fruits.begin();
		EXPECT_STREQ((*it0).c_str(), "orange");

		// Copy construct
		ft::vector< std::string >::iterator it1(it0);
		EXPECT_STREQ((*it1).c_str(), "orange");

		// Equality comparable
		EXPECT_TRUE(it0 == it1);
		// Inequality comparable
		EXPECT_FALSE(it0 != it1);

		// Pre-increment
		++it1;
		EXPECT_STREQ((*it1).c_str(), "banane");

		EXPECT_FALSE(it0 == it1);
		EXPECT_TRUE(it0 != it1);

		// Swappable
		ft::swap(it0, it1);

		EXPECT_STREQ((*it1).c_str(), "orange");
		EXPECT_STREQ((*it0).c_str(), "banane");

		// operator->
		EXPECT_STREQ(it1->c_str(), "orange");
		EXPECT_STREQ(it0->c_str(), "banane");

		// Post-inc
		EXPECT_STREQ((it1++)->c_str(), "orange");
		EXPECT_STREQ(it1->c_str(), "banane");
		it0 = fruits.begin();
		EXPECT_STREQ((*it0++).c_str(), "orange");

		it0 = fruits.begin();
		ft::vector< std::string >::iterator it0copy(it0);
		it0copy++;
		EXPECT_STREQ(it0->c_str(), "orange");
		EXPECT_STREQ(it0copy->c_str(), "banane");

		it0copy = it0;
		EXPECT_TRUE(++it0 == ++it0copy);
		EXPECT_STREQ(it0copy->c_str(), "banane");
		EXPECT_STREQ(it0->c_str(), "banane");

		// Pre-inc
		EXPECT_STREQ((--it1)->c_str(), "orange");
		++it1;
		EXPECT_STREQ((it1--)->c_str(), "banane");
		EXPECT_STREQ(it1->c_str(), "orange");

		// operator>
		EXPECT_TRUE(++it1 > --it0);

		// operator<
		EXPECT_FALSE(it1 < it0);

		// operator<=
		EXPECT_TRUE(--it0copy <= it0);

		// operator>=
		EXPECT_TRUE(it0copy >= it0);

		// operator+=
		it0 += 3;
		EXPECT_STREQ(it0->c_str(), "mango");

		// operator+
		EXPECT_STREQ((it0 + 2)->c_str(), "apple");
		EXPECT_STREQ((2 + it0)->c_str(), "apple");

		// operator-=
		it0 -= 1;
		EXPECT_STREQ(it0->c_str(), "pineapple");
		it0 -= -1;
		EXPECT_STREQ(it0->c_str(), "mango");

		// operator-
		EXPECT_STREQ((it0 - 1)->c_str(), "pineapple");
		EXPECT_STREQ((it0 - -1)->c_str(), "cherry");
		EXPECT_EQ((it0 + 5) - it0, std::ptrdiff_t(5));

		//operator[]
		EXPECT_STREQ(it0[1].c_str(), "cherry");
		EXPECT_STREQ(it0[-1].c_str(), "pineapple");

		// Default construct
		ft::vector< std::string >::iterator it2;

		// Copy assignable
		it2 = fruits.begin();
		EXPECT_STREQ((*it2).c_str(), "orange");

		// Copy construct
		ft::vector< std::string >::iterator it3(it2);
		EXPECT_STREQ((*it3).c_str(), "orange");

		// Equality comparable
		EXPECT_TRUE(it2 == it3);
		// Inequality comparable
		EXPECT_FALSE(it2 != it3);

		// Pre-increment
		++it3;
		EXPECT_STREQ((*it3).c_str(), "banane");

		EXPECT_FALSE(it2 == it3);
		EXPECT_TRUE(it2 != it3);

		// Swappable
		ft::swap(it2, it3);

		EXPECT_STREQ((*it3).c_str(), "orange");
		EXPECT_STREQ((*it2).c_str(), "banane");

		// operator->
		EXPECT_STREQ(it3->c_str(), "orange");
		EXPECT_STREQ(it2->c_str(), "banane");

		// post-inc
		EXPECT_STREQ((it3++)->c_str(), "orange");
		EXPECT_STREQ(it3->c_str(), "banane");
		it2 = fruits.begin();
		EXPECT_STREQ((*it2++).c_str(), "orange");

		it2 = fruits.begin();
		ft::vector< std::string >::iterator it2copy(it2);
		it2copy++;
		EXPECT_STREQ(it2->c_str(), "orange");
		EXPECT_STREQ(it2copy->c_str(), "banane");

		it2copy = it2;
		EXPECT_TRUE(++it2 == ++it2copy);
		EXPECT_STREQ(it2copy->c_str(), "banane");
		EXPECT_STREQ(it2->c_str(), "banane");

		// pre-inc
		EXPECT_STREQ((--it3)->c_str(), "orange");
		++it3;
		EXPECT_STREQ((it3--)->c_str(), "banane");
		EXPECT_STREQ(it3->c_str(), "orange");

		EXPECT_TRUE(++it3 > --it2);
		EXPECT_FALSE(it3 < it2);
		EXPECT_TRUE(--it2copy <= it2);
		EXPECT_TRUE(it2copy >= it2);
		ft::vector<int> vect;
		vect.push_back(42);
		vect.push_back(43);

		ft::vector<int>::iterator ite(vect.begin());
		*ite = *(ite + 1);

		EXPECT_EQ(*ite, 43);
		*/
	}

	/*
	TEST(VectorBasicTest, ConstLegacyRandomAccessIterator)
	{
		ft::vector< std::string > fruits;

		fruits.push_back("orange");
		fruits.push_back("banane");
		fruits.push_back("pineapple");
		fruits.push_back("mango");
		fruits.push_back("cherry");
		fruits.push_back("apple");

		// Default construct
		ft::vector< std::string >::const_iterator it0(fruits.begin());
		EXPECT_STREQ((*it0).c_str(), "orange");

		// Copy construct
		ft::vector< std::string >::const_iterator it1(it0);
		EXPECT_STREQ((*it1).c_str(), "orange");

		// Equality comparable
		EXPECT_TRUE(it0 == it1);
		// Inequality comparable
		EXPECT_FALSE(it0 != it1);

		// Pre-increment
		++it1;
		EXPECT_STREQ((*it1).c_str(), "banane");

		EXPECT_FALSE(it0 == it1);
		EXPECT_TRUE(it0 != it1);

		// Swappable
		ft::swap(it0, it1);

		EXPECT_STREQ((*it1).c_str(), "orange");
		EXPECT_STREQ((*it0).c_str(), "banane");

		// operator->
		EXPECT_STREQ(it1->c_str(), "orange");
		EXPECT_STREQ(it0->c_str(), "banane");

		// Post-inc
		EXPECT_STREQ((it1++)->c_str(), "orange");
		EXPECT_STREQ(it1->c_str(), "banane");
		it0 = fruits.begin();
		EXPECT_STREQ((*it0++).c_str(), "orange");

		it0 = fruits.begin();
		ft::vector< std::string >::const_iterator it0copy(it0);
		it0copy++;
		EXPECT_STREQ(it0->c_str(), "orange");
		EXPECT_STREQ(it0copy->c_str(), "banane");

		it0copy = it0;
		EXPECT_TRUE(++it0 == ++it0copy);
		EXPECT_STREQ(it0copy->c_str(), "banane");
		EXPECT_STREQ(it0->c_str(), "banane");

		// Pre-inc
		EXPECT_STREQ((--it1)->c_str(), "orange");
		++it1;
		EXPECT_STREQ((it1--)->c_str(), "banane");
		EXPECT_STREQ(it1->c_str(), "orange");

		// operator>
		EXPECT_TRUE(++it1 > --it0);

		// operator<
		EXPECT_FALSE(it1 < it0);

		// operator<=
		EXPECT_TRUE(--it0copy <= it0);

		// operator>=
		EXPECT_TRUE(it0copy >= it0);

		// operator+=
		it0 += 3;
		EXPECT_STREQ(it0->c_str(), "mango");

		// operator+
		EXPECT_STREQ((it0 + 2)->c_str(), "apple");
		EXPECT_STREQ((2 + it0)->c_str(), "apple");

		// operator-=
		it0 -= 1;
		EXPECT_STREQ(it0->c_str(), "pineapple");
		it0 -= -1;
		EXPECT_STREQ(it0->c_str(), "mango");

		// operator-
		EXPECT_STREQ((it0 - 1)->c_str(), "pineapple");
		EXPECT_STREQ((it0 - -1)->c_str(), "cherry");
		EXPECT_EQ((it0 + 5) - it0, std::ptrdiff_t(5));

		//operator[]
		EXPECT_STREQ(it0[1].c_str(), "cherry");
		EXPECT_STREQ(it0[-1].c_str(), "pineapple");

		ft::vector<int> vect;
		vect.push_back(42);
		vect.push_back(43);

		ft::vector<int>::iterator ite(vect.begin());
		*ite = *(ite + 1);

		EXPECT_EQ(*ite, 43);
	}


	TEST(VectorBasicTest, CountConstructor)
	{
		ft::vector< int > myVec(42);

		std::vector< int > stdVec(42);

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_EQ(myVec.front(), stdVec.front());
		EXPECT_EQ(myVec.back(), stdVec.back());
		EXPECT_EQ(*myVec.begin(), *stdVec.begin());
		EXPECT_EQ(*(myVec.end() - 1), *(stdVec.end() - 1));
		EXPECT_EQ(*myVec.rbegin(), *stdVec.rbegin());
		EXPECT_EQ(*(myVec.rend() - 1), *(stdVec.rend() - 1));
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVec[i], stdVec[i]);
			EXPECT_EQ(myVec.at(i), stdVec.at(i));
		}
	}

	TEST(VectorBasicTest, CopyConstructor)
	{
		ft::vector< int > myVec;
		myVec.push_back(1);
		myVec.push_back(2);
		myVec.push_back(3);

		std::vector< int > stdVec;
		stdVec.push_back(1);
		stdVec.push_back(2);
		stdVec.push_back(3);

		ft::vector< int > myVecCopy(myVec);

		std::vector< int > stdVecCopy(stdVec);

		EXPECT_TRUE(myVecCopy.get_allocator() == stdVecCopy.get_allocator());
		EXPECT_TRUE(myVecCopy.empty() == stdVecCopy.empty());
		EXPECT_EQ(myVecCopy.size(), stdVecCopy.size());
		EXPECT_EQ(myVecCopy.max_size(), stdVecCopy.max_size());
		EXPECT_EQ(myVecCopy.capacity(), stdVecCopy.capacity());
		EXPECT_EQ(myVecCopy.front(), stdVecCopy.front());
		EXPECT_EQ(myVecCopy.back(), stdVecCopy.back());
		EXPECT_EQ(*myVecCopy.begin(), *stdVecCopy.begin());
		EXPECT_EQ(*(myVecCopy.end() - 1), *(stdVecCopy.end() - 1));
		EXPECT_EQ(*myVecCopy.rbegin(), *stdVecCopy.rbegin());
		EXPECT_EQ(*(myVecCopy.rend() - 1), *(stdVecCopy.rend() - 1));
		EXPECT_TRUE((myVec == myVecCopy) ==  (stdVec == stdVecCopy));
		EXPECT_TRUE((myVec != myVecCopy) ==  (stdVec != stdVecCopy));
		EXPECT_TRUE((myVec < myVecCopy) ==  (stdVec < stdVecCopy));
		EXPECT_TRUE((myVec <= myVecCopy) ==  (stdVec <= stdVecCopy));
		EXPECT_TRUE((myVec > myVecCopy) ==  (stdVec > stdVecCopy));
		EXPECT_TRUE((myVec >= myVecCopy) ==  (stdVec >= stdVecCopy));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVecCopy[i], stdVecCopy[i]);
			EXPECT_EQ(myVecCopy.at(i), stdVecCopy.at(i));
		}
	}

	TEST(VectorBasicTest, IteratorConstructor)
	{
		ft::vector< int > vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);

		ft::vector< int > myVec(vec.begin(), vec.end());
		std::vector< int > stdVec(vec.begin(), vec.end());

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_EQ(myVec.front(), stdVec.front());
		EXPECT_EQ(myVec.back(), stdVec.back());
		EXPECT_EQ(*myVec.begin(), *stdVec.begin());
		EXPECT_EQ(*(myVec.end() - 1), *(stdVec.end() - 1));
		EXPECT_EQ(*myVec.rbegin(), *stdVec.rbegin());
		EXPECT_EQ(*(myVec.rend() - 1), *(stdVec.rend() - 1));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVec[i], stdVec[i]);
			EXPECT_EQ(myVec.at(i), stdVec.at(i));
		}
	}

	TEST(VectorBasicTest, AssignMethod1)
	{
		{
			ft::vector< int > myVec;
			myVec.push_back(1);
			myVec.push_back(2);
			myVec.push_back(3);

			std::vector< int > stdVec;
			stdVec.push_back(1);
			stdVec.push_back(2);
			stdVec.push_back(3);

			ft::vector< int > myVecCopy;
			std::vector< int > stdVecCopy;

			myVecCopy.assign(0, 42);
			stdVecCopy.assign(0, 42);

			EXPECT_TRUE(myVecCopy.get_allocator() == stdVecCopy.get_allocator());
			EXPECT_TRUE(myVecCopy.empty() == stdVecCopy.empty());
			EXPECT_EQ(myVecCopy.size(), stdVecCopy.size());
			EXPECT_EQ(myVecCopy.max_size(), stdVecCopy.max_size());
			EXPECT_EQ(myVecCopy.capacity(), stdVecCopy.capacity());
			EXPECT_TRUE((myVec == myVecCopy) ==  (stdVec == stdVecCopy));
			EXPECT_TRUE((myVec != myVecCopy) ==  (stdVec != stdVecCopy));
			EXPECT_TRUE((myVec < myVecCopy) ==  (stdVec < stdVecCopy));
			EXPECT_TRUE((myVec <= myVecCopy) ==  (stdVec <= stdVecCopy));
			EXPECT_TRUE((myVec > myVecCopy) ==  (stdVec > stdVecCopy));
			EXPECT_TRUE((myVec >= myVecCopy) ==  (stdVec >= stdVecCopy));
		}

		{
			ft::vector< int > myVec;
			myVec.push_back(1);
			myVec.push_back(2);
			myVec.push_back(3);

			std::vector< int > stdVec;
			stdVec.push_back(1);
			stdVec.push_back(2);
			stdVec.push_back(3);

			ft::vector< int > myVecCopy;
			std::vector< int > stdVecCopy;

			myVecCopy.assign(10, 42);
			stdVecCopy.assign(10, 42);

			EXPECT_TRUE(myVecCopy.get_allocator() == stdVecCopy.get_allocator());
			EXPECT_TRUE(myVecCopy.empty() == stdVecCopy.empty());
			EXPECT_EQ(myVecCopy.size(), stdVecCopy.size());
			EXPECT_EQ(myVecCopy.max_size(), stdVecCopy.max_size());
			EXPECT_EQ(myVecCopy.capacity(), stdVecCopy.capacity());
			EXPECT_EQ(myVecCopy.front(), stdVecCopy.front());
			EXPECT_EQ(myVecCopy.back(), stdVecCopy.back());
			EXPECT_EQ(*myVecCopy.begin(), *stdVecCopy.begin());
			EXPECT_EQ(*(myVecCopy.end() - 1), *(stdVecCopy.end() - 1));
			EXPECT_EQ(*myVecCopy.rbegin(), *stdVecCopy.rbegin());
			EXPECT_EQ(*(myVecCopy.rend() - 1), *(stdVecCopy.rend() - 1));
			EXPECT_TRUE((myVec == myVecCopy) ==  (stdVec == stdVecCopy));
			EXPECT_TRUE((myVec != myVecCopy) ==  (stdVec != stdVecCopy));
			EXPECT_TRUE((myVec < myVecCopy) ==  (stdVec < stdVecCopy));
			EXPECT_TRUE((myVec <= myVecCopy) ==  (stdVec <= stdVecCopy));
			EXPECT_TRUE((myVec > myVecCopy) ==  (stdVec > stdVecCopy));
			EXPECT_TRUE((myVec >= myVecCopy) ==  (stdVec >= stdVecCopy));

			for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
			{
				EXPECT_EQ(myVecCopy[i], stdVecCopy[i]);
				EXPECT_EQ(myVecCopy.at(i), stdVecCopy.at(i));
			}
		}

		{
			ft::vector< int > myVec;
			myVec.push_back(1);
			myVec.push_back(2);
			myVec.push_back(3);

			std::vector< int > stdVec;
			stdVec.push_back(1);
			stdVec.push_back(2);
			stdVec.push_back(3);

			ft::vector< int > myVecCopy;
			std::vector< int > stdVecCopy;

			myVecCopy.assign(10, 42);
			stdVecCopy.assign(10, 42);

			EXPECT_TRUE(myVecCopy.get_allocator() == stdVecCopy.get_allocator());
			EXPECT_TRUE(myVecCopy.empty() == stdVecCopy.empty());
			EXPECT_EQ(myVecCopy.size(), stdVecCopy.size());
			EXPECT_EQ(myVecCopy.max_size(), stdVecCopy.max_size());
			EXPECT_EQ(myVecCopy.capacity(), stdVecCopy.capacity());
			EXPECT_EQ(myVecCopy.front(), stdVecCopy.front());
			EXPECT_EQ(myVecCopy.back(), stdVecCopy.back());
			EXPECT_EQ(*myVecCopy.begin(), *stdVecCopy.begin());
			EXPECT_EQ(*(myVecCopy.end() - 1), *(stdVecCopy.end() - 1));
			EXPECT_EQ(*myVecCopy.rbegin(), *stdVecCopy.rbegin());
			EXPECT_EQ(*(myVecCopy.rend() - 1), *(stdVecCopy.rend() - 1));
			EXPECT_TRUE((myVec == myVecCopy) ==  (stdVec == stdVecCopy));
			EXPECT_TRUE((myVec != myVecCopy) ==  (stdVec != stdVecCopy));
			EXPECT_TRUE((myVec < myVecCopy) ==  (stdVec < stdVecCopy));
			EXPECT_TRUE((myVec <= myVecCopy) ==  (stdVec <= stdVecCopy));
			EXPECT_TRUE((myVec > myVecCopy) ==  (stdVec > stdVecCopy));
			EXPECT_TRUE((myVec >= myVecCopy) ==  (stdVec >= stdVecCopy));

			for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
			{
				EXPECT_EQ(myVecCopy[i], stdVecCopy[i]);
				EXPECT_EQ(myVecCopy.at(i), stdVecCopy.at(i));
			}
		}
	}

	TEST(VectorBasicTest, AssignMethod2)
	{
		{
			ft::vector< int > myVec;
			myVec.push_back(1);
			myVec.push_back(2);
			myVec.push_back(3);

			std::vector< int > stdVec;
			stdVec.push_back(1);
			stdVec.push_back(2);
			stdVec.push_back(3);

			ft::vector< int > myVecCopy;
			std::vector< int > stdVecCopy;

			myVecCopy.assign(myVec.begin(), myVec.begin());
			stdVecCopy.assign(stdVec.begin(), stdVec.begin());

			EXPECT_TRUE(myVecCopy.get_allocator() == stdVecCopy.get_allocator());
			EXPECT_TRUE(myVecCopy.empty() == stdVecCopy.empty());
			EXPECT_EQ(myVecCopy.size(), stdVecCopy.size());
			EXPECT_EQ(myVecCopy.max_size(), stdVecCopy.max_size());
			EXPECT_EQ(myVecCopy.capacity(), stdVecCopy.capacity());
			EXPECT_TRUE((myVec == myVecCopy) ==  (stdVec == stdVecCopy));
			EXPECT_TRUE((myVec != myVecCopy) ==  (stdVec != stdVecCopy));
			EXPECT_TRUE((myVec < myVecCopy) ==  (stdVec < stdVecCopy));
			EXPECT_TRUE((myVec <= myVecCopy) ==  (stdVec <= stdVecCopy));
			EXPECT_TRUE((myVec > myVecCopy) ==  (stdVec > stdVecCopy));
			EXPECT_TRUE((myVec >= myVecCopy) ==  (stdVec >= stdVecCopy));
		}

		{
			ft::vector< int > myVec;
			myVec.push_back(1);
			myVec.push_back(2);
			myVec.push_back(3);

			std::vector< int > stdVec;
			stdVec.push_back(1);
			stdVec.push_back(2);
			stdVec.push_back(3);

			ft::vector< int > myVecCopy;
			std::vector< int > stdVecCopy;

			myVecCopy.assign(myVec.begin(), myVec.end());
			stdVecCopy.assign(stdVec.begin(), stdVec.end());

			EXPECT_TRUE(myVecCopy.get_allocator() == stdVecCopy.get_allocator());
			EXPECT_TRUE(myVecCopy.empty() == stdVecCopy.empty());
			EXPECT_EQ(myVecCopy.size(), stdVecCopy.size());
			EXPECT_EQ(myVecCopy.max_size(), stdVecCopy.max_size());
			EXPECT_EQ(myVecCopy.capacity(), stdVecCopy.capacity());
			EXPECT_EQ(myVecCopy.front(), stdVecCopy.front());
			EXPECT_EQ(myVecCopy.back(), stdVecCopy.back());
			EXPECT_EQ(*myVecCopy.begin(), *stdVecCopy.begin());
			EXPECT_EQ(*(myVecCopy.end() - 1), *(stdVecCopy.end() - 1));
			EXPECT_EQ(*myVecCopy.rbegin(), *stdVecCopy.rbegin());
			EXPECT_EQ(*(myVecCopy.rend() - 1), *(stdVecCopy.rend() - 1));
			EXPECT_TRUE((myVec == myVecCopy) ==  (stdVec == stdVecCopy));
			EXPECT_TRUE((myVec != myVecCopy) ==  (stdVec != stdVecCopy));
			EXPECT_TRUE((myVec < myVecCopy) ==  (stdVec < stdVecCopy));
			EXPECT_TRUE((myVec <= myVecCopy) ==  (stdVec <= stdVecCopy));
			EXPECT_TRUE((myVec > myVecCopy) ==  (stdVec > stdVecCopy));
			EXPECT_TRUE((myVec >= myVecCopy) ==  (stdVec >= stdVecCopy));

			for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
			{
				EXPECT_EQ(myVecCopy[i], stdVecCopy[i]);
				EXPECT_EQ(myVecCopy.at(i), stdVecCopy.at(i));
			}
		}
	}

	TEST(VectorBasicTest, AssignmentOperator)
	{
		ft::vector< int > myVec;
		myVec.push_back(1);
		myVec.push_back(2);
		myVec.push_back(3);

		std::vector< int > stdVec;
		stdVec.push_back(1);
		stdVec.push_back(2);
		stdVec.push_back(3);

		ft::vector< int > myVecCopy;

		std::vector< int > stdVecCopy;

		myVecCopy = myVec;
		stdVecCopy = stdVec;

		EXPECT_TRUE(myVecCopy.get_allocator() == stdVecCopy.get_allocator());
		EXPECT_TRUE(myVecCopy.empty() == stdVecCopy.empty());
		EXPECT_EQ(myVecCopy.size(), stdVecCopy.size());
		EXPECT_EQ(myVecCopy.max_size(), stdVecCopy.max_size());
		EXPECT_EQ(myVecCopy.capacity(), stdVecCopy.capacity());
		EXPECT_EQ(myVecCopy.front(), stdVecCopy.front());
		EXPECT_EQ(myVecCopy.back(), stdVecCopy.back());
		EXPECT_EQ(*myVecCopy.begin(), *stdVecCopy.begin());
		EXPECT_EQ(*(myVecCopy.end() - 1), *(stdVecCopy.end() - 1));
		EXPECT_EQ(*myVecCopy.rbegin(), *stdVecCopy.rbegin());
		EXPECT_EQ(*(myVecCopy.rend() - 1), *(stdVecCopy.rend() - 1));
		EXPECT_TRUE((myVec == myVecCopy) ==  (stdVec == stdVecCopy));
		EXPECT_TRUE((myVec != myVecCopy) ==  (stdVec != stdVecCopy));
		EXPECT_TRUE((myVec < myVecCopy) ==  (stdVec < stdVecCopy));
		EXPECT_TRUE((myVec <= myVecCopy) ==  (stdVec <= stdVecCopy));
		EXPECT_TRUE((myVec > myVecCopy) ==  (stdVec > stdVecCopy));
		EXPECT_TRUE((myVec >= myVecCopy) ==  (stdVec >= stdVecCopy));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVecCopy[i], stdVecCopy[i]);
			EXPECT_EQ(myVecCopy.at(i), stdVecCopy.at(i));
		}
	}
	
	TEST(VectorBasicTest, ReserveMethod)
	{
		ft::vector< int > myVec;
		std::vector< int > stdVec;

		myVec.reserve(10);
		stdVec.reserve(10);

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));


		for (int i = 0; i < 15; i++)
		{
			myVec.push_back(i);
			stdVec.push_back(i);
		}

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_EQ(myVec.front(), stdVec.front());
		EXPECT_EQ(myVec.back(), stdVec.back());
		EXPECT_EQ(*myVec.begin(), *stdVec.begin());
		EXPECT_EQ(*(myVec.end() - 1), *(stdVec.end() - 1));
		EXPECT_EQ(*myVec.rbegin(), *stdVec.rbegin());
		EXPECT_EQ(*(myVec.rend() - 1), *(stdVec.rend() - 1));
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVec[i], stdVec[i]);
			EXPECT_EQ(myVec.at(i), stdVec.at(i));
		}
	}

	TEST(VectorBasicTest, ClearMethod)
	{
		ft::vector< int > myVec;
		myVec.push_back(1);
		myVec.push_back(2);
		myVec.push_back(3);

		std::vector< int > stdVec;
		stdVec.push_back(1);
		stdVec.push_back(2);
		stdVec.push_back(3);

		myVec.clear();
		stdVec.clear();

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));
	}

	TEST(VectorBasicTest, InsertMethod2_0)
	{
		ft::vector< int > myVec;
		myVec.push_back(1);
		myVec.push_back(2);
		myVec.push_back(3);

		std::vector< int > stdVec;
		stdVec.push_back(1);
		stdVec.push_back(2);
		stdVec.push_back(3);

		myVec.insert(myVec.begin() + 1, 2, 10);
		stdVec.insert(stdVec.begin() + 1, 2, 10);

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_EQ(myVec.front(), stdVec.front());
		EXPECT_EQ(myVec.back(), stdVec.back());
		EXPECT_EQ(*myVec.begin(), *stdVec.begin());
		EXPECT_EQ(*(myVec.end() - 1), *(stdVec.end() - 1));
		EXPECT_EQ(*myVec.rbegin(), *stdVec.rbegin());
		EXPECT_EQ(*(myVec.rend() - 1), *(stdVec.rend() - 1));
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVec[i], stdVec[i]);
			EXPECT_EQ(myVec.at(i), stdVec.at(i));
		}
	}

	TEST(VectorBasicTest, InsertMethod3)
	{
		ft::vector< int > myVec;
		myVec.push_back(1);
		myVec.push_back(2);
		myVec.push_back(3);
		myVec.push_back(4);
		myVec.push_back(5);

		std::vector< int > stdVec;
		stdVec.push_back(1);
		stdVec.push_back(2);
		stdVec.push_back(3);
		stdVec.push_back(4);
		stdVec.push_back(5);

		myVec.insert(myVec.begin() + 1, myVec.begin(), myVec.end());
		stdVec.insert(stdVec.begin() + 1, stdVec.begin(), stdVec.end());

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_EQ(myVec.front(), stdVec.front());
		EXPECT_EQ(myVec.back(), stdVec.back());
		EXPECT_EQ(*myVec.begin(), *stdVec.begin());
		EXPECT_EQ(*(myVec.end() - 1), *(stdVec.end() - 1));
		EXPECT_EQ(*myVec.rbegin(), *stdVec.rbegin());
		EXPECT_EQ(*(myVec.rend() - 1), *(stdVec.rend() - 1));
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVec[i], stdVec[i]);
			EXPECT_EQ(myVec.at(i), stdVec.at(i));
		}
	}

	TEST(VectorBasicTest, PushBackMethod)
	{
		ft::vector< int > myVec;
		for (int i = 0; i < 42; ++i)
			myVec.push_back(i);

		std::vector< int > stdVec;
		for (int i = 0; i < 42; ++i)
			stdVec.push_back(i);

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_EQ(myVec.front(), stdVec.front());
		EXPECT_EQ(myVec.back(), stdVec.back());
		EXPECT_EQ(*myVec.begin(), *stdVec.begin());
		EXPECT_EQ(*(myVec.end() - 1), *(stdVec.end() - 1));
		EXPECT_EQ(*myVec.rbegin(), *stdVec.rbegin());
		EXPECT_EQ(*(myVec.rend() - 1), *(stdVec.rend() - 1));
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVec[i], stdVec[i]);
			EXPECT_EQ(myVec.at(i), stdVec.at(i));
		}
	}

	TEST(VectorBasicTest, PopBackMethod)
	{
		ft::vector< int > myVec;
		for (int i = 0; i < 42; ++i)
			myVec.push_back(i);

		std::vector< int > stdVec;
		for (int i = 0; i < 42; ++i)
			stdVec.push_back(i);

		for (int i = 0; i < 21; ++i)
			myVec.pop_back();

		for (int i = 0; i < 21; ++i)
			stdVec.pop_back();

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_EQ(myVec.front(), stdVec.front());
		EXPECT_EQ(myVec.back(), stdVec.back());
		EXPECT_EQ(*myVec.begin(), *stdVec.begin());
		EXPECT_EQ(*(myVec.end() - 1), *(stdVec.end() - 1));
		EXPECT_EQ(*myVec.rbegin(), *stdVec.rbegin());
		EXPECT_EQ(*(myVec.rend() - 1), *(stdVec.rend() - 1));
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVec[i], stdVec[i]);
			EXPECT_EQ(myVec.at(i), stdVec.at(i));
		}
	}

	TEST(VectorBasicTest, ResizeMethod)
	{
		ft::vector< int > myVec;

		std::vector< int > stdVec;

		myVec.resize(23, 42);
		stdVec.resize(23, 42);

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_EQ(myVec.front(), stdVec.front());
		EXPECT_EQ(myVec.back(), stdVec.back());
		EXPECT_EQ(*myVec.begin(), *stdVec.begin());
		EXPECT_EQ(*(myVec.end() - 1), *(stdVec.end() - 1));
		EXPECT_EQ(*myVec.rbegin(), *stdVec.rbegin());
		EXPECT_EQ(*(myVec.rend() - 1), *(stdVec.rend() - 1));
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVec[i], stdVec[i]);
			EXPECT_EQ(myVec.at(i), stdVec.at(i));
		}

		myVec.resize(1000);
		stdVec.resize(1000);

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_EQ(myVec.front(), stdVec.front());
		EXPECT_EQ(myVec.back(), stdVec.back());
		EXPECT_EQ(*myVec.begin(), *stdVec.begin());
		EXPECT_EQ(*(myVec.end() - 1), *(stdVec.end() - 1));
		EXPECT_EQ(*myVec.rbegin(), *stdVec.rbegin());
		EXPECT_EQ(*(myVec.rend() - 1), *(stdVec.rend() - 1));
		EXPECT_TRUE((myVec == myVec) ==  (stdVec == stdVec));
		EXPECT_TRUE((myVec != myVec) ==  (stdVec != stdVec));
		EXPECT_TRUE((myVec < myVec) ==  (stdVec < stdVec));
		EXPECT_TRUE((myVec <= myVec) ==  (stdVec <= stdVec));
		EXPECT_TRUE((myVec > myVec) ==  (stdVec > stdVec));
		EXPECT_TRUE((myVec >= myVec) ==  (stdVec >= stdVec));

		for (ft::vector< int >::size_type i = 0; i < myVec.size(); ++i)
		{
			EXPECT_EQ(myVec[i], stdVec[i]);
			EXPECT_EQ(myVec.at(i), stdVec.at(i));
		}
	}
	*/
}  // namespace
