#ifndef MODELTEST_H_
#define MODELTEST_H_

#include "BaseTest.h"

class ModelTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(ModelTest)
  CPPUNIT_TEST(ModelTest, testInstantiation)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
};

#endif // MODELTEST_H_
