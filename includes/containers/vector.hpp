/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:21:08 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/01 09:39:17 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_VECTOR_HPP
# define CONTAINERS_VECTOR_HPP

# include <memory>

namespace ft
{
	class vector_iterator
	{

	};
	
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
		//	The vector's typedef
			typedef T 											value_type;
			typedef Alloc										allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;

			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef	std::ptrdiff_t								difference_type;
			typedef size_t										size_type;

		// CONSTRUCTORS
			// Default constructor
			explicit vector (const allocator_type& alloc = allocator_type());

			// Fill constructor
			explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type());

			// Range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type());

			// Copy constructor
			vector (const vector& x);

		// DESTRUCTOR
			~vector(){}
	};
}

#endif