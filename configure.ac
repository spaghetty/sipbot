#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([Opsip_tapi], [0.1], [spaghetty(AT)gmail.com])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
#AC_CONFIG_FILE([._bootmp/lib/Makefile])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE
# Checks for programs.
AC_PROG_CC
gl_EARLY
AC_PROG_CXX
AM_PROG_CC_C_O
AC_CONFIG_MACRO_DIR([m4])
gl_INIT

# Checks for libraries.
PKG_CHECK_MODULES(SOFIA_SIP_UA, sofia-sip-ua)
AC_SUBST(SOFIA_SIP_UA_LIBS)
AC_SUBST(SOFIA_SIP_UA_CFLAGS)
AC_SUBST(SOFIA_SIP_UA_VERSION)
AM_PROG_LIBTOOL
# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
ACX_PTHREAD

LTLIBOBJS=`echo "$LIBOBJS" | sed 's/\.o/.lo/g'`
AC_SUBST(LTLIBOBJS)
LTALLOCA=`echo "$ALLOCA" | sed 's/\.o/.lo/g'`
AC_SUBST(LTALLOCA)

AC_OUTPUT(Makefile src/Makefile examples/Makefile lib/Makefile)
