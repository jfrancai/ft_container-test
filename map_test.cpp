#include <algorithm>
#include <gtest/gtest.h>
#include "../include/map.hpp"
#include "../include/utility.hpp"
#include <utility>
#include <list>
#include <map>
#include <time.h>

/*
 * [ google test v1.8.1 in use for compatibility reasons ]
 *
 * Usefull links :
 * Reference Testing	: https://google.github.io/googletest/reference/testing.html
 * Reference Assertions : https://google.github.io/googletest/reference/assertions.html
 */

namespace {

	template < class T1, class T2 >
	bool comp_pair(const ft::pair< T1, T2 > &p1, const std::pair< T1, T2 > &p2)
	{
		return (p1.first == p2.first && p1.second == p2.second);
	}

	TEST(MapBasicTest, DefaultConstructor)
	{
		ft::map< std::string, int > myMap;
		std::map< std::string, int > stdMap;

		EXPECT_TRUE((myMap.empty() == true) == (stdMap.empty() == true));
		EXPECT_EQ(myMap.size(), stdMap.size());
		EXPECT_TRUE(myMap.get_allocator() == stdMap.get_allocator());
		EXPECT_EQ(myMap.count(""), stdMap.count(""));
		EXPECT_THROW({
			try
			{
				myMap.at("");
			}
			catch (const std::exception &e)
			{
				EXPECT_STREQ("map::at", e.what());
				throw;
			}
		}, std::out_of_range);
		EXPECT_EQ(myMap[""], stdMap[""]);
	}

	TEST(MapBasicTest, CopyConstructor)
	{
		ft::map< int, std::string > m0;
		ft::map< int, std::string > m1;

		for (int i = 0; i < 10; ++i)
			m0.insert(ft::make_pair(i, "toto"));

		EXPECT_FALSE(m0 == m1);
		m1 = m0;
		EXPECT_TRUE(m0 == m1);
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
		myMap.insert(ft::make_pair(42, 42));
		stdMap.insert(std::make_pair(42, 42));

		myMap.insert(ft::make_pair(42, 42));
		stdMap.insert(std::make_pair(42, 42));

		myMap.insert(ft::make_pair(43, 43));
		stdMap.insert(std::make_pair(43, 43));

		myMap.insert(ft::make_pair(44, 44));
		stdMap.insert(std::make_pair(44, 44));

		EXPECT_TRUE(myMap.get_allocator() == stdMap.get_allocator());
		EXPECT_TRUE(myMap.empty() == stdMap.empty());
		EXPECT_EQ(myMap.size(), stdMap.size());
		EXPECT_EQ(myMap.max_size(), stdMap.max_size());
		for (int i = 42; i < 45; ++i)
		{
			EXPECT_EQ(myMap.count(i), stdMap.count(i));
			EXPECT_EQ(myMap.find(i)->first, stdMap.find(i)->first);
			EXPECT_EQ(myMap.at(i), stdMap.at(i));
			EXPECT_EQ(myMap[i], stdMap[i]);
		}
		EXPECT_EQ((--myMap.find(404))->first, (--stdMap.find(404))->first);
		EXPECT_EQ(myMap.count(404), stdMap.count(404));

		EXPECT_TRUE(comp_pair(*myMap.begin(), *stdMap.begin()));
		EXPECT_TRUE(comp_pair(*(--myMap.end()), *(--stdMap.end())));
		EXPECT_TRUE(comp_pair(*myMap.rbegin(), *stdMap.rbegin()));
		EXPECT_TRUE(comp_pair(*(--(myMap.rend())), *(--stdMap.rend())));
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

		m0.insert(ft::make_pair(0, 42));

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


		m1.insert(ft::make_pair(0, 42));

		EXPECT_TRUE(m0 == m1);
		EXPECT_FALSE(m0 != m1);
		EXPECT_FALSE(m0 < m1);
		EXPECT_FALSE(m0 > m1);
		EXPECT_TRUE(m0 >= m1);
		EXPECT_TRUE(m0 <= m1);

		m0.insert(ft::make_pair(1, 43));
		m1.insert(ft::make_pair(1, 42));

		EXPECT_FALSE(m0 == m1);
		EXPECT_TRUE(m0 != m1);
		EXPECT_FALSE(m0 < m1);
		EXPECT_TRUE(m0 > m1);
		EXPECT_TRUE(m0 >= m1);
		EXPECT_FALSE(m0 <= m1);

		ft::map< int, int > m2;
		ft::map< int, int > m3;

		m2.insert(ft::make_pair(2, 42));
		m3.insert(ft::make_pair(2, 43));

		EXPECT_FALSE(m2 == m3);
		EXPECT_TRUE(m2 != m3);
		EXPECT_TRUE(m2 < m3);
		EXPECT_FALSE(m2 > m3);
		EXPECT_FALSE(m2 >= m3);
		EXPECT_TRUE(m2 <= m3);
	}

	TEST(MapBasicTest, InsertMethod2)
	{
		ft::map< int, int > myMap;
		std::map< int, int > stdMap;
		srand((unsigned)time(NULL));

		int tab[10] = { 1378, 4719, 112, 444444, 1010, 287676, 2111120, 338337, 47187, 4 };
		for (int i = 0; i < 10; ++i)
		{
			myMap.insert(ft::make_pair(tab[i], 0));
			stdMap.insert(std::make_pair(tab[i], 0));
		}
		myMap.insert(ft::make_pair(42, 42));
		stdMap.insert(std::make_pair(42, 42));

		myMap.insert(myMap.find(42), ft::make_pair(43, 43));
		stdMap.insert(stdMap.find(42), std::make_pair(43, 43));
		EXPECT_TRUE(myMap.get_allocator() == stdMap.get_allocator());
		EXPECT_TRUE(myMap.empty() == stdMap.empty());
		EXPECT_EQ(myMap.size(), stdMap.size());
		EXPECT_EQ(myMap.max_size(), stdMap.max_size());
		for (int i = 0; i < 10; ++i)
		{
			EXPECT_EQ(myMap.count(tab[i]), stdMap.count(tab[i]));
			EXPECT_EQ(myMap.find(tab[i])->first, stdMap.find(tab[i])->first);
			EXPECT_EQ(myMap.at(tab[i]), stdMap.at(tab[i]));
			EXPECT_EQ(myMap[tab[i]], stdMap[tab[i]]);
		}
		EXPECT_EQ((--myMap.find(404))->first, (--stdMap.find(404))->first);
		EXPECT_EQ(myMap.count(404), stdMap.count(404));

		EXPECT_TRUE(comp_pair(*myMap.begin(), *stdMap.begin()));
		EXPECT_TRUE(comp_pair(*(--myMap.end()), *(--stdMap.end())));
		EXPECT_TRUE(comp_pair(*myMap.rbegin(), *stdMap.rbegin()));
		EXPECT_TRUE(comp_pair(*(--(myMap.rend())), *(--stdMap.rend())));
		EXPECT_TRUE((myMap == myMap) ==  (stdMap == stdMap));
		EXPECT_TRUE((myMap != myMap) ==  (stdMap != stdMap));
		EXPECT_TRUE((myMap < myMap) ==  (stdMap < stdMap));
		EXPECT_TRUE((myMap <= myMap) ==  (stdMap <= stdMap));
		EXPECT_TRUE((myMap > myMap) ==  (stdMap > stdMap));
		EXPECT_TRUE((myMap >= myMap) ==  (stdMap >= stdMap));
	}

	TEST(MapBasicTest, Iterators)
	{

		ft::map< int, int > myMap;
		std::map< int, int > stdMap;

		for (int i = 0; i < 5; ++i)
		{
			myMap.insert(ft::make_pair(i, 42));
			stdMap.insert(std::make_pair(i, 42));
		}

		ft::map< int, int >::iterator myIt(myMap.begin());
		std::map< int, int >::iterator stdIt(stdMap.begin());


		EXPECT_TRUE(comp_pair(*myMap.begin(), *stdMap.begin()));

		myIt = myMap.end();
		stdIt = stdMap.end();


		for (int i = 5; i < 10; ++i)
		{
			myMap.insert(ft::make_pair(i, 43));
			stdMap.insert(std::make_pair(i, 43));
		}
		EXPECT_TRUE(comp_pair(*(--myIt), *(--stdIt)));

		ft::map< int, int >::iterator myIt2(--myMap.end());
		std::map< int, int >::iterator stdIt2(--stdMap.end());

		EXPECT_TRUE(comp_pair(*myIt, *stdIt));
		EXPECT_TRUE(comp_pair(*myIt2, *stdIt2));
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

		cont.insert(ft::make_pair(1, 'a'));
		cont.insert(ft::make_pair(2, 'b'));
		cont.insert(ft::make_pair(3, 'c'));
		cont.insert(ft::make_pair(4, 'd'));
		cont.insert(ft::make_pair(5, 'e'));

		ft::map< int, char, ModCmp >::value_compare comp_val = cont.value_comp();
		ft::map< int, char, ModCmp >::key_compare comp_key = cont.key_comp();

		const ft::pair<int, char> val = ft::make_pair(100, 'a');

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

	TEST(PairTest, CanCreateDefaultPair) {
		ft::pair<int, double> p;
		EXPECT_EQ(0, p.first);
		EXPECT_EQ(0.0, p.second);
	}

	TEST(PairTest, CanCreatePairWithValues) {
		ft::pair<int, double> p(42, 3.14);
		EXPECT_EQ(42, p.first);
		EXPECT_EQ(3.14, p.second);
	}

	TEST(PairTest, CanAccessPairElements) {
		ft::pair<int, double> p(42, 3.14);
		EXPECT_EQ(42, p.first);
		EXPECT_EQ(3.14, p.second);
		p.first = 13;
		p.second = 2.71;
		EXPECT_EQ(13, p.first);
		EXPECT_EQ(2.71, p.second);
	}
	
	TEST(PairTest, CanCopyConstructPair) {
		ft::pair<int, double> p(42, 3.14);
		ft::pair<int, double> p_copy(p);
		EXPECT_EQ(p.first, p_copy.first);
		EXPECT_EQ(p.second, p_copy.second);
	}
	
	TEST(PairTest, CanAssignPair) {
		ft::pair<int, double> p(42, 3.14);
		ft::pair<int, double> p_copy;
		p_copy = p;
		EXPECT_EQ(p.first, p_copy.first);
		EXPECT_EQ(p.second, p_copy.second);
	}
	
	TEST(PairTest, CanComparePairs) {
		ft::pair<int, double> p1(42, 3.14);
		ft::pair<int, double> p2(13, 2.71);
		ft::pair<int, double> p3(42, 3.14);
		EXPECT_TRUE(p1 != p2);
		EXPECT_TRUE(p1 == p3);
		EXPECT_FALSE(p2 == p3);
		EXPECT_TRUE(p2 < p3);
		EXPECT_TRUE(p3 > p2);
		EXPECT_TRUE(p3 >= p1);
		EXPECT_TRUE(p3 <= p1);
	}

	int	&ref_wrap(int &n)
	{
		return (n);
	}

	template<typename T>
	class reference_wrapper {
	public:
	    reference_wrapper(T& value) : ref(&value) {}
	    operator T&() const { return *ref; }
	private:
	    T* ref;
	};
	
	template<typename T>
	reference_wrapper<T> ref(T& value) {
	    return reference_wrapper<T>(value);
	}

	TEST(MakePairTest, CanCreatePairWithMakePair)
	{
		int n = 1;	
		int a[5] = {1, 2, 3, 4, 5};

		ft::pair<int, int> p1 = ft::make_pair(n, a[1]);
		EXPECT_EQ(p1.first, 1);
		EXPECT_EQ(p1.second, 2);

		ft::pair<reference_wrapper<int>, int *> p2 = ft::make_pair(ref(n), a);
		n = 42;
		EXPECT_EQ(p2.first, 42);
		EXPECT_EQ(*(p2.second + 2), 3);
	}

	TEST(MapBasicTest, OperatorEqual)
	{
		ft::map< int, int > m0;
		ft::map< int, int > m1;

		for (int i = 0; i < 10; ++i)
			m1.insert(ft::make_pair(i, i));
		EXPECT_FALSE(m1 == m0);
		m0 = m1;
		EXPECT_TRUE(m1 == m0);
	}

	TEST(MapBasicTest, LowerBoundMethod)
	{
		ft::map< int, int > myMap;
		std::map< int, int > stdMap;

		for (int i = 0; i < 20;)
		{	
			myMap.insert(ft::make_pair(i, i));
			stdMap.insert(std::make_pair(i, i));
			i+= 4;
		}

		for (int i = 0; i < 17; ++i)
			EXPECT_TRUE(comp_pair(*myMap.lower_bound(i), *stdMap.lower_bound(i)));

		EXPECT_TRUE(comp_pair(*(--myMap.lower_bound(42)), *(--stdMap.lower_bound(42))));
	}

	TEST(MapBasicTest, UpperBoundMethod)
	{
		ft::map< int, int > myMap;
		std::map< int, int > stdMap;

		for (int i = 0; i < 20;)
		{	
			myMap.insert(ft::make_pair(i, i));
			stdMap.insert(std::make_pair(i, i));
			i += 4;
		}

		for (int i = 0; i < 16; ++i)
			EXPECT_TRUE(comp_pair(*myMap.upper_bound(i), *stdMap.upper_bound(i)));
		EXPECT_TRUE(comp_pair(*(--myMap.upper_bound(42)), *(--stdMap.upper_bound(42))));
	}


	TEST(MapBasicTest, EqualRangeMethod)
	{
		ft::map< int, int > myMap;
		std::map< int, int > stdMap;

		for (int i = 0; i < 20;)
		{	
			myMap.insert(ft::make_pair(i, i));
			stdMap.insert(std::make_pair(i, i));
			i += 4;
		}

		EXPECT_TRUE((myMap.equal_range(7).first == myMap.lower_bound(7)) == (stdMap.equal_range(7).first == stdMap.lower_bound(7)));
		EXPECT_TRUE((myMap.equal_range(7).second == myMap.upper_bound(7)) == (stdMap.equal_range(7).second == stdMap.upper_bound(7)));
	}
}  // namespace
