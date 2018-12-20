#include "../includes/VirtualMachine.hpp"
#include "../includes/OperandCreator.hpp"
#include <assert.h>
#include "../includes/Parser.hpp"

VirtualMachine::VirtualMachine()
{
    commands[0] = &VirtualMachine::pop;
    commands[1] = &VirtualMachine::dump;
    commands[2] = &VirtualMachine::add;
    commands[3] = &VirtualMachine::sub;
    commands[4] = &VirtualMachine::mul;
    commands[5] = &VirtualMachine::div;
    commands[6] = &VirtualMachine::mod;
    commands[7] = &VirtualMachine::print;
    commands[8] = &VirtualMachine::exit_;
}
VirtualMachine::~VirtualMachine(){}
VirtualMachine::VirtualMachine(VirtualMachine const & other){*this = other;}
VirtualMachine & VirtualMachine::operator=(VirtualMachine const & other)
{
    this->ops = other.ops;
    return *this;
}

void        VirtualMachine::exec_command(int c)
{
    assert (c >= 0 && c < 9);
    (this->*(commands[c]))();
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
    catch (std::exception & e){std::cerr << "Line " << Parser::lineno() << " : " << e.what(); exit(0);}
}

void        VirtualMachine::dump()
{
    std::vector<IOperand const *>::iterator it = ops.end();
    for (it = --ops.end(); it >= ops.begin(); --it)
        std::cout << (*it)->toString() << std::endl;
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
    catch (std::exception & e) {std::cerr << "Line " << Parser::lineno() << " : " << e.what(); exit(0);}
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
    catch (std::exception & e) {std::cerr << "Line " << Parser::lineno() << " : " << e.what(); exit(0);}
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
    catch (std::exception & e) {std::cerr << "Line " << Parser::lineno() << " : " << e.what(); exit(0);}
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
    catch (std::exception & e) {std::cerr << "Line " << Parser::lineno() << " : " << e.what(); exit(0);}
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
    catch (std::exception & e) {std::cerr << "Line " << Parser::lineno() << " : " << e.what(); exit(0);}
}

void        VirtualMachine::print()
{
    assert(ops.back()->getType() == Int8);
    std::cout << (char)std::stoi(ops.back()->toString()) << std::endl;
}

void        VirtualMachine::exit_(){exit(0);}

void        VirtualMachine::push(IOperand const *op) {ops.push_back(op);}
void        VirtualMachine::assert_(IOperand const *p){
    try
    {
        if (p->toString() != ops.back()->toString())
            throw VirtualMachine::AssertionFailed();
    }
    catch (std::exception & e){std::cerr << "Line " << Parser::lineno() << " : " << e.what(); exit(0);}
}