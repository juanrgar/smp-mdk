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

#include "Mdk/Object.h"

#include <stdlib.h>
#include <string.h>

const size_t NAME_MIN_LEN = 0;
const size_t NAME_MAX_LEN = 32;

using namespace Smp::Mdk;

Object::Object(void)
  : m_name(NULL)
  , m_description(NULL)
{}

Object::Object(Smp::String8 name,
               Smp::String8 description) throw(Smp::InvalidObjectName)
{
  if (Object::ValidateName(name)) {
    this->m_name = strdup(name);
  } else {
    throw Smp::InvalidObjectName(name);
  }

  if (description != NULL) {
    this->m_description = strdup(description);
  }
}

Object::~Object()
{
  if (this->m_name != NULL) {
    free(this->m_name);
    this->m_name = NULL;
  }

  if (this->m_description != NULL) {
    free(this->m_description);
    this->m_description = NULL;
  }
}

Smp::String8
Object::GetName(void) const
{
  return this->m_name;
}

Smp::String8
Object::GetDescription(void) const
{
  return this->m_description;
}

Smp::Bool
Object::ValidateName(Smp::String8 name)
{
  Smp::Bool isValid = true;

  if (name == NULL) {
    isValid = false;
  } else {
    size_t nameLen = ::strlen(name);
    isValid = Object::ValidateNameLength(nameLen) &&
              Object::ValidateNameChars(name, nameLen);
  }

  return isValid;
}

inline Smp::Bool
Object::ValidateNameLength(size_t nameLen)
{
  return (nameLen > NAME_MIN_LEN) && (nameLen <= NAME_MAX_LEN);
}

inline Smp::Bool
Object::ValidateNameChars(Smp::String8 name, size_t nameLen)
{
  Smp::Bool remainsValid = (::isalpha(name[0]) != 0) ? true : false;
  Smp::UInt32 i = 1;

  while (remainsValid && (i < nameLen)) {
    const Smp::Bool isLetterOrDigit = (::isalnum(name[i]) != 0) ? true : false;
    const Smp::Bool isUnderscore = (name[i] == '_');
    const Smp::Bool isBracket = (name[i] == '[') || (name[i] == ']');

    remainsValid = isLetterOrDigit || isUnderscore || isBracket;
    ++i;
  }

  return remainsValid;
}
