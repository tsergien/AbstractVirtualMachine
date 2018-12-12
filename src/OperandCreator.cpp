#include "../includes/OperandCreator.hpp"


OperandCreator::OperandCreator()
{
    f[0] = &OperandCreator::createInt8;
    f[1] = &OperandCreator::createInt16;
    f[2] = &OperandCreator::createInt32;
    f[3] = &OperandCreator::createFloat;
    f[4] = &OperandCreator::createDouble;
}

OperandCreator::~OperandCreator(){}


IOperand const * OperandCreator::createOperand( eOperandType type, std::string const & value ) const
{
	return (this->*(f[type]))(value);
}

OperandCreator * OperandCreator::get_instance()
{
    static OperandCreator *inst = new OperandCreator;
    return inst;
}

IOperand const * OperandCreator::createInt8( std::string const & value ) const
{

}
IOperand const * OperandCreator::createInt16( std::string const & value ) const
{

}
IOperand const * OperandCreator::createInt32( std::string const & value ) const
{

}
IOperand const * OperandCreator::createFloat( std::string const & value ) const
{

}
IOperand const * OperandCreator::createDouble( std::string const & value ) const
{

}
