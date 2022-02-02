/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:41:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/02/02 17:04:56 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_PAIR_HPP
# define CONTAINERS_PAIR_HPP

namespace ft
{
	template< class T1, class T2 >
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(), second() {}
		pair( const T1& x, const T2& y ) : first( x ), second( y ) {}
		
		// Copy constructor
		pair( const pair& p ) : first( p.first ), second( p.second ) {}
		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ) : first( p.first ), second( p.second ) {}

		pair& operator=( const pair& other )
		{
			first = other.first;
			second = other.second;
			return *this;
		}
	};

	template< class T1, class T2 >
	pair<T1, T2> make_pair( T1 t, T2 u )
	{
		return pair<T1, T2>( t, u );
	}

	template< class T1, class T2 >
	bool operator==( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator!=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
	bool operator<( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
	{
		if ( lhs.first < rhs.first )
			return true;
		else if ( lhs.first == rhs.first )
			return ( lhs.second < rhs.second );
		return false;
	}

	template< class T1, class T2 >
	bool operator<=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
	{
		return rhs < lhs;
	}

	template< class T1, class T2 >
	bool operator>=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
	{
		return !(lhs < rhs);
	}
}

#endif