/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:52:16 by ldutriez          #+#    #+#             */
/*   Updated: 2022/01/12 18:51:11 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
# define CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "iterator_tags.hpp"

namespace ft
{
	template<class It>
	struct random_access_iterator : ft::iterator<random_access_iterator_tag, It>
	{
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef It								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef It*								pointer;
		typedef It&								reference;

		It										i;
		It&										r;

		random_access_iterator() : i(0), r(&i) {}

		random_access_iterator operator=(const random_access_iterator& rhs)
		{
			i = rhs.i;
			r = rhs.r;
			return (*this);
		}

		reference operator*() const { return r; }
		pointer operator->() const { return &r; }
		
		reference operator[](difference_type n) const { return r + n; }
		
		random_access_iterator& operator++() { ++r; return *this; }
		random_access_iterator operator++(int) { random_access_iterator tmp(*this); ++r; return tmp; }
		
		random_access_iterator& operator--() { --r; return *this; }
		random_access_iterator operator--(int) { random_access_iterator tmp(*this); --r; return tmp; }
		
		random_access_iterator& operator+=(difference_type n) { r += n; return *this; }
		random_access_iterator& operator-=(difference_type n) { r -= n; return *this; }
		
		random_access_iterator operator+(difference_type n) const { random_access_iterator tmp(*this); tmp += n; return tmp; }
		random_access_iterator operator-(difference_type n) const { random_access_iterator tmp(*this); tmp -= n; return tmp; }
		
		difference_type operator-(random_access_iterator const& rhs) const { return r - rhs.r; }

		bool operator==(random_access_iterator const& rhs) const { return r == rhs.r; }
		bool operator!=(random_access_iterator const& rhs) const { return r != rhs.r; }
		bool operator<(random_access_iterator const& rhs) const { return r < rhs.r; }
		bool operator>(random_access_iterator const& rhs) const { return r > rhs.r; }
		bool operator<=(random_access_iterator const& rhs) const { return r <= rhs.r; }
		bool operator>=(random_access_iterator const& rhs) const { return r >= rhs.r; }
	};

	template<class It>
	struct const_random_access_iterator : ft::iterator<random_access_iterator_tag, It>
	{
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef const It						value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const It*						pointer;
		typedef const It&						reference;

		It															i;
		It&															r;

		const_random_access_iterator() : i(0), r(i) {}

		reference operator*() const { return r; }
		pointer operator->() const { return &r; }
		
		reference operator[](difference_type n) const { return r + n; }
		
		const_random_access_iterator& operator++() { ++r; return *this; }
		const_random_access_iterator operator++(int) { const_random_access_iterator tmp(*this); ++r; return tmp; }
		
		const_random_access_iterator& operator--() { --r; return *this; }
		const_random_access_iterator operator--(int) { const_random_access_iterator tmp(*this); --r; return tmp; }
		
		const_random_access_iterator& operator+=(difference_type n) { r += n; return *this; }
		const_random_access_iterator& operator-=(difference_type n) { r -= n; return *this; }
		
		const_random_access_iterator operator+(difference_type n) const { const_random_access_iterator tmp(*this); tmp += n; return tmp; }
		const_random_access_iterator operator-(difference_type n) const { const_random_access_iterator tmp(*this); tmp -= n; return tmp; }
		
		difference_type operator-(const_random_access_iterator const& rhs) const { return r - rhs.r; }

		bool operator==(const_random_access_iterator const& rhs) const { return r == rhs.r; }
		bool operator!=(const_random_access_iterator const& rhs) const { return r != rhs.r; }
		bool operator<(const_random_access_iterator const& rhs) const { return r < rhs.r; }
		bool operator>(const_random_access_iterator const& rhs) const { return r > rhs.r; }
		bool operator<=(const_random_access_iterator const& rhs) const { return r <= rhs.r; }
		bool operator>=(const_random_access_iterator const& rhs) const { return r >= rhs.r; }
	
	};
}

#endif