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

void		VirtualMachine::exec_command(int c)
{
	assert (c >= 0 && c < 9);
	(this->*(commands[c]))();
}

void		VirtualMachine::pop()
{
	if (ops.empty())
		throw VirtualMachine::EmptyStack();
	else
		ops.pop_back();
}

void		VirtualMachine::dump()
{
	if (ops.empty()) return ;
	std::vector<IOperand const *>::iterator it = ops.end();
	for (it = --ops.end(); it >= ops.begin(); --it)
		std::cout << (*it)->toString() << std::endl;
}

void		VirtualMachine::add()
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

void		VirtualMachine::sub()
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

void		VirtualMachine::mul()
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

void		VirtualMachine::div()
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

void		VirtualMachine::mod()
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

void		VirtualMachine::print()
{
	assert(ops.back()->getType() == Int8);
	std::cout << (char)std::stoi(ops.back()->toString()) << std::endl;
}

void		VirtualMachine::exit_(){exit(0);}

void		VirtualMachine::push(IOperand const *op) {ops.push_back(op);}
void		VirtualMachine::assert_(IOperand const *p)
{
	if (p->toString() != ops.back()->toString())
		throw VirtualMachine::AssertionFailed();
}
