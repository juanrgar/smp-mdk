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

#include "Mdk/Uuid.h"

#include <cstring>

using namespace Smp::Mdk;

Uuid::Uuid(void)
{
  *this = NullUuid;
}

Uuid::Uuid(const Smp::Uuid& source)
{
  this->Data1 = source.Data1;
  this->Data2 = source.Data2;
  this->Data3 = source.Data3;
  ::memcpy(this->Data4, source.Data4, sizeof(this->Data4));
}

Uuid::Uuid(const char* uuidString)
{
  Set(uuidString);
}

Uuid&
Uuid::operator=(const Smp::Uuid& source)
{
  this->Data1 = source.Data1;
  this->Data2 = source.Data2;
  this->Data3 = source.Data3;
  ::memcpy(this->Data4, source.Data4, sizeof(this->Data4));

  return *this;
}

Uuid&
Uuid::operator=(const char* uuidString)
{
  return *this;
}

Smp::Bool
Uuid::operator==(const Smp::Uuid uuid) const
{
  return (this->Data1 == uuid.Data1) && (this->Data2 == uuid.Data2) &&
         (this->Data3 == uuid.Data3) &&
         (::memcmp(this->Data4, uuid.Data4, sizeof(this->Data4)) == 0);
}

Smp::Bool
Uuid::operator!=(const Smp::Uuid uuid) const
{
  return (this->Data1 != uuid.Data1) || (this->Data2 != uuid.Data2) ||
         (this->Data3 != uuid.Data3) ||
         (::memcmp(this->Data4, uuid.Data4, sizeof(this->Data4)) != 0);
}

static struct BlockInfo
{
  Smp::Bool isRaw;
  Smp::UInt32 rawOff;
  Smp::UInt32 ini;
  Smp::UInt32 len;
} blockInfo[5] = { { false, 0, 0, 8 },
                   { false, 0, 9, 4 },
                   { false, 0, 14, 4 },
                   { true, 0, 19, 4 },
                   { true, 4, 24, 12 } };

Smp::Bool
Uuid::Set(const char* uuidString)
{
  if ((uuidString == NULL) || (::strlen(uuidString) != (BUFFER_SIZE - 1))) {
    return false;
  }

  if ((uuidString[8] != '-') || (uuidString[13] != '-') ||
      (uuidString[18] != '-') || (uuidString[23] != '-')) {
    return false;
  }

  Smp::UInt32 blockData[3] = {
    0,
  };
  Smp::UInt8 blockRaw[8] = {
    0,
  };

  for (Smp::UInt32 i(0); i != 5; ++i) {
    BlockInfo& info = blockInfo[i];
    Smp::UInt32 ini = info.ini;

    for (Smp::UInt32 j(0); j != info.len; ++j) {
      Smp::Char8 c = uuidString[ini + j];
      Smp::UInt8 cnum = 0;

      if ((c >= '0') && (c <= '9')) {
        cnum = c - '0';
      } else if ((c >= 'a') && (c <= 'f')) {
        cnum = c - 'a' + 10;
      } else if ((c >= 'A') && (c <= 'F')) {
        cnum = c - 'A' + 10;
      } else {
        return false;
      }

      if (info.isRaw) {
        Smp::UInt32 off = (1 - (j & 0x01)) * 4;
        blockRaw[(info.rawOff + j) / 2] |= (cnum << off);
      } else {
        Smp::UInt32 off = (info.len - j - 1) * 4;
        blockData[i] |= (cnum << off);
      }
    }
  }

  this->Data1 = blockData[0];
  this->Data2 = (blockData[1] & 0x0FFFF);
  this->Data3 = (blockData[2] & 0x0FFFF);
  ::memcpy(this->Data4, blockRaw, sizeof(this->Data4));

  return true;
}

void
Uuid::Get(char* uuidString) const
{
  if (uuidString == NULL) {
    return;
  }

  const Smp::UInt32 blockData[3] = { this->Data1, this->Data2, this->Data3 };
  const Smp::UInt8* blockRaw = this->Data4;

  for (Smp::UInt32 i(0); i != 5; ++i) {
    BlockInfo& info = blockInfo[i];
    Smp::UInt32 ini = info.ini;

    for (Smp::UInt32 j(0); j != info.len; ++j) {
      Smp::UInt8 cnum = 0;

      if (info.isRaw) {
        Smp::UInt32 off = (1 - (j & 0x01)) * 4;
        cnum = ((blockRaw[(info.rawOff + j) / 2] >> off) & 0x0F);
      } else {
        Smp::UInt32 off = (info.len - j - 1) * 4;
        cnum = ((blockData[i] >> off) & 0x0F);
      }
      Smp::Char8 c = '\0';

      if ((cnum >= 0) && (cnum <= 9)) {
        c = cnum + '0';
      } else if ((cnum >= 10) && (cnum <= 15)) {
        c = cnum - 10 + 'A';
      }

      uuidString[ini + j] = c;
    }
  }

  uuidString[8] = '-';
  uuidString[13] = '-';
  uuidString[18] = '-';
  uuidString[23] = '-';
  uuidString[BUFFER_SIZE - 1] = '\0';
}
