AC_INIT([SmpMdk], [0.1], [juanrgar@gmail.com], [smpmdk])
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects tar-ustar dist-xz no-dist-gzip])
AM_SILENT_RULES([true])

AC_PROG_CXX
AC_LANG(C++)
AM_PROG_AR
AC_PROG_LIBTOOL
AC_LIBTOOL_DLOPEN

PKG_CHECK_MODULES(CPPUNIT, [cppunit < 1.14.0])

LIBSMPMDK_LT_VERSION=0:0:0
AC_SUBST(LIBSMPMDK_LT_VERSION)

# For each cycle:
#  first release: increment major += 1, minor = micro = 0;
#  each release before API freeze: minor += 1;
#  each release after API freeze: micro += 1;
m4_define([libsmpmdk_major_version], [0])
m4_define([libsmpmdk_minor_version], [1])
m4_define([libsmpmdk_micro_version], [0])
m4_define([libsmpmdk_version],
          [libsmpmdk_major_version.libsmpmdk_minor_version.libsmpmdk_micro_version])

LIBSMPMDK_MAJOR_VERSION=libsmpmdk_major_version
LIBSMPMDK_MINOR_VERSION=libsmpmdk_minor_version
LIBSMPMDK_MICRO_VERSION=libsmpmdk_micro_version
LIBSMPMDK_VERSION=libsmpmdk_version

AC_SUBST(LIBSMPMDK_MAJOR_VERSION)
AC_SUBST(LIBSMPMDK_MINOR_VERSION)
AC_SUBST(LIBSMPMDK_MICRO_VERSION)
AC_SUBST(LIBSMPMDK_VERSION)

AC_CONFIG_FILES([
                 Makefile
                 src/Makefile
                 tests/Makefile
                 ])
AC_OUTPUT()

dnl ==========================================================================
echo "
SmpMdk $VERSION
=============

prefix: ${prefix}
compiler: ${CXX}
"
