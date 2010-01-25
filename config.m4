dnl $Id$
dnl config.m4 for extension notifyerror

PHP_ARG_WITH(notifyerror, for notifyerror support,
[  --with-notifyerror             Include notifyerror support])

if test "$PHP_NOTIFYERROR" != "no"; then
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/libnotify/notify.h"
  if test -r $PHP_NOTIFYERROR/$SEARCH_FOR; then
    NOTIFYERROR_DIR=$PHP_NOTIFYERROR
  else
    AC_MSG_CHECKING([for libnotify files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        NOTIFYERROR_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  
  if test -z "$NOTIFYERROR_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the libnotify distribution])
  fi

  PHP_ADD_INCLUDE($NOTIFYERROR_DIR/include)

  dnl This is aquitebad assumption, better use pkg-config:
  PHP_ADD_INCLUDE($NOTIFYERROR_DIR/include/glib-2.0)
  PHP_ADD_INCLUDE(/usr/lib/glib-2.0/include)
  PHP_ADD_INCLUDE(/usr/include/gtk-2.0)
  PHP_ADD_INCLUDE(/usr/include/cairo)
  PHP_ADD_INCLUDE(/usr/include/dbus-1.0)
  PHP_ADD_INCLUDE(/usr/include/atk-1.0)
  PHP_ADD_INCLUDE(/usr/include/pango-1.0)
  PHP_ADD_INCLUDE(/usr/lib/gtk-2.0/include/)

  LIBNAME=notify
  LIBSYMBOL=notify_init 

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $NOTIFYERROR_DIR/lib, NOTIFYERROR_SHARED_LIBADD)
    AC_DEFINE(HAVE_NOTIFYERRORLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong notifyerror lib version or lib not found])
  ],[
    -L$NOTIFYERROR_DIR/lib -lm
  ])
  
  PHP_SUBST(NOTIFYERROR_SHARED_LIBADD)

  PHP_NEW_EXTENSION(notifyerror, notifyerror.c, $ext_shared)
fi
