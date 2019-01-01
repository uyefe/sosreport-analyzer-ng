# Makefile.am - use automake to generate Makefile.in

SUBDIRS = libsosreport-analyzer

AM_CXFLAGS = $(INIT_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/libsosreport-analyzer
AM_LDFLAGS = "-L/usr/local/lib"

bin_PROGRAMS = sosreport-analyzer
sosreport_analyzer_SOURCES = main.c
sosreport_analyzer_LDADD = libsosreport-analyzer/.libs/libsosreport-analyzer.so 

SOSREPORT_ANALYZERD_CONF_PATH = @SOSREPORT_ANALYZERD_CONF_PATH@
SOSREPORT_ANALYZERD_DATA_PATH = @SOSREPORT_ANALYZERD_DATA_PATH@
SOSREPORT_ANALYZERD_LIB_PATH = @SOSREPORT_ANALYZERD_LIB_PATH@

install-data-local: install-sosreport_analyzerd_conf install-sosreport_analyzerd_data install-sosreport_analyzerd_lib
uninstall-local: uninstall-sosreport_analyzerd_conf uninstall-sosreport_analyzerd_data uninstall-sosreport_analyzerd_lib

# install a default configuration file if it is not already there
install-sosreport_analyzerd_conf:
	@if [ -f $(DESTDIR)$(SOSREPORT_ANALYZERD_CONF_PATH) ]; then \
            echo "$(DESTDIR)$(SOSREPORT_ANALYZERD_CONF_PATH) already exists, install will not overwrite"; \
	else \
            $(mkinstalldirs) `dirname $(DESTDIR)$(SOSREPORT_ANALYZERD_CONF_PATH)`; \
            $(INSTALL) -m 644 $(srcdir)/sosreport-analyzerd.conf.example $(DESTDIR)$(SOSREPORT_ANALYZERD_CONF_PATH); \
	fi

uninstall-sosreport_analyzerd_conf:
	-rm -f $(DESTDIR)$(SOSREPORT_ANALYZERD_CONF_PATH)

# install sosreport-analyzerd.conf.example 
install-sosreport_analyzerd_data:
	@if [ -f $(DESTDIR)$(SOSREPORT_ANALYZERD_DATA_PATH) ]; then \
            $(INSTALL) -m 644 $(srcdir)/sosreport-analyzerd.conf.example $(DESTDIR)$(SOSREPORT_ANALYZERD_DATA_PATH)/sosreport-analyzerd.conf.example; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SOSREPORT_ANALYZERD_DATA_PATH); \
            $(INSTALL) -m 644 $(srcdir)/sosreport-analyzerd.conf.example $(DESTDIR)$(SOSREPORT_ANALYZERD_DATA_PATH)/sosreport-analyzerd.conf.example; \
	fi

uninstall-sosreport_analyzerd_data:
	-rm -rf $(DESTDIR)$(SOSREPORT_ANALYZERD_DATA_PATH)

# install libsosreport-analyzerd.so
install-sosreport_analyzerd_lib:
	@if [ -f $(DESTDIR)$(SOSREPORT_ANALYZERD_LIB_PATH) ]; then \
            $(INSTALL) -m 775 $(srcdir)/libsosreport-analyzer/.libs/libsosreport-analyzer.so $(DESTDIR)$(SOSREPORT_ANALYZERD_LIB_PATH)/libsosreport-analyzerd.so; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SOSREPORT_ANALYZERD_LIB_PATH); \
            $(INSTALL) -m 775 $(srcdir)/libsosreport-analyzer/.libs/libsosreport-analyzer.so $(DESTDIR)$(SOSREPORT_ANALYZERD_LIB_PATH)/libsosreport-analyzer.so; \
	fi

uninstall-sosreport_analyzerd_lib:
	-rm -f $(DESTDIR)$(SOSREPORT_ANALYZERD_LIB_PATH)/libsosreport-analyzer.so
