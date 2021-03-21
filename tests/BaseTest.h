#ifndef BASETEST_H_
#define BASETEST_H_

#include <cppunit/Test.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>

#define CPPUNIT_SUITE_BEGIN(name)                                              \
  static ::CppUnit::Test* suite(void)                                          \
  {                                                                            \
    ::CppUnit::TestSuite* suite = new ::CppUnit::TestSuite("name");

#define CPPUNIT_TEST(className, testName)                                      \
  suite->addTest(                                                              \
    new ::CppUnit::TestCaller<className>("testName", &className::testName));

#define CPPUNIT_SUITE_END()                                                    \
  return suite;                                                                \
  }

class BaseTest : public ::CppUnit::TestFixture
{};

#endif // BASETEST_H_
