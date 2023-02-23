#include <algorithm>
#include <gtest/gtest-typed-test.h>
#include <gtest/gtest.h>
#include <vector.hpp>
#include <list>

/*
 * [ google test v1.8.1 in use for compatibility reasons ]
 *
 * Usefull links :
 * Reference Testing	: https://google.github.io/googletest/reference/testing.html
 * Reference Assertions : https://google.github.io/googletest/reference/assertions.html
 */

namespace {

	TEST(VectorBasicTest, DefaultConstructor)
	{
		ft::vector< int > myVec;
		std::vector< int > stdVec;

		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
	}

	TEST(VectorBasicTest, Comparators)
	{
		ft::vector< int > v0;
		ft::vector< int > v1;

		EXPECT_TRUE(v0 == v1);
		EXPECT_FALSE(v0 != v1);
		EXPECT_FALSE(v0 < v1);
		EXPECT_FALSE(v0 > v1);
		EXPECT_TRUE(v0 >= v1);
		EXPECT_TRUE(v0 <= v1);

		v0.push_back(42);

		EXPECT_FALSE(v0 == v1);
		EXPECT_TRUE(v0 != v1);
		EXPECT_FALSE(v0 < v1);
		EXPECT_TRUE(v0 > v1);
		EXPECT_TRUE(v0 >= v1);
		EXPECT_FALSE(v0 <= v1);

		EXPECT_FALSE(v1 == v0);
		EXPECT_TRUE(v1 != v0);
		EXPECT_TRUE(v1 < v0);
		EXPECT_FALSE(v1 > v0);
		EXPECT_FALSE(v1 >= v0);
		EXPECT_TRUE(v1 <= v0);


		v1.push_back(42);

		EXPECT_TRUE(v0 == v1);
		EXPECT_FALSE(v0 != v1);
		EXPECT_FALSE(v0 < v1);
		EXPECT_FALSE(v0 > v1);
		EXPECT_TRUE(v0 >= v1);
		EXPECT_TRUE(v0 <= v1);

		v0.push_back(43);
		v1.push_back(42);

		EXPECT_FALSE(v0 == v1);
		EXPECT_TRUE(v0 != v1);
		EXPECT_FALSE(v0 < v1);
		EXPECT_TRUE(v0 > v1);
		EXPECT_TRUE(v0 >= v1);
		EXPECT_FALSE(v0 <= v1);

		ft::vector< int > v2;
		ft::vector< int > v3;

		v2.push_back(42);
		v3.push_back(43);

		EXPECT_FALSE(v2 == v3);
		EXPECT_TRUE(v2 != v3);
		EXPECT_TRUE(v2 < v3);
		EXPECT_FALSE(v2 > v3);
		EXPECT_FALSE(v2 >= v3);
		EXPECT_TRUE(v2 <= v3);
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

	TEST(VectorBasicTest, InsertMethod1)
	{
		ft::vector< int > myVec;
		myVec.push_back(1);
		myVec.push_back(2);
		myVec.push_back(3);

		std::vector< int > stdVec;
		stdVec.push_back(1);
		stdVec.push_back(2);
		stdVec.push_back(3);

		myVec.insert(myVec.begin() + 1, 42);
		stdVec.insert(stdVec.begin() + 1, 42);

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
//		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
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

		ft::vector< int > myVc = myVec;
		myVec.insert(myVec.begin() + 1, myVc.begin(), myVc.end());
		stdVec.insert(stdVec.begin() + 1, stdVec.begin(), stdVec.end());

		EXPECT_TRUE(myVec.get_allocator() == stdVec.get_allocator());
		EXPECT_TRUE(myVec.empty() == stdVec.empty());
		EXPECT_EQ(myVec.size(), stdVec.size());
		EXPECT_EQ(myVec.max_size(), stdVec.max_size());
//		EXPECT_EQ(myVec.capacity(), stdVec.capacity());
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

	TEST(VectorBasicTest, LegacyRandomAccessIterator)
	{
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
		/* LegacyIterator */

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

	}

//////////////////DEFAULT TYPES TESTS////////////////////////////
	const static int lenv2 = 7;

	template <typename Type>
	class VectorTest : public testing::Test
	{
		protected:
			// Default constructor initialize the class's reference
			VectorTest()
			{
				return ;
			}

			void SetUp()
			{
				v1_.push_back(42);
				for (Type i = 1; i <= lenv2; i++)
					v2_.push_back(i);
			}

			void TearDown()
			{
			}

			typedef ft::vector< Type >					Vector;

			std::vector< Type >	witnessEmptyVect;

			// Declares the variables the test want to use.
			Vector	v0_;
			Vector	v1_;
			Vector	v2_;
	};

#ifdef INT_ONLY
	typedef testing::Types< int > MyTypes;
#else
	typedef testing::Types< int, float, double, char, wchar_t> MyTypes;
#endif
	TYPED_TEST_CASE(VectorTest, MyTypes);

	TYPED_TEST(VectorTest, NonMemberSwap)
	{
		ft::vector< TypeParam > tmp1(this->v1_);
		ft::vector< TypeParam > tmp2(this->v2_);

		ft::swap(this->v1_, this->v2_);

		EXPECT_TRUE(this->v1_ == tmp2);
		EXPECT_TRUE(this->v2_ == tmp1);
	}

	TYPED_TEST(VectorTest, NonMemberFunction)
	{
		ft::vector< TypeParam > bob;
		ft::vector< TypeParam > alice;

		bob.push_back(1);

		EXPECT_TRUE(alice < bob);
		EXPECT_FALSE(bob < alice);

		EXPECT_FALSE(alice > bob);
		EXPECT_TRUE(bob > alice);

		EXPECT_FALSE(alice >= bob);
		EXPECT_TRUE(bob >= alice);

		EXPECT_TRUE(alice <= bob);
		EXPECT_FALSE(bob <= alice);

		EXPECT_FALSE(alice == bob);
		EXPECT_FALSE(bob == alice);

		EXPECT_TRUE(alice != bob);
		EXPECT_TRUE(bob != alice);

		alice.push_back(0);

		EXPECT_TRUE(alice < bob);
		EXPECT_FALSE(bob < alice);

		EXPECT_FALSE(alice > bob);
		EXPECT_TRUE(bob > alice);

		EXPECT_FALSE(alice >= bob);
		EXPECT_TRUE(bob >= alice);

		EXPECT_TRUE(alice <= bob);
		EXPECT_FALSE(bob <= alice);

		EXPECT_FALSE(alice == bob);
		EXPECT_FALSE(bob == alice);

		EXPECT_TRUE(alice != bob);
		EXPECT_TRUE(bob != alice);

		alice[0] = 1;
		bob[0] = 1;

		EXPECT_FALSE(alice < bob);
		EXPECT_FALSE(bob < alice);

		EXPECT_FALSE(alice > bob);
		EXPECT_FALSE(bob > alice);

		EXPECT_TRUE(alice >= bob);
		EXPECT_TRUE(bob >= alice);

		EXPECT_TRUE(alice <= bob);
		EXPECT_TRUE(bob <= alice);

		EXPECT_TRUE(alice == bob);
		EXPECT_TRUE(bob == alice);

		EXPECT_FALSE(alice != bob);
		EXPECT_FALSE(bob != alice);
	}

	TYPED_TEST(VectorTest, InsertTest1)
	{
		ft::vector< TypeParam > vect;
		for (TypeParam i = 0; i < 7; ++i)
			vect.push_back(i + 1);
		vect.insert(vect.begin() + 3, this->v2_.begin(), this->v2_.begin() + 2);
		typename ft::vector< TypeParam >::iterator begin = vect.begin();
		EXPECT_EQ(vect.size(), (size_t)9);

		EXPECT_EQ(begin[0], 1);
		EXPECT_EQ(begin[1], 2);
		EXPECT_EQ(begin[2], 3);
		EXPECT_EQ(begin[3], 1);
		EXPECT_EQ(begin[4], 2);
		EXPECT_EQ(begin[5], 4);
		EXPECT_EQ(begin[6], 5);
		EXPECT_EQ(begin[7], 6);
		EXPECT_EQ(begin[8], 7);
	}

	TYPED_TEST(VectorTest, InsertTest0)
	{
		typename ft::vector< TypeParam >::iterator it( this->v2_.insert(this->v2_.begin(), 42) );
		EXPECT_EQ(*this->v2_.begin(), 42);
		EXPECT_EQ(*it, 42);
		EXPECT_EQ(this->v2_.size(), (size_t)8);
		EXPECT_EQ(this->v2_.capacity(), (size_t)8);

		it = this->v1_.insert(this->v1_.end(), 43);
		EXPECT_EQ(*(this->v1_.end() - 1), 43);
		EXPECT_EQ(*it, 43);
		EXPECT_EQ(this->v1_.size(), (size_t)2);

		this->v0_.insert(this->v0_.begin(), size_t(0), 42);
		EXPECT_EQ(this->v0_.size(), (size_t)0);
		EXPECT_EQ(this->v0_.capacity(), (size_t)0);

		this->v0_.insert(this->v0_.begin(), size_t(42), 1);
		for (typename ft::vector < TypeParam >::iterator i = this->v0_.begin(); i != this->v0_.end(); ++i)
			EXPECT_EQ(*i, 1);
		EXPECT_EQ(this->v0_.capacity(), (size_t)42);

		this->v0_.insert(this->v0_.end(), size_t(1), 42);
		EXPECT_EQ(*(this->v0_.end() - 1), 42);
		EXPECT_EQ(this->v0_.size(), (size_t)43);
		EXPECT_EQ(this->v0_.capacity(), (size_t)43);
	}

	TYPED_TEST(VectorTest, ReverseIteratorTest)
	{
		ft::reverse_iterator< typename ft::vector< TypeParam >::iterator >	rev_it_0(this->v2_.begin() + 1);
		ft::reverse_iterator< typename ft::vector< TypeParam >::iterator >	rev_it_1(rev_it_0);
		rev_it_0 = rev_it_1;
		EXPECT_TRUE(*rev_it_0 == *this->v2_.begin());
		EXPECT_TRUE(*rev_it_0 == *this->v2_.begin());
		rev_it_1 = ft::reverse_iterator< typename ft::vector< TypeParam >::iterator > (this->v2_.end());
		EXPECT_EQ(rev_it_0[-1], 2);
		EXPECT_EQ(rev_it_1[0], 7);
		EXPECT_TRUE(rev_it_0 != rev_it_1);
		EXPECT_FALSE(rev_it_0 == rev_it_1);
		EXPECT_FALSE(rev_it_0 <= rev_it_1);
		EXPECT_TRUE(rev_it_0 >= rev_it_1);
		EXPECT_FALSE(rev_it_0 < rev_it_1);
		EXPECT_TRUE(rev_it_0 > rev_it_1);

		rev_it_0 = rev_it_1;
		EXPECT_FALSE(rev_it_0 != rev_it_1);
		EXPECT_TRUE(rev_it_0 == rev_it_1);
		EXPECT_TRUE(rev_it_0 <= rev_it_1);
		EXPECT_TRUE(rev_it_0 >= rev_it_1);
		EXPECT_FALSE(rev_it_0 < rev_it_1);
		EXPECT_FALSE(rev_it_0 > rev_it_1);

		rev_it_1 += 2;
		EXPECT_EQ(rev_it_1[0], 5);
		rev_it_1 -= 1;
		EXPECT_EQ(rev_it_1[0], 6);
		EXPECT_EQ((--rev_it_1)[0], 7);
		EXPECT_EQ((++rev_it_1)[0], 6);
		EXPECT_EQ((rev_it_1++)[0], 6);
		EXPECT_EQ((rev_it_1--)[0], 5);
		EXPECT_EQ(rev_it_1[0], 6);
		EXPECT_EQ(*(rev_it_1 + 1), 5);
		EXPECT_EQ(*(1 + rev_it_1), 5);
		EXPECT_EQ(*(rev_it_1 - 1), 7);
	}

	TYPED_TEST(VectorTest, TestSwap)
	{
		ft::vector< TypeParam >	tmp1(this->v1_);
		ft::vector< TypeParam >	tmp2(this->v2_);

		this->v2_.swap(this->v1_);

		EXPECT_TRUE(tmp1.size() == this->v2_.size());
		EXPECT_TRUE(tmp1.capacity() == this->v2_.size());
		EXPECT_TRUE(tmp1.get_allocator() == this->v2_.get_allocator());

		typename ft::vector< TypeParam >::iterator it_tmp1(tmp1.begin());
		typename ft::vector< TypeParam >::iterator it_v2(this->v2_.begin());

		while (it_tmp1 != tmp1.end() && it_v2 != this->v2_.end())
		{
			EXPECT_TRUE(*it_tmp1 == *it_v2);
			++it_tmp1;
			++it_v2;
		}

		typename ft::vector< TypeParam >::iterator it_tmp2(tmp2.begin());
		typename ft::vector< TypeParam >::iterator it_v1(this->v1_.begin());

		while (it_tmp2 != tmp2.end() && it_v1 != this->v1_.end())
		{
			EXPECT_TRUE(*it_tmp2 == *it_v1);
			++it_tmp2;
			++it_v1;
		}

		EXPECT_TRUE(tmp2.size() == this->v1_.size());
		EXPECT_TRUE(tmp2.capacity() == this->v1_.size());
		EXPECT_TRUE(tmp2.get_allocator() == this->v1_.get_allocator());
	}

	TYPED_TEST(VectorTest, TestResize)
	{
	}

	TYPED_TEST(VectorTest, TestErase)
	{
		ft::vector< std::string > vec(10);
		for (unsigned long int i = 0; i < vec.size(); ++i)
				vec[i] = std::string((vec.size() - i), i + 65);

		std::vector< std::string > stdVec(10);
		for (unsigned long int i = 0; i < stdVec.size(); ++i)
				stdVec[i] = std::string((stdVec.size() - i), i + 65);

		EXPECT_EQ(stdVec.size(), vec.size());

		ft::vector< std::string >::iterator it(vec.erase(vec.begin() + 2));
		std::vector< std::string >::iterator stdIt(stdVec.erase(stdVec.begin() + 2));

		EXPECT_STREQ(it->c_str(), stdIt->c_str());
	}

	TYPED_TEST(VectorTest, TestEraseFirstLast)
	{
		typename ft::vector< TypeParam >::iterator ite(this->v2_.erase(this->v2_.begin() + 1, this->v2_.end()));
		EXPECT_EQ(ite[-1], 1);
		EXPECT_EQ(ite[0], 2);
		EXPECT_EQ(this->v2_.size(), (size_t)1);
		EXPECT_TRUE(ite == this->v2_.end());
		ite  = this->v2_.erase(this->v2_.end(), this->v2_.end());
		EXPECT_EQ(ite[-1], 1);
		EXPECT_EQ(ite[0], 2);
		EXPECT_EQ(this->v2_.size(), (size_t)1);
		EXPECT_TRUE(ite == this->v2_.end());
	}

	TYPED_TEST(VectorTest,TestErasePos)
	{
		typename ft::vector< TypeParam >::iterator ite(this->v2_.erase(this->v2_.end() - 3));
		EXPECT_EQ(*ite, 6);
		EXPECT_EQ(this->v2_.size(), (size_t)6);
		ite = this->v2_.erase(this->v2_.end() - 1);
		EXPECT_TRUE(ite == this->v2_.end());
		EXPECT_EQ(this->v2_.size(), (size_t)5);
	}

	TYPED_TEST(VectorTest, TestClear)
	{
		std::size_t	oldCapacity = this->v2_.capacity();
		this->v2_.clear();	
		EXPECT_EQ(this->v2_.size(), (size_t)0);
		EXPECT_EQ(this->v2_.capacity(), oldCapacity);
		EXPECT_TRUE(this->v2_.begin() == this->v2_.end());
	}

	TYPED_TEST(VectorTest, TestIterators)
	{
		const	ft::vector< TypeParam > const_vect (this->v2_);

		// Non-const
		EXPECT_EQ(*this->v2_.begin(), 1);
		EXPECT_EQ(*(this->v2_.end() - 1), 7);
		EXPECT_EQ(*this->v2_.rbegin(), 7);
		EXPECT_EQ(*(this->v2_.rend() - 1), 1);

		// Const
		EXPECT_EQ(*const_vect.begin(), 1);
		EXPECT_EQ(*(const_vect.end() - 1), 7);
		EXPECT_EQ(*const_vect.rbegin(), 7);
		EXPECT_EQ(*(const_vect.rend() - 1), 1);
	}

	TYPED_TEST(VectorTest, TestCountConstructor)
	{
		// One param
		ft::vector< TypeParam > myVect0(size_t(0));
		EXPECT_EQ(myVect0.size(), size_t(0));
		EXPECT_EQ(myVect0.capacity(), size_t(0));
		ft::vector< TypeParam > myVect1(size_t(42));
		EXPECT_EQ(myVect1.size(), size_t(42));
		EXPECT_EQ(myVect1.capacity(), size_t(42));

		// Two param
		ft::vector< TypeParam > myVect2(size_t(3), 42);
		for (size_t i = 0; i < 3; i++)
			EXPECT_EQ(myVect2[i], 42);
		EXPECT_EQ(myVect2.size(), size_t(3));
		EXPECT_EQ(myVect2.capacity(), size_t(3));

		// Three param
		ft::vector< TypeParam > myVect3(size_t(32), 42, myVect2.get_allocator());
		EXPECT_EQ(myVect3.size(), size_t(32));
		EXPECT_EQ(myVect3.capacity(), size_t(32));
	}

	TYPED_TEST(VectorTest, TestCopyConstructor_IsExisting)
	{
		{
			ft::vector< TypeParam > myVect(this->v0_);

			EXPECT_EQ(this->v0_.capacity(), myVect.capacity());
			EXPECT_EQ(this->v0_.size(), myVect.size());
			EXPECT_EQ(this->v0_.max_size(), myVect.max_size());
			EXPECT_EQ(this->v0_.empty(), myVect.empty());
			EXPECT_EQ(this->v0_.get_allocator() == myVect.get_allocator(), true);
			EXPECT_EQ(this->v0_.data(), myVect.data());
		}

		{
			ft::vector< TypeParam > myVect(this->v1_);

			EXPECT_EQ(this->v1_.capacity(), myVect.capacity());
			EXPECT_EQ(this->v1_.size(), myVect.size());
			EXPECT_EQ(this->v1_.max_size(), myVect.max_size());
			EXPECT_EQ(this->v1_.empty(), myVect.empty());
			EXPECT_EQ(this->v1_.get_allocator() == myVect.get_allocator(), true);
			EXPECT_NE(this->v1_.data(), myVect.data());

			size_t size = this->v1_.size();
			for (size_t i = 0; i < size; i++)
			{
				EXPECT_EQ(myVect[i], this->v1_[i]);
			}
		}

		{
			ft::vector< TypeParam > myVect(this->v2_);

			EXPECT_EQ(this->v2_.size(), myVect.capacity());
			EXPECT_EQ(this->v2_.size(), myVect.size());
			EXPECT_EQ(this->v2_.max_size(), myVect.max_size());
			EXPECT_EQ(this->v2_.empty(), myVect.empty());
			EXPECT_EQ(this->v2_.get_allocator() == myVect.get_allocator(), true);
			EXPECT_NE(this->v2_.data(), myVect.data());

			size_t size = this->v2_.size();
			for (size_t i = 0; i < size; i++)
			{
				EXPECT_EQ(myVect[i], this->v2_[i]);
			}
		}
	}

	TYPED_TEST(VectorTest, TestReserve_IsExisting)
	{
		size_t max_elements = 32;
		this->v0_.reserve(max_elements);
	}

	TYPED_TEST(VectorTest, TestReserve_CapacityUpdates)
	{
		this->v0_.reserve(0);
		EXPECT_EQ(this->v0_.capacity(), size_t(0));

		this->v0_.reserve(32);
		EXPECT_EQ(this->v0_.capacity(), size_t(32));

		this->v0_.reserve(44);
		EXPECT_EQ(this->v0_.capacity(), size_t(44));

		this->v0_.reserve(0);
		EXPECT_EQ(this->v0_.capacity(), size_t(44));

		this->v2_.reserve(100);

		EXPECT_EQ(this->v2_.capacity(), size_t(100));
		EXPECT_EQ(this->v2_.size(), (size_t)lenv2);
		for (TypeParam i = 0; i < lenv2; i++)
			EXPECT_EQ(this->v2_[i], i + 1);
	}

	TYPED_TEST(VectorTest, TestReserve_Allocation)
	{
	}

	TYPED_TEST(VectorTest, TestMaxSize)
	{
		this->v0_.max_size();
		EXPECT_EQ(this->v0_.max_size(), size_t(this->witnessEmptyVect.max_size()));
		EXPECT_EQ(this->v1_.max_size(), size_t(this->witnessEmptyVect.max_size()));
		EXPECT_EQ(this->v2_.max_size(), size_t(this->witnessEmptyVect.max_size()));
	}

	TYPED_TEST(VectorTest, TestEmpty)
	{
		EXPECT_EQ(this->v0_.empty(), true);
		EXPECT_EQ(this->v1_.empty(), false);
		EXPECT_EQ(this->v2_.empty(), false);
	}

	TYPED_TEST(VectorTest, TestBack)
	{
		EXPECT_EQ(this->v2_.back(), (7));
		this->v2_.pop_back();
		this->v2_.pop_back();
		EXPECT_EQ(this->v2_.back(), (5));
	}

	TYPED_TEST(VectorTest, TestData)
	{
		TypeParam	*dataV0 = this->v0_.data();
		EXPECT_EQ(dataV0, (TypeParam *)NULL);

		TypeParam	*dataV1 = this->v1_.data();
		EXPECT_EQ(dataV1, &this->v1_[0]);
		this->v1_.pop_back();
		EXPECT_EQ(dataV1, &this->v1_[0]);
	}

	TYPED_TEST(VectorTest, TestAt)
	{
		EXPECT_EQ(this->v1_.at(0), 42);
		for (TypeParam i = 0; i < lenv2; i++)
			EXPECT_EQ(this->v2_.at(i), i + 1);
	}
	TYPED_TEST(VectorTest, TestCapacity)
	{
		EXPECT_EQ(this->v0_.capacity(), size_t(0));
		for (int i = 0; i < 8; i++)
			this->v0_.push_back(42);
		for (int i = 0; i < 10; i++)
			this->v0_.pop_back();
		EXPECT_EQ(this->v0_.capacity(), size_t(8));
	}

	TYPED_TEST(VectorTest, 3TestOperatorEQ)
	{
		this->v0_ = this->v0_; // Make sure not to modify anything if you are calling operator= on itself with (this == &rhs)
	}

	TYPED_TEST(VectorTest, TestDefaultConstructor)
	{
		EXPECT_EQ(this->v0_.size(), size_t(0));
		EXPECT_EQ(this->v0_.capacity(), size_t(0));

		// Testing to remove elements on an empty vector:
		this->v0_.pop_back();
		this->v0_.pop_back();
		this->v0_.pop_back();

		EXPECT_EQ(this->v0_.size(), size_t(0));
		EXPECT_EQ(this->v0_.capacity(), size_t(0));
	}

	TYPED_TEST(VectorTest, TestCapacitySize)
	{
		EXPECT_EQ(this->v0_.size(), size_t(0));
		EXPECT_EQ(this->v1_.size(), size_t(1));
		EXPECT_EQ(this->v2_.size(), size_t(7));
	}

	TYPED_TEST(VectorTest, TestModifierPopBack)
	{
		this->v0_.pop_back();
		this->v1_.pop_back();
		this->v2_.pop_back();

		EXPECT_EQ(this->v0_.size(), size_t(0));
		EXPECT_EQ(this->v1_.size(), size_t(0));
		EXPECT_EQ(this->v2_.size(), size_t(6));
	}
	
	TYPED_TEST(VectorTest, TestOperatorElementAccess)
	{
		//v1
		EXPECT_EQ(this->v1_[0], 42);

		//v2
		for (int i = 0; i < lenv2; i++)
			EXPECT_EQ(this->v2_[i], i + 1);
	}

	TYPED_TEST(VectorTest, TestGetAllocator)
	{
		// 0)
		std::allocator< TypeParam > alloc = this->v1_.get_allocator();
		// 1)
		TypeParam *tab = alloc.allocate(10);
		for (int i = 0; i < 10; i++)
			alloc.construct(tab + i, i);
		for (int i = 0; i < 10; i++)
			alloc.destroy(tab + i);
		alloc.deallocate(tab, 10);
	}

//////////////////OBJECTS TESTS////////////////////////////

	TYPED_TEST(VectorTest, DISABLED_TestSIGNAL)
	{
		// Calling front on empty vector is undefined.
		// Those tests takes some time so we regroup them in the same test.
		
		// Some const vector definition
		const ft::vector< TypeParam > myConstVect;

		// Calling front
		EXPECT_EXIT({
				TypeParam front = this->v0_.front();
				(void)front;
			}, testing::KilledBySignal(SIGSEGV), ".*");

		// Calling const front
		EXPECT_EXIT({
				const TypeParam ref = myConstVect.front();
				(void)ref;
			}, testing::KilledBySignal(SIGSEGV), ".*");

		// Calling data
		EXPECT_EXIT({
				TypeParam *ptr = this->v0_.data();
				TypeParam value = *ptr;
				(void)value;
			}, testing::KilledBySignal(SIGSEGV), ".*");

		// Calling const data
		EXPECT_EXIT({
				const TypeParam *const_ptr = myConstVect.data();
				TypeParam value = *const_ptr;
				(void)value;
			}, testing::KilledBySignal(SIGSEGV), ".*");

		// Calling back
		EXPECT_EXIT({
				TypeParam &reflast = this->v0_.back();
				TypeParam value = reflast;
				(void)value;
			}, testing::KilledBySignal(SIGSEGV), ".*");


		// Calling const back
		EXPECT_EXIT({
				const TypeParam &const_ref = myConstVect.back();
				TypeParam value = const_ref;
				(void)value;
			}, testing::KilledBySignal(SIGSEGV), ".*");


		// Calling at
		EXPECT_THROW({
			try
			{
				this->v0_.at(0);
			}
			catch (const std::exception &e)
			{
				EXPECT_STREQ("vector::_M_range_check: __n (which is 0) >= this->size() (which is 0)", e.what());
				throw;
			}
		}, std::out_of_range);

		// Calling const at
		EXPECT_THROW({
			try
			{
				myConstVect.at(0);
			}
			catch (const std::exception &e)
			{
				EXPECT_STREQ("vector::_M_range_check: __n (which is 0) >= this->size() (which is 0)", e.what());
				throw;
			}
		}, std::out_of_range);
		
		{
			// Some const vector definition
			ft::vector< TypeParam > myLocalVect;

			// Calling reserve with new_cap > max_size
			EXPECT_THROW({

				try
				{
					myLocalVect.reserve(-1);
				}
				catch (const std::exception &e)
				{
					EXPECT_STREQ("vector::reserve", e.what());
					throw;
				}
			}, std::length_error);

			// Calling CountConstructor with invalid param
			EXPECT_THROW({

				try
				{
					ft::vector< TypeParam > myVect(size_t(-1));
				}
				catch (const std::exception &e)
				{
					EXPECT_STREQ("cannot create std::vector larger than max_size()", e.what());
					throw;
				}
			}, std::length_error);
			// Calling resize with new_size > max_size
			EXPECT_THROW({
				try
				{
					myLocalVect.resize(-1);
				}
				catch (const std::exception &e)
				{
					EXPECT_STREQ("vector::resize", e.what());
					throw;
				}
			}, std::length_error);


		}
	}

	TYPED_TEST(VectorTest, TestFront)
	{
		//v0
		this->v0_.push_back(55);
		EXPECT_EQ(this->v0_.front(), 55);

		//v1
		EXPECT_EQ(this->v1_.front(), 42);
		this->v1_.push_back(32);
		EXPECT_EQ(this->v1_.front(), 42);

		//v2
		EXPECT_EQ(this->v2_.front(), 1);
		// overload
		this->v2_.pop_back();
		this->v2_.pop_back();
		this->v2_.pop_back();
		this->v2_.pop_back();
		this->v2_.pop_back();
		this->v2_.pop_back();
		this->v2_.pop_back();
		//std::cout << "\033[1;33m~🌈 FINAL 🌻$\033[0m v2_[0] = " << this->v2_[0] << std::endl;
		EXPECT_EQ(this->v2_.front(), 1);
	}

	template<typename Type>
	class VectorTestString: public testing::Test
	{
		protected:
			void SetUp()
			{
				// Default capacity is 1
				this->v5_.push_back("First sentence.");
				this->v5_.push_back("An other sentence.");
				// Now it should resize the capacity to 4
				this->v5_.push_back("And a third one.");

			}

			void TearDown()
			{
			}

			// Basic Vector object to test
			typedef ft::vector<Type> Vector;

			Vector v4_;
			Vector v5_;
	};

	typedef testing::Types< std::string > StringTypes;
	TYPED_TEST_CASE(VectorTestString, StringTypes);

//	TYPED_TEST(VectorTestString, TestReverIterator)
//	{
//		ft::reverse_iterator< typename ft::vector< TypeParam >::iterator >	rev_it_0(this->v5_.begin() + 1);
//		EXPECT_TRUE(rev_it_0->c_str() == (this->v5_.begin())->c_str());
//	}

	TYPED_TEST(VectorTestString, TestStringDefaultConstructor)
	{
		EXPECT_EQ(this->v4_.size(), size_t(0));
		// Test segfault here :
		//EXPECT_EQ(this->v4_[0], (char)0);

		// Testing to remove elements on an empty vector:
		this->v4_.pop_back();
		this->v4_.pop_back();
		this->v4_.pop_back();
	}

	TYPED_TEST(VectorTestString, TestStringSize)
	{
		EXPECT_EQ(this->v5_.size(), size_t(3));
		this->v5_.push_back("Toto is now inside vector");
		EXPECT_EQ(this->v5_.size(), size_t(4));
		this->v5_.pop_back();
		this->v5_.pop_back();
		EXPECT_EQ(this->v5_.size(), size_t(2));
	}

	TYPED_TEST(VectorTestString, TestStringPushBack)
	{
		EXPECT_STREQ(this->v5_[0].c_str(), "First sentence.");
		EXPECT_STREQ(this->v5_[1].c_str(), "An other sentence.");
		EXPECT_STREQ(this->v5_[2].c_str(), "And a third one.");
		this->v5_.push_back("Toto is now inside vector");
		EXPECT_STREQ(this->v5_[3].c_str(), "Toto is now inside vector");
		this->v5_[0] = "Assignment operator= of std::string is now tested";
		EXPECT_STREQ(this->v5_[0].c_str(), "Assignment operator= of std::string is now tested");
		// This Test should fail since we can not instantiate an std::string with a NULL pointer.
	    //this->v5_.push_back(NULL);
	}

}  // namespace
