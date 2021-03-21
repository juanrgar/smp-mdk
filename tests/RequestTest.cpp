#include "RequestTest.h"

#include "Mdk/Request.h"

using namespace Smp::Mdk;

void
RequestTest::setUp(void)
{}

void
RequestTest::tearDown(void)
{}

void
RequestTest::testInstantiation(void)
{
  Request* r_void = new Request("SampleVoidMethod", Smp::ST_None);
  CPPUNIT_ASSERT(r_void != NULL);
  CPPUNIT_ASSERT(strcmp(r_void->GetOperationName(), "SampleVoidMethod") == 0);
  CPPUNIT_ASSERT(r_void->GetParameterCount() == 0);
  delete r_void;

  Request* r_ret = new Request("SampleMethod", Smp::ST_Int32);
  CPPUNIT_ASSERT(r_ret != NULL);
  CPPUNIT_ASSERT(strcmp(r_ret->GetOperationName(), "SampleMethod") == 0);
  CPPUNIT_ASSERT(r_ret->GetParameterCount() == 0);
  delete r_ret;
}

void
RequestTest::testReturnVoid(void)
{
  Request* r = new Request("SampleVoidMethod", Smp::ST_None);
  CPPUNIT_ASSERT(r != NULL);
  try {
    Smp::AnySimple ret = r->GetReturnValue();
    CPPUNIT_FAIL("Exception not triggered");
  } catch (Smp::IRequest::VoidOperation& e) {
    CPPUNIT_ASSERT(strcmp(e.GetDescription(), "Operation 'SampleVoidMethod' is a void operation") == 0);
  }
  delete r;
}

void
RequestTest::testReturnType(void)
{
  Request* r = new Request("SampleMethod", Smp::ST_Int32);
  CPPUNIT_ASSERT(r != NULL);
  try {
    Smp::AnySimple ret = r->GetReturnValue();
    CPPUNIT_ASSERT(ret.type == Smp::ST_Int32);
  } catch (Smp::IRequest::VoidOperation& e) {
    CPPUNIT_FAIL("Exception triggered");
  }
  Smp::Mdk::AnySimple retValue;
  retValue.Set(Smp::Int32(24));
  r->SetReturnValue(retValue);
  try {
    Smp::AnySimple ret = r->GetReturnValue();
    CPPUNIT_ASSERT(ret.type == Smp::ST_Int32);
    CPPUNIT_ASSERT(ret.type == retValue.type);
    CPPUNIT_ASSERT(ret.value.int32Value == retValue.value.int32Value);
  } catch (Smp::IRequest::VoidOperation& e) {
    CPPUNIT_FAIL("Exception triggered");
  }
  delete r;
}
