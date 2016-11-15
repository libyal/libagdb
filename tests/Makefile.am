AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBAGDB_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_agdbinfo.sh

check_SCRIPTS = \
	test_agdbinfo.sh \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	agdb_test_compressed_block \
	agdb_test_compressed_blocks_stream_data_handle \
	agdb_test_error \
	agdb_test_file \
	agdb_test_file_information \
	agdb_test_io_handle \
	agdb_test_notify \
	agdb_test_source_information \
	agdb_test_support \
	agdb_test_volume_information

agdb_test_compressed_block_SOURCES = \
	agdb_test_compressed_block.c \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h

agdb_test_compressed_block_LDADD = \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_compressed_blocks_stream_data_handle_SOURCES = \
	agdb_test_compressed_blocks_stream_data_handle.c \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h

agdb_test_compressed_blocks_stream_data_handle_LDADD = \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_error_SOURCES = \
	agdb_test_error.c \
	agdb_test_libagdb.h \
	agdb_test_macros.h \
	agdb_test_unused.h

agdb_test_error_LDADD = \
	../libagdb/libagdb.la

agdb_test_file_SOURCES = \
	agdb_test_file.c \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_libclocale.h \
	agdb_test_libcsystem.h \
	agdb_test_libuna.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h

agdb_test_file_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libagdb/libagdb.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

agdb_test_file_information_SOURCES = \
	agdb_test_file_information.c \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h

agdb_test_file_information_LDADD = \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_io_handle_SOURCES = \
	agdb_test_io_handle.c \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h

agdb_test_io_handle_LDADD = \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_notify_SOURCES = \
	agdb_test_libagdb.h \
	agdb_test_macros.h \
	agdb_test_notify.c \
	agdb_test_unused.h

agdb_test_notify_LDADD = \
	../libagdb/libagdb.la

agdb_test_source_information_SOURCES = \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_source_information.c \
	agdb_test_unused.h

agdb_test_source_information_LDADD = \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_support_SOURCES = \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_libclocale.h \
	agdb_test_libcsystem.h \
	agdb_test_libuna.h \
	agdb_test_macros.h \
	agdb_test_support.c

agdb_test_support_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_volume_information_SOURCES = \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h \
	agdb_test_volume_information.c

agdb_test_volume_information_LDADD = \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

