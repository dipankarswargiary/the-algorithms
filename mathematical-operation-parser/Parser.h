#ifndef PARSER_H
#define PARSER_H
#include <string>
// #include <unordered_set>
// #include <vector>

class Parser
{
    private:
        static const char OPERATORS[];
        std::string expression;
        double result;

        bool isAnOperator(char c);
        void validateExpression();
        double parse(std::string exp, int opIndex);
        void calculate();

        // std::vector<std::string> tokens;
        
        // std::string toString(char c);
        // void lex();

    public:
        Parser(std::string expression);
        double getResult();
};

#endif