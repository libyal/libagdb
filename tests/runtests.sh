#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libagdb/.libs/libagdb.1.dylib" ] && [ -f ./pyagdb/.libs/pyagdb.so ]
then
    install_name_tool -change /usr/local/lib/libagdb.1.dylib "${PWD}/libagdb/.libs/libagdb.1.dylib" ./pyagdb/.libs/pyagdb.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

