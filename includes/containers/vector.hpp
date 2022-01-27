/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:21:08 by ldutriez          #+#    #+#             */
/*   Updated: 2022/01/26 17:05:16 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_VECTOR_HPP
# define CONTAINERS_VECTOR_HPP

# include <memory>
# include <sstream>
# include <exception>
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "is_integral.hpp"
# include "distance.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
		//	The vector's typedef
			typedef T 												value_type;
			typedef Alloc											allocator_type;

			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;

			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

			typedef ft::random_access_iterator< value_type >		iterator;
			typedef ft::const_random_access_iterator< value_type >	const_iterator;
			typedef ft::reverse_iterator< iterator >				reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >			const_reverse_iterator;
			typedef	std::ptrdiff_t									difference_type;

			typedef size_t											size_type;
			
		private:
			Alloc		_alloc;
			pointer		_array;
			size_type	_size;
			size_type	_capacity;

			// Private modifiers functions used to indicate if the type can be used.
			void		assign(size_type n, const value_type& val, ft::true_type)
			{
				size_type	new_capacity(1);

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				for (; new_capacity < n; new_capacity = new_capacity << 1){};
				reserve(new_capacity);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&_array[i], val);
				_size = n;
			}
			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last, ft::false_type)
			{
				size_type n = last - first;
				while (n > _capacity)
					reserve(_capacity * 2);
				for (size_type i(0); i < _size; i++)
					_alloc.destroy(&_array[i]);
				for (size_type i(0); first < last; i++)
				{
					_alloc.construct(&_array[i], *first);
					first++;
				}
				_size = n;
			}

			void		insert(iterator pos, size_type n, const value_type& val, ft::true_type)
			{
				if (n == 0)
					return ;
				if (pos == end())
				{
					if (_size +  n > _capacity)
						resize(_size + n);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(&_array[_size - n + i], val);
				}
				else
				{
					if (_size +  n > _capacity)
						resize(_size + n);					
					for (difference_type i = _size - 1; i > distance(begin(), pos); i--)
					{
						_alloc.construct(&_array[i + n], _array[i]);
					}
					for (difference_type i = 0; i < static_cast<difference_type>(n); i++)
						_alloc.construct(&_array[_size - n + i], val);
				}
			}
			template <class InputIterator>
			void		insert(iterator pos, InputIterator first, InputIterator last, ft::false_type)
			{
				size_t range;

				long temp_pos;
				Alloc alloc;
				
				long end_old_vector = end() - begin() - 1;
				range = ft::distance(first, last);
				long end_new_vector = end_old_vector + range;

				int nb_element_to_switch = end() - pos;
				temp_pos = pos - begin() + range;
				if ((_size + range) > _size)
				{
					resize(_size + range);
				}
				size_t i = 0;
				if (end_old_vector == 0)
				{
					while (i < range)
					{
						_array[i] = *first;
						first++;
						i++;
					}
					return ;
				}
				int temp_range = range;

				while (nb_element_to_switch)
				{
					_array[end_new_vector] = _array[end_old_vector - i];
					nb_element_to_switch--;
					end_new_vector--;
					i++;
				}
				temp_range -= i;
				while (temp_range > 0)
				{
					last--;
					_array[end_new_vector] =  *last;
					temp_range--;
					end_new_vector--;
				}
				while (first != last)
				{
					last--;
					_array[end_new_vector] = *last;
					end_new_vector--;
				}
			}
			
		public:
		// CONSTRUCTORS
			// Default constructor
			explicit vector (const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _array(NULL), _size(0), _capacity(0)
			{}

			// Fill constructor
			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _array(NULL), _size(0), _capacity(1)
			{
				while (_capacity < n)
					_capacity = _capacity << 1;
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&_array[i], val);
				_size = n;
			}

			// Range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _array(NULL), _size(0), _capacity(0)
			{
				assign(first, last);
			}

			// Copy constructor
			vector (const vector& x)
			: _alloc(x._alloc), _array(NULL), _size(x._size), _capacity(x._capacity)
			{
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_array[i], x._array[i]);
			}
			vector &operator=(const vector& x)
			{
				assign(x.begin(), x.end());
				return *this;
			}
		// DESTRUCTOR
			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_alloc.deallocate(_array, _size);
			}

		// Iterators
			iterator begin()
			{
				return iterator(_array);
			}
			const_iterator begin() const
			{
				return const_iterator(_array);
			}
			iterator end()
			{
				return iterator(_array + _size);
			}
			const_iterator end() const
			{
				return const_iterator(_array + _size);
			}
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

		// Capacity
			size_type	size() const { return _size; }
			size_type	max_size() const { return _alloc.max_size(); }
			void		resize(size_type n, value_type val = value_type())
			{
				reserve(n + 1);
				if (n > _size)
				{
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&_array[i], val);
				}
				else if (n < _size)
				{
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(&_array[i]);
				}
				_size = n;
			}
			size_type	capacity() const { return _capacity; }
			bool		empty() const { return _size == 0; }
			void		reserve(size_type n)
			{
				if (n > _capacity)
				{
					pointer tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&tmp[i], _array[i]);
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&_array[i]);
					_alloc.deallocate(_array, _capacity);
					_array = tmp;
					_capacity = n;
				}
			}
			
		// Element access
			reference	operator[] (size_type n)
			{
				return _array[n];
			}
			const_reference	operator[] (size_type n) const
			{
				return _array[n];
			}
			reference	at(size_type n)
			{
				_M_range_check(n); 
				return _array[n];
			}
			const_reference	at(size_type n) const
			{
				_M_range_check(n); 
				return _array[n];
			}
			reference	front() { return _array[0]; }
			const_reference	front() const { return _array[0]; }
			reference	back() { return _array[_size - 1]; }
			const_reference	back() const { return _array[_size - 1]; }

		// Modifiers
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				assign(first, last, ft::is_integral<InputIterator>());
			}

			void assign (size_type n, const T& val)
			{
				assign(n, val, ft::true_type());
			}
			// void		assign(size_type n, const value_type& val)
			// {
			// 	while (n > _capacity)
			// 		reserve(_capacity * 2);
			// 	for (size_type i = 0; i < _size; i++)
			// 		_alloc.destroy(&_array[i]);
			// 	for (size_type i = 0; i < n; i++)
			// 		_alloc.construct(&_array[i], val);
			// 	_size = n;
			// }
			// template <class InputIterator>
			// void		assign(InputIterator first, InputIterator last)
			// {
			// 	size_type n = last - first;
			// 	while (n > _capacity)
			// 		reserve(_capacity * 2);
			// 	for (size_type i(0); i < _size; i++)
			// 		_alloc.destroy(&_array[i]);
			// 	for (size_type i(0); first < last; i++ && first++)
			// 		_alloc.construct(&_array[i], *first);
			// 	_size = n;
			// }
			void		push_back(const value_type& val)
			{
				if (_capacity == 0)
					reserve(1);
				else if (_size == _capacity)
					reserve(_capacity * 2);
				_alloc.construct(&_array[_size], val);
				_size++;
			}
			void		pop_back()
			{
				_alloc.destroy(&_array[_size - 1]);
				_size--;
			}
			
			iterator	insert(iterator pos, const value_type& val)
			{
				if (_capacity == 0)
					reserve(1);
				else if (_size == _capacity)
					reserve(_size);
				for (long i = _size; i > pos - _array; i--)
					_alloc.construct(&_array[i], _array[i - 1]);
				_alloc.construct(&_array[pos - _array], val);
				_size++;
				return pos;
			}
			
			void insert (iterator pos, size_type n, const value_type& val)
			{
				insert(pos, n, val, ft::true_type());
			}

			template <class InputIterator>
			void insert (iterator pos, InputIterator first, InputIterator last)
			{
				insert(pos, first, last, ft::is_integral<InputIterator>());
			}
			// void		insert(iterator pos, size_type n, const value_type& val)
			// {
			// 	if (_size + n > _capacity)
			// 		reserve(_capacity * 2);
			// 	for (size_type i = _size; i > pos; i--)
			// 		_alloc.construct(&_array[i], _array[i - 1]);
			// 	for (size_type i = 0; i < n; i++)
			// 		_alloc.construct(&_array[pos + i], val);
			// 	_size += n;
			// }
			// template <class InputIterator>
			// void		insert(iterator pos, InputIterator first, InputIterator last)
			// {
			// 	size_type n = last - first;
			// 	if (_size + n > _capacity)
			// 		reserve(_capacity * 2);
			// 	for (size_type i = _size; i > pos; i--)
			// 		_alloc.construct(&_array[i], _array[i - 1]);
			// 	for (size_type i = 0; first < last; i++)
			// 		_alloc.construct(&_array[pos + i], *(first + i));
			// 	_size += n;
			// }
			iterator	erase(iterator pos)
			{
				iterator it_end = end();
				iterator temp = pos;
				Alloc alloc;

				while (temp != (it_end - 1))
				{
					_array[temp - begin()] = *(temp + 1); 
					temp++;
				}
				alloc.destroy(&_array[temp - begin()]);
				_size--;
				return pos;
			}
			iterator	erase(iterator first, iterator last)
			{
				for (; first != last; last--)
					erase(last);
				return first;
			}
			void		swap(vector& x)
			{
				std::swap(_array, x._array);
				std::swap(_size, x._size);
				std::swap(_capacity, x._capacity);
			}
			void		clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_size = 0;
			}
		
		// Allocator
			allocator_type	get_allocator() const { return _alloc; }

			private:
				void	_M_range_check(size_type n)
				{
					if (n >= _size)
					{
						std::ostringstream	s;
						std::string			str("vector::_M_range_check: n (which is ");

						s << n;
						str += s.str();
						str += ") >= this_size() (which is ";
						s.str("");
						s.clear();
						s << _size;
						str += s.str();
						str += ")";
						throw std::out_of_range(str);
					}
				}
	};
	template <class T, class Alloc>
	bool	operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}
	
	template <class T, class Alloc>
	bool	operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool	operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool	operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return !(rhs > lhs);
	}

	template <class T, class Alloc>
	bool	operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		if (lhs != rhs)
			return !(rhs < lhs);
		return false;
	}

	template <class T, class Alloc>
	bool	operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void	swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif