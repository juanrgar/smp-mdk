#include "Mdk/Management/ManagedContainer.h"
#include <ManagedContainerTest.h>

using namespace Smp::Mdk::Management;

class ComponentStub : public Smp::IComponent
{
public:
  ComponentStub(Smp::String8 name, Smp::String8 desc, Smp::IComposite* parent)
    : _name(name)
    , _desc(desc)
  {}

  virtual ~ComponentStub(void) {}

  virtual Smp::String8 GetName(void) const { return this->_name.c_str(); }

  virtual Smp::String8 GetDescription(void) const
  {
    return this->_desc.c_str();
  }

  virtual Smp::IComposite* GetParent(void) const { return NULL; }

private:
  std::string _name;
  std::string _desc;
};

void
ManagedContainerTest::setUp(void)
{}

void
ManagedContainerTest::tearDown(void)
{}

void
ManagedContainerTest::testInstantiation(void)
{
  ManagedContainer<ComponentStub>* cont1 = new ManagedContainer<ComponentStub>(
    "Cont1", "ManagedContainer 1", NULL, 0, 1);

  CPPUNIT_ASSERT(cont1 != NULL);

  delete cont1;
}

void
ManagedContainerTest::testPublicInterface(void)
{
  ManagedContainer<ComponentStub>* cont1 =
    new ManagedContainer<ComponentStub>("cont1", "ManagedContainer 1", NULL);
  CPPUNIT_ASSERT(cont1 != NULL);

  CPPUNIT_ASSERT_EQUAL(Smp::Int64(0), cont1->Count());
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(0), cont1->Lower());
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(-1), cont1->Upper());

  ComponentStub* comp1 = new ComponentStub("Comp1", "Comp 1", NULL);
  cont1->AddComponent(comp1);
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(1), cont1->Count());

  ComponentStub* comp2 = new ComponentStub("Comp2", "Comp 2", NULL);
  cont1->AddComponent(comp2);
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(2), cont1->Count());

  delete cont1;
}

void
ManagedContainerTest::testExceptions(void)
{
  {
    ManagedContainer<ComponentStub>* cont1 =
      new ManagedContainer<ComponentStub>(
        "cont1", "ManagedContainer 1", NULL, 0, 0);
    CPPUNIT_ASSERT(cont1 != NULL);

    ComponentStub* comp1 = new ComponentStub("Comp1", "Comp 1", NULL);

    try {
      cont1->AddComponent(comp1);
      CPPUNIT_ASSERT(false);
    } catch (Smp::Management::IManagedContainer::ContainerFull& ex) {
      CPPUNIT_ASSERT_EQUAL(Smp::Int64(0), ex.containerSize);
      std::cout << ex.containerName;
      CPPUNIT_ASSERT(strcmp("cont1", ex.containerName) == 0);
    }

    delete comp1;
    delete cont1;
  }

  {
    ManagedContainer<ComponentStub>* cont1 =
      new ManagedContainer<ComponentStub>(
        "cont1", "ManagedContainer 1", NULL, 0, 1);
    CPPUNIT_ASSERT(cont1 != NULL);

    ComponentStub* comp1 = new ComponentStub("Comp1", "Comp 1", NULL);
    ComponentStub* comp2 = new ComponentStub("Comp2", "Comp 2", NULL);

    try {
      cont1->AddComponent(comp1);
    } catch (Smp::Management::IManagedContainer::ContainerFull& ex) {
      CPPUNIT_ASSERT(false);
    }

    CPPUNIT_ASSERT_EQUAL(Smp::Int64(1), cont1->Count());

    try {
      cont1->AddComponent(comp2);
      CPPUNIT_ASSERT(false);
    } catch (Smp::Management::IManagedContainer::ContainerFull& ex) {
      CPPUNIT_ASSERT_EQUAL(Smp::Int64(1), ex.containerSize);
      std::cout << ex.containerName;
      CPPUNIT_ASSERT(strcmp("cont1", ex.containerName) == 0);
    }

    delete comp2;
    delete cont1;
  }
}
