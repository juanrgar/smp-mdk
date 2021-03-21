#include "ComponentTest.h"

#include "Mdk/Component.h"

#include "Smp/IComposite.h"

using namespace Smp::Mdk;

class CompositeObject : public Smp::IComposite
{
public:
  CompositeObject(void);
  ~CompositeObject(void);

  Smp::String8 GetName(void) const;
  Smp::String8 GetDescription(void) const;
  Smp::IComposite* GetParent() const;
  const Smp::ContainerCollection* GetContainers(void) const;
  Smp::IContainer* GetContainer(Smp::String8 name) const;
};

CompositeObject::CompositeObject(void) {}

CompositeObject::~CompositeObject(void) {}

Smp::String8
CompositeObject::GetName(void) const
{
  return NULL;
}

Smp::String8
CompositeObject::GetDescription(void) const
{
  return NULL;
}

Smp::IComposite*
CompositeObject::GetParent() const
{
  return NULL;
}

const Smp::ContainerCollection*
CompositeObject::GetContainers(void) const
{
  return NULL;
}

Smp::IContainer*
CompositeObject::GetContainer(Smp::String8 name) const
{
  return NULL;
}

void
ComponentTest::setUp(void)
{}

void
ComponentTest::tearDown(void)
{}

void
ComponentTest::testInstantiation(void)
{
  {
    Component* comp = new Component();

    CPPUNIT_ASSERT(comp != NULL);

    delete comp;
  }

  {
    Component* comp = new Component("Name", "Description", NULL);

    CPPUNIT_ASSERT(comp != NULL);

    delete comp;
  }

  {
    CompositeObject* parent = new CompositeObject();
    Component* comp = new Component("Name", "Description", parent);

    CPPUNIT_ASSERT(comp != NULL);

    delete comp;
    delete parent;
  }
}

void
ComponentTest::testInterface(void)
{
  {
    Component* comp = new Component();
    Smp::IComposite* parent = comp->GetParent();

    CPPUNIT_ASSERT(parent == NULL);

    delete comp;
  }

  {
    CompositeObject* parentGiven = new CompositeObject();
    Component* comp = new Component("Name", "Description", parentGiven);
    Smp::IComposite* parentGot = comp->GetParent();

    CPPUNIT_ASSERT(parentGot != NULL);
    CPPUNIT_ASSERT_EQUAL(dynamic_cast<Smp::IComposite*>(parentGiven),
                         parentGot);

    delete comp;
    delete parentGiven;
  }
}
