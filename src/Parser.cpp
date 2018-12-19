#include "../includes/Parser.hpp"
#include "../includes/OperandCreator.hpp"

Parser::Parser(){}
Parser::~Parser(){}

void	Parser::parse_token(s_tok & token, VirtualMachine & vm)
{
	if (!token.comment.empty()) {std::cout << token.comment << std::endl; return ;}
	
	static std::string s_commands[9] = {"pop", "dump", "add", "sub", "mul", "div", "mod", "print", "exit"};
	static std::string s_types[5] = {"int8", "int16", "int32", "float", "double"};
	static std::map<std::string, int> _commands;
	static std::map<std::string, int> _types;
	if (_commands.empty())
	{
		for (int i = 0; i < 9; i++)
			_commands.insert(std::pair<std::string, int>(s_commands[i], i));
		for (int i = 0; i < 5; i++)
			_types.insert(std::pair<std::string, int>(s_types[i], i));
	}

	eOperandType t = eOperandType(_types[token.type]);
	if (token.command == "assert")
		vm.assert_(OperandCreator::get_instance()->createOperand(t, token.value));
	else if (token.command == "push")
		vm.push(OperandCreator::get_instance()->createOperand(t, token.value));
	else
		vm.exec_command(_commands[token.command]);
}
