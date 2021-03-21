#ifndef OBJECTTEST_H_
#define OBJECTTEST_H_

#include "BaseTest.h"

class ObjectTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(ObjectTest)
  CPPUNIT_TEST(ObjectTest, testInstantiation)
  CPPUNIT_TEST(ObjectTest, testInterface)
  CPPUNIT_TEST(ObjectTest, testExceptions)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testInterface(void);
  void testExceptions(void);
};

#endif // OBJECTTEST_H_
