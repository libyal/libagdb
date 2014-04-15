dnl Function to detect if libagdb dependencies are available
AC_DEFUN([AX_LIBAGDB_CHECK_LOCAL],
 [dnl Check for internationalization functions in libagdb/libagdb_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

