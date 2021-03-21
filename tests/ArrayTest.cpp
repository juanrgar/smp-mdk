#include "ArrayTest.h"

#include "Mdk/SimpleTypes.h"

using namespace Smp::Mdk;

void
ArrayTest::setUp(void)
{}

void
ArrayTest::tearDown(void)
{}

void
ArrayTest::testBasic(void)
{
  {
    Array<Smp::Bool, 32> boolArray;
    CPPUNIT_ASSERT_EQUAL(Smp::Bool(false), boolArray[0]);
    CPPUNIT_ASSERT_EQUAL(Smp::Bool(false), (&boolArray)[0]);
  }
}
