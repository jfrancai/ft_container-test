#include <iostream>
#include <ft/stack.hpp>
#include <gtest/gtest.h>
#include <stack>
#include <list>

namespace {

	TEST(StackTest, DefaultConstructor)
	{
		ft::stack< int > s;
		EXPECT_TRUE(s.empty());
		EXPECT_EQ(s.size(), 0);
	}

	TEST(StackTest, ContainerConstructor)
	{
		ft::vector< int > v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		ft::stack< int, ft::vector< int > > s(v);
		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 3);
		EXPECT_EQ(s.top(), 3);

		std::list< int > l;
		l.push_back(4);
		l.push_back(5);
		l.push_back(6);
		ft::stack< int, std::list< int > > s2(l);
		EXPECT_FALSE(s2.empty());
		EXPECT_EQ(s2.size(), 3);
		EXPECT_EQ(s2.top(), 6);
	}

	TEST(StackTest, TopMethod)
	{
		ft::stack< int > s;
		s.push(1);
		s.push(2);
		s.push(3);
		EXPECT_EQ(s.top(), 3);
		s.top() = 4;
		EXPECT_EQ(s.top(), 4);
		const ft::stack< int > &cs = s;
		EXPECT_EQ(cs.top(), 4);
	}

	TEST(StackTest, PushMethod)
	{
		ft::stack< int > s;
		EXPECT_EQ(s.size(), 0);
		s.push(1);
		EXPECT_EQ(s.size(), 1);
		EXPECT_EQ(s.top(), 1);
		s.push(2);
		EXPECT_EQ(s.size(), 2);
		EXPECT_EQ(s.top(), 2);
		s.push(3);
		EXPECT_EQ(s.size(), 3);
		EXPECT_EQ(s.top(), 3);
	}

	TEST(StackTest, PopMethod)
	{
		ft::stack< int > s;
		s.push(1);
		s.push(2);
		s.push(3);
		EXPECT_EQ(s.size(), 3);
		EXPECT_EQ(s.top(), 3);
		s.pop();
		EXPECT_EQ(s.size(), 2);
		EXPECT_EQ(s.top(), 2);
		s.pop();
		EXPECT_EQ(s.size(), 1);
		EXPECT_EQ(s.top(), 1);
		s.pop();
		EXPECT_TRUE(s.empty());
		EXPECT_EQ(s.size(), 0);
	}

	TEST(StackTest, AssignmentOperator)
	{
		ft::stack< int > s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);

		ft::stack< int > s2;

		s2 = s1;
		EXPECT_EQ(s2.size(), 3);
		EXPECT_EQ(s2.top(), 3);

		s1.pop();
		EXPECT_EQ(s1.size(), 2);
		EXPECT_EQ(s1.top(), 2);
		EXPECT_EQ(s2.size(), 3);
		EXPECT_EQ(s2.top(), 3);
	}

	TEST(StackTest, EqualityOperator)
	{
		ft::stack< int > s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);

		ft::stack< int > s2;
		s2.push(1);
		s2.push(2);
		s2.push(3);

		ft::stack< int > s3;
		s3.push(1);
		s3.push(2);
		s3.push(4);

		ft::stack< int > s4;
		s4.push(1);
		s4.push(2);

		EXPECT_TRUE(s1 == s2);
		EXPECT_FALSE(s1 == s3);
		EXPECT_FALSE(s1 == s4);
		EXPECT_FALSE(s2 == s3);
		EXPECT_FALSE(s2 == s4);
		EXPECT_FALSE(s3 == s4);
	}

	TEST(StackTest, InEqualityOperator)
	{
		ft::stack< int > s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);

		ft::stack< int > s2;
		s2.push(1);
		s2.push(2);
		s2.push(3);

		ft::stack< int > s3;
		s3.push(1);
		s3.push(2);
		s3.push(4);

		ft::stack< int > s4;
		s4.push(1);
		s4.push(2);

		EXPECT_FALSE(s1 != s2);
		EXPECT_TRUE(s1 != s3);
		EXPECT_TRUE(s1 != s4);
		EXPECT_TRUE(s2 != s3);
		EXPECT_TRUE(s2 != s4);
		EXPECT_TRUE(s3 != s4);
	}

	TEST(StackTest, LessThanOperator)
	{
		ft::stack< int > s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);

		ft::stack< int > s2;
		s2.push(1);
		s2.push(2);
		s2.push(3);

		ft::stack< int > s3;
		s3.push(1);
		s3.push(2);
		s3.push(4);

		ft::stack< int > s4;
		s4.push(1);
		s4.push(2);
		s4.push(2);

		ft::stack< int > s5;
		s5.push(1);
		s5.push(2);

		EXPECT_FALSE(s1 < s2);
		EXPECT_FALSE(s2 < s1);
		EXPECT_TRUE(s1 < s3);
		EXPECT_FALSE(s2 < s4);
		EXPECT_FALSE(s1 < s4);
		EXPECT_FALSE(s1 < s5);
	}

	TEST(StackTest, LessThanEqualOperator)
	{
		ft::stack< int > s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);

		ft::stack< int > s2;
		s2.push(1);
		s2.push(2);
		s2.push(3);

		ft::stack< int > s3;
		s3.push(1);
		s3.push(2);
		s3.push(4);

		ft::stack< int > s4;
		s4.push(1);
		s4.push(2);
		s4.push(2);

		ft::stack< int > s5;
		s5.push(1);
		s5.push(2);

		EXPECT_TRUE(s1 <= s2);
		EXPECT_TRUE(s2 <= s1);
		EXPECT_TRUE(s1 <= s3);
		EXPECT_FALSE(s1 <= s4);
		EXPECT_FALSE(s1 <= s5);
	}

	TEST(StackTest, GreaterThanOperator)
	{
		ft::stack< int > s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);

		ft::stack< int > s2;
		s2.push(1);
		s2.push(2);
		s2.push(3);

		ft::stack< int > s3;
		s3.push(1);
		s3.push(2);
		s3.push(4);

		ft::stack< int > s4;
		s4.push(1);
		s4.push(2);
		s4.push(2);

		ft::stack< int > s5;
		s5.push(1);
		s5.push(2);

		EXPECT_FALSE(s1 > s2);
		EXPECT_FALSE(s2 > s1);
		EXPECT_FALSE(s1 > s3);
		EXPECT_TRUE(s1 > s4);
		EXPECT_TRUE(s1 > s5);
	}

	TEST(StackTest, GreaterThanEqualOperator)
	{
		ft::stack< int > s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);

		ft::stack< int > s2;
		s2.push(1);
		s2.push(2);
		s2.push(3);

		ft::stack< int > s3;
		s3.push(1);
		s3.push(2);
		s3.push(4);

		ft::stack< int > s4;
		s4.push(1);
		s4.push(2);
		s4.push(2);

		ft::stack< int > s5;
		s5.push(1);
		s5.push(2);

		EXPECT_TRUE(s1 >= s2);
		EXPECT_TRUE(s2 >= s1);
		EXPECT_FALSE(s1 >= s3);
		EXPECT_TRUE(s1 >= s4);
		EXPECT_TRUE(s1 >= s5);
	}
} // namespace
