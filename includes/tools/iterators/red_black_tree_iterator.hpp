/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:05:24 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/23 02:31:41 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP
# define CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "iterator_tags.hpp"

template<class I>
struct red_black_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, I>
{
	typedef ft::bidirectional_iterator_tag	iterator_category;
	typedef I								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef I*								pointer;
	typedef I&								reference;

	pointer	_ptr;

	red_black_tree_iterator() : _ptr(NULL) {};
	red_black_tree_iterator(pointer ptr) : _ptr(ptr) {};
	red_black_tree_iterator(const red_black_tree_iterator<I>& other) : _ptr(other._ptr) {};
	~red_black_tree_iterator() {};

	red_black_tree_iterator& operator=(const red_black_tree_iterator& other)
	{
		_ptr = other._ptr;
		return (*this);
	}

	reference operator*() const { return *_ptr; }
	pointer operator->() { return _ptr; }
	const pointer operator->() const { return _ptr; }

	red_black_tree_iterator& operator++() { _ptr = next_inorder(_ptr); return (*this); }
	red_black_tree_iterator operator++(int) { red_black_tree_iterator tmp(*this); _ptr = next_inorder(_ptr); return tmp; }

	red_black_tree_iterator& operator--() { _ptr = prev_inorder(_ptr); return (*this); }
	red_black_tree_iterator operator--(int) { red_black_tree_iterator tmp(*this); _ptr = prev_inorder(_ptr); return tmp; }
};

template<class I>
bool operator==(const red_black_tree_iterator<I>& lhs, const red_black_tree_iterator<I>& rhs)
{
	return (lhs._ptr == rhs._ptr);
}

template<class I>
bool operator!=(const red_black_tree_iterator<I>& lhs, const red_black_tree_iterator<I>& rhs)
{
	return (lhs._ptr != rhs._ptr);
}

template<class I>
struct const_red_black_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, I>
{
	typedef ft::bidirectional_iterator_tag	iterator_category;
	typedef const I							value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef const I*						pointer;
	typedef const I&						reference;

	private:
		pointer	_ptr;

	public:

		const_red_black_tree_iterator() : _ptr(NULL) {};
		const_red_black_tree_iterator(pointer ptr) : _ptr(ptr) {};
		const_red_black_tree_iterator(const const_red_black_tree_iterator<I>& other) : _ptr(other._ptr) {};
		const_red_black_tree_iterator(const red_black_tree_iterator<I>& other) : _ptr(other._ptr) {};
		~const_red_black_tree_iterator() {};

		const_red_black_tree_iterator& operator=(const red_black_tree_iterator<I>& other)
		{
			_ptr = other._ptr;
			return (*this);
		}

		const_red_black_tree_iterator& operator=(const const_red_black_tree_iterator<I>& other)
		{
			_ptr = other._ptr;
			return (*this);
		}
		
		reference operator*() const { return *_ptr; }
		pointer operator->() { return _ptr; }
		const pointer operator->() const { return _ptr; }

		const_red_black_tree_iterator& operator++() { _ptr = next_inorder(_ptr); return (*this); }
		const_red_black_tree_iterator operator++(int) { const_red_black_tree_iterator tmp(*this); _ptr = next_inorder(_ptr); return tmp; }

		const_red_black_tree_iterator& operator--() { _ptr = prev_inorder(_ptr); return (*this); }
		const_red_black_tree_iterator operator--(int) { const_red_black_tree_iterator tmp(*this); _ptr = prev_inorder(_ptr); return tmp; }
		
		friend bool operator==(const const_red_black_tree_iterator& lhs, const const_red_black_tree_iterator& rhs)
		{
			return (lhs._ptr == rhs._ptr);
		}
};

template<class I>
bool operator!=(const const_red_black_tree_iterator<I>& lhs, const const_red_black_tree_iterator<I>& rhs)
{
	return !(lhs == rhs);
}

#endif