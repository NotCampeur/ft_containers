/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:36:01 by ldutriez          #+#    #+#             */
/*   Updated: 2022/01/10 18:30:09 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
# define CONTAINERS_REVERSE_ITERATOR_HPP

namespace ft
{
	template<class It>
	class reverse_iterator
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

			reference operator*() const { return *(current - 1); }
			pointer operator->() const { return &(current - 1); }

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
	template< class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template< class Iter >
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
	{
		return it + n;
	}

	template< class Iter >
	reverse_iterator<Iter> operator-(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
	{
		return it - n;
	}
}

#endif