#include "arithmetic.h"
using namespace std;
int main()
{
  string k ="(a+7)*(15/5 + 3)";
  arithmetic zxc(k);
  cout<< zxc.try_calculate() ;

  return 0;
}
