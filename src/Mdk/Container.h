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

#ifndef MDK_CONTAINER_H_
#define MDK_CONTAINER_H_

#include "Mdk/Object.h"
#include "Smp/IContainer.h"

#include <map>
#include <string>

namespace Smp {
namespace Mdk {
template<typename T>
class Container
  : public Smp::Mdk::Object
  , public virtual Smp::IContainer
{
public:
  typedef typename std::vector<T*> ChildCollection;
  typedef typename ChildCollection::const_iterator ChildIterator;
  typedef std::map<std::string, Smp::IComponent*> Map;
  typedef typename Map::value_type ValueType;
  typedef typename Map::iterator Iterator;
  typedef typename Map::const_iterator ConstIterator;

  Container(Smp::String8 name,
            Smp::String8 description,
            Smp::IComposite* parent) throw(Smp::InvalidObjectName)
    : Object(name, description)
    , m_parent(parent)
  {}

  virtual ~Container(void) { Clear(); }

  const ComponentCollection* GetComponents(void) const
  {
    return &(this->m_components);
  }

  Smp::IComponent* GetComponent(Smp::String8 name) const
  {
    Smp::IComponent* comp = NULL;

    ConstIterator it = this->m_componentsMap.find(name);
    if (it != this->m_componentsMap.end()) {
      comp = it->second;
    }

    return comp;
  }

  virtual Smp::Int64 Count(void) const { return this->m_children.size(); }

  ChildIterator Begin(void) { return this->m_children.begin(); }

  ChildIterator End(void) { return this->m_children.end(); }

  ChildIterator begin(void) { return this->m_children.begin(); }

  ChildIterator end(void) { return this->m_children.end(); }

  const ChildCollection* GetChildren(void) { return &(this->m_children); }

  virtual T* GetChild(Smp::String8 name) const
  {
    return dynamic_cast<T*>(GetComponent(name));
  }

  const Map& GetMap(void) const { return this->m_componentsMap; }

  void Clear(void)
  {
    for (typename ChildCollection::iterator it(this->m_children.begin());
         it != this->m_children.end();
         ++it) {
      delete *it;
    }

    this->m_children.clear();
    this->m_components.clear();
    this->m_componentsMap.clear();
  }

  T* At(Smp::UInt32 index) const
  {
    T* comp = NULL;

    if ((index >= 0) && (index < Count())) {
      comp = this->m_children.at(index);
    }

    return comp;
  }

  T* operator[](Smp::UInt32 index) const { return At(index); }

protected:
  void Add(Smp::IComponent* comp) throw(Smp::DuplicateName,
                                        Smp::InvalidObjectType)
  {
    if (comp == NULL) {
      return;
    }

    Smp::IComponent* dup = GetComponent(comp->GetName());
    if (dup != NULL) {
      throw Smp::DuplicateName(comp->GetName());
    }

    T* child = dynamic_cast<T*>(comp);
    if (child == NULL) {
      throw Smp::InvalidObjectType(comp);
    }

    this->m_children.push_back(child);
    this->m_components.push_back(comp);

    this->m_componentsMap.insert(ValueType(comp->GetName(), comp));
  }

  Smp::IComposite* m_parent;

private:
  Smp::ComponentCollection m_components;
  ChildCollection m_children;
  Map m_componentsMap;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_CONTAINER_H_
