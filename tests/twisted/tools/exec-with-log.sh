#!/bin/sh

cd "/home/kalfa/src/telepathy-logger/tests/twisted/tools"

export TPL_DEBUG=all
ulimit -c unlimited
exec >> tpl-testing.log 2>&1

if test -n "$TPL_TEST_VALGRIND"; then
        export G_DEBUG=${G_DEBUG:+"${G_DEBUG},"}gc-friendly
        export G_SLICE=always-malloc
        export DBUS_DISABLE_MEM_POOLS=1
        TPL_WRAPPER="valgrind --leak-check=full --num-callers=20"
        TPL_WRAPPER="$TPL_WRAPPER --show-reachable=yes"
        TPL_WRAPPER="$TPL_WRAPPER --gen-suppressions=all"
        TPL_WRAPPER="$TPL_WRAPPER --child-silent-after-fork=yes"
        TPL_WRAPPER="$TPL_WRAPPER --suppressions=/home/kalfa/src/telepathy-logger/tests/suppressions/tp-glib.supp"
        TPL_WRAPPER="$TPL_WRAPPER --suppressions=/home/kalfa/src/telepathy-logger/tests/suppressions/tpl.supp"
elif test -n "$TPL_TEST_REFDBG"; then
        if test -z "$REFDBG_OPTIONS" ; then
                export REFDBG_OPTIONS="btnum=10"
        fi
        if test -z "$TPL_WRAPPER" ; then
                TPL_WRAPPER="refdbg"
        fi
elif test -n "$TPL_TEST_STRACE"; then
        TPL_WRAPPER="strace -o strace.log"
fi

export G_DEBUG=fatal-warnings,fatal-criticals" ${G_DEBUG}"
exec /home/kalfa/src/telepathy-logger/libtool --mode=execute $TPL_WRAPPER ../telepathy-tpl-debug
