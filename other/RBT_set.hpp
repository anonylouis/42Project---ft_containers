#ifndef RBT_SET_HPP
# define RBT_SET_HPP

# define RED 1
# define BLACK 0

# include <functional>
# include <memory>

//DEBUG TO DELETE
#include <iostream>
#include "color.hpp"

namespace ft
{
	template <class value_type, class Compare, class Allocator>
	class RBT_node_set
	{
		public :
		typedef value_type data_type;

		RBT_node_set(value_type *new_val) : _left(0), _right(0), _father(0), _color(true), data(new_val) { }

		void RBT_reset()
		{
			_left = 0;
			_right = 0;
			_father = 0;
			_color = true;
		};

		data_type	*get_ptr_data() {return (data);};
		RBT_node_set	*get_right() {return (_right);};
		RBT_node_set	*get_left() {return (_left);};
		RBT_node_set	*get_father() {return (_father);};

		friend RBT_node_set *RBT_find(RBT_node_set *base, value_type to_search, Compare comp)
		{
			while (base !=  0)
			{
				if (!comp(*(base->data) ,to_search) && !comp(to_search, *(base->data)))
					return base;
				if (comp(*(base->data), to_search))
					base = base->_right;
				else
					base = base->_left;
			}
			return 0;
		}

		friend void RBT_recolor(RBT_node_set **base, RBT_node_set *new_node)
		{
			if (new_node->_father == 0)
			{
				new_node->_color = false;
				return ;
			}
			if (new_node->_father->_father == 0)
			{
				new_node->_father->_color = false;
				return ;
			}
			if (new_node->_color == false || new_node->_father->_color == false)
				return ;
			RBT_node_set *father = new_node->_father;
			RBT_node_set *uncle = father->_father;
			uncle = (uncle->_left == father) ? uncle->_right : uncle->_left;
			if (uncle == 0 || uncle->_color == false)
			{
				RBT_node_set *grandfather = father->_father;
				if (grandfather->_left == father)
				{
					if (father->_left == new_node)
					{
						grandfather->_left = father->_right;
						if (grandfather->_left)
							grandfather->_left->_father = grandfather;
						father->_right = grandfather;
						father->_left = new_node;

						if (grandfather->_father == 0)
						{
							*base = father;
							father->_father = 0;
						}
						else
						{
							father->_father = grandfather->_father;
							if (grandfather->_father->_left == grandfather)
								grandfather->_father->_left = father;
							else
								grandfather->_father->_right = father;
						}
						grandfather->_father = father;
						grandfather->_color = true;
						father->_color = false;
					}
					else
					{
						//std::cout << "a droite du padre\n";
						grandfather->_left = new_node;
						new_node->_father = grandfather;
						father->_right = new_node->_left;
						if (new_node->_left)
							new_node->_left->_father = father;
						new_node->_left = father;
						father->_father = new_node;
						return (RBT_recolor(base, father));
					}
				}
				else
				{
					//std::cout << "a droite du gp\n";
					if (father->_right == new_node)
					{
						//std::cout << "a droite du padre\n";
						grandfather->_right = father->_left;
						if (grandfather->_right)
							grandfather->_right->_father = grandfather;
						father->_left = grandfather;
						father->_right = new_node;

						if (grandfather->_father == 0)
						{
							*base = father;
							father->_father = 0;
						}
						else
						{
							father->_father = grandfather->_father;
							if (grandfather->_father->_left == grandfather)
								grandfather->_father->_left = father;
							else
								grandfather->_father->_right = father;
						}
						grandfather->_father = father;
						grandfather->_color = true;
						father->_color = false;
					}
					else
					{
						//print_RBT(*base);
						//std::cout << "a gauche du padre\n";
						grandfather->_right = new_node;
						new_node->_father = grandfather;
						father->_left = new_node->_right;
						if (new_node->_right)
							new_node->_right->_father = father;
						new_node->_right = father;
						father->_father = new_node;
						//print_RBT(*base);
						return (RBT_recolor(base, father));
					}
				}
			}
			else
			{
				father->_color = false;
				uncle->_color = false;
				father->_father->_color = true;
				return (RBT_recolor(base, father->_father));
			}

		}

		friend void RBT_insert(RBT_node_set **base, RBT_node_set *new_node, Compare comp)
		{
			if (*base == 0)
			{
				*base = new_node;
				new_node->_color = false;
				return ;
			}
			RBT_node_set *temp = *base;
			while(true)
			{
				if (comp(*(temp->data), *(new_node->data)))
				{
					if (temp->_right == 0)
					{
						temp->_right = new_node;
						break;
					}
					temp = temp->_right;
				}
				else
				{
					if (temp->_left == 0)
					{
						temp->_left = new_node;
						break;
					}
					temp = temp->_left;
				}
			}
			new_node->_father = temp;
			if (temp->_color)
				RBT_recolor(base, new_node);
		}

		friend void RBT_insert_position(RBT_node_set **base, value_type const &k, RBT_node_set *new_node, Compare comp)
		{
			if (*base == 0)
			{
				*base = new_node;
				new_node->_color = false;
				return ;
			}
			RBT_node_set *hint = RBT_find(*base, k, comp);

			if (comp(*(hint->data), *(new_node->data)))
			{
				while(hint->_father && comp(*(hint->data), *(new_node->data)))
					hint = hint->_father;
			}
			else
			{
				if (hint->_father != 0 && !comp(*(hint->_father->data), *(new_node->data)))
					RBT_insert(base, new_node, comp);
			}
			while(true)
			{
				if (comp(*(hint->data), *(new_node->data)))
				{
					if (hint->_right == 0)
					{
						hint->_right = new_node;
						break;
					}
					hint = hint->_right;
				}
				else
				{
					if (hint->_left == 0)
					{
						hint->_left = new_node;
						break;
					}
					hint = hint->_left;
				}
			}
			new_node->_father = hint;
			if (hint->_color)
				RBT_recolor(base, new_node);
		}

		friend void RBT_double_black(RBT_node_set **base, RBT_node_set *to_fix)
		{
			if (to_fix->_father == 0)
				return ;
			else if (to_fix->_father->_left == to_fix)
			{
				RBT_node_set *brother = to_fix->_father->_right; //brother == 0 imposible ?
				if (brother->_color == false)
				{
					if ((brother->_left == 0 || brother->_left->_color == false) && (brother->_right == 0 || brother->_right->_color == false))
					{
						brother->_color = true;
						if (to_fix->_father->_color == true)
						{
							to_fix->_father->_color = false;
							return ;
						}
						return RBT_double_black(base, to_fix->_father);
					}
					else if (brother->_right != 0 && brother->_right->_color == true)
					{
						to_fix->_father->_right = brother->_left;
						if (to_fix->_father->_right)
							to_fix->_father->_right->_father = to_fix->_father;
						brother->_left = to_fix->_father;

						if (to_fix->_father->_father == 0)
						{
							*base = brother;
							brother->_father = 0;
						}
						else
						{
							brother->_father = to_fix->_father->_father;
							if (to_fix->_father->_father->_left == to_fix->_father)
								to_fix->_father->_father->_left = brother;
							else
								to_fix->_father->_father->_right = brother;
						}
						to_fix->_father->_father = brother;
						brother->_color = to_fix->_father->_color;
						to_fix->_father->_color = false;
						brother->_right->_color = false;
					}
					else
					{
						RBT_node_set *temp = brother->_left;
						to_fix->_father->_right = temp;
						temp->_father = to_fix->_father;
						brother->_left = temp->_right;
						temp->_right = brother;
						brother->_father = temp;
						temp->_color = false;
						brother->_color = true;
						//print_RBT(*base);
						return (RBT_double_black(base, to_fix));
					}
				}
				else
				{
					to_fix->_father->_right = brother->_left;
					if (to_fix->_father->_right)
						to_fix->_father->_right->_father = to_fix->_father;
					brother->_left = to_fix->_father;

					if (to_fix->_father->_father == 0)
					{
						*base = brother;
						brother->_father = 0;
					}
					else
					{
						brother->_father = to_fix->_father->_father;
						if (to_fix->_father->_father->_left == to_fix->_father)
							to_fix->_father->_father->_left = brother;
						else
							to_fix->_father->_father->_right = brother;
					}
					to_fix->_father->_father = brother;
					to_fix->_father->_color = true;
					brother->_color = false;
					return (RBT_double_black(base, to_fix));
				}
			}
			else //brother a left
			{
				RBT_node_set *brother = to_fix->_father->_left; //brother == 0 imposible ?
				if (brother->_color == false)
				{
					if ((brother->_left == 0 || brother->_left->_color == false) && (brother->_right == 0 || brother->_right->_color == false))
					{
						brother->_color = true;
						if (to_fix->_father->_color == true)
						{
							to_fix->_father->_color = false;
							return ;
						}
						return RBT_double_black(base, to_fix->_father);
					}
					else if (brother->_left != 0 && brother->_left->_color == true)
					{
						to_fix->_father->_left = brother->_right;
						if (to_fix->_father->_left)
							to_fix->_father->_left->_father = to_fix->_father;
						brother->_right = to_fix->_father;

						if (to_fix->_father->_father == 0)
						{
							*base = brother;
							brother->_father = 0;
						}
						else
						{
							brother->_father = to_fix->_father->_father;
							if (to_fix->_father->_father->_left == to_fix->_father)
								to_fix->_father->_father->_left = brother;
							else
								to_fix->_father->_father->_right = brother;
						}
						to_fix->_father->_father = brother;
						brother->_color = to_fix->_father->_color;
						to_fix->_father->_color = false;
						brother->_left->_color = false;
					}
					else
					{
						RBT_node_set *temp = brother->_right;
						to_fix->_father->_left = temp;
						temp->_father = to_fix->_father;
						brother->_right = temp->_left;
						temp->_left = brother;
						brother->_father = temp;
						temp->_color = false;
						brother->_color = true;
						//print_RBT(*base);
						return (RBT_double_black(base, to_fix));
					}
				}
				else
				{
					to_fix->_father->_left = brother->_right;
					if (to_fix->_father->_left)
							to_fix->_father->_left->_father = to_fix->_father;
					brother->_right = to_fix->_father;

					if (to_fix->_father->_father == 0)
					{
						*base = brother;
						brother->_father = 0;
					}
					else
					{
						brother->_father = to_fix->_father->_father;
						if (to_fix->_father->_father->_left == to_fix->_father)
							to_fix->_father->_father->_left = brother;
						else
							to_fix->_father->_father->_right = brother;
					}
					to_fix->_father->_father = brother;
					to_fix->_father->_color = true;
					brother->_color = false;
					return (RBT_double_black(base, to_fix));
				}
			}
		}

		friend void RBT_delete(RBT_node_set **base, RBT_node_set *to_delete)
		{
			if (to_delete->_right == 0 && to_delete->_left == 0)
			{
				if (to_delete->_father == 0)
					*base = 0;
				else
				{
					if (to_delete->_color == false)
						RBT_double_black(base, to_delete);
					if (to_delete->_father->_left == to_delete)
						to_delete->_father->_left = 0;
					else
						to_delete->_father->_right = 0;
					return;
				}
			}
			else if (to_delete->_right == 0)
			{
				if (to_delete->_father == 0)
				{
					*base = to_delete->_left;
					to_delete->_left->_father = 0;
				}
				else
				{
					if (to_delete->_father->_left == to_delete)
						to_delete->_father->_left = to_delete->_left;
					else
						to_delete->_father->_right = to_delete->_left;
					to_delete->_left->_father = to_delete->_father;
				}
				if (to_delete->_color == false)
				{
					if (to_delete->_left->_color == true)
						to_delete->_left->_color = false;
					else
						return RBT_double_black(base, to_delete->_left);
				}
			}
			else if (to_delete->_left == 0)
			{
				if (to_delete->_father == 0)
				{
					*base = to_delete->_right;
					to_delete->_right->_father = 0;
				}
				else
				{
					if (to_delete->_father->_right == to_delete)
						to_delete->_father->_right = to_delete->_right;
					else
						to_delete->_father->_left = to_delete->_right;
					to_delete->_right->_father = to_delete->_father;
				}
				if (to_delete->_color == false)
				{
					if (to_delete->_right->_color == true)
						to_delete->_right->_color = false;
					else
						return RBT_double_black(base, to_delete->_right);
				}
			}
			else
			{
				RBT_node_set *temp = to_delete->_left;
				while (temp->_right != 0)
					temp = temp->_right;
				RBT_node_set *left_node = to_delete->_left;
				RBT_node_set *right_node = to_delete->_right;
				RBT_node_set *father_node = to_delete->_father;
				bool i = to_delete->_color;
				if (to_delete->_father == 0)
				{
					*base = temp;
				}
				else
				{
					if (to_delete->_father->_left == to_delete)
						to_delete->_father->_left = temp;
					else
						to_delete->_father->_right = temp;
				}
				if (temp->_father != to_delete)
					to_delete->_father = temp->_father;
				else
					to_delete->_father = temp;
				to_delete->_left = temp->_left;
				to_delete->_right = temp->_right;
				if (to_delete->_left != 0)
					to_delete->_left->_father = to_delete;
				if (to_delete->_right != 0)
					to_delete->_right->_father = to_delete;
				if (to_delete->_father && to_delete->_father->_left == temp)
					to_delete->_father->_left = to_delete;
				else if (to_delete->_father)
					to_delete->_father->_right = to_delete;
				if (left_node != temp)
					temp->_left = left_node;
				else
					temp->_left = to_delete;
				temp->_right = right_node;
				temp->_father = father_node;
				right_node->_father = temp;
				if (left_node != temp)
					left_node->_father = temp;
				to_delete->_color = temp->_color;
				temp->_color = i;
				//return ;
				//print_RBT(*base);
				return RBT_delete(base, to_delete);
			}
		}

		friend RBT_node_set *RBT_min(RBT_node_set *base)
		{
			if (base == 0)
				return (0);
			while (base->_left && base->_left->data != 0)
				base = base->_left;
			return (base);
		}

		friend RBT_node_set *RBT_max(RBT_node_set *base)
		{
			if (base == 0)
				return (0);
			while (base->_right && base->_right->data != 0)
				base = base->_right;
			return (base);
		}

		//TO DELETE
		friend void print_RBT(RBT_node_set *base, int n = 0)
		{
			int save = n;
			if (base == 0)
			{
				std::cout << std::string(save,' ') << "NIL\n";
			}
			else
			{
				if (base->_color)
					std::cout << red;
				std::cout << std::string(save,' ');
				std::cout << *(base->data);
				std::cout << " father = ";
				if (base->_father != 0)
					std::cout << base->_father->data;
				else
					std::cout << italic << "RIEN" << reset;
				std::cout << "\n" << reset;
				print_RBT(base->_left, save + 1);
				print_RBT(base->_right, save + 1);
			}
		}

		friend	void	set_extremum_node(RBT_node_set *base, RBT_node_set *nodemin, RBT_node_set *nodemax)
		{
			RBT_node_set *temp_min = RBT_min(base);
			RBT_node_set *temp_max = RBT_max(base);

			if (temp_min != 0)
			{
				temp_min->_left = nodemin;
				nodemin->_father = temp_min;
			}
			if (temp_max != 0)
			{
				temp_max->_right = nodemax;
				nodemax->_father = temp_max;
			}
		}

		friend	void	delete_extremum_node(RBT_node_set *base)
		{
			RBT_node_set *temp_min = RBT_min(base);
			RBT_node_set *temp_max = RBT_max(base);

			if (temp_min != 0)
			
				temp_min->_left = 0;
			if (temp_max != 0)
				temp_max->_right = 0;
		}
		

		private :
			RBT_node_set	*_left;
			RBT_node_set	*_right;
			RBT_node_set	*_father;
			bool		_color;

			data_type	*data;
	};

}

#endif
