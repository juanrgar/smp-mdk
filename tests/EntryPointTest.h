#ifndef ENTRYPOINTTEST_H_
#define ENTRYPOINTTEST_H_

#include "BaseTest.h"

class EntryPointTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(EntryPointTest)
  CPPUNIT_TEST(EntryPointTest, testInstantiation)
  CPPUNIT_TEST(EntryPointTest, testExecution)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testExecution(void);
};

#endif // ENTRYPOINTTEST_H_
