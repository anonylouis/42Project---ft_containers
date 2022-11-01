#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <sstream>

#include "../other/enable_if.hpp"
#include "../other/is_integral.hpp"
#include "../other/reverse_iterator.hpp"
#include "../other/iterator.hpp"
#include "../other/equal.hpp"
#include "../other/lexicographical_compare.hpp"

//debug 
#include <iostream>
#include "../other/color.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public :

			template <class U>
			class vector_iterator
			{
				public :
					typedef U value_type;
					typedef ptrdiff_t difference_type;
					typedef U* pointer;
					typedef U& reference;
					typedef std::random_access_iterator_tag iterator_category;

					// CONSTRUCTOR DESTRUCTOR
					vector_iterator(pointer itr = 0) : _ptr(itr) {};
					vector_iterator(vector_iterator const& copy) : _ptr(copy._ptr) {};

					vector_iterator &operator=(vector_iterator const& copy)
					{
						_ptr = copy._ptr;
						return *this;
					};

					~vector_iterator() {};

					// MEMBER FUNCTIONS

					reference operator*() const {return *_ptr;};
					pointer operator->() const {return _ptr;};
					reference operator[](difference_type n) const {return _ptr[n];};

					vector_iterator &operator++() {_ptr++;return *this;};
					vector_iterator operator++(int) {vector_iterator save(*this);_ptr++;return save;};

					vector_iterator &operator--() {_ptr--;return *this;};
					vector_iterator operator--(int) {vector_iterator save(*this);_ptr--;return save;};

					vector_iterator operator-(difference_type n) const {vector_iterator save(*this);save._ptr -= n;return (save);};
					
					vector_iterator &operator+=(difference_type n) {_ptr += n;return (*this);};
					vector_iterator &operator-=(difference_type n) {_ptr -= n;return (*this);};

					difference_type operator-(vector_iterator const& b) const {return (_ptr - b._ptr);};

					// NON-MEMBER FUNCTIONS (keyword friend)

					friend bool operator== (vector_iterator const& a, vector_iterator const& b) {return a._ptr == b._ptr;};
					friend bool operator!= (vector_iterator const& a, vector_iterator const& b) {return a._ptr != b._ptr;};
					friend bool operator> (vector_iterator const& a, vector_iterator const& b) {return a._ptr > b._ptr;};
					friend bool operator>= (vector_iterator const& a, vector_iterator const& b) {return a._ptr >= b._ptr;};
					friend bool operator< (vector_iterator const& a, vector_iterator const& b) {return a._ptr < b._ptr;};
					friend bool operator<= (vector_iterator const& a, vector_iterator const& b) {return a._ptr <= b._ptr;};

					friend vector_iterator operator+(vector_iterator const& a, difference_type n) {vector_iterator save(a);save._ptr += n;return (save);};
					friend vector_iterator operator+(difference_type n, vector_iterator const& a) {vector_iterator save(a);save._ptr += n;return (save);};

					//CONVERSION TO CONST
					operator vector_iterator<const value_type>() const {return vector_iterator<const value_type>(_ptr);};

				private :
					pointer _ptr;
			};

			// TYPEDEF
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef vector_iterator<T> iterator;
			typedef vector_iterator<const T> const_iterator;
			typedef ft::reverse_iterator<iterator > reverse_iterator;
			typedef ft::reverse_iterator<const_iterator > const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

			// CONSTRUCTOR 

			explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _len(0), _first(0), _capacity(0)
			{
			}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _len(n), _capacity(n)
			{
				if (_len == 0)
					return ;
				_first = _alloc.allocate(_capacity);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&_first[i], val);
			}
			
			template <class InputIterator>
			vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				InputIterator temp = first;
				_len = 0;
				while (temp != last)
				{
					++temp;
					_len++;
				}
				_capacity = _len;
				if (_capacity == 0)
					return; 
				_first = _alloc.allocate(_capacity);
				size_type i = 0;
				while (first != last)
				{
					_alloc.construct(&_first[i], *first);
					++first;
					++i;
				}
			}

			vector(const vector& copy) : _alloc(copy._alloc), _len(copy._len), _capacity(copy._len)
			{
				if (_len == 0)
					return ;
				_first = _alloc.allocate(_len);
				for (size_type i = 0; i < _len; i++)
					_alloc.construct(&_first[i], (copy._first)[i]);
			}

			// DESTRUCTOR
			~vector()
			{
				for (size_type i = 0; i < _len; i++)
					_alloc.destroy(&_first[i]);
				if (_capacity)
					_alloc.deallocate(_first, _capacity);
			}

			// ASSIGNMENT OPERATOR
			vector& operator= (const vector& copy)
			{
				extend_capacity(copy._len);
				for (size_type i = copy._len; i < _len; i++)
					_alloc.destroy(&_first[i]);
				for (size_type i = 0; i < copy._len; i++)
				{
					if (i < _len)
						_first[i] = copy._first[i];
					else
						_alloc.construct(&_first[i], copy._first[i]);
				}
				_len = copy._len;
				return (*this);
			}

			// ITERATORS
			iterator begin()
			{
				return (iterator(_first));
			}
			const_iterator begin() const
			{
				return (const_iterator(_first));
			}
			iterator end()
			{
				return (iterator(_first + _len));
			}
			const_iterator end() const
			{
				if (_len == 0)
					return (const_iterator(_first));
				return (const_iterator(_first + _len));
			}

			// REVERSE ITERATORS
			reverse_iterator rbegin()
			{
				return (reverse_iterator((*this).end()));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator((*this).end()));
			}
			reverse_iterator rend()
			{
				return (reverse_iterator((*this).begin()));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator((*this).begin()));
			}

			//CAPACITY
			size_type size() const
			{
				return (_len);
			}
			size_type max_size() const
			{
				return (_alloc.max_size());
			}
			size_type capacity() const
			{
				return (_capacity);
			}
			bool empty() const
			{
				return (_len == 0);
			}
			void reserve (size_type n)
			{
				if (n > _alloc.max_size())
					throw std::length_error("vector::reserve");
				extend_capacity(n);
			}
			void resize (size_type n, value_type val = value_type())
			{
				if (n > _alloc.max_size())
					throw std::length_error("ft::vector::_M_fill_insert");
				extend_capacity(n);
				if (n > _len)
				{
					for (size_type i = _len; i < n; i++)
						_alloc.construct(&_first[i], val);
				}
				else
				{
					for (size_type i = n; i < _len; i++)
						_alloc.destroy(&_first[i]);
				}
				_len = n;
			}
			
			//ELEMENT ACCESS

			reference operator[]( size_type pos )
			{
				return (_first[pos]);
			}
			const_reference operator[]( size_type pos ) const
			{
				return (_first[pos]);
			}
			reference at (size_type n)
			{
				if (n >= _len)
				{
					std::stringstream ss;
					ss << "ft::vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << _len << ")";
					throw std::out_of_range(ss.str());
				}
				return (_first[n]);
			}
			const_reference at (size_type n) const
			{
				if (n >= _len)
				{
					std::stringstream ss;
					ss << "ft::vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << _len << ")";
					throw std::out_of_range(ss.str());
				}
				return (_first[n]);
			}
			reference front()
			{
				return (_first[0]);
			}
			const_reference front() const
			{
				return (_first[0]);
			}
			reference back()
			{
				return (_first[_len - 1]);
			}
			const_reference back() const
			{
				return (_first[_len - 1]);
			}

			//MODIFIERS
			template <class InputIterator>
  			void assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				size_type	save_len = _len;

				size_type d = std::distance(first, last);
				extend_capacity(d);
				
				for (size_type i = 0; i < d; i++)
				{
					if (i < save_len)
						_alloc.destroy(&_first[i]);
					_alloc.construct(&_first[i], *(first++));
				}
				for (size_type i = d; i < save_len; i++)
					_alloc.destroy(&_first[i]);
				_len = d;
			}

			void assign (size_type n, const value_type& val)
			{
				for (size_type i = 0; i < _len; i++)
					_alloc.destroy(&_first[i]);
				extend_capacity(n);
				_len = n;
				for (size_type i = 0; i < _len; i++)
					_alloc.construct(&_first[i], val);
			}

			void push_back (const value_type& val)
			{
				extend_capacity(_len + 1);
				_alloc.construct(&_first[_len], val);
				_len++;
			}

			void pop_back()
			{
				_alloc.destroy(&_first[_len - 1]);
				_len--;
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type	pos = position - this->begin();
				
				extend_capacity(_len + 1);
				_len += 1;
				
				//std::cout << "pos = " << pos << std::endl;
				for(size_type i = _len - 1; i > pos; i--) // value after pos
				{
					_alloc.construct(&_first[i], _first[i - 1]);
					_alloc.destroy(&_first[i - 1]);
				}

				_alloc.construct(&_first[pos], val); // add val at pos

				return (iterator(_first + pos));
			}
			
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;

				vector<T, Alloc>	save(*this); 
				size_type			pos = position - this->begin();

				//std::cout << "pos =" << pos << "\n";
				
				extend_capacity(_len + n);
				_len += n;
				
				for(size_type i = 0; i < n; i++) // add n * val
				{
					if (pos + i < save._len)
						_alloc.destroy(&_first[pos + i]);
					_alloc.construct(&_first[pos + i], val);
				}

				//std::cout << "post pos value !\n";

				for(size_type i = pos + n; i < _len; i++) // add value after n*val
				{
					if (i < save._len)
						_alloc.destroy(&_first[i]);
					_alloc.construct(&_first[i], save._first[i - n]);
				}
			}

			template <class InputIterator>
    			void insert (iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
			{
				size_type n = std::distance(first, last);
				
				if (n == 0)
					return ;

				vector<T, Alloc>	save(*this); 
				size_type			pos = position - this->begin();

				//std::cout << "pos =" << pos << "\n";
				
				extend_capacity(_len + n);
				_len += n;
				
				for(size_type i = 0; i < n; i++) // add n values between first and last
				{
					if (pos + i < save._len)
						_alloc.destroy(&_first[pos + i]);
					_alloc.construct(&_first[pos + i], *first);
					++first;
				}

				//std::cout << "post pos value !\n";

				for(size_type i = pos + n; i < _len; i++) // add value after n*val
				{
					if (i < save._len)
						_alloc.destroy(&_first[i]);
					_alloc.construct(&_first[i], save._first[i - n]);
				}
			}

			iterator erase (iterator position)
			{
				_len--;
				iterator end = this->end();
				iterator temp(position);
				_alloc.destroy(position.operator->());
				while (temp != end)
				{
					_alloc.construct(temp.operator->(), *(temp + 1));
					temp++;
					_alloc.destroy(temp.operator->());
				}
				return (position);
			}
			
			iterator erase (iterator first, iterator last)
			{
				iterator end = this->end();

				iterator temp(first);
				while(temp != last)
				{
					_alloc.destroy(temp.operator->());
					temp ++;
				}

				temp = first;
				size_type n = std::distance(first, last);
				_len -= n;

				while (temp+n != end)
				{
					_alloc.construct(temp.operator->(), *(temp + n));
					_alloc.destroy((temp+n).operator->());
					temp++;
				}
				return (first);
			}

			void swap (vector& x)
			{
				allocator_type	save_alloc = x._alloc;
				size_type		save_len = x._len;
				pointer			save_first = x._first;
				size_type		save_capacity = x._capacity;

				x._alloc = _alloc;
				x._len = _len;
				x._first = _first;
				x._capacity = _capacity; 

				_alloc = save_alloc;
				_len = save_len;
				_first = save_first;
				_capacity = save_capacity;
			}

			void clear()
			{
				while (_len)
				{
					_alloc.destroy(_first + _len - 1);
					_len--;
				}
			}

			allocator_type get_allocator() const
			{
				return (_alloc);
			}

		private :
			allocator_type	_alloc;
			size_type		_len;
			pointer			_first;
			size_type		_capacity;

			void extend_capacity(size_type n)
			{
				if (_capacity >= n)
					return;
				if (_capacity == 0)
				{
					_first = _alloc.allocate(n);
					_capacity = n;
					return ;
				}
				pointer		save_first = _first;
				size_type	save_capacity = _capacity;

				while (_capacity < n)
				{
					if ((_alloc.max_size() - _capacity) >= _capacity)
						_capacity *= 2;
					else
						_capacity =_alloc.max_size();
				}
				_first = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _len; i++)
					_alloc.construct(&_first[i], save_first[i]);
				for (size_type i = 0; i < _len; i++)
					_alloc.destroy(&save_first[i]);
				_alloc.deallocate(save_first, save_capacity);
			}

			void print_vector()
			{
				std::cout << red;
				for(size_t i = 0; i < _len; i++)
					std::cout << _first[i] << " ";
				std::cout << std::endl << reset;
			}

	};
		template <class T, class Alloc>
		bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		};

		template <class T, class Alloc>
		bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		};

		template <class T, class Alloc>
		bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(),lhs.end(), rhs.begin(), rhs.end()));
		};

		template <class T, class Alloc>
		bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (!(rhs < lhs));
		};

		template <class T, class Alloc>
		bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		};

		template <class T, class Alloc>
		bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
		{
			return (!(lhs < rhs));
		};
	
		template <class T, class Alloc>
  		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		};

}

#endif