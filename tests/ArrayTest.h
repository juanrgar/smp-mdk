#ifndef ARRAYTEST_H_
#define ARRAYTEST_H_

#include "BaseTest.h"

class ArrayTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(ArrayTest)
  CPPUNIT_TEST(ArrayTest, testBasic)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testBasic(void);
};

#endif // ARRAYTEST_H_
