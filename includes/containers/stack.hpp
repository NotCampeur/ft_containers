/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:23:00 by notcampeur        #+#    #+#             */
/*   Updated: 2022/02/01 17:20:25 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_STACK_HPP
# define CONTAINERS_STACK_HPP

# include <vector.hpp>

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		protected:
			Container									c;
			
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
			
			explicit stack( const Container& cont = Container() ) : c(cont) {}
			stack( const stack& other ) : c(other.c) {}
			~stack() {}

			stack&	operator=( const stack& other ) { c = other.c; return *this; }

			// Element access
			reference	top() { return c.back(); }
			const_reference	top() const { return c.back(); }

			// Capacity
			bool	empty() const { return c.empty(); }
			size_type	size() const { return c.size(); }

			// Modifiers
			void	push( const value_type& val ) { c.push_back(val); }
			void	pop() { c.pop_back(); }
			
			friend bool	operator==( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
			{
				return lhs.c == rhs.c;
			}
			
			friend bool	operator<( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
			{
				return lhs.c < rhs.c;
			}
	};


	template< class T, class Container >
	bool	operator!=( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T, class Container >
	bool	operator<=( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
	{
		return !(lhs > rhs);
	}

	template< class T, class Container >
	bool	operator>( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
	{
		return rhs < lhs;
	}

	template< class T, class Container >
	bool	operator>=( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
	{
		return !(lhs < rhs);
	}
}

#endif