#ifndef REFERENCETEST_H_
#define REFERENCETEST_H_

#include "BaseTest.h"

class ReferenceTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(ReferenceTest)
  CPPUNIT_TEST(ReferenceTest, testInstantiation)
  CPPUNIT_TEST(ReferenceTest, testPublicInterface)
  CPPUNIT_TEST(ReferenceTest, testExceptions)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testPublicInterface(void);
  void testExceptions(void);
};

#endif // REFERENCETEST_H_
