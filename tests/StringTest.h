#ifndef STRINGTEST_H_
#define STRINGTEST_H_

#include "BaseTest.h"

class StringTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(StringTest)
  CPPUNIT_TEST(StringTest, testBasic)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testBasic(void);
};

#endif // STRINGTEST_H_
