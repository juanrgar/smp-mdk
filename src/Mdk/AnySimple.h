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

#ifndef MDK_ANYSIMPLE_H_
#define MDK_ANYSIMPLE_H_

#include "Smp/Exceptions.h"
#include "Smp/SimpleTypes.h"

#include "Mdk/DateTime.h"
#include "Mdk/Duration.h"

namespace Smp {
namespace Mdk {
struct AnySimple : public Smp::AnySimple
{
public:
  Smp::AnySimple& operator=(const Smp::AnySimple& source);

  void Set(Smp::Int64 v, Smp::SimpleTypeKind t) throw(Smp::InvalidAnyType);

  void Set(Smp::Bool v);
  void Set(Smp::Char8 v);
  void Set(Smp::Int8 v);
  void Set(Smp::UInt8 v);
  void Set(Smp::Int16 v);
  void Set(Smp::UInt16 v);
  void Set(Smp::Int32 v);
  void Set(Smp::UInt32 v);
  void Set(Smp::Int64 v);
  void Set(Smp::UInt64 v);
  void Set(Smp::Float32 v);
  void Set(Smp::Float64 v);
  void Set(Smp::Mdk::DateTime& v);
  void Set(Smp::Mdk::Duration& v);
  void Set(Smp::String8 const v);
  void Set(Smp::AnySimple& source) throw(Smp::InvalidAnyType);

  void Get(Smp::Char8& v) throw(Smp::InvalidAnyType);
  void Get(Smp::Bool& v) throw(Smp::InvalidAnyType);
  void Get(Smp::Int8& v) throw(Smp::InvalidAnyType);
  void Get(Smp::Int16& v) throw(Smp::InvalidAnyType);
  void Get(Smp::Int32& v) throw(Smp::InvalidAnyType);
  void Get(Smp::Int64& v) throw(Smp::InvalidAnyType);
  void Get(Smp::UInt8& v) throw(Smp::InvalidAnyType);
  void Get(Smp::UInt16& v) throw(Smp::InvalidAnyType);
  void Get(Smp::UInt32& v) throw(Smp::InvalidAnyType);
  void Get(Smp::UInt64& v) throw(Smp::InvalidAnyType);
  void Get(Smp::Float32& v) throw(Smp::InvalidAnyType);
  void Get(Smp::Float64& v) throw(Smp::InvalidAnyType);
  void Get(Smp::String8& v) throw(Smp::InvalidAnyType);
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_ANYSIMPLE_H_
