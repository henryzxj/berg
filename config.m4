dnl $Id$
dnl config.m4 for extension berg

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(berg, for berg support,
dnl Make sure that the comment is aligned:
dnl [  --with-berg             Include berg support])

dnl Otherwise use enable:

 PHP_ARG_ENABLE(berg, whether to enable berg support,
 Make sure that the comment is aligned:
 [  --enable-berg           Enable berg support])
 
PHP_ARG_ENABLE(berg-debug, for berg debug support,
    [ --enable-berg-debug       Enable enable berg debug support], no, no)

if test "$PHP_BERG" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-berg -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/berg.h"  # you most likely want to change this
  dnl if test -r $PHP_BERG/$SEARCH_FOR; then # path given as parameter
  dnl   BERG_DIR=$PHP_BERG
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for berg files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       BERG_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$BERG_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the berg distribution])
  dnl fi

  dnl # --with-berg -> add include path
  dnl PHP_ADD_INCLUDE($BERG_DIR/include)

  dnl # --with-berg -> check for lib and symbol presence
  dnl LIBNAME=berg # you may want to change this
  dnl LIBSYMBOL=berg # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BERG_DIR/$PHP_LIBDIR, BERG_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_BERGLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong berg lib version or lib not found])
  dnl ],[
  dnl   -L$BERG_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(BERG_SHARED_LIBADD)
   if test "$PHP_BERG_DEBUG" != "no"; then
         CFLAGS="$CFLAGS -Wall -g -ggdb -O0 -DPHP_BERG_DEBUG=1"
         AC_DEFINE(PHP_berg_DEBUG, 1, [Enable berg debug support])
   else
         CFLAGS="$CFLAGS -Wall -g -ggdb -O0 -Wunused-variable -Wpointer-sign -Wimplicit-function-declaration -Winline -Wunused-macros -Wredundant-decls -Wstrict-aliasing=2 -Wswitch-enum -Wdeclaration-after-statement"
   fi
  PHP_PROTOBUF_SRCS="berg.c"
  PHP_NEW_EXTENSION(berg, $PHP_PROTOBUF_SRCS, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
