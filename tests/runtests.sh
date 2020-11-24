#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libagdb/.libs/libagdb.1.dylib && test -f ./pyagdb/.libs/pyagdb.so;
then
	install_name_tool -change /usr/local/lib/libagdb.1.dylib ${PWD}/libagdb/.libs/libagdb.1.dylib ./pyagdb/.libs/pyagdb.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

