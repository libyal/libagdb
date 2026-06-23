AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

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
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libagdb.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libagdb

test_inputs_agdbinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) agdbinfo

test_library: \
	package.m4 \
	test_inputs_libagdb.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_tools: \
	package.m4 \
	test_inputs_agdbinfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

