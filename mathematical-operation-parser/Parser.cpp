#include "Parser.h"
#include <iostream>
#include <cstdlib>

// operators in proper order for parsing
const char Parser::OPERATORS[] = {'-', '+', '/', '*'};

// constructor
Parser::Parser(std::string expression)
{
    this->expression = expression;
    this->result = 0;
    this->calculate();
}

bool Parser::isAnOperator(char c)
{
    for (char op : OPERATORS)
    {
        if (c == op)
            return true;
    }

    return false;
}

// Note: I have used multi-level if statements which can be
// done in only one if statement for better readibality
void Parser::validateExpression()
{
    std::string token{expression[0]};
    std::string exceptionMessage = "Exception: Invalid expression provided!";

    try {
        for (int i = 1; i < expression.length(); i++)
        {
            if (token.length() == 1) // first char of the token is '.'
            {
                if (isAnOperator(token[0]) || token[0] == '.')
                    throw exceptionMessage;
            }
            else if (i == (expression.length() - 1))    // last char of the exp
            {
                if (expression[i] == '.' || isAnOperator(expression[i]))
                    throw exceptionMessage;
            }
            else if (isAnOperator(expression[i]))   // operator encountered
            {
                if (i == expression.length() - 1)
                    throw exceptionMessage;

                else if (token[(token.length() - 1)] == '.')
                    throw exceptionMessage;
                
                else if (isAnOperator(expression[(i+1)]))
                    throw exceptionMessage;

                token = expression[(i+1)];
                i++;
            }

            token += expression[i];
        }
    }
    catch (std::string message)
    {
        std::cout << message << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

// parser
double Parser::parse(std::string exp, int opIndex)
{
    // return the double value of the string
    if (opIndex > 3)
        return std::stod(exp);
    
    std::string subExp{exp[0]};
    double firstSubExpResult{};   // stors the first sub expression's result
    double secondSubExpResult{};  // stors the second sub expression's result

    // the operator scanner
    for (int i = 1; i < exp.length(); i++)
    {
        if (exp[i] == OPERATORS[opIndex])
        {
            firstSubExpResult = parse(subExp, opIndex + 1);
            secondSubExpResult = parse(exp.substr(i+1, exp.length() - i - 1), opIndex);
            break;
        }
        else
            subExp += exp[i];
    }

    // in case the current operator does not exists in the input 
    // expression go to the next level for scanning the next operator
    if (subExp.length() == exp.length())
        return parse(subExp, opIndex + 1);

    // return the current exp's result
    switch(OPERATORS[opIndex])
    {
        case '*':
            return firstSubExpResult * secondSubExpResult;
        case '/':
            return firstSubExpResult / secondSubExpResult;
        case '+':
            return firstSubExpResult + secondSubExpResult;
        case '-':
            return firstSubExpResult - secondSubExpResult;
    }

    // no use of it btw, 
    // but the compiler does not allow without it
    return 0;
}

// calculate the result
void Parser::calculate()
{
    validateExpression();

    result = parse(expression, 0);
}

// getter
double Parser::getResult()
{
    return result;
}



// I realized I don't need this in this version of my implementation. lol
//
//
// std::string Parser::toString(char c)
// {
//     std::string str{c};
//     return str;
// }
//
//
// tokenizer
//
// void Parser::lexer()
// {
//     std::string token = toString(expression[0]);
//
//     for (int i = 1; i < expression.length(); i++)
//     {
//         if (isAnOperator(expression[i]))
//         {
//             tokens.push_back(token);
//             tokens.push_back(toString(expression[i]));
//             token = "";
//         }
//         else
//             token += expression[i];
//     }
// }