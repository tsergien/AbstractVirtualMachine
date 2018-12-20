#include "../includes/OperandCreator.hpp"
#include "../includes/Type.hpp"

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
    if (value.empty()){std::cerr << "Error: empty value!\n"; exit(0);}
	return (this->*(f[type]))(value);
}

OperandCreator * OperandCreator::get_instance()
{
    static OperandCreator *inst = new OperandCreator;
    return inst;
}

IOperand const * OperandCreator::createInt8( std::string const & value ) const
{
    return new Type<char>(value, Int8);
}
IOperand const * OperandCreator::createInt16( std::string const & value ) const
{
    return new Type<short int>(value, Int16);
}
IOperand const * OperandCreator::createInt32( std::string const & value ) const
{
    return new Type<int>(value, Int32);
}
IOperand const * OperandCreator::createFloat(std::string const & value ) const
{
    return new Type<float>(value, Float);
}
IOperand const * OperandCreator::createDouble( std::string const & value ) const
{
    return new Type<double>(value, Double);
}
