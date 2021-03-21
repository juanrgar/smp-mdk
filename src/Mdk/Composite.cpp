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

#include "Mdk/Composite.h"

#include <string.h>

#include <algorithm>

using namespace Smp::Mdk;

Composite::Composite(void) {}

Composite::~Composite(void)
{
  // It is guaranteed this will not throw any
  // exception.
  Clear();
}

const Smp::ContainerCollection*
Composite::GetContainers(void) const
{
  return &(this->m_containers);
}

Smp::IContainer*
Composite::GetContainer(Smp::String8 name) const
{
  if (name == NULL) {
    return NULL;
  }

  Smp::ContainerCollection::const_iterator it(this->m_containers.begin());
  Smp::ContainerCollection::const_iterator endIt(this->m_containers.end());
  Smp::IContainer* container = NULL;

  // We do not allow NULL containers.

  while ((container == NULL) && (it != endIt)) {
    if (strcmp(name, (*it)->GetName()) == 0) {
      container = *it;
    }
    ++it;
  }

  return container;
}

void
Composite::AddContainer(Smp::IContainer* container)
{
  if (container == NULL) {
    return;
  }

  Smp::IContainer* dup = GetContainer(container->GetName());
  if (dup != NULL) {
    return;
  }

  this->m_containers.push_back(container);
}

void
Composite::Clear(void)
{
  this->m_containers.clear();
}
