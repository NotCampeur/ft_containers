/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:52:16 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/01 02:45:15 by ldutriez         ###   ########.fr       */
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

		pointer									_ptr;

		random_access_iterator() {}

		random_access_iterator(pointer ptr) : _ptr(ptr) {}

		reference operator*() const { return *_ptr; }
		pointer operator->() { return _ptr; }
		const pointer operator->() const { return _ptr; }
		
		reference operator[](difference_type n) const { return *(_ptr + n); }
		
		random_access_iterator& operator++() { ++_ptr; return *this; }
		random_access_iterator operator++(int) { random_access_iterator tmp(*this); ++_ptr; return tmp; }
		
		random_access_iterator& operator--() { --_ptr; return *this; }
		random_access_iterator operator--(int) { random_access_iterator tmp(*this); --_ptr; return tmp; }
		
		random_access_iterator& operator+=(difference_type n) { _ptr += n; return *this; }
		random_access_iterator& operator-=(difference_type n) { _ptr -= n; return *this; }
		
		random_access_iterator operator+(difference_type n) const { random_access_iterator tmp(*this); tmp += n; return tmp; }
		random_access_iterator operator-(difference_type n) const { random_access_iterator tmp(*this); tmp -= n; return tmp; }
		
		friend difference_type operator-(random_access_iterator const& lhs, random_access_iterator const& rhs) { return lhs._ptr - rhs._ptr; }

		friend bool operator==(random_access_iterator<It> const& lhs, random_access_iterator<It> const& rhs) { return lhs._ptr == rhs._ptr; }
		friend bool operator!=(random_access_iterator<It> const& lhs, random_access_iterator<It> const& rhs) { return lhs._ptr != rhs._ptr; }
		friend bool operator<(random_access_iterator<It> const& lhs, random_access_iterator<It> const& rhs) { return lhs._ptr < rhs._ptr; }
		friend bool operator>(random_access_iterator<It> const& lhs, random_access_iterator<It> const& rhs) { return lhs._ptr > rhs._ptr; }
		friend bool operator<=(random_access_iterator<It> const& lhs, random_access_iterator<It> const& rhs) { return lhs._ptr <= rhs._ptr; }
		friend bool operator>=(random_access_iterator<It> const& lhs, random_access_iterator<It> const& rhs) { return lhs._ptr >= rhs._ptr; }
	};

	template<class It>
	struct const_random_access_iterator : ft::iterator<random_access_iterator_tag, It>
	{
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef const It						value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const It*						pointer;
		typedef const It&						reference;

		private:
			pointer									_ptr;

		public:
			
			const_random_access_iterator() {}
			const_random_access_iterator(const random_access_iterator<It> & iterator) : _ptr(iterator._ptr) {}
			const_random_access_iterator(pointer ptr) : _ptr(ptr) {}

			const_random_access_iterator& operator=(const random_access_iterator<It> &rhs)
			{
				this->_ptr = rhs._ptr;
				return (*this);
			}

			reference operator*() const { return *_ptr; }
			pointer operator->() { return _ptr; }
			const pointer operator->() const { return _ptr; }

			reference operator[](difference_type n) const { return *(_ptr + n); }
			
			const_random_access_iterator& operator++() { ++_ptr; return *this; }
			const_random_access_iterator operator++(int) { const_random_access_iterator tmp(*this); ++_ptr; return tmp; }
			
			const_random_access_iterator& operator--() { --_ptr; return *this; }
			const_random_access_iterator operator--(int) { const_random_access_iterator tmp(*this); --_ptr; return tmp; }
			
			const_random_access_iterator& operator+=(difference_type n) { _ptr += n; return *this; }
			const_random_access_iterator& operator-=(difference_type n) { _ptr -= n; return *this; }
			
			const_random_access_iterator operator+(difference_type n) const { const_random_access_iterator tmp(*this); tmp += n; return tmp; }
			const_random_access_iterator operator-(difference_type n) const { const_random_access_iterator tmp(*this); tmp -= n; return tmp; }
			
			friend difference_type operator-(const_random_access_iterator const& lhs, const_random_access_iterator const& rhs) { return lhs._ptr - rhs._ptr; }

			friend bool operator==(const_random_access_iterator<It> const& lhs, const_random_access_iterator<It> const& rhs) { return lhs._ptr == rhs._ptr; }
			friend bool operator!=(const_random_access_iterator<It> const& lhs, const_random_access_iterator<It> const& rhs) { return lhs._ptr != rhs._ptr; }
			friend bool operator<(const_random_access_iterator<It> const& lhs, const_random_access_iterator<It> const& rhs) { return lhs._ptr < rhs._ptr; }
			friend bool operator>(const_random_access_iterator<It> const& lhs, const_random_access_iterator<It> const& rhs) { return lhs._ptr > rhs._ptr; }
			friend bool operator<=(const_random_access_iterator<It> const& lhs, const_random_access_iterator<It> const& rhs) { return lhs._ptr <= rhs._ptr; }
			friend bool operator>=(const_random_access_iterator<It> const& lhs, const_random_access_iterator<It> const& rhs) { return lhs._ptr >= rhs._ptr; }
	};
}

#endif