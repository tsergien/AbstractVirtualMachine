#include "../includes/Parser.hpp"
#include "../includes/OperandCreator.hpp"

Parser::Parser(){}
Parser::~Parser(){}

void	Parser::parse_token(s_tok token, VirtualMachine & vm)
{
	std::string commands[9] = {"pop", "dump", "add", "sub", "mul", "div", "mod", "print", "exit"};
	std::string types[5] = {"int8", "int16", "int32", "float", "double"};
	for (int i = 0; i < 9; i++)
		if (token.command == commands[i])
		{
			vm.exec_command(i);
			return ;
		}

	eOperandType t = (eOperandType)0;
	for (int i = 0; i < 5; i++)
		if (token.type == types[i]) {t = (eOperandType)i; break;}
	if (token.command == "assert")
		vm.assert_(OperandCreator::get_instance()->createOperand(t, token.value));
	else if (token.command == "push")
		vm.push(OperandCreator::get_instance()->createOperand(t, token.value));
}