#include "arithmetic.h"
#include <sstream>

lexema:: lexema(int first, string second) : type(first), str(second) // work
{

}
arithmetic::arithmetic(string& tmp) noexcept : inputstring(tmp) //work
{
    priority={
        pair<string, int>{"+",1}, pair<string, int>{"-",1},
        pair<string, int>{"*",2}, pair<string, int>{"/",2}
    };
}

void arithmetic:: parser() ///work
{
    if(inputstring.size()==0) throw "so_small_input";

    for(size_t i = 0; i < inputstring.size(); i++)
    {
        if(isalpha(inputstring[i])) /// считаю, что переменные состоят из одной буквы(не сочетание)
        {   string k = "1";
            k[0] = inputstring[i];
            lexema tmp(1 ,k);
            variables[k] = -999;
            input.push_back(tmp);
        }
        if(strchr("+-*/", inputstring[i]) != nullptr)
        {
            string k = "1";
            k[0] = inputstring[i];
            lexema tmp(3 ,k);
            input.push_back(tmp);
        }
        if(strchr("()", inputstring[i]) != nullptr)
        {
            string k = "1";
            k[0] = inputstring[i];
            lexema tmp(4 ,k);
            input.push_back(tmp);
        }
        if(inputstring[i] == ' ') continue;
        if((isdigit(inputstring[i])) || (inputstring[i] == '.') || (inputstring[i] == ','))
        {
            string tmp1="1";
            tmp1[0] = inputstring[i];
            int z = 0;
            for( int j = i + 1; j < inputstring.size(); j++)
            {
                if((isdigit(inputstring[j])) || (inputstring[j] == '.') || (inputstring[j] == ','))
                {
                    tmp1+="1";
                    tmp1[z+1] = inputstring[j];
                    z++;
                    i++;
                }
                else break;
            }
            lexema tmp(2, tmp1);
            input.push_back(tmp);
        }
        }
        ///
        for(int i = 0; i < input.size(); i ++)
        {
            cout<<input[i].str<<" ";
        }
    
}
bool arithmetic:: check()const 
{
    int sosotoinie_skobok = 0;
    if((input[0].str == "+") || (input[0].str == "*") || (input[0].str == "/"))
    {
        throw "first symbol is invalid(operation)";
    }
    for(size_t i = 0; i < input.size() - 1; i++)
    {

        if(input[i].str == "(") sosotoinie_skobok++;
        if(input[i].str == ")") sosotoinie_skobok--;
        if(sosotoinie_skobok < 0) throw "error skobki";


        for (int k = 1; k < 3; k++)
        {
            for(int p = 1; p < 3; p++)
            {
                if(input[i].type == k && input[i+1].type == p)
                throw " error operands";
            }
        }
        if(input[i].type == 3 && input[i+1].type == 3) throw " error (oper)(oper)";

    }
    if(input[input.size() - 1].str == "(") sosotoinie_skobok++;
    if(input[input.size() - 1].str == ")") sosotoinie_skobok--;

    if (sosotoinie_skobok != 0) throw "error skobki";

    return true;
}

void arithmetic:: to_postfix()noexcept
{
    super_stack <lexema> st;
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i].type == 1 || input[i].type == 2) postfix.push_back(input[i]);
        if (input[i].str == "(") st.push(input[i]);
        if (input[i].str == ")")
        {
            while(st.Top().str != "(" ) // here mistake
            {
                postfix.push_back(st.Top());
                st.pop();
            }
            
            st.pop();
        }
        if (input[i].type == 3) //here
        {
            //while(priority[input[i].str] <= priority[st.Top().str] ) // or here
           // {
            //   postfix.push_back(st.Top()); // or here
            //   st.pop();
            //}
            //st.push(input[i]);
            while(!st.empty())
            {
                lexema rt = st.pop();
                if (priority[input[i].str] <= priority[rt.str] )
                {
                    postfix.push_back(rt);
                }
                else 
                st.push(rt);
                break;
            }
            st.push(input[i]);
        }
    }
    while(!st.empty())
    {
        if(st.Top().type != 4)
        {
            postfix.push_back(st.Top());
        }
        st.pop();
    }
    

}

double arithmetic:: calculate()  noexcept
{ 
    super_stack <double> st;
    for (int i = 0; i < postfix.size(); i++)
    {
        if(postfix[i].type == 1)
        st.push(variables[postfix[i].str]);



        if(postfix[i].type == 2)
        {
            for(int j = 0; j < postfix[i].str.size(); j ++)
            {
                if(postfix[i].str[j] == ',') postfix[i].str[j] = '.';
            }
            stringstream s(postfix[i].str);
            double k;
            s>>k;
            st.push(k);
        }




        if (postfix[i].type == 3)
        {
            string s = postfix[i].str;
        switch (s[0])
        {
        case '+':
        {
            double right = st.pop(), left = st.pop();
            st.push(left + right);
            break;
        }
        
        case '-':
        {
            double right = st.pop(), left = st.pop();
            st.push(left - right);
            break;
        }

        case '*':
        {
            double right = st.pop(), left = st.pop();
            st.push(left * right);
            break;
        }

        case '/':
        {
            double right = st.pop(), left = st.pop();
            st.push(double(left / right));
            break;
        }
        default:
        {
            cout<<" it's fiasko"<<endl;
            break;
        }
        }
        }

    } 

    return st.pop();
}

void arithmetic:: getvalue() //work
{
for (auto& [first, second] : variables)
        {
            cout<<"Input value of "<<first<<": ";
            cin>>second;
            
        }
        
}


double arithmetic:: try_calculate() //work
{
    this->parser();
    cout<<"Check : "<<this->check()<<endl; 
    this->to_postfix();

    for(int i = 0; i < postfix.size(); i++)
    postfix_string += postfix[i].str + " ";
    postfix_string.pop_back();
    
    this->getvalue();
    return this->calculate();
}




string arithmetic:: input_string_out()const noexcept //work
{
    return inputstring;

}
string arithmetic:: postfix_string_out()  noexcept //work
{
    return postfix_string;
}







/*void arithmetic:: print_parse()
{
    for(int i = 0; i < input.size(); i ++)
    {
        cout<<input[i].str<<endl;
    }
}*/
/*void arithmetic:: ghj()
{
    variables["first"] = 0.0;
    variables["sirst"] = 0.0;
    variables["tirst"] = 0.0;
}*/