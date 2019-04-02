/*
 *  common.c - common functions 
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

#include <unistd.h> /* should be above for declaring macro */
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include "../common/global.c"
#include "common.h"
#include "cfg.h"
#include "setter_getter.h"

/* sos_dir_file_obj */
struct dir_file_name sos_dir_file_obj_raw = 
    {{ "test.txt", "test.txt", "test.txt", "test.txt" }};

/* sos_header_obj */
struct line_data sos_header_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* line_obj */
struct line_data sos_line_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tail_obj */
struct line_data sos_tail_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* mcinfo_boot_grub__obj */
struct line_data mcinfo_boot_grub__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* mcinfo_cmdlog__obj */
struct line_data mcinfo_cmdlog__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_pki__obj */
struct line_data etc_pki__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_cron_d__obj */
struct line_data etc_cron_d__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_sysconfig_network_scripts_ifcfg__obj */
struct line_data etc_sysconfig_network_scripts_ifcfg__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_log_messages_obj */
struct line_data var_log_messages_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_log_secure_obj */
struct line_data var_log_secure_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_log_audit__obj */
struct line_data var_log_audit__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_logs_journalctl___no_pager_obj */
struct line_data sos_commands_logs_journalctl___no_pager_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_networking_ethtool__S_obj */
struct line_data sos_commands_networking_ethtool__S_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_networking_ethtool__i_obj */
struct line_data sos_commands_networking_ethtool__i_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_boot__obj */
struct line_data sos_commands_boot__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_httpd__obj */
struct line_data etc_httpd__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* proc__obj */
struct line_data proc__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_crash__obj */
struct line_data var_crash__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_default__obj */
struct line_data etc_default__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_logrotate_d__obj */
struct line_data etc_logrotate_d__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_modprobe_d__obj */
struct line_data etc_modprobe_d__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_host_obj */
struct line_data etc_host_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_udev__obj */
struct line_data etc_udev__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_yum_repos_d__obj */
struct line_data etc_yum_repos_d__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_systemd_system__obj */
struct line_data etc_systemd_system__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_systemd__obj */
struct line_data etc_systemd__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* usr_lib_systemd__obj */
struct line_data usr_lib_systemd__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_sar__obj */
struct line_data sos_commands_sar__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_virsh__obj */
struct line_data sos_commands_virsh__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_usb__obj */
struct line_data sos_commands_usb__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* lib__obj */
struct line_data lib__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc__obj */
struct line_data etc__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_networking__obj */
struct line_data sos_commands_networking__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* dev__obj */
struct line_data dev__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* usr__obj */
struct line_data usr__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var__obj */
struct line_data var__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_spool_cron__obj */
struct line_data var_spool_cron__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_obj */
struct line_data sos_commands_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_abrt__obj */
struct line_data sos_commands_abrt__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_1_obj */
struct line_data tmp_1_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_2_obj */
struct line_data tmp_2_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_3_obj */
struct line_data tmp_3_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_4_obj */
struct line_data tmp_4_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_5_obj */
struct line_data tmp_5_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_6_obj */
struct line_data tmp_6_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_7_obj */
struct line_data tmp_7_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_8_obj */
struct line_data tmp_8_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_9_obj */
struct line_data tmp_9_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_10_obj */
struct line_data tmp_10_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_11_obj */
struct line_data tmp_11_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_12_obj */
struct line_data tmp_12_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_13_obj */
struct line_data tmp_13_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_14_obj */
struct line_data tmp_14_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_15_obj */
struct line_data tmp_15_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_16_obj */
struct line_data tmp_16_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_17_obj */
struct line_data tmp_17_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_18_obj */
struct line_data tmp_18_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_19_obj */
struct line_data tmp_19_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_20_obj */
struct line_data tmp_20_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_21_obj */
struct line_data tmp_21_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_22_obj */
struct line_data tmp_22_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_23_obj */
struct line_data tmp_23_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_24_obj */
struct line_data tmp_24_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_25_obj */
struct line_data tmp_25_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_26_obj */
struct line_data tmp_26_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_27_obj */
struct line_data tmp_27_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_28_obj */
struct line_data tmp_28_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_29_obj */
struct line_data tmp_29_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_30_obj */
struct line_data tmp_30_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_31_obj */
struct line_data tmp_31_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_32_obj */
struct line_data tmp_32_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_33_obj */
struct line_data tmp_33_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_34_obj */
struct line_data tmp_34_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_35_obj */
struct line_data tmp_35_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tmp_36_obj */
struct line_data tmp_36_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* making pointers to the structs */
struct dir_file_name *sos_dir_file_obj = &sos_dir_file_obj_raw;
struct line_data *sos_header_obj = &sos_header_obj_raw;
struct line_data *sos_line_obj = &sos_line_obj_raw;
struct line_data *sos_tail_obj = &sos_tail_obj_raw;
struct line_data *tmp_1_obj = &tmp_1_obj_raw;
struct line_data *tmp_2_obj = &tmp_2_obj_raw;
struct line_data *tmp_3_obj = &tmp_3_obj_raw;
struct line_data *tmp_4_obj = &tmp_4_obj_raw;
struct line_data *tmp_5_obj = &tmp_5_obj_raw;
struct line_data *tmp_6_obj = &tmp_6_obj_raw;
struct line_data *tmp_7_obj = &tmp_7_obj_raw;
struct line_data *tmp_8_obj = &tmp_8_obj_raw;
struct line_data *tmp_9_obj = &tmp_9_obj_raw;
struct line_data *tmp_10_obj = &tmp_10_obj_raw;
struct line_data *tmp_11_obj = &tmp_11_obj_raw;
struct line_data *tmp_12_obj = &tmp_12_obj_raw;
struct line_data *tmp_13_obj = &tmp_13_obj_raw;
struct line_data *tmp_14_obj = &tmp_14_obj_raw;
struct line_data *tmp_15_obj = &tmp_15_obj_raw;
struct line_data *tmp_16_obj = &tmp_16_obj_raw;
struct line_data *tmp_17_obj = &tmp_17_obj_raw;
struct line_data *tmp_18_obj = &tmp_18_obj_raw;
struct line_data *tmp_19_obj = &tmp_19_obj_raw;
struct line_data *tmp_20_obj = &tmp_20_obj_raw;
struct line_data *tmp_21_obj = &tmp_21_obj_raw;
struct line_data *tmp_22_obj = &tmp_22_obj_raw;
struct line_data *tmp_23_obj = &tmp_23_obj_raw;
struct line_data *tmp_24_obj = &tmp_24_obj_raw;
struct line_data *tmp_25_obj = &tmp_25_obj_raw;
struct line_data *tmp_26_obj = &tmp_26_obj_raw;
struct line_data *tmp_27_obj = &tmp_27_obj_raw;
struct line_data *tmp_28_obj = &tmp_28_obj_raw;
struct line_data *tmp_29_obj = &tmp_29_obj_raw;
struct line_data *tmp_30_obj = &tmp_30_obj_raw;
struct line_data *tmp_31_obj = &tmp_31_obj_raw;
struct line_data *tmp_32_obj = &tmp_32_obj_raw;
struct line_data *tmp_33_obj = &tmp_33_obj_raw;
struct line_data *tmp_34_obj = &tmp_34_obj_raw;
struct line_data *tmp_35_obj = &tmp_35_obj_raw;
struct line_data *tmp_36_obj = &tmp_36_obj_raw;

struct line_data *mcinfo_boot_grub__obj = &mcinfo_boot_grub__obj_raw;
struct line_data *mcinfo_cmdlog__obj = &mcinfo_cmdlog__obj_raw;
struct line_data *etc_pki__obj = &etc_pki__obj_raw;
struct line_data *etc_cron_d__obj = &etc_cron_d__obj_raw;
struct line_data *etc_sysconfig_network_scripts_ifcfg__obj = &etc_sysconfig_network_scripts_ifcfg__obj_raw;
struct line_data *var_log_messages_obj = &var_log_messages_obj_raw;
struct line_data *var_log_secure_obj = &var_log_secure_obj_raw;
struct line_data *var_log_audit__obj = &var_log_audit__obj_raw;
struct line_data *sos_commands_logs_journalctl___no_pager_obj = &sos_commands_logs_journalctl___no_pager_obj_raw;
struct line_data *sos_commands_networking_ethtool__S_obj = &sos_commands_networking_ethtool__S_obj_raw;
struct line_data *sos_commands_networking_ethtool__i_obj = &sos_commands_networking_ethtool__i_obj_raw;
struct line_data *sos_commands_boot__obj = &sos_commands_boot__obj_raw;
struct line_data *etc_httpd__obj = &etc_httpd__obj_raw;
struct line_data *proc__obj = &proc__obj_raw;
struct line_data *var_crash__obj = &var_crash__obj_raw;
struct line_data *etc_default__obj = &etc_default__obj_raw;
struct line_data *etc_logrotate_d__obj = &etc_logrotate_d__obj_raw;
struct line_data *etc_modprobe_d__obj = &etc_modprobe_d__obj_raw;
struct line_data *etc_host_obj = &etc_host_obj_raw;
struct line_data *etc_udev__obj = &etc_udev__obj_raw;
struct line_data *etc_yum_repos_d__obj = &etc_yum_repos_d__obj_raw;
struct line_data *etc_systemd_system__obj = &etc_systemd_system__obj_raw;
struct line_data *etc_systemd__obj = &etc_systemd__obj_raw;
struct line_data *usr_lib_systemd__obj = &usr_lib_systemd__obj_raw;
struct line_data *sos_commands_sar__obj = &sos_commands_sar__obj_raw;
struct line_data *sos_commands_virsh__obj = &sos_commands_virsh__obj_raw;
struct line_data *sos_commands_usb__obj = &sos_commands_usb__obj_raw;
struct line_data *lib__obj = &lib__obj_raw;
struct line_data *etc__obj = &etc__obj_raw;
struct line_data *sos_commands_networking__obj = &sos_commands_networking__obj_raw;
struct line_data *dev__obj = &dev__obj_raw;
struct line_data *usr__obj = &usr__obj_raw;
struct line_data *var__obj = &var__obj_raw;
struct line_data *sos_commands_obj = &sos_commands_obj_raw;
struct line_data *var_spool_cron__obj = &var_spool_cron__obj_raw;
struct line_data *sos_commands_abrt__obj = &sos_commands_abrt__obj_raw;

char *str_arr_boot_grub [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_cmdlog [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_pki [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_cron [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_ifcfg [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_log_messages [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_log_secure [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_log_audit [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_logs_journalctl [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_ethtool_S [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_ethtool_i [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_boot [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_httpd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_proc [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_crash [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_default [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_logrotate_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_modprobe_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_host [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_udev [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_yum_repos_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_systemd_system [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_systemd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_usr_lib_systemd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_sar [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_virsh [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_usb [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_lib [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_networking [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_dev [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_usr [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_spool_cron [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_abrt [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];

int read_analyze_dir ( const char *member, const char *dname, int recursive )
{
    DIR *dir = NULL;
    struct dirent *dp;
    int str_len = 0;
    int str_len_fname_part = 0;
    int str_len_dname_full = 0;
    char *fname_part, *dname_full;
    char full_path [ MAX_LINE_LENGTH ];  
    char read_path [ MAX_LINE_LENGTH ];  
    char str_ret [ MAX_LINE_LENGTH ];  
    char fname_part_path [ MAX_LINE_LENGTH ];  

    memset ( full_path, '\0', sizeof ( full_path ) ); 
    memset ( read_path, '\0', sizeof ( read_path ) ); 
    memset ( str_orig, '\0', sizeof ( str_orig ) ); 
    memset ( fname_part_path, '\0', sizeof ( fname_part_path ) ); 
    snprintf (full_path, MAX_LINE_LENGTH, "%s/%s", dname, member );
    str_len = ( int ) strlen ( full_path );
    if ( str_len <= 0 )
    {
        printf("Path 1 is too short (%s): %d %s\n",full_path, str_len, strerror(errno));
        free_sosreport_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    full_path [ str_len ] = '\0';
    strcpy ( str_orig, full_path );

    fname_part = cut_str_from_the_last_slash ( reverse_the_string ( full_path, str_len ), str_len, str_ret );

    snprintf (fname_part_path, MAX_LINE_LENGTH, "%s", fname_part );
    str_len_fname_part = ( int ) strlen ( fname_part );
    str_len_dname_full = str_len - str_len_fname_part;
    if ( str_len_dname_full <= 0 ) 
    {
        printf("Path 2 is too short %d %s\n",str_len_dname_full, strerror(errno));
        free_sosreport_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }

    if ( recursive == 0 )
        dname_full = cut_str_by_the_last_slash ( full_path, str_len_dname_full );
    else
        dname_full = ( char * ) dname;

    int var_crash_exists = 1; 

    if ( dname_full != NULL )
    {
        /* if open directory fails, exit with error message,
         * and print that the member should be set to 'skip'.
         */
        if ( ( dir = opendir ( dname_full ) ) == NULL ) 
        {
            printf("can't open directory (%s): %s\n",dname_full,strerror(errno));
            printf("You should set 'skip' to %s in conf file.\n",member);
            if ( strcmp ( member, "var/crash/" ) == 0 )
            {
                var_crash_exists = 0;                
                puts("I skip 'var/crash/' automatically.");
                puts("Do not set 'skip' to member 'var/crash/'.");
            }
            else
            {
                printf("Skip '%s' and go on.\n",member);
                /* free_sosreport_analyzer_obj ( ); */
                return ( 0 );
                /* exit ( EXIT_FAILURE ); */
            }
        }
    }
    char *str;
    int i = 0;
    /* limit of fname_part files to be analyzed */
    int str_arr_valid_size = 0;

    /* read from directory and set in an array */
    if ( var_crash_exists == 1 )
    {
        for ( dp = readdir ( dir ),i = 0; dp != NULL; dp = readdir ( dir ) )
        {
            char full_path_plus_str [ MAX_LINE_LENGTH ];  
            char filename [ MAX_LINE_LENGTH ];  
            memset ( full_path_plus_str, '\0', sizeof ( full_path_plus_str ) ); 
            memset ( filename, '\0', sizeof ( filename ) ); 

            if ( ( dp->d_type != DT_REG ) && ( dp->d_type != DT_DIR ) )
                continue;

            str = dp->d_name;
            /*###FIX ME
             * proc/kallsyms is a big file, so...
             * journal... is a big file, so...
             * cil or hll... is selinux stuff and human can't read, so...
             * messages* should be read by other member , so...
             * others have big one, compressed or selinux modules.
             * in proc/ there are some files which have only write permissions and couldn't be read.
             * file sos_commands/networking/ethtool_-d* is sometimes too big.
             *
             * we should check file with a function and if the file is too big, skip it. 
             * Now, if file size is over 50Mbytes, skip the file.
             */
            snprintf (filename, MAX_LINE_LENGTH, "%s%s", dname_full, str );
            struct stat st;
            stat(filename, &st);
            int size = 0;
            size = st.st_size;

            if ( size > MAX_ANALYZE_FILE_SIZE )
            {
                printf("Skipping %s (size:%d)\n",filename,size);
                continue;
            }
            if ( ( strcmp ( str, "." ) == 0 ) || ( strcmp ( str, ".." )  == 0 ) ||
                ( ( strcmp ( member, "cmdlog/" ) == 0 ) && ( strstr ( str, "verbose" ) != NULL ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( ( strstr ( str, "cil" ) != NULL ) || ( strstr ( str, "hll" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( ( strstr ( str, ".bin" ) != NULL ) || ( strstr ( str, ".kern" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( ( strstr ( str, ".db" ) != NULL ) || ( strstr ( str, "policy." ) != NULL ) ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( ( strstr ( str, "lang_ext" ) != NULL ) || ( strstr ( str, ".pp" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( strstr ( str, "commit_num" ) != NULL ) ) ||
                ( ( strcmp ( member, "proc/" ) == 0 ) && ( ( strstr ( str, "register" ) != NULL ) || ( strstr ( str, "compact_memory" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "proc/" ) == 0 ) && ( ( strstr ( str, "flush" ) != NULL ) || ( strstr ( str, "kallsyms" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "proc/" ) == 0 ) && ( ( strstr ( str, "purge" ) != NULL ) || ( strstr ( str, "rebase" ) != NULL ) ) )||
                ( ( strcmp ( member, "var/log/messages" ) == 0 ) && ( strstr ( str, ".gz" ) != NULL ) ) || 
                ( ( strcmp ( member, "var/log/secure" ) == 0 ) && ( strstr ( str, ".gz" ) != NULL ) ) || 
                ( ( strcmp ( member, "var/" ) == 0 ) && (  strstr ( str, "journal" ) != NULL ) ) || 
                ( ( strcmp ( member, "var/") == 0 ) && ( strstr ( str, "messages" ) != NULL ) ) ||
                ( ( strcmp ( member, "var/") == 0 ) && ( ( strstr ( str, "sa" ) != NULL ) || ( strstr ( str, "crash" ) != NULL ) ) ) || 
                ( ( strcmp ( member, "var/") == 0 ) && ( strstr ( str, "nova" ) != NULL ) ) ||
                ( ( strcmp ( member, "sos_commands/networking/") == 0 ) && ( strstr ( str, "ethtool_-d" ) != NULL ) ) || 
                ( ( strcmp ( member, "sos_commands/") == 0 ) && ( strstr ( str, "journalctl" ) != NULL ) ) )
                continue;

            /* Here, we try to read files recursively */
            if (
                ( ( strcmp ( member, "etc/pki/" ) == 0 ) || 
                ( strcmp ( member, "etc/httpd/" ) == 0 ) ||
                ( strcmp ( member, "var/crash/" ) == 0 ) ||
                ( strcmp ( member, "proc/" ) == 0 ) ||
                ( strcmp ( member, "etc/udev/" ) == 0 ) ||
                ( strcmp ( member, "etc/systemd/system/" ) == 0 ) ||
                ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) || 
                ( strcmp ( member, "lib/" ) == 0 ) ||
                ( strcmp ( member, "etc/" ) == 0 ) || 
                ( strcmp ( member, "sos_commands/networking/" ) == 0 ) ||
                ( strcmp ( member, "dev/" ) == 0 ) || 
                ( strcmp ( member, "usr/" ) == 0 ) || 
                ( strcmp ( member, "var/" ) == 0 ) || 
                ( strcmp ( member, "sos_commands/" ) == 0 ) )
                &&
                /* try to read all files in the directory */
                ( ( recursive == 0 ) || ( recursive == 1 ) )
            )
            {
                if ( dp->d_type == DT_DIR )
                {
                    snprintf (full_path_plus_str, MAX_LINE_LENGTH, "%s%s/", dname_full, str );
                    /* call myself and read files in the directory */
                    printf("Reding files in the directory '%s'\n",full_path_plus_str);
                    read_analyze_dir ( member, full_path_plus_str, 1 );
                }
            }
            /* Here are members of above and has files in the rootdir of itself
             * do read etc/systemd/system/'s rootdir so, no need here
             * do read proc/'s rootdir so, no need here
             * do read sos_commands/networking/'s rootdir so, no need here
             */
            if (
                ( ( strcmp ( member, "etc/pki/" ) == 0 ) || 
                ( strcmp ( member, "etc/httpd/" ) == 0 ) || 
                ( strcmp ( member, "var/crash/" ) == 0 ) || 
                ( strcmp ( member, "etc/udev/" ) == 0 ) ||
                ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) || 
                ( strcmp ( member, "lib/" ) == 0 ) ||
                ( strcmp ( member, "etc/" ) == 0 ) || 
                ( strcmp ( member, "dev/" ) == 0 ) || 
                ( strcmp ( member, "usr/" ) == 0 ) || 
                ( strcmp ( member, "var/" ) == 0 ) || 
                ( strcmp ( member, "sos_commands/" ) == 0 ) )
                &&
                ( recursive == 0 )
                )
                continue;
            /*
             *  find files with name fname_part 
             */
            if ( strstr ( str, fname_part ) != NULL )
            {
                /* so, only fname_part files will remain */
                snprintf (read_path, MAX_LINE_LENGTH, "%s%s", dname_full, str );

                /* note that for the same directory, longest one will match first */
                if ( strstr ( read_path, "/boot/grub/" ) != 0 )
                    append_list ( &tmp_1_obj, read_path );
                else if ( strstr ( read_path, "/cmdlog/" ) != 0 )
                    append_list ( &tmp_2_obj, read_path );
                else if ( strstr ( read_path, "/etc/cron.d/" ) != 0 )
                    append_list ( &tmp_4_obj, read_path );
                else if ( strstr ( read_path, "/etc/default/" ) != 0 )
                    append_list ( &tmp_16_obj, read_path );
                else if ( strstr ( read_path, "/etc/host" ) != 0 )
                    append_list ( &tmp_19_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/httpd/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_13_obj, read_path );
                else if ( strstr ( read_path, "/etc/logrotate.d/" ) != 0 )
                    append_list ( &tmp_17_obj, read_path );
                else if ( strstr ( read_path, "/etc/modprobe.d/" ) != 0 )
                    append_list ( &tmp_18_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/pki/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_3_obj, read_path );
                else if ( strstr ( read_path, "/etc/sysconfig/network-scripts/ifcfg-" ) != 0 )
                    append_list ( &tmp_5_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/systemd/system/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_22_obj, read_path );
                else if ( strstr ( read_path, "/etc/systemd/" ) != 0 )
                    append_list ( &tmp_23_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/udev/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_20_obj, read_path );
                else if ( strstr ( read_path, "/etc/yum.repos.d/" ) != 0 )
                    append_list ( &tmp_21_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/boot/" ) != 0 )
                    append_list ( &tmp_12_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/logs/journalctl_--no-pager" ) != 0 )
                    append_list ( &tmp_9_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/networking/ethtool_-S" ) != 0 )
                    append_list ( &tmp_10_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/networking/ethtool_-i" ) != 0 )
                    append_list ( &tmp_11_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/networking/" ) != 0 )
                    append_list ( &tmp_30_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/abrt/" ) != 0 )
                    append_list ( &tmp_36_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/sar/" ) != 0 )
                    append_list ( &tmp_25_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/usb/" ) != 0 )
                    append_list ( &tmp_27_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/virsh/" ) != 0 )
                    append_list ( &tmp_26_obj, read_path );
                else if ( ( strstr ( read_path, "/usr/lib/systemd/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_24_obj, read_path );
                else if ( strstr ( read_path, "/var/crash/" ) != 0 )
                    append_list ( &tmp_15_obj, read_path );
                else if ( strstr ( read_path, "/var/log/messages" ) != 0 )
                    append_list ( &tmp_6_obj, read_path );
                else if ( strstr ( read_path, "/var/log/secure" ) != 0 )
                    append_list ( &tmp_7_obj, read_path );
                else if ( strstr ( read_path, "/var/log/audit/" ) != 0 )
                    append_list ( &tmp_8_obj, read_path );
                else if ( strstr ( read_path, "/var/spool/cron/" ) != 0 )
                    append_list ( &tmp_35_obj, read_path );

                /* reading everything stuff should be the last */
                else if ( ( strstr ( read_path, "/etc/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_29_obj, read_path );
                else if ( ( strstr ( read_path, "/dev/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_31_obj, read_path );
                else if ( ( strstr ( read_path, "/lib/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_28_obj, read_path );
                /* for proc/'s rootdir */
                else if ( strstr ( read_path, "/proc/" ) != 0 )
                    append_list ( &tmp_14_obj, read_path );
                else if ( ( strstr ( read_path, "/proc/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_14_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/" ) != 0 )
                    append_list ( &tmp_34_obj, read_path );
                else if ( ( strstr ( read_path, "/usr/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_32_obj, read_path );
                else if ( ( strstr ( read_path, "/var/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_33_obj, read_path );
                i++; /* needed here */
                str_arr_valid_size++;
                if ( str_arr_valid_size == MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR )
                    break;
            }
        }
    }
    /* close the directory */
    if ( var_crash_exists == 1 )
        closedir ( dir );

    return ( 0 );
}

int read_file_from_analyze_dir ( node **obj, const char *member )
{
    int files = 0;
    node *ptr_tmp = NULL;
    ptr_tmp = *obj;
    while ( ptr_tmp != NULL )
    {
        if ( strcmp ( ptr_tmp->_line, "" ) == 0 )
        {
            files ++;
            ptr_tmp = ptr_tmp->next;
            continue;
        }
        printf("Read '%s' \n",ptr_tmp->_line);
        read_file ( ptr_tmp->_line, member, files );
        files ++;
        ptr_tmp = ptr_tmp->next;
    }
    return ( 0 );
}

/* These are the items to be analyzed not statically nor checked by multi-lines */
static int bios_information = 0;
static int memory_array_information = 0;
static int memory_information = 0;

/* These are array numbers limits. */
int arr_max0 = 0;
int arr_max2 = 2;
int arr_max12 = 12;
int arr_max20 = 20;
const char *items_mcinfo_boot_grub_;
const char *items_mcinfo_cmdlog_;
const char *items_date;
const char *items_lsb_release;
const char *items_uname;
const char *items_hostname;
const char *items_uptime;
const char *items_proc_cpuinfo [ 12 ];
const char *items_root_anaconda_ks_cfg [ 12 ];
const char *items_dmidecode [ 12 ];
const char *items_lsmod [ 12 ];
const char *items_lspci [ 20 ];
const char *items_sos_commands_devices_udevadm_info___export_db [ 12 ];
const char *items_sos_commands_scsi_lsscsi;
const char *items_installed_rpms [ 12 ];
const char *items_df [ 2 ];
const char *items_vgdisplay;
const char *items_free;
const char *items_ip_addr;
const char *items_route;
const char *items_last [ 12 ];
const char *items_ps [ 12 ];
const char *items_lsof [ 12 ];
const char *items_netstat [ 12 ];
const char *items_etc_kdump_conf;
const char *items_etc_sysctl_conf;
const char *items_etc_rsyslog_conf;
const char *items_etc_sysconfig_network_scripts_ifcfg_;
const char *items_proc_meminfo [ 12 ];
const char *items_proc_interrupts;
const char *items_proc_net_dev;
const char *items_proc_net_sockstat;
const char *items_etc_logrotate_conf;
const char *items_etc_pki_;
const char *items_etc_cron_d_;
const char *items_var_log_dmesg;
const char *items_var_log_messages [ 20 ];
const char *items_var_log_secure [ 12 ];
const char *items_var_log_audit_ [ 12 ];
const char *items_sos_commands_kernel_sysctl__a [ 12 ];
const char *items_sos_commands_logs_journalctl___no_pager [ 20 ];
const char *items_sos_commands_networking_ethtool__S [ 12 ];
const char *items_sos_commands_networking_ethtool__i [ 12 ];
const char *items_sos_commands_boot_ [ 12 ];
const char *items_etc_httpd_;
const char *items_proc_;
const char *items_var_crash_;
const char *items_etc_default_;
const char *items_etc_logrotate_d_;
const char *items_etc_modprobe_d_;
const char *items_etc_host;
const char *items_etc_udev_;
const char *items_etc_yum_cfg;
const char *items_etc_yum_repos_d_;
const char *items_etc_systemd_system_;
const char *items_etc_systemd_;
const char *items_usr_lib_systemd_;
const char *items_sos_commands_sar_;
const char *items_sos_commands_virsh_;
const char *items_sos_commands_usb_;
const char *items_lib_;
const char *items_etc_;
const char *items_sos_commands_networking_;
const char *items_dev_;
const char *items_usr_;
const char *items_var_;
const char *items_sos_commands_;
const char *items_var_spool_cron_;
const char *items_sos_commands_abrt_ [ 12 ];

int read_file ( const char *file_name, const char *member, int files )
{
    char filename_mcinfo_boot_grub_ [ MAX_LINE_LENGTH ];
    char filename_mcinfo_boot_grub__curr [ MAX_LINE_LENGTH ];
    memset ( filename_mcinfo_boot_grub_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_mcinfo_boot_grub__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_mcinfo_cmdlog_ [ MAX_LINE_LENGTH ];
    char filename_mcinfo_cmdlog__curr [ MAX_LINE_LENGTH ];
    memset ( filename_mcinfo_cmdlog_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_mcinfo_cmdlog__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_pki_ [ MAX_LINE_LENGTH ];
    char filename_etc_pki__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_pki_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_pki__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_cron_d_ [ MAX_LINE_LENGTH ];
    char filename_etc_cron_d__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_cron_d_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_cron_d__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_sysconfig_network_scripts_ifcfg_ [ MAX_LINE_LENGTH ];
    char filename_etc_sysconfig_network_scripts_ifcfg__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_sysconfig_network_scripts_ifcfg_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_sysconfig_network_scripts_ifcfg__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_var_log_messages [ MAX_LINE_LENGTH ];
    char filename_var_log_messages_curr [ MAX_LINE_LENGTH ];
    memset ( filename_var_log_messages, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_var_log_messages_curr, '\0', MAX_LINE_LENGTH ); 
    char filename_var_log_secure [ MAX_LINE_LENGTH ];
    char filename_var_log_secure_curr [ MAX_LINE_LENGTH ];
    memset ( filename_var_log_secure, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_var_log_secure_curr, '\0', MAX_LINE_LENGTH ); 
    char filename_var_log_audit_ [ MAX_LINE_LENGTH ];
    char filename_var_log_audit__curr [ MAX_LINE_LENGTH ];
    memset ( filename_var_log_audit_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_var_log_audit__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_var_crash_ [ MAX_LINE_LENGTH ];
    char filename_var_crash__curr [ MAX_LINE_LENGTH ];
    memset ( filename_var_crash_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_var_crash__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_logs_journalctl___no_pager [ MAX_LINE_LENGTH ];
    char filename_sos_commands_logs_journalctl___no_pager_curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_logs_journalctl___no_pager, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_logs_journalctl___no_pager_curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_networking_ethtool__S [ MAX_LINE_LENGTH ];
    char filename_sos_commands_networking_ethtool__S_curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_networking_ethtool__S, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_networking_ethtool__S_curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_networking_ethtool__i [ MAX_LINE_LENGTH ];
    char filename_sos_commands_networking_ethtool__i_curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_networking_ethtool__i, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_networking_ethtool__i_curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_boot_ [ MAX_LINE_LENGTH ];
    char filename_sos_commands_boot__curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_boot_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_boot__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_httpd_ [ MAX_LINE_LENGTH ];
    char filename_etc_httpd__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_httpd_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_httpd__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_proc_ [ MAX_LINE_LENGTH ];
    char filename_proc__curr [ MAX_LINE_LENGTH ];
    memset ( filename_proc_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_proc__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_default_ [ MAX_LINE_LENGTH ];
    char filename_etc_default__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_default_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_default__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_logrotate_d_ [ MAX_LINE_LENGTH ];
    char filename_etc_logrotate_d__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_logrotate_d_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_logrotate_d__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_modprobe_d_ [ MAX_LINE_LENGTH ];
    char filename_etc_modprobe_d__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_modprobe_d_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_modprobe_d__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_host [ MAX_LINE_LENGTH ];
    char filename_etc_host_curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_host, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_host_curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_udev_ [ MAX_LINE_LENGTH ];
    char filename_etc_udev__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_udev_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_udev__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_yum_repos_d_ [ MAX_LINE_LENGTH ];
    char filename_etc_yum_repos_d__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_yum_repos_d_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_yum_repos_d__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_systemd_system_ [ MAX_LINE_LENGTH ];
    char filename_etc_systemd_system__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_systemd_system_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_systemd_system__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_systemd_ [ MAX_LINE_LENGTH ];
    char filename_etc_systemd__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_systemd_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc_systemd__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_usr_lib_systemd_ [ MAX_LINE_LENGTH ];
    char filename_usr_lib_systemd__curr [ MAX_LINE_LENGTH ];
    memset ( filename_usr_lib_systemd_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_usr_lib_systemd__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_sar_ [ MAX_LINE_LENGTH ];
    char filename_sos_commands_sar__curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_sar_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_sar__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_virsh_ [ MAX_LINE_LENGTH ];
    char filename_sos_commands_virsh__curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_virsh_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_virsh__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_usb_ [ MAX_LINE_LENGTH ];
    char filename_sos_commands_usb__curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_usb_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_usb__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_lib_ [ MAX_LINE_LENGTH ];
    char filename_lib__curr [ MAX_LINE_LENGTH ];
    memset ( filename_lib_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_lib__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_etc_ [ MAX_LINE_LENGTH ];
    char filename_etc__curr [ MAX_LINE_LENGTH ];
    memset ( filename_etc_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_etc__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_networking_ [ MAX_LINE_LENGTH ];
    char filename_sos_commands_networking__curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_networking_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_networking__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_dev_ [ MAX_LINE_LENGTH ];
    char filename_dev__curr [ MAX_LINE_LENGTH ];
    memset ( filename_dev_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_dev__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_usr_ [ MAX_LINE_LENGTH ];
    char filename_usr__curr [ MAX_LINE_LENGTH ];
    memset ( filename_usr_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_usr__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_var_ [ MAX_LINE_LENGTH ];
    char filename_var__curr [ MAX_LINE_LENGTH ];
    memset ( filename_var_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_var__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_ [ MAX_LINE_LENGTH ];
    char filename_sos_commands__curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_var_spool_cron_ [ MAX_LINE_LENGTH ];
    char filename_var_spool_cron__curr [ MAX_LINE_LENGTH ];
    memset ( filename_var_spool_cron_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_var_spool_cron__curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_abrt_ [ MAX_LINE_LENGTH ];
    char filename_sos_commands_abrt__curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_abrt_, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_abrt__curr, '\0', MAX_LINE_LENGTH ); 

    int file_name_len = ( int ) strlen ( file_name );
    char *hairline2 = "<<<<";
    char *blank_line = "";
    if ( file_name_len <= 0 )
    {
        printf("no file name supplied (%s): %d %s\n",file_name,file_name_len,strerror(errno));
        free_sosreport_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    if ( file_name_len > MAX_FULL_PATH_LENGTH )
    {
        printf("file name too long (%s): %d %s\n",file_name,file_name_len,strerror(errno));
        free_sosreport_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    FILE *fp;
    int lnr = 0, i = 0;
    char linebuf [ MAX_LINE_LENGTH ];
    char *line;

    /* when this function had been called from 'read_analyze_dir()', items should be set only once */
    if ( files == 0)
        set_token_to_item_arr ( file_name );

    /* open sosreport config file */
    if ( ( fp=fopen ( file_name, "r" ) ) == NULL )
    {
        printf("can't open file (%s): %s\n",file_name,strerror(errno));
        printf("Try set 'skip' to this member in config file.\n");
        printf("Also, please check lsb-release and use appropriate conf file in /usr/share/sosreport-analyzer.\n");
        printf("Skip '%s' and go on.\n",member);
        return ( 0 );
        /* free_sosreport_analyzer_obj ( ); */
        /* exit ( EXIT_FAILURE ); */
    }
    /* read file and parse lines */
    while ( fgets ( linebuf, sizeof ( linebuf ), fp ) != NULL )
    {
        lnr++;
        line = linebuf;
        int x = 0;

        /* strip newline */
        i = ( int ) strlen ( line );
        if ( (i > MAX_LINE_LENGTH ) || ( i <= 0 ) || ( line [ i - 1 ] != '\n' ) )
        {
            printf("%s:%d: line too long or last line missing newline. Skipping this line.\n",file_name,lnr);
            continue;
        }
        line [ i - 1 ] = '\0';
        /* ignore comment lines */
        if ( line [ 0 ] == '#' )
            continue;

        /* get item if any and append to object
         * this part should survive through while loop 
         *
         * note that this part is longest match
         *
         */
        /* ---- mcfinfo only stuff go here ---- */
        if ( strstr ( file_name, "/boot/grub/" ) != NULL )
        {
            snprintf ( filename_mcinfo_boot_grub__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_mcinfo_boot_grub_, filename_mcinfo_boot_grub__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_mcinfo_boot_grub_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            append_item_to_sos_line_obj ( line, "boot/grub/", items_mcinfo_boot_grub_ );
        }
        else if ( strstr ( file_name, "/cmdlog/" ) != NULL )
        {
            snprintf ( filename_mcinfo_cmdlog__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_mcinfo_cmdlog_, filename_mcinfo_cmdlog__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_mcinfo_cmdlog_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            append_item_to_sos_line_obj ( line, "cmdlog/", items_mcinfo_cmdlog_ );
        }
        /* ---- end mcfinfo only stuff go here ---- */
        /* ---- independent files go here ---- */
        else if ( ( strstr ( file_name, "/date" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "date", items_date );
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/df" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "df" ) ; x++ )
                append_item_to_sos_line_obj ( line, "df", items_df [ x ] );
        }
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/dmidecode" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "dmidecode" ) ; x++ )
                append_item_to_sos_line_obj ( line, "dmidecode", items_dmidecode [ x ] );
        }
        else if ( strstr ( file_name, "/etc/host" ) != NULL )
        {
            snprintf ( filename_etc_host_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_host, filename_etc_host_curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_host, MAX_LINE_LENGTH, "%s", file_name );
            append_item_to_sos_line_obj ( line, "etc/host", items_etc_host );
        }
        else if ( ( strstr ( file_name, "/etc/kdump.conf" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "etc/kdump.conf", items_etc_kdump_conf );
        else if ( ( strstr ( file_name, "/etc/sysctl.conf" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "etc/sysctl.conf", items_etc_sysctl_conf );
        else if ( ( strstr ( file_name, "/etc/rsyslog.conf" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "etc/rsyslog.conf", items_etc_rsyslog_conf );
        else if ( strstr ( file_name, "/etc/sysconfig/network-scripts/ifcfg-" ) != NULL )
        {
            snprintf ( filename_etc_sysconfig_network_scripts_ifcfg__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_sysconfig_network_scripts_ifcfg_, filename_etc_sysconfig_network_scripts_ifcfg__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_sysconfig_network_scripts_ifcfg_, MAX_LINE_LENGTH, "%s", file_name );
            append_item_to_sos_line_obj ( line, "etc/sysconfig/network-scripts/ifcfg-", items_etc_sysconfig_network_scripts_ifcfg_ );
        }
        else if ( strstr ( file_name, "/proc/meminfo" ) != NULL )
        {
            for ( x = 0; x < sosreport_analyzer_cfg->proc_meminfo.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "proc/meminfo", items_proc_meminfo [ x ] );
        }
        else if ( ( strstr ( file_name, "/free" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "free", items_free );
        else if ( ( strstr ( file_name, "/lsb-release" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "lsb-release", items_lsb_release );
        else if ( ( strstr ( file_name, "/uname" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "uname", items_uname );
        else if ( ( strstr ( file_name, "/hostname" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "hostname", items_hostname );
        else if ( ( strstr ( file_name, "/uptime" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "uptime", items_uptime );
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/last" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "last" ) ; x++ )
                append_item_to_sos_line_obj ( line, "last", items_last [ x ] );
        }
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/lsmod" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "lsmod" ) ; x++ )
                append_item_to_sos_line_obj ( line, "lsmod", items_lsmod [ x ] );
        }
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/lsof" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "lsof" ) ; x++ )
                append_item_to_sos_line_obj ( line, "lsof", items_lsof [ x ] );
        }
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/lspci" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "lspci" ) ; x++ )
                append_item_to_sos_line_obj ( line, "lspci", items_lspci [ x ] );
        }
        /* multiple items pattern */
        else if ( strstr ( file_name, "/proc/cpuinfo" ) != NULL )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "proc/cpuinfo" ) ; x++ )
                append_item_to_sos_line_obj ( line, "proc/cpuinfo", items_proc_cpuinfo [ x ] );
        }
        else if ( ( strstr ( file_name, "/root/anaconda-ks.cfg" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "root/anaconda-ks.cfg", items_root_anaconda_ks_cfg [ 0 ] );
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/sos_commands/devices/udevadm_info_--export-db" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "sos_commands/devices/udevadm_info_--export-db" ) ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/devices/udevadm_info_--export-db", items_sos_commands_devices_udevadm_info___export_db [ x ] );
        }
        else if ( ( strstr ( file_name, "/sos_commands/scsi/lsscsi" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "sos_commands/scsi/lsscsi", items_sos_commands_scsi_lsscsi );
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/installed-rpms" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "installed-rpms" ) ; x++ )
                append_item_to_sos_line_obj ( line, "installed-rpms", items_installed_rpms [ x ] );
        }
        else if ( ( strstr ( file_name, "/vgdisplay" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "vgdisplay", items_vgdisplay );
        else if ( ( strstr ( file_name, "/ip_addr" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "ip_addr", items_ip_addr );
        else if ( ( strstr ( file_name, "/route" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "route", items_route );
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/ps" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "ps" ) ; x++ )
                append_item_to_sos_line_obj ( line, "ps", items_ps [ x ] );
        }
        /* multiple items pattern */
        else if ( ( strstr ( file_name, "/netstat" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            for ( x = 0; x < get_item_numbers_of_member ( "netstat" ) ; x++ )
                append_item_to_sos_line_obj ( line, "netstat", items_netstat [ x ] );
        }
        else if ( strstr ( file_name, "/proc/interrupts" ) != NULL )
            append_item_to_sos_line_obj ( line, "proc/interrupts", items_proc_interrupts );
        else if ( ( strstr ( file_name, "/proc/net/dev" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "proc/net/dev", items_proc_net_dev );
        else if ( ( strstr ( file_name, "/proc/net/sockstat" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "proc/net/sockstat", items_proc_net_sockstat );
        else if ( ( strstr ( file_name, "/etc/logrotate.conf" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "etc/logrotate.conf", items_etc_logrotate_conf );
        /* ---- end independent files go here ---- */
        /* ---- etc go here ---- */
        else if ( ( strstr ( file_name, "/etc/pki/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_pki__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_pki_, filename_etc_pki__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_pki_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_pki_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/pki/", items_etc_pki_ );
        }
        else if ( ( strstr ( file_name, "/etc/cron.d/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_cron_d__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_cron_d_, filename_etc_cron_d__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_cron_d_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_cron_d_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/cron.d/", items_etc_cron_d_ );
        }
        else if ( ( strstr ( file_name, "/etc/default/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_default__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_default_, filename_etc_default__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_default_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_default_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/default/", items_etc_default_ );
        }
        else if ( ( strstr ( file_name, "/etc/httpd/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_httpd__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_httpd_, filename_etc_httpd__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_httpd_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_httpd_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/httpd/", items_etc_httpd_ );
        }
        else if ( ( strstr ( file_name, "/etc/logrotate.d/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_logrotate_d__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_logrotate_d_, filename_etc_logrotate_d__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_logrotate_d_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_logrotate_d_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/logrotate.d/", items_etc_logrotate_d_ );
        }
        else if ( ( strstr ( file_name, "/etc/modprobe.d/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_modprobe_d__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_modprobe_d_, filename_etc_modprobe_d__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_modprobe_d_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_modprobe_d_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/modprobe.d/", items_etc_modprobe_d_ );
        }
        else if ( ( strstr ( file_name, "/etc/udev/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_udev__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_udev_, filename_etc_udev__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_udev_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_udev_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/udev/", items_etc_udev_ );
        }
        else if ( ( strstr ( file_name, "/etc/yum.conf" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "etc/yum.conf", items_etc_yum_cfg );
        else if ( ( strstr ( file_name, "/etc/yum.repos.d/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_yum_repos_d__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_yum_repos_d_, filename_etc_yum_repos_d__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_yum_repos_d_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_yum_repos_d_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/yum.repos.d/", items_etc_yum_repos_d_ );
        }
        else if ( ( strstr ( file_name, "/etc/systemd/system/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_systemd_system__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_systemd_system_, filename_etc_systemd_system__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_systemd_system_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_systemd_system_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/systemd/system/", items_etc_systemd_system_ );
        }
        else if ( ( strstr ( file_name, "/etc/systemd/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_systemd__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_systemd_, filename_etc_systemd__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_systemd_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_systemd_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/systemd/", items_etc_systemd_ );
        }
        /* ---- end etc go here ---- */
        /* ---- sos_commands go here ---- */
        else if ( strstr ( file_name, "/sos_commands/abrt/" ) != NULL )
        {
            snprintf ( filename_sos_commands_abrt__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_abrt_, filename_sos_commands_abrt__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_sos_commands_abrt_, MAX_LINE_LENGTH, "%s", file_name );
            /* multiple items pattern */
            for ( x = 0; x < get_item_numbers_of_member ( "sos_commands/abrt/" ) ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/abrt/", items_sos_commands_abrt_ [ x ] );
        }
        else if ( strstr ( file_name, "/sos_commands/boot/" ) != NULL )
        {
            snprintf ( filename_sos_commands_boot__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_boot_, filename_sos_commands_boot__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_sos_commands_boot_, MAX_LINE_LENGTH, "%s", file_name );
            /* multiple items pattern */
            for ( x = 0; x < get_item_numbers_of_member ( "sos_commands/boot/" ) ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/boot/", items_sos_commands_boot_ [ x ] );
        }
        else if ( ( strstr ( file_name, "/sos_commands/kernel/sysctl_-a" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            /* multiple items pattern */
            for ( x = 0; x < get_item_numbers_of_member ( "sos_commands/kernel/sysctl_-a" ) ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/kernel/sysctl_-a", items_sos_commands_kernel_sysctl__a [ x ] );
        }
        else if ( ( strstr ( file_name, "/sos_commands/logs/journalctl_--no-pager" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf (filename_sos_commands_logs_journalctl___no_pager_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_logs_journalctl___no_pager, filename_sos_commands_logs_journalctl___no_pager_curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf ( filename_sos_commands_logs_journalctl___no_pager, MAX_LINE_LENGTH, "%s", file_name );
            /* multiple items pattern */
            for ( x = 0; x < get_item_numbers_of_member ( "sos_commands/logs/journalctl_--no-pager" ) ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/logs/journalctl_--no-pager", items_sos_commands_logs_journalctl___no_pager [ x ] );
        }
        else if ( ( strstr ( file_name, "/sos_commands/networking/ethtool_-S" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf (filename_sos_commands_networking_ethtool__S_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_networking_ethtool__S, filename_sos_commands_networking_ethtool__S_curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf ( filename_sos_commands_networking_ethtool__S, MAX_LINE_LENGTH, "%s", file_name );
            /* multiple items pattern */
            for ( x = 0; x < get_item_numbers_of_member ( "sos_commands/networking/ethtool_-S" ) ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/networking/ethtool_-S", items_sos_commands_networking_ethtool__S [ x ] );
        }
        else if ( ( strstr ( file_name, "/sos_commands/networking/ethtool_-i" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf (filename_sos_commands_networking_ethtool__i_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_networking_ethtool__i, filename_sos_commands_networking_ethtool__i_curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf ( filename_sos_commands_networking_ethtool__i, MAX_LINE_LENGTH, "%s", file_name );
            /* multiple items pattern */
            for ( x = 0; x < get_item_numbers_of_member ( "sos_commands/networking/ethtool_-i" ) ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/networking/ethtool_-i", items_sos_commands_networking_ethtool__i [ x ] );
        }
        else if ( ( strstr ( file_name, "/sos_commands/networking/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_sos_commands_networking__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_networking_, filename_sos_commands_networking__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_sos_commands_networking_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_sos_commands_networking_ != NULL )
                append_item_to_sos_line_obj ( line, "sos_commands/networking/", items_sos_commands_networking_ );
        }
        else if ( ( strstr ( file_name, "/sos_commands/sar/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_sos_commands_sar__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_sar_, filename_sos_commands_sar__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_sos_commands_sar_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_sos_commands_sar_ != NULL )
                append_item_to_sos_line_obj ( line, "sos_commands/sar/", items_sos_commands_sar_ );
        }
        else if ( ( strstr ( file_name, "/sos_commands/usb/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_sos_commands_usb__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_usb_, filename_sos_commands_usb__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_sos_commands_usb_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_sos_commands_usb_ != NULL )
                append_item_to_sos_line_obj ( line, "sos_commands/usb/", items_sos_commands_usb_ );
        }
        else if ( ( strstr ( file_name, "/sos_commands/virsh/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_sos_commands_virsh__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_virsh_, filename_sos_commands_virsh__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_sos_commands_virsh_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_sos_commands_virsh_ != NULL )
                append_item_to_sos_line_obj ( line, "sos_commands/virsh/", items_sos_commands_virsh_ );
        }
        /* ---- end sos_commands go here ---- */
        /* ---- usr go here ---- */
        else if ( ( strstr ( file_name, "/usr/lib/systemd/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_usr_lib_systemd__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_usr_lib_systemd_, filename_usr_lib_systemd__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_usr_lib_systemd_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_usr_lib_systemd_ != NULL )
                append_item_to_sos_line_obj ( line, "usr_lib/systemd/", items_usr_lib_systemd_ );
        }
        /* ---- end usr go here ---- */
        /* ---- var go here ---- */
        else if ( ( strstr ( file_name, "/var/crash/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_var_crash__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_var_crash_, filename_var_crash__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_var_crash_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_var_crash_ != NULL )
                append_item_to_sos_line_obj ( line, "var/crash/", items_var_crash_ );
        }
        else if ( strstr ( file_name, "/var/log/audit/" ) != NULL )
        {
            snprintf ( filename_var_log_audit__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_var_log_audit_, filename_var_log_audit__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_var_log_audit_, MAX_LINE_LENGTH, "%s", file_name );
            /* multiple items pattern */
            for ( x = 0; x < get_item_numbers_of_member ( "var/log/audit/" ) ; x++ )
                append_item_to_sos_line_obj ( line, "var/log/audit/", items_var_log_audit_ [ x ] );
        }
        else if ( strstr ( file_name, "/var/log/dmesg" ) != NULL )
            append_item_to_sos_line_obj ( line, "var/log/dmesg", items_var_log_dmesg );
        else if ( strstr ( file_name, "/var/log/messages" ) != NULL )
        {
            snprintf ( filename_var_log_messages_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_var_log_messages, filename_var_log_messages_curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_var_log_messages, MAX_LINE_LENGTH, "%s", file_name );
            /* multiple items pattern */
            for ( x = 0; x < get_item_numbers_of_member ( "var/log/messages" ) ; x++ )
                append_item_to_sos_line_obj ( line, "var/log/messages", items_var_log_messages [ x ] );
        }
        else if ( strstr ( file_name, "/var/log/secure" ) != NULL )
        {
            snprintf ( filename_var_log_secure_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_var_log_secure, filename_var_log_secure_curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_var_log_secure, MAX_LINE_LENGTH, "%s", file_name );
            /* multiple items pattern */
            for ( x = 0; x < get_item_numbers_of_member ( "var/log/secure" ) ; x++ )
                append_item_to_sos_line_obj ( line, "var/log/secure", items_var_log_secure [ x ] );
        }
        else if ( ( strstr ( file_name, "/var/spool/cron/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_var_spool_cron__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_var_spool_cron_, filename_var_spool_cron__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_var_spool_cron_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_var_spool_cron_ != NULL )
                append_item_to_sos_line_obj ( line, "var/spool/cron/", items_var_spool_cron_ );
        }
        /* ---- end var go here ---- */
        /* ---- read everything stuff should go here ---- */
        else if ( ( strstr ( file_name, "/dev/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_dev__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_dev_, filename_dev__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_dev_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_dev_ != NULL )
                append_item_to_sos_line_obj ( line, "dev/", items_dev_ );
        }
        else if ( ( strstr ( file_name, "/etc/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_, filename_etc__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_etc_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_etc_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/", items_etc_ );
        }
        else if ( ( strstr ( file_name, "/lib/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_lib__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_lib_, filename_lib__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_lib_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_lib_ != NULL )
                append_item_to_sos_line_obj ( line, "lib/", items_lib_ );
        }
        else if ( ( strstr ( file_name, "/proc/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_proc__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_proc_, filename_proc__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_proc_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_proc_ != NULL )
                append_item_to_sos_line_obj ( line, "proc/", items_proc_ );
        }
        else if ( ( strstr ( file_name, "/sos_commands/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_sos_commands__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_, filename_sos_commands__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_sos_commands_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_sos_commands_ != NULL )
                append_item_to_sos_line_obj ( line, "sos_commands/", items_sos_commands_ );
        }
        else if ( ( strstr ( file_name, "/usr/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_usr__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_usr_, filename_usr__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_usr_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_usr_ != NULL )
                append_item_to_sos_line_obj ( line, "usr/", items_usr_ );
        }
        else if ( ( strstr ( file_name, "/var/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_var__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_var_, filename_var__curr) != 0 )
            {
                append_list ( &sos_line_obj, blank_line );
                append_list ( &sos_line_obj, hairline2 );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, blank_line );
            }
            snprintf (filename_var_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' because item is 'all' here. 
             */
            if ( items_var_ != NULL )
                append_item_to_sos_line_obj ( line, "var/", items_var_ );
        }
        /* ---- end read everything stuff should go here ---- */
        else
            break;
        /* strip trailing spaces */
        for ( i--; ( i > 0 ) && isspace ( line [ i -1 ] ) ; i-- )
            line [ i -1 ] = '\0';
    }
    /* after reading all lines, close the file pointer */
    fclose ( fp );

    return ( 0 );
}

void set_token_to_item_arr ( const char *file_name )
{
    /* initialized item numbers of member here */
    init_item_numbers_of_member ( );

    int i = 0;

    /* ### FIX ME - make this function for better summary */
    const char s [ 8 ] = " \t\n\r"; /* this is the delimiter */
    char *token = NULL;
    /*
     * ### FIX ME
     * file_name should be excluded directory of given by -D 
     */
    /* ---- mcfinfo only stuff go here ---- */
    /* Remember always that this part is the longest match */
    /* member boot/grub/ */
    if ( ( strstr ( file_name, "/boot/grub/" ) != NULL ) && ( member_item_exists ( "boot/grub/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->mcinfo_boot_grub_.member, s );
        items_mcinfo_boot_grub_ = token;
    }
    /* member cmdlog */
    else if ( ( strstr ( file_name, "/cmdlog/" ) != NULL ) && ( member_item_exists ( "cmdlog/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->mcinfo_cmdlog_.member, s );
        items_mcinfo_cmdlog_ = token;
    }
    /* ---- end mcfinfo only stuff go here ---- */
    /* ---- independent files go here ---- */
    /* Remember always that this part is the longest match */
    /* member date */
    else if ( ( strstr ( file_name, "/date" ) != NULL ) && ( member_item_exists ( "date" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->date.member, s );
        items_date = token;
    }
    /* member df */
    else if ( ( strstr ( file_name, "/df" ) != NULL ) && ( member_item_exists ( "df" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->df.member, s );
        items_df [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->df.item_num > arr_max2 )
            {
                printf("can't set items over %d for df\n",arr_max2);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_df  [ i ] = token;
        }
        set_item_numbers_of_member ( "df", i); 
    }
    /* member dmidecode */
    else if ( ( strstr ( file_name, "/dmidecode" ) != NULL ) && ( member_item_exists ( "dmidecode" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->dmidecode.member, s );
        items_dmidecode [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->dmidecode.item_num > arr_max12 )
            {
                printf("can't set items over %d for dmidecode\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_dmidecode  [ i ] = token;
        }
        set_item_numbers_of_member ( "dmidecode", i); 
    }
    /* member free */
    else if ( ( strstr ( file_name, "/free" ) != NULL ) && ( member_item_exists ( "free" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->free.member, s );
        items_free = token;
    }
    /* member hostname */
    else if ( ( strstr ( file_name, "/hostname" ) != NULL ) && ( member_item_exists ( "hostname" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->hostname.member, s );
        items_hostname = token;
    }
    /* member installed-rpms */
    else if ( ( strstr ( file_name, "/installed-rpms" ) != NULL ) && ( member_item_exists ( "installed-rpms" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->installed_rpms.member, s );
        items_installed_rpms [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->installed_rpms.item_num > arr_max12 )
            {
                printf("can't set items over %d for installed-rpms\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_installed_rpms  [ i ] = token;
        }
        set_item_numbers_of_member ( "installed-rpms", i); 
    }
    /* member ip_addr */
    else if ( ( strstr ( file_name, "/ip_addr" ) != NULL ) && ( member_item_exists ( "ip_addr" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->ip_addr.member, s );
        items_ip_addr = token;
    }
    /* member last */
    else if ( ( strstr ( file_name, "/last" ) != NULL ) && ( member_item_exists ( "last" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->last.member, s );
        items_last [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->last.item_num > arr_max12 )
            {
                printf("can't set items over %d for last\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_last  [ i ] = token;
        }
        set_item_numbers_of_member ( "last", i); 
    }
    /* member lsb_release */
    else if ( ( strstr ( file_name, "/lsb-release" ) != NULL ) && ( member_item_exists ( "lsb-release" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lsb_release.member, s );
        items_lsb_release = token;
    }
    /* member lsmod */
    else if ( ( strstr ( file_name, "/lsmod" ) != NULL ) && ( member_item_exists ( "lsmod" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lsmod.member, s );
        items_lsmod [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->lsmod.item_num > arr_max12 )
            {
                printf("can't set items over %d for lsmod\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_lsmod  [ i ] = token;
        }
        set_item_numbers_of_member ( "lsmod", i); 
    }
    /* member lsof */
    else if ( ( strstr ( file_name, "/lsof" ) != NULL ) && ( member_item_exists ( "lsof" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lsof.member, s );
        items_lsof [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->lsof.item_num > arr_max12 )
            {
                printf("can't set items over %d for lsof\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_lsof  [ i ] = token;
        }
        set_item_numbers_of_member ( "lsof", i); 
    }
    /* member lspci */
    else if ( ( strstr ( file_name, "/lspci" ) != NULL ) && ( member_item_exists ( "lspci" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lspci.member, s );
        items_lspci [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->lspci.item_num > arr_max20 )
            {
                printf("can't set items over %d for lspci\n",arr_max20);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_lspci  [ i ] = token;
        }
        set_item_numbers_of_member ( "lspci", i); 
    }
    /* member netstat */
    else if ( ( strstr ( file_name, "/netstat" ) != NULL ) && ( member_item_exists ( "netstat" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->netstat.member, s );
        items_netstat [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->netstat.item_num > arr_max12 )
            {
                printf("can't set items over %d for netstat\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_netstat  [ i ] = token;
        }
        set_item_numbers_of_member ( "netstat", i); 
    }
    /* member uname */
    else if ( ( strstr ( file_name, "/uname" ) != NULL ) && ( member_item_exists ( "uname" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->uname.member, s );
        items_uname = token;
    }
    /* member uptime */
    else if ( ( strstr ( file_name, "/uptime" ) != NULL ) && ( member_item_exists ( "uptime" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->uptime.member, s );
        items_uptime = token;
    }
    /* member vgdisplay */
    else if ( ( strstr ( file_name, "/vgdisplay" ) != NULL ) && ( member_item_exists ( "vgdisplay" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->vgdisplay.member, s );
        items_vgdisplay = token;
    }
    /* member route */
    else if ( ( strstr ( file_name, "/route" ) != NULL ) && ( member_item_exists ( "route" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->route.member, s );
        items_route = token;
    }
    /* member ps */
    else if ( ( strstr ( file_name, "/ps" ) != NULL ) && ( member_item_exists ( "ps" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->ps.member, s );
        items_ps [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->ps.item_num > arr_max12 )
            {
                printf("can't set items over %d for ps\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_ps  [ i ] = token;
        }
        set_item_numbers_of_member ( "ps", i); 
    }
    /* member etc/host */
    else if ( ( strstr ( file_name, "/etc/host" ) != NULL ) && ( member_item_exists ( "etc/host" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_host.member, s );
        items_etc_host = token;
    }
    /* member etc/kdump.conf */
    else if ( ( strstr ( file_name, "/etc/kdump.conf" ) != NULL ) && ( member_item_exists ( "etc/kdump.conf" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_kdump_conf.member, s );
        items_etc_kdump_conf = token;
    }
    /* member etc/logrotate.conf */
    else if ( ( strstr ( file_name, "/etc/logrotate.conf" ) != NULL ) && ( member_item_exists ( "etc/logrotate.conf" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_logrotate_conf.member, s );
        items_etc_logrotate_conf = token;
    }
    /* member etc/sysctl.conf */
    else if ( ( strstr ( file_name, "/etc/sysctl.conf" ) != NULL ) && ( member_item_exists ( "etc/sysctl.conf" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_sysctl_conf.member, s );
        items_etc_sysctl_conf = token;
    }
    /* member etc/rsyslog.conf */
    else if ( ( strstr ( file_name, "/etc/rsyslog.conf" ) != NULL ) && ( member_item_exists ( "etc/rsyslog.conf" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_rsyslog_conf.member, s );
        items_etc_rsyslog_conf = token;
    }
    /* member etc/sysconfig/network-scripts/ifcfg- */
    else if ( ( strstr ( file_name, "/etc/sysconfig/network-scripts/ifcfg-" ) != NULL ) && ( member_item_exists ( "etc/sysconfig/network-scripts/ifcfg-" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.member, s );
        items_etc_sysconfig_network_scripts_ifcfg_ = token;
    }
    /* member etc/yum.conf */
    else if ( ( strstr ( file_name, "/etc/yum.conf" ) != NULL ) && ( member_item_exists ( "etc/yum.conf" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_yum_conf.member, s );
        items_etc_yum_cfg = token;
    }
    /* member proc/cpuinfo */
    else if ( ( strstr ( file_name, "/proc/cpuinfo" ) != NULL ) && ( member_item_exists ( "proc/cpuinfo" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_cpuinfo.member, s );
        items_proc_cpuinfo [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->proc_cpuinfo.item_num > arr_max12 )
            {
                printf("can't set items over %d for proc/cpuinfo\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_proc_cpuinfo  [ i ] = token;
        }
        set_item_numbers_of_member ( "proc/cpuinfo", i); 
    }
    /* member proc/meminfo */
    else if ( ( strstr ( file_name, "/proc/meminfo" ) != NULL ) && ( member_item_exists ( "proc/meminfo" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_meminfo.member, s );
        items_proc_meminfo [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->proc_meminfo.item_num > arr_max12 )
            {
                printf("can't set items over %d for proc/meminfo\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_proc_meminfo  [ i ] = token;
        }
        set_item_numbers_of_member ( "proc/meminfo", i); 
    }
    /* member proc/interrupts */
    else if ( ( strstr ( file_name, "/proc/interrupts" ) != NULL ) && ( member_item_exists ( "proc/interrupts" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_interrupts.member, s );
        items_proc_interrupts = token;
    }
    /* member proc/net/dev */
    else if ( ( strstr ( file_name, "/proc/net/dev" ) != NULL ) && ( member_item_exists ( "proc/net/dev" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_net_dev.member, s );
        items_proc_net_dev = token;
    }
    /* member proc/net/sockstat */
    else if ( ( strstr ( file_name, "/proc/net/sockstat" ) != NULL ) && ( member_item_exists ( "proc/net/sockstat" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_net_sockstat.member, s );
        items_proc_net_sockstat = token;
    }
    /* member root/anaconda-ks.cfg */
    else if ( ( strstr ( file_name, "/root/anaconda-ks.cfg" ) != NULL ) && ( member_item_exists ( "root/anaconda-ks.cfg" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->root_anaconda_ks_cfg.member, s );
        items_root_anaconda_ks_cfg [ 0 ] = token;
    }
    /* member sos_commands/devices/udevadm_info_--export-db */
    else if ( ( strstr ( file_name, "/sos_commands/devices/udevadm_info_--export-db" ) != NULL ) && ( member_item_exists ( "sos_commands/devices/udevadm_info_--export-db" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.member, s );
        items_sos_commands_devices_udevadm_info___export_db [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.item_num > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/devices/udevadm_info_--export-db\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_sos_commands_devices_udevadm_info___export_db  [ i ] = token;
        }
        set_item_numbers_of_member ( "sos_commands/devices/udevadm_info_--export-db", i); 
    }
    /* member sos_commands/scsi/lsscsi */
    else if ( ( strstr ( file_name, "/sos_commands/scsi/lsscsi" ) != NULL ) && ( member_item_exists ( "sos_commands/scsi/lsscsi" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.member, s );
        items_sos_commands_scsi_lsscsi = token;
    }
    /* ---- end independent files go here ---- */
    /* ---- etc go here ---- */
    /* Remember always that this part is the longest match */
    /* member etc/cron.d/ */
    else if ( ( strstr ( file_name, "/etc/cron.d/" ) != NULL ) && ( member_item_exists ( "etc/cron.d/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_cron_d_.member, s );
        items_etc_cron_d_ = token;
    }
    /* member etc/httpd/ */
    else if ( ( strstr ( file_name, "/etc/httpd/" ) != NULL ) && ( member_item_exists ( "etc/httpd/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_httpd_.member, s );
        items_etc_httpd_ = token;
    }
    /* member etc/default/ */
    else if ( ( strstr ( file_name, "/etc/default/" ) != NULL ) && ( member_item_exists ( "etc/default/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_default_.member, s );
        items_etc_default_ = token;
    }
    /* member etc/logrotate.d/ */
    else if ( ( strstr ( file_name, "/etc/logrotate.d/" ) != NULL ) && ( member_item_exists ( "etc/logrotate.d/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_logrotate_d_.member, s );
        items_etc_logrotate_d_ = token;
    }
    /* member etc/modprobe.d/ */
    else if ( ( strstr ( file_name, "/etc/modprobe.d/" ) != NULL ) && ( member_item_exists ( "etc/modprobe.d/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_modprobe_d_.member, s );
        items_etc_modprobe_d_ = token;
    }
    /* member etc/pki/ */
    else if ( ( strstr ( file_name, "/etc/pki/" ) != NULL ) && ( member_item_exists ( "etc/pki/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_pki_.member, s );
        items_etc_pki_ = token;
    }
    /* member etc/udev/ */
    else if ( ( strstr ( file_name, "/etc/udev/" ) != NULL ) && ( member_item_exists ( "etc/udev/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_udev_.member, s );
        items_etc_udev_ = token;
    }
    /* member etc/systemd/system/ */
    else if ( ( strstr ( file_name, "/etc/systemd/system/" ) != NULL ) && ( member_item_exists ( "etc/systemd/system/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_systemd_system_.member, s );
        items_etc_systemd_system_ = token;
    }
    /* member etc/systemd/ */
    else if ( ( strstr ( file_name, "/etc/systemd/" ) != NULL ) && ( member_item_exists ( "etc/systemd/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_systemd_.member, s );
        items_etc_systemd_ = token;
    }
    /* member etc/yum.repos.d/ */
    else if ( ( strstr ( file_name, "/etc/yum.repos.d/" ) != NULL ) && ( member_item_exists ( "etc/yum.repos.d/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_yum_repos_d_.member, s );
        items_etc_yum_repos_d_ = token;
    }
    /* ---- end etc go here ---- */
    /* ---- usr go here ---- */
    /* Remember always that this part is the longest match */
    /* member usr/lib/systemd/ */
    else if ( ( strstr ( file_name, "/usr/lib/systemd/" ) != NULL ) && ( member_item_exists ( "usr/lib/systemd/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->usr_lib_systemd_.member, s );
        items_usr_lib_systemd_ = token;
    }
    /* ---- end usr go here ---- */
    /* ---- sos_commands go here ---- */
    /* Remember always that this part is the longest match */
    /* member sos_commands/abrt/ */
    else if ( ( strstr ( file_name, "/sos_commands/abrt/" ) != NULL ) && ( member_item_exists ( "sos_commands/abrt/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_abrt_.member, s );
        items_sos_commands_abrt_ [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->sos_commands_abrt_.item_num > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/abrt/\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_sos_commands_abrt_  [ i ] = token;
        }
        set_item_numbers_of_member ( "sos_commands/abrt/", i); 
    }
    /* member sos_commands/boot/ */
    else if ( ( strstr ( file_name, "/sos_commands/boot/" ) != NULL ) && ( member_item_exists ( "sos_commands/boot/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_boot_.member, s );
        items_sos_commands_boot_ [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->sos_commands_boot_.item_num > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/boot/\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_sos_commands_boot_  [ i ] = token;
        }
        set_item_numbers_of_member ( "sos_commands/boot/", i); 
    }
    /* member sos_commands/kernel/sysctl_-a */
    else if ( ( strstr ( file_name, "/sos_commands/kernel/sysctl_-a" ) != NULL ) && ( member_item_exists ( "sos_commands/kernel/sysctl_-a" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.member, s );
        items_sos_commands_kernel_sysctl__a [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_num > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/kernel/sysctl_-a\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_sos_commands_kernel_sysctl__a  [ i ] = token;
        }
        set_item_numbers_of_member ( "sos_commands/kernel/sysctl_-a", i); 
    }
    /* member sos_commands/logs/journalctl_--no-pager */
    else if ( ( strstr ( file_name, "/sos_commands/logs/journalctl_--no-pager" ) != NULL ) && ( member_item_exists ( "sos_commands/logs/journalctl_--no-pager" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.member, s );
        items_sos_commands_logs_journalctl___no_pager [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_num > arr_max20 )
            {
                printf("can't set items over %d for sos_commands/logs/journalctl_--no-pager\n",arr_max20);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_sos_commands_logs_journalctl___no_pager  [ i ] = token;
        }
        set_item_numbers_of_member ( "sos_commands/logs/journalctl_--no-pager", i); 
    }
    /* member sos_commands/networking/ethtool_-S */
    else if ( ( strstr ( file_name, "/sos_commands/networking/ethtool_-S" ) != NULL ) && ( member_item_exists ( "sos_commands/networking/ethtool_-S" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.member, s );
        items_sos_commands_networking_ethtool__S [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_num > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/networking/ethtool_-S\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_sos_commands_networking_ethtool__S  [ i ] = token;
        }
        set_item_numbers_of_member ( "sos_commands/networking/ethtool_-S", i); 
    }
    /* member sos_commands/networking/ethtool_-i */
    else if ( ( strstr ( file_name, "/sos_commands/networking/ethtool_-i" ) != NULL ) && ( member_item_exists ( "sos_commands/networking/ethtool_-i" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.member, s );
        items_sos_commands_networking_ethtool__i [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_num > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/networking/ethtool_-i\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_sos_commands_networking_ethtool__i  [ i ] = token;
        }
        set_item_numbers_of_member ( "sos_commands/networking/ethtool_-i", i); 
    }
    /* member sos_commands/networking/ */
    else if ( ( strstr ( file_name, "/sos_commands/networking/" ) != NULL ) && ( member_item_exists ( "sos_commands/networking/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_networking_.member, s );
        items_sos_commands_networking_ = token;
    }
    /* member sos_commands/sar/ */
    else if ( ( strstr ( file_name, "/sos_commands/sar/" ) != NULL ) && ( member_item_exists ( "sos_commands/sar/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_sar_.member, s );
        items_sos_commands_sar_ = token;
    }
    /* member sos_commands/usb/ */
    else if ( ( strstr ( file_name, "/sos_commands/usb/" ) != NULL ) && ( member_item_exists ( "sos_commands/usb/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_usb_.member, s );
        items_sos_commands_usb_ = token;
    }
    /* member sos_commands/virsh/ */
    else if ( ( strstr ( file_name, "/sos_commands/virsh/" ) != NULL ) && ( member_item_exists ( "sos_commands/virsh/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_virsh_.member, s );
        items_sos_commands_virsh_ = token;
    }
    /* ---- end sos_commands go here ---- */
    /* ---- var go here ---- */
    /* Remember always that this part is the longest match */
    /* member var/crash/ */
    else if ( ( strstr ( file_name, "/var/crash/" ) != NULL ) && ( member_item_exists ( "var/crash/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_crash_.member, s );
        items_var_crash_ = token;
    }
    /* member var/spool/cron/ */
    else if ( ( strstr ( file_name, "/var/spool/cron/" ) != NULL ) && ( member_item_exists ( "var/spool/cron/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_spool_cron_.member, s );
        items_var_spool_cron_ = token;
    }
    /* member var/log/dmesg */
    else if ( ( strstr ( file_name, "/var/log/dmesg" ) != NULL ) && ( member_item_exists ( "var/log/dmesg" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_log_dmesg.member, s );
        items_var_log_dmesg = token;
    }
    /* member var/log/messages */
    else if ( ( strstr ( file_name, "/var/log/messages" ) != NULL ) && ( member_item_exists ( "var/log/messages" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_log_messages.member, s );
        items_var_log_messages [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->var_log_messages.item_num > arr_max20 )
            {
                printf("can't set items over %d for var/log/messages\n",arr_max20);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_var_log_messages  [ i ] = token;
        }
        set_item_numbers_of_member ( "var/log/messages", i); 
    }
    /* member var/log/secure */
    else if ( ( strstr ( file_name, "/var/log/secure" ) != NULL ) && ( member_item_exists ( "var/log/secure" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_log_secure.member, s );
        items_var_log_secure [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->var_log_secure.item_num > arr_max12 )
            {
                printf("can't set items over %d for var/log/secure\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_var_log_secure  [ i ] = token;
        }
        set_item_numbers_of_member ( "var/log/secure", i); 
    }
    /* member var/log/audit/ */
    else if ( ( strstr ( file_name, "/var/log/audit/" ) != NULL ) && ( member_item_exists ( "var/log/audit/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_log_audit_.member, s );
        items_var_log_audit_ [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->var_log_audit_.item_num > arr_max12 )
            {
                printf("can't set items over %d for var/log/audit/\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            items_var_log_audit_  [ i ] = token;
        }
        set_item_numbers_of_member ( "var/log/audit/", i); 
    }
    /* ---- end var go here ---- */
    /* ---- read everything stuff go here ---- */
    /* Remember always that this part is the longest match */
    /* member dev/ */
    else if ( ( strstr ( file_name, "/dev/" ) != NULL ) && ( member_item_exists ( "dev/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->dev_.member, s );
        items_dev_ = token;
    }
    /* member etc/ */
    else if ( ( strstr ( file_name, "/etc/" ) != NULL ) && ( member_item_exists ( "etc/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_.member, s );
        items_etc_ = token;
    }
    /* member lib/ */
    else if ( ( strstr ( file_name, "/lib/" ) != NULL ) && ( member_item_exists ( "lib/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lib_.member, s );
        items_lib_ = token;
    }
    /* member proc/ */
    else if ( ( strstr ( file_name, "/proc/" ) != NULL ) && ( member_item_exists ( "proc/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_.member, s );
        items_proc_ = token;
    }
    /* member sos_commands/ */
    else if ( ( strstr ( file_name, "/sos_commands/" ) != NULL ) && ( member_item_exists ( "sos_commands/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_.member, s );
        items_sos_commands_ = token;
    }
    /* member usr/ */
    else if ( ( strstr ( file_name, "/usr/" ) != NULL ) && ( member_item_exists ( "usr/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->usr_.member, s );
        items_usr_ = token;
    }
    /* member var/ */
    else if ( ( strstr ( file_name, "/var/" ) != NULL ) && ( member_item_exists ( "var/" ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_.member, s );
        items_var_ = token;
    }
    /* ---- end read everything stuff go here ---- */
}

void read_file_pre ( const char *member, const char *dir_name )
{
    char str_tmp [ MAX_LINE_LENGTH - 6 ]; 
    memset ( str_tmp, '\0', MAX_LINE_LENGTH - 6 ); 
    char str_tmp2 [ MAX_LINE_LENGTH ]; 
    memset ( str_tmp2, '\0', MAX_LINE_LENGTH ); 
    char result_tmp_pre [ MAX_LINE_LENGTH - 21 ]; 
    memset ( result_tmp_pre, '\0', MAX_LINE_LENGTH - 21 ); 
    char result_tmp [ MAX_LINE_LENGTH ]; 
    memset ( result_tmp, '\0', MAX_LINE_LENGTH ); 

    char str_tmp3 [ MAX_LINE_LENGTH ]; 
    memset ( str_tmp3, '\0', MAX_LINE_LENGTH ); 
    int i = 0;
    char *hairline1 = "####";
    char *hairline2 = "<<<<";

    if (
        ( ( strcmp ( member, "boot/grub/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->mcinfo_boot_grub_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "cmdlog/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->mcinfo_cmdlog_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "date") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->date.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsb-release") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsb_release.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "uname") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->uname.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "hostname") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->hostname.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "uptime") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->uptime.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/cpuinfo") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_cpuinfo.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "root/anaconda-ks.cfg") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->root_anaconda_ks_cfg.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "dmidecode") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->dmidecode.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsmod") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsmod.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lspci") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lspci.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/devices/udevadm_info_--export-db") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/scsi/lsscsi") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "installed-rpms") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->installed_rpms.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "df") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->df.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "vgdisplay") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->vgdisplay.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "free") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->free.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "ip_addr") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->ip_addr.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "route") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->route.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "last") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->last.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "ps") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->ps.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsof") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsof.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "netstat") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->netstat.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/kdump.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_kdump_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/sysctl.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysctl_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/rsyslog.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_rsyslog_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/meminfo") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_meminfo.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/interrupts") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_interrupts.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/net/dev") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_dev.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/net/sockstat") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_sockstat.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/logrotate.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_logrotate_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/pki/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_pki_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/cron.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_cron_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/spool/cron/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_spool_cron_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/dmesg") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_dmesg.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/messages") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_messages.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/secure") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_secure.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/audit/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_audit_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/kernel/sysctl_-a") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/ethtool_-S") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/ethtool_-i") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/boot/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_boot_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/httpd/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_httpd_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/crash/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_crash_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/default/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_default_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/logrotate.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_logrotate_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/modprobe.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_modprobe_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/host") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_host.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/udev/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_udev_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/yum.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_yum_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/yum.repos.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_yum_repos_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/systemd/system/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_systemd_system_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/systemd/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_systemd_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "usr/lib/systemd/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->usr_lib_systemd_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/sar/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_sar_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/virsh/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_virsh_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/usb/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_usb_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lib/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lib_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "dev/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->dev_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "usr/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->usr_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/abrt/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_abrt_.member, "" ) != 0 ) )
    )
    {
        search_list ( &sos_header_obj, member, result_tmp_pre );
        snprintf ( result_tmp, MAX_LINE_LENGTH, "(config setting is %s)", result_tmp_pre );
        snprintf (str_tmp, MAX_LINE_LENGTH, "%s/%s", get_dirname ( str_tmp3 ), member );
        snprintf ( str_tmp2, MAX_LINE_LENGTH, "file:%s", str_tmp );
        append_list ( &sos_line_obj, "" );
        append_list ( &sos_line_obj, hairline1 );
        append_list ( &sos_line_obj, hairline2 );
        append_list ( &sos_line_obj, str_tmp2 );
        append_list ( &sos_line_obj, result_tmp );
        append_list ( &sos_line_obj, "" );

        /* for ones of which should read directory, or matched files in the directory */
        /* This order is the order of tmp_<number>_obj */
        if (
            ( strcmp ( member, "boot/grub/" ) == 0 ) ||
            ( strcmp ( member, "cmdlog/" ) == 0 ) ||
            ( strcmp ( member, "etc/pki/" ) == 0 ) ||
            ( strcmp ( member, "etc/cron.d/" ) == 0 ) ||
            ( strcmp ( member, "var/spool/cron/" ) == 0 ) ||
            ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 ) ||
            ( strcmp ( member, "var/log/messages" ) == 0 ) ||
            ( strcmp ( member, "var/log/secure" ) == 0 ) ||
            ( strcmp ( member, "var/log/audit/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/boot/" ) == 0 ) ||
            ( strcmp ( member, "etc/httpd/" ) == 0 ) ||
            ( strcmp ( member, "proc/" ) == 0 ) ||
            ( strcmp ( member, "var/crash/" ) == 0 ) ||
            ( strcmp ( member, "etc/default/" ) == 0 ) ||
            ( strcmp ( member, "etc/logrotate.d/" ) == 0 ) ||
            ( strcmp ( member, "etc/modprobe.d/" ) == 0 ) ||
            ( strcmp ( member, "etc/host" ) == 0 ) ||
            ( strcmp ( member, "etc/udev/" ) == 0 ) ||
            ( strcmp ( member, "etc/yum.repos.d/" ) == 0 ) ||
            ( strcmp ( member, "etc/systemd/system/" ) == 0 ) ||
            ( strcmp ( member, "etc/systemd/" ) == 0 ) ||
            ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/sar/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/virsh/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/usb/" ) == 0 ) ||
            ( strcmp ( member, "lib/" ) == 0 ) ||
            ( strcmp ( member, "etc/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networking/" ) == 0 ) ||
            ( strcmp ( member, "dev/" ) == 0 ) ||
            ( strcmp ( member, "usr/" ) == 0 ) ||
            ( strcmp ( member, "var/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/abrt/" ) == 0 )
           )
        {
            printf("analyze member '%s'\n",member);
            read_analyze_dir ( member, get_dirname ( str_tmp3 ), 0 );
        }
        else
            read_file ( str_tmp, member, 0 );
        /* now, we actually read files here for directory stuff */
        if ( strcmp ( member, "boot/grub/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_1_obj, str_arr_boot_grub ); i ++ )
                append_list ( &mcinfo_boot_grub__obj, str_arr_boot_grub [ i ] );
            read_file_from_analyze_dir ( &mcinfo_boot_grub__obj, "boot/grub/" );
        }
        else if ( strcmp ( member, "cmdlog/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_2_obj, str_arr_cmdlog ); i ++ )
                append_list ( &mcinfo_cmdlog__obj, str_arr_cmdlog [ i ] );
            read_file_from_analyze_dir ( &mcinfo_cmdlog__obj, "cmdlog/" );
        }
        else if ( strcmp ( member, "dev/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_31_obj, str_arr_dev ); i ++ )
                append_list ( &dev__obj, str_arr_dev [ i ] );
            read_file_from_analyze_dir ( &dev__obj, "dev/" );
        }
        else if ( strcmp ( member, "etc/pki/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_3_obj, str_arr_pki ); i ++ )
                append_list ( &etc_pki__obj, str_arr_pki [ i ] );
            read_file_from_analyze_dir ( &etc_pki__obj, "etc/pki/" );
        }
        else if ( strcmp ( member, "etc/cron.d/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_4_obj, str_arr_cron ); i ++ )
                append_list ( &etc_cron_d__obj, str_arr_cron [ i ] );
            read_file_from_analyze_dir ( &etc_cron_d__obj, "etc/cron.d/" );
        }
        else if ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_5_obj, str_arr_ifcfg ); i ++ )
                append_list ( &etc_sysconfig_network_scripts_ifcfg__obj, str_arr_ifcfg [ i ] );
            read_file_from_analyze_dir ( &etc_sysconfig_network_scripts_ifcfg__obj, "etc/sysconfig/network-scripts/ifcfg-" );
        }
        else if ( strcmp ( member, "etc/httpd/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_13_obj, str_arr_etc_httpd ); i ++ )
                append_list ( &etc_httpd__obj, str_arr_etc_httpd [ i ] );
            read_file_from_analyze_dir ( &etc_httpd__obj, "etc/httpd/" );
        }
        else if ( strcmp ( member, "etc/default/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_16_obj, str_arr_etc_default ); i ++ )
                append_list ( &etc_default__obj, str_arr_etc_default [ i ] );
            read_file_from_analyze_dir ( &etc_default__obj, "etc/default/" );
        }
        else if ( strcmp ( member, "etc/host" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_19_obj, str_arr_etc_host ); i ++ )
                append_list ( &etc_host_obj, str_arr_etc_host [ i ] );
            read_file_from_analyze_dir ( &etc_host_obj, "etc/host" );
        }
        else if ( strcmp ( member, "etc/logrotate.d/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_17_obj, str_arr_etc_logrotate_d ); i ++ )
                append_list ( &etc_logrotate_d__obj, str_arr_etc_logrotate_d [ i ] );
            read_file_from_analyze_dir ( &etc_logrotate_d__obj, "etc/logrotate.d/" );
        }
        else if ( strcmp ( member, "etc/modprobe.d/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_18_obj, str_arr_etc_modprobe_d ); i ++ )
                append_list ( &etc_modprobe_d__obj, str_arr_etc_modprobe_d [ i ] );
            read_file_from_analyze_dir ( &etc_modprobe_d__obj, "etc/modprobe.d/" );
        }
        else if ( strcmp ( member, "etc/udev/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_20_obj, str_arr_etc_udev ); i ++ )
                append_list ( &etc_udev__obj, str_arr_etc_udev [ i ] );
            read_file_from_analyze_dir ( &etc_udev__obj, "etc/udev/" );
        }
        else if ( strcmp ( member, "etc/yum.repos.d/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_21_obj, str_arr_etc_yum_repos_d ); i ++ )
                append_list ( &etc_yum_repos_d__obj, str_arr_etc_yum_repos_d [ i ] );
            read_file_from_analyze_dir ( &etc_yum_repos_d__obj, "etc/yum.repos.d/" );
        }
        else if ( strcmp ( member, "etc/systemd/system/" ) == 0 )
        {
            for ( i= 0; i < bubble_sort_object_by_the_string ( &tmp_22_obj, str_arr_etc_systemd_system ); i ++ )
                append_list ( &etc_systemd_system__obj, str_arr_etc_systemd_system [ i ] );
            read_file_from_analyze_dir ( &etc_systemd_system__obj, "etc/systemd/system/" );
        }
        else if ( strcmp ( member, "etc/systemd/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_23_obj, str_arr_etc_systemd ); i ++ )
                append_list ( &etc_systemd__obj, str_arr_etc_systemd [ i ] );
            read_file_from_analyze_dir ( &etc_systemd__obj, "etc/systemd/" );
        }
        else if ( strcmp ( member, "etc/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_29_obj, str_arr_etc ); i ++ )
                append_list ( &etc__obj, str_arr_etc [ i ] );
            read_file_from_analyze_dir ( &etc__obj, "etc/" );
        }
        else if ( strcmp ( member, "lib/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_28_obj, str_arr_lib ); i ++ )
                append_list ( &lib__obj, str_arr_lib [ i ] );
            read_file_from_analyze_dir ( &lib__obj, "lib/" );
        }
        else if ( strcmp ( member, "proc/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_14_obj, str_arr_proc ); i ++ )
                append_list ( &proc__obj, str_arr_proc [ i ] );
            read_file_from_analyze_dir ( &proc__obj, "proc/" );
        }
        else if ( strcmp ( member, "sos_commands/sar/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_25_obj, str_arr_sos_commands_sar ); i ++ )
                append_list ( &sos_commands_sar__obj, str_arr_sos_commands_sar [ i ] );
            read_file_from_analyze_dir ( &sos_commands_sar__obj, "sos_commands/sar/" );
        }
        else if ( strcmp ( member, "sos_commands/virsh/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_26_obj, str_arr_sos_commands_virsh ); i ++ )
                append_list ( &sos_commands_virsh__obj, str_arr_sos_commands_virsh [ i ] );
            read_file_from_analyze_dir ( &sos_commands_virsh__obj, "sos_commands/virsh/" );
        }
        else if ( strcmp ( member, "sos_commands/usb/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_27_obj, str_arr_sos_commands_usb ); i ++ )
                append_list ( &sos_commands_usb__obj, str_arr_sos_commands_usb [ i ] );
            read_file_from_analyze_dir ( &sos_commands_usb__obj, "sos_commands/usb/" );
        }
        else if ( strcmp ( member, "sos_commands/networking/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_30_obj, str_arr_sos_commands_networking ); i ++ )
                append_list ( &sos_commands_networking__obj, str_arr_sos_commands_networking [ i ] );
            read_file_from_analyze_dir ( &sos_commands_networking__obj, "sos_commands/networking/" );
        }
        else if ( strcmp ( member, "sos_commands/abrt/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_36_obj, str_arr_sos_commands_abrt ); i ++ )
                append_list ( &sos_commands_abrt__obj, str_arr_sos_commands_abrt [ i ] );
            read_file_from_analyze_dir ( &sos_commands_abrt__obj, "sos_commands/abrt/" );
        }
        else if ( strcmp ( member, "sos_commands/boot/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_12_obj, str_arr_boot ); i ++ )
                append_list ( &sos_commands_boot__obj, str_arr_boot [ i ] );
            read_file_from_analyze_dir ( &sos_commands_boot__obj, "sos_commands/boot/" );
        }
        else if ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_9_obj, str_arr_logs_journalctl ); i ++ )
                append_list ( &sos_commands_logs_journalctl___no_pager_obj, str_arr_logs_journalctl [ i ] );
            read_file_from_analyze_dir ( &sos_commands_logs_journalctl___no_pager_obj, "sos_commands/logs/journalctl_--no-pager" );
        }
        else if ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_10_obj, str_arr_ethtool_S ); i ++ )
                append_list ( &sos_commands_networking_ethtool__S_obj, str_arr_ethtool_S [ i ] );
            read_file_from_analyze_dir ( &sos_commands_networking_ethtool__S_obj, "sos_commands/networking/ethtool_-S" );
        }
        else if ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_11_obj, str_arr_ethtool_i ); i ++ )
                append_list ( &sos_commands_networking_ethtool__i_obj, str_arr_ethtool_i [ i ] );
            read_file_from_analyze_dir ( &sos_commands_networking_ethtool__i_obj, "sos_commands/networking/ethtool_-i" );
        }
        else if ( strcmp ( member, "sos_commands/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_34_obj, str_arr_sos_commands ); i ++ )
                append_list ( &sos_commands_obj, str_arr_sos_commands [ i ] );
            read_file_from_analyze_dir ( &sos_commands_obj, "sos_commands/" );
        }
        else if ( strcmp ( member, "usr/lib/systemd/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_24_obj, str_arr_usr_lib_systemd ); i ++ )
                append_list ( &usr_lib_systemd__obj, str_arr_usr_lib_systemd [ i ] );
            read_file_from_analyze_dir ( &usr_lib_systemd__obj, "usr/lib/systemd/" );
        }
        else if ( strcmp ( member, "usr/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_32_obj, str_arr_usr ); i ++ )
                append_list ( &usr__obj, str_arr_usr [ i ] );
            read_file_from_analyze_dir ( &usr__obj, "usr/" );
        }
        else if ( strcmp ( member, "var/crash/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_15_obj, str_arr_var_crash ); i ++ )
                append_list ( &var_crash__obj, str_arr_var_crash [ i ] );
            read_file_from_analyze_dir ( &var_crash__obj, "var/crash/" );
        }
        else if ( strcmp ( member, "var/log/messages" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_6_obj, str_arr_var_log_messages ); i ++ )
                append_list ( &var_log_messages_obj, str_arr_var_log_messages [ i ] );
            read_file_from_analyze_dir ( &var_log_messages_obj, "var/log/messages" );
        }
        else if ( strcmp ( member, "var/log/secure" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_7_obj, str_arr_var_log_secure ); i ++ )
                append_list ( &var_log_secure_obj, str_arr_var_log_secure [ i ] );
            read_file_from_analyze_dir ( &var_log_secure_obj, "var/log/secure" );
        }
        else if ( strcmp ( member, "var/log/audit/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_8_obj, str_arr_var_log_audit ); i ++ )
                append_list ( &var_log_audit__obj, str_arr_var_log_audit [ i ] );
            read_file_from_analyze_dir ( &var_log_audit__obj, "var/log/audit/" );
        }
        else if ( strcmp ( member, "var/spool/cron/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_35_obj, str_arr_var_spool_cron ); i ++ )
                append_list ( &var_spool_cron__obj, str_arr_var_spool_cron [ i ] );
            read_file_from_analyze_dir ( &var_spool_cron__obj, "var/spool/cron/" );
        }
        else if ( strcmp ( member, "var/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_33_obj, str_arr_var ); i ++ )
                append_list ( &var__obj, str_arr_var [ i ] );
            read_file_from_analyze_dir ( &var__obj, "var/" );
        }
    }
}

int check_time_span_str ( const char *time_span_str )
{
    char str_tmp [ 12 ];
    memset ( str_tmp, '\0', sizeof ( str_tmp ) ); 
    strncpy ( str_tmp, time_span_str, 11 );
    int i = 0;
    for ( i = 0; i < 11; i++ )
    {
        if ( ( i == 0 ) || ( i == 6 ) )
            if ( ( str_tmp [ i ] != '0' ) && ( str_tmp [ i ] != '1' ) && ( str_tmp [ i ] != '2' ) )
                return 0;
        if ( ( i == 2 ) || ( i == 8 ) )
            if ( str_tmp [ i ] != ':' )
                return 0;
        if ( i == 5 )
            if ( str_tmp [ i ] != '-' )
                return 0;
        if ( ( i == 1 ) || ( i == 3 ) || ( i == 4 ) || ( i == 7 ) || ( i == 9 ) || ( i == 10 ) )
            if (
                ( str_tmp [ i ] != '0' ) && ( str_tmp [ i ] != '1' ) && ( str_tmp [ i ] != '2' ) && 
                ( str_tmp [ i ] != '3' ) && ( str_tmp [ i ] != '4' ) && ( str_tmp [ i ] != '5' ) && 
                ( str_tmp [ i ] != '6' ) && ( str_tmp [ i ] != '7' ) && ( str_tmp [ i ] != '8' ) && 
                ( str_tmp [ i ] != '9' )
               )
                   return 0;
    }

    if ( str_tmp [ 0 ] == '2' )
    {
        if ( ( str_tmp [ 1 ] != '0' ) && ( str_tmp [ 1 ] != '1' ) && ( str_tmp [ 1 ] != '2' ) && ( str_tmp [ 1 ] != '3' ) )
            return 0;
        if ( ( str_tmp [ 1 ] == '2' ) && ( ( str_tmp [ 6 ] == '1' ) || ( str_tmp [ 6 ] == '0' ) ) )
            return 0;
        if ( ( str_tmp [ 1 ] == '1' ) && ( str_tmp [ 6 ] == '0' ) )
            return 0;
    }

    if ( str_tmp [ 0 ] == str_tmp [ 6 ] )
    {
        if ( str_tmp [ 1 ] == '9' )
            if ( str_tmp [ 7 ] != '9' )
                return 0;
        if ( str_tmp [ 1 ] == '8' )
            if ( ( str_tmp [ 7 ] != '9' ) && ( str_tmp [ 7 ] != '8' ) )
                return 0;
        if ( str_tmp [ 1 ] == '7' )
            if ( ( str_tmp [ 7 ] != '9' ) && ( str_tmp [ 7 ] != '8' ) && ( str_tmp [ 7 ] != '7' ) )
                return 0;
        if ( str_tmp [ 1 ] == '6' )
            if ( ( str_tmp [ 7 ] != '9' ) && ( str_tmp [ 7 ] != '8' ) && ( str_tmp [ 7 ] != '7' ) && ( str_tmp [ 7 ] != '6' ) )
                return 0;
        if ( str_tmp [ 1 ] == '5' )
            if ( ( str_tmp [ 7 ] == '4' ) || ( str_tmp [ 7 ] == '3' ) || ( str_tmp [ 7 ] == '2' ) || ( str_tmp [ 7 ] == '1' ) || ( str_tmp [ 7 ] == '0' ) )
                return 0;
        if ( str_tmp [ 1 ] == '4' )
            if ( ( str_tmp [ 7 ] == '3' ) || ( str_tmp [ 7 ] == '2' ) || ( str_tmp [ 7 ] == '1' ) || ( str_tmp [ 7 ] == '0' ) )
                return 0;
        if ( str_tmp [ 1 ] == '3' )
            if ( ( str_tmp [ 7 ] == '2' ) || ( str_tmp [ 7 ] == '1' ) || ( str_tmp [ 7 ] == '0' ) )
                return 0;
        if ( str_tmp [ 1 ] == '2' )
            if ( ( str_tmp [ 7 ] == '1' ) || ( str_tmp [ 7 ] == '0' ) )
                return 0;
        if ( str_tmp [ 1 ] == '1' )
            if ( str_tmp [ 7 ] == '0' )
                return 0;

        if ( str_tmp [ 1 ] == str_tmp [ 7 ] )
        {
            if ( str_tmp [ 3 ] == '9' )
                if ( str_tmp [ 9 ] != '9' )
                    return 0;
            if ( str_tmp [ 3 ] == '8' )
                if ( ( str_tmp [ 9 ] != '9' ) && ( str_tmp [ 9 ] != '8' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '7' )
                if ( ( str_tmp [ 9 ] != '9' ) && ( str_tmp [ 9 ] != '8' ) && ( str_tmp [ 9 ] != '7' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '6' )
                if ( ( str_tmp [ 9 ] != '9' ) && ( str_tmp [ 9 ] != '8' ) && ( str_tmp [ 9 ] != '7' ) && ( str_tmp [ 9 ] != '6' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '5' )
                if ( ( str_tmp [ 9 ] == '4' ) || ( str_tmp [ 9 ] == '3' ) || ( str_tmp [ 9 ] == '2' ) || ( str_tmp [ 9 ] == '1' ) || ( str_tmp [ 9 ] == '0' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '4' )
                if ( ( str_tmp [ 9 ] == '3' ) || ( str_tmp [ 9 ] == '2' ) || ( str_tmp [ 9 ] == '1' ) || ( str_tmp [ 9 ] == '0' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '3' )
                if ( ( str_tmp [ 9 ] == '2' ) || ( str_tmp [ 9 ] == '1' ) || ( str_tmp [ 9 ] == '0' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '2' )
                if ( ( str_tmp [ 9 ] == '1' ) || ( str_tmp [ 9 ] == '0' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '1' )
                if ( str_tmp [ 9 ] == '0' )
                    return 0;
        }
    }

    if ( str_tmp [ 6 ] == '2' )
        if ( ( str_tmp [ 7 ] != '0' ) && ( str_tmp [ 7 ] != '1' ) && ( str_tmp [ 7 ] != '2' ) && ( str_tmp [ 7 ] != '3' ) ) 
            return 0;
    if ( ( ( str_tmp [ 0 ] == '1' ) || ( str_tmp [ 0 ] == '2' ) ) && ( str_tmp [ 6 ] == '0' ) ) 
        return 0;
    if ( ( ( str_tmp [ 0 ] == '2' ) ) && ( ( str_tmp [ 6 ] == '0' ) || ( str_tmp [ 6 ] == '1' ) ) )
        return 0;

    if (
        ( str_tmp [ 0 ] == str_tmp [ 6 ] ) &&
        ( str_tmp [ 1 ] == str_tmp [ 7 ] ) && 
        ( str_tmp [ 3 ] == str_tmp [ 9 ] )
       )
    {
        if ( str_tmp [ 4 ] == '9' )
            if ( str_tmp [ 10 ] != '9' )
                return 0;
        if ( str_tmp [ 4 ] == '8' )
            if ( ( str_tmp [ 10 ] != '9' ) && ( str_tmp [ 10 ] != '8' ) )
                return 0;
        if ( str_tmp [ 4 ] == '7' )
            if ( ( str_tmp [ 10 ] != '9' ) && ( str_tmp [ 10 ] != '8' ) && ( str_tmp [ 10 ] != '7' ) )
                return 0;
        if ( str_tmp [ 4 ] == '6' )
            if ( ( str_tmp [ 10 ] != '9' ) && ( str_tmp [ 10 ] != '8' ) && ( str_tmp [ 10 ] != '7' ) && ( str_tmp [ 10 ] != '6' ) )
                return 0;
        if ( str_tmp [ 4 ] == '5' )
            if ( ( str_tmp [ 10 ] == '4' ) || ( str_tmp [ 10 ] == '3' ) || ( str_tmp [ 10 ] == '2' ) || ( str_tmp [ 10 ] == '1' ) || ( str_tmp [ 10 ] == '0' ) )
                return 0;
        if ( str_tmp [ 4 ] == '4' )
            if ( ( str_tmp [ 10 ] == '3' ) || ( str_tmp [ 10 ] == '2' ) || ( str_tmp [ 10 ] == '1' ) || ( str_tmp [ 10 ] == '0' ) )
                return 0;
        if ( str_tmp [ 4 ] == '3' )
            if ( ( str_tmp [ 10 ] == '2' ) || ( str_tmp [ 10 ] == '1' ) || ( str_tmp [ 10 ] == '0' ) )
                return 0;
        if ( str_tmp [ 4 ] == '2' )
            if ( ( str_tmp [ 10 ] == '1' ) || ( str_tmp [ 10 ] == '0' ) )
                return 0;
        if ( str_tmp [ 4 ] == '1' )
            if ( str_tmp [ 10 ] == '0' )
                return 0;
    }

    return 1;
}

const char *get_dirname ( char str_tmp [ MAX_LINE_LENGTH ] )
{
    strncpy ( str_tmp, sos_dir_file_obj->dir_file_names.dirname, MAX_LINE_LENGTH );
    return str_tmp;
}

const char *get_sos_file_name_to_be_written ( void )
{
    return sos_dir_file_obj->dir_file_names.sos_file_name_to_be_written;
}

const char *get_sar_file_name_to_be_written ( void )
{
    return sos_dir_file_obj->dir_file_names.sar_file_name_to_be_written;
}

const char *get_ps_file_name_to_be_written ( void )
{
    return sos_dir_file_obj->dir_file_names.ps_file_name_to_be_written;
}

int is_dir_present ( const char *dname )
{
    int strlen_dname = ( int )strlen ( dname );

    if ( strlen_dname <= 0 )
    {
        printf("Directory (%s) name is too short.: %s\n",dname,strerror(errno));
        return ( 0 );
    }
    if ( strlen_dname > NAME_MAX )
    {
        printf("Directory (%s) name is too long.: %s\n",dname,strerror(errno));
        return ( 0 );
    }
    if ( dname != NULL )
    {
        DIR *dir = NULL;
        /* if open directory fails, return 1 */
        char str_tmp [ NAME_MAX ];
        strncpy ( str_tmp, dname, NAME_MAX - 1 );
        if ( ( dir = opendir ( str_tmp ) ) == NULL ) 
        {
            printf("can't open directory (%s): %s\n",dname,strerror(errno));
            free_sosreport_analyzer_obj ( );
            return 1;
        }
        else
        closedir ( dir );
    }
    return ( 0 );
}

int check_result_dir ( const char *dname )
{
    int strlen_dname = ( int )strlen ( dname );

    if ( strlen_dname <= 0 )
    {
        printf("Directory (%s) name is too short.: %s\n",dname,strerror(errno));
        return ( 0 );
    }
    if ( strlen_dname > NAME_MAX )
    {
        printf("Directory (%s) name is too long.: %s\n",dname,strerror(errno));
        return ( 0 );
    }
    if ( dname != NULL )
    {
        DIR *dir = NULL;
        /* if open directory fails, create it, if it fails, exit with error message */
        char str_tmp [ NAME_MAX ];
        strncpy ( str_tmp, dname, NAME_MAX - 1 );
        if ( ( dir = opendir ( str_tmp ) ) == NULL ) 
        {
            printf("can't open directory (%s): %s\n",dname,strerror(errno));
            printf("creating directory %s\n",dname);
            if ( mkdir ( dname, 0755 ) == 0 )
            {
                printf("created directory %s\n",dname);
            }
            else
            {
                printf("can't open directory %s\n",dname);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
        }
        else
            printf("directory %s exists\n",dname);
        closedir ( dir );
    }
    return ( 0 );
}

void sos_file_to_write ( void )
{
    char * result_dir = "sosreport-analyzer-results";
    char * result_dir_with_slash = "sosreport-analyzer-results/";
    char buff_dir [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_dir, '\0', MAX_FILE_NAME_LENGTH ); 
    strcpy ( buff_dir, result_dir );
    char buff_dir_analyzed [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_dir_analyzed, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff_dir_analyzed_graph [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_dir_analyzed_graph, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff_sos [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_sos, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff_sar [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_sar, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff_ps [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_ps, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff2 [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff2, '\0', MAX_FILE_NAME_LENGTH ); 
    char f_t [ 40 ];
    memset ( f_t, '\0', 40 ); 
    char f_t2 [ 40 ];
    memset ( f_t2, '\0', 40 ); 
    char f_t3 [ 40 ];
    memset ( f_t3, '\0', 40 ); 
    char str_tmp [ MAX_LINE_LENGTH ]; 
    memset ( str_tmp, '\0', MAX_LINE_LENGTH ); 

    strcpy ( buff2, get_dirname ( str_tmp ) );
    /* firstly, we create results directory */
    check_result_dir ( buff_dir );
    char str_ret [ MAX_FILE_NAME_LENGTH ]; 
    /* secondly, we create sosreport directory which has been analyed in the results directory we've just created */
    if ( strstr ( buff2, "/" ) != NULL )
    {
        int strlen_buff2 = ( int ) strlen ( buff2 );
        if ( strlen_buff2 <= 0 )
        {
            printf("buff2 is too short (%s): %d %s\n",buff2, strlen_buff2, strerror(errno));
            free_sosreport_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }
        strcpy ( buff_dir_analyzed, cut_str_from_the_last_slash ( reverse_the_string ( buff2, strlen_buff2 ), strlen_buff2, str_ret ) );
    }
    else
        strcpy ( buff_dir_analyzed, buff2 );
    strcat ( buff_dir, "/" );
    strcat ( buff_dir, buff_dir_analyzed );
    check_result_dir ( buff_dir );
    strcpy ( buff_dir_analyzed_graph, buff_dir );
    strcat ( buff_dir_analyzed_graph, "/graphs" );
    check_result_dir ( buff_dir_analyzed_graph );
    /* thirdly, we set file name */
    strcat ( buff_sos, result_dir_with_slash );
    strcat ( buff_sar, result_dir_with_slash );
    strcat ( buff_sos, buff_dir_analyzed );
    strcat ( buff_sar, buff_dir_analyzed );
    strcat ( buff_ps, buff_dir_analyzed_graph );
    strcat ( buff_sos, "/" );
    strcat ( buff_sar, "/" );
    strcat ( buff_ps, "/" );
    strcat ( buff_sos, buff_dir_analyzed );
    strcat ( buff_sar, buff_dir_analyzed );
    strcat ( buff_ps, buff_dir_analyzed );
    /* each analyed file should have unique name */
    struct tm *timenow;
    time_t now = time ( NULL );
    timenow = localtime ( &now );
    /* for sos file */
    strftime ( f_t, sizeof ( f_t ), "_%Y%m%d%H%M%S", timenow );
    strncat ( buff_sos, f_t, MAX_FILE_NAME_LENGTH - 1 );
    strncat ( buff_sos, ".txt", MAX_FILE_NAME_LENGTH - 1);
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strcpy ( sos_dir_file_obj->dir_file_names.sos_file_name_to_be_written, buff_sos );
    /* for sar file */
    strftime ( f_t2, sizeof ( f_t2 ), "_sar_%Y%m%d%H%M%S", timenow );
    strncat ( buff_sar, f_t2, MAX_FILE_NAME_LENGTH - 1 );
    strncat ( buff_sar, ".txt", MAX_FILE_NAME_LENGTH - 1 );
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strcpy ( sos_dir_file_obj->dir_file_names.sar_file_name_to_be_written, buff_sar );
    /* for ps file */
    strftime ( f_t3, sizeof ( f_t3 ), "_ps_%Y%m%d%H%M%S", timenow );
    strncat ( buff_ps, f_t3, MAX_FILE_NAME_LENGTH - 1 );
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strcpy ( sos_dir_file_obj->dir_file_names.ps_file_name_to_be_written, buff_ps );
}

int append_item_to_sos_line_obj ( char *line, const char *member, const char *item )
{
    /* These should echo only needed lines, note item number is limited by
     * set_token_to_item_arr.
     */
    /* First, check if item has 'all'. When item is 'all', should echo every lines */
    if ( strcmp ( item, "all" ) == 0 )
            append_list ( &sos_line_obj, line );
    if ( ( strcmp ( member, "dmidecode" ) == 0 ) && ( strcmp ( item, "bios" ) == 0 ) )
    {
        if ( strcmp ( line, "BIOS Information" ) == 0 )
            bios_information = 1;
        if ( strstr ( line , "Characteristics:" ) != 0 )
        {
            bios_information = 0;
            return 1;
        }
        if ( bios_information == 1 )
            append_list ( &sos_line_obj, line );
        if ( strstr ( line , "BIOS Revision:" ) != NULL )
            append_list ( &sos_line_obj, line );
    }
    else if ( ( strcmp ( member, "dmidecode" ) == 0 ) && ( strcmp ( item, "memory" ) == 0 ) )
    {
        if ( strcmp ( line, "Physical Memory Array" ) == 0 )
            memory_array_information = 1;
        if ( strstr ( line, "Handle" ) != NULL )
            memory_array_information = 0;
        if ( strcmp ( line, "Memory Device" ) == 0 )
        {
            append_list ( &sos_line_obj, line );
            memory_information = 1;
        }
        if ( strcmp ( line, "OEM" ) == 0 )
            memory_information = 0;
        if ( memory_array_information == 1 )
            append_list ( &sos_line_obj, line );
        if ( memory_information == 1 )
        {
            if ( strstr ( line , "Size:" ) != NULL )
                append_list ( &sos_line_obj, line );
        }
    }
    /* These should echo matched lines which had been set by config file, note item number is 
     * limited by set_token_to_item_arr. members which could have only one item is excluded here.
     * Another way of saying is, these may have item 'all' or others.
     */
    else if ( 
        ( strcmp ( member, "dmidecode" ) == 0 ) ||
        ( strcmp ( member, "lsmod" ) == 0 ) ||
        ( strcmp ( member, "lspci" ) == 0 ) ||
        ( strcmp ( member, "proc/cpuinfo" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/devices/udevadm_info_--export-db" ) == 0 ) ||
        ( strcmp ( member, "installed-rpms" ) == 0 ) ||
        ( strcmp ( member, "df" ) == 0 ) ||
        ( strcmp ( member, "last" ) == 0 ) ||
        ( strcmp ( member, "ps" ) == 0 ) ||
        ( strcmp ( member, "lsof" ) == 0 ) ||
        ( strcmp ( member, "netstat" ) == 0 ) ||
        ( strcmp ( member, "proc/meminfo" ) == 0 ) ||
        ( strcmp ( member, "etc/pki/" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.d/" ) == 0 ) ||
        ( strcmp ( member, "var/spool/cron/" ) == 0 ) ||
        ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 ) ||
        ( strcmp ( member, "var/log/messages" ) == 0 ) ||
        ( strcmp ( member, "var/log/secure" ) == 0 ) ||
        ( strcmp ( member, "var/log/audit/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/kernel/sysctl_-a" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/scsi/lsscsi" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/boot/" ) == 0 ) ||
        ( strcmp ( member, "etc/httpd/" ) == 0 ) ||
        ( strcmp ( member, "proc/" ) == 0 ) ||
        ( strcmp ( member, "var/crash/" ) == 0 ) ||
        ( strcmp ( member, "etc/default/" ) == 0 ) ||
        ( strcmp ( member, "etc/logrotate.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/modprobe.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/host" ) == 0 ) ||
        ( strcmp ( member, "etc/udev/" ) == 0 ) ||
        ( strcmp ( member, "etc/yum.repos.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/systemd/system/" ) == 0 ) ||
        ( strcmp ( member, "etc/systemd/" ) == 0 ) ||
        ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/sar/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/virsh/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/usb/" ) == 0 ) ||
        ( strcmp ( member, "lib/" ) == 0 ) ||
        ( strcmp ( member, "etc/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networking/" ) == 0 ) ||
        ( strcmp ( member, "dev/" ) == 0 ) ||
        ( strcmp ( member, "usr/" ) == 0 ) ||
        ( strcmp ( member, "var/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/abrt/" ) == 0 )
    )
    {
        if ( strstr ( line , item ) != NULL )
            append_list ( &sos_line_obj, line );
        else
            return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

void free_sosreport_analyzer_obj ( void )
{
    if ( sos_header_obj != NULL ) 
        clear_list ( &sos_header_obj ); 
    if ( sos_line_obj != NULL ) 
        clear_list ( &sos_line_obj ); 
    if ( sos_tail_obj != NULL ) 
        clear_list ( &sos_tail_obj ); 

    if ( tmp_1_obj != NULL ) 
        clear_list ( &tmp_1_obj ); 
    if ( tmp_2_obj != NULL ) 
        clear_list ( &tmp_2_obj ); 
    if ( tmp_3_obj != NULL ) 
        clear_list ( &tmp_3_obj ); 
    if ( tmp_4_obj != NULL ) 
        clear_list ( &tmp_4_obj ); 
    if ( tmp_5_obj != NULL ) 
        clear_list ( &tmp_5_obj ); 
    if ( tmp_6_obj != NULL ) 
        clear_list ( &tmp_6_obj ); 
    if ( tmp_7_obj != NULL ) 
        clear_list ( &tmp_7_obj ); 
    if ( tmp_8_obj != NULL ) 
        clear_list ( &tmp_8_obj ); 
    if ( tmp_9_obj != NULL ) 
        clear_list ( &tmp_9_obj ); 
    if ( tmp_10_obj != NULL ) 
        clear_list ( &tmp_10_obj ); 
    if ( tmp_11_obj != NULL ) 
        clear_list ( &tmp_11_obj ); 
    if ( tmp_12_obj != NULL ) 
        clear_list ( &tmp_12_obj ); 
    if ( tmp_13_obj != NULL ) 
        clear_list ( &tmp_13_obj ); 
    if ( tmp_14_obj != NULL ) 
        clear_list ( &tmp_14_obj ); 
    if ( tmp_15_obj != NULL ) 
        clear_list ( &tmp_15_obj ); 
    if ( tmp_16_obj != NULL ) 
        clear_list ( &tmp_16_obj ); 
    if ( tmp_17_obj != NULL ) 
        clear_list ( &tmp_17_obj ); 
    if ( tmp_18_obj != NULL ) 
        clear_list ( &tmp_18_obj ); 
    if ( tmp_19_obj != NULL ) 
        clear_list ( &tmp_19_obj ); 
    if ( tmp_20_obj != NULL ) 
        clear_list ( &tmp_20_obj ); 
    if ( tmp_21_obj != NULL ) 
        clear_list ( &tmp_21_obj ); 
    if ( tmp_22_obj != NULL ) 
        clear_list ( &tmp_22_obj ); 
    if ( tmp_23_obj != NULL ) 
        clear_list ( &tmp_23_obj ); 
    if ( tmp_24_obj != NULL ) 
        clear_list ( &tmp_24_obj ); 
    if ( tmp_25_obj != NULL ) 
        clear_list ( &tmp_25_obj ); 
    if ( tmp_26_obj != NULL ) 
        clear_list ( &tmp_26_obj ); 
    if ( tmp_27_obj != NULL ) 
        clear_list ( &tmp_27_obj ); 
    if ( tmp_28_obj != NULL ) 
        clear_list ( &tmp_28_obj ); 
    if ( tmp_29_obj != NULL ) 
        clear_list ( &tmp_29_obj ); 
    if ( tmp_30_obj != NULL ) 
        clear_list ( &tmp_30_obj ); 
    if ( tmp_31_obj != NULL ) 
        clear_list ( &tmp_31_obj ); 
    if ( tmp_32_obj != NULL ) 
        clear_list ( &tmp_32_obj ); 
    if ( tmp_33_obj != NULL ) 
        clear_list ( &tmp_33_obj ); 
    if ( tmp_34_obj != NULL ) 
        clear_list ( &tmp_34_obj ); 
    if ( tmp_35_obj != NULL ) 
        clear_list ( &tmp_35_obj ); 
    if ( tmp_36_obj != NULL ) 
        clear_list ( &tmp_36_obj ); 

    if ( etc_pki__obj != NULL ) 
        clear_list ( &etc_pki__obj ); 
    if ( etc_cron_d__obj != NULL ) 
        clear_list ( &etc_cron_d__obj ); 
    if ( etc_sysconfig_network_scripts_ifcfg__obj != NULL ) 
        clear_list ( &etc_sysconfig_network_scripts_ifcfg__obj ); 
    if ( var_log_messages_obj != NULL ) 
        clear_list ( &var_log_messages_obj ); 
    if ( var_log_secure_obj != NULL ) 
        clear_list ( &var_log_secure_obj ); 
    if ( var_log_audit__obj != NULL ) 
        clear_list ( &var_log_audit__obj ); 
    if ( sos_commands_logs_journalctl___no_pager_obj != NULL ) 
        clear_list ( &sos_commands_logs_journalctl___no_pager_obj ); 
    if ( sos_commands_networking_ethtool__S_obj != NULL ) 
        clear_list ( &sos_commands_networking_ethtool__S_obj ); 
    if ( sos_commands_networking_ethtool__i_obj != NULL ) 
        clear_list ( &sos_commands_networking_ethtool__i_obj ); 
    if ( sos_commands_boot__obj != NULL ) 
        clear_list ( &sos_commands_boot__obj ); 
    if ( mcinfo_boot_grub__obj != NULL )
        clear_list ( &mcinfo_boot_grub__obj );
    if ( mcinfo_cmdlog__obj != NULL )
        clear_list ( &mcinfo_cmdlog__obj );
    if ( etc_httpd__obj != NULL ) 
        clear_list ( &etc_httpd__obj ); 
    if ( proc__obj != NULL ) 
        clear_list ( &proc__obj ); 
    if ( var_crash__obj != NULL ) 
        clear_list ( &var_crash__obj ); 
    if ( etc_default__obj != NULL ) 
        clear_list ( &etc_default__obj ); 
    if ( etc_logrotate_d__obj != NULL ) 
        clear_list ( &etc_logrotate_d__obj ); 
    if ( etc_modprobe_d__obj != NULL ) 
        clear_list ( &etc_modprobe_d__obj ); 
    if ( etc_host_obj != NULL ) 
        clear_list ( &etc_host_obj ); 
    if ( etc_udev__obj != NULL ) 
        clear_list ( &etc_udev__obj ); 
    if ( etc_yum_repos_d__obj != NULL ) 
        clear_list ( &etc_yum_repos_d__obj ); 
    if ( etc_systemd_system__obj != NULL ) 
        clear_list ( &etc_systemd_system__obj ); 
    if ( etc_systemd__obj != NULL ) 
        clear_list ( &etc_systemd__obj ); 
    if ( usr_lib_systemd__obj != NULL ) 
        clear_list ( &usr_lib_systemd__obj ); 
    if ( sos_commands_sar__obj != NULL ) 
        clear_list ( &sos_commands_sar__obj ); 
    if ( sos_commands_virsh__obj != NULL ) 
        clear_list ( &sos_commands_virsh__obj ); 
    if ( sos_commands_usb__obj != NULL ) 
        clear_list ( &sos_commands_usb__obj ); 
    if ( lib__obj != NULL ) 
        clear_list ( &lib__obj ); 
    if ( etc__obj != NULL ) 
        clear_list ( &etc__obj ); 
    if ( sos_commands_networking__obj != NULL ) 
        clear_list ( &sos_commands_networking__obj ); 
    if ( dev__obj != NULL ) 
        clear_list ( &dev__obj ); 
    if ( usr__obj != NULL ) 
        clear_list ( &usr__obj ); 
    if ( var__obj != NULL ) 
        clear_list ( &var__obj ); 
    if ( sos_commands_obj != NULL ) 
        clear_list ( &sos_commands_obj ); 
    if ( var_spool_cron__obj != NULL ) 
        clear_list ( &var_spool_cron__obj ); 
    if ( sos_commands_abrt__obj != NULL ) 
        clear_list ( &sos_commands_abrt__obj ); 
}
