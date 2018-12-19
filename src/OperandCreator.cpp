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
    try
    {
        if (value != std::to_string((char)std::stoi(value)))
            throw Type::OverflowExc();
        else
            return new Type(value, Int8);
    }
    catch (std::exception & e){std::cout << e.what();exit(0);}
    return new Type(value, Int8);
}
IOperand const * OperandCreator::createInt16( std::string const & value ) const
{
    try
    {
        if (value != std::to_string((short int)std::stoi(value)))
            throw Type::OverflowExc();
        else
            return new Type(value, Int8);
    }
    catch (std::exception & e){std::cout << e.what();exit(0);}
    return new Type(value, Int16);
}
IOperand const * OperandCreator::createInt32( std::string const & value ) const
{
    try
    {
        if (value != std::to_string((int)std::stoi(value)))
            throw Type::OverflowExc();
        else
            return new Type(value, Int8);
    }
    catch (std::exception & e){std::cout << e.what();exit(0);}
    return new Type(value, Int32);
}
IOperand const * OperandCreator::createFloat(std::string const & value ) const
{
    return new Type(value, Float);
}
IOperand const * OperandCreator::createDouble( std::string const & value ) const
{
    return new Type(value, Double);
}
