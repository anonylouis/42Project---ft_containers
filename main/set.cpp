/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 01:41:48 by lcalvie           #+#    #+#             */
/*   Updated: 2022/11/01 17:05:54 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* <------------------------> VECTOR FROM STD OR FT <------------------------> */

#if REAL
	# include <set>
	namespace ft = std;
#else
	# include "../includes/set.hpp"
#endif

/* <-------------------------------------------------------------------------> */

#include <iostream>
#include <string>
#include "../other/color.hpp"
#include <vector>

template <typename T>
void print_set(T &m)
{
	typename T::iterator start = m.begin();
	typename T::iterator finish = m.end();

	while (start != finish)
	{
		std::cout << *start << " ";
		++start;
	}
	std::cout << "\n";
}

template<class T, class Compare, class Alloc >
void	print_comparisons(ft::set<T,Compare,Alloc> &set1, ft::set<T,Compare,Alloc> &set2)
{
	std::cout << red << italic;

	if (set1 == set2)
		std::cout << "set1 == set2" << std::endl;
	if (set1 != set2)
		std::cout << "set1 != set2" << std::endl;
	if (set1 < set2)
		std::cout << "set1 < set2" << std::endl;
	if (set1 <= set2)
		std::cout << "set1 <= set2" << std::endl;
	if (set1 > set2)
		std::cout << "set1 > set2" << std::endl;
	if (set1 >= set2)
		std::cout << "set1 >= set2" << std::endl;

	std::cout << reset;
}

int main()
{
	std::cout << italic << "Library used : "<< (REAL ? "std" : "ft") << std::endl << std::endl << reset;
	std::cout << std::boolalpha;


	std::cout << red << bold << "Constructors :" << std::endl << reset;

	std::cout << italic << "default constructor :\n" << reset;
	ft::set<int> test;
	print_set(test);
	std::cout << std::endl;

	std::vector<int> temp_vec;
	temp_vec.push_back(1);
	temp_vec.push_back(2);
	temp_vec.push_back(3);
	temp_vec.push_back(1);
	std::cout << italic << "range constructor :\n" << reset;
	ft::set<int> test2(temp_vec.begin(), temp_vec.end());
	print_set(test2);
	std::cout << std::endl;

	std::cout << italic << " copy constructor :\n" << reset;
	ft::set<int> test3(test2);
	print_set(test3);
	std::cout << std::endl;

	std::cout << italic << " assignment operator :\n" << reset;
	test2 = test3;
	print_set(test2);
	std::cout << std::endl;


	std::cout << red << bold << "iterators :" << std::endl << reset;

	ft::set<int>::iterator start = test2.begin();
	ft::set<int>::iterator finish = test2.end();

	while (start != finish)
	{
		std::cout << *start << " ";
		++start;
		--start;
		start++;
		start--;
		++start;
	}

	std::cout << red << bold << "\nreverse iterators :" << std::endl << reset;

	ft::set<int>::reverse_iterator start2 = test2.rbegin();
	ft::set<int>::reverse_iterator finish2 = test2.rend();

	while (start2 != finish2)
	{
		std::cout << " -  " << *start2 << " ";
		++start2;
		--start2;
		start2++;
		start2--;
		++start2;
	}

	std::cout << red << bold << "\ncapacity  :"<< std::endl << reset;
	std::cout << italic << "empty :\n" << reset;
	std::cout << "default constructor is empty ? : " << test.empty() << std::endl;
	std::cout << "range   constructor is empty ? : " << test2.empty() << std::endl;

	std::cout << italic << "size :\n" << reset;
	std::cout << "default constructor size = " << test.size() << std::endl;
	std::cout << "range   constructor size = " << test2.size() << std::endl;

	std::cout << italic << "max_size :\n" << reset;
	std::cout << "default constructor max_size = " << test.max_size() << std::endl;


	std::cout << red << bold << "modifiers  :"<< std::endl << reset;
	std::cout << italic << "insert one element :\n" << reset;
	ft::pair<ft::set<int>::iterator, bool> ins1 =  test.insert(4);
	std::cout << "insertion reussite : " << ins1.second << ", val = " << *(ins1.first) << std::endl;
	ft::pair<ft::set<int>::iterator, bool> ins2 =  test.insert(1);
	std::cout << "insertion reussite : " << ins2.second << ", val = " << *(ins2.first) << std::endl;

	std::cout << std::endl << italic << "insert with hint :\n" << reset;
	test.insert(test.begin(), 10);
	test.insert(test.begin(), 20);
	test.insert(test.begin(), 1);
	print_set(test);

	ft::set<int> test4;
	test4.insert(5);
	test4.insert(6);
	test4.insert(7);
	test4.insert(2);
	
	std::cout << std::endl << italic << "insert range element :\n" << reset;
	test.insert(test4.rbegin(), test4.rend());
	print_set(test);
	std::cout << "size = " << test.size() << std::endl;

	std::cout << std::endl << italic << "erase iterator :\n" << reset;
	std::cout << "erase test.begin() " << std::endl;
	test.erase(test.begin());
	print_set(test);
	std::cout << std::endl << italic << "erase val:\n" << reset;
	std::cout << "erase 2" << std::endl;
	test.erase(2);
	print_set(test);
	std::cout << std::endl << italic << "erase range :\n" << reset;
	std::cout << "erase iterator range (test.end - 2 a test.end)" << std::endl;
	test.erase(--(--test.end()), test.end());
	print_set(test);
	std::cout << "size = " << test.size() << std::endl;

	std::cout << std::endl << italic << "swap :\n" << reset;
	std::cout << "set 1 :" << std::endl;
	print_set(test);
	std::cout << "set 2 :" << std::endl;
	print_set(test4);
	test.swap(test4);
	std::cout << "\nset 1 :" << std::endl;
	print_set(test);
	std::cout << "set 2 :" << std::endl;
	print_set(test4);

	std::cout << std::endl << italic << "clear set1 :\n" << reset;
	test.clear();
	std::cout << "size = " << test.size() << std::endl;

	std::cout << red << bold << "\nobservers :" << std::endl << reset;
	std::cout << std::endl << italic << "key_comp() && value_comp() :\n" << reset;
	ft::set<int>::key_compare comp = test4.key_comp();
	std::cout << "1 < 2 ? " << comp(1, 2) << std::endl;
	std::cout << "2 < 1 ? " << comp(2, 1) << std::endl;

	std::cout << red << bold << "\noperations :" << std::endl << reset;
	std::cout << "find 4 ? " << (test4.find(4) != test4.end()) << std::endl;
	std::cout << "find 2 ? " << (test4.find(2) != test4.end()) << std::endl;
	std::cout << std::endl;
	std::cout << "count 4 ? " << test4.count(4) << std::endl;
	std::cout << "count 2 ? " << test4.count(2) << std::endl;

	ft::set<int>::iterator last = test4.end();

	std::cout << "\nlower bound from 3 " << std::endl;
	ft::set<int>::iterator first = test4.lower_bound(3);
	while (first != last)
	{
		std::cout << *first << " " << std::endl;
		++first;
	}
	std::cout << "\nupper bound from 4 " << std::endl;
	first = test4.upper_bound(4);
	while (first != last)
	{
		std::cout << *first << " " << std::endl;
		++first;
	}

	std::cout << "\nequal range : 3 " << std::endl;
	ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> eq = test4.equal_range(3);
	std::cout << "\"deux\" before :" << *(eq.first) << " -> " << *(eq.first) << std::endl;
	std::cout << "\"deux\" after  :" << *(eq.second) << " -> " << *(eq.second) << std::endl;
	
	std::cout << "\nequal range : 4 " << std::endl;
	ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> eq2 = test4.equal_range(4);
	std::cout << "\"deux\" before :" << *(eq2.first) << " " << std::endl;
	std::cout << "\"deux\" after  :" << *(eq2.second) << " " << std::endl;

	std::cout << std::endl << red << bold << "COMPARAISONS :" << std::endl << reset;
	ft::set<int> set1;
	ft::set<int> set2;

	set1.insert(2);
	set1.insert(12);

	set2.insert(2);
	set2.insert(10);

	
	std::cout << "set1 = \n";
	print_set(set1);
	std::cout << "set2 = \n";
	print_set(set2);

	print_comparisons(set1, set2);

	set2 = set1;
	
	std::cout << std::endl << "set1 = \n";
	print_set(set1);
	std::cout << "set2 = \n";
	print_set(set2);
	print_comparisons(set1,set2);
	
	return 0;
}