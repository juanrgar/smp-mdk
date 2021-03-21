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

#include "Mdk/Management/ManagedModel.h"

using namespace Smp::Mdk::Management;

ManagedModel::ManagedModel() {}

ManagedModel::ManagedModel(
  Smp::String8 name,
  Smp::String8 description,
  Smp::IComposite* parent) throw(Smp::InvalidObjectName)
{}

ManagedModel::~ManagedModel() {}

void
ManagedModel::SetName(String8 name) throw(Smp::InvalidObjectName)
{}

void
ManagedModel::SetDescription(String8 description)
{}

void
ManagedModel::SetParent(IComposite* parent)
{}

Smp::AnySimple
ManagedModel::GetFieldValue(String8 fullName) throw(
  Smp::Management::IManagedModel::InvalidFieldName)
{
  return Smp::AnySimple();
}

void
ManagedModel::SetFieldValue(String8 fullName, const Smp::AnySimple value) throw(
  Smp::Management::IManagedModel::InvalidFieldName,
  Smp::Management::IManagedModel::InvalidFieldValue)
{}

void
ManagedModel::GetArrayValue(
  String8 fullName,
  const AnySimpleArray values,
  const Int32 length) throw(Smp::Management::IManagedModel::InvalidFieldName,
                            Smp::Management::IManagedModel::InvalidArraySize)
{}

void
ManagedModel::SetArrayValue(
  String8 fullName,
  const AnySimpleArray values,
  const Int32 length) throw(Smp::Management::IManagedModel::InvalidFieldName,
                            Smp::Management::IManagedModel::InvalidArraySize,
                            Smp::Management::IManagedModel::InvalidArrayValue)
{}