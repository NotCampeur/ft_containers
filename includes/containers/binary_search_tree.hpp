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

namespace ft
{
	template< class T >
	class binary_search_tree
	{
		private:
			typedef binary_search_tree<T>*	node_pointer;

			node_pointer				_parent;
			node_pointer				_left;
			node_pointer				_right;
			T							_value;

			// For now I consider that a binary tree must be initiate with at least one value.
			binary_search_tree() : _parent(NULL), _left(NULL), _right(NULL), _value() {}
		public:
			binary_search_tree(const T& value) : _parent(NULL), _left(NULL), _right(NULL), _value(value) {}
			binary_search_tree(const binary_search_tree& other) : _parent(other._parent), _left(other._left), _right(other._right), _value(other._value) {}

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
				}
				return (*this);
			}

			void	insert(const T& value)
			{
				if (value < _value)
				{
					if (_left)
						_left->insert(value);
					else
					{
						_left = new binary_search_tree(value);
						_left->_parent = this;
					}
				}
				else if (value > _value)
				{
					if (_right)
						_right->insert(value);
					else
					{
						_right = new binary_search_tree(value);
						_right->_parent = this;
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