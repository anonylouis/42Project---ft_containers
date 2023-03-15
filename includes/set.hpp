#ifndef SET_HPP
# define SET_HPP

#include <functional>
#include <memory>
# include "../other/RBT_set.hpp"
# include "../other/pair.hpp"
# include "../other/reverse_iterator.hpp"
# include "../other/lexicographical_compare.hpp"
# include "../other/equal.hpp"

#include "../other/color.hpp"
#include <iostream>


namespace ft
{
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public :

			//U = T = value_type
			//M = node
			template <class U, class N>
			class set_iterator
			{
				public :
					typedef U value_type;
					typedef ptrdiff_t difference_type;
					typedef U* pointer;
					typedef U& reference;
					typedef std::bidirectional_iterator_tag iterator_category;

					// CONSTRUCTOR DESTRUCTOR
					set_iterator(N *itr = 0) : _ptr(itr) {};
					set_iterator(set_iterator const& copy) : _ptr(copy._ptr) {};

					set_iterator &operator=(set_iterator const& copy)
					{
						_ptr = copy._ptr;
						return *this;
					};

					~set_iterator() {};

					// MEMBER FUNCTIONS

					reference operator*() const {return *(_ptr->get_ptr_data());};
					pointer operator->() const {return _ptr->get_ptr_data();};

					set_iterator &operator++()
					{
						if (_ptr->get_ptr_data() == 0)
						{
							if (_ptr->get_father() == 0 || _ptr->get_father()->get_right() == _ptr)
								return *this;
						}
						if (_ptr->get_right() != 0)
						{
							_ptr = _ptr->get_right();
							while (_ptr->get_left() != 0)
								_ptr = _ptr->get_left();
						}
						else if (_ptr->get_father()->get_left() ==_ptr)
							_ptr = _ptr->get_father();
						else
						{
							while (_ptr->get_father()->get_right() ==_ptr)
								_ptr = _ptr->get_father();
							_ptr = _ptr->get_father();
						}
						return *this;  
					};

					set_iterator operator++(int) {set_iterator save(*this);++(*this);return save;};

					set_iterator &operator--() 
					{
						if (_ptr->get_ptr_data() == 0)
						{
							if (_ptr->get_father() == 0 || _ptr->get_father()->get_left() == _ptr)
								return *this;
						}
						if (_ptr->get_left() != 0)
						{
							_ptr = _ptr->get_left();
							while (_ptr->get_right() != 0)
								_ptr = _ptr->get_right();
						}
						else if (_ptr->get_father()->get_right() ==_ptr)
							_ptr = _ptr->get_father();
						else
						{
							while (_ptr->get_father()->get_left() ==_ptr)
								_ptr = _ptr->get_father();
							_ptr = _ptr->get_father();
						}
						return *this;
					};

					set_iterator operator--(int) {set_iterator save(*this);--(*this);return save;};

					// NON-MEMBER FUNCTIONS (keyword friend)

					friend bool operator== (set_iterator const& a, set_iterator const& b) {return a._ptr == b._ptr;};
					friend bool operator!= (set_iterator const& a, set_iterator const& b) {return a._ptr != b._ptr;};

					//CONVERSION TO CONST
					operator set_iterator<const value_type, N>() const {return set_iterator<const value_type, N>(_ptr);};

				private :
					N *_ptr;
			};

			typedef T key_type;
			typedef T value_type;
			typedef Compare key_compare;
			typedef Compare value_compare;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef	RBT_node_set<value_type, Compare, Alloc> node;
			typedef typename allocator_type::template rebind<node>::other allocator_node;

			typedef set_iterator<const value_type, node> iterator;
			typedef set_iterator<const value_type, node> const_iterator;
			typedef ft::reverse_iterator<iterator > reverse_iterator;
			typedef ft::reverse_iterator<const_iterator > const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

			//CONSTRUCTOR
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc_val(alloc), _alloc_node(allocator_node()),_base_tree(0), _size(0)
			{
				min_node = _alloc_node.allocate(1);
				_alloc_node.construct(min_node, (value_type *) 0);
				max_node = _alloc_node.allocate(1);
				_alloc_node.construct(max_node, (value_type *) 0);
			};

			template <class InputIterator>
  			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc_val(alloc), _alloc_node(allocator_node()), _base_tree(0), _size(0)
			{
				min_node = _alloc_node.allocate(1);
				_alloc_node.construct(min_node, (value_type *) 0);
				max_node = _alloc_node.allocate(1);
				_alloc_node.construct(max_node, (value_type *) 0);
				
				while (first != last)
				{
					this->insert(*first);
					++first;
				}
				set_extremum_node(_base_tree, min_node, max_node);
			};

			set (const set& x) : _comp(x._comp), _alloc_val(x._alloc_val), _alloc_node(x._alloc_node), _base_tree(0), _size(x._size)
			{
				min_node = _alloc_node.allocate(1);
				_alloc_node.construct(min_node, (value_type *) 0);
				max_node = _alloc_node.allocate(1);
				_alloc_node.construct(max_node, (value_type *) 0);

				value_type	*temp_value;
				node		*temp_node;
				set::const_iterator first = x.begin();
				set::const_iterator last = x.end();

				while (first != last)
				{
					temp_value = _alloc_val.allocate(1);
					_alloc_val.construct(temp_value, *first);
					temp_node = _alloc_node.allocate(1);
					_alloc_node.construct(temp_node, temp_value);

					RBT_insert(&_base_tree, temp_node, _comp);

					++first;
				}
				set_extremum_node(_base_tree, min_node, max_node);
			}

			//DESTRUCTOR
			~set()
			{
				delete_extremum_node(_base_tree);
				recursive_destructor(_base_tree);
				_alloc_node.destroy(min_node);
				_alloc_node.deallocate(min_node, 1);
				_alloc_node.destroy(max_node);
				_alloc_node.deallocate(max_node, 1);
			}

			// ASSIGNMENT OPERATOR
			set& operator= (const set& x)
			{
				_size = x._size;
				delete_extremum_node(_base_tree);
				node *new_base = 0;

				set::const_iterator x_first = x.begin();
				set::const_iterator x_last = x.end();

				this->recursive_assignment(_base_tree, &new_base, x_first, x_last);
				
				value_type	*temp_value;
				node		*temp_node;
				while (x_first != x_last)
				{
					temp_value = _alloc_val.allocate(1);
					_alloc_val.construct(temp_value, *x_first);
					temp_node = _alloc_node.allocate(1);
					_alloc_node.construct(temp_node, temp_value);
					++x_first;
					RBT_insert(&new_base, temp_node, _comp);
				}
				_base_tree = new_base;

				set_extremum_node(_base_tree, min_node, max_node);
				return *this;
			}

			//ITERATORS
			iterator begin()
			{
				delete_extremum_node(_base_tree);
				node *temp = RBT_min(_base_tree);
				set_extremum_node(_base_tree, min_node, max_node);
				if (temp)
					return iterator(temp);
				return iterator(max_node);
			};

			const_iterator begin() const
			{
				delete_extremum_node(_base_tree);
				node *temp = RBT_min(_base_tree);
				set_extremum_node(_base_tree, min_node, max_node);
				if (temp)
					return iterator(temp);
				return iterator(max_node);
			};

			iterator end() {return iterator(max_node);};
			const_iterator end() const {return iterator(max_node);};

			//REVERSE ITERATORS
			reverse_iterator rbegin()
			{
				return (reverse_iterator((*this).end()));
			};
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator((*this).end()));
			};
			reverse_iterator rend()
			{
				return (reverse_iterator((*this).begin()));
			};
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator((*this).begin()));
			};

			//CAPACITY
			bool empty() const {return (_size == 0);};
			size_type size() const {return (_size);};
			size_type max_size() const {return (_alloc_node.max_size());};

			//INSERT
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				delete_extremum_node(_base_tree);
				node *temp = RBT_find(_base_tree, val, _comp);
				if (temp)
				{
					set_extremum_node(_base_tree, min_node, max_node);
					return (ft::make_pair(iterator(temp), false));
				}
				value_type	*temp_value = _alloc_val.allocate(1);
				_alloc_val.construct(temp_value, val);
				node *temp_node = _alloc_node.allocate(1);
				_alloc_node.construct(temp_node, temp_value);
				RBT_insert(&_base_tree, temp_node, _comp);
				set_extremum_node(_base_tree, min_node, max_node);
				_size++;
				return (ft::make_pair(iterator(temp_node), true));
			}

			iterator insert (iterator position, const value_type& val)
			{
				delete_extremum_node(_base_tree);
				node *temp = RBT_find(_base_tree, val, _comp);
				if (temp)
				{
					set_extremum_node(_base_tree, min_node, max_node);
					return (iterator(temp));
				}
				value_type	*temp_value = _alloc_val.allocate(1);
				_alloc_val.construct(temp_value, val);
				node *temp_node = _alloc_node.allocate(1);
				_alloc_node.construct(temp_node, temp_value);
				if (position != this->end())
					RBT_insert_position(&_base_tree, *position, temp_node, _comp);
				else
					RBT_insert(&_base_tree, temp_node, _comp);
				set_extremum_node(_base_tree, min_node, max_node);
				_size++;
				return (iterator(temp_node));
			};

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last)
			{
				delete_extremum_node(_base_tree);
				while (first != last)
				{
					if (RBT_find(_base_tree, *first, _comp) == 0)
					{
						value_type	*temp_value = _alloc_val.allocate(1);
						_alloc_val.construct(temp_value, *first);
						node *temp_node = _alloc_node.allocate(1);
						_alloc_node.construct(temp_node, temp_value);

						RBT_insert(&_base_tree, temp_node, _comp);
						_size++;
					}
					++first;
				}
				set_extremum_node(_base_tree, min_node, max_node);
			}

			//ERASE
			void erase (iterator position)
			{
				delete_extremum_node(_base_tree);
				node* to_delete = RBT_find(_base_tree, *position, _comp);
				if (to_delete != 0)
				{
					RBT_delete(&_base_tree, to_delete);
					_alloc_val.destroy(to_delete->get_ptr_data());
					_alloc_val.deallocate(to_delete->get_ptr_data(), 1);
					_alloc_node.destroy(to_delete);
					_alloc_node.deallocate(to_delete, 1);
					_size--;
				}
				set_extremum_node(_base_tree, min_node, max_node);
			}

			size_type erase (const key_type& k)
			{
				delete_extremum_node(_base_tree);
				node* to_delete = RBT_find(_base_tree, k, _comp);
				if (to_delete == 0)
				{
					set_extremum_node(_base_tree, min_node, max_node);
					return 0;
				}
				RBT_delete(&_base_tree, to_delete);
				_alloc_val.destroy(to_delete->get_ptr_data());
				_alloc_val.deallocate(to_delete->get_ptr_data(), 1);
				_alloc_node.destroy(to_delete);
				_alloc_node.deallocate(to_delete, 1);
				_size--;
				set_extremum_node(_base_tree, min_node, max_node);
				return 1;
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
					this->erase(first++);
			}
			
			//SWAP
			void swap (set& x)
			{
				allocator_type save_alloc_val = _alloc_val;
				allocator_node save_alloc_node = _alloc_node;
				node*	save_base_tree = _base_tree;
				size_type	save_size = _size;
				node*	save_min_node = min_node;
				node*	save_max_node = max_node;

				_alloc_val = x._alloc_val;
				_alloc_node = x._alloc_node;
				_base_tree = x._base_tree;
				_size = x._size;
				min_node = x.min_node;
				max_node = x.max_node;

				x._alloc_val = save_alloc_val;
				x._alloc_node = save_alloc_node;
				x._base_tree = save_base_tree;
				x._size = save_size;
				x.min_node = save_min_node;
				x.max_node = save_max_node;
			}

			//CLEAR
			void clear()
			{
				delete_extremum_node(_base_tree);
				recursive_destructor(_base_tree);
				_size = 0;
				_base_tree = 0;
			}

			//OBSERVERS
			key_compare key_comp() const {return _comp;};

			value_compare value_comp() const {return _comp;};

			//OPERATIONS
			iterator find (const key_type& k)
			{
				delete_extremum_node(_base_tree);
				node *to_save = RBT_find(_base_tree, k, _comp);
				set_extremum_node(_base_tree, min_node, max_node);
				if (to_save)
					return (iterator(to_save));
				return (this->end());
			};

			const_iterator find (const key_type& k) const
			{
				delete_extremum_node(_base_tree);
				node *to_save = RBT_find(_base_tree, k, _comp);
				set_extremum_node(_base_tree, min_node, max_node);
				if (to_save)
					return (const_iterator(to_save));
				return (this->end());
			};

			size_type count (const key_type& k) const
			{
				delete_extremum_node(_base_tree);
				bool temp = RBT_find(_base_tree, k, _comp) == 0;
				set_extremum_node(_base_tree, min_node, max_node);
				return (temp ? 0 : 1);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator first = begin();
				iterator last = end();
				while (first != last)
				{
					if (!_comp(*first, k))
						break;
					++first;
				}
				return (first);
			};

			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator first = begin();
				const_iterator last = end();
				while (first != last)
				{
					if (!_comp(*first, k))
						break;
					++first;
				}
				return (first);
			};

			iterator upper_bound (const key_type& k)
			{
				iterator first = begin();
				iterator last = end();
				while (first != last)
				{
					if (_comp(k, *first))
						break;
					++first;
				}
				return (first);
			};

			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator first = begin();
				const_iterator last = end();
				while (first != last)
				{
					if (_comp(k, *first))
						break;
					++first;
				}
				return (first);
			};

			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {return (ft::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k)));};
			ft::pair<iterator,iterator> equal_range (const key_type& k) {return (ft::pair<iterator,iterator>(lower_bound(k), upper_bound(k)));};

			//ALLOCATOR
			allocator_type get_allocator() const {return _alloc_val;};

			//TO DELETE
			void print() const
			{
				delete_extremum_node(_base_tree);
				std::cout << "\n------------\n";
				print_RBT(_base_tree);
				std::cout << "------------\n";
				set_extremum_node(_base_tree, min_node, max_node);
			}

		private :
			key_compare const& _comp;
			allocator_type _alloc_val;
			allocator_node _alloc_node;
			node*	_base_tree;
			size_type	_size;

			node*	min_node;
			node*	max_node;

			void	recursive_destructor(node *base)
			{
				if (base == 0)
					return ;
				recursive_destructor(base->get_left());
				recursive_destructor(base->get_right());
				_alloc_val.destroy(base->get_ptr_data());
				_alloc_val.deallocate(base->get_ptr_data(), 1);
				_alloc_node.destroy(base);
				_alloc_node.deallocate(base, 1);
			}

			void recursive_assignment(node *base, node **new_base, const_iterator &first, const_iterator &last)
			{
				if (base == 0)
					return ;
				recursive_assignment(base->get_left(), new_base, first, last);
				recursive_assignment(base->get_right(), new_base, first, last);
				if (first != last)
				{
					_alloc_val.destroy(base->get_ptr_data());
					_alloc_val.construct(base->get_ptr_data(), *first);
					base->RBT_reset();
					RBT_insert(new_base, base, _comp);
					++first;
				}
				else
				{
					_alloc_val.destroy(base->get_ptr_data());
					_alloc_val.deallocate(base->get_ptr_data(), 1);
					_alloc_node.destroy(base);
					_alloc_node.deallocate(base, 1);
				}
			};

	};

	template<class T, class Compare, class Alloc>
	void swap(ft::set<T,Compare,Alloc>& lhs, ft::set<T,Compare,Alloc>& rhs)
	{lhs.swap(rhs);};

	template<class T, class Compare, class Alloc >
	bool operator==( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template<class T, class Compare, class Alloc >
	bool operator!=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	};

	template<class T, class Compare, class Alloc >
	bool operator<( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(),lhs.end(), rhs.begin(), rhs.end()));
	};

	template<class T, class Compare, class Alloc >
	bool operator<=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	};

	template<class T, class Compare, class Alloc >
	bool operator>( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	};

	template<class T, class Compare, class Alloc >
	bool operator>=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	};


}

#endif
