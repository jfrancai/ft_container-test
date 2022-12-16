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

	// Mock utils
	using testing::AtLeast;
	using testing::_;

	// Wrapping the std::allocator API into an interface
	template < class Type >
	class IAllocator
	{
		public:
			typedef Type				value_type;
			typedef Type*				pointer;
			typedef const Type*			const_pointer;
			typedef Type&				reference;
			typedef const Type&			const_reference;
			typedef std::size_t			size_type;
			typedef std::ptrdiff_t		difference_type;

			// Destructor has to be virtual
			virtual ~IAllocator() {}

			virtual	void	deallocate(pointer p, size_type n) = 0;
			virtual pointer	allocate(size_type n) = 0;
			virtual void	construct( pointer p, const_reference val ) = 0;
			virtual void	destroy(pointer p) = 0;
	};

	class IWatcher
	{
		public:
			IWatcher() {}
			virtual	~IWatcher() {}

			virtual void	watch(void) = 0;
			virtual void	stopwatch(void) = 0;
	};

	class WrapAllocatorWatcher : public IWatcher {

		public:
			WrapAllocatorWatcher(void) :
				_isWatching(false),
				_timeCalledDealloc(0),
				_timeCalledAlloc(0),
				_timeCalledConstr(0),
				_timeCalledDestr(0)
			{return;}

			virtual ~WrapAllocatorWatcher() {}

			virtual void	watch(void) {this->_isWatching = true;}
			virtual void	stopwatch(void) {this->_isWatching = false;}

			int		getTimesDealloc(void) const {return (this->_timeCalledDealloc);}
			int		getTimesAlloc(void) const {return (this->_timeCalledAlloc);}
			int		getTimesConstr(void) const {return (this->_timeCalledConstr);}
			int		getTimesDestr(void) const {return (this->_timeCalledDestr);}

			void	incTimesDealloc(void) {if (this->_isWatching == 0) return; this->_timeCalledDealloc++;}
			void	incTimesAlloc(void) {if (this->_isWatching == 0) return; this->_timeCalledAlloc++;}
			void	incTimesConstr(void) {if (this->_isWatching == 0) return; this->_timeCalledConstr++;}
			void	incTimesDestr(void) {if (this->_isWatching == 0) return; this->_timeCalledDestr++;}

		private: 
			bool	_isWatching;
			int		_timeCalledDealloc;
			int		_timeCalledAlloc;
			int		_timeCalledConstr;
			int		_timeCalledDestr;

	};

	// Mocking allocator interface into the MockAllocator class
	template< class Type >
	class WrapAllocator : public IAllocator< Type >{
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


			WrapAllocator(void) : 
				_alloc(),
				_watcher(NULL)
			{
				return ;
			}

			virtual ~WrapAllocator(void)
			{}

			/*
			 * Member functions
			 */
			virtual void	deallocate(pointer p, size_type n) {
				if (this->_watcher)
					this->_watcher->incTimesDealloc();
				return (this->_alloc.deallocate(p, n));
			}

			virtual pointer	allocate(size_type n) {
				if (this->_watcher)
					this->_watcher->incTimesAlloc();
				return (this->_alloc.allocate(n));
			}

			virtual void	construct( pointer p, const_reference val) {
				if (this->_watcher)
					this->_watcher->incTimesConstr();
				return (this->_alloc.construct(p, val));
			}

			virtual void	destroy(pointer p)
			{
				if (this->_watcher)
					this->_watcher->incTimesDestr();
				return (this->_alloc.destroy(p));
			}

			void	setWatcher(WrapAllocatorWatcher *watcher){this->_watcher = watcher;}

		private:
			std::allocator< Type >	_alloc;
			WrapAllocatorWatcher	*_watcher;
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
		typedef WrapAllocator<int> WrapAlloc;


		// First instantiate a watcher
		WrapAllocatorWatcher watcher;

		// Open a new scope so the watcher is at a higher level than the vector.
		// Now it can see what is happening inside its destructor.
		{
			// Construct the tested vector
			ft::vector< int, WrapAlloc > intVector;

			// Then get the constructed allocator inside the tested vector
			WrapAlloc &wAlloc = intVector.getAlloc();

			// Put the watcher inside the vector
			wAlloc.setWatcher(&watcher);

			// Start watching
			watcher.watch();
		}
		EXPECT_EQ(watcher.getTimesAlloc(), 0);
		EXPECT_EQ(watcher.getTimesDealloc(), 1);
		EXPECT_EQ(watcher.getTimesConstr(), 0);
		EXPECT_EQ(watcher.getTimesDestr(), 0);
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
	

//////////////////DEFAULT TYPES TESTS////////////////////////////
	template <typename Type>
	class VectorTest : public testing::Test
	{
		protected:
			// Default constructor initialize the class's reference
			VectorTest() :
				wAlloc0_(this->wV0_.getAlloc())
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
			}

			typedef ft::vector< Type >					Vector;

			typedef WrapAllocator< Type >				WrapAlloc;
			typedef ft::vector< Type, WrapAlloc >		wVector;

			// watcher help you see the calls to the allocator function inside the vector
			WrapAllocatorWatcher						watcher;

			// Declares the variables the test want to use.
			Vector	v0_;
			Vector	v1_;
			Vector	v2_;

			wVector		wV0_;
			WrapAlloc	&wAlloc0_;
	};

#ifdef INT_ONLY
	typedef testing::Types< int > MyTypes;
#else
	typedef testing::Types< int, float, double, char, wchar_t> MyTypes;
#endif
	TYPED_TEST_CASE(VectorTest, MyTypes);

	TYPED_TEST(VectorTest, 2TestOperatorEQ)
	{
		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		{
			wVector	wV0;
			WrapAlloc &wAlloc0 = wV0.getAlloc();
			wAlloc0.setWatcher(&this->watcher);

			wVector	wV1;
			WrapAlloc &wAlloc1 = wV1.getAlloc();
			wAlloc1.setWatcher(&this->watcher);

			// Test setup
			for (int i = 0; i < 42; i++)
				wV1.push_back(42 + i);
			EXPECT_EQ(wV0.size(), (size_t)0);
			EXPECT_EQ(wV1.size(), (size_t)42);

			this->watcher.watch();
			wV1 = wV0;
			this->watcher.stopwatch();

			EXPECT_EQ(wV0.size(), wV1.size());
			EXPECT_EQ(wV0.capacity(), wV1.capacity());
			for (size_t i = 0; i < wV0.size(); i++)
				EXPECT_EQ(wV0[i], wV1[i]);
		}
		EXPECT_EQ(this->watcher.getTimesAlloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDealloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDestr(), 42);
		EXPECT_EQ(this->watcher.getTimesConstr(), 0);
	}

	TYPED_TEST(VectorTest, 1TestOperatorEQ)
	{
		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		{
			wVector	wV0;
			WrapAlloc &wAlloc0 = wV0.getAlloc();
			wAlloc0.setWatcher(&this->watcher);

			wVector	wV1;
			WrapAlloc &wAlloc1 = wV1.getAlloc();
			wAlloc1.setWatcher(&this->watcher);

			// Test setup
			for (int i = 0; i < 42; i++)
				wV1.push_back(42 + i);
			EXPECT_EQ(wV0.size(), (size_t)0);
			EXPECT_EQ(wV1.size(), (size_t)42);

			this->watcher.watch();
			wV0 = wV1;
			this->watcher.stopwatch();

			EXPECT_EQ(wV0.size(), wV1.size());
			EXPECT_EQ(wV0.capacity(), wV1.capacity());
			for (size_t i = 0; i < wV0.size(); i++)
				EXPECT_EQ(wV0[i], wV1[i]);
		}
		EXPECT_EQ(this->watcher.getTimesAlloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDealloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDestr(), 0);
		EXPECT_EQ(this->watcher.getTimesConstr(), 42);
	}

	TYPED_TEST(VectorTest, 0TestOperatorEQ)
	{
		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		{
			wVector	wV0;
			WrapAlloc &wAlloc0 = wV0.getAlloc();
			wAlloc0.setWatcher(&this->watcher);

			wVector	wV1;
			WrapAlloc &wAlloc1 = wV1.getAlloc();
			wAlloc1.setWatcher(&this->watcher);

			// Test setup
			EXPECT_EQ(wV0.size(), (size_t)0);
			EXPECT_EQ(wV1.size(), (size_t)0);

			this->watcher.watch();
			wV0 = wV1;
			this->watcher.stopwatch();

			EXPECT_EQ(wV0.size(), wV1.size());
			EXPECT_EQ(wV0.capacity(), wV1.capacity());
		}
		EXPECT_EQ(this->watcher.getTimesAlloc(), 0);
		EXPECT_EQ(this->watcher.getTimesDealloc(), 0);
		EXPECT_EQ(this->watcher.getTimesDestr(), 0);
		EXPECT_EQ(this->watcher.getTimesConstr(), 0);
	}

	TYPED_TEST(VectorTest, TestDefaultConstructor)
	{
		EXPECT_EQ(this->v0_.size(), (size_t)0);

		EXPECT_EQ(this->v0_[0], 0);
		EXPECT_EQ(this->v0_[1], 0);

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
	
	TYPED_TEST(VectorTest, TestOperatorElementAccess)
	{
		//v1
		EXPECT_EQ(this->v1_[0], 42);
		EXPECT_EQ(this->v1_[1], 0);

		//v2
		for (int i = 0; i < this->lenv2; i++)
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

	TYPED_TEST(VectorTest, TestAssign_1_IsExisting)
	{
		// 0) Existance
		this->v1_.assign(5, 'a');
		// 1) Updating the size
		EXPECT_EQ(this->v1_.size(), 5);
		// 2) Updating the value
		EXPECT_EQ(this->v1_.capacity(), 8);
		// 3) Do not accept garbage
		EXPECT_THROW({
			try
			{
				this->v1_.assign(-1, 'a');
			}
			catch (const std::exception &e)
			{
				EXPECT_STREQ("cannot create std::vector larger than max_size()", e.what());
				throw;

			}
		}, std::invalid_argument);
	}

	TYPED_TEST(VectorTest, TestAssign_1_WithCountInfOrEqToCapacity)
	{
		// v1_ is of size 1 so we are not suppose to reallocate memory
		size_t size = 1;
		this->v1_.assign(size, 'a');
		for (size_t i = 0; i < size; i++)
			EXPECT_EQ(this->v1_[i], 'a');
		EXPECT_EQ(this->v1_.size(), 1);
		EXPECT_EQ(this->v1_.capacity(), 2);

		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		// Enforce not to call any deallocate or allocate in this case (Let's push some more object also).
		{
			// Test set up
			wVector	wVect;
			WrapAlloc &wAlloc = wVect.getAlloc();
			wAlloc.setWatcher(&this->watcher);

			wVect.push_back(42);
			wVect.push_back(21);
			wVect.push_back(21);
			wVect.push_back(24);
			wVect.push_back(48);
			////////////////////

			// The actual test
			this->watcher.watch();
			wVect.assign(3, 'a');
			this->watcher.stopwatch();
			// We are not interested on what is happening inside the destructor that why we call watch stop.

			EXPECT_EQ(wVect.size(), 3);
			EXPECT_EQ(wVect.capacity(), 8);
		}
		EXPECT_EQ(this->watcher.getTimesAlloc(), 0);
		EXPECT_EQ(this->watcher.getTimesDealloc(), 0);
		EXPECT_EQ(this->watcher.getTimesDestr(), 5);
		EXPECT_EQ(this->watcher.getTimesConstr(), 3);
	}

	TYPED_TEST(VectorTest, TestAssign_1_WithCountSupToCapacity)
	{
		// v1_ is of size 1 so we are not suppose to reallocate memory
		size_t size = 10;
		this->v1_.assign(size, 'a');
		for (size_t i = 0; i < size; i++)
			EXPECT_EQ(this->v1_[i], 'a');

		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		// Enforce not to call any deallocate or allocate in this case (Let's push some more object also).
		{
			// Test set up
			wVector	wVect;
			WrapAlloc &wAlloc = wVect.getAlloc();
			wAlloc.setWatcher(&this->watcher);

			wVect.push_back(42);
			////////////////////

			// The actual test
			this->watcher.watch();
			wVect.assign(100, 'a');
			this->watcher.stopwatch();
			// We are not interested on what is happening inside the destructor that why we call watch stop.
			EXPECT_EQ(wVect.size(), 100);
			EXPECT_EQ(wVect.capacity(), 128);
		}
		EXPECT_EQ(this->watcher.getTimesAlloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDealloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDestr(), 1);
		EXPECT_EQ(this->watcher.getTimesConstr(), 100);
	}

//////////////////OBJECTS TESTS////////////////////////////

	TYPED_TEST(VectorTest, TestConstFront)
	{
		const ft::vector<TypeParam> myConstVect;
		myConstVect.front();
	}

	TYPED_TEST(VectorTest, TestFront)
	{
		//v0
		EXPECT_EQ(this->v0_.front(), 0); // Undefined behavior
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

			typedef WrapAllocator< Type >				WrapAlloc;
			typedef ft::vector< Type, WrapAlloc >		wVector;

			// watcher help you see the calls to the allocator function inside the vector
			WrapAllocatorWatcher						watcher;

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

	TYPED_TEST(VectorTestString, TestStringAllocation)
	{
		typedef WrapAllocator<TypeParam> WrapAlloc;
		typedef ft::vector<TypeParam, WrapAlloc> wVector;

		{
			wVector	wVect;
			WrapAlloc &wAlloc = wVect.getAlloc();
			wAlloc.setWatcher(&this->watcher);
			this->watcher.watch();

			wVect.push_back("toto is born");
		}
		EXPECT_EQ(this->watcher.getTimesAlloc(), 0);
		EXPECT_EQ(this->watcher.getTimesDealloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDestr(), 1);
		EXPECT_EQ(this->watcher.getTimesConstr(), 1);
	}
}  // namespace
