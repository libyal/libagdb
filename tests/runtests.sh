#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libagdb/.libs/libagdb.1.dylib && test -f ./pyagdb/.libs/pyagdb.so
then
	install_name_tool -change /usr/local/lib/libagdb.1.dylib ${PWD}/libagdb/.libs/libagdb.1.dylib ./pyagdb/.libs/pyagdb.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

