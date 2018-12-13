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
    char val = std::stoi(value);
    return new Type<char>(val, Int8);
}
IOperand const * OperandCreator::createInt16( std::string const & value ) const
{
    short int val = std::stoi(value);
    return new Type<short int>(val, Int16);
}
IOperand const * OperandCreator::createInt32( std::string const & value ) const
{
    int val = std::stoi(value);
    return new Type<int>(val, Int32);
}
IOperand const * OperandCreator::createFloat( std::string const & value ) const
{
    float val = std::stof(value);
    return new Type<float>(val, Float);
}
IOperand const * OperandCreator::createDouble( std::string const & value ) const
{
    double val = std::stod(value);
    return new Type<double>(val, Double);
}
