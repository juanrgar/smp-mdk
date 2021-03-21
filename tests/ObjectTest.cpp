#include "ObjectTest.h"

#include "Mdk/Object.h"

using namespace Smp::Mdk;

void
ObjectTest::setUp(void)
{}

void
ObjectTest::tearDown(void)
{}

void
ObjectTest::testInstantiation(void)
{
  Object* obj1 = new Object();

  CPPUNIT_ASSERT(obj1 != NULL);

  delete obj1;

  Object* obj2 = new Object("ObjectName", "Object description");

  CPPUNIT_ASSERT(obj2 != NULL);

  delete obj2;
}

void
ObjectTest::testInterface(void)
{
  {
    const Object* obj1 = new Object();

    Smp::String8 nameGot = obj1->GetName();
    CPPUNIT_ASSERT_EQUAL(Smp::String8(NULL), nameGot);

    Smp::String8 descGot = obj1->GetDescription();
    CPPUNIT_ASSERT_EQUAL(Smp::String8(NULL), descGot);

    delete obj1;
  }

  {
    Smp::String8 nameGiven = "ObjectName";
    Smp::String8 descGiven = "Object description";

    const Object* obj2 = new Object(nameGiven, descGiven);

    Smp::String8 nameGot = obj2->GetName();
    CPPUNIT_ASSERT_EQUAL(0, strcmp(nameGiven, nameGot));

    Smp::String8 descGot = obj2->GetDescription();
    CPPUNIT_ASSERT_EQUAL(0, strcmp(descGiven, descGot));

    delete obj2;
  }
}

void
ObjectTest::testExceptions(void)
{
  bool exceptionCatched = false;

  try {
    const Object* obj = new Object("", "");
    delete obj;
  } catch (Smp::InvalidObjectName& ex) {
    exceptionCatched = true;
  }

  CPPUNIT_ASSERT_EQUAL(true, exceptionCatched);
}
