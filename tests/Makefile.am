TESTS = smp_sdk_tests
check_PROGRAMS = smp_sdk_tests
smp_sdk_tests_SOURCES = \
						TestRunner.cpp \
						ObjectTest.cpp \
						ComponentTest.cpp \
						ModelTest.cpp \
						EntryPointTest.cpp \
						EventSinkTest.cpp \
						EventsTest.cpp \
						UuidTest.cpp \
						ArrayTest.cpp \
						StringTest.cpp \
						ReferenceTest.cpp \
						ContainerTest.cpp \
						CompositeTest.cpp \
						RequestTest.cpp \
						ManagedContainerTest.cpp \
						ManagedReferenceTest.cpp
smp_sdk_tests_CXXFLAGS = $(CPPUNIT_CFLAGS) -I$(top_srcdir)/src -std=c++98
smp_sdk_tests_LDADD = $(CPPUNIT_LIBS) $(top_builddir)/src/libsmpmdk.la -ldl
