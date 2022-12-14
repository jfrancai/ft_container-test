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


// Testing Library
#include <gtest/gtest.h>
// Mocking Library
#include "gmock/gmock.h"
// The tested Library
#include <ft/vector.hpp>

namespace {

	using testing::AtLeast;

	// Wrapping the std::allocator API into an interface
	// Not really an interface here but huh...
	template < class T >
	class IAllocator
	{
		public:
			typedef T				value_type;
			typedef T*				pointer;
			typedef const T*		const_pointer;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef std::size_t		size_type;
			typedef std::ptrdiff_t	difference_type;

			// Destructor has to be virtual
			virtual ~IAllocator() {}

			virtual	void	deallocate(pointer p, size_type n){return (this->_alloc.deallocate(p, n));}
			virtual pointer	allocate(size_type n) {return (this->_alloc.allocate(n));}
			virtual void	construct( pointer p, const_reference val ){return (this->_alloc.construct(p, val));}
			virtual void	destroy(pointer p){return (this->_alloc.destroy(p));}
		private:
			std::allocator< T >	_alloc;
	};

	// Mocking allocator interface into the MockAllocator class
	template< class Type >
	class MockAllocator : public IAllocator< Type >{
		public:
			/*
			 * Member Types
			 */
			typedef Type			value_type;
			typedef Type*			pointer;
			typedef const Type*		const_pointer;
			typedef Type&			reference;
			typedef const Type&		const_reference;
			typedef std::size_t		size_type;
			typedef std::ptrdiff_t	difference_type;

			/*
			 * Member functions
			 */

			// Mocks
			MOCK_METHOD1_T(destroy, void(pointer));
			MOCK_METHOD2_T(construct, void(pointer, const_reference));
			MOCK_METHOD0_T(construct, void(void));
			MOCK_METHOD1_T(allocate, pointer(size_type));
			MOCK_METHOD2_T(deallocate, void(pointer, size_type));
	};

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
		// Aliases
		typedef MockAllocator<int> MockAlloc;

		// Thanks to the mAlloc we are now able to see wich alloc function our vector container is using.
		// Expectng it to use some alloc function in certain condition.
#ifdef NICE
		typedef testing::NiceMock< MockAlloc > NiceMockAlloc;

		ft::vector< int, NiceMockAlloc > intVector;
		NiceMockAlloc &mAlloc = intVector.getAlloc();
#else
		ft::vector< int, MockAlloc > intVector;
		MockAlloc &mAlloc = intVector.getAlloc();
#endif

		// At this stage we can only check if our object are correctly calling their destructor.
		EXPECT_CALL(mAlloc, deallocate(intVector.getElements(), 2))
			.Times(1);
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
	
	template <typename Type>
	class VectorTest : public testing::Test
	{
		protected:
			// Default constructor initialize the class's reference
			VectorTest() : 
				mAlloc0_(this->mv0_.getAlloc()),
				mAlloc1_(this->mv1_.getAlloc())
			{
				return ;
			}

			const static int lenv2 = 7;
			void SetUp()
			{
				// We don't expect the data to be initialized at the start, so we do:
				// 		It is undefined behavior to do such thing, vector size is 0.
				// 		It's working only because we are dealing with default types.
				this->v0_[0] = 0;
				this->v0_[1] = 0;

				v1_.push_back(42);
				// Same here: undefined behavior in the real world, testing purpose only:
				v1_[1] = 0;

				for (Type i = 1; i <= lenv2; i++)
					v2_.push_back(i);
			}

			void TearDown()
			{
				// Die is the function called inside the MockAllocator destructor,
				// so we can be sure that the allocator destructor is also called.
				EXPECT_CALL(mAlloc0_, deallocate(mv0_.getElements(), mv0_.getCapacity()))
					.Times(1);
				EXPECT_CALL(mAlloc1_, deallocate(mv1_.getElements(), mv1_.getCapacity()))
					.Times(1);
			}

#ifdef NICE
			typedef testing::NiceMock< MockAllocator< Type >  > MockAlloc;
#else
			typedef MockAllocator< Type > MockAlloc;
#endif
			typedef ft::vector< Type >				Vector;
			typedef ft::vector< Type, MockAlloc >	mVector;

			// Declares the variables the test want to use.
			Vector	v0_;
			Vector	v1_;
			Vector	v2_;

			mVector	mv0_;
			mVector	mv1_;

			MockAlloc	&mAlloc0_;
			MockAlloc	&mAlloc1_;
	};

#ifdef INT_ONLY
	typedef testing::Types< int > MyTypes;
#else
	typedef testing::Types< int, float, double, char, wchar_t> MyTypes;
#endif
	TYPED_TEST_CASE(VectorTest, MyTypes);

	TYPED_TEST(VectorTest, TestDefaultConstructor)
	{
		EXPECT_EQ(this->v0_.size(), (size_t)0);

		EXPECT_EQ(this->v0_[0], 0);
		EXPECT_EQ(this->v0_[0], 0);

		// Testing to remove elements on an empty vector:
		this->v0_.pop_back();
		this->v0_.pop_back();
		this->v0_.pop_back();

		EXPECT_EQ(this->v0_.size(), (size_t)0);
	}

	TYPED_TEST(VectorTest, TestCapacitySize)
	{
		EXPECT_EQ(this->v0_.size(), (size_t)0);
		EXPECT_EQ(this->v1_.size(), (size_t)1);
		EXPECT_EQ(this->v2_.size(), (size_t)7);
	}

	TYPED_TEST(VectorTest, TestModifierPopBack)
	{
		this->v0_.pop_back();
		this->v1_.pop_back();
		this->v2_.pop_back();

		EXPECT_EQ(this->v0_.size(), (size_t)0);
		EXPECT_EQ(this->v1_.size(), (size_t)0);
		EXPECT_EQ(this->v2_.size(), (size_t)6);
	}
	
	//test Operator = // vector& operator=( const vector& other );
	TYPED_TEST(VectorTest, 1TestOperatorEQ)
	{
		this->mv1_.push_back(2);
		this->mv1_.push_back(222);
		this->mv1_.push_back(420);
		this->mv0_.push_back(12);
		this->mv0_.push_back(22);
		this->mv0_.push_back(32);
		this->mv0_.push_back(42);
		this->mv0_.push_back(4);

		size_t mv0Size = this->mv0_.size();
		//size_t mv1Size = this->mv1_.size();
		size_t mv1capacity = this->mv1_.getCapacity();
		size_t mv0capacity = this->mv0_.getCapacity();

		TypeParam * Elements = this->mv0_.getElements();
		std::cout << "adress of the first Element = " << Elements << std::endl;
		for (size_t i = 0; i < mv0Size; i++)
			EXPECT_CALL(this->mAlloc0_, destroy(Elements + i))
				.Times(1);
		EXPECT_CALL(this->mAlloc0_, deallocate(Elements, mv0capacity))
			.Times(AtLeast(1));
		EXPECT_CALL(this->mAlloc0_, allocate(mv1capacity))
			.Times(AtLeast(1));
		Elements = this->mv0_.getElements();
		std::cout << "adress of the second Element = " << Elements << std::endl;
		/*for (size_t i = 0; i < mv1Size; i++)
			EXPECT_CALL(this->mAlloc0_, construct(Elements + i, this->mv1_[i]));
		*/this->mv0_ = this->mv1_;
		/*
		EXPECT_CALL(this->mAlloc0_, construct(this->mv0_.getElements()))
			.Times(v1Size);

		ASSERT_EQ(k, this->v2_.size());
		for (size_t i = 0; i < v0Size; i++)
			EXPECT_EQ(this->v0_[i], this->v2_[i]); 
		*/
	}

	TYPED_TEST(VectorTest, TestOperatorElementAccess)
	{
		//v1
		EXPECT_EQ(this->v1_[0], 42);
		EXPECT_EQ(this->v1_[1], 0);

		//v2
		for (int i = 0; i < this->lenv2; i++)
			EXPECT_EQ(this->v2_[i], i + 1);
	}

	template<typename Type>
	class VectorTestString: public testing::Test
	{
		protected:
			void SetUp()
			{
				// Default capacity is 2
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

	TYPED_TEST(VectorTestString, TestStringDefaultConstructor)
	{
		EXPECT_EQ(this->v4_.size(), (size_t)0);
		// Test segfault here :
		//EXPECT_EQ(this->v4_[0], (char)0);

		// Testing to remove elements on an empty vector:
		this->v4_.pop_back();
		this->v4_.pop_back();
		this->v4_.pop_back();
	}

	TYPED_TEST(VectorTestString, TestStringSize)
	{
		EXPECT_EQ(this->v5_.size(), (size_t)3);
		this->v5_.push_back("Toto is now inside vector");
		EXPECT_EQ(this->v5_.size(), (size_t)4);
		this->v5_.pop_back();
		this->v5_.pop_back();
		EXPECT_EQ(this->v5_.size(), (size_t)2);
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

	/*
	TYPED_TEST(VectorTestString, TestStringAllocation)
	{
		typedef MockAllocator<TypeParam> MockAlloc;
		typedef MockVector<TypeParam, MockAlloc> MockVect;

		MockVect mVector;
		MockAlloc mAlloc = mVector.getAlloc();

		EXPECT_CALL(mAlloc, destroy(mVector.getElements()))
			.Times(1);
		EXPECT_CALL(mAlloc, construct(mVector.getElements(), "toto is born"))
			.Times(1);
		EXPECT_CALL(mAlloc, Die())
			.Times(1);
		EXPECT_CALL(mVector, Die())
			.Times(1);

		mVector.push_back("toto is born");
	}
	
	*/
}  // namespace
