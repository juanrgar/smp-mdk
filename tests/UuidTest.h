#ifndef UUIDTEST_H_
#define UUIDTEST_H_

#include "BaseTest.h"

class UuidTest : public BaseTest
{
public:
  CPPUNIT_SUITE_BEGIN(UuidTest)
  CPPUNIT_TEST(UuidTest, testConstructors)
  CPPUNIT_TEST(UuidTest, testGetSet)
  CPPUNIT_SUITE_END()

  void setUp(void);
  void tearDown(void);

  void testConstructors(void);
  void testGetSet(void);
};

#endif // UUIDTEST_H_
