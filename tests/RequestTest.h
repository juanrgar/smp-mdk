#ifndef REQUESTTEST_H_
#define REQUESTTEST_H_

#include "BaseTest.h"

class RequestTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(RequestTest)
  CPPUNIT_TEST(RequestTest, testInstantiation)
  CPPUNIT_TEST(RequestTest, testReturnVoid)
  CPPUNIT_TEST(RequestTest, testReturnType)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testReturnVoid(void);
  void testReturnType(void);
};

#endif // REQUESTTEST_H_
