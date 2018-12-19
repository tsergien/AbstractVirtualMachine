#ifndef VIRTUAL_MACHINE_HPP
# define VIRTUAL_MACHINE_HPP
# include "IOperand.hpp"
# include <vector>
# define POP 0
# define DUMP 1
# define ADD 2
# define SUB 3
# define MUL 4
# define DIV 5
# define MOD 6
# define PRINT 7
# define EXIT 8

class VirtualMachine
{
public:
    class EmptyStack : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mException: pop on empty stack\033[0m\n";
		}
	};
    class AssertionFailed : public std::exception
	{
		public:
		virtual const char*  what() const throw(){
			return "\x1b[38;5;196mException: an assertion instruction is not true\033[0m\n";
		}
	};
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

	typedef void(VirtualMachine::*fptr)(void); 
	void		exec_command(int c);

    void        pop();
    void        dump();
    void        add();
    void        sub();
    void        mul();
    void        div();
    void        mod();
    void        print();
    void        exit_();

    void        push(IOperand const *op);
    void        assert_(IOperand const *p);
private:
	std::vector<IOperand const *>   ops;
	fptr	commands[9];
};

#endif
