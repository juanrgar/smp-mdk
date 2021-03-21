#ifndef EVENTSTEST_H_
#define EVENTSTEST_H_

#include "BaseTest.h"

class EventsTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(EventsTest)
  CPPUNIT_TEST(EventsTest, testInstantiation)
  CPPUNIT_TEST(EventsTest, testConnection)
  CPPUNIT_TEST(EventsTest, testTrigger)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testInstantiation(void);
  void testConnection(void);
  void testTrigger(void);
};

#endif // EVENTSTEST_H_
