#ifndef TYPE_CLASS
# define TYPE_CLASS
# include "IOperand.hpp"
# include "OperandCreator.hpp"
# include <vector>
# include <string>
# include <climits>

template <typename T>
class Type : public IOperand {
	std::string		_sval;
	eOperandType	_type;
	unsigned int	_precision;
	T				_val;
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


	Type() :   _sval("0.0"), _type(Double),  _precision(4), _val(0){}
	Type(std::string s, eOperandType type = Double) : _sval(s), _type(type){
		_precision = (int)_type;
		try
		{
			_val = _type < Float ? (T)std::stoi(_sval) : (T)std::stod(_sval);
			_sval = std::to_string(_val);
			if (_sval.find("."))
				while (_sval[_sval.size()-1] == '0') _sval.erase(_sval.size()-1, 1);
			if (_type < Float && _sval[0] != '-' && _sval != std::to_string(_val))
				throw Type::OverflowExc();
			if (_type < Float && _sval[0] == '-' && _sval != std::to_string(_val))
				throw Type::UnderflowExc();
		}
		catch (std::exception & e) {std::cout << "constr: " << e.what(); exit(0);}
	}
	virtual ~Type(){}
	Type(Type const & other){*this = other;}
	Type const & operator=(Type const & other)
	{
		_type = other._type;
		_val = other._val;
		_sval = other._vsal;
		_precision = other._precision;
		return *this;
	}

	virtual int getPrecision( void ) const {return (int)_type;}
	virtual eOperandType getType( void ) const	{return _type;}
	virtual std::string const & toString( void ) const {return _sval;}
	
	int	min_val(eOperandType t) const
	{
		switch(t)
		{
			case 0: return -128;
			case 1: return -32768;
			default: return -2147483648;
		}
		return 0;
	}
	int	max_val(eOperandType t) const
	{
		switch(t)
		{
			case 0: return 127;
			case 1: return 32767;
			default: return 2147483647;
		}
		return 0;
	}

	T cast(eOperandType t, std::string s) const
	{
		return t < Float ? std::stoi(s) : std::stod(s);
	}

	
	virtual IOperand const * operator+( IOperand const & rhs ) const
	{
		eOperandType t;
		double r;
		r = std::stod(rhs.toString());
		t = _type > rhs.getType() ? _type : rhs.getType();
		try
		{
			if (t < Float && _val > max_val(t) - r)
				throw Type::OverflowExc();
			else if (t < Float && _val < min_val(t) - r)
				throw Type::UnderflowExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(_val + cast(t, rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what();}
		return 0;
	}

	virtual IOperand const * operator-( IOperand const & rhs ) const
	{
		eOperandType t;
		double r;
		r = std::stod(rhs.toString());
		t = std::max(_type, rhs.getType());
		try
		{
			if (t < Float && _val > max_val(t) + r)
				throw Type::OverflowExc();
			else if (t < Float && _val < min_val(t) + r )
				throw Type::UnderflowExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(_val - cast(t, rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what(); exit(0);}
		return 0;
	}

	virtual IOperand const * operator*( IOperand const & rhs ) const
	{
		eOperandType t;
		double r;
		r = std::stod(rhs.toString());
		t = std::max(_type, rhs.getType());
		try
		{
			if (t < Float && r > 0 && _val > max_val(t) / r)
				throw Type::OverflowExc();
			else if (t < Float && _val < min_val(t) / r && _val > max_val(t) / r)//a*b<Min: a<Min/b | a>-Min/b
				throw Type::UnderflowExc();
			else
				return OperandCreator::get_instance()->createOperand(t, std::to_string(_val * cast(t, rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what(); exit(0);}
		return 0;
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
				return OperandCreator::get_instance()->createOperand(t, std::to_string(_val / cast(t, rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what(); exit(0);}
		return 0;
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
				return OperandCreator::get_instance()->createOperand(t, std::to_string((int)_val % std::stoi(rhs.toString())));
		}
		catch (std::exception & e){std::cerr << e.what(); exit(0);}
		return 0;
	}
};

#endif
