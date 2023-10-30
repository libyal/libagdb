AUTOMAKE_OPTIONS = subdir-objects

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
	@PTHREAD_CPPFLAGS@ \
	@LIBAGDB_DLL_IMPORT@

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_agdbinfo.sh

check_SCRIPTS = \
	test_agdbinfo.sh \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh \
	test_tools.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	agdb_test_compressed_block \
	agdb_test_compressed_blocks_stream_data_handle \
	agdb_test_compressed_file_header \
	agdb_test_error \
	agdb_test_file \
	agdb_test_file_information \
	agdb_test_io_handle \
	agdb_test_notify \
	agdb_test_source_information \
	agdb_test_support \
	agdb_test_tools_info_handle \
	agdb_test_tools_output \
	agdb_test_tools_signal \
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

agdb_test_compressed_file_header_SOURCES = \
	agdb_test_compressed_file_header.c \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h

agdb_test_compressed_file_header_LDADD = \
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
	agdb_test_functions.c agdb_test_functions.h \
	agdb_test_getopt.c agdb_test_getopt.h \
	agdb_test_libagdb.h \
	agdb_test_libbfio.h \
	agdb_test_libcerror.h \
	agdb_test_libclocale.h \
	agdb_test_libcnotify.h \
	agdb_test_libuna.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h

agdb_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libagdb/libagdb.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

agdb_test_file_information_SOURCES = \
	agdb_test_file_information.c \
	agdb_test_functions.c agdb_test_functions.h \
	agdb_test_libbfio.h \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_libfdata.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h

agdb_test_file_information_LDADD = \
	@LIBFDATA_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
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
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_notify.c \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h

agdb_test_notify_LDADD = \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

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
	agdb_test_functions.c agdb_test_functions.h \
	agdb_test_getopt.c agdb_test_getopt.h \
	agdb_test_libagdb.h \
	agdb_test_libbfio.h \
	agdb_test_libcerror.h \
	agdb_test_libclocale.h \
	agdb_test_libcnotify.h \
	agdb_test_libuna.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_support.c \
	agdb_test_unused.h

agdb_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_tools_info_handle_SOURCES = \
	../agdbtools/agdbinput.c ../agdbtools/agdbinput.h \
	../agdbtools/info_handle.c ../agdbtools/info_handle.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_tools_info_handle.c \
	agdb_test_unused.h

agdb_test_tools_info_handle_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_tools_output_SOURCES = \
	../agdbtools/agdbtools_output.c ../agdbtools/agdbtools_output.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_tools_output.c \
	agdb_test_unused.h

agdb_test_tools_output_LDADD = \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_tools_signal_SOURCES = \
	../agdbtools/agdbtools_signal.c ../agdbtools/agdbtools_signal.h \
	agdb_test_libcerror.h \
	agdb_test_macros.h \
	agdb_test_tools_signal.c \
	agdb_test_unused.h

agdb_test_tools_signal_LDADD = \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

agdb_test_volume_information_SOURCES = \
	agdb_test_functions.c agdb_test_functions.h \
	agdb_test_libbfio.h \
	agdb_test_libagdb.h \
	agdb_test_libcerror.h \
	agdb_test_libfdata.h \
	agdb_test_macros.h \
	agdb_test_memory.c agdb_test_memory.h \
	agdb_test_unused.h \
	agdb_test_volume_information.c

agdb_test_volume_information_LDADD = \
	@LIBFDATA_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libagdb/libagdb.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

