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
	int				_precision;
public:
	class DivExc : public std::exception
	{
		public:
		DivExc();
		~DivExc() throw() ;
		DivExc(DivExc const & other);
		DivExc const & operator=(DivExc const & other);
		virtual const char*  what() const throw();
	};
	class ModExc : public std::exception
	{
		public:
		ModExc();
		~ModExc() throw() ;
		ModExc(ModExc const & other);
		ModExc const & operator=(ModExc const & other);
		virtual const char*  what() const throw();
	};
	class OverflowExc : public std::exception
	{
		public:
		OverflowExc();
		~OverflowExc() throw() ;
		OverflowExc(OverflowExc const & other);
		OverflowExc const & operator=(OverflowExc const & other);
		virtual const char*  what() const throw();
	};
	class UnderflowExc : public std::exception
	{
		public:
		UnderflowExc();
		~UnderflowExc() throw() ;
		UnderflowExc(UnderflowExc const & other);
		UnderflowExc const & operator=(UnderflowExc const & other);
		virtual const char*  what() const throw();
	};

	Type() : _value(0), _type(Double), _precision(4) {}
	Type(T value, eOperandType type = Double) : _value(value), _type(type), _precision(type){}
	~Type(){}
	Type(Type const & other){*this = other;}
	Type const & operator=(Type const & other){
		_type = other._type;
		_precision = other._precision;
		_value = other._value;//is it okay?
		return *this;
	}

	virtual int getPrecision( void ) const {return _precision;}
	virtual eOperandType getType( void ) const	{return _type;}
	
	int		min_val(eOperandType t)
	{
		switch(t)
		{
			case 0: return 127;
			case 1: return 32767;
			case 2: return 2147483647;
			case 3: return 2147483647;// float ? ??????????????????????????????????/
			case 4: return 2147483647;// double ?????????????????????????
		}
		return 0;
	}
	int		max_val(eOperandType t)
	{
		switch(t)
		{
			case 0: return -128;
			case 1: return -32768;
			case 2: return -2147483648;
			case 3: return -2147483648;// float ? ??????????????????????????????????/
			case 4: return -2147483648;// double ?????????????????????????
		}
		return 0;
	}

	virtual IOperand const * operator+( IOperand const & rhs ) const
	{
		eOperandType t = std::max(_type, rhs.getType());
		double r = std::stod(rhs.toString());
		try
		{
			if (_value > max_val(t) - r)
				throw Type::OverflowExc("\x1b[38;5;196mOverflow\033[0m\n");
			if (_value < min_val(t) - r )//a + b < min
				throw Type::UnderflowExc("\x1b[38;5;196mUnderflow\033[0m\n");
		}
		catch (std::exception & e){std::cerr << e.what();}
		return OperandCreator::get_instance()->createOperand(std::to_string(_value + std::stod(rhs.toString())), t);
	}

	virtual IOperand const * operator-( IOperand const & rhs ) const
	{
		eOperandType t = std::max(_type, rhs.getType());
		double r = std::stod(rhs.toString());
		try
		{
			if (_value > max_val(t) + r)
				throw Type::OverflowExc("\x1b[38;5;196mOverflow\033[0m\n");
			if (_value < min_val(t) + r )
				throw Type::UnderflowExc("\x1b[38;5;196mUnderflow\033[0m\n");
		}
		catch (std::exception & e){std::cerr << e.what();}
		return OperandCreator::get_instance()->createOperand(std::to_string(_value - std::stod(rhs.toString())), t);
	}

	virtual IOperand const * operator*( IOperand const & rhs ) const
	{
		eOperandType t = std::max(_type, rhs.getType());
		double r = std::stod(rhs.toString());
		try
		{
			if (r > 0 && _value > max_val(t) / r)
				throw Type::OverflowExc("\x1b[38;5;196mOverflow\033[0m\n");
			if (_value < min_val(t) / r && _value > max_val(t) / r)//a*b<Min: a<Min/b | a>-Min/b
				throw Type::UnderflowExc("\x1b[38;5;196mUnderflow\033[0m\n");
		}
		catch (std::exception & e){std::cerr << e.what();}
		return OperandCreator::get_instance()->createOperand(std::to_string(_value * std::stod(rhs.toString())), t);
	}

	virtual IOperand const * operator/( IOperand const & rhs ) const
	{
		eOperandType t = std::max(_type, rhs.getType());
		try
		{
			if (std::stod(rhs.toString()) == 0)// mb inline isZero(double a){return a < epsilon];}
				throw Type::DivExc("\x1b[38;5;196mDivision by zero\033[0m\n");
			return OperandCreator::get_instance()->createOperand(std::to_string(_value / std::stod(rhs.toString())), t);
		}
		catch (std::exception & e){std::cerr << e.what();}
	}

	virtual IOperand const * operator%( IOperand const & rhs ) const
	{
		eOperandType t = std::max(_type, rhs.getType());
		try
		{
			if (std::stod(rhs.toString()) == 0)// mb inline isZero(double a){return a < epsilon];}
				throw Type::ModExc("\x1b[38;5;196mModulo by zero\033[0m\n");
			return OperandCreator::get_instance()->createOperand(std::to_string(_value % std::stod(rhs.toString())), t);
		}
		catch (std::exception & e){std::cerr << e.what();}
	}
	
	virtual std::string const & toString( void ) const
	{return std::to_string(_value);}
};

#endif
