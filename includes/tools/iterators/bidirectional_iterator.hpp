/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:01:03 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/03 15:35:51 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP
# define CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "iterator_tags.hpp"

namespace ft
{
	template<class I>
	struct bidirectional_iterator : ft::iterator<bidirectional_iterator_tag, I>
	{
		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef I								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef I*								pointer;
		typedef I&								reference;

		pointer	_ptr;

		bidirectional_iterator() : _ptr(NULL) {};
		bidirectional_iterator(const bidirectional_iterator<I>& other) : _ptr(other._ptr) {};
		~bidirectional_iterator() {};

		bidirectional_iterator& operator=(const bidirectional_iterator& other)
		{
			_ptr = other._ptr;
			return (*this);
		}

		reference operator*() const { return *_ptr; }
		pointer operator->() { return _ptr; }
		const pointer operator->() const { return _ptr; }

		bidirectional_iterator& operator++() { ++_ptr; return (*this); }
		bidirectional_iterator operator++(int) { bidirectional_iterator<I> tmp(*this); ++_ptr; return tmp; }

		bidirectional_iterator& operator--() { --_ptr; return (*this); }
		bidirectional_iterator operator--(int) { bidirectional_iterator<I> tmp(*this); --_ptr; return tmp; }

		friend bool operator==(const bidirectional_iterator<I>& lhs, const bidirectional_iterator<I>& rhs) { return (lhs._ptr == rhs._ptr); }
	};

	template<class I>
	bool operator!=(const bidirectional_iterator<I>& lhs, const bidirectional_iterator<I>& rhs) { return !(lhs == rhs); }

	template<class I>
	struct const_bidirectional_iterator : ft::iterator<bidirectional_iterator_tag, I>
	{
		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef const I							value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const I*						pointer;
		typedef const I&						reference;

		const_bidirectional_iterator() : _ptr(NULL) {};
		const_bidirectional_iterator(const const_bidirectional_iterator<I>& other) : _ptr(other._ptr) {};
		~const_bidirectional_iterator() {};

		const_bidirectional_iterator& operator=(const const_bidirectional_iterator<I>& other)
		{
			_ptr = other._ptr;
			return (*this);
		}
		
		const_bidirectional_iterator& operator=(const bidirectional_iterator<I>& other)
		{
			_ptr = other._ptr;
			return (*this);
		}

		reference operator*() const { return *_ptr; }
		pointer operator->() { return _ptr; }
		const pointer operator->() const { return _ptr; }

		const_bidirectional_iterator& operator++() { ++_ptr; return (*this); }
		const_bidirectional_iterator operator++(int) { const_bidirectional_iterator<I> tmp(*this); ++_ptr; return tmp; }

		const_bidirectional_iterator& operator--() { --_ptr; return (*this); }
		const_bidirectional_iterator operator--(int) { const_bidirectional_iterator<I> tmp(*this); --_ptr; return tmp; }

		friend bool operator==(const const_bidirectional_iterator<I>& lhs, const const_bidirectional_iterator<I>& rhs) { return (lhs._ptr == rhs._ptr); }
		
		private:
			pointer	_ptr;
	};

	template<class I>
	bool operator!=(const const_bidirectional_iterator<I>& lhs, const const_bidirectional_iterator<I>& rhs) { return !(lhs == rhs); }
}

#endif