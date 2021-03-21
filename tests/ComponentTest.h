#ifndef COMPONENTTEST_H_
#define COMPONENTTEST_H_

#include "BaseTest.h"

class ComponentTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(ComponentTest)
  CPPUNIT_TEST(ComponentTest, testInstantiation)
  // CPPUNIT_TEST(ComponentTest, testInterface)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testInterface(void);
};

#endif // COMPONENTTEST_H_
