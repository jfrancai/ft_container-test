#include <iostream>
#include <type_traits.hpp>
#include <gtest/gtest.h>

namespace {

	TEST(IsIntegralTest, BasicTypes)
	{
		bool val = ft::is_integral<char>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<signed char>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<unsigned char>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<short>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<unsigned short>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<int>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<unsigned int>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<long>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<unsigned long>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<long long>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<unsigned long long>::value;
		EXPECT_TRUE(val);
		val = ft::is_integral<bool>::value;
		EXPECT_TRUE(val);
	}

	TEST(IsIntegralTest, NonIntegralTypes)
	{
		EXPECT_FALSE(ft::is_integral<float>::value);
		EXPECT_FALSE(ft::is_integral<double>::value);
		EXPECT_FALSE(ft::is_integral<long double>::value);
		EXPECT_FALSE(ft::is_integral<void>::value);
		EXPECT_FALSE(ft::is_integral<std::string>::value);
		EXPECT_FALSE(ft::is_integral<std::vector<int>::iterator>::value);
	}

} // namespace
