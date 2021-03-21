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

#ifndef MDK_UUID_H_
#define MDK_UUID_H_

#include "Smp/Exceptions.h"
#include "Smp/SimpleTypes.h"

namespace Smp {
namespace Mdk {
struct Uuid : public Smp::Uuid
{
  static const Smp::Int32 BUFFER_SIZE = 37;

  Uuid(void);
  Uuid(const Smp::Uuid& source);
  Uuid(const char* uuidString);

  Uuid& operator=(const Smp::Uuid& source);
  Uuid& operator=(const char* uuidString);
  Smp::Bool operator==(const Smp::Uuid uuid) const;
  Smp::Bool operator!=(const Smp::Uuid uuid) const;

  Smp::Bool Set(const char* uuidString);
  void Get(char* uuidString) const;
};

static const Uuid NullUuid = Uuid("00000000-0000-0000-0000-000000000000");
} // namespace Mdk
} // namespace Smp

#endif // MDK_UUID_H_
