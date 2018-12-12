#ifndef OPERANDCREATOR
# define OPERANDCREATOR
# include "IOperand.hpp"

    // typedef std::function< IOperand const * (std::string const & value) > funcptr; 
// std::vector<IOperand const * (std::string const & value)> f;

class OperandCreator;
typedef IOperand const *(OperandCreator::*funcptr)(std::string const & value) const;

class OperandCreator
{
    ~OperandCreator();
    OperandCreator(OperandCreator const & other) = delete;
    OperandCreator const & operator=(OperandCreator const & other) = delete;
    
    OperandCreator * get_instance();
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
