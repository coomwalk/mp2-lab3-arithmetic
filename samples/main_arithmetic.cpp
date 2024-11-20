#include "arithmetic.h"
using namespace std;
int main()
{
  string k ="(34+17)/44+b";
  arithmetic zxc(k);
  int zibrail =  zxc.try_calculate() ;
  cout<<endl<<zxc.input_string_out()<<endl;
  cout<<zxc.postfix_string_out()<<endl;
  cout<<endl<<"RESULT: "<<zibrail<<endl;

  return 0;
}
