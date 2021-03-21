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

#ifndef MDK_INVOCATOR_H_
#define MDK_INVOCATOR_H_

#include "Mdk/Object.h"
#include "Smp/IDynamicInvocation.h"
#include "Smp/IEntryPoint.h"

namespace Smp {
namespace Mdk {
class Invocator
  : public virtual Smp::Mdk::Object
  , public virtual Smp::IEntryPoint
{
public:
  Invocator(Smp::String8 name,
            Smp::String8 description,
            Smp::IDynamicInvocation* owner,
            Smp::IRequest* request);
  virtual ~Invocator();

  Smp::IComponent* GetOwner(void) const;

  void Execute() const;

  void operator()() const;

private:
  IDynamicInvocation* m_owner;
  IRequest* m_request;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_INVOCATOR_H_
