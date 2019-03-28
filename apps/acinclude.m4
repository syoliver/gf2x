
AC_DEFUN([BMI2_EXAMPLE],[AC_LANG_SOURCE([
#include <x86intrin.h> /* for _pdep_u64 */
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char * argv[[]]) {
    volatile uint64_t a = UINT64_C(0x3456789012391873);
    volatile uint64_t b = UINT64_C(0xe92183172937191e);
    a = _pdep_u64 (a, UINT64_C(0x5555555555555555));
    b = _pdep_u64 (b, UINT64_C(0xaaaaaaaaaaaaaaaa));
    volatile uint64_t c = a ^ b;
    return c == UINT64_C(0x9860f6b03c217ad) ? EXIT_SUCCESS : EXIT_FAILURE;
}
])])

# Check whether we need some flag such as -mbmi2 in order to enable bmi2
# support
AC_DEFUN([CHECK_BMI2_SUPPORT],[
 ac_save_CFLAGS=$CFLAGS
 AC_CACHE_CHECK([whether $CC can compile and run bmi2 code], [gf2x_cv_cc_supports_bmi2],[
  gf2x_cv_cc_supports_bmi2=no
  if test "x${enable_bmi2}" = xno ; then
   echo $ECHO_N "explicitly disabled, "
  else
   CFLAGS="$ac_save_CFLAGS -mbmi2"
   AC_RUN_IFELSE([BMI2_EXAMPLE()],[
    gf2x_cv_cc_supports_bmi2=yes
   ],[
    CFLAGS="$ac_save_CFLAGS"
    AC_RUN_IFELSE([BMI2_EXAMPLE()],[
     gf2x_cv_cc_supports_bmi2="yes, but without -mbmi2"
    ],[
     gf2x_cv_cc_supports_bmi2=no
    ])
   ],[
   echo $ECHO_N "cross-compiling, "
   if test "x${enable_bmi2}" = xyes ; then
    echo $ECHO_N "explicitly enabled, "
    gf2x_cv_cc_supports_bmi2=yes
   else
    gf2x_cv_cc_supports_bmi2=no
   fi
   ])
  fi
 ])
 ac_save_CPPFLAGS=$CPPFLAGS
 if test "$gf2x_cv_cc_supports_bmi2" = "yes" ;then
  # Tweaking CFLAGS is often not enough.
  AC_CACHE_CHECK([whether -mbmi2 is also understood by the preprocessor],
   [gf2x_cv_cpp_understands_mbmi2_flag],[
   CPPFLAGS="$ac_save_CPPFLAGS -mbmi2"
   AC_PREPROC_IFELSE([BMI2_EXAMPLE()],[
    gf2x_cv_cpp_understands_mbmi2_flag=yes
   ],[
    CPPFLAGS="$ac_save_CPPFLAGS"
    AC_PREPROC_IFELSE([BMI2_EXAMPLE()],[
    gf2x_cv_cpp_understands_mbmi2_flag=no
    ],[
     AC_MSG_ERROR([Sorry, the preprocessor can't parse bmi2!])
    ])
   ])
  ])
 fi
 CFLAGS=$ac_save_CFLAGS
 CPPFLAGS=$ac_save_CPPFLAGS
 if test "$gf2x_cv_cc_supports_bmi2" = "yes" ;then
  CFLAGS="$CFLAGS -mbmi2"
 fi
 if test "$gf2x_cv_cpp_understands_mbmi2_flag" = "yes" ; then
  CPPFLAGS="$CPPFLAGS -mbmi2"
 fi
 if test "$gf2x_cv_cc_supports_bmi2" != "no" ;then
  AC_DEFINE([GF2X_HAVE_BMI2_SUPPORT],[1],[Define if bmi2 code as present in the source tree is supported by the compiler])
 fi
])# CHECK_BMI2_SUPPORT

