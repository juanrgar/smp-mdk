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

#include "Mdk/Duration.h"

using namespace Smp::Mdk;

const Smp::Int64 NS_IN_SECOND = 1e9;
const Smp::Int64 NS_IN_MINUTE = 60 * NS_IN_SECOND;
const Smp::Int64 NS_IN_HOUR = 60 * NS_IN_MINUTE;
const Smp::Int64 NS_IN_DAY = 24 * NS_IN_HOUR;

Duration::Duration(void)
  : ticks(0L)
{}

Duration::Duration(const Smp::Duration& source)
  : ticks(source)
{}

Duration::Duration(const Smp::Int32 days,
                   const Smp::Int16 hours,
                   const Smp::Int16 minutes,
                   const Smp::Int16 seconds,
                   const Smp::Int32 nanoseconds)
  : ticks(days * NS_IN_DAY + hours * NS_IN_HOUR + minutes * NS_IN_MINUTE +
          seconds * NS_IN_SECOND + nanoseconds)
{}

Duration::Duration(const Smp::Float64 seconds)
  : ticks(seconds * NS_IN_SECOND)
{}

Duration::Duration(const char* string)
{
  // TODO
}

Smp::Mdk::Duration&
Duration::operator=(const Smp::Duration& source)
{
  this->ticks = source;
  return *this;
}

Smp::Mdk::Duration&
Duration::operator=(const Smp::Float64 seconds)
{
  this->ticks = seconds * NS_IN_SECOND;
  return *this;
}

Smp::Mdk::Duration
Duration::operator-(void) const
{
  return Smp::Mdk::Duration(0 - this->ticks);
}

Smp::Mdk::Duration
Duration::operator+(Smp::Mdk::Duration duration) const
{
  return Smp::Mdk::Duration(this->ticks + duration.ticks);
}

Smp::Mdk::Duration
Duration::operator-(Smp::Mdk::Duration duration) const
{
  return Smp::Mdk::Duration(this->ticks - duration.ticks);
}

void
Duration::operator+=(Smp::Mdk::Duration duration)
{
  this->ticks += duration.ticks;
}

void
Duration::operator-=(Smp::Mdk::Duration duration)
{
  this->ticks -= duration.ticks;
}

Smp::Bool
Duration::operator>(Smp::Mdk::Duration duration) const
{
  return this->ticks > duration.ticks;
}

Smp::Bool
Duration::operator<(Smp::Mdk::Duration duration) const
{
  return this->ticks < duration.ticks;
}

Smp::Bool
Duration::operator==(Smp::Mdk::Duration duration) const
{
  return this->ticks == duration.ticks;
}

Smp::Bool
Duration::operator!=(Smp::Mdk::Duration duration) const
{
  return this->ticks != duration.ticks;
}

Smp::Bool
Duration::Set(const Smp::Int32 days,
              const Smp::Int16 hours,
              const Smp::Int16 minutes,
              const Smp::Int16 seconds,
              const Smp::Int32 nanoseconds)
{
  this->ticks = days * NS_IN_DAY + hours * NS_IN_HOUR + minutes * NS_IN_MINUTE +
                seconds * NS_IN_SECOND + nanoseconds;

  return this->ticks >= 0;
}

void
Duration::Get(Smp::Int32& days,
              Smp::Int16& hours,
              Smp::Int16& minutes,
              Smp::Int16& seconds,
              Smp::Int32& nanoseconds) const
{
  Smp::Duration localTicks = this->ticks;

  if (localTicks >= NS_IN_DAY) {
    days = localTicks / NS_IN_DAY;
    localTicks -= (days * NS_IN_DAY);
  }

  if (localTicks >= NS_IN_HOUR) {
    hours = localTicks / NS_IN_HOUR;
    localTicks -= (hours * NS_IN_HOUR);
  }

  if (localTicks >= NS_IN_MINUTE) {
    minutes = localTicks / NS_IN_MINUTE;
    localTicks -= (minutes * NS_IN_MINUTE);
  }

  if (localTicks >= NS_IN_SECOND) {
    seconds = localTicks / NS_IN_SECOND;
    localTicks -= (seconds * NS_IN_SECOND);
  }

  nanoseconds = localTicks;
}

Smp::Bool
Duration::Set(const Smp::Float64 seconds)
{
  this->ticks = seconds * NS_IN_SECOND;

  return this->ticks >= 0;
}

Smp::Float64
Duration::Get(void) const
{
  Smp::Float64 ticksFloat = this->ticks;

  return ticksFloat / NS_IN_SECOND;
}

Smp::Bool
Duration::Set(const char* string)
{
  //  TODO
  return false;
}

void
Duration::Get(char* string) const
{
  //  TODO
}
