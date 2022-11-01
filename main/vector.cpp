/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:33:44 by lcalvie           #+#    #+#             */
/*   Updated: 2022/11/01 17:06:16 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* <------------------------> VECTOR FROM STD OR FT <------------------------> */

#if REAL
	# include <vector>
	namespace ft = std;
#else
	# include "../includes/vector.hpp"
#endif

/* <-------------------------------------------------------------------------> */

#include <iostream>
#include "../other/color.hpp"

template <typename T>
void	print_vector(ft::vector<T> &vec)
{
	for(size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void	print_vector(ft::vector<T> &vec, typename ft::vector<T>::iterator start)
{
	typename ft::vector<T>::iterator end = vec.end();
	while (start < end)
		std::cout << *(start++) << " ";
	std::cout << std::endl;
}

template <typename T>
void	print_comparisons(ft::vector<T> &vector1, ft::vector<T> &vector2)
{
	std::cout << red << italic;

	if (vector1 == vector2)
		std::cout << "vector1 == vector2" << std::endl;
	if (vector1 != vector2)
		std::cout << "vector1 != vector2" << std::endl;
	if (vector1 < vector2)
		std::cout << "vector1 < vector2" << std::endl;
	if (vector1 <= vector2)
		std::cout << "vector1 <= vector2" << std::endl;
	if (vector1 > vector2)
		std::cout << "vector1 > vector2" << std::endl;
	if (vector1 >= vector2)
		std::cout << "vector1 >= vector2" << std::endl;

	std::cout << reset;
}

int main()
{
	std::cout << italic << "Library used : "<< (REAL ? "std" : "ft") << std::endl << std::endl << reset;

	std::cout << red << bold << "Default constructor :" << std::endl << reset;
	ft::vector<int> vector1;
	print_vector(vector1);

	std::cout << red << bold << "fill constructor :" << std::endl << reset;
	ft::vector<int> vector2(7,5);
	print_vector(vector2);
	ft::vector<int> vector3(4);
	print_vector(vector3);

	std::cout << red << bold << "range constructor :" << std::endl << reset;
	int tab[5] = {1,2,3,4,5};
	ft::vector<int> vector4(tab,tab+5);
	print_vector(vector4);

	std::cout << red << bold << "copy constructor :" << std::endl << reset;
	ft::vector<int> vector5(vector4);
	vector5[0] = 42;
	std::cout << "copy modified: ";
	print_vector(vector5);
	std::cout << "original     :  ";
	print_vector(vector4);

	std::cout << std::endl;
	std::cout << red << bold << "assignment operator :" << std::endl << reset;
	vector5 = vector2;
	vector5[0] = 42;
	std::cout << "copy modified: ";
	print_vector(vector5);
	std::cout << "original     :  ";
	print_vector(vector2);

	std::cout << std::endl << red << bold << "ITERATORS :" << std::endl << reset;
	
	ft::vector<int>::iterator it1 = vector4.begin();
	ft::vector<int>::iterator it2 = vector4.end();

	while(it1 != it2)
	{
		std::cout << *it1 << " ";
		std::cout << it1[0] << " ";
		it1++;
		it1+=1;
		it1-=1;
		it1 = --it1 + 1;
	}
	std::cout << std::endl;
	std::cout << green << "int - iterator undefined but iterator - int defined " << reset << std::endl;
	std::cout << italic << "vector size with it : " <<  vector4.end() - vector4.begin() << std::endl << reset;

	std::cout << std::endl << red << bold << "REVERSE ITERATORS :" << std::endl << reset;

	ft::vector<int>::reverse_iterator it3 = vector4.rbegin();
	ft::vector<int>::reverse_iterator it4 = vector4.rend();

	while(it3 != it4)
	{
		std::cout << *it3 << " ";
		it3++;
	}
	std::cout << std::endl;

	std::cout << std::endl << red << bold << "SIZE :" << std::endl << reset;
	std::cout << vector4.size() << std::endl;
	
	std::cout << std::endl << red << bold << "MAX SIZE :" << std::endl << reset;
	std::cout << vector4.max_size() << std::endl;

	std::cout << std::endl << red << bold << "RESERVE :" << std::endl << reset;
	print_vector(vector4);
	std::cout << "            capacity = " << vector4.capacity() << std::endl;
	vector4.reserve(4);
	std::cout << "reserve(4); capacity = " << vector4.capacity() << std::endl;
	vector4.reserve(6);
	std::cout << "reserve(6); capacity = " << vector4.capacity() << std::endl;
	vector4.reserve(10);
	std::cout << "reserve(10); capacity = " << vector4.capacity() << std::endl;
	vector4.reserve(70);
	std::cout << "reserve(70); capacity = " << vector4.capacity() << std::endl;
	try
	{
		vector4.reserve(vector4.max_size() + 1);
	}
	catch (std::exception const& e)
	{
		std::cout << yellow;
		std::cout << "EXCEPTION CATCH\n";
		std::cout << "reserve(max_capacity + 1) = " << e.what() << std::endl;
		std::cout << reset;
	}
	
	std::cout << std::endl << red << bold << "RESIZE :" << std::endl << reset;
	print_vector(vector2);
	vector2.resize(3,42);
	std::cout << "resize(3,42); capacity = " << vector2.capacity() << std::endl;
	print_vector(vector2);
	vector2.resize(7);
	std::cout << "reserve(7); capacity = " << vector2.capacity() << std::endl;
	print_vector(vector2);
	vector2.resize(14,42);
	std::cout << "reserve(14,42); capacity = " << vector2.capacity() << std::endl;
	print_vector(vector2);
	try
	{
		vector2.resize(vector2.max_size() + 1);
	}
	catch (std::exception const& e)
	{
		std::cout << yellow;
		std::cout << "EXCEPTION CATCH\n";
		std::cout << "resize(max_capacity + 1) = " << e.what() << std::endl;
		std::cout << reset;
	}

	std::cout << std::endl << red << bold << "AT ACCESS:" << std::endl << reset;
	for(size_t i = 0; i < vector4.size(); i++)
		std::cout << vector4.at(i) << " ";
	std::cout << std::endl;
	try
	{
		vector4.at(vector4.size());
	}
	catch (std::exception const& e)
	{
		std::cout << yellow;
		std::cout << "EXCEPTION CATCH\n";
		std::cout << "v.at(v.size()) = " << e.what() << std::endl;
		std::cout << reset;
	}

	try
	{
		vector4.at(vector4.size()+10);
	}
	catch (std::exception const& e)
	{
		std::cout << yellow;
		std::cout << "EXCEPTION CATCH\n";
		std::cout << "v.at(v.size()+10) = " << e.what() << std::endl;
		std::cout << reset;
	}

	std::cout << std::endl << red << bold << "FRONT & BACK ELEMENT:" << std::endl << reset;
	print_vector(vector2);
	std::cout << underline << "front = " << vector2.front() << ", back = " << vector2.back() << std::endl << reset;
	print_vector(vector3);
	std::cout << underline << "front = " << vector3.front() << ", back = " << vector3.back() << std::endl << reset;
	print_vector(vector4);
	std::cout << underline << "front = " << vector4.front() << ", back = " << vector4.back() << std::endl << reset;

	std::cout << std::endl << red << bold << "ASSIGN :" << std::endl << reset;
	vector3.reserve(42);
	print_vector(vector3);
	std::cout << "capacity = " << vector3.capacity() << std::endl;
	vector3.assign(8, 10);
	std::cout << "assign(8,10)" << std::endl;
	print_vector(vector3);
	std::cout << "capacity = " << vector3.capacity() << std::endl;
	std::cout << "----- vector 5  -----" << std::endl;
	vector5[2] = -3;
	vector5[5] = 7;
	print_vector(vector5);
	std::cout << "vector3.assign(vector5.begin(), vector5.end() - 1)" << std::endl;
	vector3.assign(vector5.begin(), vector5.end() - 1);
	print_vector(vector3);
	std::cout << "capacity = " << vector3.capacity() << std::endl;

	std::cout << std::endl << red << bold << "PUSH_BACK & POP_BACK :" << std::endl << reset;
	std::cout << green << "pop_back on empty vector = segfault" << std::endl << reset;
	//vector1.pop_back();
	vector1.push_back(6);
	std::cout << "vector1.push_back(6)" << std::endl;
	std::cout << "vector = ";
	print_vector(vector1);
	vector1.push_back(5);
	std::cout << "vector1.push_back(5)" << std::endl;
	std::cout << "vector = ";
	print_vector(vector1);
	vector1.push_back(3);
	vector1.push_back(5);
	std::cout << "vector1.push_back(3)" << std::endl;
	std::cout << "vector1.push_back(5)" << std::endl;
	std::cout << "vector = ";
	print_vector(vector1);
	vector1.push_back(30);
	std::cout << "vector1.push_back(30)" << std::endl;
	std::cout << "vector = ";
	print_vector(vector1);
	vector1.pop_back();
	std::cout << "vector1.pop_back()" << std::endl;
	std::cout << "vector = ";
	print_vector(vector1);
	vector1.pop_back();
	std::cout << "vector1.pop_back()" << std::endl;
	std::cout << "vector = ";
	print_vector(vector1);

	std::cout << std::endl << red << bold << "INSERT :" << std::endl << reset;

	std::cout << green << "insert a val without reallocate" << std::endl << reset;
	std::cout << "vector1.insert(vector1.begin(), 7)" << std::endl;
	std::cout << "vector1.insert(vector1.end() - 1, 4)" << std::endl;
	vector1.insert(vector1.begin(), 7);
	vector1.insert(vector1.end() - 1, 4);
	print_vector(vector1);
	std::cout << "capacity = " << vector1.capacity() << " (len=" << vector1.size() << ")" << std::endl;

	std::cout << green << "insert fill val without reallocate" << std::endl << reset;
	std::cout << "vector1.insert(vector1.begin() + 2 , 2 ,99);" << std::endl;
	vector1.insert(vector1.begin() + 2 , 2 ,99);
	print_vector(vector1);
	std::cout << "capacity = " << vector1.capacity() << " (len=" << vector1.size() << ")" << std::endl;

	std::cout << green << "insert fill val with reallocate" << std::endl << reset;
	std::cout << "vector1.insert(vector1.end(), 11, 42)" << std::endl;
	vector1.insert(vector1.end(), 9 ,42);
	print_vector(vector1);
	std::cout << "capacity = " << vector1.capacity() << " (len=" << vector1.size() << ")" << std::endl;

	std::cout << green << "insert a val with reallocate" << std::endl << reset;
	vector1.insert(vector1.end() - 11, 41);
	std::cout << "vector1.insert(vector1.end() - 10, 41);" << std::endl;
	print_vector(vector1);
	std::cout << "capacity = " << vector1.capacity() << " (len=" << vector1.size() << ")" << std::endl;

	std::cout << green << "insert input range without reallocate" << std::endl << reset;
	vector1.insert(vector1.begin(),vector1.begin(), vector1.begin() + 15);
	std::cout << "vector1.insert(vector1.begin(),vector1.begin(), vector1.begin() + 15);" << std::endl;
	print_vector(vector1);
	std::cout << "capacity = " << vector1.capacity() << " (len=" << vector1.size() << ")" << std::endl;

	std::cout << green << "insert input range with allocate" << std::endl << reset;
	vector1.insert(vector1.begin() + 1,vector2.begin(), vector2.end());
	std::cout << "vector1.insert(vector1.begin() + 1,vector2.begin(), vector2.end());" << std::endl;
	print_vector(vector1);
	std::cout << "capacity = " << vector1.capacity() << " (len=" << vector1.size() << ")" << std::endl;

	std::cout << std::endl << red << bold << "ERASE :" << std::endl << reset;
	std::cout << green << "erase at vector end = segfault" << std::endl << std::endl << reset;
	//vector1.erase(vector1.end());
	
	std::cout << green << "erase single val" << std::endl << reset;

	
	std::cout << "-- vector1.erase(vector1.begin())" << std::endl;
	std::cout << "since function return value = ";
	print_vector(vector1, vector1.erase(vector1.begin()));
	std::cout << "since beginning             = ";
	print_vector(vector1);

	std::cout << "-- vector1.erase(vector1.end() - 1)" << std::endl;
	std::cout << "since function return value = ";
	print_vector(vector1, vector1.erase(vector1.end() - 1));
	std::cout << "since beginning             = ";
	print_vector(vector1);

	std::cout << "-- vector1.erase(vector1.begin() + 14)" << std::endl;
	std::cout << "since function return value = ";
	print_vector(vector1, vector1.erase(vector1.begin() + 14));
	std::cout << "since beginning             = ";
	print_vector(vector1);

	std::cout << green << "erase range val" << std::endl << reset;

	std::cout << "-- vector1.erase(vector1.begin(), vector1.begin() + 30)" << std::endl;
	std::cout << "since function return value = ";
	print_vector(vector1, vector1.erase(vector1.begin(), vector1.begin() + 30));
	std::cout << "since beginning             = ";
	print_vector(vector1);

	std::cout << "-- vector1.erase(vector1.end() - 7, vector1.end())" << std::endl;
	std::cout << "since function return value = ";
	print_vector(vector1, vector1.erase(vector1.end() - 7, vector1.end()));
	std::cout << "since beginning             = ";
	print_vector(vector1);

	std::cout << std::endl << red << bold << "SWAP :" << std::endl << reset;
	it1 = vector1.begin();
	it2 = vector1.end();

	std:: cout << "vector1 = ";
	print_vector(vector1);
	std:: cout << "vector4 = ";
	print_vector(vector4);
	std:: cout <<"vector1.swap(vector4);" << std::endl;
	vector1.swap(vector4);
	std:: cout << "vector1 = ";
	print_vector(vector1);
	std:: cout << "vector4 = ";

	while(it1 != it2)
	{
		std::cout << *it1 << " ";
		it1++;
	}
	std::cout << std::endl;

	std::cout << "re-swap with non member-function : " << std::endl;
	std:: cout <<"ft::swap(vector1, vector4);" << std::endl;
	ft::swap(vector1, vector4);
	std:: cout << "vector1 = ";
	print_vector(vector1);
	std:: cout << "vector4 = ";
	print_vector(vector4);

	std::cout << std::endl << red << bold << "CLEAR :" << std::endl << reset;
	std:: cout << "vector1 = ";
	print_vector(vector1);
	std:: cout <<"vector1.clear();" << std::endl;
	vector1.clear();
	std:: cout << "vector1 = ";
	print_vector(vector1);

	std::cout << std::endl << red << bold << "GET_ALLOCATOR :" << std::endl << reset;

	ft::vector<int>::pointer alloc = vector4.get_allocator().allocate(5);
	for (int i=0; i<5; i++) vector4.get_allocator().construct(&alloc[i],i);
	std::cout << "The allocated array contains:";
	for (int i=0; i<5; i++) std::cout << ' ' << alloc[i];
	std::cout << std::endl;
	for (int i=0; i<5; i++) vector4.get_allocator().destroy(&alloc[i]);
  	vector4.get_allocator().deallocate(alloc,5);
	
	std::cout << std::endl << red << bold << "OPERATIONS :" << std::endl << reset;
	int tab1[] = {1,2,3,4,5};
	int tab2[] = {1,2,3,4,6};
	vector1.assign(tab1, tab1 + 5);
	vector2.assign(tab2, tab2 + 5);
	std::cout << "vector1 = ";
	print_vector(vector1);
	std::cout << "vector2 = ";
	print_vector(vector2);

	print_comparisons(vector1, vector2);

	vector2 = vector1;
	
	std::cout << std::endl << "vector1 = ";
	print_vector(vector1);
	std::cout << "vector2 = ";
	print_vector(vector2);
	print_comparisons(vector1,vector2);
	
	ft::vector<std::string> test1;
	test1.insert(test1.begin(), 0, "lol");
}