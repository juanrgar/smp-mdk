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

#ifndef MDK_COMPOSITE_H_
#define MDK_COMPOSITE_H_

#include "Smp/IComposite.h"

namespace Smp {
namespace Mdk {
class Composite : public virtual Smp::IComposite
{
public:
  Composite(void);
  virtual ~Composite(void);

  virtual const Smp::ContainerCollection* GetContainers(void) const;

  virtual Smp::IContainer* GetContainer(Smp::String8 name) const;

protected:
  void AddContainer(Smp::IContainer* container);
  void Clear(void);

private:
  Smp::ContainerCollection m_containers;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_COMPOSITE_H_
