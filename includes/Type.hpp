#ifndef TYPE_CLASS
# define TYPE_CLASS
# include "IOperand.hpp"
# include "Parser.hpp"
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


	Type() : _sval("0.0"), _type(Double),  _precision(4), _val(0){}
	Type(std::string s, eOperandType type = Double) : _sval(s), _type(type)
	{
		_precision = (int)_type;
		_val = _type < Float ? (T)std::stoi(_sval) : (T)std::stod(_sval);
		_sval = std::to_string(_val);
		if (_sval.find(".") != std::string::npos)
			while (_sval[_sval.size()-1] == '0' && _sval[_sval.size()-2] != '.') _sval.erase(_sval.size()-1, 1);
		if (_type < Float && _sval[0] != '-' && _sval != std::to_string(_val))
			throw Type::OverflowExc();
		if (_type < Float && _sval[0] == '-' && _sval != std::to_string(_val))
			throw Type::UnderflowExc();
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
			case 0: return std::numeric_limits<int8_t>::min();
			case 1: return std::numeric_limits<int16_t>::min();
			default: return std::numeric_limits<int>::min();
		}
		return 0;
	}
	int	max_val(eOperandType t) const
	{
		switch(t)
		{
			case 0: return std::numeric_limits<int8_t>::max();
			case 1: return std::numeric_limits<int16_t>::max();
			default: return std::numeric_limits<int>::max();
		}
		return 0;
	}

	T cast(eOperandType t, std::string s) const
	{
		return t < Float ? std::stoi(s) : std::stod(s);
	}



	// **************** OPERATORS ***********************
	virtual IOperand const * operator+( IOperand const & rhs ) const
	{
		eOperandType t;
		double r;
		r = std::stod(rhs.toString());
		t = _type > rhs.getType() ? _type : rhs.getType();
		if (t < Float && _val > max_val(t) - r)
			throw Type::OverflowExc();
		else if (t < Float && _val < min_val(t) - r)
			throw Type::UnderflowExc();
		return OperandCreator::get_instance()->createOperand(t, std::to_string(_val + cast(t, rhs.toString())));
	}

	virtual IOperand const * operator-( IOperand const & rhs ) const
	{
		eOperandType t;
		double r;
		r = std::stod(rhs.toString());
		t = std::max(_type, rhs.getType());
		if (t < Float && _val > max_val(t) + r)
			throw Type::OverflowExc();
		else if (t < Float && _val < min_val(t) + r )
			throw Type::UnderflowExc();
		return OperandCreator::get_instance()->createOperand(t, std::to_string(_val - cast(t, rhs.toString())));
	}

	virtual IOperand const * operator*( IOperand const & rhs ) const
	{
		eOperandType t;
		double r;
		r = std::stod(rhs.toString());
		t = std::max(_type, rhs.getType());
		if (t < Float && r > 0 && _val > max_val(t) / r)
			throw Type::OverflowExc();
		else if (t < Float && _val < min_val(t) / r && _val > max_val(t) / r)
			throw Type::UnderflowExc();
		return OperandCreator::get_instance()->createOperand(t, std::to_string(_val * cast(t, rhs.toString())));
	}

	virtual IOperand const * operator/( IOperand const & rhs ) const
	{
		eOperandType t;
		t = std::max(_type, rhs.getType());
		if (std::stod(rhs.toString()) == 0)
			throw Type::DivExc();
		return OperandCreator::get_instance()->createOperand(t, std::to_string(_val / cast(t, rhs.toString())));
	}

	virtual IOperand const * operator%( IOperand const & rhs ) const
	{
		eOperandType t;
		t = std::max(_type, rhs.getType());
		if (std::stod(rhs.toString()) == 0)
			throw Type::ModExc();
		else if (t > Int32)
			throw Type::WrongTypes();
		return OperandCreator::get_instance()->createOperand(t, std::to_string((int)_val % std::stoi(rhs.toString())));
	}


};

#endif
