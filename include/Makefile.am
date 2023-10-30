include_HEADERS = \
	libagdb.h

pkginclude_HEADERS = \
	libagdb/codepage.h \
	libagdb/definitions.h \
	libagdb/error.h \
	libagdb/extern.h \
	libagdb/features.h \
	libagdb/types.h

EXTRA_DIST = \
	libagdb.h.in \
	libagdb/definitions.h.in \
	libagdb/features.h.in \
	libagdb/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libagdb.h
	-rm -f libagdb/definitions.h
	-rm -f libagdb/features.h
	-rm -f libagdb/types.h
	-rm -f Makefile

