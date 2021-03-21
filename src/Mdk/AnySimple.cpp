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

#include "Mdk/AnySimple.h"

using namespace Smp::Mdk;

Smp::AnySimple&
AnySimple::operator=(const Smp::AnySimple& source)
{
  if (this->owner && (this->type == Smp::ST_String8)) {
    delete[] this->value.string8Value;
    this->value.string8Value = NULL;
  }

  this->type = source.type;

  if (source.type == Smp::ST_String8) {
    this->owner = true;
    this->value.string8Value = strdup(source.value.string8Value);
  } else {
    value = source.value;
  }

  return *this;
}

void
AnySimple::Set(const Smp::Int64 v,
               Smp::SimpleTypeKind t) throw(Smp::InvalidAnyType)
{
  this->type = t;
  this->value.int64Value = v;
}

#define ANY_SIMPLE_SETTER(typeU, typeu)                                        \
  void AnySimple::Set(Smp::typeU v)                                            \
  {                                                                            \
    this->type = Smp::ST_##typeU;                                              \
    this->value.typeu##Value = v;                                              \
  }

ANY_SIMPLE_SETTER(Bool, bool)
ANY_SIMPLE_SETTER(Char8, char8)
ANY_SIMPLE_SETTER(Int8, int8)
ANY_SIMPLE_SETTER(UInt8, uInt8)
ANY_SIMPLE_SETTER(Int16, int16)
ANY_SIMPLE_SETTER(UInt16, uInt16)
ANY_SIMPLE_SETTER(Int32, int32)
ANY_SIMPLE_SETTER(UInt32, uInt32)
ANY_SIMPLE_SETTER(Int64, int64)
ANY_SIMPLE_SETTER(UInt64, uInt64)
ANY_SIMPLE_SETTER(Float32, float32)
ANY_SIMPLE_SETTER(Float64, float64)

void
AnySimple::Set(Smp::Mdk::DateTime& v)
{
  Set(v.ticks, Smp::ST_DateTime);
}

void
AnySimple::Set(Smp::Mdk::Duration& v)
{
  Set(v.ticks, Smp::ST_Duration);
}

void
AnySimple::Set(Smp::String8 const v)
{
  if (v == NULL) {
    return;
  }

  if (this->owner == (this->type == Smp::ST_String8)) {
    delete[] this->value.string8Value;
    this->value.string8Value = NULL;
  }

  this->owner = true;
  this->value.string8Value = strdup(v);
}

void
AnySimple::Set(Smp::AnySimple& source) throw(Smp::InvalidAnyType)
{
  *this = source;
}

#define ANY_SIMPLE_GETTER(typeU, typeu)                                        \
  void AnySimple::Get(Smp::typeU& v) throw(Smp::InvalidAnyType)                \
  {                                                                            \
    if (this->type == Smp::ST_##typeU) {                                       \
      v = this->value.typeu##Value;                                            \
    } else {                                                                   \
      throw Smp::InvalidAnyType(Smp::ST_##typeU, this->type);                  \
    }                                                                          \
  }

ANY_SIMPLE_GETTER(Bool, bool)
ANY_SIMPLE_GETTER(Char8, char8)
ANY_SIMPLE_GETTER(Int8, int8)
ANY_SIMPLE_GETTER(UInt8, uInt8)
ANY_SIMPLE_GETTER(Int16, int16)
ANY_SIMPLE_GETTER(UInt16, uInt16)
ANY_SIMPLE_GETTER(Int32, int32)
ANY_SIMPLE_GETTER(UInt32, uInt32)
ANY_SIMPLE_GETTER(Int64, int64)
ANY_SIMPLE_GETTER(UInt64, uInt64)
ANY_SIMPLE_GETTER(Float32, float32)
ANY_SIMPLE_GETTER(Float64, float64)
ANY_SIMPLE_GETTER(String8, string8)
