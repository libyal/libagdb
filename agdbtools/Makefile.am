AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBAGDB_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	agdbinfo

agdbinfo_SOURCES = \
	agdbinfo.c \
	agdbinput.c agdbinput.h \
	agdbtools_getopt.c agdbtools_getopt.h \
	agdbtools_i18n.h \
	agdbtools_libagdb.h \
	agdbtools_libbfio.h \
	agdbtools_libcerror.h \
	agdbtools_libclocale.h \
	agdbtools_libcnotify.h \
	agdbtools_libfdatetime.h \
	agdbtools_libuna.h \
	agdbtools_output.c agdbtools_output.h \
	agdbtools_unused.h \
	info_handle.c info_handle.h

agdbinfo_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	../libagdb/libagdb.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on agdbinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(agdbinfo_SOURCES)

