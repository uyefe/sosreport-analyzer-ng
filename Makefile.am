# Makefile.am - use automake to generate Makefile.in
#

SUBDIRS = libsosreport-analyzer libsar-analyzer

AM_CXFLAGS = $(INIT_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/libsosreport-analyzer -I$(top_srcdir)/libsar-analyzer
AM_LDFLAGS = -L$(top_srcdir)/libsosreport-analyzer -L$(top_srcdir)/libsar-analyzer -Wl,-rpath,/usr/local/lib

bin_PROGRAMS = sosreport-analyzer
sosreport_analyzer_SOURCES = main.c
sosreport_analyzer_LDADD = -lsosreport-analyzer -lsar-analyzer

SOSREPORT_ANALYZER_CONF_PATH = @SOSREPORT_ANALYZER_CONF_PATH@
SOSREPORT_ANALYZER_MCINFO_CONF_PATH = @SOSREPORT_ANALYZER_MCINFO_CONF_PATH@
SOSREPORT_ANALYZER_DATA_PATH = @SOSREPORT_ANALYZER_DATA_PATH@
SOSREPORT_ANALYZER_INCLUDE_PATH = @SOSREPORT_ANALYZER_INCLUDE_PATH@
SOSREPORT_ANALYZER_LIB_PATH = @SOSREPORT_ANALYZER_LIB_PATH@
SAR_ANALYZER_LIB_PATH = @SAR_ANALYZER_LIB_PATH@

install-data-local: install-sosreport_analyzer_conf install-sosreport_analyzer_mcinfo_conf install-sosreport_analyzer_data install-sosreport_analyzer_include install-sosreport_analyzer_lib install-sar_analyzer_lib
uninstall-local: uninstall-sosreport_analyzer_conf uninstall-sosreport_analyzer_mcinfo_conf uninstall-sosreport_analyzer_data uninstall-sosreport_analyzer_include uninstall-sosreport_analyzer_lib uninstall-sar_analyzer_lib

# install a default sosreport-analyzer configuration file if it is not already there
install-sosreport_analyzer_conf:
	@if [ -f $(DESTDIR)$(SOSREPORT_ANALYZER_CONF_PATH) ]; then \
            echo "$(DESTDIR)$(SOSREPORT_ANALYZER_CONF_PATH) already exists, install will not overwrite"; \
	else \
            $(mkinstalldirs) `dirname $(DESTDIR)$(SOSREPORT_ANALYZER_CONF_PATH)`; \
            $(INSTALL) -m 644 $(srcdir)/sosreport-analyzer.conf.example $(DESTDIR)$(SOSREPORT_ANALYZER_CONF_PATH); \
	fi

uninstall-sosreport_analyzer_conf:
	-rm -f $(DESTDIR)$(SOSREPORT_ANALYZER_CONF_PATH)

# install a default sosreport-analyzer-mcinfo configuration file if it is not already there
install-sosreport_analyzer_mcinfo_conf:
	@if [ -f $(DESTDIR)$(SOSREPORT_ANALYZER_MCINFO_CONF_PATH) ]; then \
            echo "$(DESTDIR)$(SOSREPORT_ANALYZER_MCINFO_CONF_PATH) already exists, install will not overwrite"; \
	else \
            $(mkinstalldirs) `dirname $(DESTDIR)$(SOSREPORT_ANALYZER_MCINFO_CONF_PATH)`; \
            $(INSTALL) -m 644 $(srcdir)/sosreport-analyzer-mcinfo.conf.example $(DESTDIR)$(SOSREPORT_ANALYZER_MCINFO_CONF_PATH); \
	fi

uninstall-sosreport_analyzer_mcinfo_conf:
	-rm -f $(DESTDIR)$(SOSREPORT_ANALYZER_MCINFO_CONF_PATH)

# install sosreport-analyzer.conf.example and sosreport-analyzer-mcinfo.conf.example
install-sosreport_analyzer_data:
	@if [ -f $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH) ]; then \
            $(INSTALL) -m 644 $(srcdir)/sosreport-analyzer.conf.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/sosreport-analyzer-mcinfo.conf.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer-mcinfo.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/sosreport-analyzer.conf.CentOS7.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer.conf.CentOS7.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/sosreport-analyzer.conf.CentOS6.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer.conf.CentOS6.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/sosreport-analyzer-mcinfo.conf.AXS6.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer-mcinfo.conf.AXS6.example; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH); \
            $(INSTALL) -m 644 $(srcdir)/sosreport-analyzer.conf.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/sosreport-analyzer-mcinfo.conf.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer-mcinfo.conf.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/sosreport-analyzer.conf.CentOS7.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer.conf.CentOS7.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/sosreport-analyzer.conf.CentOS6.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer.conf.CentOS6.example; \
            $(INSTALL) -m 644 $(srcdir)/conf/sosreport-analyzer-mcinfo.conf.AXS6.example $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)/sosreport-analyzer-mcinfo.conf.AXS6.example; \
	fi

uninstall-sosreport_analyzer_data:
	-rm -rf $(DESTDIR)$(SOSREPORT_ANALYZER_DATA_PATH)

# install header files (not all, yet) 
install-sosreport_analyzer_include:
	@if [ -d $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH) ]; then \
            $(INSTALL) -m 644 $(srcdir)/common/global.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/global.h; \
            $(INSTALL) -m 644 $(srcdir)/common/common_line_data.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/common_line_data.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/cfg.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/cfg.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/common.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/common.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/line_data.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/line_data.h; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH); \
            $(INSTALL) -m 644 $(srcdir)/common/global.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/global.h; \
            $(INSTALL) -m 644 $(srcdir)/common/common_line_data.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/common_line_data.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/cfg.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/cfg.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/common.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/common.h; \
            $(INSTALL) -m 644 $(srcdir)/libsosreport-analyzer/line_data.h $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)/line_data.h; \
	fi

uninstall-sosreport_analyzer_include:
	-rm -rf $(DESTDIR)$(SOSREPORT_ANALYZER_INCLUDE_PATH)

# install libsosreport-analyzer.so
install-sosreport_analyzer_lib:
	@if [ -f $(DESTDIR)$(SOSREPORT_ANALYZER_LIB_PATH) ]; then \
            $(INSTALL) -m 775 $(srcdir)/libsosreport-analyzer/.libs/libsosreport-analyzer.so $(DESTDIR)$(SOSREPORT_ANALYZER_LIB_PATH)/libsosreport-analyzer.so; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SOSREPORT_ANALYZER_LIB_PATH); \
            $(INSTALL) -m 775 $(srcdir)/libsosreport-analyzer/.libs/libsosreport-analyzer.so $(DESTDIR)$(SOSREPORT_ANALYZER_LIB_PATH)/libsosreport-analyzer.so; \
	fi

uninstall-sosreport_analyzer_lib:
	-rm -f $(DESTDIR)$(SOSREPORT_ANALYZER_LIB_PATH)/libsosreport-analyzer.so

# install libsar-analyzer.so
install-sar_analyzer_lib:
	@if [ -f $(DESTDIR)$(SAR_ANALYZER_LIB_PATH) ]; then \
            $(INSTALL) -m 775 $(srcdir)/libsar-analyzer/.libs/libsar-analyzer.so $(DESTDIR)$(SAR_ANALYZER_LIB_PATH)/libsar-analyzer.so; \
	else \
            $(MKDIR_P) $(DESTDIR)$(SAR_ANALYZER_LIB_PATH); \
            $(INSTALL) -m 775 $(srcdir)/libsar-analyzer/.libs/libsar-analyzer.so $(DESTDIR)$(SAR_ANALYZER_LIB_PATH)/libsar-analyzer.so; \
	fi

uninstall-sar_analyzer_lib:
	-rm -f $(DESTDIR)$(SAR_ANALYZER_LIB_PATH)/libsar-analyzer.so
