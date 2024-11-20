// тесты для вычисления арифметических выражений
#include <gtest.h>
#include "arithmetic.h"


TEST(arithmetic, cant_str_start_with_operation)
{
  string zibrail2 = "*(34+17)/44";
  arithmetic zxc(zibrail2);
  ASSERT_ANY_THROW(zxc.try_calculate());
  //ASSERT_NO_THROW();
  //EXPECT_EQ();
  //EXPECT_NE();
  //ASSERT_ANY_THROW();
}

TEST(arithmetic, cant_skobki_close_more_open)
{
  string zibrail2 = "(34+17))/44";
  arithmetic zxc(zibrail2);
  ASSERT_ANY_THROW(zxc.try_calculate());
}

TEST(arithmetic, cant_operands_close)
{
  string zibrail2 = "(34+17a)/44";
  arithmetic zxc(zibrail2);
  ASSERT_ANY_THROW(zxc.try_calculate());
}
TEST(arithmetic, cant_operation_close)
{
  string zibrail2 = "(34+*17)/44";
  arithmetic zxc(zibrail2);
  ASSERT_ANY_THROW(zxc.try_calculate());
}

TEST(arithmetic, cant_skobki_error)
{
  string zibrail2 = "((34+17)/44";
  arithmetic zxc(zibrail2);
  ASSERT_ANY_THROW(zxc.try_calculate());
}

TEST(arithmetic, correct_postfix )
{
  string zibrail2 = "(34+17)/44";
  arithmetic zxc(zibrail2);
  EXPECT_EQ("34 17 + 44 /", zxc.postfix_string_out());
}

TEST(arithmetic, correct_parse )
{
  string zibrail2 = "(34+17)/44+b";
  arithmetic zxc(zibrail2);
  
}

///////////////////////
