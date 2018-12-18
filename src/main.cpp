#include <iostream>
#include "../includes/Type.hpp"
#include "../includes/VirtualMachine.hpp"
#include "../includes/Lexer.hpp"
#include "../includes/Parser.hpp"
#include <regex>
#include <string>
#include <errno.h>
#include <fstream>

int main(int ac, char **av)
{
	Lexer lex;
	VirtualMachine vm;
	std::string line;
	if (ac == 1)
		while (std::getline(std::cin, line, '\n'))
		{
			if (lex.set_token(line))
			Parser::parse_token(lex.get_clone(), vm);
		}
	for (int i = 1;  i < ac; i++)
	{
		std::filebuf fb;
		if (fb.open (av[i] ,std::ios::in))
 		{
    		std::istream is(&fb);
			std::vector<s_tok> tokens;
			while (std::getline(is, line, '\n'))
			{
				if (lex.set_token(line))
				tokens.push_back(lex.get_clone());
			}
			for (unsigned i = 0; i < tokens.size(); i++)
				Parser::parse_token(tokens[i], vm);
    		fb.close();
  		}
		if (errno) { std::cerr << av[i]<<": " << strerror(errno) << std::endl; }
	}
	system("leaks -q vm");
    return 0;
}









// #include "../parsing/parser.hpp"

// extern "C" int yyparse (void);
// extern  int yylex();
// extern FILE * yyin;
// extern char *yytext;
// int		start_program()
// {
// 	while (yylex())
// 		std::cout << yytext << std::endl;

// 	// return 0;
// 	return yyparse();
// }


// When reading from the standard input, the end of the program is
// indicated by the special symbol ";;" otherwise absent.
// int 	main(int ac, char **av)
// {
// 	if (ac == 1)
// 		start_program();
// 	for (int i = 1; i < ac; i++)
// 	{
// 		FILE *myfile = fopen(av[i], "r");
// 		if (!myfile)
// 		{
// 			std::cerr << "Can't open " << av[i] << " file! " << std::endl;
// 			return -1;
// 		}
// 		yyin = myfile;
// 		start_program();
// 	}
// 	return (0);
// }



//   ************** tests *******************
void test0()
{
	IOperand const * x0 = OperandCreator::get_instance()->createOperand(Int8, std::to_string(0));
	IOperand const * x1 = OperandCreator::get_instance()->createOperand(Int8, std::to_string(12));
	IOperand const * x2 = OperandCreator::get_instance()->createOperand(Int16, std::to_string(16));
	IOperand const * x3 = OperandCreator::get_instance()->createOperand(Int32, std::to_string(30));
	IOperand const * x4 = OperandCreator::get_instance()->createOperand(Float, std::to_string(40));
	IOperand const * x5 = OperandCreator::get_instance()->createOperand(Double, std::to_string(50));

	// std::cout << "****** TEST 0  ********" << std::endl;

	std::cout << "x1 : " << x1->toString() << std::endl;
	std::cout << "x2 : " << x2->toString() << std::endl;
	std::cout << "x3 : " << x3->toString() << std::endl;

	std::cout << "x1 + x1 : " << (*x1 + *x1)->toString() << std::endl;
	std::cout << "x1 - x1 : " << (*x1 - *x2)->toString() << std::endl;
	std::cout << "x1 - x2 : " << (*x1 - *x2)->toString() << std::endl;
	std::cout << "x1 * x2 : " << (*x1 * *x2)->toString() << std::endl;
	std::cout << "x1 / x2 : " << (*x1 / *x2)->toString() << std::endl;
	std::cout << "x4 / x5 : " << (*x4 / *x5)->toString() << std::endl;
	std::cout << "x1 / x5 : " << (*x1 / *x5)->toString() << std::endl;
	std::cout << "x2 % x0 : " << (*x2 % *x0)->toString() << std::endl;

}

void test1()
{
	VirtualMachine vm;

	vm.push(OperandCreator::get_instance()->createOperand(Int8, std::to_string(0)));
	vm.push(OperandCreator::get_instance()->createOperand(Int8, std::to_string(49)));
	vm.push(OperandCreator::get_instance()->createOperand(Int16, std::to_string(100)));
	vm.push(OperandCreator::get_instance()->createOperand(Int32, std::to_string(200)));
	vm.push(OperandCreator::get_instance()->createOperand(Float, std::to_string(2.8)));
	vm.push(OperandCreator::get_instance()->createOperand(Double, std::to_string(1.5)));

	std::cout << "stack: \n";
	vm.dump();

	vm.add();
	vm.dump();

	vm.pop();

	vm.div();
	vm.dump();
	
	vm.pop();
	vm.print();

	vm.push(OperandCreator::get_instance()->createOperand(Int8, std::to_string(57)));
	// vm.push(OperandCreator::get_instance()->createOperand(Int8, std::to_string(120)));
	// vm.add();
	vm.dump();
	// vm.push(OperandCreator::get_instance()->createOperand(Int32, std::to_string(2.8)));
	// vm.push(OperandCreator::get_instance()->createOperand(Double, std::to_string(1.5)));
	std::cout << "stack: \n";
	vm.dump();
	
	vm.mod();

	std::cout << "stack: \n";
	vm.dump();
}
