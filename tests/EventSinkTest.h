#ifndef EVENTSINKTEST_H_
#define EVENTSINKTEST_H_

#include "BaseTest.h"

class EventSinkTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(EventSinkTest)
  CPPUNIT_TEST(EventSinkTest, testInstantiation)
  CPPUNIT_TEST(EventSinkTest, testExecution)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testExecution(void);
};

#endif // EVENTSINKTEST_H_
