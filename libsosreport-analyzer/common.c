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

/* sos_dir_file_obj */
struct dir_file_name sos_dir_file_obj_raw = 
    {{ "test.txt", "test.txt", "test.txt", "test.txt" }};

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

/* making pointers to the structs */
struct dir_file_name *sos_dir_file_obj = &sos_dir_file_obj_raw;
struct line_data *mcinfo_boot_grub__obj = &mcinfo_boot_grub__obj_raw;
struct line_data *mcinfo_cmdlog__obj = &mcinfo_cmdlog__obj_raw;
struct line_data *sos_header_obj = &sos_header_obj_raw;
struct line_data *sos_line_obj = &sos_line_obj_raw;
struct line_data *sos_tail_obj = &sos_tail_obj_raw;
struct line_data *etc_cron_d__obj = &etc_cron_d__obj_raw;
struct line_data *etc_sysconfig_network_scripts_ifcfg__obj = &etc_sysconfig_network_scripts_ifcfg__obj_raw;
struct line_data *var_log_messages_obj = &var_log_messages_obj_raw;
struct line_data *var_log_secure_obj = &var_log_secure_obj_raw;
struct line_data *var_log_audit__obj = &var_log_audit__obj_raw;
struct line_data *sos_commands_logs_journalctl___no_pager_obj = &sos_commands_logs_journalctl___no_pager_obj_raw;
struct line_data *sos_commands_networking_ethtool__S_obj = &sos_commands_networking_ethtool__S_obj_raw;
struct line_data *sos_commands_networking_ethtool__i_obj = &sos_commands_networking_ethtool__i_obj_raw;
struct line_data *sos_commands_boot__obj = &sos_commands_boot__obj_raw;

void read_analyze_dir ( const char *member, const char *dname )
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
    dname_full = cut_str_by_the_last_slash ( full_path, str_len_dname_full );
    
    if ( dname_full != NULL )
    {
        /* if open directory fails, exit with error message */
        if ( ( dir = opendir ( dname_full ) ) == NULL ) 
        {
            printf("can't open directory (%s): %s\n",dname_full,strerror(errno));
            free_sosreport_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }
    }
    char *str;
    int i = 0;

    /* limit of fname_part files to be analyzed */
    int str_arr_valid_size = 0;

    /* setting NULL to objects for directory related stuff including those matched files */
    if ( strstr ( full_path, "boot/gurb/") != 0 )
        mcinfo_boot_grub__obj = NULL;
    else if ( strstr ( full_path, "etc/sysconfig/network-scripts/ifcfg-") != 0 )
        etc_sysconfig_network_scripts_ifcfg__obj = NULL;
    else if ( strstr ( full_path, "cmdlog") != 0 )
        mcinfo_cmdlog__obj = NULL;
    else if ( strstr ( full_path, "cron") != 0 )
        etc_cron_d__obj = NULL;
    else if ( strstr ( full_path, "messages") != 0 )
        var_log_messages_obj = NULL;
    else if ( strstr ( full_path, "secure") != 0 )
        var_log_secure_obj = NULL;
    else if ( strstr ( full_path, "audit") != 0 )
        var_log_audit__obj = NULL;
    else if ( strstr ( full_path, "journalctl") != 0 )
        sos_commands_logs_journalctl___no_pager_obj = NULL;
    else if ( strstr ( full_path, "ethtool_-S") != 0 )
        sos_commands_networking_ethtool__S_obj = NULL;
    else if ( strstr ( full_path, "sos_commands/boot/") != 0 )
        sos_commands_boot__obj = NULL;

    /* read from directory and set in an array */
    for ( dp = readdir ( dir ),i = 0; dp != NULL; dp = readdir ( dir ) )
    {
        if ( dp->d_type != DT_REG )
            continue;
        str = dp->d_name;
        /*
         *  find files with name fname_part 
         */
        if ( strstr ( str, fname_part ) != NULL )
        {
            /* so, only fname_part files will remain */
            snprintf (read_path, MAX_LINE_LENGTH, "%s%s", dname_full, str );
            if ( strstr ( read_path, "boot/grub") != 0 )
                append_list ( &mcinfo_boot_grub__obj, read_path );
            else if ( strstr ( read_path, "cmdlog") != 0 )
                append_list ( &mcinfo_cmdlog__obj, read_path );
            else if ( strstr ( read_path, "cron") != 0 )
                append_list ( &etc_cron_d__obj, read_path );
            else if ( strstr ( read_path, "etc/sysconfig/network-scripts/ifcfg-") != 0 )
                append_list ( &etc_sysconfig_network_scripts_ifcfg__obj, read_path );
            else if ( strstr ( read_path, "messages") != 0 )
                append_list ( &var_log_messages_obj, read_path );
            else if ( strstr ( read_path, "secure") != 0 )
                append_list ( &var_log_secure_obj, read_path );
            else if ( strstr ( read_path, "audit") != 0 )
                append_list ( &var_log_audit__obj, read_path );
            else if ( strstr ( read_path, "journalctl") != 0 )
                append_list ( &sos_commands_logs_journalctl___no_pager_obj, read_path );
            else if ( strstr ( read_path, "ethtool_-S") != 0 )
                append_list ( &sos_commands_networking_ethtool__S_obj, read_path );
            else if ( strstr ( read_path, "ethtool_-i") != 0 )
                append_list ( &sos_commands_networking_ethtool__i_obj, read_path );
            else if ( strstr ( read_path, "sos_commands/boot/") != 0 )
                append_list ( &sos_commands_boot__obj, read_path );
            i++; /* needed here */
            str_arr_valid_size++;
            if ( str_arr_valid_size == MAX_ANALYZE_FILES )
                break;
        }
    }
    /* close the directory */
    closedir ( dir );

    /* read every files related */
    node *ptr_tmp = NULL;
    if ( strstr ( read_path, "boot/grub") != 0 )
        ptr_tmp = *(&mcinfo_boot_grub__obj);
    else if ( strstr ( read_path, "cmdlog") != 0 )
        ptr_tmp = *(&mcinfo_cmdlog__obj);
    else if ( strstr ( read_path, "cron") != 0 )
        ptr_tmp = *(&etc_cron_d__obj);
    else if ( strstr ( read_path, "etc/sysconfig/network-scripts/ifcfg-") != 0 )
        ptr_tmp = *(&etc_sysconfig_network_scripts_ifcfg__obj);
    else if ( strstr ( read_path, "messages") != 0 )
        ptr_tmp = *(&var_log_messages_obj);
    else if ( strstr ( read_path, "secure") != 0 )
        ptr_tmp = *(&var_log_secure_obj);
    else if ( strstr ( read_path, "audit") != 0 )
        ptr_tmp = *(&var_log_audit__obj);
    else if ( strstr ( read_path, "journalctl") != 0 )
        ptr_tmp = *(&sos_commands_logs_journalctl___no_pager_obj);
    else if ( strstr ( read_path, "ethtool_-S") != 0 )
        ptr_tmp = *(&sos_commands_networking_ethtool__S_obj);
    else if ( strstr ( read_path, "ethtool_-i") != 0 )
        ptr_tmp = *(&sos_commands_networking_ethtool__i_obj);
    else if ( strstr ( read_path, "sos_commands/boot/") != 0 )
        ptr_tmp = *(&sos_commands_boot__obj);
    /* now we read each file in the directory */
    int files = 0;
    while ( ptr_tmp != NULL )
    {
        read_file ( ptr_tmp->_line, member, files );
        files ++;
        ptr_tmp = ptr_tmp->next;
    }
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
const char *items_root_anaconda_ks_cfg [ 12 ];
const char *items_dmidecode [ 12 ];
const char *items_lsmod [ 12 ];
const char *items_lspci [ 20 ];
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
const char *items_etc_sysconfig_network_scripts_ifcfg_;
const char *items_proc_meminfo [ 12 ];
const char *items_proc_interrupts;
const char *items_proc_net_dev;
const char *items_proc_net_sockstat;
const char *items_etc_logrotate_conf;
const char *items_etc_cron_d_;
const char *items_var_log_dmesg;
const char *items_var_log_messages [ 12 ];
const char *items_var_log_secure [ 12 ];
const char *items_var_log_audit_ [ 12 ];
const char *items_sos_commands_kernel_sysctl__a [ 12 ];
const char *items_sos_commands_logs_journalctl___no_pager [ 12 ];
const char *items_sos_commands_networking_ethtool__S [ 12 ];
const char *items_sos_commands_networking_ethtool__i [ 12 ];
const char *items_sos_commands_boot_ [ 12 ];

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

    int file_name_len = ( int ) strlen ( file_name );
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
        free_sosreport_analyzer_obj ( );
        exit ( EXIT_FAILURE );
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
         */
        if ( strstr ( file_name, "boot/grub/" ) != NULL )
        {
            snprintf ( filename_mcinfo_boot_grub__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_mcinfo_boot_grub_, filename_mcinfo_boot_grub__curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf (filename_mcinfo_boot_grub_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' when echoing every file in member
             * directory, so...
             */
            append_item_to_sos_line_obj ( line, "boot/grub/", items_mcinfo_boot_grub_ );
        }
        else if ( strstr ( file_name, "cmdlog/" ) != NULL )
        {
            snprintf ( filename_mcinfo_cmdlog__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_mcinfo_cmdlog_, filename_mcinfo_cmdlog__curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf (filename_mcinfo_cmdlog_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' when echoing every file in member
             * directory, so...
             */
            append_item_to_sos_line_obj ( line, "cmdlog/", items_mcinfo_cmdlog_ );
        }
        else if ( ( strstr ( file_name, "date" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "date", items_date );
        else if ( ( strstr ( file_name, "lsb-release" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "lsb-release", items_lsb_release );
        else if ( ( strstr ( file_name, "uname" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "uname", items_uname );
        else if ( ( strstr ( file_name, "hostname" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "hostname", items_hostname );
        else if ( ( strstr ( file_name, "uptime" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "uptime", items_uptime );
        else if ( ( strstr ( file_name, "root/anaconda-ks.cfg" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "root/anaconda-ks.cfg", items_root_anaconda_ks_cfg [ 0 ] );
        else if ( ( strstr ( file_name, "dmidecode" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->dmidecode.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "dmidecode", items_dmidecode [ x ] );
        else if ( ( strstr ( file_name, "lsmod" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->lsmod.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "lsmod", items_lsmod [ x ] );
        else if ( ( strstr ( file_name, "lspci" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->lspci.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "lspci", items_lspci [ x ] );
        else if ( ( strstr ( file_name, "sos_commands/scsi/lsscsi" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "sos_commands/scsi/lsscsi", items_sos_commands_scsi_lsscsi );
        else if ( ( strstr ( file_name, "installed-rpms" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->installed_rpms.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "installed-rpms", items_installed_rpms [ x ] );
        else if ( ( strstr ( file_name, "df" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->df.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "df", items_df [ x ] );
        else if ( ( strstr ( file_name, "vgdisplay" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "vgdisplay", items_vgdisplay );
        else if ( ( strstr ( file_name, "free" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "free", items_free );
        else if ( ( strstr ( file_name, "ip_addr" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "ip_addr", items_ip_addr );
        else if ( ( strstr ( file_name, "route" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "route", items_route );
        else if ( ( strstr ( file_name, "last" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->last.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "last", items_last [ x ] );
        else if ( ( strstr ( file_name, "ps" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->ps.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "ps", items_ps [ x ] );
        else if ( ( strstr ( file_name, "lsof" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->lsof.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "lsof", items_lsof [ x ] );
        else if ( ( strstr ( file_name, "netstat" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->netstat.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "netstat", items_netstat [ x ] );
        else if ( ( strstr ( file_name, "etc/kdump.conf" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "etc/kdump.conf", items_etc_kdump_conf );
        else if ( ( strstr ( file_name, "etc/sysctl.conf" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "etc/sysctl.conf", items_etc_sysctl_conf );
        else if ( strstr ( file_name, "etc/sysconfig/network-scripts/ifcfg-" ) != NULL )
        {
            snprintf ( filename_etc_sysconfig_network_scripts_ifcfg__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_sysconfig_network_scripts_ifcfg_, filename_etc_sysconfig_network_scripts_ifcfg__curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf (filename_etc_sysconfig_network_scripts_ifcfg_, MAX_LINE_LENGTH, "%s", file_name );
            append_item_to_sos_line_obj ( line, "etc/sysconfig/network-scripts/ifcfg-", items_etc_sysconfig_network_scripts_ifcfg_ );
        }
        else if ( strstr ( file_name, "proc/meminfo" ) != NULL )
            for ( x = 0; x < sosreport_analyzer_cfg->proc_meminfo.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "proc/meminfo", items_proc_meminfo [ x ] );
        else if ( strstr ( file_name, "proc/interrupts" ) != NULL )
            append_item_to_sos_line_obj ( line, "proc/interrupts", items_proc_interrupts );
        else if ( ( strstr ( file_name, "proc/net/dev" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "proc/net/dev", items_proc_net_dev );
        else if ( ( strstr ( file_name, "proc/net/sockstat" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "proc/net/sockstat", items_proc_net_sockstat );
        else if ( ( strstr ( file_name, "etc/logrotate.conf" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            append_item_to_sos_line_obj ( line, "etc/logrotate.conf", items_etc_logrotate_conf );
        else if ( ( strstr ( file_name, "etc/cron.d/" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf ( filename_etc_cron_d__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_etc_cron_d_, filename_etc_cron_d__curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf (filename_etc_cron_d_, MAX_LINE_LENGTH, "%s", file_name );
            /* unlike others like 'messages' which have same name should be applied in the
             * directory, here, we don't need 'for loop' when echoing every file in member
             * directory, so...
             */
            if ( items_etc_cron_d_ != NULL )
                append_item_to_sos_line_obj ( line, "etc/cron.d/", items_etc_cron_d_ );
        }
        else if ( strstr ( file_name, "var/log/dmesg" ) != NULL )
            append_item_to_sos_line_obj ( line, "var/log/dmesg", items_var_log_dmesg );
        else if ( strstr ( file_name, "var/log/messages" ) != NULL )
        {
            snprintf ( filename_var_log_messages_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_var_log_messages, filename_var_log_messages_curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf (filename_var_log_messages, MAX_LINE_LENGTH, "%s", file_name );
            for ( x = 0; x < sosreport_analyzer_cfg->var_log_messages.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "var/log/messages", items_var_log_messages [ x ] );
        }
        else if ( strstr ( file_name, "var/log/secure" ) != NULL )
        {
            snprintf ( filename_var_log_secure_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_var_log_secure, filename_var_log_secure_curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf (filename_var_log_secure, MAX_LINE_LENGTH, "%s", file_name );
            for ( x = 0; x < sosreport_analyzer_cfg->var_log_secure.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "var/log/secure", items_var_log_secure [ x ] );
        }
        else if ( strstr ( file_name, "var/log/audit/" ) != NULL )
        {
            snprintf ( filename_var_log_audit__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_var_log_audit_, filename_var_log_audit__curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf (filename_var_log_audit_, MAX_LINE_LENGTH, "%s", file_name );
            for ( x = 0; x < sosreport_analyzer_cfg->var_log_audit_.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "var/log/audit/", items_var_log_audit_ [ x ] );
        }
        else if ( ( strstr ( file_name, "sos_commands/kernel/sysctl_-a" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
            for ( x = 0; x < sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/kernel/sysctl_-a", items_sos_commands_kernel_sysctl__a [ x ] );
        else if ( ( strstr ( file_name, "sos_commands/logs/journalctl_--no-pager" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf (filename_sos_commands_logs_journalctl___no_pager_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_logs_journalctl___no_pager, filename_sos_commands_logs_journalctl___no_pager_curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf ( filename_sos_commands_logs_journalctl___no_pager, MAX_LINE_LENGTH, "%s", file_name );
            for ( x = 0; x < sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/logs/journalctl_--no-pager", items_sos_commands_logs_journalctl___no_pager [ x ] );
        }
        else if ( ( strstr ( file_name, "sos_commands/networking/ethtool_-S" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf (filename_sos_commands_networking_ethtool__S_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_networking_ethtool__S, filename_sos_commands_networking_ethtool__S_curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf ( filename_sos_commands_networking_ethtool__S, MAX_LINE_LENGTH, "%s", file_name );
            for ( x = 0; x < sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/networking/ethtool_-S", items_sos_commands_networking_ethtool__S [ x ] );
        }
        else if ( ( strstr ( file_name, "sos_commands/networking/ethtool_-i" ) != NULL ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
        {
            snprintf (filename_sos_commands_networking_ethtool__i_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_networking_ethtool__i, filename_sos_commands_networking_ethtool__i_curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf ( filename_sos_commands_networking_ethtool__i, MAX_LINE_LENGTH, "%s", file_name );
            for ( x = 0; x < sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/networking/ethtool_-i", items_sos_commands_networking_ethtool__i [ x ] );
        }
        else if ( strstr ( file_name, "sos_commands/boot/" ) != NULL )
        {
            snprintf ( filename_sos_commands_boot__curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_boot_, filename_sos_commands_boot__curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf (filename_sos_commands_boot_, MAX_LINE_LENGTH, "%s", file_name );
            for ( x = 0; x < sosreport_analyzer_cfg->sos_commands_boot_.item_num ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/boot/", items_sos_commands_boot_ [ x ] );
        }
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
    /* on members which have more than 2 tokens, should be initialized here */
    sosreport_analyzer_cfg->dmidecode.item_num = 0;
    sosreport_analyzer_cfg->lsmod.item_num = 0;
    sosreport_analyzer_cfg->lspci.item_num = 0;
    sosreport_analyzer_cfg->installed_rpms.item_num = 0;
    sosreport_analyzer_cfg->df.item_num = 0;
    sosreport_analyzer_cfg->last.item_num = 0;
    sosreport_analyzer_cfg->ps.item_num = 0;
    sosreport_analyzer_cfg->lsof.item_num = 0;
    sosreport_analyzer_cfg->netstat.item_num = 0;
    sosreport_analyzer_cfg->proc_meminfo.item_num = 0;
    sosreport_analyzer_cfg->etc_cron_d_.item_num = 0;
    sosreport_analyzer_cfg->var_log_messages.item_num = 0;
    sosreport_analyzer_cfg->var_log_secure.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_boot_.item_num = 0;
    sosreport_analyzer_cfg->mcinfo_cmdlog_.item_num = 0;

    int i = 0;

    /* ### FIX ME - make this function for better summary */
    const char s [ 8 ] = " \t\n\r"; /* this is the delimiter */
    char *token = NULL;
    /*
     * ### FIX ME
     * file_name should be excluded directory of given by -D 
     */
    /* member boot/grub/ */
    if ( ( strstr ( file_name, "boot/grub/" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->mcinfo_boot_grub_.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->mcinfo_boot_grub_.member, s );
        items_mcinfo_boot_grub_ = token;
    }
    /* member cmdlog */
    else if ( ( strstr ( file_name, "cmdlog/" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->mcinfo_cmdlog_.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->mcinfo_cmdlog_.member, s );
        items_mcinfo_cmdlog_ = token;
    }
    /* member date */
    else if ( ( strstr ( file_name, "/date" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->date.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->date.member, s );
        items_date = token;
    }
    /* member lsb_release */
    else if ( ( strstr ( file_name, "/lsb-release" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->lsb_release.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lsb_release.member, s );
        items_lsb_release = token;
    }
    /* member uname */
    else if ( ( strstr ( file_name, "/uname" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->uname.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->uname.member, s );
        items_uname = token;
    }
    /* member hostname */
    else if ( ( strstr ( file_name, "/hostname" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->hostname.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->hostname.member, s );
        items_hostname = token;
    }
    /* member uptime */
    else if ( ( strstr ( file_name, "/uptime" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->uptime.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->uptime.member, s );
        items_uptime = token;
    }
    /* member root/anaconda-ks.cfg */
    else if ( ( strstr ( file_name, "root/anaconda-ks.cfg" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->root_anaconda_ks_cfg.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->root_anaconda_ks_cfg.member, s );
        items_root_anaconda_ks_cfg [ 0 ] = token;
    }
    /* member dmidecode */
    else if ( ( strstr ( file_name, "/dmidecode" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->dmidecode.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->dmidecode.item_num = i; 
            items_dmidecode  [ sosreport_analyzer_cfg->dmidecode.item_num ] = token;
        }
    }
    /* member lsmod */
    else if ( ( strstr ( file_name, "/lsmod" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->lsmod.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->lsmod.item_num = i; 
            items_lsmod  [ sosreport_analyzer_cfg->lsmod.item_num ] = token;
        }
    }
    /* member lspci */
    else if ( ( strstr ( file_name, "/lspci" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->lspci.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->lspci.item_num = i; 
            items_lspci  [ sosreport_analyzer_cfg->lspci.item_num ] = token;
        }
    }
    /* member sos_commands/scsi/lsscsi */
    else if ( ( strstr ( file_name, "sos_commands/scsi/lsscsi" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.member, s );
        items_sos_commands_scsi_lsscsi = token;
    }
    /* member installed-rpms */
    else if ( ( strstr ( file_name, "/installed-rpms" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->installed_rpms.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->installed_rpms.member, s );
        items_installed_rpms [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->installed_rpms.item_num > arr_max12 )
            {
                printf("can't set items over %d for installed_rpms\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            sosreport_analyzer_cfg->installed_rpms.item_num = i; 
            items_installed_rpms  [ sosreport_analyzer_cfg->installed_rpms.item_num ] = token;
        }
    }
    /* member df */
    else if ( ( strstr ( file_name, "/df" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->df.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->df.item_num = i; 
            items_df  [ sosreport_analyzer_cfg->df.item_num ] = token;
        }
    }
    /* member vgdisplay */
    else if ( ( strstr ( file_name, "/vgdisplay" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->vgdisplay.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->vgdisplay.member, s );
        items_vgdisplay = token;
    }
    /* member free */
    else if ( ( strstr ( file_name, "/free" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->free.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->free.member, s );
        items_free = token;
    }
    /* member ip_addr */
    else if ( ( strstr ( file_name, "/ip_addr" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->ip_addr.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->ip_addr.member, s );
        items_ip_addr = token;
    }
    /* member route */
    else if ( ( strstr ( file_name, "/route" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->route.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->route.member, s );
        items_route = token;
    }
    /* member last */
    else if ( ( strstr ( file_name, "/last" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->last.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->last.item_num = i; 
            items_last  [ sosreport_analyzer_cfg->last.item_num ] = token;
        }
    }
    /* member ps */
    else if ( ( strstr ( file_name, "/ps" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->ps.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->ps.item_num = i; 
            items_ps  [ sosreport_analyzer_cfg->ps.item_num ] = token;
        }
    }
    /* member lsof */
    else if ( ( strstr ( file_name, "/lsof" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->lsof.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->lsof.item_num = i; 
            items_lsof  [ sosreport_analyzer_cfg->lsof.item_num ] = token;
        }
    }
    /* member netstat */
    else if ( ( strstr ( file_name, "/netstat" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->netstat.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->netstat.item_num = i; 
            items_netstat  [ sosreport_analyzer_cfg->netstat.item_num ] = token;
        }
    }
    /* member etc/kdump.conf */
    else if ( ( strstr ( file_name, "etc/kdump.conf" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->etc_kdump_conf.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_kdump_conf.member, s );
        items_etc_kdump_conf = token;
    }
    /* member etc/sysctl.conf */
    else if ( ( strstr ( file_name, "etc/sysctl.conf" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysctl_conf.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_sysctl_conf.member, s );
        items_etc_sysctl_conf = token;
    }
    /* member etc/sysconfig/network-scripts/ifcfg- */
    else if ( ( strstr ( file_name, "etc/sysconfig/network-scripts/ifcfg-" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.member, s );
        items_etc_sysconfig_network_scripts_ifcfg_ = token;
    }
    /* member proc/meminfo */
    else if ( ( strstr ( file_name, "proc/meminfo" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->proc_meminfo.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_meminfo.member, s );
        items_proc_meminfo [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->proc_meminfo.item_num > arr_max12 )
            {
                printf("can't set items over %d for proc/meminfo\n",arr_max2);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            sosreport_analyzer_cfg->proc_meminfo.item_num = i; 
            items_proc_meminfo  [ sosreport_analyzer_cfg->proc_meminfo.item_num ] = token;
        }
    }
    /* member proc/interrupts */
    else if ( ( strstr ( file_name, "proc/interrupts" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->proc_interrupts.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_interrupts.member, s );
        items_proc_interrupts = token;
    }
    /* member proc/net/dev */
    else if ( ( strstr ( file_name, "proc/net/dev" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_dev.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_net_dev.member, s );
        items_proc_net_dev = token;
    }
    /* member proc/net/sockstat */
    else if ( ( strstr ( file_name, "proc/net/sockstat" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_sockstat.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_net_sockstat.member, s );
        items_proc_net_sockstat = token;
    }
    /* member etc/logrotate.conf */
    else if ( ( strstr ( file_name, "etc/logrotate.conf" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->etc_logrotate_conf.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_logrotate_conf.member, s );
        items_etc_logrotate_conf = token;
    }
    /* member etc/cron.d/ */
    else if ( ( strstr ( file_name, "etc/cron.d/" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->etc_cron_d_.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_cron_d_.member, s );
        items_etc_cron_d_ = token;
    }
    /* member var/log/dmesg */
    else if ( ( strstr ( file_name, "var/log/dmesg" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->var_log_dmesg.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_log_dmesg.member, s );
        items_var_log_dmesg = token;
    }
    /* member var/log/messages */
    else if ( ( strstr ( file_name, "var/log/messages" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->var_log_messages.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_log_messages.member, s );
        items_var_log_messages [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->var_log_messages.item_num > arr_max12 )
            {
                printf("can't set items over %d for var/log/messages\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            sosreport_analyzer_cfg->var_log_messages.item_num = i; 
            items_var_log_messages  [ sosreport_analyzer_cfg->var_log_messages.item_num ] = token;
        }
    }
    /* member var/log/secure */
    else if ( ( strstr ( file_name, "var/log/secure" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->var_log_secure.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->var_log_secure.item_num = i; 
            items_var_log_secure  [ sosreport_analyzer_cfg->var_log_secure.item_num ] = token;
        }
    }
    /* member var/log/audit/ */
    else if ( ( strstr ( file_name, "var/log/audit/" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->var_log_audit_.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->var_log_audit_.item_num = i; 
            items_var_log_audit_  [ sosreport_analyzer_cfg->var_log_audit_.item_num ] = token;
        }
    }
    /* member sos_commands/kernel/sysctl_-a */
    else if ( ( strstr ( file_name, "sos_commands/kernel/sysctl_-a" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_num = i; 
            items_sos_commands_kernel_sysctl__a  [ sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_num ] = token;
        }
    }
    /* member sos_commands/logs/journalctl_--no-pager */
    else if ( ( strstr ( file_name, "sos_commands/logs/journalctl_--no-pager" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.member, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.member, s );
        items_sos_commands_logs_journalctl___no_pager [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            if ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_num > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/logs/journalctl_--no-pager\n",arr_max12);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            i ++;
            sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_num = i; 
            items_sos_commands_logs_journalctl___no_pager  [ sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_num ] = token;
        }
    }
    /* member sos_commands/networking/ethtool_-S */
    else if ( ( strstr ( file_name, "sos_commands/networking/ethtool_-S" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_num = i; 
            items_sos_commands_networking_ethtool__S  [ sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_num ] = token;
        }
    }
    /* member sos_commands/networking/ethtool_-i */
    else if ( ( strstr ( file_name, "sos_commands/networking/ethtool_-i" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_num = i; 
            items_sos_commands_networking_ethtool__i  [ sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_num ] = token;
        }
    }
    /* member sos_commands/boot/ */
    else if ( ( strstr ( file_name, "sos_commands/boot/" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_boot_.member, "" ) != 0 ) )
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
            sosreport_analyzer_cfg->sos_commands_boot_.item_num = i; 
            items_sos_commands_boot_  [ sosreport_analyzer_cfg->sos_commands_boot_.item_num ] = token;
        }
    }
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

    if (
        ( ( strcmp ( member, "boot/grub/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->mcinfo_boot_grub_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "cmdlog/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->mcinfo_cmdlog_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "date") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->date.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsb-release") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsb_release.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "uname") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->uname.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "hostname") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->hostname.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "uptime") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->uptime.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "root/anaconda-ks.cfg") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->root_anaconda_ks_cfg.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "dmidecode") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->dmidecode.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsmod") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsmod.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lspci") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lspci.member, "" ) != 0 ) ) ||
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
        ( ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/meminfo") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_meminfo.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/interrupts") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_interrupts.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/net/dev") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_dev.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/net/sockstat") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_sockstat.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/logrotate.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_logrotate_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/cron.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_cron_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/dmesg") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_dmesg.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/messages") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_messages.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/secure") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_secure.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/audit/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_audit_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/kernel/sysctl_-a") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/ethtool_-S") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/ethtool_-i") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/boot/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_boot_.member, "" ) != 0 ) )
    )
    {
        search_list ( &sos_header_obj, member, result_tmp_pre );
        snprintf ( result_tmp, MAX_LINE_LENGTH, "(config setting is %s)", result_tmp_pre );
        snprintf (str_tmp, MAX_LINE_LENGTH, "%s/%s", get_dirname ( str_tmp3 ), member );
        snprintf ( str_tmp2, MAX_LINE_LENGTH, "file:%s", str_tmp );
        append_list ( &sos_line_obj, "" );
        append_list ( &sos_line_obj, str_tmp2 );
        append_list ( &sos_line_obj, result_tmp );
        append_list ( &sos_line_obj, "" );

        /* for ones of which should read directory, or matched files in the directory */
        if (
            ( strcmp ( member, "boot/grub/" ) == 0 ) ||
            ( strcmp ( member, "cmdlog/" ) == 0 ) ||
            ( strcmp ( member, "etc/cron.d/" ) == 0 ) ||
            ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 ) ||
            ( strcmp ( member, "var/log/messages" ) == 0 ) ||
            ( strcmp ( member, "var/log/secure" ) == 0 ) ||
            ( strcmp ( member, "var/log/audit/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/boot/" ) == 0 )
           )
            read_analyze_dir ( member, get_dirname ( str_tmp3 ) );
        else
            read_file ( str_tmp, member, 0 );
    }
}

int check_time_span_str ( const char *time_span_str )
{
    char str_tmp [ 12 ];
    memset ( str_tmp, '\0', sizeof ( str_tmp ) ); 
    strncpy ( str_tmp, time_span_str, 11 );
    for ( int i = 0; i < 11; i++ )
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
        ( strcmp ( member, "installed-rpms" ) == 0 ) ||
        ( strcmp ( member, "df" ) == 0 ) ||
        ( strcmp ( member, "last" ) == 0 ) ||
        ( strcmp ( member, "ps" ) == 0 ) ||
        ( strcmp ( member, "lsof" ) == 0 ) ||
        ( strcmp ( member, "netstat" ) == 0 ) ||
        ( strcmp ( member, "proc/meminfo" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 ) ||
        ( strcmp ( member, "var/log/messages" ) == 0 ) ||
        ( strcmp ( member, "var/log/secure" ) == 0 ) ||
        ( strcmp ( member, "var/log/audit/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/kernel/sysctl_-a" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/scsi/lsscsi" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/boot/" ) == 0 )
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
    clear_list ( &sos_header_obj ); 
    clear_list ( &sos_line_obj ); 
    clear_list ( &etc_cron_d__obj ); 
    clear_list ( &etc_sysconfig_network_scripts_ifcfg__obj ); 
    clear_list ( &var_log_messages_obj ); 
    clear_list ( &var_log_secure_obj ); 
    clear_list ( &var_log_audit__obj ); 
    clear_list ( &sos_commands_logs_journalctl___no_pager_obj ); 
    clear_list ( &sos_commands_networking_ethtool__S_obj ); 
    clear_list ( &sos_commands_networking_ethtool__i_obj ); 
    clear_list ( &sos_commands_boot__obj ); 
    clear_list ( &sos_tail_obj ); 
    clear_list ( &mcinfo_boot_grub__obj );
    clear_list ( &mcinfo_cmdlog__obj );
}
