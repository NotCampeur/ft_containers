/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:05:24 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/28 00:16:51 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP
# define CONTAINERS_RED_BLACK_TREE_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "iterator_tags.hpp"
# include "../../containers/binary_tree/red_black_tree_node.hpp"

template<class I>
struct red_black_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, I>
{
	typedef ft::bidirectional_iterator_tag	iterator_category;
	typedef I								value_type;
	typedef typename I::value_type			value_value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef I*								pointer;
	typedef I&								reference;
	typedef typename I::value_type*			value_pointer;
	typedef typename I::value_type&			value_reference;

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

	pointer base() const
	{
		return (_ptr);
	}
	
	value_reference operator*() const { return *_ptr->_value; }
	value_pointer operator->() { return _ptr->_value; }
	const value_pointer operator->() const { return _ptr->_value; }

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
	typedef const typename I::value_type	value_value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef const I*						pointer;
	typedef const I&						reference;
	typedef const typename I::value_type*	value_pointer;
	typedef const typename I::value_type&	value_reference;

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
		
		pointer base() const
		{
			return (_ptr);
		}

		value_reference operator*() const { return *_ptr->_value; }
		value_pointer operator->() { return _ptr->_value; }
		const value_pointer operator->() const { return _ptr->_value; }

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

template<class It>
class rb_reverse_iterator : public
	ft::iterator<typename ft::iterator_traits<It>::iterator_category,
				typename ft::iterator_traits<It>::value_type,
				typename ft::iterator_traits<It>::difference_type,
				typename ft::iterator_traits<It>::pointer,
				typename ft::iterator_traits<It>::reference >
{
	protected:
		It															current;
	public:
		typedef It													iterator_type;
		typedef typename ft::iterator_traits<It>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<It>::value_type		value_type;
		typedef typename ft::iterator_traits<It>::difference_type	difference_type;
		typedef typename ft::iterator_traits<It>::pointer			pointer;
		typedef typename ft::iterator_traits<It>::reference			reference;
		typedef typename iterator_type::value_pointer				type_pointer;
		typedef typename iterator_type::value_reference				type_reference;

		rb_reverse_iterator() : current() {}
		explicit rb_reverse_iterator(iterator_type it) : current(it) {}
		template<class It2>
		rb_reverse_iterator(const rb_reverse_iterator<It2> & it) : current(it.base()) {}

		rb_reverse_iterator & operator=(const rb_reverse_iterator & it)
		{
			current = it.current;
			return *this;
		}

		iterator_type base() const { return current; }

		type_reference operator*() const { iterator_type tmp = current; --tmp; return *tmp; }
		type_pointer operator->() const { return &(operator*()); }

		type_reference operator[](difference_type n) const { return *(current - 1 - n); }

		rb_reverse_iterator& operator++() { --current; return *this; }
		rb_reverse_iterator operator++(int) { rb_reverse_iterator tmp(*this); --current; return tmp; }

		rb_reverse_iterator& operator--() { ++current; return *this; }
		rb_reverse_iterator operator--(int) { rb_reverse_iterator tmp(*this); ++current; return tmp; }

		rb_reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
		rb_reverse_iterator& operator-=(difference_type n) { current += n; return *this; }

		rb_reverse_iterator operator+(difference_type n) const { rb_reverse_iterator tmp(current - n); return tmp; }
		rb_reverse_iterator operator-(difference_type n) const { rb_reverse_iterator tmp(current + n); return tmp; }
};
template< class It1, class It2 >
bool operator==(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
{
	return lhs.base() == rhs.base();
}

template< class It1, class It2 >
bool operator!=(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
{
	return lhs.base() != rhs.base();
}

template< class It1, class It2 >
bool operator<(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
{
	return lhs.base() > rhs.base();
}

template< class It1, class It2 >
bool operator<=(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
{
	return lhs.base() >= rhs.base();
}

template< class It1, class It2 >
bool operator>(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
{
	return lhs.base() < rhs.base();
}

template< class It1, class It2 >
bool operator>=(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
{
	return lhs.base() <= rhs.base();
}

template< class It >
rb_reverse_iterator<It> operator+(typename rb_reverse_iterator<It>::difference_type n, const rb_reverse_iterator<It>& it)
{
	return it + n;
}

template < class It >
typename rb_reverse_iterator<It>::difference_type operator-(const rb_reverse_iterator<It>& lhs,
	const rb_reverse_iterator<It>& rhs)
{
	return rhs.base() - lhs.base();
}

// A c++11 compliant reverse iterator
template < class It1 , class It2>
typename rb_reverse_iterator<It1>::difference_type operator-(const rb_reverse_iterator<It1>& lhs,
	const rb_reverse_iterator<It2>& rhs)
{
	return rhs.base() - lhs.base();
}

#endif