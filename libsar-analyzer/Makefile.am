# Makefile.am - use automake to generate Makefile.in

lib_LTLIBRARIES = libsar-analyzer.la

if LANG_JP 
libsar_analyzer_la_SOURCES=common_jp.c make_report.c sar_analyzer_jp.c setter_getter.c
else
libsar_analyzer_la_SOURCES=common.c make_report.c sar_analyzer.c setter_getter.c
endif

libsar_analyzer_la_LDFLAGS = -version-info 1:53:0 

all:

clean-local:

