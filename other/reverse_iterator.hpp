#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "iterators_traits.hpp"
# include <memory>

namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
		public :
			typedef Iter iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer pointer;
			typedef typename ft::iterator_traits<Iter>::reference reference;
		
			//CONSTRUCTOR
			reverse_iterator() : _itr(0) {}

			explicit reverse_iterator(iterator_type x) : _itr(x) {}

			template< class U >
			reverse_iterator(const reverse_iterator<U>& other) : _itr(other.base()) {}

			template< class U >
			reverse_iterator& operator=(const reverse_iterator<U>& other)
			{
				_itr = other.base();
				return (*this);
			}
		
			// MEMBER FUNCTIONS

			iterator_type base() const {return(_itr);};

			reference operator*() const {iterator_type tmp = _itr; return *--tmp;};

			pointer operator->() const  {iterator_type tmp = _itr;--tmp;return (tmp.operator->());};

			reference operator[]( difference_type n ) const {return (_itr[-n-1]);};

			reverse_iterator &operator++() {--_itr;return(*this);};
			reverse_iterator operator++(int) {reverse_iterator save = *this;--_itr;return(save);};

			reverse_iterator &operator--() {++_itr;return(*this);};
			reverse_iterator operator--(int) {reverse_iterator save = *this;++_itr;return(save);};

			reverse_iterator operator+( difference_type n ) const {reverse_iterator save = *this;save._itr-=n;return(save);};
			reverse_iterator operator-( difference_type n ) const {reverse_iterator save = *this;save._itr+=n;return(save);};

			reverse_iterator& operator+=( difference_type n ) {_itr-=n;return (*this);};
			reverse_iterator& operator-=( difference_type n ) {_itr+=n;return (*this);};

			// CONVERSION TO NON-CONST

			//operator Iter() const {return _itr;};

		protected :
			iterator_type _itr;
	};

	// NON-MEMBER FUNCTIONS

	template< class Iter >
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it )
	{
		return reverse_iterator<Iter>(it.base() - n);
	}

	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
	{
		return -(lhs.base() - rhs.base());
	}

	template <template<class> class Iterator, class U>
	typename reverse_iterator<Iterator<U> >::difference_type operator-( const reverse_iterator<Iterator<const U> >& lhs, const reverse_iterator<Iterator<U> >& rhs )
	{
		return -(lhs.base() - rhs.base());
	}

	template <template<class> class Iterator, class U>
	typename reverse_iterator<Iterator<U> >::difference_type operator-( const reverse_iterator<Iterator<U> >& lhs, const reverse_iterator<Iterator<const U> >& rhs )
	{
		return -(lhs.base() - rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

}

# endif