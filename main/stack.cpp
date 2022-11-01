/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:10:20 by lcalvie           #+#    #+#             */
/*   Updated: 2022/11/01 17:06:08 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* <------------------------> VECTOR FROM STD OR FT <------------------------> */

#if REAL
	# include <stack>
	namespace ft = std;
#else
	# include "../includes/stack.hpp"
#endif

/* <-------------------------------------------------------------------------> */

#include <iostream>
#include "../other/color.hpp"

template <typename T>
void	print_comparisons(ft::stack<T> &stack1, ft::stack<T> &stack2)
{
	std::cout << red << italic;

	if (stack1 == stack2)
		std::cout << "stack1 == stack2" << std::endl;
	if (stack1 != stack2)
		std::cout << "stack1 != stack2" << std::endl;
	if (stack1 < stack2)
		std::cout << "stack1 < stack2" << std::endl;
	if (stack1 <= stack2)
		std::cout << "stack1 <= stack2" << std::endl;
	if (stack1 > stack2)
		std::cout << "stack1 > stack2" << std::endl;
	if (stack1 >= stack2)
		std::cout << "stack1 >= stack2" << std::endl;

	std::cout << reset;
}

int main()
{
	ft::stack<int> stk;
	std::cout << red << bold << "empty stack created" << std::endl << reset;
	
	std::cout << "push(1)" << std::endl;
	std::cout << "push(2)" << std::endl;
	std::cout << "push(3)" << std::endl;
	stk.push(1);
	stk.push(2);
	stk.push(3);

	ft::stack<int> copy(stk);
	std::cout << red << bold << "copy created" << std::endl << reset;

	
	std::cout << "copy.push(4)" << std::endl;
	std::cout << "copy.push(5)" << std::endl;
	copy.push(4);
	copy.push(5);

	std::cout << std::endl;
	std::cout << "stk.size = " << stk.size() << std::endl;
	std::cout << "copy.size = " << copy.size() << std::endl;

	std::cout << std::endl;
	std::cout << "stk.top = " << stk.top() << std::endl;
	std::cout << "copy.top = " << copy.top() << std::endl;

	std::cout << std::endl;
	std::cout << "COMPARAISONS : " << std::endl;
	print_comparisons(stk, copy);

	std::cout << std::endl;
	std::cout << "pop()" << std::endl;
	std::cout << "pop()" << std::endl;
	std::cout << "pop()" << std::endl;

	stk.pop();
	stk.pop();
	stk.pop();
	copy.pop();
	copy.pop();
	copy.pop();

	std::cout << std::endl << std::boolalpha;
	std::cout << "stk.empty = " << stk.empty() << std::endl;
	std::cout << "copy.empty = " << copy.empty() << std::endl;
	
	return 0;
}
