#ifndef TYPE_CLASS
# define TYPE_CLASS
# include "IOperand.hpp"
# include <vector>

template <typename T>
class Type : public IOperand {
// In order to choose the right member function for the creation of the new IOperand,
// you MUST create and use an array (here, a vector shows little interest) of pointers on
// member functions with enum values as index.
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
public:
	Type(){}
	~Type(){}
	Type(Type const & other){*this = other;}
	Type const & operator=(Type const & other)
	{
		return *this;
	}

	typedef std::function< IOperand const *(std::string const & value) > funcptr; 
	IOperand const * createOperand( eOperandType type, std::string const & value ) const
	{
		std::vector<funcptr> f;
		f.push_back(this->createInt8);
		f.push_back(this->createInt16);
		f.push_back(this->createInt32);
		f.push_back(this->createFloat);
		f.push_back(this->createDouble);
		for (int i = Int8; i != Double; i++)
			if (i == type)
				return (f[i](value));
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
