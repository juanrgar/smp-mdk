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

#include <cppunit/ui/text/TestRunner.h>

#include "ArrayTest.h"
#include "CompositeTest.h"
#include "ContainerTest.h"
#include "EntryPointTest.h"
#include "EventsTest.h"
#include "ManagedContainerTest.h"
#include "ManagedReferenceTest.h"
#include "ModelTest.h"
#include "ObjectTest.h"
#include "ReferenceTest.h"
#include "RequestTest.h"
#include "StringTest.h"
#include "UuidTest.h"

int
main(int argc, char* argv[])
{
  ::CppUnit::TextUi::TestRunner runner;

  runner.addTest(ObjectTest::suite());
  runner.addTest(ModelTest::suite());
  runner.addTest(EntryPointTest::suite());
  runner.addTest(EventsTest::suite());
  runner.addTest(UuidTest::suite());
  runner.addTest(ArrayTest::suite());
  runner.addTest(StringTest::suite());
  runner.addTest(ReferenceTest::suite());
  runner.addTest(ContainerTest::suite());
  runner.addTest(CompositeTest::suite());
  runner.addTest(RequestTest::suite());
  runner.addTest(ManagedContainerTest::suite());
  runner.addTest(ManagedReferenceTest::suite());
  bool testResult = runner.run();

  return testResult ? 0 : 1;
}
