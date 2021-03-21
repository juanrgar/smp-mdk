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

#ifndef MDK_DATETIME_H_
#define MDK_DATETIME_H_

#include "Smp/Exceptions.h"
#include "Smp/SimpleTypes.h"

namespace Smp {
namespace Mdk {
struct DateTime
{
  Smp::DateTime ticks;

  DateTime(void);
  //            DateTime(
  //                    const Smp::DateTime& source);
  //            DateTime(
  //                    const Smp::Float64 days);
  //            DateTime(
  //                    const Smp::Int16 year,
  //                    const Smp::Int16 month,
  //                    const Smp::Int16 day,
  //                    const Smp::Int16 hours,
  //                    const Smp::Int16 minutes,
  //                    const Smp::Int16 seconds,
  //                    const Smp::Int32 nanoseconds = 0);
  //            DateTime(
  //                    const char* string);
  //
  //            Smp::Mdk::DateTime& operator= (
  //                    const Smp::DateTime& source);
  //            Smp::Mdk::DateTime& operator= (
  //                    const Smp::Float64 days);
  //            Smp::Mdk::Duration operator- (
  //                    Smp::Mdk::DateTime dateTime) const;
  //            Smp::Mdk::DateTime operator+ (
  //                    Smp::Mdk::Duration duration) const;
  //            Smp::Mdk::DateTime operator- (
  //                    Smp::Mdk::Duration duration) const;
  //            void operator+= (
  //                    Smp::Mdk::Duration duration);
  //            void operator-= (
  //                    Smp::Mdk::Duration duration);
  //            bool operator> (
  //                    Smp::Mdk::DateTime dateTime) const;
  //            bool operator< (
  //                    Smp::Mdk::DateTime dateTime) const;
  //            bool operator== (
  //                    Smp::Mdk::DateTime dateTime) const;
  //            bool operator!= (
  //                    Smp::Mdk::DateTime dateTime) const;
  //
  //            Smp::Bool Set(
  //                    const Smp::Int16 year,
  //                    const Smp::Int16 month,
  //                    const Smp::Int16 day,
  //                    const Smp::Int16 hours,
  //                    const Smp::Int16 minutes,
  //                    const Smp::Int16 seconds,
  //                    const Smp::Int32 nanoseconds = 0);
  //            void Get(
  //                    Smp::Int16& year,
  //                    Smp::Int16& month,
  //                    Smp::Int16& day,
  //                    Smp::Int16& hours,
  //                    Smp::Int16& minutes,
  //                    Smp::Int16& seconds,
  //                    Smp::Int32& nanoseconds) const;
  //            Smp::Bool Set(
  //                    const Smp::Float64 days);
  //            Smp::Float64 Get(void) const;
  //            Smp::Bool Set(
  //                    const char* string);
  //            void Get(
  //                    char* string) const;
  //
  //            static Smp::Bool IsLeapYear(
  //                    Smp::Int32 year);
};
} // namespace Mdk
} // namespace Smp

#endif // MDK_DATETIME_H_
