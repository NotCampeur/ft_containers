/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:55:25 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/14 13:57:58 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP

# include "red_black_tree_node.hpp"

template< class T >
class rbtree
{
	private:
		RedBlackTreeNode<T>*				_root;
		
	public:
		rbtree() : _root(NULL) {};
		~rbtree() {delete _root;};

		RedBlackTreeNode<T>*	root() const {return _root;};

		void	insert(const T& value)
		{
			if (_root == NULL)
				_root = new RedBlackTreeNode<T>(value);
			else
				_root = _root->insert(value);
		};
};

#endif