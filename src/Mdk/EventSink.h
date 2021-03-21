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

#ifndef MDK_EVENTSINK_H_
#define MDK_EVENTSINK_H_

#include "Mdk/Object.h"
#include "Smp/IComponent.h"
#include "Smp/IEventSink.h"

namespace Smp {
namespace Mdk {
class MdkEventSink : public virtual Smp::IEventSink
{};

class VoidEventSink
  : public Smp::Mdk::Object
  , public virtual MdkEventSink
{
public:
  template<typename T>
  VoidEventSink(
    Smp::String8 name,
    Smp::String8 description,
    T* consumer,
    void (T::*callback)(Smp::IObject* sender)) throw(Smp::InvalidObjectName)
    : Object(name, description)
    , m_eventSinkHelper(new VoidEventSinkHelper<T>(consumer, callback))
  {}

  virtual ~VoidEventSink(void)
  {
    if (this->m_eventSinkHelper != NULL) {
      delete this->m_eventSinkHelper;
      this->m_eventSinkHelper = NULL;
    }
  }

  void Notify(Smp::IObject* sender, Smp::AnySimple arg)
  {
    if (this->m_eventSinkHelper != NULL) {
      this->m_eventSinkHelper->Notify(sender);
    }
  }

private:
  class IVoidEventSinkHelper
  {
  public:
    virtual ~IVoidEventSinkHelper(void) {}

    virtual void Notify(Smp::IObject* sender) = 0;
  };

  template<typename T>
  class VoidEventSinkHelper : public virtual IVoidEventSinkHelper
  {
  private:
    typedef void (T::*CallbackType)(Smp::IObject* sender);

  public:
    VoidEventSinkHelper(T* consumer, CallbackType callback)
      : m_consumer(consumer)
      , m_callback(callback)
    {}

    virtual ~VoidEventSinkHelper(void) {}

    void Notify(Smp::IObject* sender)
    {
      if (this->m_consumer != NULL) {
        (this->m_consumer->*m_callback)(sender);
      }
    }

  private:
    T* m_consumer;
    CallbackType m_callback;
  };

  IVoidEventSinkHelper* m_eventSinkHelper;
};

class EventSink
  : public Smp::Mdk::Object
  , public virtual Smp::IEventSink
{
public:
  template<typename T>
  EventSink(
    Smp::String8 name,
    Smp::String8 description,
    T* consumer,
    void (T::*callback)(Smp::IObject* sender,
                        Smp::AnySimple arg)) throw(Smp::InvalidObjectName)
    : Object(name, description)
    , m_eventSinkHelper(new EventSinkHelper<T>(consumer, callback))
  {}

  virtual ~EventSink(void)
  {
    if (this->m_eventSinkHelper != NULL) {
      delete this->m_eventSinkHelper;
      this->m_eventSinkHelper = NULL;
    }
  }

  void Notify(Smp::IObject* sender, Smp::AnySimple arg)
  {
    if (this->m_eventSinkHelper != NULL) {
      this->m_eventSinkHelper->Notify(sender, arg);
    }
  }

private:
  class IEventSinkHelper
  {
  public:
    virtual ~IEventSinkHelper(void) {}

    virtual void Notify(Smp::IObject* sender, const Smp::AnySimple& arg) = 0;
  };

  template<typename T>
  class EventSinkHelper : public virtual IEventSinkHelper
  {
  private:
    typedef void (T::*CallbackType)(Smp::IObject* sender, Smp::AnySimple arg);

  public:
    EventSinkHelper(T* consumer, CallbackType callback)
      : m_consumer(consumer)
      , m_callback(callback)
    {}

    virtual ~EventSinkHelper(void) {}

    void Notify(Smp::IObject* sender, const Smp::AnySimple& arg)
    {
      if (this->m_consumer != NULL) {
        (this->m_consumer->*m_callback)(sender, arg);
      }
    }

  private:
    T* m_consumer;
    CallbackType m_callback;
  };

private:
  IEventSinkHelper* m_eventSinkHelper;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_EVENTSINK_H_
