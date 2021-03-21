#include "EventsTest.h"

#include "Mdk/EventSink.h"
#include "Mdk/EventSource.h"

#include "Smp/IObject.h"

using namespace Smp::Mdk;

// ****************************************************************************************************************
// //

class Target
{
public:
  Target(void);
  virtual ~Target(void);

  void VoidCallback(Smp::IObject* sender);
  void BoolCallback(Smp::IObject* sender, Smp::AnySimple arg);

  const Smp::IObject* get_LastSender(void) const;
  const Smp::AnySimple& get_LastArg(void) const;
  void Reset(void);

  Smp::IEventSink* MyVoidEventSink;
  Smp::IEventSink* MyBoolEventSink;

private:
  VoidEventSink* _myVoidEventSink;
  EventSink* _myBoolEventSink;

  Smp::IObject* lastSender;
  Smp::AnySimple lastArg;
};

Target::Target(void)
{
  this->_myVoidEventSink = new VoidEventSink("TargetVoidEventSink",
                                             "EventSink Description",
                                             this,
                                             &Target::VoidCallback);
  this->MyVoidEventSink = this->_myVoidEventSink;

  this->_myBoolEventSink = new EventSink("TargetBoolEventSink",
                                         "EventSink Description",
                                         this,
                                         &Target::BoolCallback);
  this->MyBoolEventSink = this->_myBoolEventSink;

  Reset();
}

Target::~Target(void)
{
  if (this->_myVoidEventSink != NULL) {
    delete this->_myVoidEventSink;
    this->_myVoidEventSink = NULL;
    this->MyVoidEventSink = NULL;
  }
}

void
Target::VoidCallback(Smp::IObject* sender)
{
  this->lastSender = sender;
  this->lastArg.type = Smp::ST_None;
}

void
Target::BoolCallback(Smp::IObject* sender, Smp::AnySimple arg)
{
  this->lastSender = sender;
  this->lastArg = arg;
}

const Smp::IObject*
Target::get_LastSender(void) const
{
  return this->lastSender;
}

const Smp::AnySimple&
Target::get_LastArg(void) const
{
  return this->lastArg;
}

void
Target::Reset(void)
{
  this->lastSender = NULL;
  this->lastArg.type = Smp::ST_None;
}

// ****************************************************************************************************************
// //

class Source : public virtual Smp::IComponent
{
public:
  Source(void);
  virtual ~Source(void);

  Smp::String8 GetName(void) const { return NULL; }
  Smp::String8 GetDescription(void) const { return NULL; }
  Smp::IComposite* GetParent(void) const { return NULL; }

  void EmitVoidEvent(void);
  void EmitBoolEvent(Smp::Bool arg);

  Smp::IEventSource* MyVoidEventSource;
  Smp::IEventSource* MyBoolEventSource;

private:
  VoidEventSource* _myVoidEventSource;
  EventSource<Smp::Bool>* _myBoolEventSource;
};

Source::Source(void)
{
  this->_myVoidEventSource = new VoidEventSource(
    "SourceVoidEventSource", "EventSource Description", this);
  this->MyVoidEventSource = this->_myVoidEventSource;

  this->_myBoolEventSource = new EventSource<Smp::Bool>(
    "SourceBoolEventSource", "EventSource Description", this);
  this->MyBoolEventSource = this->_myBoolEventSource;
}

Source::~Source(void)
{
  if (this->_myVoidEventSource != NULL) {
    delete this->_myVoidEventSource;
    this->_myVoidEventSource = NULL;
    this->MyVoidEventSource = NULL;
  }
}

void
Source::EmitVoidEvent(void)
{
  if (this->_myVoidEventSource != NULL) {
    this->_myVoidEventSource->Emit(this);
  }
}

void
Source::EmitBoolEvent(Smp::Bool arg)
{
  if (this->_myBoolEventSource != NULL) {
    this->_myBoolEventSource->Emit(this, arg);
  }
}

// ****************************************************************************************************************
// //

void
EventsTest::setUp(void)
{}

void
EventsTest::tearDown(void)
{}

void
EventsTest::testInstantiation(void)
{
  {
    Target* target = new Target();
    Source* source = new Source();

    CPPUNIT_ASSERT(target != NULL);
    CPPUNIT_ASSERT(source != NULL);

    delete target;
    delete source;
  }
}

void
EventsTest::testConnection(void)
{
  {
    Target* target = new Target();
    Source* source = new Source();
    Smp::Bool exceptionRaised = false;

    try {
      source->MyVoidEventSource->Subscribe(target->MyVoidEventSink);
    } catch (std::exception& ex) {
      exceptionRaised = true;
    }

    CPPUNIT_ASSERT_EQUAL(false, exceptionRaised);

    try {
      source->MyBoolEventSource->Subscribe(target->MyBoolEventSink);
    } catch (std::exception& ex) {
      exceptionRaised = true;
    }

    CPPUNIT_ASSERT_EQUAL(false, exceptionRaised);

    delete target;
    delete source;
  }
}

void
EventsTest::testTrigger(void)
{
  {
    Target* target = new Target();
    Source* source = new Source();

    source->MyVoidEventSource->Subscribe(target->MyVoidEventSink);
    source->EmitVoidEvent();

    CPPUNIT_ASSERT(target->get_LastSender() == source);
    CPPUNIT_ASSERT_EQUAL(Smp::ST_None, target->get_LastArg().type);

    source->MyBoolEventSource->Subscribe(target->MyBoolEventSink);
    source->EmitBoolEvent(true);

    CPPUNIT_ASSERT(target->get_LastSender() == source);
    CPPUNIT_ASSERT_EQUAL(Smp::ST_Bool, target->get_LastArg().type);
    CPPUNIT_ASSERT_EQUAL(true, target->get_LastArg().value.boolValue);

    delete target;
    delete source;
  }
}
