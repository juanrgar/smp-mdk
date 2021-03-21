#include "ReferenceTest.h"

#include "Mdk/Reference.h"

using namespace Smp::Mdk;

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

template<typename T>
class ReferenceSubclass : public virtual Smp::Mdk::Reference<T>
{
public:
  ReferenceSubclass(Smp::String8 name,
                    Smp::String8 desc,
                    Smp::IComponent* parent)
    : Reference<T>(name, desc, parent)
  {}

  virtual ~ReferenceSubclass(void) {}

  void AddPublic(Smp::IComponent* component)
  {
    try {
      Reference<T>::Add(component);
    } catch (Smp::InvalidObjectType ex) {
    }
  }

  Smp::Bool RemovePublic(Smp::IComponent* component)
  {
    return Reference<T>::Remove(component);
  }
};

void
ReferenceTest::setUp(void)
{}

void
ReferenceTest::tearDown(void)
{}

void
ReferenceTest::testInstantiation(void)
{
  Reference<ComponentStub>* ref1 =
    new Reference<ComponentStub>("Ref1", "Ref 1", NULL);

  CPPUNIT_ASSERT(ref1 != NULL);

  delete ref1;
}

void
ReferenceTest::testPublicInterface(void)
{
  ReferenceSubclass<ComponentStub>* ref1 =
    new ReferenceSubclass<ComponentStub>("Ref1", "Ref 1", NULL);
  CPPUNIT_ASSERT(ref1 != NULL);

  CPPUNIT_ASSERT_EQUAL(Smp::Int64(0), ref1->Count());
  CPPUNIT_ASSERT(ref1->Begin() == ref1->End());

  ComponentStub* comp1 = new ComponentStub("Comp1", "Comp 1", NULL);
  ref1->AddPublic(comp1);
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(1), ref1->Count());
  CPPUNIT_ASSERT(ref1->Begin() != ref1->End());

  ComponentStub* comp2 = new ComponentStub("Comp2", "Comp 2", NULL);
  ref1->AddPublic(comp2);
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(2), ref1->Count());
  CPPUNIT_ASSERT(ref1->Begin() != ref1->End());

  {
    Smp::Bool res = ref1->RemovePublic(comp1);
    CPPUNIT_ASSERT_EQUAL(true, res);
    CPPUNIT_ASSERT_EQUAL(Smp::Int64(1), ref1->Count());
    CPPUNIT_ASSERT(ref1->Begin() != ref1->End());
  }

  {
    Smp::Bool res = ref1->RemovePublic(comp2);
    CPPUNIT_ASSERT_EQUAL(true, res);
    CPPUNIT_ASSERT_EQUAL(Smp::Int64(0), ref1->Count());
    CPPUNIT_ASSERT(ref1->Begin() == ref1->End());
  }

  ref1->AddPublic(comp1);
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(1), ref1->Count());
  CPPUNIT_ASSERT(ref1->Begin() != ref1->End());

  ref1->Clear();
  CPPUNIT_ASSERT_EQUAL(Smp::Int64(0), ref1->Count());

  delete comp1;
  delete comp2;
  delete ref1;
}

void
ReferenceTest::testExceptions(void)
{
  //    bool exceptionCatched = false;
  //
  //    try {
  //        const Object* obj = new Object("", "");
  //        delete obj;
  //    } catch (Smp::InvalidObjectName& ex) {
  //        exceptionCatched = true;
  //    }
  //
  //    CPPUNIT_ASSERT_EQUAL(true, exceptionCatched);
}
