#ifndef TYPE_CLASS
# define TYPE_CLASS
# include "IOperand.hpp"
# include "OperandCreator.hpp"
# include <vector>
# include <string>
# include <climits>

class Type : public IOperand {
	std::string		_value;
	eOperandType	_type;
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


	Type() :  _value("0"), _type(Double), _precision(15){}
	Type(std::string s, eOperandType type = Double) : _value(s), _type(type),  _precision(type){
		if (_type == 3)
			_precision = 8;
		if (_type == 4)
			_precision = 15;
	}
	virtual ~Type(){}
	Type(Type const & other){*this = other;}
	Type const & operator=(Type const & other)
	{
		_type = other._type;
		_value = other._value;
		_precision = other._precision;
		return *this;
	}

	virtual int getPrecision( void ) const {return (int)_type;}
	virtual eOperandType getType( void ) const	{return _type;}
	virtual std::string const & toString( void ) const {return _value;}
	
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
		t = _type > rhs.getType() ? _type : rhs.getType();
		try
		{
			if (t < Float && std::stod(_value) > max_val(t) - r)
				throw Type::OverflowExc();
			else if (t < Float && std::stod(_value) < min_val(t) - r)
				throw Type::UnderflowExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(std::stod(_value) + std::stod(rhs.toString())));
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
			if (std::stod(_value) > max_val(t) + r)
				throw Type::OverflowExc();
			else if (std::stod(_value) < min_val(t) + r )
				throw Type::UnderflowExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(std::stod(_value) - std::stod(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what(); exit(0);}
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
			if (t < Float && r > 0 && std::stod(_value) > max_val(t) / r)
				throw Type::OverflowExc();
			else if (t < Float && std::stod(_value) < min_val(t) / r && std::stod(_value) > max_val(t) / r)//a*b<Min: a<Min/b | a>-Min/b
				throw Type::UnderflowExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(std::stod(_value) * std::stod(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what();exit(0);exit(0);}
		exit(0);
	}

	virtual IOperand const * operator/( IOperand const & rhs ) const
	{
		eOperandType t;
		t = std::max(_type, rhs.getType());
		try
		{
			if (std::stod(rhs.toString()) == 0)
				throw Type::DivExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(std::stod(_value) / std::stod(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what();exit(0);}
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
			else if (t > Int32)
				throw Type::WrongTypes();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(std::stoi(_value) % std::stoi(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what();exit(0);}
		exit(0);
	}
	
	
};

#endif
