# Makefile.am - use automake to generate Makefile.in

bin_PROGRAMS = sar-analyzer

AM_CXFLAGS = $(INIT_CFLAGS)

if LANG_JP 
sar_analyzer_SOURCES=common_jp.c line_data.c make_report.c sar_analyzer_jp.c setter_getter.c
else
sar_analyzer_SOURCES=common.c line_data.c make_report.c sar_analyzer.c setter_getter.c
endif

all:

clean-local:

