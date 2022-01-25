#ifndef VECTOR_H
# define VECTOR_H

# include <memory>
# include <cstddef>

# include "vector_iter.hpp"
# include "../iterator/iterator.hpp"
# include "../type_traits/type_traits.hpp"
# include "../algorithm/algorithm.hpp"

namespace	ft
{

	// vector DECLARATION

	template< typename T, typename Alloc = std::allocator< T > >
	class vector
	{

	public:

		// Member Types
		typedef T										value_type;
		typedef	T*										pointer;
		typedef T&										reference;
		typedef	T const*								const_pointer;
		typedef T const&								const_reference;
		typedef Alloc									allocator_type;
		typedef std::size_t								size_type;
		typedef	ptrdiff_t								difference_type;
		typedef vector_iter<T>							iterator;
		typedef vector_iter<const T>					const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const iterator>	const_reverse_iterator;

		// Member Functions

		//constructors and destructor
		explicit vector< T, Alloc >(allocator_type const & alloc =
			allocator_type());
		explicit vector< T, Alloc >(size_type n,
			value_type const & val = value_type(),
			allocator_type const & alloc = allocator_type());
		//range constructor function template
		/*
		**	HOW enable_if WORKS:
		**
		**	IF is_integral<InputIterator>::value == true THERE WILL BE
		**	NO enable_if<true, T>::type, AND THANKS TO C++'s
		**	SFINAE (Substitution Failure Is Not An Error), THE TYPE
		**	SUBSTITUTION FOR THIS TEMPLATE WILL FAIL WITHOUT GENERATING A
		**	COMPILATION ERROR AND OTHER CONTRUCTOR FUNCTIONS WILL BE CHECKED
		**	TO SEE IF ANYONE MATCHES THE REQUIRED CONSTRUCTION ARGUMENTS.
		**
		**	NOT FINDING A CONSTRUCTOR THAT MATCHES THE REQUIRED ARGUMENTS
		**	WILL RESULT IN A COMPILATION ERROR.
		**
		**	IF is_integral<InputIterator>::value == false THEN
		**	enable_if<true, T>::type EXISTS, BECAUSE THE FIRST typename OF
		**	THE enable_if TEMPLATE IS A boolean WHICH, IF ITS VALUE IS true,
		**	WILL INSTANTIATE THE enable_if<true, T> SPECIALIZATION TEMPLATE
		**	THAT DECLARES THE ::type typename.
		**
		**	WHY CONVERT enable_if<true, T>::type TO pointer (*)?
		**	SO THAT WHEN THE RANGE CONSTRUCTOR MATCHES THE PASSED ARGUMENTS,
		**	THE 4TH ARGUMENT, WHICH IS JUST TO CHECK IF THE FIRST 2 ARGUMENTS
		**	PASSED TO THE CONSTRUCTOR ARE NOT INTEGRAL, WILL BE INITIALIZED TO
		**	0 BY DEFAULT WITHOUT MATTERING WHAT IS THE TYPE THAT RETURNS
		**	enable_if<true, T>::type AS IT IS CONVERTED TO A POINTER, AND WILL
		**	NOT BE USED.
		*/
		template< typename InputIterator >
		vector< T, Alloc >(InputIterator first, InputIterator last,
			allocator_type const & alloc = allocator_type(),
			typename
			ft::enable_if< ft::is_integral<InputIterator>::value
			== false >::type * = 0);
		vector< T, Alloc >(vector< T, Alloc > const & src);
		~vector< T, Alloc >(void);

		//assignment operator overload
		vector< T, Alloc > &	operator=(vector< T, Alloc > const & rhs);

		//iterators
		iterator				begin(void);
		const_iterator			begin(void) const;
		iterator				end(void);
		const_iterator			end(void) const;
		reverse_iterator		rbegin(void);
		const_reverse_iterator	rbegin(void) const;
		reverse_iterator		rend(void);
		const_reverse_iterator	rend(void) const;

		// capacity
		size_type				size(void) const;
		size_type				capacity(void) const;
		bool					empty(void) const;
		size_type				max_size(void) const;
		void					resize(size_type n,
									value_type val = value_type());
		void					reserve(size_type n);

		// access
		reference				front(void);
		const_reference			front(void) const;
		reference				back(void);
		const_reference			back(void) const;
		reference				at(size_type n);
		const_reference			at(size_type n) const;
		reference				operator[](size_type n);
		const_reference			operator[](size_type n) const;

		// modifiers
		void					assign(size_type n, value_type const & val);
		//assign template
		template< typename InputIterator >
		void					assign(InputIterator first, InputIterator last,
			typename ft::enable_if< ft::is_integral<InputIterator>::value
			== false >::type * = 0);
		void					push_back(value_type const & val);
		void					pop_back(void);
		iterator				insert(iterator position,
									value_type const & val);
		void					insert(iterator position, size_type n,
									const value_type& val);
		//insert template
		template< typename InputIterator >
    	void					insert(iterator position, InputIterator first,
									InputIterator last,
									typename ft::enable_if
									< ft::is_integral<InputIterator>::value
									== false >::type * = 0);
		iterator				erase(iterator position);
		iterator				erase(iterator first, iterator last);
		void 					swap(vector & x);
		void					clear(void);

		// allocator
		allocator_type			get_allocator(void) const;

	private:

		// Attributes
		allocator_type	_alloc;
		pointer			_content;
		size_type		_size;
		size_type		_capacity;

		// Functions
		void			_allocate_content(size_type n,
							value_type val = value_type());
		void			_free_content(void);
		void			_modify_capacity(size_type new_cap,
							value_type val = value_type());
		void			_move_values_back(size_type from_index,
							size_type positions);
		void			_construct_insert(pointer aux, size_type needle,
							value_type const & val, size_type n);
		template< typename InputIterator >
		void			_construct_insert(pointer aux, size_type needle,
							InputIterator first, InputIterator last,
							typename ft::enable_if
							< ft::is_integral<InputIterator>::value
							== false >::type * = 0);
		void			_fill_content(size_type start_pos, size_type end_pos,
							value_type const & val);
		template< typename InputIterator >
		void			_fill_content(size_type position, InputIterator first,
							InputIterator last, typename ft::enable_if
							< ft::is_integral<InputIterator>::value
							== false >::type * = 0);


	};




	// vector DEFINITION

	// Public Members

	template< typename T, typename Alloc >
	vector< T, Alloc >::vector(allocator_type const & alloc) : _alloc(alloc),
		_content(0), _size(0), _capacity(0)
	{
		std::cout << "vector default Constructor called" << std::endl;
		return ;
	}

	template< typename T, typename Alloc >
	vector< T, Alloc >::vector(size_type n, value_type const & val,
		allocator_type const & alloc) : _alloc(alloc), _content(0),
		_size(n), _capacity(n)
	{
		std::cout << "vector fill Constructor called" << std::endl;
		this->_allocate_content(this->_capacity, val);
		return ;
	}

	template< typename T, typename Alloc >
	template< typename InputIterator >
	vector<T, Alloc>::vector(InputIterator first, InputIterator last,
		allocator_type const & alloc,
		typename
		ft::enable_if< ft::is_integral<InputIterator>::value == false >::type *)
		: _alloc(alloc), _content(0), _size(last - first), _capacity(_size)
	{
		size_type	i;

		std::cout << "vector range Constructor called" << std::endl;
		this->_allocate_content(this->_capacity);
		for (i = 0; first + i != last; ++i)
		{
			this->_content[i] = *(first + i);
		}
		return ;
	}

	template< typename T, typename Alloc >
	vector< T, Alloc >::vector(vector< T, Alloc > const & src)
		: _alloc(src._alloc), _content(0), _size(0), _capacity(0)
	{
		*this = src;
		return ;
	}

	template< typename T, typename Alloc >
	vector< T, Alloc >::~vector(void)
	{
		std::cout << "vector Destructor called" << std::endl;
		this->_free_content();
		return ;
	}

	template< typename T, typename Alloc >
	vector< T, Alloc > &
		vector< T, Alloc >::operator=(vector< T, Alloc > const & rhs)
	{
		size_type	i;

		if (this != &rhs)
		{
			if (this->_capacity != rhs._capacity)
			{
				this->_free_content();
				this->_content = this->_alloc.allocate(rhs._capacity);
				for (i = 0; i < rhs._size; ++i)
					this->_alloc.construct(this->_content + i, rhs._content[i]);
				for (; i < rhs._capacity; ++i)
					this->_alloc.construct(this->_content + i, value_type());
				this->_capacity = rhs._capacity;
			}
			else
			{
				for (i = 0; i < rhs._size; ++i)
					this->_content[i] = rhs._content[i];
			}
			this->_size = rhs._size;
		}
		return (*this);
	}

	// iterator Functions

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::iterator	vector< T, Alloc >::begin(void)
	{
		iterator	it(this->_content);

		return (it);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::const_iterator
		vector< T, Alloc >::begin(void) const
	{
		const_iterator	it(this->_content);

		return (it);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::iterator	vector< T, Alloc >::end(void)
	{
		iterator	it(this->_content + this->_size);

		return (it);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::const_iterator
		vector< T, Alloc >::end(void) const
	{
		const_iterator	it(this->_content + this->_size);

		return (it);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::reverse_iterator
		vector< T, Alloc >::rbegin(void)
	{
		reverse_iterator	it(this->_content + this->_size);

		return (it);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::const_reverse_iterator
		vector< T, Alloc >::rbegin(void) const
	{
		const_reverse_iterator	it(this->_content + this->_size);

		return (it);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::reverse_iterator
		vector< T, Alloc >::rend(void)
	{
		reverse_iterator	it(this->_content);

		return (it);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::const_reverse_iterator
		vector< T, Alloc >::rend(void) const
	{
		const_reverse_iterator	it(this->_content);

		return (it);
	}

	// capacity Functions

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::size_type
		vector< T, Alloc >::size(void) const
	{
		return (this->_size);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::size_type
		vector< T, Alloc >::capacity(void) const
	{
		return (this->_capacity);
	}

	template< typename T, typename Alloc >
	bool	vector< T, Alloc >::empty(void) const
	{
		return (!this->_size);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::size_type
		vector< T, Alloc >::max_size(void) const
	{
		return (this->_alloc.max_size());
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::resize(size_type n, value_type val)
	{
		size_type	i;

		//TEST CASE: n = 0

		// Will reallocate memory if new size is greater than current capacity.
		if (n > this->_capacity)
			this->_modify_capacity(this->_size * 2 >= n
				? this->_size * 2 : n, val);
		/*
		** Will reallocate memory if n is more than 2 times lower than current
		** capacity to optimize memory usage.
		*/
		else if (n < this->_capacity)
		{
			if (static_cast<float>(this->_capacity) / static_cast<float>(n)
				> static_cast<float>(2))
				this->_modify_capacity(n * 2, val);
		}
		/*
		** If any memory reallocation was done, this->_size would be equal to n,
		** and will not enter the for loop.
		*/
		for (i = this->_size; i < n; ++i)
			this->_content[i] = val;
		this->_size = n;
		return ;
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::reserve(size_type n)
	{
		if (n <= this->_capacity)
			return ;
		this->_modify_capacity(n);
		return ;
	}

	// access Functions

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::reference	vector< T, Alloc >::front(void)
	{
		//std::cout << "front called ";
		return (*this->_content);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::const_reference
		vector< T, Alloc >::front(void) const
	{
		//std::cout << "const front called ";
		return (*this->_content);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::reference	vector< T, Alloc >::back(void)
	{
		//std::cout << "back called ";
		return (this->_content[this->_size - 1]);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::const_reference
		vector< T, Alloc >::back(void) const
	{
		//std::cout << "const back called ";
		return (this->_content[this->_size - 1]);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::reference
		vector< T, Alloc >::at(size_type n)
	{
		//std::cout << "at called ";
		if (n >= this->_size)
			throw std::out_of_range("Bad index");
		return (this->_content[n]);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::const_reference
		vector< T, Alloc >::at(size_type n) const
	{
		//std::cout << "const at called ";
		if (n >= this->_size)
			throw std::out_of_range("Bad index");
		return (this->_content[n]);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::reference
		vector< T, Alloc >::operator[](size_type n)
	{
		//std::cout << "operator[] called ";
		return (this->_content[n]);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::const_reference
		vector< T, Alloc >::operator[](size_type n) const
	{
		//std::cout << "const operator[] called ";
		return (this->_content[n]);
	}

	// modifier Functions

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::assign(size_type n, value_type const & val)
	{
		this->_free_content();
		this->_size = n;
		this->_capacity = this->_size;
		this->_allocate_content(this->_capacity, val);
		return ;
	}

	template< typename T, typename Alloc >
	template< typename InputIterator >
	void	vector< T, Alloc >::assign(InputIterator first, InputIterator last,
				typename ft::enable_if< ft::is_integral<InputIterator>::value
				== false >::type *)
	{
		size_type	i;

		std::cout << "ASSIGN RANGED CALLED" << std::endl;
		this->_free_content();
		this->_size = last - first;
		this->_capacity = this->_size;
		this->_content = this->_alloc.allocate(this->_capacity);
		for (i = 0; first + i != last; ++i)
		{
			this->_alloc.construct(this->_content + i, *(first + i));
		}
		return ;
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::push_back(value_type const & val)
	{
		if (this->_size + 1 > this->_capacity)
		{
			this->_modify_capacity(this->_size ? this->_size * 2 : 2);
		}
		this->_content[this->_size] = val;
		this->_size += 1;
		return ;
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::pop_back(void)
	{
		if (this->_size)
			this->_size -= 1;
		return ;
	}

	template< typename T, typename Alloc >
	typename vector<T, Alloc>::iterator
		vector< T, Alloc >::insert(iterator position, value_type const & val)
	{
		size_type	pos_index;
		pointer		aux;
		size_type	new_capacity;

		pos_index = position - this->begin();
		if (this->_size == this->_capacity)
		{
			new_capacity = this->_capacity ? this->_capacity * 2 : 2;
			aux = this->_alloc.allocate(new_capacity);
			this->_construct_insert(aux, pos_index, val, 1);
			this->_free_content();
			this->_content = aux;
			this->_capacity = new_capacity;
		}
		else
		{
			this->_move_values_back(pos_index, 1);
			this->_content[pos_index] = val;
		}
		this->_size += 1;
		return (this->begin() + pos_index);
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::insert(iterator position, size_type n,
				value_type const & val)
	{
		size_type	pos_index;
		pointer		aux;
		size_type	new_capacity;

		pos_index = position - this->begin();
		if (this->_size + n > this->_capacity)
		{
			new_capacity = this->_capacity * 2 >= this->_size + n
				? this->_capacity * 2 : this->_size + n;
			aux = this->_alloc.allocate(new_capacity);
			this->_construct_insert(aux, pos_index, val, n);
			this->_free_content();
			this->_content = aux;
			this->_capacity = new_capacity;
		}
		else
		{
			this->_move_values_back(pos_index, n);
			this->_fill_content(pos_index, pos_index + n, val);
		}
		this->_size += n;
		return ;
	}

	template< typename T, typename Alloc >
	template< typename InputIterator >
    void	vector<T, Alloc>::insert(iterator position, InputIterator first,
				InputIterator last, typename ft::enable_if
				< ft::is_integral<InputIterator>::value == false >::type *)
	{
		pointer		aux;
		size_type	pos_index;
		size_type	n;
		size_type	new_capacity;

		pos_index = position - this->begin();
		n = last - first;
		if (this->_size + n > this->_capacity)
		{
			new_capacity = this->_capacity * 2 >= this->_size + n
				? this->_capacity * 2 : this->_size + n;
			aux = this->_alloc.allocate(new_capacity);
			this->_construct_insert(aux, pos_index, first, last);
			this->_free_content();
			this->_content = aux;
			this->_capacity = new_capacity;
		}
		else
		{
			this->_move_values_back(pos_index, n);
			this->_fill_content(pos_index, first, last);
		}
		this->_size += n;
		return ;
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::iterator
		vector< T, Alloc >::erase(iterator position)
	{
		size_type	pos_index;
		size_type	i;

		pos_index = position - this->begin();
		for (i = pos_index + 1; i < this->_size; ++i)
		{
			this->_content[i - 1] = this->_content[i];
		}
		this->resize(this->_size - 1);
		return (this->begin() + pos_index);
	}

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::iterator
		vector< T, Alloc >::erase(iterator first, iterator last)
	{
		size_type	pos_index;
		size_type	num_elements;
		size_type	i;

		pos_index = first - this->begin();
		num_elements = last - first;
		for (i = pos_index + num_elements; i < this->_size; ++i)
		{
			this->_content[i - num_elements] = this->_content[i];
		}
		this->_resize(this->_size - num_elements);
		return (this->_begin() + pos_index);
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::swap(vector<T, Alloc> & x)
	{
		pointer	aux_content;
		size_type	aux_capacity;
		size_type	aux_size;

		if (this != &x)
		{
			aux_content = this->_content;
			aux_capacity = this->_capacity;
			aux_size = this->_size;
			this->_content = x._content;
			this->_capacity = x._capacity;
			this->_size = x._size;
			x._content = aux_content;
			x._capacity = aux_capacity;
			x._size = aux_size;
		}
		return ;
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::clear(void)
	{
		this->_free_content();
		this->_capacity = 0;
		this->_size = 0;
		return ;
	}

	// allocator Function

	template< typename T, typename Alloc >
	typename vector< T, Alloc >::allocator_type
		vector< T, Alloc >::get_allocator(void) const
	{
		return (this->_alloc);
	}

	// Private Members


	template< typename T, typename Alloc >
	void	vector< T, Alloc >::_allocate_content(size_type n, value_type val)
	{
		size_type	i;

		this->_content = this->_alloc.allocate(n);
		for (i = 0; i < n; i++)
			this->_alloc.construct(this->_content + i, val);
		return ;
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::_free_content(void)
	{
		if (!this->_capacity)
			return ;
		this->_alloc.destroy(this->_content);
		this->_alloc.deallocate(this->_content, this->_capacity);
		return ;
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::_modify_capacity(size_type new_cap,
		value_type val)
	{
		pointer		aux;
		size_type	end_old_content;
		size_type	i;

		aux = this->_alloc.allocate(new_cap);
		end_old_content = this->_size <= new_cap ? this->_size : new_cap;
		for (i = 0; i < end_old_content; ++i)
			this->_alloc.construct(aux + i, this->_content[i]);
		this->_free_content();
		this->_capacity = new_cap;
		for (i = end_old_content; i < this->_capacity; ++i)
			this->_alloc.construct(aux + i, val);
		this->_content = aux;
		return ;
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::_move_values_back(size_type from_index,
				size_type positions)
	{
		size_type	i;
	
		for (i = this->_size - 1; i > from_index; --i)
		{
			this->_content[i + positions] = this->_content[i];
		}
		this->_content[i + positions] = this->_content[i];
		return ;
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::_construct_insert(pointer aux, size_type needle,
				value_type const & val, size_type n)
	{
		size_type	new_capacity;
		size_type	i;
		size_type	j;

		new_capacity = this->_capacity + n;
		for (i = 0; i < needle; ++i)
		{
			this->_alloc.construct(aux + i, this->_content[i]);
		}
		for (i = needle; i < needle + n; ++i)
		{
			this->_alloc.construct(aux + i, val);
		}
		for (j = needle; j < this->_size; ++j, ++i)
		{
			this->_alloc.construct(aux + i, this->_content[j]);
		}
		for (; i < new_capacity; ++i)
		{
			this->_alloc.construct(aux + i, val);
		}
		return ;
	}

	template< typename T, typename Alloc >
	template< typename InputIterator >
	void	vector< T, Alloc >::_construct_insert(pointer aux, size_type needle,
				InputIterator first, InputIterator last, typename ft::enable_if
				< ft::is_integral<InputIterator>::value == false >::type *)
	{
		size_type		new_capacity;
		size_type		i;
		size_type		j;
		InputIterator	it;

		new_capacity = this->_capacity + (last - first);
		for (i = 0; i < needle; ++i)
		{
			this->_alloc.construct(aux + i, this->_content[i]);
		}
		for (it = first; it != last; ++it, ++i)
		{
			this->_alloc.construct(aux + i, *it);
		}
		for (j = needle; j < this->_size; ++j, ++i)
		{
			this->_alloc.construct(aux + i, this->_content[j]);
		}
		for (; i < new_capacity; ++i)
		{
			this->_alloc.construct(aux + i, *first);
		}
		return ;
	}

	template< typename T, typename Alloc >
	void	vector< T, Alloc >::_fill_content(size_type start_pos,
				size_type end_pos, value_type const & val)
	{
		size_type	i;

		for (i = start_pos; i < end_pos; ++i)
		{
			this->_content[i] = val;
		}
		return ;
	}

	template< typename T, typename Alloc >
	template< typename InputIterator >
	void	vector< T, Alloc >::_fill_content(size_type position,
				InputIterator first, InputIterator last, typename ft::enable_if
				< ft::is_integral<InputIterator>::value == false >::type *)
	{
		size_type		i;
		InputIterator	it;

		for (i = position, it = first; it != last; ++i, ++it)
		{
			this->_content[i] = *it;
		}
		return ;
	}

	//Non-member function overloads

	template< typename T, typename Alloc >
	void	swap(vector<T,Alloc> & x, vector<T,Alloc> & y)
	{
		if (&x != &y)
			x.swap(y);
		return ;
	}

	template < typename T, typename Alloc >
	bool	operator==(vector< T, Alloc > const & lhs,
				vector< T, Alloc > const & rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template < typename T, typename Alloc >
	bool	operator!=(vector< T, Alloc > const & lhs,
				vector< T, Alloc > const & rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename T, typename Alloc>
	bool	operator<(vector< T, Alloc > const & lhs,
				vector< T, Alloc > const & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end()));
	}

	template <typename T, typename Alloc>
	bool	operator<=(vector< T, Alloc > const & lhs,
				vector< T, Alloc > const & rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename T, typename Alloc>
	bool	operator>(vector< T, Alloc > const & lhs,
				vector< T, Alloc > const & rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, typename Alloc>
	bool	operator>=(vector< T, Alloc > const & lhs,
				vector< T, Alloc > const & rhs)
	{
		return (!(lhs < rhs));
	}

}

#endif