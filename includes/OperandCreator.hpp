#ifndef OPERANDCREATOR
# define OPERANDCREATOR
# include "IOperand.hpp"

class OperandCreator;
typedef IOperand const *(OperandCreator::*funcptr)(std::string const & value) const;

class OperandCreator
{
public:
    ~OperandCreator();
    static OperandCreator * get_instance();
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private:
    funcptr     f[5];
    OperandCreator();
    IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};

#endif
