#ifndef MANAGEDCONTAINERTEST_H_
#define MANAGEDCONTAINERTEST_H_

#include "BaseTest.h"

class ManagedContainerTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(ContainerTest)
  CPPUNIT_TEST(ManagedContainerTest, testInstantiation)
  CPPUNIT_TEST(ManagedContainerTest, testPublicInterface)
  CPPUNIT_TEST(ManagedContainerTest, testExceptions)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testPublicInterface(void);
  void testExceptions(void);
};

#endif // MANAGEDCONTAINERTEST_H_
