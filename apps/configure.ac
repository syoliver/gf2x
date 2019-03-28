#  This file is part of the gf2x library.
#
#  Copyright 2007, 2008, 2009, 2010, 2013, 2014, 2015
#  Richard Brent, Pierrick Gaudry, Emmanuel Thome', Paul Zimmermann
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of either:
#   - If the archive contains a file named toom-gpl.c (not a trivial
#     placeholder), the GNU General Public License as published by the
#     Free Software Foundation; either version 3 of the License, or (at
#     your option) any later version.
#   - If the archive contains a file named toom-gpl.c which is a trivial
#     placeholder, the GNU Lesser General Public License as published by
#     the Free Software Foundation; either version 2.1 of the License, or
#     (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE.  See the license text for more details.
#  
#  You should have received a copy of the GNU General Public License as
#  well as the GNU Lesser General Public License along with this program;
#  see the files COPYING and COPYING.LIB.  If not, write to the Free
#  Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
#  02110-1301, USA.

AC_INIT([gf2x-apps], [1.3.0])

: ${CXXFLAGS=-g -O4 -std=c++11 -fopenmp}

# AC_CONFIG_AUX_DIR([config])
# AC_CONFIG_MACRO_DIR([config])
AC_CANONICAL_TARGET

AC_LANG([C])

AC_FUNC_ALLOCA

AM_INIT_AUTOMAKE([1.13])

# disable for releases: AM_MAINTAINER_MODE([disable])
AM_MAINTAINER_MODE([enable])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CC_C99
AC_PROG_CPP

PKG_PREREQ(0.29)
PKG_PROG_PKG_CONFIG(0.29)
PKG_CHECK_MODULES([GF2X], [gf2x >= 1.3.0])

# Not sure this makes sense, really. I don't like to tinker with rpath.
GF2X_RPATH_LIBS=`$PKG_CONFIG --libs-only-L gf2x 2>/dev/null | sed -e s'/^-L/-Wl,-rpath,/'`
AC_SUBST([GF2X_RPATH_LIBS])

AC_ARG_WITH([ntl],
            [AS_HELP_STRING([--with-ntl],
                 [look for NTL in this directory])],
            [],
            [with_ntl=no])
if ! test "x$with_ntl" = xno ; then
 LDFLAGS="$LDFLAGS -L$with_ntl/lib"
 CPPFLAGS="$CPPFLAGS -I$with_ntl/include"
fi

AC_CHECK_HEADER([gmp.h],[],[AC_MSG_ERROR([GMP headers not found])])
AC_CHECK_LIB([gmp], [__gmpz_init], [], [AC_MSG_ERROR([GMP library not found])])

AC_CHECK_HEADER([NTL/version.h],[],[AC_MSG_ERROR([NTL headers not found])])
AC_CHECK_LIB([ntl], [_ZN3NTL4GF2X9normalizeEv], [], [AC_MSG_ERROR([NTL library not found])])

CHECK_BMI2_SUPPORT()

AM_PROG_CC_C_O

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

# vim: set sw=1:
