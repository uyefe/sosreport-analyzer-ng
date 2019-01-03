# Makefile.am - use automake to generate Makefile.in
#

SUBDIRS = libsosreport-analyzer libsar-analyzer

AM_CXFLAGS = $(INIT_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/libsosreport-analyzer -I$(top_srcdir)/libsar-analyzer
AM_LDFLAGS = -L$(top_srcdir)/libsosreport-analyzer -L$(top_srcdir)/libsar-analyzer -Wl,-rpath,/usr/local/lib

bin_PROGRAMS = sosreport-analyzer
sosreport_analyzer_SOURCES = main.c
sosreport_analyzer_LDADD = -lsosreport-analyzer -lsar-analyzer

SOSREPORT_ANALYZERD_CONF_PATH = @SOSREPORT_ANALYZERD_CONF_PATH@
SOSREPORT_ANALYZERD_DATA_PATH = @SOSREPORT_ANALYZERD_DATA_PATH@
SOSREPORT_ANALYZERD_INCLUDE_PATH = @SOSREPORT_ANALYZERD_INCLUDE_PATH@
SOSREPORT_ANALYZERD_LIB_PATH = @SOSREPORT_ANALYZERD_LIB_PATH@
SAR_ANALYZERD_LIB_PATH = @SAR_ANALYZERD_LIB_PATH@

install-data-local: install-sosreport_analyzerd_conf install-sosreport_analyzerd_data install-sosreport_analyzerd_include install-sosreport_analyzerd_lib install-sar_analyzerd_lib
uninstall-local: uninstall-sosreport_analyzerd_conf uninstall-sosreport_analyzerd_data uninstall-sosreport_analyzerd_include uninstall-sosreport_analyzerd_lib uninstall-sar_analyzerd_lib

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

# install cfg.h 
install-sosreport_analyzerd_include:
	@if [ -d $(DESTDIR)$(SOSREPORT_ANALYZERD_INCLUDE_PATH) ]; then \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/cfg.h $(DESTDIR)$(SOSREPORT_ANALYZERD_INCLUDE_PATH)/cfg.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/common.h $(DESTDIR)$(SOSREPORT_ANALYZERD_INCLUDE_PATH)/common.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/line_data.h $(DESTDIR)$(SOSREPORT_ANALYZERD_INCLUDE_PATH)/line_data.h; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SOSREPORT_ANALYZERD_INCLUDE_PATH); \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/cfg.h $(DESTDIR)$(SOSREPORT_ANALYZERD_INCLUDE_PATH)/cfg.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/common.h $(DESTDIR)$(SOSREPORT_ANALYZERD_INCLUDE_PATH)/common.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/line_data.h $(DESTDIR)$(SOSREPORT_ANALYZERD_INCLUDE_PATH)/line_data.h; \
	fi

uninstall-sosreport_analyzerd_include:
	-rm -rf $(DESTDIR)$(SOSREPORT_ANALYZERD_INCLUDE_PATH)

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

# install libsar-analyzerd.so
install-sar_analyzerd_lib:
	@if [ -f $(DESTDIR)$(SAR_ANALYZERD_LIB_PATH) ]; then \
            $(INSTALL) -m 775 $(srcdir)/libsar-analyzer/.libs/libsar-analyzer.so $(DESTDIR)$(SAR_ANALYZERD_LIB_PATH)/libsar-analyzerd.so; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SAR_ANALYZERD_LIB_PATH); \
            $(INSTALL) -m 775 $(srcdir)/libsar-analyzer/.libs/libsar-analyzer.so $(DESTDIR)$(SAR_ANALYZERD_LIB_PATH)/libsar-analyzer.so; \
	fi

uninstall-sar_analyzerd_lib:
	-rm -f $(DESTDIR)$(SAR_ANALYZERD_LIB_PATH)/libsar-analyzer.so
