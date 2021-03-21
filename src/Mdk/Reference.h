/** This file is part of smp-mdk
 *
 * Copyright (C) 2018 Juan R. Garcia Blanco
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

#ifndef MDK_REFERENCE_H_
#define MDK_REFERENCE_H_

#include "Mdk/Object.h"
#include "Smp/IReference.h"

#include <algorithm>

namespace Smp {
namespace Mdk {
template<typename T>
class Reference
  : public Smp::Mdk::Object
  , public virtual Smp::IReference
{
public:
  typedef typename std::vector<T*> ProviderCollection;
  typedef typename ProviderCollection::const_iterator ProviderIterator;

  Reference(Smp::String8 name,
            Smp::String8 description,
            Smp::IComponent* parent) throw(Smp::InvalidObjectName)
    : Object(name, description)
    , m_parent(parent)
  {}

  virtual ~Reference(void) { Clear(); }

  virtual const Smp::ComponentCollection* GetComponents(void) const
  {
    return &(this->m_components);
  }

  virtual Smp::IComponent* GetComponent(Smp::String8 name) const
  {
    Smp::ComponentCollection::const_iterator it(this->m_components.begin());
    Smp::ComponentCollection::const_iterator endIt(this->m_components.end());
    Smp::IComponent* comp = NULL;

    while ((comp == NULL) && (it != endIt)) {
      if (::strcmp(name, (*it)->GetName()) == 0) {
        comp = *it;
      }

      ++it;
    }

    return comp;
  }

  virtual Smp::Int64 Count(void) const { return this->m_providers.size(); }

  virtual ProviderIterator Begin(void) { return this->m_providers.begin(); }

  virtual ProviderIterator End(void) { return this->m_providers.end(); }

  virtual ProviderIterator begin(void) { return this->m_providers.begin(); }

  virtual ProviderIterator end(void) { return this->m_providers.end(); }

  virtual void Clear(void)
  {
    this->m_providers.clear();
    this->m_components.clear();
  }

  virtual T* At(Smp::Int32 index) const
  {
    T* ret = NULL;

    if ((index >= 0) && (index < this->m_providers.size())) {
      ret = this->m_providers[index];
    }

    return ret;
  }

  virtual T* operator[](Smp::Int32 index) { return At(index); }

protected:
  virtual void Add(Smp::IComponent* component) throw(Smp::InvalidObjectType)
  {
    if (component == NULL) {
      return;
    }

    T* provider = dynamic_cast<T*>(component);

    if (provider == NULL) {
      throw Smp::InvalidObjectType(component);
    }

    this->m_providers.push_back(provider);
    this->m_components.push_back(component);
  }

  virtual Smp::Bool Remove(Smp::IComponent* component)
  {
    if (component == NULL) {
      return false;
    }

    T* provider = dynamic_cast<T*>(component);

    if (provider == NULL) {
      return false;
    }

    Smp::Bool res = true;

    typename ProviderCollection::iterator it =
      std::find(this->m_providers.begin(), this->m_providers.end(), provider);

    if (it != this->m_providers.end()) {
      this->m_providers.erase(it);

      Smp::ComponentCollection::iterator jt = std::find(
        this->m_components.begin(), this->m_components.end(), provider);

      if (jt != this->m_components.end()) {
        this->m_components.erase(jt);
      }
    } else {
      res = false;
    }

    return res;
  }

private:
  Smp::IComponent* m_parent;
  ProviderCollection m_providers;
  Smp::ComponentCollection m_components;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_REFERENCE_H_
