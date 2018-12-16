#include <iostream>
#include <regex>
#include <string>

int main(int arc, char **av)
{
    std::cmatch result;
    std::regex  command("((?:\\s*)?"
                        "(add|sub|mul|div|mod|exit|print|pop)"
                        "(?:\\s*)?)|"
                        "(push|assert)(\\s+)(int8|int16|int32|float|double)"
                        "(?:\\s*)?"
                        "(\\()"
                        "(?:\\s*)?([-|+]?[0-9]+\\.?[0-9]+)([E|e]?[-|+]?[0-9]+)?"
                        "(?:\\s*)?"
                        "(\\))(?:\\s*)?"
                        );

    std::string s;
    std::cout << "Enter command, please:\n";
    try
    {
         while (std::getline(std::cin, s, '\n'))
        {
            if (std::regex_match(s.c_str(), result, command))
                for(int i = 0; i < result.size(); i++)
                    std::cout << "res["<<i<<"]: " << result[i] << std::endl;
            std::cout << "Enter command, please:\n";
        }
    }
    catch (std::regex_error & e) {std::cout << e.what() << std::endl;}
    return 0;
}

