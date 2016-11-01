AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBAGDB_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_agdbinfo.sh

check_SCRIPTS = \
	test_agdbinfo.sh \
	test_api_functions.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	agdb_test_error \
	agdb_test_open_close \
	agdb_test_support

agdb_test_error_SOURCES = \
	agdb_test_error.c \
	agdb_test_libagdb.h \
	agdb_test_libcstring.h \
	agdb_test_macros.h \
	agdb_test_unused.h

agdb_test_error_LDADD = \
	../libagdb/libagdb.la \
	@LIBCSTRING_LIBADD@

agdb_test_open_close_SOURCES = \
	agdb_test_libcerror.h \
	agdb_test_libagdb.h \
	agdb_test_libcstring.h \
	agdb_test_libcsystem.h \
	agdb_test_open_close.c

agdb_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

agdb_test_support_SOURCES = \
	agdb_test_libagdb.h \
	agdb_test_libcstring.h \
	agdb_test_macros.h \
	agdb_test_support.c \
	agdb_test_unused.h

agdb_test_support_LDADD = \
	../libagdb/libagdb.la \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

