#ifndef VIRTUAL_MACHINE_HPP
# define VIRTUAL_MACHINE_HPP
# include "IOperand.hpp"
# include <vector>

// AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
// another container that behaves like a stack is up to you. Whatever the container, it MUST
// only contain pointers to the abstract type IOperand.
class VirtualMachine
{
    std::vector<IOperand *>   ops;
public:
    VirtualMachine();
    ~VirtualMachine();
    VirtualMachine(VirtualMachine const & other);
    VirtualMachine & operator=(VirtualMachine const & other);

    void        print();
    void        pop();
    void        dump();
    void        add();
    void        sub();
    void        mul();
    void        div();
    void        mod();
    void        push(eOperandType type, IOperand *op);
    void        assert(eOperandType type, IOperand *p);

};

#endif
