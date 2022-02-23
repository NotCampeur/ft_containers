/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:36:01 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/22 17:56:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
# define CONTAINERS_REVERSE_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"

namespace ft
{
	template<class It>
	class reverse_iterator : public
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

			reverse_iterator() : current() {}
			explicit reverse_iterator(iterator_type it) : current(it) {}
			template<class It2>
			reverse_iterator(const reverse_iterator<It2> & it) : current(it.base()) {}

			reverse_iterator & operator=(const reverse_iterator & it)
			{
				current = it.current;
				return *this;
			}

			iterator_type base() const { return current; }

			reference operator*() const { iterator_type tmp = current; return *--tmp; }
			pointer operator->() const { return &(operator*()); }

			reference operator[](difference_type n) const { return *(current - 1 - n); }

			reverse_iterator& operator++() { --current; return *this; }
			reverse_iterator operator++(int) { reverse_iterator tmp(*this); --current; return tmp; }

			reverse_iterator& operator--() { ++current; return *this; }
			reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++current; return tmp; }

			reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
			reverse_iterator& operator-=(difference_type n) { current += n; return *this; }

			reverse_iterator operator+(difference_type n) const { reverse_iterator tmp(current - n); return tmp; }
			reverse_iterator operator-(difference_type n) const { reverse_iterator tmp(current + n); return tmp; }
	};
	template< class It1, class It2 >
	bool operator==(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template< class It1, class It2 >
	bool operator!=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template< class It1, class It2 >
	bool operator<(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template< class It1, class It2 >
	bool operator<=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template< class It1, class It2 >
	bool operator>(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template< class It1, class It2 >
	bool operator>=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template< class It >
	reverse_iterator<It> operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& it)
	{
		return it + n;
	}
	
	template < class It >
	typename reverse_iterator<It>::difference_type operator-(const reverse_iterator<It>& lhs,
		const reverse_iterator<It>& rhs)
	{
		return rhs.base() - lhs.base();
	}

	// A c++11 compliant reverse iterator
	template < class It1 , class It2>
	typename reverse_iterator<It1>::difference_type operator-(const reverse_iterator<It1>& lhs,
		const reverse_iterator<It2>& rhs)
	{
		return rhs.base() - lhs.base();
	}
}

#endif