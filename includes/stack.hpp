#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

//DEBUG
#include "iostream"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public :
		//TYPEDEF
		typedef	T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		//CONSTRUCTOR
		explicit stack (const container_type& ctnr = container_type()) : _cntr(ctnr) {};
		stack( const stack& copy ) : _cntr(copy._cntr) {};

		//ASSIGNEMENT OPERATOR
		stack& operator=( const stack& copy )
		{
			_cntr = copy._cntr;
			return (*this);
		}

		//EMPTY
		bool empty() const {return _cntr.empty();};
		
		//SIZE
		size_type size() const {return _cntr.size();};

		//TOP
		value_type& top() {return _cntr.back();};
		const value_type& top() const {return _cntr.back();};

		//PUSH
		void push (const value_type& val) {_cntr.push_back(val);};

		//POP
		void pop() {_cntr.pop_back();};

		//OPERATORS
		friend bool operator== (const stack& lhs, const stack& rhs) {return (lhs._cntr == rhs._cntr);};

		friend bool operator!= (const stack& lhs, const stack& rhs) {return (lhs._cntr != rhs._cntr);};


		friend bool operator<  (const stack& lhs, const stack& rhs) {return (lhs._cntr <  rhs._cntr);};


		friend bool operator<= (const stack& lhs, const stack& rhs) {return (lhs._cntr <= rhs._cntr);};


		friend bool operator>  (const stack& lhs, const stack& rhs) {return (lhs._cntr >  rhs._cntr);};


		friend bool operator>= (const stack& lhs, const stack& rhs) {return (lhs._cntr >= rhs._cntr);};

		private :
			container_type _cntr;
	};

}

#endif