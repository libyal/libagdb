AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	@PTHREAD_CPPFLAGS@

lib_LTLIBRARIES = libagdb.la

libagdb_la_SOURCES = \
	agdb_file_header.h \
	agdb_file_information.h \
	agdb_volume_information.h \
	libagdb.c \
	libagdb_codepage.h \
	libagdb_compressed_block.c libagdb_compressed_block.h \
	libagdb_compressed_blocks_stream.c libagdb_compressed_blocks_stream.h \
	libagdb_debug.c libagdb_debug.h \
	libagdb_definitions.h \
	libagdb_error.c libagdb_error.h \
	libagdb_extern.h \
	libagdb_file.c libagdb_file.h \
	libagdb_file_information.c libagdb_file_information.h \
	libagdb_io_handle.c libagdb_io_handle.h \
	libagdb_libbfio.h \
	libagdb_libcdata.h \
	libagdb_libcerror.h \
	libagdb_libclocale.h \
	libagdb_libcnotify.h \
	libagdb_libcstring.h \
	libagdb_libfcache.h \
	libagdb_libfdata.h \
	libagdb_libfdatetime.h \
	libagdb_libfwnt.h \
	libagdb_libuna.h \
	libagdb_notify.c libagdb_notify.h \
	libagdb_support.c libagdb_support.h \
	libagdb_types.h \
	libagdb_unused.h \
	libagdb_volume_information.c libagdb_volume_information.h

libagdb_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFWNT_LIBADD@ \
	@PTHREAD_LIBADD@

libagdb_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libagdb_definitions.h.in \
	libagdb.rc \
	libagdb.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libagdb_definitions.h
	/bin/rm -f libagdb.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libagdb ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libagdb_la_SOURCES)

