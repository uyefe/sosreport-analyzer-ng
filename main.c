/*
 * main.c - main file for sosreport-analyzer.
 * This file contains the contents of sosreport-analyzer.
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

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libsosreport-analyzer/cfg.h"
#include "libsosreport-analyzer/common.h"
#include "libsosreport-analyzer/line_data.h"

/* configuration file of this program/library */
static const char *fname = "/etc/sosreport-analyzerd.conf";

const char *app_name = "sosreport-analyzer-ng";

/* brief Print help for this application */
static void print_help ( void )
{
    printf("\n VERSION %d.%d.%d\n",PROGRAM_VERSION,PROGRAM_RELEASE,PROGRAM_SUB_RELEASE);
    printf("\n Before use: Edit %s.\n", fname);
    printf("\n If you are unsure, copy from /usr/share/sosreport-analyzerd/sosreport-analyzerd.conf.example to %s.\n", fname);
    printf("\n Usage: %s -D <path_to_sosreport_directory>  \n\n", app_name);
    printf("  Options:\n");
    printf("   -D|--directory <path_to_sosreport_directory>   analyze files in the directory\n\n");
    printf("   -h|--help      Print this help\n\n");
    printf("\n");
}

/* Main function */
int main ( int argc, char *argv [ ] )
{
    if ( argc <=2 )
    {
        print_help ( );
        return EXIT_FAILURE;
    }
    static struct option long_options [ ] = {
        { "directory", required_argument, 0, 'D' },
        { "help", no_argument, 0, 'h' },
        { NULL, 0, 0, 0 }
    };
    int value = 0, option_index = 0, dir_len = 0;
    int dir_len_check = 256;
    const char *dir_name = NULL;

    sos_header_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    sos_line_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    sos_tail_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    var_log_messages_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    if ( ( sos_header_obj == NULL ) || ( sos_line_obj == NULL ) || ( sos_tail_obj == NULL ) )
    {
        printf ("Failed to allocate memory for report obj.");
        free ( sos_header_obj );
        free ( sos_line_obj );
        free ( sos_tail_obj );
        free ( var_log_messages_obj );
        sos_header_obj = NULL;
        sos_line_obj = NULL;
        sos_tail_obj = NULL;
        var_log_messages_obj = NULL;
    }
    /* initialize the line list object (node) */
    init_list ( &sos_header_obj );
    init_list ( &sos_line_obj );
    init_list ( &sos_tail_obj );
    init_list ( &var_log_messages_obj );

    char str_tmp [ MAX_LINE_LENGTH ]; 
    char str_tmp2 [ MAX_LINE_LENGTH ]; 
    memset ( str_tmp, '\0', MAX_LINE_LENGTH ); 
    memset ( str_tmp2, '\0', MAX_LINE_LENGTH ); 
    append_list ( &sos_header_obj, "########" );
    snprintf ( str_tmp2, MAX_LINE_LENGTH, "%s: Version-%d.%d.%d", app_name, PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE ); 
    append_list ( &sos_header_obj, str_tmp2 );
    append_list ( &sos_header_obj, "########" );
    append_list ( &sos_tail_obj, "########" );
    memset ( str_tmp2, '\0', MAX_LINE_LENGTH ); 
    snprintf ( str_tmp2, MAX_LINE_LENGTH, "%s ends.", app_name ); 
    append_list ( &sos_tail_obj, str_tmp2 );
    /* Try to process all command line arguments */
    while ( ( value = getopt_long ( argc, argv, "hD:", long_options, &option_index ) ) != -1 ) {
        switch ( value ) {
            case 'D':
                dir_name = optarg;
                dir_len = strlen ( dir_name );
                if ( strstr ( dir_name,"\n" ) != NULL || ( dir_len > dir_len_check ) )
                {
                    printf("Can't analyze this directory.\n");
                    print_help ( );
                    return EXIT_FAILURE;
                }else{
                    memset ( str_tmp2, '\0', MAX_LINE_LENGTH ); 
                    snprintf ( str_tmp2, MAX_LINE_LENGTH, "dirname:%s",dir_name );
                    append_list ( &sos_header_obj, str_tmp2 );
                    append_list ( &sos_header_obj, "" );
                    break;
                }
            case 'h':
                print_help ( );
                return EXIT_SUCCESS;
                case '?':
                print_help ( );
                return EXIT_FAILURE;
            default:
                print_help ( );
                return EXIT_FAILURE;
                break;
        }
    }
    /* read sosreport files */
    cfg_init ( fname );
    read_file_pre ( "date", dir_name );
    read_file_pre ( "lsb-release", dir_name );
    read_file_pre ( "uname", dir_name );
    read_file_pre ( "hostname", dir_name );
    read_file_pre ( "uptime", dir_name );
    read_file_pre ( "root/anaconda-ks.cfg", dir_name );
    read_file_pre ( "dmidecode", dir_name );
    read_file_pre ( "lsmod", dir_name );
    read_file_pre ( "lspci", dir_name );
    read_file_pre ( "sos_commands/scsi/lsscsi", dir_name );
    read_file_pre ( "installed-rpms", dir_name );
    read_file_pre ( "df", dir_name );
    read_file_pre ( "vgdisplay", dir_name );
    read_file_pre ( "free", dir_name );
    read_file_pre ( "ip_addr", dir_name );
    read_file_pre ( "route", dir_name );
    read_file_pre ( "last", dir_name );
    read_file_pre ( "ps", dir_name );
    read_file_pre ( "lsof", dir_name );
    read_file_pre ( "netstat", dir_name );
    read_file_pre ( "etc/kdump.conf", dir_name );
    read_file_pre ( "etc/sysctl.conf", dir_name );
    read_file_pre ( "proc/meminfo", dir_name );
    read_file_pre ( "proc/interrupts", dir_name );
    read_file_pre ( "proc/net/dev", dir_name );
    read_file_pre ( "proc/net/sockstat", dir_name );
    read_file_pre ( "var/log/messages", dir_name );
    read_file_pre ( "sos_commands/kernel/sysctl_-a", dir_name );
    read_file_pre ( "sos_commands/logs/journalctl_--no-pager", dir_name );
    read_file_pre ( "sos_commands/networking/ethtool_-S", dir_name );
    append_list ( &sos_header_obj, "Also, read these files." );
    append_list ( &sos_header_obj, "--------" );
    append_list ( &var_log_messages_obj, "--------" );
    append_list ( &sos_commands_logs_journalctl___no_pager_obj, "--------" );
    print_list ( &sos_header_obj );
    print_list ( &var_log_messages_obj );
    print_list ( &sos_commands_logs_journalctl___no_pager_obj );
    print_list ( &sos_commands_networking_ethtool__S_obj );
    print_list ( &sos_line_obj );
    print_list ( &sos_tail_obj );
    cfg_clear (); 
    clear_list ( &sos_header_obj ); 
    clear_list ( &sos_line_obj ); 
    clear_list ( &var_log_messages_obj ); 
    clear_list ( &sos_commands_logs_journalctl___no_pager_obj ); 
    clear_list ( &sos_commands_networking_ethtool__S_obj ); 
    clear_list ( &sos_tail_obj ); 
    return EXIT_SUCCESS;
}
