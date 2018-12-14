#ifndef VIRTUAL_MACHINE_HPP
# define VIRTUAL_MACHINE_HPP
# include "IOperand.hpp"
# include <vector>

// AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
// another container that behaves like a stack is up to you. Whatever the container, it MUST
// only contain pointers to the abstract type IOperand.
class VirtualMachine
{
    std::vector<IOperand const *>   ops;
public:
    class EmptyStack : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mException: pop on empty stack\033[0m\n";
		}
	};
    // class AssertionFailed : public std::exception
	// {
	// 	public:
	// 	virtual const char*  what() const throw(){
	// 		return "\x1b[38;5;196mException: an assert instruction is not true\033[0m\n";
	// 	}
	// };
    class NotEnoughArguments : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mException: there are not enough arguments\033[0m\n";
		}
	};

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
    void        push(IOperand const *op);
    void        assert_(IOperand const *p);

};

#endif
