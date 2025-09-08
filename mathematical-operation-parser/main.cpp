#include <iostream>
#include "Parser.h"
using namespace std;

// test
int main()
{
    string expression = "3+13*2/5-9*1";

    Parser parser = Parser(expression);
    cout << "\nResult: " << parser.getResult() << endl; // output: -0.8
    
    return 0;
}