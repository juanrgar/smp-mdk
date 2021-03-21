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

#include "Mdk/Request.h"

#include <stdlib.h>
#include <string.h>

using namespace Smp::Mdk;

Request::Request(Smp::String8 name, Smp::SimpleTypeKind retType)
{
  m_name = strdup(name);
  m_returnValue.Set(0, retType);
}

Request::~Request()
{
  if (m_name) {
    free(m_name);
    m_name = NULL;
  }
}

Smp::String8
Request::GetOperationName() const
{
  return m_name;
}

Smp::Int32
Request::GetParameterCount() const
{
  return m_parameters.size();
}

Smp::Int32
Request::GetParameterIndex(Smp::String8 parameterName) const
{
  Smp::Int32 index = -1;

  for (ParameterCollection::const_iterator it(m_parameters.begin());
       it != m_parameters.end();
       ++it) {
    if (strcmp(it->GetName(), parameterName) == 0) {
      break;
    }
    ++index;
  }

  return index;
}

void
Request::SetParameterValue(
  const Smp::Int32 index,
  const Smp::AnySimple value) throw(Smp::IRequest::InvalidParameterIndex,
                                    Smp::IRequest::InvalidParameterValue,
                                    Smp::InvalidAnyType)
{
  if (index >= m_parameters.size()) {
    throw Smp::IRequest::InvalidParameterIndex(m_name, index);
  }
  Smp::AnySimple& val = m_parameters.at(index).GetValue();
  if (val.type != value.type) {
    throw Smp::InvalidAnyType(value.type, val.type);
  }
  // TODO when to throw InvalidReturnValue
  val = value;
}

Smp::AnySimple
Request::GetParameterValue(const Smp::Int32 index) const
  throw(Smp::IRequest::InvalidParameterIndex)
{
  if (index >= m_parameters.size()) {
    throw Smp::IRequest::InvalidParameterIndex(m_name, index);
  }
  return m_parameters.at(index).GetValue();
}

void
Request::SetReturnValue(const Smp::AnySimple value) throw(
  Smp::IRequest::InvalidReturnValue,
  Smp::IRequest::VoidOperation,
  Smp::InvalidAnyType)
{
  if (m_returnValue.type == ST_None) {
    throw Smp::IRequest::VoidOperation(m_name);
  }
  if (m_returnValue.type != value.type) {
    throw Smp::InvalidAnyType(value.type, m_returnValue.type);
  }
  // TODO when to throw InvalidReturnValue
  m_returnValue = value;
}

Smp::AnySimple
Request::GetReturnValue() const throw(Smp::IRequest::VoidOperation)
{
  if (m_returnValue.type == ST_None) {
    throw Smp::IRequest::VoidOperation(m_name);
  }
  return m_returnValue;
}

void
Request::AddParameter(Smp::String8 name, Smp::SimpleTypeKind type)
{
  m_parameters.push_back(Parameter(name, type));
}

Request::Parameter::Parameter(Smp::String8 name, Smp::SimpleTypeKind type)
{
  m_name = strdup(name);
  m_value.Set(0, type);
}

Request::Parameter::~Parameter()
{
  if (m_name != NULL) {
    free(m_name);
    m_name = NULL;
  }
}

const Smp::AnySimple&
Request::Parameter::GetValue() const
{
  return m_value;
}

Smp::AnySimple&
Request::Parameter::GetValue()
{
  return m_value;
}

Smp::String8
Request::Parameter::GetName() const
{
  return m_name;
}
