AC_INIT([cairomm], [1.8.2], [cairo@cairographics.org], [cairomm])
AC_PREREQ([2.62])

AC_CONFIG_SRCDIR([cairomm/cairomm.h])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([cairomm/cairommconfig.h])

AM_INIT_AUTOMAKE([1.10 -Wno-portability no-define nostdinc tar-pax])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

MM_INIT_MODULE([cairomm-1.0], m4_expand([AC_PACKAGE_VERSION]))

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([CAIROMM_SO_VERSION], [5:0:4])

AC_PROG_CXX
AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

AC_SUBST([CAIROMM_MODULES], ['cairo >= 1.8.0 sigc++-2.0'])
PKG_CHECK_MODULES([CAIROMM], [$CAIROMM_MODULES])

MM_ARG_ENABLE_DOCUMENTATION
MM_ARG_WITH_TAGFILE_DOC([libstdc++.tag], [mm-common-libstdc++])
MM_ARG_WITH_TAGFILE_DOC([libsigc++-2.0.tag], [sigc++-2.0])

AC_LANG([C++])
MM_ARG_ENABLE_WARNINGS([CAIROMM_WXXFLAGS],
                       [-Wall],
                       [-Wall -g -Wextra])

AC_CONFIG_FILES([Makefile
                 cairomm/Makefile
                 data/Makefile
                 data/cairomm-1.0.pc
                 docs/Makefile
                 docs/reference/Doxyfile
                 examples/Makefile
                 tests/Makefile])

AC_PROG_CXX
AC_PROG_CXXCPP
AC_LANG_CPLUSPLUS
AC_PROG_INSTALL
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL

# Ensure MSVC-compatible struct packing convention is used when
# compiling for Win32 with gcc.
# What flag to depends on gcc version: gcc3 uses "-mms-bitfields", while
# gcc2 uses "-fnative-struct".
# TODO: Disabled for now. I don't think this should be enabled by the
# libraries themselves on behalf of the user. That makes no sense as
# it is a platform-wide ABI choice.

AC_CHECK_HEADERS(string list map, , exit)
dnl some platforms (e.g. Solaris) need additional C headers included so
dnl that there are always prototypes and defines available.
AC_CHECK_HEADERS(math.h)

########################
# Determine Dependencies
########################
dnl always install the 'base' pkg-config file
INSTALLED_PC="cairomm-1.0.pc"

dnl then check and add additional dependencies
PKG_CHECK_MODULES(CAIROFT, cairo-ft, [HAS_FT=yes], [HAS_FT=no])
if test x$HAS_FT = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-ft-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-ft"
fi

PKG_CHECK_MODULES(CAIROPDF, cairo-pdf, [HAS_PDF=yes], [HAS_PDF=no])
if test x$HAS_PDF = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-pdf-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-pdf"
fi

PKG_CHECK_MODULES(CAIROPNG, cairo-png, [HAS_PNG=yes], [HAS_PNG=no])
if test x$HAS_PNG = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-png-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-png"
fi

PKG_CHECK_MODULES(CAIROPS, cairo-ps, [HAS_PS=yes], [HAS_PS=no])
if test x$HAS_PS = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-ps-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-ps"
fi

PKG_CHECK_MODULES(CAIROSVG, cairo-svg, [HAS_SVG=yes], [HAS_SVG=no])
if test x$HAS_SVG = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-svg-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-svg"
fi

PKG_CHECK_MODULES(CAIROXLIB, cairo-xlib, [HAS_XLIB=yes], [HAS_XLIB=no])
if test x$HAS_XLIB = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-xlib-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-xlib"
fi

PKG_CHECK_MODULES(CAIROXLIBXRENDER, cairo-xlib-xrender, [HAS_XLIBXRENDER=yes], [HAS_XLIBXRENDER=no])
if test x$HAS_XLIBXRENDER = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-xlib-xrender-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-xlib-xrender"
fi

PKG_CHECK_MODULES(CAIROWIN32, cairo-win32, [HAS_WIN32=yes], [HAS_WIN32=no])
if test x$HAS_WIN32 = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-win32-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-win32"
fi

PKG_CHECK_MODULES(CAIROWIN32FONT, cairo-win32-font, [HAS_WIN32FONT=yes], [HAS_WIN32FONT=no])
if test x$HAS_WIN32FONT = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-win32-font-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-win32-font"
fi

PKG_CHECK_MODULES(CAIROQUARTZ, cairo-quartz, [HAS_QUARTZ=yes], [HAS_QUARTZ=no])
if test x$HAS_QUARTZ = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-quartz-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-quartz"
fi

PKG_CHECK_MODULES(CAIROQUARTZFONT, cairo-quartz-font, [HAS_QUARTZFONT=yes], [HAS_QUARTZFONT=no])
if test x$HAS_QUARTZFONT = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-quartz-font-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-quartz-font"
fi

PKG_CHECK_MODULES(CAIROQUARTZIMAGE, cairo-quartz-image, [HAS_QUARTZIMAGE=yes], [HAS_QUARTZIMAGE=no])
if test x$HAS_QUARTZIMAGE = xyes; then
  INSTALLED_PC="$INSTALLED_PC cairomm-quartz-image-1.0.pc"
  DEPS_PC="$DEPS_PC cairo-quartz-image"
fi

PKG_CHECK_MODULES(CAIROMM, [$DEPS_PC])

AC_SUBST(INSTALLED_PC)

CONFIG_PC=""
for pc in $INSTALLED_PC; do
  CONFIG_PC="$CONFIG_PC data/$pc"
done


AC_ARG_ENABLE(tests,
              AC_HELP_STRING([--enable-tests=yes|no],
                             [enable automated tests (default is no)]),
              ENABLE_TESTS=$enableval,
              ENABLE_TESTS=auto)

if test x$ENABLE_TESTS = xauto ; then
    dnl unless explicitly disabled, attempt to enable tests for developers and
    dnl disable it for others
    if test x$CAIROMM_DEVEL = xon ; then
        ENABLE_TESTS=yes
    else
        ENABLE_TESTS=no
    fi
fi

if test x$ENABLE_TESTS = xyes ; then
#######################################################
#boost build system sucks no end.
#it is damn hard to detect the version of boost
#that is installed. All that because our friends of
#the boost project don't want to integrate to autofoo.
#So we resort to hugly hacks to detect the version of
#boost that is installed.
#######################################################
    AX_BOOST_BASE([1.33.1])
    AX_BOOST_UNIT_TEST_FRAMEWORK

    dnl AX_BOOST_BASE defines a --with-boost[=DIR] option that sets
    dnl $ac_boost_path as a custom boost prefix, so use that if it was specified
    if test x$ac_boost_path != x; then
        unit_framework_lib_candidates="$ac_boost_path/lib/libboost_unit_test_framework.a
        $ac_boost_path/lib/libboost_unit_test_framework-st.a
        $ac_boost_path/libboost_unit_test_framework.a
        $ac_boost_path/libboost_unit_test_framework-st.a"
    else
        unit_framework_lib_candidates="/usr/lib/libboost_unit_test_framework-st.a
        /usr/lib/libboost_unit_test_framework.a
        /usr/lib64/libboost_unit_test_framework-st.a
        /usr/lib64/libboost_unit_test_framework.a"
    fi
    for i in $unit_framework_lib_candidates ; do
        if test -f $i ; then
            BOOST_UNIT_TEST_FRAMEWORK_STATIC_LIB=$i
            break
        fi
    done
    if test x$BOOST_UNIT_TEST_FRAMEWORK_STATIC_LIB != x; then
        AC_SUBST(BOOST_UNIT_TEST_FRAMEWORK_STATIC_LIB)
        AC_MSG_NOTICE(support of automated tests enabled)
    else
        AC_MSG_ERROR([Tried to enable unit tests, but couldn't find Boost Unit Test framework static library candidate.  You can specify a custom location using --with-boost=/path/to/lib])
    fi
else
    AC_MSG_NOTICE(disabled support of automated tests)
fi
AM_CONDITIONAL(AUTOTESTS, test x$ENABLE_TESTS = xyes)

CAIROMM_ARG_ENABLE_API_EXCEPTIONS

AC_CONFIG_FILES([
  $CONFIG_PC
  MSVC_Net2005/Makefile
    MSVC_Net2005/gendef/Makefile
    MSVC_Net2005/cairomm/Makefile
    MSVC_Net2005/cairomm/cairomm.rc
    MSVC_Net2005/examples/Makefile
      MSVC_Net2005/examples/pdf-surface/Makefile
      MSVC_Net2005/examples/ps-surface/Makefile
      MSVC_Net2005/examples/svg-surface/Makefile
      MSVC_Net2005/examples/image-surface/Makefile
      MSVC_Net2005/examples/text-rotate/Makefile
      MSVC_Net2005/examples/toy-text/Makefile
      MSVC_Net2005/examples/user-font/Makefile
  MSVC_Net2008/Makefile
    MSVC_Net2008/gendef/Makefile
    MSVC_Net2008/cairomm/Makefile
    MSVC_Net2008/cairomm/cairomm.rc
    MSVC_Net2008/examples/Makefile
      MSVC_Net2008/examples/pdf-surface/Makefile
      MSVC_Net2008/examples/ps-surface/Makefile
      MSVC_Net2008/examples/svg-surface/Makefile
      MSVC_Net2008/examples/image-surface/Makefile
      MSVC_Net2008/examples/text-rotate/Makefile
      MSVC_Net2008/examples/toy-text/Makefile
      MSVC_Net2008/examples/user-font/Makefile
])

AC_OUTPUT
