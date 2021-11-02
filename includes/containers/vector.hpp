/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:21:08 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/02 12:45:33 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_VECTOR_HPP
# define CONTAINERS_VECTOR_HPP

# include <memory>
# include <sstream>
# include <exception>

namespace ft
{
	// class vector_iterator
	// {

	// };
	
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
		//	The vector's typedef
			typedef T 													value_type;
			typedef Alloc												allocator_type;

			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;

			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;

			typedef std::iterator< std::random_access_iterator_tag, T > iterator;
			typedef std::iterator< std::random_access_iterator_tag, T > const_iterator;
			typedef std::reverse_iterator< iterator >					reverse_iterator;
			typedef std::reverse_iterator< const_iterator >				const_reverse_iterator;

			typedef	std::ptrdiff_t										difference_type;
			typedef size_t												size_type;
			
		private:
			Alloc		_alloc;
			pointer		_array;
			size_type	_size;
			size_type	_capacity;

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
			}

			// Range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _array(NULL), _size(0), _capacity(0)
			{
				for (; first != last; first++)
					push_back(*first);
			}

			// Copy constructor
			vector (const vector& x)
			: _alloc(x._alloc), _array(NULL), _size(x._size), _capacity(x._capacity)
			{
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_array[i], x._array[i]);
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
				return _array;
			}
			const_iterator begin() const
			{
				return _array;
			}
			iterator end()
			{
				return _array + _size;
			}
			const_iterator end() const
			{
				return _array + _size;
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
				while (n > _capacity)
					reserve(_capacity);
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
			void		assign(size_type n, const value_type& val)
			{
				while (n > _capacity)
					reserve(_capacity * 2);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&_array[i], val);
				_size = n;
			}
			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last)
			{
				size_type n = last - first;
				while (n > _capacity)
					reserve(_capacity * 2);
				for (size_type i(0); i < _size; i++)
					_alloc.destroy(&_array[i]);
				for (size_type i(0); first < last; i++ && first++)
					_alloc.construct(&_array[i], *first);
				_size = n;
			}
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
				if (_size == _capacity)
					reserve(_capacity * 2);
				for (size_type i = _size; i > pos; i--)
					_alloc.construct(&_array[i], _array[i - 1]);
				_alloc.construct(&_array[pos], val);
				_size++;
				return pos;
			}
			void		insert(iterator pos, size_type n, const value_type& val)
			{
				if (_size + n > _capacity)
					reserve(_capacity * 2);
				for (size_type i = _size; i > pos; i--)
					_alloc.construct(&_array[i], _array[i - 1]);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&_array[pos + i], val);
				_size += n;
			}
			template <class InputIterator>
			void		insert(iterator pos, InputIterator first, InputIterator last)
			{
				size_type n = last - first;
				if (_size + n > _capacity)
					reserve(_capacity * 2);
				for (size_type i = _size; i > pos; i--)
					_alloc.construct(&_array[i], _array[i - 1]);
				for (size_type i = 0; first < last; i++ && first++)
					_alloc.construct(&_array[pos + i], *first);
				_size += n;
			}
			iterator	erase(iterator pos)
			{
				for (size_type i = pos; i < _size - 1; i++)
					_alloc.construct(&_array[i], _array[i + 1]);
				_alloc.destroy(&_array[_size - 1]);
				_size--;
				return pos;
			}
			iterator	erase(iterator first, iterator last)
			{
				for (size_type i = first; i < last; i++)
					_alloc.destroy(&_array[i]);
				for (size_type i = last; i < _size - 1; i++)
					_alloc.construct(&_array[i], _array[i + 1]);
				_size -= last - first;
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
}

#endif