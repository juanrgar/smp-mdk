#ifndef MANAGEDREFERENCETEST_H_
#define MANAGEDREFERENCETEST_H_

#include "BaseTest.h"

class ManagedReferenceTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(ContainerTest)
  CPPUNIT_TEST(ManagedReferenceTest, testInstantiation)
  CPPUNIT_TEST(ManagedReferenceTest, testPublicInterface)
  CPPUNIT_TEST(ManagedReferenceTest, testExceptions)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testPublicInterface(void);
  void testExceptions(void);
};

#endif // MANAGEDREFERENCETEST_H_
