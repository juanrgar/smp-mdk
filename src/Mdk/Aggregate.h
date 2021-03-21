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

#ifndef MDK_AGGREGATE_H_
#define MDK_AGGREGATE_H_

#include "Smp/IAggregate.h"
#include "Smp/IReference.h"

namespace Smp {
namespace Mdk {
class Aggregate : public virtual Smp::IAggregate
{
public:
  Aggregate(void);
  virtual ~Aggregate(void);

  const Smp::ReferenceCollection* GetReferences(void) const;

  Smp::IReference* GetReference(Smp::String8 name) const;

protected:
  void AddReference(Smp::IReference* ref);

  void Clear(void);

private:
  Smp::ReferenceCollection m_references;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_COMPONENT_H_
