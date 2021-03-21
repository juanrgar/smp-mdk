#include "ManagedReferenceTest.h"

#include "Mdk/Management/ManagedReference.h"

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
ManagedReferenceTest::setUp(void)
{}

void
ManagedReferenceTest::tearDown(void)
{}

void
ManagedReferenceTest::testInstantiation(void)
{
  ManagedReference<ComponentStub>* ref1 = new ManagedReference<ComponentStub>(
    "Ref1", "ManagedReference 1", NULL, 0, 1);

  CPPUNIT_ASSERT(ref1 != NULL);

  delete ref1;
}

void
ManagedReferenceTest::testPublicInterface(void)
{
  ManagedReference<ComponentStub>* ref1 =
    new ManagedReference<ComponentStub>("Ref1", "ManagedReference 1", NULL);
  CPPUNIT_ASSERT(ref1 != NULL);

  CPPUNIT_ASSERT_EQUAL(Smp::Int64(0), ref1->Count());
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(0), ref1->Lower());
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(-1), ref1->Upper());

  ComponentStub* comp1 = new ComponentStub("Comp1", "Comp 1", NULL);
  ref1->AddComponent(comp1);
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(1), ref1->Count());

  ComponentStub* comp2 = new ComponentStub("Comp2", "Comp 2", NULL);
  ref1->AddComponent(comp2);
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(2), ref1->Count());

  delete ref1;
}

void
ManagedReferenceTest::testExceptions(void)
{
  {
    ManagedReference<ComponentStub>* ref1 = new ManagedReference<ComponentStub>(
      "ref1", "ManagedReference 1", NULL, 0, 0);
    CPPUNIT_ASSERT(ref1 != NULL);

    ComponentStub* comp1 = new ComponentStub("Comp1", "Comp 1", NULL);

    try {
      ref1->AddComponent(comp1);
      CPPUNIT_ASSERT(false);
    } catch (Smp::Management::IManagedReference::ReferenceFull& ex) {
      CPPUNIT_ASSERT_EQUAL(Smp::Int64(0), ex.referenceSize);
      std::cout << ex.referenceName;
      CPPUNIT_ASSERT(strcmp("ref1", ex.referenceName) == 0);
    }

    delete comp1;
    delete ref1;
  }

  {
    ManagedReference<ComponentStub>* ref1 = new ManagedReference<ComponentStub>(
      "ref1", "ManagedReference 1", NULL, 0, 1);
    CPPUNIT_ASSERT(ref1 != NULL);

    ComponentStub* comp1 = new ComponentStub("Comp1", "Comp 1", NULL);
    ComponentStub* comp2 = new ComponentStub("Comp2", "Comp 2", NULL);

    try {
      ref1->AddComponent(comp1);
    } catch (Smp::Management::IManagedReference::ReferenceFull& ex) {
      CPPUNIT_ASSERT(false);
    }

    CPPUNIT_ASSERT_EQUAL(Smp::Int64(1), ref1->Count());

    try {
      ref1->AddComponent(comp2);
      CPPUNIT_ASSERT(false);
    } catch (Smp::Management::IManagedReference::ReferenceFull& ex) {
      CPPUNIT_ASSERT_EQUAL(Smp::Int64(1), ex.referenceSize);
      std::cout << ex.referenceName;
      CPPUNIT_ASSERT(strcmp("ref1", ex.referenceName) == 0);
    }

    delete comp2;
    delete ref1;
  }
}
