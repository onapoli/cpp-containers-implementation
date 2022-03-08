#ifndef STACK_H
# define STACK_H

# include "vector.hpp"

namespace	ft
{
	template< typename T, typename Container = ft::vector<T> >
	class	stack
	{
	
	public:
		//Member types
		typedef T			value_type;
		typedef Container	container_type;
		typedef std::size_t	size_type;
		//Member functions
		explicit stack< T, Container >(container_type const & ctnr
			= container_type());

		bool				empty(void) const;
		size_type			size(void) const;
		value_type &		top(void);
		value_type const &	top(void) const;
		void				push(value_type const & val);
		void				pop(void);

		//Non-Member functions
		/*
		**	DECLARED HERE TO ADD THE friend KEYWORD, THAT WILL
		**	ALLOW BOTH stacks TO ACCESS ITS PRIVATE MEMBERS.
		*/
		friend bool	operator==(stack< T, Container > const & lhs,
						stack< T, Container > const & rhs)
		{
			return (lhs._ctnr == rhs._ctnr);
		}
		friend bool	operator!=(stack< T, Container > const & lhs,
						stack< T, Container > const & rhs)
		{
			return (lhs._ctnr != rhs._ctnr);
		}
		friend bool	operator<(stack< T, Container > const & lhs,
						stack< T, Container > const & rhs)
		{
			return (lhs._ctnr < rhs._ctnr);
		}
		friend bool	operator<=(stack< T, Container > const & lhs,
						stack< T, Container > const & rhs)
		{
			return (lhs._ctnr <= rhs._ctnr);
		}
		friend bool	operator>(stack< T, Container > const & lhs,
						stack< T, Container > const & rhs)
		{
			return (lhs._ctnr > rhs._ctnr);
		}
		friend bool	operator>=(stack< T, Container > const & lhs,
						stack< T, Container > const & rhs)
		{
			return (lhs._ctnr >= rhs._ctnr);
		}

	private:
		container_type	_ctnr;
	};

	template< typename T, typename Container >
	stack< T, Container >::stack(container_type const & ctnr) : _ctnr(ctnr)
	{
		//CUIDADO, DICE LA REFERENCIA QUE ALMACENA UNA COPIA. COMPROBAR SI ES ASÍ.
		return ;
	}

	template< typename T, typename Container >
	bool	stack< T, Container >::empty(void) const
	{
		return (this->_ctnr.empty());
	}

	template< typename T, typename Container >
	typename stack< T, Container >::size_type
		stack< T, Container >::size(void) const
	{
		return (this->_ctnr.size());
	}

	template< typename T, typename Container >
	typename stack< T, Container >::value_type &
		stack< T, Container >::top(void)
	{
		return (this->_ctnr.back());
	}

	template< typename T, typename Container >
	typename stack< T, Container >::value_type const &
		stack< T, Container >::top(void) const
	{
		return (this->_ctnr.back());
	}

	template< typename T, typename Container >
	void	stack< T, Container >::push(value_type const & val)
	{
		this->_ctnr.push_back(val);
		return ;
	}

	template< typename T, typename Container >
	void	stack< T, Container >::pop(void)
	{
		this->_ctnr.pop_back();
		return ;
	}

}

#endif