dnl Process this file with autoconf to produce a configure script

AC_PREREQ(2.61)
AC_INIT(Lesson_7_Autotools, 1.0)

dnl Check for required programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_LIBTOOL
AC_PROG_MKDIR_P

AC_CANONICAL_SYSTEM
AC_CONFIG_HEADERS([config.h])

dnl Initialize and use automake
AM_INIT_AUTOMAKE([foreign])

AC_SYS_LARGEFILE

dnl Check for library functions that SQLite can optionally use
AC_CHECK_FUNCS([fdatasync usleep fullfsync localtime_r gmtime_r])
AC_FUNC_STRERROR_R

dnl This allows us specify individual liking flags for each target
AM_PROG_CC_C_O 

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

dnl Enable pkg-config      
PKG_PROG_PKG_CONFIG

dnl Link with Makefile.am in source directories
AC_CONFIG_FILES(Makefile lib/Makefile src/Makefile)
                
AC_SUBST([BUILD_CFLAGS])

dnl Security xFLAGS
SECURITYFLAGS="-fstack-protector --param=ssp-buffer-size=4 -D_FORTIFY_SOURCE=2 -Wall -Wno-comment -Wformat-security"
CXXFLAGS="$CXXFLAGS $SECURITYFLAGS"
CFLAGS="$CFLAGS $SECURITYFLAGS"
LDFLAGS="$LDFLAGS -Wl,-z,relro -Wl,--hash-style=gnu"

dnl Compile with -rdynamic
LDFLAGS="$LDFLAGS -rdynamic"

dnl Do not link with unnecessary libraries
LDFLAGS="$LDFLAGS -Wl,--as-needed"

dnl Use the latest C++ standard 
CXXFLAGS="$CXXFLAGS -std=c++11"

dnl Warn of unused precompiled headers
CXXFLAGS="$CXXFLAGS -Winvalid-pch"

dnl Use the modern C standard
CFLAGS="$CFLAGS -std=c99"

AC_OUTPUT

