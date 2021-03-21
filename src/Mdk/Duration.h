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

#ifndef MDK_DURATION_H_
#define MDK_DURATION_H_

#include "Smp/Exceptions.h"
#include "Smp/SimpleTypes.h"

namespace Smp {
namespace Mdk {
struct Duration
{
  Smp::Duration ticks;

  Duration(void);
  Duration(const Smp::Duration& source);
  Duration(const Smp::Int32 days,
           const Smp::Int16 hours,
           const Smp::Int16 minutes,
           const Smp::Int16 seconds,
           const Smp::Int32 nanoseconds = 0);
  Duration(const Smp::Float64 seconds);
  Duration(const char* string);

  Smp::Mdk::Duration& operator=(const Smp::Duration& source);
  Smp::Mdk::Duration& operator=(const Smp::Float64 seconds);
  Smp::Mdk::Duration operator-(void) const;
  Smp::Mdk::Duration operator+(Smp::Mdk::Duration duration) const;
  Smp::Mdk::Duration operator-(Smp::Mdk::Duration duration) const;
  void operator+=(Smp::Mdk::Duration duration);
  void operator-=(Smp::Mdk::Duration duration);
  Smp::Bool operator>(Smp::Mdk::Duration duration) const;
  Smp::Bool operator<(Smp::Mdk::Duration duration) const;
  Smp::Bool operator==(Smp::Mdk::Duration duration) const;
  Smp::Bool operator!=(Smp::Mdk::Duration duration) const;

  Smp::Bool Set(const Smp::Int32 days,
                const Smp::Int16 hours,
                const Smp::Int16 minutes,
                const Smp::Int16 seconds,
                const Smp::Int32 nanoseconds = 0);
  void Get(Smp::Int32& days,
           Smp::Int16& hours,
           Smp::Int16& minutes,
           Smp::Int16& seconds,
           Smp::Int32& nanoseconds) const;
  Smp::Bool Set(const Smp::Float64 seconds);
  Smp::Float64 Get(void) const;
  Smp::Bool Set(const char* string);
  void Get(char* string) const;
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_DURATION_H_
