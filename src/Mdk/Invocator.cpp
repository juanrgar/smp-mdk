/** This file is part of smp-mdk
 *
 * Copyright (C) 2021 Juan R. Garcia Blanco
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

#include "Mdk/Invocator.h"

using namespace Smp::Mdk;

Invocator::Invocator(Smp::String8 name,
                     Smp::String8 description,
                     Smp::IDynamicInvocation* owner,
                     Smp::IRequest* request)
  : Mdk::Object(name, description)
  , m_owner(owner)
  , m_request(request)
{}

Invocator::~Invocator() {}

Smp::IComponent*
Invocator::GetOwner(void) const
{
  return m_owner;
}

void
Invocator::Execute() const
{
  m_owner->Invoke(m_request);
}

void
Invocator::operator()() const
{
  Execute();
}