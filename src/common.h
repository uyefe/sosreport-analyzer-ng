/*
 *  common.h - common definitions
 *  This file contains the contents of sosreport-analyzer.
 *
 *  Copyright (C) 2018 Shintaro Fujiwara
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301 USA
 */

#include "line_data.h"

#ifndef SOSREPORT_ANALYZER_COMMON_H
#define SOSREPORT_ANALYZER_COMMON_H

#define PROGRAM_VERSION 0
#define PROGRAM_RELEASE 0
#define PROGRAM_SUB_RELEASE 2

/* the maximum line length of file name */
#define MAX_FULL_PATH_LENGTH  512

/* the maximum line length in the sar file */
#define MAX_LINE_LENGTH  4096

/* the maximum line length of file name */
#define MAX_FILE_NAME_LENGTH  255

/* the maximum analyze files */
#define MAX_ANALYZE_FILES  12

/*
 * These are pointers to the global data, it should be available
 * once sosreport_analyzer_init() was called.
 */
extern struct line_data *header_obj;
extern struct line_data *line_obj;
extern struct line_data *tail_obj;
extern struct line_data *var_log_messages_obj;
extern struct line_data *sos_commands_logs_journalctl___no_pager_obj;
extern struct line_data *sos_commands_networking_ethtool__S_obj;

/*
 * reverse_the_string()
 *
 * This function reverse the string 
 *
 */
char *reverse_the_string ( char *str_p, int str_len );

/*
 * cut_str_from_the_last_slash()
 *
 * This function returns the string from the last slash when string given with the length. 
 *
 */
char *cut_str_from_the_last_slash ( char *str_p, int str_len );

/*
 * cut_str_by_the_last_slash()
 *
 * This function returns the string to the last slash when string given with the length. 
 *
 */
char *cut_str_by_the_last_slash ( char *str_p, int str_len );

/*
 * read_analyze_dir()
 *
 * This function read directory and do something
 *
 */
void read_analyze_dir ( const char *member, const char *dname );

/*
 * read_file()
 *
 * This function read from file and do something
 *
 */
void read_file ( const char *file_name );

/*
 * read_file_pre()
 *
 * This function convey data to function read_file
 *
 */
void read_file_pre ( const char *member, const char *dir_name );

/*
 * set_token_to_item_arr ()
 *
 * This function sets items as an array of each member which had been set in config file. 
 */
void set_token_to_item_arr ( const char *file_name );

/*
 * append_item_to_line_obj()
 *
 * This function check line and if something matches, append to line_obj 
 *
 */
int append_item_to_line_obj ( char *line, const char *member, const char *item );

#endif /* SOSREPORT_ANALYZER_COMMON_H */
