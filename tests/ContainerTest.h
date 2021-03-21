#ifndef CONTAINERTEST_H_
#define CONTAINERTEST_H_

#include "BaseTest.h"

class ContainerTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(ContainerTest)
  CPPUNIT_TEST(ContainerTest, testInstantiation)
  CPPUNIT_TEST(ContainerTest, testPublicInterface)
  CPPUNIT_TEST(ContainerTest, testExceptions)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testPublicInterface(void);
  void testExceptions(void);
};

#endif // CONTAINERTEST_H_
