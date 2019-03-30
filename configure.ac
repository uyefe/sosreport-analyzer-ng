# configure.ac - process this file with autoconf to produce configure
#
# Copyright (C) 2018-2019 Shintaro Fujiwara 
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301 USA

AC_PREREQ([2.69])
AC_COPYRIGHT(
[Copyright (C) 2018-2019 Shintaro Fujiwara 

This configure script is derived from configure.ac which is free software;
you can redistribute it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version. See the
configure.ac file for more details.])

# initialize and set version and bugreport address
AC_INIT([sosreport-analyzer], [1.0.91], [shintaro.fujiwara@gmail.com])
RELEASE_MONTH="Mar 2019"
AC_SUBST(RELEASE_MONTH)
AC_CONFIG_MACRO_DIR([m4])

# display notice and initialize automake
AC_MSG_NOTICE([configuring AC_PACKAGE_TARNAME AC_PACKAGE_VERSION])
AM_INIT_AUTOMAKE([1.11.2 --warnings=all])
AC_CONFIG_SRCDIR([main.c])

# create a config.h file (Automake will add -DHAVE_CONFIG_H)
#AC_CONFIG_HEADERS([config.h])

# check locale
LOCALE_THIS=`locale | grep LANG | cut -d= -f2`

# conditional behaivor
AM_CONDITIONAL(LANG_JP, test `locale | grep LANG | cut -d= -f2` = "ja_JP.UTF-8")

# check for programs
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AM_PROG_CC_C_O
AC_USE_SYSTEM_EXTENSIONS
AC_PROG_LN_S
AM_PROG_AR

LT_INIT

AC_ENABLE_SHARED
AC_DISABLE_STATIC
AC_PROG_LIBTOOL(libtool)

# check for debugging options
AC_ARG_ENABLE(debug,
              AS_HELP_STRING([--enable-debug],
                             [enable extensive debugging and logging]),
              [if test "x$enableval" != "xno" ; then CFLAGS="-g -DDEBUG $CFLAGS" ; fi])

# check for extra compiler warnings
DESIRED_CFLAGS="-Wall"
AC_ARG_ENABLE(warnings,
              AS_HELP_STRING([--enable-warnings],
                             [enable extra compiler warnings (gcc)]),
              [if test "x$enableval" != "no"
               then
                 CFLAGS="$CFLAGS -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs -Waggregate-return -Wmissing-declarations -Wunused -Wformat=2 -Wswitch-default -Wswitch-enum -Wfloat-equal -Wbad-function-cast -Wredundant-decls"
                 DESIRED_CFLAGS="$DESIRED_CFLAGS -Wextra -Wdeclaration-after-statement -Werror-implicit-function-declaration -Werror=implicit"
               fi])
test_gcc_flag() {
    AC_LANG_CONFTEST([AC_LANG_PROGRAM()])
    $CC -c conftest.c $CFLAGS $@ > /dev/null 2> /dev/null
    ret=$?
    rm -f conftest.o
    return $ret
}
for flag in $DESIRED_CFLAGS
do
    AC_MSG_CHECKING([whether $CC accepts $flag])
    if test_gcc_flag $flag
    then
        CFLAGS="$CFLAGS $flag"
        AC_MSG_RESULT([yes])
    else
        AC_MSG_RESULT([no])
    fi
done

# checks for availability of header files

AC_CHECK_HEADERS([stdlib.h stdio.h string.h time.h dirent.h errno.h ctype.h math.h sys/stat.h fcntl.h limits.h getopt.h])

# other general checks
AC_C_INLINE
AC_C_CONST

# checks for availability of common functions
AC_CHECK_FUNCS([sigaction snprintf])
AC_SEARCH_LIBS(socket, socket)
AC_CHECK_FUNCS([strcasecmp strncasecmp strchr strcspn strspn strtol strtoul strtoull strndup])
AC_CHECK_FUNCS([malloc realloc atexit])
AC_FUNC_FORK
AC_CHECK_FUNCS(__assert_fail)
AC_SEARCH_LIBS(clock_gettime, rt)
AC_CHECK_FUNCS([setusershell getusershell endusershell getgrouplist])
AC_CHECK_DECLS([setusershell, getusershell, endusershell])

# check the name of the sosreport-analyzer configuration file
AC_ARG_WITH(sosreport-analyzer-conf-file,
            AS_HELP_STRING([--with-sosreport-analyzer-conf-file=PATH],
                           [path to sosreport-analyzer configuration file @<:@/etc/sosreport-analyzer.conf@:>@]),
            [ SOSREPORT_ANALYZER_CONF_PATH="$with_sosreport_analyzer_conf_file" ],
            [ SOSREPORT_ANALYZER_CONF_PATH="/etc/sosreport-analyzer.conf" ])
AC_DEFINE_UNQUOTED(SOSREPORT_ANALYZER_CONF_PATH, "$SOSREPORT_ANALYZER_CONF_PATH", [Path to sosreport-analyzer configuration file.])
AC_SUBST(SOSREPORT_ANALYZER_CONF_PATH)

# check the name of the sosreport-analyzer-mcinfo configuration file
AC_ARG_WITH(sosreport-analyzer-mcinfo-conf-file,
            AS_HELP_STRING([--with-sosreport-analyzer-mcinfo-conf-file=PATH],
                           [path to sosreport-analyzer-mcinfo configuration file @<:@/etc/sosreport-analyzer-mcinfo.conf@:>@]),
            [ SOSREPORT_ANALYZER_MCINFO_CONF_PATH="$with_sosreport_analyzer_mcinfo_conf_file" ],
            [ SOSREPORT_ANALYZER_MCINFO_CONF_PATH="/etc/sosreport-analyzer-mcinfo.conf" ])
AC_DEFINE_UNQUOTED(SOSREPORT_ANALYZER_MCINFO_CONF_PATH, "$SOSREPORT_ANALYZER_MCINFO_CONF_PATH", [Path to sosreport-analyzer-mcinfo configuration file.])
AC_SUBST(SOSREPORT_ANALYZER_MCINFO_CONF_PATH)

# check the name of the data file
AC_ARG_WITH(sosreport-analyzer-data-file,
            AS_HELP_STRING([--with-sosreport-analyzer-data-file=PATH],
                           [path to sosreport-analyzer data file @<:@/usr/share/sosreport-analyzer/sosreport-analyzer.conf.example@:>@]),
            [ SOSREPORT_ANALYZER_DATA_PATH="$with_sosreport_analyzer_data_file" ],
            [ SOSREPORT_ANALYZER_DATA_PATH="/usr/share/sosreport-analyzer" ])
AC_DEFINE_UNQUOTED(SOSREPORT_ANALYZER_DATA_PATH, "$SOSREPORT_ANALYZER_DATA_PATH", [Path to sosreport-analyzer data file.])
AC_SUBST(SOSREPORT_ANALYZER_DATA_PATH)

# check the name of the include/sosreport-analyzer file
AC_ARG_WITH(sosreport-analyzerd-include-file,
            AS_HELP_STRING([--with-sosreport-analyzer-include-file=PATH],
                           [path to sosreport-analyzer include file @<:@/usr/local/include/sosreport-analyzer/cfg.h@:>@]),
            [ SOSREPORT_ANALYZER_INCLUDE_PATH="$with_sosreport_analyzer_include_file" ],
            [ SOSREPORT_ANALYZER_INCLUDE_PATH="/usr/local/include/sosreport-analyzer" ])
AC_DEFINE_UNQUOTED(SOSREPORT_ANALYZER_INCLUDE_PATH, "$SOSREPORT_ANALYZER_INCLUDE_PATH", [Path to sosreport-analyzer include file.])
AC_SUBST(SOSREPORT_ANALYZER_INCLUDE_PATH)

# check the name of the libsosreport-analyzer file
AC_ARG_WITH(sosreport-analyzer-lib-file,
            AS_HELP_STRING([--with-sosreport-analyzer-lib-file=PATH],
                           [path to sosreport-analyzer lib file @<:@/usr/local/lib/libsosreport-analyzer.so@:>@]),
            [ SOSREPORT_ANALYZER_LIB_PATH="$with_sosreport_analyzer_lib_file" ],
            [ SOSREPORT_ANALYZER_LIB_PATH="/usr/local/lib" ])
AC_DEFINE_UNQUOTED(SOSREPORT_ANALYZER_LIB_PATH, "$SOSREPORT_ANALYZER_LIB_PATH", [Path to sosreport-analyzer lib file.])
AC_SUBST(SOSREPORT_ANALYZER_LIB_PATH)

# check the name of the libsar-analyzer file
AC_ARG_WITH(sar-analyzerd-lib-file,
            AS_HELP_STRING([--with-sar-analyzer-lib-file=PATH],
                           [path to sar-analyzer lib file @<:@/usr/local/lib/libsar-analyzer.so@:>@]),
            [ SAR_ANALYZER_LIB_PATH="$with_sar_analyzer_lib_file" ],
            [ SAR_ANALYZER_LIB_PATH="/usr/local/lib" ])
AC_DEFINE_UNQUOTED(SAR_ANALYZER_LIB_PATH, "$SAR_ANALYZER_LIB_PATH", [Path to sar-analyzer lib file.])
AC_SUBST(SAR_ANALYZER_LIB_PATH)

AC_CONFIG_FILES([
  Makefile
  libsosreport-analyzer/Makefile
  libsar-analyzer/Makefile
])
AC_OUTPUT
