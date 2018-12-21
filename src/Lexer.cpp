#include "../includes/Lexer.hpp"
#include "../includes/Parser.hpp"
#include <regex>

Lexer::Lexer(){}
Lexer::~Lexer(){}
Lexer::Lexer(Lexer const & other){*this = other;}
Lexer const & Lexer::operator=(Lexer const & other){(void)other; return *this;}

int	Lexer::lineno() const
{
	static int line;
	return line++;
}


void	Lexer::read_tokens(std::istream & is, std::vector<s_tok> & tokens)
{
	std::string line;
	std::string exit_instr = (&is == &std::cin) ? ";;" : "exit";

	while (std::getline(is, line, '\n') && line != exit_instr)
	{
		lineno();
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
	std::regex  line("(\\s*)(dump|add|sub|mul|div|mod|print|pop|exit)"
						"|"
						"(\\s*)(push|assert)(\\s+)(int8|int16|int32|float|double)"
						"(\\s*)(\\()(\\s*)"
						"([-+]?[0-9]*\\.?[0-9]+)"
						"(\\s*)(\\))(\\s*)"
						);
	std::regex	command("(assert|push|dump|add|sub|mul|div|mod|print|pop|exit)");
	std::regex	type("(int8|int16|int32|float|double)");
	std::regex	val("(\\()(\\s*)([-+]?[0-9]*\\.?[0-9]+)");
	std::regex	comment("(^;)");    
	std::smatch res;
	s_tok		token;
	bool		matched;

	try
	{
		if (std::regex_search(s, res, comment)) {token.comment = s; return token;}
		matched = std::regex_match(s, res, line);

		if (std::regex_search(s, res, command) && matched)
			token.command = res[1].str();
		else throw Lexer::InstrUnknown();

		if (std::regex_search(s, res, type) && matched)
			token.type = res[1].str();
		else throw Lexer::WrongType();

		if ( std::regex_search(s, res, val) && matched)
			token.value = (res[2].str() == "(") ? res[2].str() : res[3].str();
		else throw Lexer::WrongValue(); 
		if ( (token.value.find(".") != std::string::npos && token.type.find("int") != std::string::npos) ||
		(token.value.find(".") == std::string::npos && token.type.find("int")==std::string::npos) )
			throw Lexer::WrongValue();
		
	}
	catch(std::exception & e) {std::cerr << "Line " << Lexer::lineno() << " : " << e.what(); exit(0);}
	return token;
}
