#include "../includes/VirtualMachine.hpp"
#include "../includes/OperandCreator.hpp"
#include <assert.h>

VirtualMachine::VirtualMachine(){}
VirtualMachine::~VirtualMachine(){}
VirtualMachine::VirtualMachine(VirtualMachine const & other){*this = other;}
VirtualMachine & VirtualMachine::operator=(VirtualMachine const & other)
{
    this->ops = other.ops;
    return *this;
}

void        VirtualMachine::pop()
{
    try
    {
        if (ops.empty())
            throw VirtualMachine::EmptyStack();
        else
            ops.pop_back();
    }
    catch (std::exception & e){std::cerr << e.what(); exit(0);}
}

void        VirtualMachine::dump()
{
    std::vector<IOperand const *>::iterator it = ops.end();
    for (it = --ops.end(); it >= ops.begin(); --it)
        std::cout << (*it)->toString() << std::endl;
    std::cout << std::endl;
}

void        VirtualMachine::assert_(IOperand const *p)
{
    assert(p->toString() == ops.back()->toString());
    // try
    // {
    //     if (p->toString() == ops.back()->toString())
    //         throw VirtualMachine::AssertionFailed();
    // }
    // catch (std::exception & e) {std::cerr << e.what();}
}

void        VirtualMachine::add()
{
    try
    {
        if (ops.size() < 2)
            throw VirtualMachine::NotEnoughArguments();
        else
        {
            int i = ops.size() - 1;
            IOperand const *e = *(ops[i]) + *(ops[i - 1]);
            push(e);
            ops.erase(ops.begin() + i);
            ops.erase(ops.begin() + i - 1);
        }
    }
    catch (std::exception & e) {std::cerr << e.what();}
}
void        VirtualMachine::sub()
{
    try
    {
        if (ops.size() < 2)
            throw VirtualMachine::NotEnoughArguments();
        else
        {
            int i = ops.size() - 1;
            IOperand const *e = *(ops[i]) - *(ops[i - 1]);
            push(e);
            ops.erase(ops.begin() + i);
            ops.erase(ops.begin() + i - 1);
        }
    }
    catch (std::exception & e) {std::cerr << e.what();}
}
void        VirtualMachine::mul()
{
    try
    {
        if (ops.size() < 2)
            throw VirtualMachine::NotEnoughArguments();
        else
        {
            int i = ops.size() - 1;
            IOperand const *e = *(ops[i]) * *(ops[i - 1]);
            push(e);
            ops.erase(ops.begin() + i);
            ops.erase(ops.begin() + i - 1);
        }
    }
    catch (std::exception & e) {std::cerr << e.what();}
}

void        VirtualMachine::div()
{
    try
    {
        if (ops.size() < 2)
            throw VirtualMachine::NotEnoughArguments();
        else
        {
            int i = ops.size() - 1;
            IOperand const *e = *(ops[i]) / *(ops[i - 1]);
            push(e);
            ops.erase(ops.begin() + i);
            ops.erase(ops.begin() + i - 1);
        }
    }
    catch (std::exception & e) {std::cerr << e.what();}
}

void        VirtualMachine::mod()
{
    try
    {
        if (ops.size() < 2)
            throw VirtualMachine::NotEnoughArguments();
        else
        {
            int i = ops.size() - 1;
            IOperand const *e = *(ops[i]) % *(ops[i - 1]);
            push(e);
            ops.erase(ops.begin() + i);
            ops.erase(ops.begin() + i - 1);
        }
    }
    catch (std::exception & e) {std::cerr << e.what();}
}

void        VirtualMachine::print()
{
    assert(ops.back()->getType() == Int8);
    std::cout << (char)std::stoi(ops.back()->toString()) << std::endl;
}

void        VirtualMachine::push(IOperand const *op) {ops.push_back(op);}
