#include "CompositeTest.h"

#include "Mdk/Composite.h"

using namespace Smp::Mdk;

class CompositeSubclass : public virtual Smp::Mdk::Composite
{
public:
  CompositeSubclass(void) {}

  virtual ~CompositeSubclass(void) {}

  Smp::String8 GetName(void) const { return NULL; }

  Smp::String8 GetDescription(void) const { return NULL; }

  Smp::IComposite* GetParent(void) const { return NULL; }

  void AddPublic(Smp::IContainer* container)
  {
    Smp::Mdk::Composite::AddContainer(container);
  }

  void ClearPublic(void) { Smp::Mdk::Composite::Clear(); }
};

class ContainerStub : public virtual Smp::IContainer
{
public:
  ContainerStub(Smp::String8 name, Smp::String8 desc, Smp::IComposite* parent)
    : m_name(name)
  {}

  virtual ~ContainerStub(void) {}

  Smp::String8 GetName(void) const { return this->m_name.c_str(); }

  Smp::String8 GetDescription(void) const { return NULL; }

  const Smp::ComponentCollection* GetComponents(void) const { return NULL; }

  Smp::IComponent* GetComponent(Smp::String8 name) const { return NULL; }

private:
  std::string m_name;
};

void
CompositeTest::setUp(void)
{}

void
CompositeTest::tearDown(void)
{}

void
CompositeTest::testInstantiation(void)
{
  CompositeSubclass* comp = new CompositeSubclass();

  CPPUNIT_ASSERT(comp != NULL);

  delete comp;
}

void
CompositeTest::testInterface(void)
{
  CompositeSubclass* comp = new CompositeSubclass();
  ContainerStub* cont1 = new ContainerStub("Cont1", "Container 1", NULL);

  Smp::IContainer* container1 = comp->GetContainer("");
  CPPUNIT_ASSERT(NULL == container1);

  Smp::IContainer* container2 = comp->GetContainer(NULL);
  CPPUNIT_ASSERT(NULL == container2);

  {
    const Smp::ContainerCollection* containerCollection = comp->GetContainers();
    CPPUNIT_ASSERT_EQUAL(size_t(0), containerCollection->size());
  }

  {
    comp->AddPublic(cont1);

    CPPUNIT_ASSERT_EQUAL(size_t(1), comp->GetContainers()->size());
  }

  {
    Smp::IContainer* cont = comp->GetContainer("Cont1");
    CPPUNIT_ASSERT(dynamic_cast<Smp::IContainer*>(cont1) == cont);
  }

  {
    comp->ClearPublic();

    CPPUNIT_ASSERT_EQUAL(size_t(0), comp->GetContainers()->size());
  }

  delete cont1;
  delete comp;
}
