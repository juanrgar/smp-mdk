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

#ifndef MDK_REQUEST_H_
#define MDK_REQUEST_H_

#include "Mdk/SimpleTypes.h"
#include "Smp/IRequest.h"

namespace Smp {
namespace Mdk {
class Request : public virtual Smp::IRequest
{
public:
  Request(Smp::String8 name, Smp::SimpleTypeKind retType = Smp::ST_None);

  virtual ~Request(void);

  virtual Smp::String8 GetOperationName() const;

  virtual Smp::Int32 GetParameterCount() const;

  virtual Smp::Int32 GetParameterIndex(Smp::String8 parameterName) const;

  virtual void SetParameterValue(
    const Smp::Int32 index,
    const Smp::AnySimple value) throw(Smp::IRequest::InvalidParameterIndex,
                                      Smp::IRequest::InvalidParameterValue,
                                      Smp::InvalidAnyType);

  virtual Smp::AnySimple GetParameterValue(const Smp::Int32 index) const
    throw(Smp::IRequest::InvalidParameterIndex);

  virtual void SetReturnValue(const Smp::AnySimple value) throw(
    Smp::IRequest::InvalidReturnValue,
    Smp::IRequest::VoidOperation,
    Smp::InvalidAnyType);

  virtual Smp::AnySimple GetReturnValue() const
    throw(Smp::IRequest::VoidOperation);

  virtual void AddParameter(Smp::String8 name, Smp::SimpleTypeKind type);

private:
  class Parameter
  {
  public:
    Parameter(Smp::String8 name, Smp::SimpleTypeKind type);
    ~Parameter();
    const Smp::AnySimple& GetValue() const;
    Smp::AnySimple& GetValue();
    Smp::String8 GetName() const;

  private:
    Smp::Char8* m_name;
    Smp::Mdk::AnySimple m_value;
  };
  typedef std::vector<Parameter> ParameterCollection;

  Smp::Char8* m_name;
  Smp::Mdk::AnySimple m_returnValue;
  ParameterCollection m_parameters;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_REQUEST_H_
