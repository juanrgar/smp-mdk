/** This file is part of smp-mdk
 *
 * Copyright (C) 2017 Juan R. Garcia Blanco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MDK_EVENTSOURCE_H_
#define MDK_EVENTSOURCE_H_

#include "Mdk/EventSink.h"
#include "Mdk/Object.h"
#include "Mdk/SimpleTypes.h"

#include "Smp/IComponent.h"
#include "Smp/IEventSource.h"

namespace Smp {
namespace Mdk {
class VoidEventSource
  : public Smp::Mdk::Object
  , public virtual Smp::IEventSource
{
public:
  VoidEventSource(Smp::String8 name,
                  Smp::String8 description,
                  Smp::IComponent* publisher) throw(Smp::InvalidObjectName)
    : Object(name, description)
  {}

  virtual ~VoidEventSource(void) { this->m_eventSinks.clear(); }

  virtual void Subscribe(Smp::IEventSink* eventSink) throw(
    Smp::IEventSource::AlreadySubscribed,
    Smp::IEventSource::InvalidEventSink)
  {
    VoidEventSink* voidEventSink = dynamic_cast<VoidEventSink*>(eventSink);

    if (voidEventSink == NULL) {
      throw Smp::IEventSource::InvalidEventSink(this, eventSink);
    }

    for (Smp::EventSinkCollection::const_iterator it(
           this->m_eventSinks.begin());
         it != this->m_eventSinks.end();
         ++it) {
      if (*it == eventSink) {
        throw Smp::IEventSource::AlreadySubscribed(this, eventSink);
      }
    }

    this->m_eventSinks.push_back(eventSink);
  }

  virtual void Unsubscribe(Smp::IEventSink* eventSink) throw(
    Smp::IEventSource::NotSubscribed)
  {
    Smp::Bool found = false;
    Smp::EventSinkCollection::iterator it(this->m_eventSinks.end());

    while (!found && (it != this->m_eventSinks.end())) {
      if (*it == eventSink) {
        found = true;
      }

      ++it;
    }

    if (found) {
      this->m_eventSinks.erase(it);
    } else {
      throw Smp::IEventSource::NotSubscribed(this, eventSink);
    }
  }

  void Emit(Smp::IComponent* sender)
  {
    Smp::AnySimple arg;
    arg.type = Smp::ST_None;

    for (Smp::EventSinkCollection::iterator it(this->m_eventSinks.begin());
         it != this->m_eventSinks.end();
         ++it) {
      (*it)->Notify(sender, arg);
    }
  }

  void operator()(Smp::IComponent* sender) { Emit(sender); }

private:
  Smp::EventSinkCollection m_eventSinks;
};

template<typename T>
class EventSource
  : public Smp::Mdk::Object
  , public virtual Smp::IEventSource
{
public:
  EventSource(Smp::String8 name,
              Smp::String8 description,
              Smp::IComponent* publisher) throw(Smp::InvalidObjectName)
    : Object(name, description)
  {}

  virtual ~EventSource(void) { this->m_eventSinks.clear(); }

  virtual void Subscribe(Smp::IEventSink* eventSink) throw(
    Smp::IEventSource::AlreadySubscribed,
    Smp::IEventSource::InvalidEventSink)
  {
    EventSink* mdkEventSink = dynamic_cast<EventSink*>(eventSink);

    if (mdkEventSink == NULL) {
      throw Smp::IEventSource::InvalidEventSink(this, eventSink);
    }

    for (Smp::EventSinkCollection::const_iterator it(
           this->m_eventSinks.begin());
         it != this->m_eventSinks.end();
         ++it) {
      if (*it == eventSink) {
        throw Smp::IEventSource::AlreadySubscribed(this, eventSink);
      }
    }

    this->m_eventSinks.push_back(eventSink);
  }

  virtual void Unsubscribe(Smp::IEventSink* eventSink) throw(
    Smp::IEventSource::NotSubscribed)
  {
    Smp::Bool found = false;
    Smp::EventSinkCollection::iterator it(this->m_eventSinks.end());

    while (!found && (it != this->m_eventSinks.end())) {
      if (*it == eventSink) {
        found = true;
      }

      ++it;
    }

    if (found) {
      this->m_eventSinks.erase(it);
    } else {
      throw Smp::IEventSource::NotSubscribed(this, eventSink);
    }
  }

  void Emit(Smp::IComponent* sender, T arg)
  {
    Smp::Mdk::AnySimple anyArg;
    anyArg.Set(arg);

    for (Smp::EventSinkCollection::iterator it(this->m_eventSinks.begin());
         it != this->m_eventSinks.end();
         ++it) {
      (*it)->Notify(sender, anyArg);
    }
  }

  void operator()(Smp::IComponent* sender, T arg) { Emit(sender, arg); }

private:
  Smp::EventSinkCollection m_eventSinks;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_EVENTSOURCE_H_
