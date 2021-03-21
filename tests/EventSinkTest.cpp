#include "EventSinkTest.h"

#include "Mdk/EventSink.h"

#include "Smp/IObject.h"

using namespace Smp::Mdk;

class EventSinkConsumer
{
public:
  EventSinkConsumer(void);
  virtual ~EventSinkConsumer(void);

  void EventCallback(Smp::IObject* sender, Smp::AnySimple arg);

  const Smp::IObject* get_LastSender(void) const;
  const Smp::AnySimple& get_LastArg(void) const;

private:
  Smp::IObject* lastSender;
  Smp::AnySimple lastArg;
};

EventSinkConsumer::EventSinkConsumer(void) {}

EventSinkConsumer::~EventSinkConsumer(void) {}

void
EventSinkConsumer::EventCallback(Smp::IObject* sender, Smp::AnySimple arg)
{
  this->lastSender = sender;
  this->lastArg = arg;
}

const Smp::IObject*
EventSinkConsumer::get_LastSender(void) const
{
  return this->lastSender;
}

const Smp::AnySimple&
EventSinkConsumer::get_LastArg(void) const
{
  return this->lastArg;
}

class EventProducer : public virtual Smp::IObject
{
public:
  EventProducer(void) {}
  virtual ~EventProducer(void) {}

  Smp::String8 GetName(void) const { return NULL; }
  Smp::String8 GetDescription(void) const { return NULL; }
};

void
EventSinkTest::setUp(void)
{}

void
EventSinkTest::tearDown(void)
{}

void
EventSinkTest::testInstantiation(void)
{
  {
    EventSinkConsumer* consumer = new EventSinkConsumer();
    EventSink* eventSink = new EventSink(
      "Name", "Description", consumer, &EventSinkConsumer::EventCallback);

    CPPUNIT_ASSERT(eventSink != NULL);

    delete eventSink;
    delete consumer;
  }
}

void
EventSinkTest::testExecution(void)
{
  {
    EventSinkConsumer* consumer = new EventSinkConsumer();
    EventSink* eventSink = new EventSink(
      "Name", "Description", consumer, &EventSinkConsumer::EventCallback);

    Smp::IObject* senderGiven = NULL;
    Smp::AnySimple argGiven;
    argGiven.type = Smp::ST_UInt32;
    argGiven.value.uInt32Value = 24;

    eventSink->Notify(senderGiven, argGiven);

    const Smp::IObject* senderGot = consumer->get_LastSender();
    CPPUNIT_ASSERT_EQUAL(static_cast<const Smp::IObject*>(senderGiven),
                         senderGot);

    const Smp::AnySimple& argGot = consumer->get_LastArg();
    CPPUNIT_ASSERT_EQUAL(argGiven.type, argGot.type);
    CPPUNIT_ASSERT_EQUAL(argGiven.value.uInt32Value, argGot.value.uInt32Value);

    delete eventSink;
    delete consumer;
  }

  {
    EventProducer* senderGiven = new EventProducer();
    EventSinkConsumer* consumer = new EventSinkConsumer();
    EventSink* eventSink = new EventSink(
      "Name", "Description", consumer, &EventSinkConsumer::EventCallback);

    Smp::AnySimple argGiven;
    argGiven.type = Smp::ST_UInt32;
    argGiven.value.uInt32Value = 24;

    eventSink->Notify(senderGiven, argGiven);

    const Smp::IObject* senderGot = consumer->get_LastSender();
    CPPUNIT_ASSERT_EQUAL(static_cast<const Smp::IObject*>(senderGiven),
                         senderGot);

    const Smp::AnySimple& argGot = consumer->get_LastArg();
    CPPUNIT_ASSERT_EQUAL(argGiven.type, argGot.type);
    CPPUNIT_ASSERT_EQUAL(argGiven.value.uInt32Value, argGot.value.uInt32Value);

    delete eventSink;
    delete consumer;
  }
}
