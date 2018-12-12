#ifndef TYPE_CLASS
# define TYPE_CLASS
# include "IOperand.hpp"
# include <vector>

template <typename T>
class Type : public IOperand {
// In order to choose the right member function for the creation of the new IOperand,
// you MUST create and use an array (here, a vector shows little interest) of pointers on
// member functions with enum values as index.
	
public:
	Type(){}
	~Type(){}
	Type(Type const & other){*this = other;}
	Type const & operator=(Type const & other)
	{
		return *this;
	}

	

	// virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
	// virtual eOperandType getType( void ) const = 0; // Type of the instance
	// virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
	// virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
	// virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
	// virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
	// virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
	// virtual std::string const & toString( void ) const = 0; // String representation of the instance
	// virtual ~IOperand( void ) {}
};

#endif
