#ifndef TYPE_CLASS
# define TYPE_CLASS
# include "IOperand.hpp"
# include "OperandCreator.hpp"
# include <vector>
# include <climits>

//AbstractVM must raise an exception
// and stop the execution of the program cleanly. It is forbidden to raise scalar exceptions.
// Moreover your exception classes must inherit from std::exception.

// • The assembly program includes one or several lexical errors or syntactic errors.
// • An instruction is unknown
// • Overflow on a value
// • Underflow on a value
// • Instruction pop on an empty stack
// • Division/modulo by 0
// • The program doesn’t have an exit instruction
// • An assert instruction is not true
// • The stack is composed of strictly less that two values when an arithmetic instruction
// is executed.

template <typename T>
class Type : public IOperand {
	T				_value;
	eOperandType	_type;
	std::string		_s;
	unsigned int	_precision;
public:
	class DivExc : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mDivision by zero exception\033[0m\n";
		}
	};
	class ModExc : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mModulo by zero exception\033[0m\n";
		}
	};
	class OverflowExc : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mOverflow exception\033[0m\n";
		}
	};
	class UnderflowExc : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mUnderflow exception\033[0m\n";
		}
	};
	class WrongTypes : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mWrong type exception: % operation requires integer types only\033[0m\n";
		}
	};


	Type() : _value(0), _type(Double), _s("0"), _precision(15){}
	Type(T value, eOperandType type = Double) : _value(value), _type(type), _s(std::to_string(value)), _precision(type){
		if (_type == 3)
			_precision = 8;
		if (_type == 4)
			_precision = 15;
	}
	~Type(){}
	Type(Type const & other){*this = other;}
	Type const & operator=(Type const & other){
		_type = other._type;
		_s = other._s;
		_precision = other._precision;
		_value = other._value;//is it okay?
		return *this;
	}

	virtual int getPrecision( void ) const {return (int)_type;}
	virtual eOperandType getType( void ) const	{return _type;}
	virtual std::string const & toString( void ) const {return _s;}
	
	int	min_val(eOperandType t) const
	{
		switch(t)
		{
			case 0: return -128;
			case 1: return -32768;
			case 2: return -2147483648;
			case 3: return -2147483648;
			case 4: return -2147483648;
		}
		return 0;
	}
	int	max_val(eOperandType t) const
	{
		switch(t)
		{
			case 0: return 127;
			case 1: return 32767;
			case 2: return 2147483647;
			case 3: return 2147483647;
			case 4: return 2147483647;
		}
		return 0;
	}

	virtual IOperand const * operator+( IOperand const & rhs ) const
	{
		eOperandType t;
		double r;
		r = std::stod(rhs.toString());
		t = std::max(_type, rhs.getType());
		try
		{
			if (_value > max_val(t) - r && t < 3)
				throw Type::OverflowExc();
			else if (_value < min_val(t) - r && t < 3)//a + b < min
				throw Type::UnderflowExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(_value + std::stod(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what();}
		exit(0);
	}

	virtual IOperand const * operator-( IOperand const & rhs ) const
	{
		eOperandType t;
		double r;
		r = std::stod(rhs.toString());
		t = std::max(_type, rhs.getType());
		try
		{
			if (_value > max_val(t) + r)
				throw Type::OverflowExc();
			else if (_value < min_val(t) + r )
				throw Type::UnderflowExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(_value - std::stod(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what();}
		exit(0);
	}

	virtual IOperand const * operator*( IOperand const & rhs ) const
	{
		eOperandType t;
		double r;
		r = std::stod(rhs.toString());
		t = std::max(_type, rhs.getType());
		try
		{
			if (r > 0 && _value > max_val(t) / r && t < 3)
				throw Type::OverflowExc();
			else if (_value < min_val(t) / r && _value > max_val(t) / r && t < 3)//a*b<Min: a<Min/b | a>-Min/b
				throw Type::UnderflowExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(_value * std::stod(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what();}
		exit(0);
	}

	virtual IOperand const * operator/( IOperand const & rhs ) const
	{
		eOperandType t;
		t = std::max(_type, rhs.getType());
		try
		{
			if (std::stod(rhs.toString()) == 0)// mb inline isZero(double a){return a < epsilon];}
				throw Type::DivExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(_value / std::stod(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what();}
		exit(0);
	}

	virtual IOperand const * operator%( IOperand const & rhs ) const
	{
		eOperandType t;
		t = std::max(_type, rhs.getType());
		try
		{
			if (std::stod(rhs.toString()) == 0)
				throw Type::ModExc();
			else if (t > 2)
				throw Type::WrongTypes();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string((int)_value % std::stoi(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what();}
		exit(0);
	}
	
	
};

#endif
