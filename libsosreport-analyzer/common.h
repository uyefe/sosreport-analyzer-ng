/*
 *  common.h - common definitions
 *  This file contains the contents of sosreport-analyzer.
 *
 *  Copyright (C) 2018-2019 Shintaro Fujiwara
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

#include "../common/global.h"
#include "line_data.h"

#ifndef SOSREPORT_ANALYZER_COMMON_H
#define SOSREPORT_ANALYZER_COMMON_H

/*
 * These are pointers to the global data, it should be available
 * once sosreport_analyzer_init() was called.
 *
 * These structs are for ones of which should read directory, or matched files in the directory.
 */
extern struct line_data *tmp_obj;
extern struct dir_file_name *sos_dir_file_obj;
extern struct line_data *sos_header_obj;
extern struct line_data *sos_line_obj;
extern struct line_data *sos_tail_obj;
extern struct line_data *etc_pki__obj;
extern struct line_data *etc_cron_d__obj;
extern struct line_data *etc_sysconfig_network_scripts_ifcfg__obj;
extern struct line_data *var_log_messages_obj;
extern struct line_data *var_log_secure_obj;
extern struct line_data *var_log_audit__obj;
extern struct line_data *sos_commands_logs_journalctl___no_pager_obj;
extern struct line_data *sos_commands_networking_ethtool__S_obj;
extern struct line_data *sos_commands_networking_ethtool__i_obj;
extern struct line_data *sos_commands_boot__obj;
extern struct line_data *mcinfo_boot_grub__obj;
extern struct line_data *mcinfo_cmdlog__obj;
extern struct file_data *file_data_obj;

/*
 * new function reading files from the result of 'read_analyze_dir'
 */
int read_file_from_analyze_dir ( node **obj, const char *member );

/*
 * read_analyze_dir()
 *
 * This function read directory and do something
 *
 */
int read_analyze_dir ( const char *member, const char *dname, int recursive );

/*
 * read_file()
 *
 * This function read from file and do something
 *
 */
int read_file ( const char *file_name, const char *member, int files );

/*
 * read_file_pre()
 *
 * This function convey data to function read_file
 *
 */
void read_file_pre ( const char *member, const char *dir_name );

/* 
 *  Function Name: check_result_dir ()
 *
 *  This function checks result directory.
 *  If result directory does not exist, creates it.
 *
 *  Caller : main ()
 *
 *  Calls : none
 *
 */
int check_result_dir ( const char *dname );

/* 
 *  Function Name: check_time_span_str ()
 *
 *  This function checks time-span string.
 *  If it's fine, returns 1, and if not returns 0
 *  should be in style '00:00-00:00' and no other
 *  Caller : main ()
 *
 *  Calls : none
 *
 */
int check_time_span_str ( const char *time_span_str );

/*
 * Function Name: get_dirname ()
 *
 * This function returns dirname for analyzed result
 * 
 * Caller : main ()
 *
 * Calls : none
 *
 */
const char *get_dirname ( char [ MAX_LINE_LENGTH ] );

/*
 * Function Name: get_sos_file_name_to_be_written ()
 *
 * This function returns sos_file_name_to_be_written for analyzed result
 * 
 * Caller : main ()
 *
 * Calls : none
 *
 */
const char *get_sos_file_name_to_be_written ( void );

/*
 * Function Name: get_sar_file_name_to_be_written ()
 *
 * This function returns sar_file_name_to_be_written for analyzed result
 * 
 * Caller : main ()
 *
 * Calls : none
 *
 */
const char *get_sar_file_name_to_be_written ( void );

/*
 * Function Name: get_ps_file_name_to_be_written ()
 *
 * This function returns ps_file_name_to_be_written for analyzed result
 * 
 * Caller : main ()
 *
 * Calls : none
 *
 */
const char *get_ps_file_name_to_be_written ( void );

/*
 *  Function Name: sos_file_to_write ()
 *
 *  This function sets file name to be written to the sosreport_analyzer_obj.
 *
 *  Caller : main ()
 *
 */
void sos_file_to_write ( void );

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
int append_item_to_sos_line_obj ( char *line, const char *member, const char *item );

/*
 * free_sosreport_analyzer_obj ()
 *
 * This function frees sosreport-analyzer objects
 *
 */
void free_sosreport_analyzer_obj ( void );

#endif /* SOSREPORT_ANALYZER_COMMON_H */
