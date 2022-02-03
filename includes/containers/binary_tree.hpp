/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:29:34 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/03 18:06:52 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_BINARY_TREE_HPP
# define CONTAINERS_BINARY_TREE_HPP

# include <exception>
# include "Logger.hpp"

namespace ft
{
	template< class T >
	class binary_tree
	{
		private:
			typedef binary_tree<T>*	node_pointer;

			node_pointer				_parent;
			node_pointer				_left;
			node_pointer				_right;
			T							_value;

			// For now I consider that a binary tree must be initiate with at least one value.
			binary_tree() : _parent(NULL), _left(NULL), _right(NULL), _value() {}

		public:
			binary_tree(const T& value) : _parent(NULL), _left(NULL), _right(NULL), _value(value) {}
			binary_tree(const binary_tree& other) : _parent(other._parent), _left(other._left), _right(other._right), _value(other._value) {}

			// The destructor will not delete all the tree but only his children.
			~binary_tree()
			{
				if (_left)
					delete _left;
				if (_right)
					delete _right;
			}

			binary_tree&				operator=(const binary_tree& other)
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
						_left = new binary_tree(value);
						_left->_parent = this;
					}
				}
				else if (value > _value)
				{
					if (_right)
						_right->insert(value);
					else
					{
						_right = new binary_tree(value);
						_right->_parent = this;
					}
				}
				else
					throw std::runtime_error("binary_tree::insert: value already exists.");
			}

			void	print(void)
			{
				if (_left)
					_left->print();
				Logger() << _value;
				if (_right)
					_right->print();
			}
	};
}

#endif