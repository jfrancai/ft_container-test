/*
 * Usefull links :
 * Reference Testing	: https://google.github.io/googletest/reference/testing.html
 * Reference Assertions : https://google.github.io/googletest/reference/assertions.html
 *
 * [ google test v1.8.1 in use for compatibility reasons ]
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
 * 	1)	vector(); ok
 * 	2)	vector( const vector& other ); ok
 * 	3)	explicit vector( const Allocator& alloc ); ok
 * 	4)	explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()); ok
 * 	5)	template< class InputIt > vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
 *
 * Destructors
 *
 */


#include <algorithm>
// Testing Library
#include <gtest/gtest.h>
// Mocking Library
//#include "gmock/gmock.h"
// The tested Library
#include <ft/vector.hpp>

namespace {

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

			virtual	void		deallocate(pointer p, size_type n) = 0;
			virtual pointer		allocate(size_type n) = 0;
			virtual void		construct( pointer p, const_reference val ) = 0;
			virtual void		destroy(pointer p) = 0;
			virtual size_type	max_size(void) const = 0;
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
				_timeCalledDestr(0),
				_timeCalledMaxSize(0)
			{return;}

			virtual ~WrapAllocatorWatcher() {}

			virtual void	watch(void) {this->_isWatching = true;}
			virtual void	stopwatch(void) {this->_isWatching = false;}

			int		getTimesDealloc(void) const {return (this->_timeCalledDealloc);}
			int		getTimesAlloc(void) const {return (this->_timeCalledAlloc);}
			int		getTimesConstr(void) const {return (this->_timeCalledConstr);}
			int		getTimesDestr(void) const {return (this->_timeCalledDestr);}
			int		getTimesMaxSize(void) const {return (this->_timeCalledMaxSize);}

			void	incTimesDealloc(void) {if (this->_isWatching == 0) return; this->_timeCalledDealloc++;}
			void	incTimesAlloc(void) {if (this->_isWatching == 0) return; this->_timeCalledAlloc++;}
			void	incTimesConstr(void) {if (this->_isWatching == 0) return; this->_timeCalledConstr++;}
			void	incTimesDestr(void) {if (this->_isWatching == 0) return; this->_timeCalledDestr++;}
			void	incTimesMaxSize(void) {if (this->_isWatching == 0) return; this->_timeCalledMaxSize++;}

			void	initWatcher(void) {
				_isWatching = false;
				_timeCalledDealloc = 0;
				_timeCalledAlloc = 0;
				_timeCalledConstr = 0;
				_timeCalledDestr = 0;
				_timeCalledMaxSize = 0;
			}

		private: 
			bool	_isWatching;
			int		_timeCalledDealloc;
			int		_timeCalledAlloc;
			int		_timeCalledConstr;
			int		_timeCalledDestr;
			int		_timeCalledMaxSize;

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

			WrapAllocator(WrapAllocatorWatcher& wrapAllocatorWatcher) : 
				_alloc(),
				_watcher(wrapAllocatorWatcher)
			{
				return ;
			}

			virtual ~WrapAllocator(void)
			{}

			/*
			 * Member functions
			 */
			virtual void	deallocate(pointer p, size_type n) {
				this->_watcher.incTimesDealloc();
				return (this->_alloc.deallocate(p, n));
			}

			virtual pointer	allocate(size_type n) {
				this->_watcher.incTimesAlloc();
				return (this->_alloc.allocate(n));
			}

			virtual void	construct( pointer p, const_reference val) {
				this->_watcher.incTimesConstr();
				return (this->_alloc.construct(p, val));
			}

			virtual void	destroy(pointer p)
			{
				this->_watcher.incTimesDestr();
				return (this->_alloc.destroy(p));
			}

			virtual size_type	max_size(void) const
			{
				this->_watcher.incTimesMaxSize();
				return (this->_alloc.max_size());
			}

		private:
			std::allocator< Type >	_alloc;
			WrapAllocatorWatcher	&_watcher;
			WrapAllocator(void);
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
			// Construct an wrapped allocator that use a watcher
			WrapAlloc wAlloc(watcher);

			// Construct the tested vector with copy of the wAlloc object
			ft::vector< int, WrapAlloc > intVector(wAlloc);

			// Start watching
			watcher.watch();
		}
		EXPECT_EQ(watcher.getTimesAlloc(), (0));
		EXPECT_EQ(watcher.getTimesDealloc(), (1));
		EXPECT_EQ(watcher.getTimesConstr(), (0));
		EXPECT_EQ(watcher.getTimesDestr(), (0));
	}

	TEST(VectorBasicTest, Iterator)
	{
		ft::vector< std::string > fruits;

		fruits.push_back("orange");
		fruits.push_back("banane");

		// Default construct
		ft::vector< std::string >::iterator it0;
		/* LegacyIterator */
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
		std::swap(it0, it1);

		EXPECT_STREQ((*it1).c_str(), "orange");
		EXPECT_STREQ((*it0).c_str(), "banane");
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
				this->watcher.initWatcher();
			}

			typedef ft::vector< Type >					Vector;

			typedef WrapAllocator< Type >				WrapAlloc;
			typedef ft::vector< Type, WrapAlloc >		wVector;

			// watcher help you see the calls to the allocator function inside the vector
			WrapAllocatorWatcher						watcher;

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


	TYPED_TEST(VectorTest, TestBegin)
	{
	}

	TYPED_TEST(VectorTest, TestCountConstructor)
	{
		// One param
		ft::vector< TypeParam > myVect0(0);
		EXPECT_EQ(myVect0.size(), size_t(0));
		EXPECT_EQ(myVect0.capacity(), size_t(0));
		ft::vector< TypeParam > myVect1(42);
		EXPECT_EQ(myVect1.size(), size_t(42));
		EXPECT_EQ(myVect1.capacity(), size_t(42));

		// Two param
		ft::vector< TypeParam > myVect2(3, 42);
		for (size_t i = 0; i < 3; i++)
			EXPECT_EQ(myVect2[i], 42);
		EXPECT_EQ(myVect2.size(), size_t(3));
		EXPECT_EQ(myVect2.capacity(), size_t(3));

		// Three param
		ft::vector< TypeParam > myVect3(32, 42, myVect2.get_allocator());
		EXPECT_EQ(myVect3.size(), size_t(32));
		EXPECT_EQ(myVect3.capacity(), size_t(32));

		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		{
			// Test set up
			WrapAlloc wAlloc(this->watcher);

			// Watch
			this->watcher.watch();
			wVector myVect4(32, 42, wAlloc);
			this->watcher.stopwatch();

			EXPECT_EQ(myVect4.size(), size_t(32));
			EXPECT_EQ(myVect4.capacity(), size_t(32));

			// endWatch
			EXPECT_EQ(this->watcher.getTimesAlloc(), (1));
			EXPECT_EQ(this->watcher.getTimesDealloc(), (0));
			EXPECT_EQ(this->watcher.getTimesDestr(), (0));
			EXPECT_EQ(this->watcher.getTimesConstr(), (32));
		}
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

			EXPECT_EQ(this->v2_.capacity(), myVect.capacity());
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
		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		{
			// Test set up
			WrapAlloc wAlloc(this->watcher);
			wVector	wVect(wAlloc);

			// Watch
			this->watcher.watch();
			wVect.reserve(0);
			this->watcher.stopwatch();
			// endWatch
			EXPECT_EQ(this->watcher.getTimesAlloc(), (0));
			EXPECT_EQ(this->watcher.getTimesDealloc(), (0));
			EXPECT_EQ(this->watcher.getTimesDestr(), (0));
			EXPECT_EQ(this->watcher.getTimesConstr(), (0));
			EXPECT_EQ(wVect.size(), size_t(0));
		}

		{
			// Test set up
			WrapAlloc	wAlloc(this->watcher);
			wVector		wVect(wAlloc);

			wVect.push_back(42);
			wVect.push_back(1);

			// Watch
			this->watcher.watch();
			wVect.reserve(35);
			this->watcher.stopwatch();
			// endWatch
			EXPECT_EQ(this->watcher.getTimesAlloc(), (1));
			EXPECT_EQ(this->watcher.getTimesDealloc(), (1));
			EXPECT_LE(this->watcher.getTimesDestr(), (2));
			EXPECT_LE(this->watcher.getTimesConstr(), (2));
		}
	}

	TYPED_TEST(VectorTest, TestMaxSize)
	{
		this->v0_.max_size();
		EXPECT_EQ(this->v0_.max_size(), size_t(this->witnessEmptyVect.max_size()));
		EXPECT_EQ(this->v1_.max_size(), size_t(this->witnessEmptyVect.max_size()));
		EXPECT_EQ(this->v2_.max_size(), size_t(this->witnessEmptyVect.max_size()));

		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		{
			// Test set up
			WrapAlloc wAlloc(this->watcher);
			wVector	wVect(wAlloc);

			// Watch
			this->watcher.watch();
			wVect.max_size();
			this->watcher.stopwatch();
			// endWatch
		}
#ifdef __APPLE__
		if (sizeof(TypeParam) == 1)
			EXPECT_EQ(this->watcher.getTimesMaxSize(), 0);
		else
			EXPECT_EQ(this->watcher.getTimesMaxSize(), 1);
#else
		EXPECT_EQ(this->watcher.getTimesMaxSize(), 1);
#endif
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

	TYPED_TEST(VectorTest, 2TestOperatorEQ)
	{
		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		{
			WrapAlloc wAlloc0(this->watcher);
			wVector	wV0(wAlloc0);

			WrapAlloc wAlloc1(this->watcher);
			wVector	wV1(wAlloc1);

			// Test setup
			for (int i = 0; i < 42; i++)
				wV1.push_back(42 + i);
			EXPECT_EQ(wV0.size(), size_t(0));
			EXPECT_EQ(wV1.size(), size_t(42));

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
			WrapAlloc wAlloc0(this->watcher);
			wVector	wV0(wAlloc0);

			WrapAlloc wAlloc1(this->watcher);
			wVector	wV1(wAlloc1);

			// Test setup
			for (int i = 0; i < 42; i++)
				wV1.push_back(42 + i);
			EXPECT_EQ(wV0.size(), size_t(0));
			EXPECT_EQ(wV1.size(), size_t(42));

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
			WrapAlloc wAlloc0(this->watcher);
			wVector	wV0(wAlloc0);

			WrapAlloc wAlloc1(this->watcher);
			wVector	wV1(wAlloc1);

			// Test setup
			EXPECT_EQ(wV0.size(), size_t(0));
			EXPECT_EQ(wV1.size(), size_t(0));

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

	TYPED_TEST(VectorTest, TestAssign_1_OnEmptyVect)
	{
		{
			typedef WrapAllocator< TypeParam >				WrapAlloc;
			typedef ft::vector< TypeParam, WrapAlloc >		wVector;

			// Test set up
			WrapAlloc wAlloc(this->watcher);
			wVector	wVect(wAlloc);

			// Watch
			this->watcher.watch();
			wVect.assign(1, 42);
			this->watcher.stopwatch();
			// endWatch

			EXPECT_EQ(wVect.size(), size_t(1));
			EXPECT_EQ(wVect.capacity(), size_t(1));
		}
		EXPECT_EQ(this->watcher.getTimesAlloc(), 1);
		EXPECT_LE(this->watcher.getTimesDealloc(), 1); // EXPECT_LE because deallocation with size of 0 may be expected
		EXPECT_EQ(this->watcher.getTimesDestr(), 0);
		EXPECT_EQ(this->watcher.getTimesConstr(), 1);
		//EXPECT_EQ(this->watcher.getTimesMaxSize(), int(1));
	}

	TYPED_TEST(VectorTest, TestAssign_1_IsExisting)
	{
		// 0) Existance
		this->v1_.assign(5, 'a');
		// 1) Updating the size
		EXPECT_EQ(this->v1_.size(), size_t(5));
		// 2) Updating the value
		EXPECT_EQ(this->v1_.capacity(), size_t(8));
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
		EXPECT_EQ(this->v1_.size(), size_t(1));
		EXPECT_EQ(this->v1_.capacity(), size_t(1));

		typedef WrapAllocator< TypeParam >				WrapAlloc;
		typedef ft::vector< TypeParam, WrapAlloc >		wVector;

		// Enforce not to call any deallocate or allocate in this case (Let's push some more object also).
		{
			// Test set up
			WrapAlloc wAlloc(this->watcher);
			wVector	wVect(wAlloc);

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

			EXPECT_EQ(wVect.size(), size_t(3));
			EXPECT_EQ(wVect.capacity(), size_t(8));
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
			WrapAlloc wAlloc(this->watcher);
			wVector	wVect(wAlloc);

			wVect.push_back(42);
			////////////////////

			// The actual test
			this->watcher.watch();
			wVect.assign(100, 'a');
			this->watcher.stopwatch();
			// We are not interested on what is happening inside the destructor that why we call watch stop.
			EXPECT_EQ(wVect.size(), size_t(100));
			EXPECT_EQ(wVect.capacity(), size_t(128));
		}
		EXPECT_EQ(this->watcher.getTimesAlloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDealloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDestr(), 1);
		EXPECT_EQ(this->watcher.getTimesConstr(), 100);
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

	TYPED_TEST(VectorTestString, TestStringAllocation)
	{
		typedef WrapAllocator<TypeParam> WrapAlloc;
		typedef ft::vector<TypeParam, WrapAlloc> wVector;

		{
			WrapAlloc wAlloc(this->watcher);
			wVector	wVect(wAlloc);

			this->watcher.watch();
			wVect.push_back("toto is born");
		}
		EXPECT_EQ(this->watcher.getTimesAlloc(), 1);
		EXPECT_GE(this->watcher.getTimesDealloc(), 1);
		EXPECT_EQ(this->watcher.getTimesDestr(), 1);
		EXPECT_EQ(this->watcher.getTimesConstr(), 1);
	}
}  // namespace
