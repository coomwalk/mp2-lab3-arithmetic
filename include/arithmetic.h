// объявление функций и классов для вычисления арифметических выражений
#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include "super_stack.h"

using namespace std;

struct lexema
{
    int type; // !переменная 1  || число-операнд 2 || !операция 3 || 4 скобка 
    string  str;
    lexema(int first, string second);
};
class arithmetic
{
    private:
    string inputstring;
    vector <lexema> input;
    vector <lexema> postfix;
    string postfix_string;
    map <string, double> variables;
    map <string, int> priority;
    bool check()const ;
    void parser();
    void to_postfix()noexcept;
    void getvalue();
    double calculate()  noexcept;

    public:
    
    void input_string_out()const noexcept;
    void postfix_string_out() const noexcept;
    arithmetic(string& tmp) noexcept;
    double try_calculate();

    ~arithmetic() = default;
};












#endif