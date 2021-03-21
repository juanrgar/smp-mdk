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

#ifndef MDK_ENTRYPOINT_H_
#define MDK_ENTRYPOINT_H_

#include "Mdk/Object.h"
#include "Smp/IComponent.h"
#include "Smp/IEntryPoint.h"

namespace Smp {
namespace Mdk {
class EntryPoint
  : public Smp::Mdk::Object
  , public virtual Smp::IEntryPoint
{
public:
  template<typename T>
  EntryPoint(Smp::String8 name,
             Smp::String8 description,
             T* owner,
             void (T::*entryPoint)(void)) throw(Smp::InvalidObjectName)
    : Object(name, description)
    , m_entryPointHelper(new EntryPointHelper<T>(owner, entryPoint))
    , m_owner(owner)
  {}

  virtual ~EntryPoint(void)
  {
    if (this->m_entryPointHelper != NULL) {
      delete this->m_entryPointHelper;
      this->m_entryPointHelper = NULL;
    }
  }

  Smp::IComponent* GetOwner(void) const { return this->m_owner; }

  void Execute(void) const
  {
    if (this->m_entryPointHelper != NULL) {
      this->m_entryPointHelper->Execute();
    }
  }

  void operator()() const { Execute(); }

private:
  class IEntryPointHelper
  {
  public:
    virtual ~IEntryPointHelper(void) {}

    virtual void Execute(void) = 0;
  };

  template<typename T>
  class EntryPointHelper : public virtual IEntryPointHelper
  {
  private:
    typedef void (T::*EntryPointType)(void);

  public:
    EntryPointHelper(T* owner, EntryPointType entryPoint)
      : m_owner(owner)
      , m_entryPoint(entryPoint)
    {}

    virtual ~EntryPointHelper(void) {}

    void Execute(void)
    {
      if (this->m_owner != NULL) {
        (this->m_owner->*m_entryPoint)();
      }
    }

  private:
    T* m_owner;
    EntryPointType m_entryPoint;
  };

private:
  Smp::IComponent* m_owner;
  IEntryPointHelper* m_entryPointHelper;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_ENTRYPOINT_H_
