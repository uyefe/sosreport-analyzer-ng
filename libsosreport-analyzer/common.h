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
extern struct line_data *sos_subtitle_general_obj;
extern struct line_data *sos_subtitle_cpu_obj;
extern struct line_data *sos_subtitle_module_obj;
extern struct line_data *sos_subtitle_device_obj;
extern struct line_data *sos_subtitle_file_systems_obj;
extern struct line_data *sos_subtitle_disk_usage_obj;
extern struct line_data *sos_subtitle_memory_usage_obj;
extern struct line_data *sos_subtitle_networking_obj;
extern struct line_data *sos_subtitle_process_obj;
extern struct line_data *sos_subtitle_virtualization_obj;
extern struct line_data *sos_subtitle_files_obj;
extern struct line_data *sos_subtitle_systemd_obj;
extern struct line_data *sos_subtitle_security_obj;
extern struct line_data *sos_subtitle_kernel_obj;
extern struct line_data *sos_subtitle_yum_obj;
extern struct line_data *sos_subtitle_login_obj;
extern struct line_data *sos_subtitle_cron_obj;
extern struct line_data *sos_subtitle_logrotate_obj;
extern struct line_data *sos_subtitle_logs_and_journals_obj;
extern struct line_data *sos_subtitle_httpd_obj;
extern struct line_data *sos_subtitle_others_obj;
extern struct line_data *sos_line_obj;
extern struct line_data *sos_tail_obj;

extern struct line_data *tmp_1_obj;
extern struct line_data *tmp_2_obj;
extern struct line_data *tmp_3_obj;
extern struct line_data *tmp_4_obj;
extern struct line_data *tmp_5_obj;
extern struct line_data *tmp_6_obj;
extern struct line_data *tmp_7_obj;
extern struct line_data *tmp_8_obj;
extern struct line_data *tmp_9_obj;
extern struct line_data *tmp_10_obj;
extern struct line_data *tmp_11_obj;
extern struct line_data *tmp_12_obj;
extern struct line_data *tmp_13_obj;
extern struct line_data *tmp_14_obj;
extern struct line_data *tmp_15_obj;
extern struct line_data *tmp_16_obj;
extern struct line_data *tmp_17_obj;
extern struct line_data *tmp_18_obj;
extern struct line_data *tmp_19_obj;
extern struct line_data *tmp_20_obj;
extern struct line_data *tmp_21_obj;
extern struct line_data *tmp_22_obj;
extern struct line_data *tmp_23_obj;
extern struct line_data *tmp_24_obj;
extern struct line_data *tmp_25_obj;
extern struct line_data *tmp_26_obj;
extern struct line_data *tmp_27_obj;
extern struct line_data *tmp_28_obj;
extern struct line_data *tmp_29_obj;
extern struct line_data *tmp_30_obj;
extern struct line_data *tmp_31_obj;
extern struct line_data *tmp_32_obj;
extern struct line_data *tmp_33_obj;
extern struct line_data *tmp_34_obj;
extern struct line_data *tmp_35_obj;
extern struct line_data *tmp_36_obj;
extern struct line_data *tmp_37_obj;
extern struct line_data *tmp_38_obj;
extern struct line_data *tmp_39_obj;
extern struct line_data *tmp_40_obj;
extern struct line_data *tmp_41_obj;
extern struct line_data *tmp_42_obj;
extern struct line_data *tmp_43_obj;
extern struct line_data *tmp_44_obj;
extern struct line_data *tmp_45_obj;
extern struct line_data *tmp_46_obj;
extern struct line_data *tmp_47_obj;
extern struct line_data *tmp_48_obj;
extern struct line_data *tmp_49_obj;
extern struct line_data *tmp_50_obj;
extern struct line_data *tmp_51_obj;
extern struct line_data *tmp_52_obj;
extern struct line_data *tmp_53_obj;
extern struct line_data *tmp_54_obj;
extern struct line_data *tmp_55_obj;
extern struct line_data *tmp_56_obj;
extern struct line_data *tmp_57_obj;
extern struct line_data *tmp_58_obj;
extern struct line_data *tmp_59_obj;
extern struct line_data *tmp_60_obj;
extern struct line_data *tmp_61_obj;
extern struct line_data *tmp_62_obj;
extern struct line_data *tmp_63_obj;

extern struct line_data *mcinfo_boot_grub__obj;
extern struct line_data *mcinfo_cmdlog__obj;
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
extern struct file_data *file_data_obj;
extern struct line_data *etc_httpd__obj;
extern struct line_data *proc__obj;
extern struct line_data *var_crash__obj;
extern struct line_data *etc_default__obj;
extern struct line_data *etc_logrotate_d__obj;
extern struct line_data *etc_modprobe_d__obj;
extern struct line_data *etc_host_obj;
extern struct line_data *etc_udev__obj;
extern struct line_data *etc_yum_repos_d__obj;
extern struct line_data *etc_systemd_system__obj;
extern struct line_data *etc_systemd__obj;
extern struct line_data *usr_lib_systemd__obj;
extern struct line_data *sos_commands_sar__obj;
extern struct line_data *sos_commands_virsh__obj;
extern struct line_data *sos_commands_usb__obj;
extern struct line_data *lib__obj;
extern struct line_data *etc__obj;
extern struct line_data *sos_commands_networking__obj;
extern struct line_data *dev__obj;
extern struct line_data *usr__obj;
extern struct line_data *var__obj;
extern struct line_data *sos_commands_obj;
extern struct line_data *var_spool_cron__obj;
extern struct line_data *sos_commands_abrt__obj;
extern struct line_data *sys_module__obj;
extern struct line_data *etc_pam_d__obj;
extern struct line_data *sos_commands_pam__obj;
extern struct line_data *sos_commands_apache__obj;
extern struct line_data *etc_audit__obj;
extern struct line_data *sos_commands_auditd__obj;
extern struct line_data *sos_commands_memory__obj;
extern struct line_data *etc_firewalld__obj;
extern struct line_data *sos_commands_firewalld__obj;
extern struct line_data *sos_commands_devicemapper__obj;
extern struct line_data *etc_sysconfig__obj;
extern struct line_data *etc_selinux__obj;
extern struct line_data *sos_commands_selinux__obj;
extern struct line_data *etc_yum__obj;
extern struct line_data *sos_commands_yum__obj;
extern struct line_data *etc_dnf__obj;
extern struct line_data *sos_commands_dnf__obj;
extern struct line_data *etc_cron_hourly__obj;
extern struct line_data *etc_cron_daily__obj;
extern struct line_data *etc_cron_weekly__obj;
extern struct line_data *etc_cron_monthly__obj;
extern struct line_data *sos_commands_networkmanager__obj;
extern struct line_data *etc_networkmanager__obj;
extern struct line_data *sos_commands_ipmitool__obj;
extern struct line_data *sos_commands_wireless__obj;
extern struct line_data *etc_lvm__obj;
extern struct line_data *sos_commands_lvm2__obj;

extern char *str_arr_boot_grub [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_cmdlog [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_pki [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_cron_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_ifcfg [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_var_log_messages [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_var_log_secure [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_var_log_audit [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_logs_journalctl [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_ethtool_S [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_ethtool_i [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_boot [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_httpd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_proc [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_var_crash [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_default [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_logrotate_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_modprobe_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_host [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_udev [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_yum_repos_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_systemd_system [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_systemd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_usr_lib_systemd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_sar [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_virsh [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_usb [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_lib [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_networking [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_dev [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_usr [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_var [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_var_spool_cron [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_abrt [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sys_module [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_pam_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_pam [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_apache [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_audit [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_auditd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_memory [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_firewalld [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_firewalld [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_devicemapper [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_sysconfig [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_selinux [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_selinux [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_yum [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_yum [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_dnf [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_dnf [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_cron_hourly [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_cron_daily [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_cron_weekly [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_cron_hourly [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_networkmanager [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_networkmanager [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_ipmitool [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_wireless [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_etc_lvm [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
extern char *str_arr_sos_commands_lvm2 [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];

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
 *  Function Name: is_dir_present ()
 *
 *  This function checks directory.
 *  If directory does not exist, returns 1.
 *  If directory exists returns 0.
 *
 *  Caller : main ()
 *
 *  Calls : none
 *
 */
int is_dir_present ( const char *dname );

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
int set_token_to_item_arr ( const char *file_name, const char *member );

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

/*
 * check_item_string_length ()
 *
 * This function checks item string length in the conf file 
 *
 */
int check_item_string_length ( const char *token, const char *member );

#endif /* SOSREPORT_ANALYZER_COMMON_H */
