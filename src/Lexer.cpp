#include "../includes/Lexer.hpp"
#include "../includes/Parser.hpp"
#include <regex>

Lexer::Lexer(){}
Lexer::~Lexer(){}
Lexer::Lexer(Lexer const & other){*this = other;}
Lexer const & Lexer::operator=(Lexer const & other){(void)other; return *this;}

void	Lexer::read_tokens(std::istream & is, std::vector<s_tok> & tokens)
{
	std::string line;
	std::string exit_instr = (&is == &std::cin) ? ";;" : "exit";

	while (std::getline(is, line, '\n') && line != exit_instr)
	{
		if (!line.empty())
			tokens.push_back(this->set_token(line));
	}
	try
	{
		if (line == exit_instr)
			;
		else throw Lexer::NoExitInstr();
	}
	catch (std::exception & e) {std::cerr << "Line " << Parser::lineno() << " : " << e.what(); exit(0);}
}

s_tok Lexer::set_token(std::string s)
{
	std::regex  line("(dump|add|sub|mul|div|mod|print|pop|exit)"
						"|"
						"(push|assert)(\\s+)(int8|int16|int32|float|double)"
						"(\\s*)(\\()(\\s*)"
						"([-+]?[0-9]*\\.?[0-9]+)"
						"(\\s*)(\\))(\\s*)"
						);
	std::regex	command("(\\s*)(assert|push|dump|add|sub|mul|div|mod|print|pop|exit)(\\s*)");
	std::regex	type("(int8|int16|int32|float|double)");
	std::regex	val("(\\()(\\s*)([-+]?[0-9]*\\.?[0-9]+)");
	std::regex	comment("(^;)");    
	std::smatch res;
	s_tok		token;

	try
	{
		if (std::regex_search(s, res, comment)) token.comment = s;
		else if (!std::regex_search(s, res, command))
			throw Lexer::InstrUnknown();
		else if (std::regex_match(s, res, line))
		{
			if (std::regex_search(s, res, command))
				token.command = (res[1].str() == " ") ? res[2].str() : res[1].str();
			if (std::regex_search(s, res, type))
				token.type = res[1].str();
			if (std::regex_search(s, res, val))
				token.value = (res[2].str() == "(") ? res[2].str() : res[3].str();
		}
		else throw Lexer::LexicalError();
	}
	catch(std::exception & e) {std::cerr << "Line " << Parser::lineno() << " : " << e.what(); exit(0);}
	return token;
}
