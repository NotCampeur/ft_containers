/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:21:08 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/31 17:00:29 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft
{
	class iterator
	{

	};
	
	template < typename T, typename Alloc = std::allocator<T> >
	class Vector
	{
		public:
		// CONSTRUCTORS
			// Default constructor
			explicit Vector (const allocator_type& alloc = allocator_type());

			// Fill constructor
			explicit Vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type());

			// Range constructor
			template <class InputIterator>
			Vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type());

			// Copy constructor
			Vector (const Vector& x);

		// DESTRUCTOR
			~Vector(){}

		//	The Vector's typedef
			typedef T 								value_type;
			typedef Alloc							allocator_type;

			typedef allocator_type::reference		reference;
			typedef allocator_type::const_reference	const_reference;

			typedef allocator_type::pointer			pointer;
			typedef allocator_type::const_pointer	const_pointer;

			typedef	std::ptrdiff_t					difference_type;
			typedef size_t							size_type;
	};
}

#endif