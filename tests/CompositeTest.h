#ifndef COMPOSITETEST_H_
#define COMPOSITETEST_H_

#include "BaseTest.h"

class CompositeTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(CompositeTest)
  CPPUNIT_TEST(CompositeTest, testInstantiation)
  CPPUNIT_TEST(CompositeTest, testInterface)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testInterface(void);
};

#endif // COMPOSITETEST_H_
