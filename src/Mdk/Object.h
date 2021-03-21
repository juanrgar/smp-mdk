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

#ifndef MDK_OBJECT_H_
#define MDK_OBJECT_H_

#include "Smp/Exceptions.h"
#include "Smp/IObject.h"

namespace Smp {
namespace Mdk {
class Object : public virtual Smp::IObject
{
public:
  Object(void);
  Object(Smp::String8 name,
         Smp::String8 description) throw(Smp::InvalidObjectName);
  virtual ~Object(void);

  virtual Smp::String8 GetName(void) const;
  virtual Smp::String8 GetDescription(void) const;

  static Smp::Bool ValidateName(Smp::String8 name);

protected:
  Smp::Char8* m_name;
  Smp::Char8* m_description;

private:
  static Smp::Bool ValidateNameLength(size_t nameLen);
  static Smp::Bool ValidateNameChars(Smp::String8 name, size_t nameLen);
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_OBJECT_H_
