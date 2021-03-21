#include "EntryPointTest.h"

#include "Mdk/EntryPoint.h"

#include "Smp/IComponent.h"

#include <cppunit/TestSuite.h>

using namespace Smp::Mdk;

class EntryPointPublisher : public Smp::IComponent
{
public:
  EntryPointPublisher(void);
  ~EntryPointPublisher(void);

  Smp::String8 GetName(void) const;
  Smp::String8 GetDescription(void) const;
  Smp::IComposite* GetParent(void) const;

  void EntryPointCallback(void);

  Smp::Bool get_EntryPointCalled(void) const;
  void ResetEntryPointCalled(void);

private:
  Smp::Bool _entryPointCalled;
};

EntryPointPublisher::EntryPointPublisher(void) {}

EntryPointPublisher::~EntryPointPublisher(void) {}

Smp::IComposite*
EntryPointPublisher::GetParent(void) const
{
  return NULL;
}

Smp::String8
EntryPointPublisher::GetName(void) const
{
  return NULL;
}

Smp::String8
EntryPointPublisher::GetDescription(void) const
{
  return NULL;
}

void
EntryPointPublisher::EntryPointCallback(void)
{
  this->_entryPointCalled = true;
}

Smp::Bool
EntryPointPublisher::get_EntryPointCalled(void) const
{
  return this->_entryPointCalled;
}

void
EntryPointPublisher::ResetEntryPointCalled(void)
{
  this->_entryPointCalled = false;
}

void
EntryPointTest::setUp(void)
{}

void
EntryPointTest::tearDown(void)
{}

void
EntryPointTest::testInstantiation(void)
{
  {
    EntryPointPublisher* owner = new EntryPointPublisher();
    EntryPoint* entryPoint = new EntryPoint(
      "Name", "Description", owner, &EntryPointPublisher::EntryPointCallback);

    CPPUNIT_ASSERT(entryPoint != NULL);

    delete entryPoint;
    delete owner;
  }
}

void
EntryPointTest::testExecution(void)
{
  {
    EntryPointPublisher* owner = new EntryPointPublisher();
    EntryPoint* entryPoint = new EntryPoint(
      "Name", "Description", owner, &EntryPointPublisher::EntryPointCallback);

    entryPoint->Execute();

    CPPUNIT_ASSERT_EQUAL(true, owner->get_EntryPointCalled());

    delete entryPoint;
    delete owner;
  }
}
