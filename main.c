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

#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libsosreport-analyzer/cfg.h"
#include "libsosreport-analyzer/common.h"
#include "libsosreport-analyzer/line_data.h"
#include "libsar-analyzer/common.h"

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
    if ( ! isatty ( fileno ( stdout ) ) )
    {
        fprintf(stderr,"You are not a terminal!\n");
        fprintf(stderr,"You are not allowed to redirect to a file.\n");
        return EXIT_FAILURE;
    }
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

    sos_dir_file_obj = ( struct dir_file_name * ) malloc ( sizeof ( struct dir_file_name ) );
    memset ( sos_dir_file_obj, 0, sizeof ( struct dir_file_name ) ); 
    sos_header_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    memset ( sos_header_obj, 0, sizeof ( struct line_data ) ); 
    sos_line_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    memset ( sos_line_obj, 0, sizeof ( struct line_data ) ); 
    sos_tail_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    memset ( sos_tail_obj, 0, sizeof ( struct line_data ) ); 
    var_log_messages_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    memset ( var_log_messages_obj, 0, sizeof ( struct line_data ) ); 
    sos_commands_logs_journalctl___no_pager_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    memset ( sos_commands_logs_journalctl___no_pager_obj, 0, sizeof ( struct line_data ) ); 
    sos_commands_networking_ethtool__S_obj = ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
    memset ( sos_commands_networking_ethtool__S_obj, 0, sizeof ( struct line_data ) ); 

    if ( ( sos_dir_file_obj == NULL ) || ( sos_header_obj == NULL ) || ( sos_line_obj == NULL ) || ( sos_tail_obj == NULL ) )
    {
        printf ("Failed to allocate memory for report obj.");
        free ( tmp_obj );
        free ( sos_dir_file_obj );
        free ( sos_header_obj );
        free ( sos_line_obj );
        free ( sos_tail_obj );
        free ( var_log_messages_obj );
        free ( sos_commands_logs_journalctl___no_pager_obj );
        free ( sos_commands_networking_ethtool__S_obj );
        sos_dir_file_obj = NULL;
        sos_header_obj = NULL;
        sos_line_obj = NULL;
        sos_tail_obj = NULL;
        var_log_messages_obj = NULL;
        sos_commands_logs_journalctl___no_pager_obj = NULL;
        sos_commands_networking_ethtool__S_obj = NULL;
    }
    /* initialize the line list object (node) */
    init_list ( &sos_header_obj );
    init_list ( &sos_line_obj );
    init_list ( &sos_tail_obj );
    init_list ( &var_log_messages_obj );
    init_list ( &sos_commands_logs_journalctl___no_pager_obj );
    init_list ( &sos_commands_networking_ethtool__S_obj );

    char str_tmp [ MAX_FILE_NAME_LENGTH ]; 
    char str_tmp2 [ MAX_FILE_NAME_LENGTH ]; 
    memset ( str_tmp, '\0', MAX_FILE_NAME_LENGTH ); 
    memset ( str_tmp2, '\0', MAX_FILE_NAME_LENGTH ); 
    append_list ( &sos_header_obj, "########" );
    snprintf ( str_tmp2, MAX_FILE_NAME_LENGTH, "%s: Version-%d.%d.%d", app_name, PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE ); 
    append_list ( &sos_header_obj, str_tmp2 );
    append_list ( &sos_header_obj, "########" );
    append_list ( &sos_tail_obj, "########" );
    memset ( str_tmp2, '\0', MAX_FILE_NAME_LENGTH ); 
    snprintf ( str_tmp2, MAX_FILE_NAME_LENGTH, "%s ends.", app_name ); 
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
                    strcpy ( sos_dir_file_obj->dir_file_names.dirname, dir_name );
                    strcpy ( str_tmp2, reverse_the_string ( ( char * ) dir_name, strlen ( dir_name ) ) );
                    for ( int i = 0; i < strlen ( dir_name ); i++ )
                    {
                        if ( i > 0 )
                            str_tmp2[i] = '\0';
                    }    
                    if ( strcmp ( str_tmp2, "/" ) == 0 )
                    {
                        strcpy ( str_tmp2, ( char * ) dir_name );
                        str_tmp2 [ strlen ( dir_name ) -1 ] = '\0';
                        strcpy ( sos_dir_file_obj->dir_file_names.dirname, str_tmp2 );
                    }
                    snprintf ( str_tmp2, MAX_FILE_NAME_LENGTH, "dirname:%s",dir_name );
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

    sos_file_to_write ( );

    const char *sos_file_write = ""; 
    FILE *fp_w;
    /* --------  for file write --------*/
    sos_file_write = get_sos_file_name_to_be_written ( );
    /* open result directory */
    char str_dir_result [ MAX_FILE_NAME_LENGTH ]; 
    memset ( str_dir_result, '\0', MAX_FILE_NAME_LENGTH ); 
    strncpy ( str_dir_result, "./sosreport-analyzer-results", MAX_FILE_NAME_LENGTH );
    if ( check_result_dir ( str_dir_result ) != 0 )
        printf("can't open dir %s (%s)\n",str_dir_result,strerror(errno));

    /* open result file */
    if ( ( fp_w = fopen ( sos_file_write, "a" ) ) == NULL )
    {
        printf("can't open file (%s): %s\n",sos_file_write,strerror(errno));
        exit ( EXIT_FAILURE );
    }
    file_write_list ( &sos_header_obj, fp_w );
    file_write_list ( &var_log_messages_obj, fp_w );
    file_write_list ( &sos_commands_logs_journalctl___no_pager_obj, fp_w );
    file_write_list ( &sos_commands_networking_ethtool__S_obj, fp_w );
    file_write_list ( &sos_line_obj, fp_w );
    file_write_list ( &sos_tail_obj, fp_w );
    /* printf("Wrote file to ./%s\n",sos_file_write); */
    
    /* close the file pointer */
    fclose ( fp_w );

    /* for sar-analyzer stuff */
    int SAR_OPTION = 'Z';
    int REPORT = 0;
    int MESSAGE_ONLY = 1;
    /*
     *  initialize sar_analyzer object, line object
     *  also, starts analyzing
     */
    const char *file_name = NULL;
    memset ( str_tmp, '\0', MAX_FILE_NAME_LENGTH ); 
    snprintf ( str_tmp, MAX_FILE_NAME_LENGTH, "%s/var/log/sa", ( char * ) get_dirname ( ) ); 
    sar_analyzer_init ( str_tmp, file_name, SAR_OPTION, REPORT, MESSAGE_ONLY );
    char str_num [ MAX_FILE_NAME_LENGTH + 1 ] = { '\0' };
    char str_tmp_sar [ 10 ] = "dir_name:";
    strncpy ( str_num, str_tmp_sar, 10 );
    strncat ( str_num, get_dir_name_analyze ( ), MAX_DIR_NAME_LENGTH );
    append_list ( &report_obj, "--------" );
    append_list ( &report_obj, str_num );
    append_list ( &report_obj, "--------" );

    print_list ( &line_all_obj );
    /* print 'files names' which had been analyzed*/
    print_and_file_write_analyzed_files ( &line_all_obj, "filename", "print" ,NULL );
    /* printing report objects */
    print_list ( &line_all_obj );
    print_list ( &header_obj );
    print_list ( &report_cpu_obj );
    for ( int v = 0; v <= get_core_numbers ( ); v++ )
        print_list ( &report_cpu_spike_obj [ v ] );
    print_list ( &report_cpu_explanation_obj );
    print_list ( &report_tasks_obj );
    print_list ( &report_tasks_spike_obj );
    print_list ( &report_tasks_explanation_obj );
    print_list ( &report_pswap_obj );
    print_list ( &report_pswap_spike_obj );
    print_list ( &report_pswap_explanation_obj );
    print_list ( &report_paging_obj );
    print_list ( &report_paging_spike_obj );
    print_list ( &report_paging_explanation_obj );
    print_list ( &report_io_transfer_rate_obj );
    print_list ( &report_io_transfer_rate_spike_obj );
    print_list ( &report_io_transfer_rate_explanation_obj );
    print_list ( &report_memory_obj );
    print_list ( &report_memory_spike_obj );
    print_list ( &report_memory_explanation_obj );
    print_list ( &report_swpused_obj );
    print_list ( &report_swpused_spike_obj );
    print_list ( &report_swpused_explanation_obj );
    print_list ( &report_kernel_table_obj );
    print_list ( &report_kernel_table_spike_obj );
    print_list ( &report_kernel_table_explanation_obj );
    print_list ( &report_ldavg_obj );
    print_list ( &report_ldavg_spike_obj );
    print_list ( &report_ldavg_explanation_obj );
    print_list ( &report_block_device_obj );
    for ( int v = 0; v <= get_block_device_numbers ( ); v++ )
        print_list ( &report_block_device_spike_obj [ v ] );
    print_list ( &report_block_device_explanation_obj );
    print_list ( &report_network_obj );
    for ( int v = 0; v <= get_network_device_numbers ( ); v++ )
        print_list ( &report_network_spike_obj [ v ] );
    print_list ( &report_network_explanation_obj );
    print_list ( &report_network_error_obj );
    for ( int v = 0; v <= get_network_device_numbers ( ); v++ )
        print_list ( &report_network_error_spike_obj [ v ] );
    print_list ( &report_network_error_explanation_obj );
    print_list ( &report_thrashing_obj );
    for ( int v = 0; v <= get_network_device_numbers ( ); v++ )
        print_list ( &report_network_down_obj [ v ] );
    print_list ( &report_obj );
    /* print "Linux" lines (top of sar file)*/
    print_and_file_write_analyzed_files ( &line_all_obj, "Linux", "print" ,NULL );
    /* --------  for file write --------*/
    /* creating file name to be written from SAR_OPTION */
    file_to_write ( SAR_OPTION );

    const char *sar_file_write = ""; 
    char *file_ps_write = "";
    /* --------  for file write --------*/
    sar_file_write = get_sar_file_name_to_be_written ( );
    file_ps_write = ( char * ) get_ps_file_name_to_be_written ( );
    FILE *fp_sar_w;
    FILE *fp_ps_w [ MAX_ANALYZE_FILES ];
    FILE *fp_ps2_w [ MAX_ANALYZE_FILES ];
    FILE *fp_ps3_w [ MAX_ANALYZE_FILES ];
    FILE *fp_ps4_w [ MAX_ANALYZE_FILES ];

    /* open result file */
    if ( ( fp_sar_w = fopen ( sar_file_write, "a" ) ) == NULL )
    {
        printf("can't open file (%s): %s\n",sar_file_write,strerror(errno));
        exit ( EXIT_FAILURE );
    }

    print_and_file_write_analyzed_files ( &line_all_obj, "filename", NULL, fp_sar_w );

    /* writing report object to result file */
    file_write_list ( &line_all_obj, fp_sar_w );
    file_write_list ( &header_obj, fp_sar_w );
    file_write_list ( &report_cpu_obj, fp_sar_w );
    for ( int v = 0; v <= get_core_numbers ( ); v++ )
        file_write_list ( &report_cpu_spike_obj [ v ], fp_sar_w );
    file_write_list ( &report_cpu_explanation_obj, fp_sar_w );
    file_write_list ( &report_tasks_obj, fp_sar_w );
    file_write_list ( &report_tasks_spike_obj, fp_sar_w );
    file_write_list ( &report_tasks_explanation_obj, fp_sar_w );
    file_write_list ( &report_pswap_obj, fp_sar_w );
    file_write_list ( &report_pswap_spike_obj, fp_sar_w );
    file_write_list ( &report_pswap_explanation_obj, fp_sar_w );
    file_write_list ( &report_paging_obj, fp_sar_w );
    file_write_list ( &report_paging_spike_obj, fp_sar_w );
    file_write_list ( &report_paging_explanation_obj, fp_sar_w );
    file_write_list ( &report_io_transfer_rate_obj, fp_sar_w );
    file_write_list ( &report_io_transfer_rate_spike_obj, fp_sar_w );
    file_write_list ( &report_io_transfer_rate_explanation_obj, fp_sar_w );
    file_write_list ( &report_memory_obj, fp_sar_w );
    file_write_list ( &report_memory_spike_obj, fp_sar_w );
    file_write_list ( &report_memory_explanation_obj, fp_sar_w );
    file_write_list ( &report_swpused_obj, fp_sar_w );
    file_write_list ( &report_swpused_spike_obj, fp_sar_w );
    file_write_list ( &report_swpused_explanation_obj, fp_sar_w );
    file_write_list ( &report_kernel_table_obj, fp_sar_w );
    file_write_list ( &report_kernel_table_spike_obj, fp_sar_w );
    file_write_list ( &report_kernel_table_explanation_obj, fp_sar_w );
    file_write_list ( &report_ldavg_obj, fp_sar_w );
    file_write_list ( &report_ldavg_spike_obj, fp_sar_w );
    file_write_list ( &report_ldavg_explanation_obj, fp_sar_w );
    file_write_list ( &report_block_device_obj, fp_sar_w );
    for ( int v = 0; v <= get_block_device_numbers ( ); v++ )
        file_write_list ( &report_block_device_spike_obj [ v ], fp_sar_w );
    file_write_list ( &report_block_device_explanation_obj, fp_sar_w );
    file_write_list ( &report_network_obj, fp_sar_w );
    for ( int v = 0; v <= get_network_device_numbers ( ); v++ )
        file_write_list ( &report_network_spike_obj [ v ], fp_sar_w );
    file_write_list ( &report_network_explanation_obj, fp_sar_w );
    file_write_list ( &report_network_error_obj, fp_sar_w );
    for ( int v = 0; v <= get_network_device_numbers ( ); v++ )
        file_write_list ( &report_network_error_spike_obj [ v ], fp_sar_w );
    file_write_list ( &report_network_error_explanation_obj, fp_sar_w );
    file_write_list ( &report_thrashing_obj, fp_sar_w );
    for ( int v = 0; v <= get_network_device_numbers ( ); v++ )
        file_write_list ( &report_network_down_obj [ v ], fp_sar_w );
    file_write_list ( &report_obj, fp_sar_w );

    /* writing "Linux" lines (top of sar file) to result file */
    print_and_file_write_analyzed_files ( &line_all_obj, "Linux", NULL, fp_sar_w );

    puts("------------------------");
    printf("Please check result file ./%s\n",sos_file_write);
    printf("Also check sar result file ./%s\n",sar_file_write);

    /* close the file pointers */
    fclose ( fp_sar_w );

    for ( int v = 0, x = 1; v < MAX_ANALYZE_FILES; v++, x++ )
    {
        char str_tmp [ MAX_LINE_LENGTH ] = { '\0' };
        memset ( str_tmp, '\0', MAX_LINE_LENGTH );
        snprintf ( str_tmp, MAX_LINE_LENGTH, "%s%s%d%s", file_ps_write, "-cpu-", x, ".ps" );
        if ( ( fp_ps_w [ v ] = fopen ( str_tmp,"a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n",str_tmp,strerror(errno));
            exit ( EXIT_FAILURE );
        }
        snprintf ( str_tmp, MAX_LINE_LENGTH, "%s%s%d%s", file_ps_write, "-mem-", x, ".ps" );
        if ( ( fp_ps2_w [ v ] = fopen ( str_tmp,"a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n",str_tmp,strerror(errno));
            exit ( EXIT_FAILURE );
        }
        snprintf ( str_tmp, MAX_LINE_LENGTH, "%s%s%d%s", file_ps_write, "-ldv-", x, ".ps" );
        if ( ( fp_ps3_w [ v ] = fopen ( str_tmp,"a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n",str_tmp,strerror(errno));
            exit ( EXIT_FAILURE );
        }
        snprintf ( str_tmp, MAX_LINE_LENGTH, "%s%s%d%s", file_ps_write, "-ior-", x, ".ps" );
        if ( ( fp_ps4_w [ v ] = fopen ( str_tmp,"a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n",str_tmp,strerror(errno));
            exit ( EXIT_FAILURE );
        }
    }
    /* appending needed lines to ps obj -- this is needed we don't know the last line of each graph when drawing */
    for ( int v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for file cpu */
        append_list ( &ps_cpu_usr_obj [ v ], "stroke");
        append_list ( &ps_cpu_sys_obj [ v ] , "stroke");
        append_list ( &ps_cpu_iowait_obj [ v ], "stroke");
        append_list ( &ps_cpu_idle_obj [ v ], "stroke");
        append_list ( &ps_paging_pgpgin_obj [ v ], "stroke");
        append_list ( &ps_paging_pgpgout_obj [ v ], "stroke");
        append_list ( &ps_paging_fault_obj [ v ], "stroke");
        append_list ( &ps_paging_mjflt_obj [ v ], "stroke");
        append_list ( &ps_paging_vmeff_obj [ v ], "stroke");
        /* for file mem */
        append_list ( &ps_memory_memused_obj [ v ], "stroke");
        append_list ( &ps_memory_kbcommit_obj [ v ], "stroke");
        append_list ( &ps_memory_commit_obj [ v ], "stroke");
        append_list ( &ps_swapping_pswpin_obj [ v ], "stroke");
        append_list ( &ps_swapping_pswpout_obj [ v ], "stroke");
        /* for file ldv */
        append_list ( &ps_ldavg_runq_obj [ v ], "stroke");
        append_list ( &ps_ldavg_plist_obj [ v ], "stroke");
        append_list ( &ps_ldavg_ldavg_one_obj [ v ], "stroke");
        append_list ( &ps_ldavg_ldavg_five_obj [ v ], "stroke");
        append_list ( &ps_ldavg_ldavg_15_obj [ v ], "stroke");
        append_list ( &ps_tasks_proc_obj [ v ], "stroke");
        append_list ( &ps_tasks_cswch_obj [ v ], "stroke");
        /* for file ior */
        append_list ( &ps_io_transfer_rate_tps_obj [ v ], "stroke");
        append_list ( &ps_io_transfer_rate_bread_obj [ v ], "stroke");
        append_list ( &ps_io_transfer_rate_bwrtn_obj [ v ], "stroke");
        append_list ( &ps_kernel_table_dentunusd_obj [ v ], "stroke");
        append_list ( &ps_kernel_table_file_obj [ v ], "stroke");
        append_list ( &ps_kernel_table_inode_obj [ v ], "stroke");
        /* for linux restart string */
        append_list ( &ps_restart_obj [ v ], "stroke");
        append_list ( &ps_restart_obj [ v ], "%");
    }
    /* appending needed lines to ps obj -- adding % to the very last of each ps file */
    for ( int v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for file cpu */
        append_list ( &ps_paging_vmeff_obj [ v ], "%");
        /* for file mem */
        append_list ( &ps_swapping_pswpout_obj [ v ], "%");
        /* for file ldv */
        append_list ( &ps_ldavg_ldavg_15_obj [ v ], "%");
        /* for file ior */
        append_list ( &ps_kernel_table_inode_obj [ v ], "%");
    }
    /* appending needed lines to ps obj -- adding % to the very last of each box */
    for ( int v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for file cpu */
        append_list ( &ps_cpu_label_obj [ v ], "stroke");
        append_list ( &ps_cpu_label_obj [ v ], "%");
        append_list ( &ps_paging_label_obj [ v ], "stroke");
        append_list ( &ps_paging_label_obj [ v ], "%");
        /* for file mem */
        append_list ( &ps_memory_label_obj [ v ], "stroke");
        append_list ( &ps_memory_label_obj [ v ], "%");
        append_list ( &ps_swapping_label_obj [ v ], "stroke");
        append_list ( &ps_swapping_label_obj [ v ], "%");
        /* for file ldv */
        append_list ( &ps_ldavg_label_obj [ v ], "stroke");
        append_list ( &ps_ldavg_label_obj [ v ], "%");
        append_list ( &ps_tasks_label_obj [ v ], "stroke");
        append_list ( &ps_tasks_label_obj [ v ], "%");
        /* for file ior */
        append_list ( &ps_io_transfer_rate_label_obj [ v ], "stroke");
        append_list ( &ps_io_transfer_rate_label_obj [ v ], "%");
        append_list ( &ps_kernel_table_label_obj [ v ], "stroke");
        append_list ( &ps_kernel_table_label_obj [ v ], "%");
    }
    /* now we write obj to postscript (.ps) file */
    for ( int v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for file cpu */
        file_write_list ( &ps_common_cpu_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_label_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_usr_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_sys_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_iowait_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_idle_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_label_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_pgpgin_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_pgpgout_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_fault_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_mjflt_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_vmeff_obj [ v ], fp_ps_w [ v ] );
        /* for file mem */
        file_write_list ( &ps_common_memory_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_memory_label_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_memory_memused_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_memory_kbcommit_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_memory_commit_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_swapping_label_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_swapping_pswpin_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_swapping_pswpout_obj [ v ], fp_ps2_w [ v ] );
        /* for file ldv */
        file_write_list ( &ps_common_ldavg_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_label_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_runq_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_plist_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_ldavg_one_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_ldavg_five_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_ldavg_15_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_tasks_label_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_tasks_proc_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_tasks_cswch_obj [ v ], fp_ps3_w [ v ] );
        /* for file ior */
        file_write_list ( &ps_common_io_transfer_rate_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_io_transfer_rate_label_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_io_transfer_rate_tps_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_io_transfer_rate_bread_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_io_transfer_rate_bwrtn_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_kernel_table_label_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_kernel_table_dentunusd_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_kernel_table_file_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_kernel_table_inode_obj [ v ], fp_ps4_w [ v ] );
        /* for linux restart string */
        file_write_list ( &ps_restart_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_restart_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_restart_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_restart_obj [ v ], fp_ps4_w [ v ] );
    }
    char str_tmp_echo [ MAX_LINE_LENGTH ] = { '\0' };
    memset ( str_tmp_echo, '\0', MAX_LINE_LENGTH );
    snprintf ( str_tmp_echo, MAX_LINE_LENGTH, "%s%s", file_ps_write, "-<item>-<no>.ps" );
    printf("Please check graphs in the ps file: %s\n\n",str_tmp_echo);
    /* close the file pointers */
    for ( int v = 0; v < MAX_ANALYZE_FILES; v++ )
    { 
        fclose ( fp_ps_w [ v ] );
        fclose ( fp_ps2_w [ v ] );
        fclose ( fp_ps3_w [ v ] );
        fclose ( fp_ps4_w [ v ] );
    }

    cfg_clear (); 

    free ( sos_dir_file_obj );
    sos_dir_file_obj = NULL;
    free ( sos_header_obj );
    sos_header_obj = NULL;
    free ( sos_line_obj );
    sos_line_obj = NULL;
    free ( var_log_messages_obj );
    var_log_messages_obj = NULL;
    free ( sos_commands_logs_journalctl___no_pager_obj );
    sos_commands_logs_journalctl___no_pager_obj = NULL;
    free ( sos_commands_networking_ethtool__S_obj );
    sos_commands_networking_ethtool__S_obj = NULL;
    free ( sos_tail_obj );
    sos_tail_obj = NULL;

    clear_list ( &sos_header_obj ); 
    sos_header_obj = NULL;
    clear_list ( &sos_line_obj ); 
    sos_line_obj = NULL;
    clear_list ( &var_log_messages_obj ); 
    var_log_messages_obj = NULL;
    clear_list ( &sos_commands_logs_journalctl___no_pager_obj ); 
    sos_commands_logs_journalctl___no_pager_obj = NULL;
    clear_list ( &sos_commands_networking_ethtool__S_obj ); 
    sos_commands_networking_ethtool__S_obj = NULL;
    clear_list ( &sos_tail_obj ); 
    sos_tail_obj = NULL;

    /* freeing sar-analyzer objects */
    free_sar_analyzer_obj ( );

    return EXIT_SUCCESS;
}
