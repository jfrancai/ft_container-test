#include <gtest/gtest.h>
//#include <vector>

/*
 *
 * Usefull links :
 * Reference Testing	: https://google.github.io/googletest/reference/testing.html
 * Reference Assertions : https://google.github.io/googletest/reference/assertions.html
 *
 */

namespace {

	//		To create a test:
	//
	// 1)	Use the TEST() macro to define and name a test function.
	//		These are ordinary C++ functions that don’t return a value.
	//
	// 2)	In this function, along with any valid C++ statements you want to include,
	// 		use the various googletest assertions to check values.
	//
	// 3)	The test’s result is determined by the assertions;
	//		if any assertion in the test fails (either fatally or non-fatally), 
	//		or if the test crashes, the entire test fails. Otherwise, it succeeds.

	//		To create a fixture:
	//
	// 1)	Derive a class from ::testing::Test.
	// 		Start its body with protected:,
	// 		as we’ll want to access fixture members from sub-classes.
	//
	// 2)	Inside the class, declare any objects you plan to use.
	//
	// 3)	If necessary, write a default constructor or SetUp() function to prepare the objects for each test.
	// 		A common mistake is to spell SetUp() as Setup() with a small u.
	// 		Use override in C++11 to make sure you spelled it correctly.
	//
	// 4)	If necessary, write a destructor or TearDown() function to release any resources you allocated in SetUp().
	// 		To learn when you should use the constructor/destructor and when you should use SetUp()/TearDown(), read the FAQ.
	//
	// 5)	If needed, define subroutines for your tests to share.
	

	// This test the Constructeur and Destructeur, belong to OnOffTest test case
	TEST(OnOffTest, Constructeur)
	{
		std::string v1 = "Constructeur called";
		std::string v2 = "The output of the Constructeur";
		EXPECT_EQ(v1, v2);
	}
	
	// To test the Destructeur message -> v2 = output of the Destructeur message when it's done
	TEST(OnOffTest, Destructeur)
	{
		std::string v1 = "Destructeur called";
		std::string v2 = "The output of the Destructeur";
		EXPECT_EQ(v1, v2);
	}

	TEST(Capacity, size)
	{
		std::string str = "Hello coucou tout le monde";
		size_t v1 = str.size();
		size_t v2 = 15;
		// v2 = size of str caculated by ft_vector
		EXPECT_EQ(v1, v2);
	}


}  // namespace
