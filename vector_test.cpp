/* 
 * Usefull links :
 * Reference Testing	: https://google.github.io/googletest/reference/testing.html
 * Reference Assertions : https://google.github.io/googletest/reference/assertions.html
 */

/*	
 *	Test-driven development cycle
 *	
 *
 * 1.	Add a test
 *
 * 		The adding of a new feature begins by writing a test that passes if the feature's specifications are met.
 * 		The developer can discover these specifications by asking about use cases and user stories.
 * 		A key benefit of test-driven development is that it makes the developer focus on requirements before writing code.
 * 		This is in contrast with the usual practice, where unit tests are only written after code.
 *
 *
 * 2.	Run all tests.
 *
 * 		The new test should fail for expected reasons
 * 		This shows that new code is actually needed for the desired feature.
 * 		It validates that the test harness is working correctly.
 * 		It rules out the possibility that the new test is flawed and will always pass.
 *
 *
 * 3.	Write the simplest code that passes the new test
 *
 *		Inelegant or hard code is acceptable, as long as it passes the test.
 *		The code will be honed anyway in Step 5.
 *		No code should be added beyond the tested functionality.
 *
 *
 * 4.	All tests should now pass
 *
 *		If any fail, the new code must be revised until they pass.
 *		This ensures the new code meets the test requirements and does not break existing features.
 *
 *
 * 5.	Refactor as needed, using tests after each refactor to ensure that functionality is preserved
 *
 *		Code is refactored for readability and maintainability.
 *		In particular, hard-coded test data should be removed.
 *		Running the test suite after each refactor helps ensure that no existing functionality is broken.
 *
 *
 * 6.	Repeat
 *
 *		The cycle above is repeated for each new piece of functionality.
 *		Tests should be small and incremental, and commits made often.
 *		That way, if new code fails some tests, the programmer can simply undo or revert rather than debug excessively.
 */

/*
 * TODO_LIST
 *
 * Constructors
 *
 * 	1)	vector();
 * 	2)	vector( const vector& other );
 * 	3)	explicit vector( const Allocator& alloc );
 * 	4)	explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
 * 	5)	template< class InputIt > vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
 *
 * Destructors
 *
 */

#include <gtest/gtest.h>
#include <ft/vector.hpp>

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
	
	TEST(VectorBasicTest, IsExisting)
	{
		// First I check if I can instanciate the vector template
		// Before going any futher, this line should pass the test lifecycle:
		ft::vector<int> myIntVector;
		(void) myIntVector;
	}


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

	class VectorTest : public testing::Test
	{
		protected:
			void SetUp() override
			{
				// Call to the default constructor.
				v1_.push_back(42);

				v2.push_back(1);
				v2.push_back(2);
				v2.push_back(3);
				v2.push_back(4);
			}

			// Declares the variables the test want to use.
			ft::vector<int> v0_;
			ft::vector<int> v1_;
			ft::vector<int> v2_;
	};

	TEST_F(VectorTest, DefaultConstructor)
	{
		// We want to test the default constructor
		EXPECT_EQ(v0_.size(), (size_t)0);
		EXPECT_EQ(v1_.size(), (size_t)1);
		EXPECT_EQ(v2_.size(), (size_t)4);

	}

	TEST_F(VectorTest, TestingModifiers)
	{
		v0_.pop_back();
		v1_.pop_back();
		v2_.pop_back();

		EXPECT_EQ(v0_.size(), (size_t)0);
		EXPECT_EQ(v1_.size(), (size_t)0);
		EXPECT_EQ(v2_.size(), (size_t)3);
	}
}  // namespace
