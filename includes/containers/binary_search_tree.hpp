/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:29:34 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/04 15:21:06 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_BINARY_SEARCH_TREE_HPP
# define CONTAINERS_BINARY_SEARCH_TREE_HPP

# include <exception>
# include "Logger.hpp"

typedef enum 	e_node_color
{
	red,
	black
}				node_color;

namespace ft
{
	template< class T >
	class binary_search_tree
	{
		public:
			typedef binary_search_tree<T>*	node_pointer;

			node_pointer				_parent;
			node_pointer				_left;
			node_pointer				_right;
			T							_value;
			node_color					_color;

		private:
			// For now I consider that a binary tree must be initiate with at least one value.
			binary_search_tree()
			: _parent(NULL), _left(NULL), _right(NULL)
			, _value(), _color(black) {}

		public:
			// The parent must be a black node.
			binary_search_tree(const T& value, node_color color = black)
			: _parent(NULL), _left(NULL), _right(NULL)
			, _value(value), _color(color) {}
			binary_search_tree(const binary_search_tree& other)
			: _parent(other._parent), _left(other._left), _right(other._right)
			, _value(other._value), _color(other._color) {}

			// The destructor will not delete all the tree but only his children.
			~binary_search_tree()
			{
				if (_left)
					delete _left;
				if (_right)
					delete _right;
			}

			binary_search_tree&				operator=(const binary_search_tree& other)
			{
				if (this != &other)
				{
					_parent = other._parent;
					_left = other._left;
					_right = other._right;
					_value = other._value;
					_color = other._color;
				}
				return (*this);
			}

		private:
			// This function will rotate the tree to the right.
			// ie: the parent will be the right child of the current node.
			void	right_rotate(node_pointer node)
			{
				node_pointer				parent = node->_parent;
				node_pointer				left = node->_left;

				if (parent)
				{
					node->_parent = parent->_parent;
					if (node->_right)
						parent->_left = node->_right;
					else
						parent->_left = NULL;
					node->_right = parent;
					parent->_parent = node;
				}
				else
				{
					left->_parent = parent;
					node->_parent = node->_left;
					node->_left = left->_right;
					left->_right = node;
				}
			}

			void	left_rotate(node_pointer node)
			{
				node_pointer				parent = node->_parent;
				node_pointer				right = node->_right;

				if (parent)
				{
					node->_parent = parent->_parent;
					if (node->_left)
						parent->_right = node->_left;
					else
						parent->_right = NULL;
					node->_left = parent;
					parent->_parent = node;
				}
				else
				{
					right->_parent = node->_parent;
					node->_parent = node->_right;
					node->_right = right->_left;
					right->_left = node;
				}
			}

			// Will init the pointer with the address of relatives of node.
			void	build_relation(node_pointer const node, node_pointer & parent, node_pointer & grand_parent, node_pointer & uncle)
			{
				parent = node->_parent;
				if (parent)
				{
					grand_parent = parent->_parent;
					if (grand_parent)
					{
						if (grand_parent->_left == this)
							uncle = grand_parent->_right;
						else if (grand_parent->_right == this)
							uncle = grand_parent->_left;
					}
				}
			}

			// In the case the uncle is red.
			void	resolve_uncle_red(node_pointer node)
			{
				node_pointer	uncle(NULL);
				node_pointer	grand_parent(NULL);
				node_pointer	parent(NULL);

				build_relation(node, parent, grand_parent, uncle);
				
				if (parent && grand_parent && uncle
				&& parent->_color == red && uncle->_color == red)
				{
					parent->_color = black;
					uncle->_color = black;
					grand_parent->_color = red;
					resolve_uncle_red(grand_parent);
				}
			}

			// This function will resolve any color violation.
			void	resolve_color_violation(node_pointer node)
			{
				node_pointer	uncle(NULL);
				node_pointer	grand_parent(NULL);
				node_pointer	parent(NULL);

				build_relation(node, parent, grand_parent, uncle);
				
				if (parent && grand_parent && uncle
				&& parent->_color == red && uncle->_color == red)
					resolve_uncle_red(node);
			}


		public:
			// This function might be call on an non empty tree.
			// It will add a node to the tree.
			// throw std::exception if the value is already in the tree.
			void	insert(const T& value)
			{
				if (value < _value)
				{
					if (_left)
						_left->insert(value);
					else
					{
						_left = new binary_search_tree(value, red);
						_left->_parent = this;
						resolve_color_violation(_left);
					}
				}
				else if (value > _value)
				{
					if (_right)
						_right->insert(value);
					else
					{
						_right = new binary_search_tree(value, red);
						_right->_parent = this;
						resolve_color_violation(_right);
					}
				}
				else
					throw std::runtime_error("binary_search_tree::insert: value already exists.");
			}

			void	erase(const T& value)
			{
				if (value < _value)
				{
					if (_left)
						_left->erase(value);
					else
						throw std::runtime_error("binary_search_tree::erase: value not found.");
				}
				else if (value > _value)
				{
					if (_right)
						_right->erase(value);
					else
						throw std::runtime_error("binary_search_tree::erase: value not found.");
				}
				else
				{
					if (_left && _right)
					{
						_value = _right->_value;
						_right->erase(_value);
					}
					else if (_left)
					{
						_value = _left->_value;
						_left->erase(_value);
					}
					else if (_right)
					{
						_value = _right->_value;
						_right->erase(_value);
					}
					else
					{
						if (_parent)
						{
							if (_parent->_left == this)
								_parent->_left = NULL;
							else
								_parent->_right = NULL;
						}
						delete this;
					}
				}
			}


			void	print(void)
			{
				static int		index(0);
				std::string		side;

				if (_left)
					_left->print();
				if (_parent && _parent->_left == this)
					side = "left";
				else if (_parent && _parent->_right == this)
					side = "right";
				else
					side = "root";

				Logger() << index << " [ " << side << " ] : " << _value;
				index++;
				if (_right)
					_right->print();
				if (_parent == NULL)
					index = 0;
			}
	};
}

#endif