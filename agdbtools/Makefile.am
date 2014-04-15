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
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBAGDB_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	agdbinfo

agdbinfo_SOURCES = \
	info_handle.c info_handle.h \
	agdbinfo.c \
	agdbinput.c agdbinput.h \
	agdboutput.c agdboutput.h \
	agdbtools_libcerror.h \
	agdbtools_libclocale.h \
	agdbtools_libcnotify.h \
	agdbtools_libcstring.h \
	agdbtools_libcsystem.h \
	agdbtools_libfdatetime.h \
	agdbtools_libagdb.h \
	agdbtools_libuna.h

agdbinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libagdb/libagdb.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on agdbinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(agdbinfo_SOURCES)

