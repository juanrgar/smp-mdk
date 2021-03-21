#include "StringTest.h"

#include "Mdk/SimpleTypes.h"

using namespace Smp::Mdk;

void
StringTest::setUp(void)
{}

void
StringTest::tearDown(void)
{}

void
StringTest::testBasic(void)
{
  {
    String<32> hString;
    CPPUNIT_ASSERT_EQUAL(size_t(0), ::strlen(&hString));
  }

  {
    String<32> hString("hello");
    CPPUNIT_ASSERT_EQUAL(size_t(5), ::strlen(&hString));
    CPPUNIT_ASSERT_EQUAL(Smp::Char8('h'), hString[0]);
    CPPUNIT_ASSERT_EQUAL(Smp::Char8('e'), hString[1]);
    CPPUNIT_ASSERT_EQUAL(Smp::Char8('l'), hString[2]);
    CPPUNIT_ASSERT_EQUAL(Smp::Char8('l'), hString[3]);
    CPPUNIT_ASSERT_EQUAL(Smp::Char8('o'), hString[4]);
  }
}
