/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 11:09:38 by lcalvie           #+#    #+#             */
/*   Updated: 2022/11/01 17:06:00 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* <------------------------> VECTOR FROM STD OR FT <------------------------> */

#if REAL
	# include <map>
	namespace ft = std;
#else
	# include "../includes/map.hpp"
	# include "../other/pair.hpp"
#endif

/* <-------------------------------------------------------------------------> */

#include <iostream>
#include <string>
#include "../other/color.hpp"
#include <vector>

template <typename T>
void print_map(T &m)
{
	typename T::iterator start = m.begin();
	typename T::iterator finish = m.end();

	while (start != finish)
	{
		std::cout << " -  " << (*start).first << " -> " << (*start).second << std::endl;
		++start;
	}
}

template< class Key, class T, class Compare, class Alloc >
void	print_comparisons(ft::map<Key,T,Compare,Alloc> &map1, ft::map<Key,T,Compare,Alloc> &map2)
{
	std::cout << red << italic;

	if (map1 == map2)
		std::cout << "map1 == map2" << std::endl;
	if (map1 != map2)
		std::cout << "map1 != map2" << std::endl;
	if (map1 < map2)
		std::cout << "map1 < map2" << std::endl;
	if (map1 <= map2)
		std::cout << "map1 <= map2" << std::endl;
	if (map1 > map2)
		std::cout << "map1 > map2" << std::endl;
	if (map1 >= map2)
		std::cout << "map1 >= map2" << std::endl;

	std::cout << reset;
}

int main()
{
	std::cout << italic << "Library used : "<< (REAL ? "std" : "ft") << std::endl << std::endl << reset;
	std::cout << std::boolalpha;


	std::cout << red << bold << "Constructors :" << std::endl << reset;

	std::cout << italic << "default constructor :\n" << reset;
	ft::map<std::string, int> test;
	print_map(test);
	std::cout << std::endl;

	std::vector<ft::pair<std::string, std::string> > temp_vec;
	temp_vec.push_back(ft::make_pair("lcalvie    ", "METTEZ MOI 125 SVP"));
	temp_vec.push_back(ft::make_pair("correcteur1", "QUEL FLOW !"));
	temp_vec.push_back(ft::make_pair("correcteur2", "UN MEC TROP FORT"));
	temp_vec.push_back(ft::make_pair("correcteur3", "LE + SYMPA DES CORRECTEURS"));
	std::cout << italic << "range constructor :\n" << reset;
	ft::map<std::string, std::string> test2(temp_vec.begin(), temp_vec.end());
	print_map(test2);
	std::cout << std::endl;

	std::cout << italic << " copy constructor :\n" << reset;
	ft::map<std::string, std::string> test3(test2);
	print_map(test3);
	std::cout << std::endl;

	std::cout << italic << " assignment operator :\n" << reset;
	test2 = test3;
	print_map(test2);
	std::cout << std::endl;


	
	std::cout << red << bold << "iterators :" << std::endl << reset;

	ft::map<std::string, std::string>::iterator start = test2.begin();
	ft::map<std::string, std::string>::iterator finish = test2.end();

	while (start != finish)
	{
		std::cout << " -  " << (*start).first << " -> " << (*start).second << std::endl;
		++start;
		--start;
		start++;
		start--;
		++start;
	}

	std::cout << red << bold << "reverse iterators :" << std::endl << reset;

	ft::map<std::string, std::string>::reverse_iterator start2 = test2.rbegin();
	ft::map<std::string, std::string>::reverse_iterator finish2 = test2.rend();

	while (start2 != finish2)
	{
		std::cout << " -  " << (*start2).first << " -> " << (*start2).second << std::endl;
		++start2;
		--start2;
		start2++;
		start2--;
		++start2;
	}

	std::cout << red << bold << "capacity  :"<< std::endl << reset;
	std::cout << italic << "empty :\n" << reset;
	std::cout << "default constructor is empty ? : " << test.empty() << std::endl;
	std::cout << "range   constructor is empty ? : " << test2.empty() << std::endl;

	std::cout << italic << "size :\n" << reset;
	std::cout << "default constructor size = " << test.size() << std::endl;
	std::cout << "range   constructor size = " << test2.size() << std::endl;

	std::cout << italic << "max_size :\n" << reset;
	std::cout << "default constructor max_size = " << test.max_size() << std::endl;

	test["un"] = 1;
	test["deux"] = 2;
	test["trois"] = 3;

	std::cout << red << bold << "element access  :"<< std::endl << reset;
	std::cout << "test[\"un\"] = " << test["un"] << std::endl;
	std::cout << "test[\"deux\"] = " << test["deux"] << std::endl;
	std::cout << "test[\"trois\"] = " << test["trois"] << std::endl;

	std::cout << red << bold << "modifiers  :"<< std::endl << reset;
	std::cout << italic << "insert one element :\n" << reset;
	ft::pair<ft::map<std::string, int>::iterator, bool> ins1 =  test.insert(ft::pair<std::string, int>((std::string) "a", 1));
	std::cout << "insertion reussite : " << ins1.second << ", key = " << (*(ins1.first)).first << " value = " << (*(ins1.first)).second << std::endl;
	ft::pair<ft::map<std::string, int>::iterator, bool> ins2 =  test.insert(ft::pair<std::string, int>((std::string) "a", 10));
	std::cout << "insertion reussite : " << ins2.second << ", key = " << (*(ins2.first)).first << " value = " << (*(ins2.first)).second << std::endl;
	ft::pair<ft::map<std::string, int>::iterator, bool> ins3 =  test.insert(ft::pair<std::string, int>((std::string) "b", 2));
	std::cout << "insertion reussite : " << ins3.second << ", key = " << (*(ins3.first)).first << " value = " << (*(ins3.first)).second << std::endl;
	ft::pair<ft::map<std::string, int>::iterator, bool> ins4 =  test.insert(ft::pair<std::string, int>((std::string) "b", 20)); 
	std::cout << "insertion reussite : " << ins4.second << ", key = " << (*(ins4.first)).first << " value = " << (*(ins4.first)).second << std::endl;

	std::cout << std::endl << italic << "insert with hint :\n" << reset;
	test.insert(test.begin(), ft::pair<std::string, int>((std::string) "aa", 10));
	test.insert(test.begin(), ft::pair<std::string, int>((std::string) "z", 20));
	print_map(test);

	ft::map<std::string, int> test4;
	test4["sens de la vie "] = 42;
	test4["meilleur eccole "] = 42;
	test4["sept fois six "] = 42;
	
	std::cout << std::endl << italic << "insert range element :\n" << reset;
	test.insert(test4.rbegin(), test4.rend());
	print_map(test);
	std::cout << "size = " << test.size() << std::endl;

	std::cout << std::endl << italic << "erase iterator :\n" << reset;
	std::cout << "erase test.begin() " << std::endl;
	test.erase(test.begin());
	print_map(test);
	std::cout << std::endl << italic << "erase key :\n" << reset;
	std::cout << "erase \"z\"" << std::endl;
	test.erase("z");
	print_map(test);
	std::cout << std::endl << italic << "erase key :\n" << reset;
	std::cout << "erase iterator range (test.end - 2 a test.end)" << std::endl;
	test.erase(--(--test.end()), test.end());
	print_map(test);
	std::cout << "size = " << test.size() << std::endl;

	std::cout << std::endl << italic << "swap :\n" << reset;
	std::cout << "map 1 :" << std::endl;
	print_map(test);
	std::cout << "map 2 :" << std::endl;
	print_map(test4);
	test.swap(test4);
	std::cout << "\nmap 1 :" << std::endl;
	print_map(test);
	std::cout << "map 2 :" << std::endl;
	print_map(test4);

	std::cout << std::endl << italic << "clear map1 :\n" << reset;
	test.clear();
	std::cout << "size = " << test.size() << std::endl;

	std::cout << red << bold << "\nobservers :" << std::endl << reset;
	std::cout << std::endl << italic << "key_comp() :\n" << reset;
	ft::map<std::string, int>::key_compare comp = test4.key_comp();
	std::cout << "a < z ? " << comp("a","z") << std::endl;
	std::cout << "z < a ? " << comp("z","a") << std::endl;

	std::cout << std::endl << italic << "value_comp() :\n" << reset;
	ft::map<std::string, int>::value_compare comp2 = test4.value_comp();
	std::cout << "a < z ? " << comp2(ft::pair<std::string, int>("a",2), ft::pair<std::string, int>("z",1)) << std::endl;
	std::cout << "z < a ? " << comp2(ft::pair<std::string, int>("z",2), ft::pair<std::string, int>("a",1)) << std::endl;

	std::cout << red << bold << "\noperations :" << std::endl << reset;
	std::cout << "find \"aa\" ? " << (test4.find("aa") != test4.end()) << std::endl;
	std::cout << "find \"aaa\" ? " << (test4.find("aaa") != test4.end()) << std::endl;
	std::cout << std::endl;
	std::cout << "count \"aa\" ? " << test4.count("aa") << std::endl;
	std::cout << "count \"aaa\" ? " << test4.count("aaa") << std::endl;

	ft::map<std::string, int>::iterator last = test4.end();

	std::cout << "\nlower bound from \"deux\" " << std::endl;
	ft::map<std::string, int>::iterator first = test4.lower_bound("deux");
	while (first != last)
	{
		std::cout << " -  " << (*first).first << " -> " << (*first).second << std::endl;
		++first;
	}
	std::cout << "\nupper bound from \"deux\" " << std::endl;
	first = test4.upper_bound("deux");
	while (first != last)
	{
		std::cout << " -  " << (*first).first << " -> " << (*first).second << std::endl;
		++first;
	}

	std::cout << "\nequal range : \"deux\" " << std::endl;
	ft::pair<ft::map<std::string, int>::iterator, ft::map<std::string, int>::iterator> eq = test4.equal_range("deux");
	std::cout << "\"deux\" before :" << (*(eq.first)).first << " -> " << (*(eq.first)).second << std::endl;
	std::cout << "\"deux\" after  :" << (*(eq.second)).first << " -> " << (*(eq.second)).second << std::endl;
	
	std::cout << "\nequal range : \"c\" " << std::endl;
	ft::pair<ft::map<std::string, int>::iterator, ft::map<std::string, int>::iterator> eq2 = test4.equal_range("c");
	std::cout << "\"deux\" before :" << (*(eq2.first)).first << " -> " << (*(eq2.first)).second << std::endl;
	std::cout << "\"deux\" after  :" << (*(eq2.second)).first << " -> " << (*(eq2.second)).second << std::endl;

	std::cout << std::endl << red << bold << "COMPARAISONS :" << std::endl << reset;
	ft::map<int, int> map1;
	ft::map<int, int> map2;

	map1[1] = 2;
	map1[2] = 42;

	map2[1] = 2;
	map2[2] = 40;

	
	std::cout << "map1 = \n";
	print_map(map1);
	std::cout << "map2 = \n";
	print_map(map2);

	print_comparisons(map1, map2);

	map2 = map1;
	
	std::cout << std::endl << "map1 = \n";
	print_map(map1);
	std::cout << "map2 = \n";
	print_map(map2);
	print_comparisons(map1,map2);
	
	return 0;
}