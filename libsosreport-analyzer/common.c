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

/* sos_header_obj */
struct line_data sos_header_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* line_obj */
struct line_data sos_line_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* tail_obj */
struct line_data sos_tail_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* var_log_messages_obj */
struct line_data var_log_messages_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_logs_journalctl___no_pager_obj */
struct line_data sos_commands_logs_journalctl___no_pager_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_networking_ethtool__S_obj */
struct line_data sos_commands_networking_ethtool__S_obj_raw =
    {
        "", /* each line */
        NULL /* next pointer */
    };

/* initialise */
struct line_data *sos_header_obj = &sos_header_obj_raw;
struct line_data *sos_line_obj = &sos_line_obj_raw;
struct line_data *sos_tail_obj = &sos_tail_obj_raw;
struct line_data *var_log_messages_obj = &var_log_messages_obj_raw;
struct line_data *sos_commands_logs_journalctl___no_pager_obj = &sos_commands_logs_journalctl___no_pager_obj_raw;
struct line_data *sos_commands_networking_ethtool__S_obj = &sos_commands_networking_ethtool__S_obj_raw;

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
    memset ( str_orig, '\0', sizeof ( str_orig ) ); 
    memset ( fname_part_path, '\0', sizeof ( fname_part_path ) ); 
    snprintf (full_path, MAX_LINE_LENGTH, "%s/%s", dname, member );
    str_len = strlen ( full_path );
    full_path [ str_len ] = '\0';
    strcpy ( str_orig, full_path );
    fname_part = cut_str_from_the_last_slash ( reverse_the_string ( full_path, str_len ), str_len, str_ret );
    snprintf (fname_part_path, MAX_LINE_LENGTH, "%s", fname_part );
    str_len_fname_part = strlen ( fname_part );
    str_len_dname_full = str_len - str_len_fname_part;
    dname_full = cut_str_by_the_last_slash ( full_path, str_len_dname_full );
    
    if ( dname_full != NULL )
    {
        /* if open directory fails, exit with error message */
        if ( ( dir = opendir ( dname_full ) ) == NULL ) 
        {
            printf("can't open directory (%s): %s\n",dname_full,strerror(errno));
            exit ( EXIT_FAILURE );
        }
    }
    char *str;
    int i = 0;

    /* limit of fname_part files to be analyzed */
    int str_arr_valid_size = 0;

    /* let's set NULL to objects */
    if ( strstr ( full_path, "messages") != 0 )
        var_log_messages_obj = NULL;
    else if ( strstr ( full_path, "journalctl") != 0 )
        sos_commands_logs_journalctl___no_pager_obj = NULL;
    else if ( strstr ( full_path, "ethtool_-S") != 0 )
        sos_commands_networking_ethtool__S_obj = NULL;

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
            if ( strstr ( read_path, "messages") != 0 )
            {
                append_list ( &var_log_messages_obj, read_path );
            }
            else if ( strstr ( read_path, "journalctl") != 0 )
            {
                append_list ( &sos_commands_logs_journalctl___no_pager_obj, read_path );
            }
            else if ( strstr ( read_path, "ethtool_-S") != 0 )
            {
                append_list ( &sos_commands_networking_ethtool__S_obj, read_path );
            }
	    i++; /* needed here */
            str_arr_valid_size++;
            if ( str_arr_valid_size == MAX_ANALYZE_FILES )
                break;
        }
    }
    /* close the directory */
    closedir ( dir );

    /* Check the number of files in the directory and if 0, exit */
    if ( str_arr_valid_size == 0 )
    {
        printf("There are no files in this directory (%s):%s\n",dname,strerror(errno));
        exit ( EXIT_FAILURE );
    }
    /* read every messages files */
    node *ptr_tmp = NULL;
    if ( strstr ( read_path, "messages") != 0 )
        ptr_tmp = *(&var_log_messages_obj);
    else if ( strstr ( read_path, "journalctl") != 0 )
        ptr_tmp = *(&sos_commands_logs_journalctl___no_pager_obj);
    else if ( strstr ( read_path, "ethtool_-S") != 0 )
        ptr_tmp = *(&sos_commands_networking_ethtool__S_obj);
    while ( ptr_tmp != NULL )
    {
        read_file ( ptr_tmp->_line );
        ptr_tmp = ptr_tmp->next;
    }
}

/* These are the items to be analyzed not statically nor checked by multi-lines */
int date_information = 0;
int bios_information = 0;
int memory_array_information = 0;
int memory_information = 0;
int df_information = 0;

/* These are array numbers limits. */
int arr_max0 = 0;
int arr_max2 = 2;
int arr_max12 = 12;
int arr_max20 = 20;
const char *items_date;
const char *items_lsb_release;
const char *items_uname;
const char *items_hostname;
const char *items_uptime;
const char *items_root_anaconda_ks_cfg [ 11 ];
const char *items_dmidecode [ 11 ];
const char *items_lsmod [ 11 ];
const char *items_lspci [ 19 ];
const char *items_sos_commands_scsi_lsscsi;
const char *items_installed_rpms [ 11 ];
const char *items_df [ 1 ];
const char *items_vgdisplay;
const char *items_free;
const char *items_ip_addr;
const char *items_route;
const char *items_last [ 11 ];
const char *items_ps [ 11 ];
const char *items_lsof [ 11 ];
const char *items_netstat [ 11 ];
const char *items_etc_kdump_conf;
const char *items_etc_sysctl_conf;
const char *items_proc_meminfo [ 11 ];
const char *items_proc_interrupts;
const char *items_proc_net_dev;
const char *items_proc_net_sockstat;
const char *items_var_log_messages [ 11 ];
const char *items_sos_commands_kernel_sysctl__a [ 11 ];
const char *items_sos_commands_logs_journalctl___no_pager [ 11 ];
const char *items_sos_commands_networking_ethtool__S [ 11 ];
/* members which could have items */
int dmidecode = 0, lsmod = 0, lspci = 0, sos_commands_scsi_lsscsi = 0;
int installed_rpms = 0, df = 0, last = 0;
int ps = 0, lsof = 0, netstat = 0, proc_meminfo = 0, var_log_messages = 0;
int sos_commands_kernel_sysctl__a = 0;
int sos_commands_logs_journalctl___no_pager = 0;
int sos_commands_networking_ethtool__S = 0, root_anaconda_ks_cfg = 0;

void read_file ( const char *file_name )
{
    char filename_var_log_messages [ MAX_LINE_LENGTH ];
    char filename_var_log_messages_curr [ MAX_LINE_LENGTH ];
    memset ( filename_var_log_messages, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_var_log_messages_curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_logs_journalctl___no_pager [ MAX_LINE_LENGTH ];
    char filename_sos_commands_logs_journalctl___no_pager_curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_logs_journalctl___no_pager, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_logs_journalctl___no_pager_curr, '\0', MAX_LINE_LENGTH ); 
    char filename_sos_commands_networking_ethtool__S [ MAX_LINE_LENGTH ];
    char filename_sos_commands_networking_ethtool__S_curr [ MAX_LINE_LENGTH ];
    memset ( filename_sos_commands_networking_ethtool__S, '\0', MAX_LINE_LENGTH ); 
    memset ( filename_sos_commands_networking_ethtool__S_curr, '\0', MAX_LINE_LENGTH ); 

    int file_name_len = strlen ( file_name );
    if ( file_name_len <= 0 )
    {
        printf("no file name supplied (%s): %d %s\n",file_name,file_name_len,strerror(errno));
        exit ( EXIT_FAILURE );
    }
    if ( file_name_len > MAX_FULL_PATH_LENGTH )
    {
        printf("file name too long (%s): %d %s\n",file_name,file_name_len,strerror(errno));
        exit ( EXIT_FAILURE );
    }
    FILE *fp;
    int lnr = 0, i = 0;
    char linebuf [ MAX_LINE_LENGTH ];
    char *line;

    set_token_to_item_arr ( file_name );

    /* open sosreport config file */
    if ( ( fp=fopen ( file_name, "r" ) ) == NULL )
    {
        printf("can't open file (%s): %s\n",file_name,strerror(errno));
        printf("Try set 'skip' to this member in /etc/sosreport-analyzer.conf.\n");
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
        if ( strstr ( file_name, "date" ) != NULL )
            append_item_to_sos_line_obj ( line, "date", items_date );
        else if ( strstr ( file_name, "lsb-release" ) != NULL )
            append_item_to_sos_line_obj ( line, "lsb-release", items_lsb_release );
        else if ( strstr ( file_name, "uname" ) != NULL )
            append_item_to_sos_line_obj ( line, "uname", items_uname );
        else if ( strstr ( file_name, "hostname" ) != NULL )
            append_item_to_sos_line_obj ( line, "hostname", items_hostname );
        else if ( strstr ( file_name, "uptime" ) != NULL )
            append_item_to_sos_line_obj ( line, "uptime", items_uptime );
        else if ( strstr ( file_name, "root/anaconda-ks.cfg" ) != NULL )
            append_item_to_sos_line_obj ( line, "root/anaconda-ks.cfg", items_root_anaconda_ks_cfg [ 0 ] );
        else if ( strstr ( file_name, "dmidecode" ) != NULL )
            for ( x = 0; x < dmidecode ; x++ )
                append_item_to_sos_line_obj ( line, "dmidecode", items_dmidecode [ x ] );
        else if ( strstr ( file_name, "lsmod" ) != NULL )
            for ( x = 0; x < lsmod ; x++ )
                append_item_to_sos_line_obj ( line, "lsmod", items_lsmod [ x ] );
        else if ( strstr ( file_name, "lspci" ) != NULL )
            for ( x = 0; x < lspci ; x++ )
                append_item_to_sos_line_obj ( line, "lspci", items_lspci [ x ] );
        else if ( strstr ( file_name, "sos_commands/scsi/lsscsi" ) != NULL )
            append_item_to_sos_line_obj ( line, "sos_commands/scsi/lsscsi", items_sos_commands_scsi_lsscsi );
        else if ( strstr ( file_name, "installed-rpms" ) != NULL )
            for ( x = 0; x < installed_rpms ; x++ )
                append_item_to_sos_line_obj ( line, "installed-rpms", items_installed_rpms [ x ] );
        else if ( strstr ( file_name, "df" ) != NULL )
            for ( x = 0; x < df ; x++ )
                append_item_to_sos_line_obj ( line, "df", items_df [ x ] );
        else if ( strstr ( file_name, "vgdisplay" ) != NULL )
            append_item_to_sos_line_obj ( line, "vgdisplay", items_vgdisplay );
        else if ( strstr ( file_name, "free" ) != NULL )
            append_item_to_sos_line_obj ( line, "free", items_free );
        else if ( strstr ( file_name, "ip_addr" ) != NULL )
            append_item_to_sos_line_obj ( line, "ip_addr", items_ip_addr );
        else if ( strstr ( file_name, "route" ) != NULL )
            append_item_to_sos_line_obj ( line, "route", items_route );
        else if ( strstr ( file_name, "last" ) != NULL )
            for ( x = 0; x < last ; x++ )
                append_item_to_sos_line_obj ( line, "last", items_last [ x ] );
        else if ( strstr ( file_name, "ps" ) != NULL )
            for ( x = 0; x < ps ; x++ )
                append_item_to_sos_line_obj ( line, "ps", items_ps [ x ] );
        else if ( strstr ( file_name, "lsof" ) != NULL )
            for ( x = 0; x < lsof ; x++ )
                append_item_to_sos_line_obj ( line, "lsof", items_lsof [ x ] );
        else if ( strstr ( file_name, "netstat" ) != NULL )
            for ( x = 0; x < netstat ; x++ )
                append_item_to_sos_line_obj ( line, "netstat", items_netstat [ x ] );
        else if ( strstr ( file_name, "etc/kdump.conf" ) != NULL )
            append_item_to_sos_line_obj ( line, "etc/kdump.conf", items_etc_kdump_conf );
        else if ( strstr ( file_name, "etc/sysctl.conf" ) != NULL )
            append_item_to_sos_line_obj ( line, "etc/sysctl.conf", items_etc_sysctl_conf );
        else if ( strstr ( file_name, "proc/meminfo" ) != NULL )
            for ( x = 0; x < proc_meminfo ; x++ )
                append_item_to_sos_line_obj ( line, "proc/meminfo", items_proc_meminfo [ x ] );
        else if ( strstr ( file_name, "proc/interrupts" ) != NULL )
            append_item_to_sos_line_obj ( line, "proc/interrupts", items_proc_interrupts );
        else if ( strstr ( file_name, "proc/net/dev" ) != NULL )
            append_item_to_sos_line_obj ( line, "proc/net/dev", items_proc_net_dev );
        else if ( strstr ( file_name, "proc/net/sockstat" ) != NULL )
            append_item_to_sos_line_obj ( line, "proc/net/sockstat", items_proc_net_sockstat );
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
            for ( x = 0; x < var_log_messages; x++ )
                append_item_to_sos_line_obj ( line, "var/log/messages", items_var_log_messages [ x ] );
        }
        else if ( strstr ( file_name, "sos_commands/kernel/sysctl_-a" ) != NULL )
            for ( x = 0; x < sos_commands_kernel_sysctl__a ; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/kernel/sysctl_-a", items_sos_commands_kernel_sysctl__a [ x ] );
        else if ( strstr ( file_name, "sos_commands/logs/journalctl_--no-pager" ) != NULL )
        {
            snprintf (filename_sos_commands_logs_journalctl___no_pager_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_logs_journalctl___no_pager, filename_sos_commands_logs_journalctl___no_pager_curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf ( filename_sos_commands_logs_journalctl___no_pager, MAX_LINE_LENGTH, "%s", file_name );
            for ( x = 0; x < sos_commands_logs_journalctl___no_pager; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/logs/journalctl_--no-pager", items_sos_commands_logs_journalctl___no_pager [ x ] );
        }
        else if ( strstr ( file_name, "sos_commands/networking/ethtool_-S" ) != NULL )
        {
            snprintf (filename_sos_commands_networking_ethtool__S_curr, MAX_LINE_LENGTH, "%s", file_name );
            if ( strcmp ( filename_sos_commands_networking_ethtool__S, filename_sos_commands_networking_ethtool__S_curr) != 0 )
            {
                append_list ( &sos_line_obj, "----------------" );
                append_list ( &sos_line_obj, (char *)file_name );
                append_list ( &sos_line_obj, "----------------" );
            }
            snprintf ( filename_sos_commands_networking_ethtool__S, MAX_LINE_LENGTH, "%s", file_name );
            for ( x = 0; x < sos_commands_networking_ethtool__S; x++ )
                append_item_to_sos_line_obj ( line, "sos_commands/networking/ethtool_-S", items_sos_commands_networking_ethtool__S [ x ] );
        }
        else
            break;
        /* strip trailing spaces */
        for ( i--; ( i > 0 ) && isspace ( line [ i -1 ] ) ; i-- )
            line [ i -1 ] = '\0';
    }
    /* after reading all lines, close the file pointer */
    fclose ( fp );
}

void set_token_to_item_arr ( const char *file_name )
{
    /* on members which have more than 2 tokens, should be initialised here */
    dmidecode = 0, lsmod = 0, lspci = 0, installed_rpms = 0, df = 0, last = 0;
    ps = 0, lsof = 0, netstat = 0, proc_meminfo = 0, var_log_messages = 0;
    sos_commands_kernel_sysctl__a = 0, sos_commands_logs_journalctl___no_pager = 0;
    sos_commands_networking_ethtool__S = 0;
    /* ### FIX ME - make this function for better summary */
    const char s [ 8 ] = " \t\n\r"; /* this is the delimiter */
    char *token = NULL;
    /* member date */
    if ( ( strstr ( file_name, "date" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->date, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->date, s );
        items_date = token;
    }
    /* member lsb_release */
    else if ( ( strstr ( file_name, "lsb-release" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->lsb_release, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lsb_release, s );
        items_lsb_release = token;
    }
    /* member uname */
    else if ( ( strstr ( file_name, "uname" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->uname, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->uname, s );
        items_uname = token;
    }
    /* member hostname */
    else if ( ( strstr ( file_name, "hostname" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->hostname, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->hostname, s );
        items_hostname = token;
    }
    /* member uptime */
    else if ( ( strstr ( file_name, "uptime" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->uptime, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->uptime, s );
        items_uptime = token;
    }
    /* member root/anaconda-ks.cfg */
    else if ( ( strstr ( file_name, "root/anaconda-ks.cfg" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->root_anaconda_ks_cfg, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->root_anaconda_ks_cfg, s );
        items_root_anaconda_ks_cfg [ 0 ] = token;
    }
    /* member dmidecode */
    else if ( ( strstr ( file_name, "dmidecode" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->dmidecode, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->dmidecode, s );
        items_dmidecode [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            dmidecode ++;
            if ( dmidecode > arr_max12 )
            {
                printf("can't set items over %d for dmidecode\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_dmidecode  [ dmidecode ] = token;
        }
    }
    /* member lsmod */
    else if ( ( strstr ( file_name, "lsmod" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->lsmod, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lsmod, s );
        items_lsmod [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            lsmod ++;
            if ( lsmod > arr_max12 )
            {
                printf("can't set items over %d for lsmod\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_lsmod  [ lsmod ] = token;
        }
    }
    /* member lspci */
    else if ( ( strstr ( file_name, "lspci" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->lspci, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lspci, s );
        items_lspci [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            lspci ++;
            if ( lspci > arr_max20 )
            {
                printf("can't set items over %d for lspci\n",arr_max20);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_lspci  [ lspci ] = token;
        }
    }
    /* member sos_commands/scsi/lsscsi */
    else if ( ( strstr ( file_name, "sos_commands/scsi/lsscsi" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi, s );
        items_sos_commands_scsi_lsscsi = token;
    }
    /* member installed-rpms */
    else if ( ( strstr ( file_name, "installed-rpms" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->installed_rpms, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->installed_rpms, s );
        items_installed_rpms [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            installed_rpms ++;
            if ( lsmod > arr_max12 )
            {
                printf("can't set items over %d for installed_rpms\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_installed_rpms  [ installed_rpms ] = token;
        }
    }
    /* member df */
    else if ( ( strstr ( file_name, "df" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->df, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->df, s );
        items_df [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            df ++;
            if ( df > arr_max2 )
            {
                printf("can't set items over %d for df\n",arr_max2);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_df  [ df ] = token;
        }
    }
    /* member vgdisplay */
    else if ( ( strstr ( file_name, "vgdisplay" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->vgdisplay, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->vgdisplay, s );
        items_vgdisplay = token;
    }
    /* member free */
    else if ( ( strstr ( file_name, "free" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->free, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->free, s );
        items_free = token;
    }
    /* member ip_addr */
    else if ( ( strstr ( file_name, "ip_addr" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->ip_addr, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->ip_addr, s );
        items_ip_addr = token;
    }
    /* member route */
    else if ( ( strstr ( file_name, "route" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->route, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->route, s );
        items_route = token;
    }
    /* member last */
    else if ( ( strstr ( file_name, "last" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->last, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->last, s );
        items_last [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            last ++;
            if ( last > arr_max12 )
            {
                printf("can't set items over %d for last\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_last  [ last ] = token;
        }
    }
    /* member ps */
    else if ( ( strstr ( file_name, "ps" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->ps, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->ps, s );
        items_ps [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            ps ++;
            if ( ps > arr_max12 )
            {
                printf("can't set items over %d for ps\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_ps  [ ps ] = token;
        }
    }
    /* member lsof */
    else if ( ( strstr ( file_name, "lsof" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->lsof, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->lsof, s );
        items_lsof [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            lsof ++;
            if ( lsof > arr_max12 )
            {
                printf("can't set items over %d for lsof\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_lsof  [ lsof ] = token;
        }
    }
    /* member netstat */
    else if ( ( strstr ( file_name, "netstat" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->netstat, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->netstat, s );
        items_netstat [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            netstat ++;
            if ( netstat > arr_max12 )
            {
                printf("can't set items over %d for netstat\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_netstat  [ netstat ] = token;
        }
    }
    /* member etc/kdump.conf */
    else if ( ( strstr ( file_name, "etc/kdump.conf" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->etc_kdump_conf, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_kdump_conf, s );
        items_etc_kdump_conf = token;
    }
    /* member etc/sysctl.conf */
    else if ( ( strstr ( file_name, "etc/sysctl.conf" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysctl_conf, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->etc_sysctl_conf, s );
        items_etc_sysctl_conf = token;
    }
    /* member proc/meminfo */
    else if ( ( strstr ( file_name, "proc/meminfo" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->proc_meminfo, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_meminfo, s );
        items_proc_meminfo [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            proc_meminfo ++;
            if ( proc_meminfo > arr_max2 )
            {
                printf("can't set items over %d for proc/meminfo\n",arr_max2);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_proc_meminfo  [ proc_meminfo ] = token;
        }
    }
    /* member proc/interrupts */
    else if ( ( strstr ( file_name, "proc/interrupts" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->proc_interrupts, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_interrupts, s );
        items_proc_interrupts = token;
    }
    /* member proc/net/dev */
    else if ( ( strstr ( file_name, "proc/net/dev" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_dev, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_net_dev, s );
        items_proc_net_dev = token;
    }
    /* member proc/net/sockstat */
    else if ( ( strstr ( file_name, "proc/net/sockstat" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_sockstat, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->proc_net_sockstat, s );
        items_proc_net_sockstat = token;
    }
    /* member var/log/messages */
    else if ( ( strstr ( file_name, "var/log/messages" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->var_log_messages, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->var_log_messages, s );
        items_var_log_messages [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            var_log_messages ++;
            if ( var_log_messages > arr_max12 )
            {
                printf("can't set items over %d for var/log/messages\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_var_log_messages  [ var_log_messages ] = token;
        }
    }
    /* member sos_commands/kernel/sysctl_-a */
    else if ( ( strstr ( file_name, "sos_commands/kernel/sysctl_-a" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a, s );
        items_sos_commands_kernel_sysctl__a [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            sos_commands_kernel_sysctl__a ++;
            if ( sos_commands_kernel_sysctl__a > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/kernel/sysctl_-a\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_sos_commands_kernel_sysctl__a  [ sos_commands_kernel_sysctl__a ] = token;
        }
    }
    /* member sos_commands/logs/journalctl_--no-pager */
    else if ( ( strstr ( file_name, "sos_commands/logs/journalctl_--no-pager" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager, s );
        items_sos_commands_logs_journalctl___no_pager [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            sos_commands_logs_journalctl___no_pager ++;
            if ( sos_commands_logs_journalctl___no_pager > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/logs/journalctl_--no-pager\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_sos_commands_logs_journalctl___no_pager  [ sos_commands_logs_journalctl___no_pager ] = token;
        }
    }
    /* member sos_commands/networking/ethtool_-S */
    else if ( ( strstr ( file_name, "sos_commands/networking/ethtool_-S" ) != NULL ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S, "" ) != 0 ) )
    {
        /* get the first token */
        token = strtok ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S, s );
        items_sos_commands_networking_ethtool__S [ 0 ] = token;
        /* get the next token ... */
        while ( token != NULL )
        {
            sos_commands_networking_ethtool__S ++;
            if ( sos_commands_networking_ethtool__S > arr_max12 )
            {
                printf("can't set items over %d for sos_commands/networking/ethtool_-S\n",arr_max12);
                exit ( EXIT_FAILURE );
            }
            token = strtok ( NULL, s );
            if ( token == NULL )
                break;
            items_sos_commands_networking_ethtool__S  [ sos_commands_networking_ethtool__S ] = token;
        }
    }
}

void read_file_pre ( const char *member, const char *dir_name )
{
    char str_tmp [ MAX_FILE_NAME_LENGTH ]; 
    memset ( str_tmp, '\0', MAX_FILE_NAME_LENGTH ); 
    char str_tmp2 [ MAX_FILE_NAME_LENGTH ]; 
    memset ( str_tmp2, '\0', MAX_FILE_NAME_LENGTH ); 
    char result_tmp_pre [ MAX_LINE_LENGTH - 21 ]; 
    memset ( result_tmp_pre, '\0', MAX_LINE_LENGTH - 21 ); 
    char result_tmp [ MAX_LINE_LENGTH ]; 
    memset ( result_tmp, '\0', MAX_LINE_LENGTH ); 

    //snprintf (str_tmp, strlen ( dir_name ) + strlen ( member ) + 2, "%s/%s", dir_name, member );
    snprintf (str_tmp, strlen ( get_dirname ( ) ) + strlen ( member ) + 2, "%s/%s", get_dirname ( ), member );

    if (
        ( ( strcmp ( member, "date") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->date, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsb-release") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsb_release, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "uname") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->uname, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "hostname") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->hostname, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "uptime") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->uptime, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "root/anaconda-ks.cfg") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->root_anaconda_ks_cfg, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "dmidecode") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->dmidecode, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsmod") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsmod, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lspci") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lspci, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/scsi/lsscsi") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "installed-rpms") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->installed_rpms, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "df") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->df, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "vgdisplay") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->vgdisplay, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "free") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->free, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "ip_addr") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->ip_addr, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "route") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->route, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "last") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->last, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "ps") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->ps, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsof") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsof, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "netstat") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->netstat, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/kdump.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_kdump_conf, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/sysctl.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysctl_conf, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/meminfo") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_meminfo, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/interrupts") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_interrupts, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/net/dev") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_dev, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/net/sockstat") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_sockstat, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/messages") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_messages, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/kernel/sysctl_-a") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/ethtool_-S") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S, "" ) != 0 ) )
    )
    {
        search_list ( &sos_header_obj, member, result_tmp_pre );
        snprintf ( result_tmp, MAX_LINE_LENGTH, "(config setting is %s)", result_tmp_pre );
        snprintf ( str_tmp2, MAX_LINE_LENGTH, "file:%s", str_tmp );
        append_list ( &sos_line_obj, "" );
        append_list ( &sos_line_obj, str_tmp2 );
        append_list ( &sos_line_obj, result_tmp );
        append_list ( &sos_line_obj, "" );

        /* for ones of which should be read directory */
        if (
            ( strcmp ( member, "var/log/messages" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 )
           )
            //read_analyze_dir ( member, dir_name );
            read_analyze_dir ( member, get_dirname ( ) );
        else
            read_file ( str_tmp );
    }
}

const char *get_sos_file_name_to_be_written ( void )
{
    return file_data_obj->sos_file_name_to_be_written;
}

const char *get_sar_file_name_to_be_written ( void )
{
    return file_data_obj->sar_file_name_to_be_written;
}

const char *get_ps_file_name_to_be_written ( void )
{
    return file_data_obj->ps_file_name_to_be_written;
}

int check_result_dir ( const char *dname )
{
    if ( dname != NULL )
    {
        /* if open directory fails, create it, if it fails, exit with error message */
        if ( !opendir ( dname ) ) 
        {
            printf("can't open directory %s\n",dname);
            printf("creating directory %s\n",dname);
            if ( mkdir ( dname, 0755 ) == 0 )
            {
                printf("created directory %s\n",dname);
            }
            else
            {
                printf("can't open directory %s\n",dname);
                exit ( EXIT_FAILURE );
            }
        }
        else
            printf("directory %s exists\n",dname);
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

    strcpy ( buff2, get_dirname ( ) );
    /* firstly, we create results directory */
    check_result_dir ( buff_dir );
    char str_ret [ MAX_FILE_NAME_LENGTH ]; 
    /* secondly, we create sosreport directory which has been analyed in the results directory we've just created */
    if ( strstr ( buff2, "/" ) != NULL )
        strcpy ( buff_dir_analyzed, cut_str_from_the_last_slash ( reverse_the_string ( buff2, strlen ( buff2 ) ), strlen ( buff2 ), str_ret ) );
    else
        strcpy ( buff_dir_analyzed, buff2 );
    strcat ( buff_dir, "/" );
    strcat ( buff_dir, buff_dir_analyzed );
    check_result_dir ( buff_dir );
    /* thirdly, we set file name */
    strcat ( buff_sos, result_dir_with_slash );
    strcat ( buff_sar, result_dir_with_slash );
    strcat ( buff_ps, result_dir_with_slash );
    strcat ( buff_sos, buff_dir_analyzed );
    strcat ( buff_sar, buff_dir_analyzed );
    strcat ( buff_ps, buff_dir_analyzed );
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
    strcpy ( file_data_obj->sos_file_name_to_be_written, buff_sos );
    /* for sar file */
    strftime ( f_t2, sizeof ( f_t2 ), "_sar_%Y%m%d%H%M%S", timenow );
    strncat ( buff_sar, f_t2, MAX_FILE_NAME_LENGTH - 1 );
    strncat ( buff_sar, ".txt", MAX_FILE_NAME_LENGTH - 1 );
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strcpy ( file_data_obj->sar_file_name_to_be_written, buff_sar );
    /* for ps file */
    strftime ( f_t3, sizeof ( f_t3 ), "_ps_%Y%m%d%H%M%S", timenow );
    strncat ( buff_ps, f_t3, MAX_FILE_NAME_LENGTH - 1 );
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strcpy ( file_data_obj->ps_file_name_to_be_written, buff_ps );
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
        ( strcmp ( member, "var/log/messages" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/kernel/sysctl_-a" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/scsi/lsscsi" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 )
    )
    {
        if ( strstr ( line , item ) != NULL )
            append_list ( &sos_line_obj, line );
    }
    return EXIT_SUCCESS;
}
