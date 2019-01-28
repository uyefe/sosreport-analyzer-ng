/*
 *  common.c - common functions 
 *  This file contains the contents of sar-analyzer.
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

#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "common.h"
#include "../libsosreport-analyzer/line_data.h"
#include "setter_getter.h"
#include "../common/global.c"
#include "check.c"

void initialize_block_device_name ( void )
{
    int x = 0;

    /* for sar_analyzer_obj */
    strcpy ( sar_analyzer_obj->device_names [ 0 ], "first" );
    for ( x = 1; x <= MAX_BLOCK_DEVICE_NUMBERS; x++ )
        strcpy ( sar_analyzer_obj->device_names [ x ], "ignore" );

    /* for sar_analyzer_all_obj */
    strcpy ( sar_analyzer_all_obj->device_names [ 0 ], "first" );
    for ( x = 1; x <= MAX_BLOCK_DEVICE_NUMBERS; x++ )
        strcpy ( sar_analyzer_all_obj->device_names [ x ], "ignore" );
}

void initialize_network_device_name ( void )
{
    int x = 0;

    /* for sar_analyzer_obj */
    strcpy ( sar_analyzer_obj->network_device_names [ 0 ], "first" );
    for ( x = 1; x <= MAX_NETWORK_DEVICE_NUMBERS; x++ )
        strcpy ( sar_analyzer_obj->network_device_names [ x ], "ignore" );

    /* for sar_analyzer_all_obj */
    strcpy ( sar_analyzer_all_obj->network_device_names [ 0 ], "first" );
    for ( x = 1; x <= MAX_NETWORK_DEVICE_NUMBERS; x++ )
        strcpy ( sar_analyzer_all_obj->network_device_names [ x ], "ignore" );
}

int search_network_device_name ( const char *network_device_name )
{
    int x = 0;
    for (x = 1; x <= get_network_device_numbers (); x++ )
    {
        if ( strcmp ( ( char * ) get_network_device_names ( x ), network_device_name ) == 0 )
        {
            return x;
        }
    }
    return (0);
}

void set_dir_name_analyze ( const char *dname )
{
    sar_analyzer_obj->dir_name_analyze = dname;
}

void set_hostname ( char *hostname )
{
    strcpy ( sar_analyzer_all_obj->hostname, hostname );
}

void set_files_n ( int var )
{
    sar_analyzer_obj->files_n = var;
}

void read_sa_dir ( const char *dname, int SAR_OPTION, int REPORT, int MESSAGE_ONLY )
{
    DIR *dir;
    struct dirent *dp;
    dir = opendir ( dname ); 
    char *str, *str_tmp;
    int i = 0, ii = 0 , j = 0, files_n = 0;

    /* limit of sar files to be analyzed */
    char *str_arr [ MAX_ANALYZE_FILES ];

    int str_arr_valid_size = 0;

    /* read from directory and set in an array */
    for ( dp = readdir ( dir ); dp != NULL; dp = readdir ( dir ) )
    {
        if ( dp->d_type != DT_REG )
            continue;
        str = dp->d_name;
        /*
         *  find files with name sar
         *  skip reading "sar_all" file 
         */
        if ( strstr ( str, "sar_all" ) != 0 )
            continue;
        if ( strstr ( str, "sar" ) != 0 )
        {
            /* exclude files with name tar or bz */
            if ( strstr ( str, "tar" ) == 0 && strstr ( str, "bz" ) == 0 )
            {
                /* so, only sar[0-9][0-9] files will remain */
                str_arr [ str_arr_valid_size ] = str;
                str_arr_valid_size++;
                if ( str_arr_valid_size == MAX_ANALYZE_FILES -1 )
                    break;
            }
        }
    }

    /* Check the number of files in the directory and if 0, exit */
    if ( str_arr_valid_size == 0 )
    {
        printf("-There are no sar files in this directory (%s):%s\n",dname,strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }

    /* bubble sort the array */

    for ( j= 0; j < str_arr_valid_size; j++ )
    {
        /* This makes largest item to the end of an array. */
        for ( i = 0; i < str_arr_valid_size - ( 1 + j ); i++ )
        {
            ii = i + 1;
            if ( strcmp ( str_arr [ i ], str_arr [ ii ] ) > 0 )
            {
                str_tmp = str_arr [ i ]; 
                str_arr [ i ] = str_arr [ ii ]; 
                str_arr [ ii ] = str_tmp; 
            }
        }
    }

    /* end bubble sort */

    /* sets total file numbers to the struct */
    files_n = str_arr_valid_size;
    set_files_n ( files_n );

    /* now pass an array to the function, this will be done by passing first pointer of an array */
    read_write_file ( dir, dname, str_arr, files_n, SAR_OPTION, REPORT, MESSAGE_ONLY );

    /* freeing memory */
    for ( i = 0; i < MAX_ANALYZE_FILES; i++ )
        str_arr[i]=NULL;
}

void read_write_file ( DIR *dir, const char *dname, char *sar_arr [ ], int files_n, int SAR_OPTION, int REPORT, int MESSAGE_ONLY )
{
    int dname_len = ( int ) strlen ( dname );
    if ( dname_len <= 0 )
    {
        printf("no dir name supplied (%s): %d %s\n",dname,dname_len,strerror(errno));
        /* freeing object and setting it to NULL */
        for ( int i = 0; i < files_n; i++ )
            sar_arr[i]=NULL;
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    if ( dname_len > MAX_DIR_NAME_LENGTH )
    {
        printf("directory name too long (%s): %d %s\n",dname,dname_len,strerror(errno));
        /* freeing object and setting it to NULL */
        for ( int i = 0; i < files_n; i++ )
            sar_arr[i]=NULL;
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    /* stripping last slash if any */

    int i = 0;
    /* new array: MAX_ANALYZE_FILES tupples with MAX_DIR_NAME_LENGTH characters */

    char sar_full_path_arr [ MAX_ANALYZE_FILES ] [ MAX_DIR_NAME_LENGTH ] = { { 0 } };
    
    int ii = 0;
    char full_path [ MAX_FULL_PATH_LENGTH ];
    memset ( full_path, '\0', sizeof ( full_path ) ); 
    for ( i = 0; i < files_n; i++ )
    {
        /* this is needed for initializing */
        for ( ii = 0; ii < MAX_FULL_PATH_LENGTH; ii++ )
            full_path [ ii ] = '\0';
        strncpy ( full_path, dname, MAX_DIR_NAME_LENGTH - 1 );
        strncat ( full_path, "/", MAX_DIR_NAME_LENGTH - 1  );
        strncat ( full_path, sar_arr [ i ], MAX_DIR_NAME_LENGTH - 1 );
        strncpy ( sar_full_path_arr [ i ], full_path, MAX_FULL_PATH_LENGTH );
        /* freeing memory */
        sar_arr[i]=NULL;
    }
    /* read sar files for sanity check */
    for ( i = 0; i < files_n; i++ )
    {
        char str_tmp [ 17 ] = "--------file no.";
        char str_num [ 50 ] = { '\0' };
        snprintf ( str_num, MAX_INPUT, "%s%d", str_tmp, i + 1 );
        /* let 'read_sar_check()' do the job */
        initialize_avg_checked_int ( );
        read_sar_check ( i, sar_full_path_arr [ i ], SAR_OPTION );
    }

    if ( SAR_OPTION == 'Z' )
    {
        append_list ( &header_obj, "" );
        append_list ( &header_obj, "sar file sanity check PASS" );
    }
    else
    {
        append_list ( &line_obj, "" );
        append_list ( &line_obj, "sar file sanity check PASS" );
    }

    /* read one sar file and set cpu paragraph to CHECK_AS_PARAGRAPH */
    /* let 'read_cpu_each()' do the job */
    initialize_avg_checked_int ( );
    read_sar_cpu_as_paragraph ( sar_full_path_arr [ 0 ] );

    /**** here we create postscript file for the future use ****/
    FILE *fp_ps_w [ MAX_ANALYZE_FILES ];
    FILE *fp_ps2_w [ MAX_ANALYZE_FILES ];
    FILE *fp_ps3_w [ MAX_ANALYZE_FILES ];
    FILE *fp_ps4_w [ MAX_ANALYZE_FILES ];

    /* open postscript dummy file here just to set data to the each object */
    for ( i = 0; i < MAX_ANALYZE_FILES; i++ )
    {
        /* -------- ps file -------- */
        if ( ( fp_ps_w [ i ] = fopen ( "dummy.ps", "a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n","dummy.ps",strerror(errno));
            for ( int i = 0; i < files_n; i++ )
                sar_arr[i]=NULL;
            free_sar_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }

        /* appending headers to ps obj */
        append_header_to_ps_objs ( &ps_common_cpu_obj [ i ], fp_ps_w [ i ] );
        /* appending rectangulars to ps obj */
        append_rectangular_to_ps_objs ( &ps_common_cpu_obj [ i ], fp_ps_w [ i ], "up" );
        append_rectangular_to_ps_objs ( &ps_common_cpu_obj [ i ], fp_ps_w [ i ], "down" );
        /* appending labels to ps obj */
        append_labels_to_ps_obj ( &ps_common_cpu_obj [ i ], fp_ps_w [ i ], "cpu" );

        pclose ( fp_ps_w [ i ] );

        /* --------  ps file -------- */
        if ( ( fp_ps2_w [ i ] = fopen ( "dummy2.ps", "a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n","dummy2.ps",strerror(errno));
            for ( int i = 0; i < files_n; i++ )
                sar_arr[i]=NULL;
            free_sar_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }

        /* appending headers to ps obj */
        append_header_to_ps_objs ( &ps_common_memory_obj [ i ], fp_ps2_w [ i ] );
        /* appending rectangulars to ps obj */
        append_rectangular_to_ps_objs ( &ps_common_memory_obj [ i ], fp_ps2_w [ i ], "up" );
        append_rectangular_to_ps_objs ( &ps_common_memory_obj [ i ], fp_ps2_w [ i ], "down" );
        /* appending labels to ps obj */
        append_labels_to_ps_obj ( &ps_common_memory_obj [ i ], fp_ps2_w [ i ], "memory" );

        pclose ( fp_ps2_w [ i ] );

        /* --------  ps file -------- */
        if ( ( fp_ps3_w [ i ] = fopen ( "dummy3.ps", "a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n","dummy3.ps",strerror(errno));
            for ( int i = 0; i < files_n; i++ )
                sar_arr[i]=NULL;
            free_sar_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }

        /* appending headers to ps obj */
        append_header_to_ps_objs ( &ps_common_ldavg_obj [ i ], fp_ps3_w [ i ] );
        /* appending rectangulars to ps obj */
        append_rectangular_to_ps_objs ( &ps_common_ldavg_obj [ i ], fp_ps3_w [ i ], "up" );
        append_rectangular_to_ps_objs ( &ps_common_ldavg_obj [ i ], fp_ps3_w [ i ], "down" );
        /* appending labels to ps obj */
        append_labels_to_ps_obj ( &ps_common_ldavg_obj [ i ], fp_ps3_w [ i ], "ldavg" );

        pclose ( fp_ps3_w [ i ] );

        /* --------  ps file -------- */
        if ( ( fp_ps4_w [ i ] = fopen ( "dummy4.ps", "a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n","dummy4.ps",strerror(errno));
            for ( int i = 0; i < files_n; i++ )
                sar_arr[i]=NULL;
            free_sar_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }

        /* appending headers to ps obj */
        append_header_to_ps_objs ( &ps_common_io_transfer_rate_obj [ i ], fp_ps4_w [ i ] );
        /* appending rectangulars to ps obj */
        append_rectangular_to_ps_objs ( &ps_common_io_transfer_rate_obj [ i ], fp_ps4_w [ i ], "up" );
        append_rectangular_to_ps_objs ( &ps_common_io_transfer_rate_obj [ i ], fp_ps4_w [ i ], "down" );
        /* appending labels to ps obj */
        append_labels_to_ps_obj ( &ps_common_io_transfer_rate_obj [ i ], fp_ps4_w [ i ], "io_transfer_rate" );

        pclose ( fp_ps4_w [ i ] );
    }
    /**** end here we create postscript file for the future use ****/

    /* read sar files */
    for ( i = 0; i < files_n; i++ )
    {
        char str_tmp [ 17 ] = "--------file no.";
        char str_num [ 50 ] = { '\0' };
        snprintf ( str_num, MAX_INPUT, "%s%d", str_tmp, i + 1 );
        if ( SAR_OPTION == 'Z' )
            append_list ( &line_all_obj, str_num );
        else
            append_list ( &line_obj, str_num );
        /* let 'read_sar()' do the job */
        read_sar ( i, sar_full_path_arr [ i ], SAR_OPTION, REPORT, MESSAGE_ONLY );
        /* doing average anlyzing also even in Z option, results should be treated in make_report function later on */
        if ( SAR_OPTION == 'Z' )
            read_sar ( i, sar_full_path_arr [ i ], 'A', REPORT, MESSAGE_ONLY );
    }
    /* closing dir pointer here */
    closedir ( dir );

    make_report ( SAR_OPTION, REPORT, files_n );
}

void read_sar_cpu_as_paragraph ( const char *filename )
{
    FILE *fp;
    int lnr = 0;
    struct stat;
    char linebuf [ MAX_LINE_LENGTH ];
    char *line;
    int i;
    int _cpu_as_paragraph = 0;

    /* open sar file */
    if ( ( fp=fopen ( filename,"r" ) ) == NULL )
    {
        printf("can't open file (%s): %s\n",filename,strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    /* read file and parse lines */
    while ( fgets ( linebuf,sizeof ( linebuf ),fp ) != NULL )
    {
        lnr++;
        line = linebuf;
        /* strip newline */
        i = ( int ) strlen ( line );
        if ( ( i <= 0 ) || ( line [ i - 1 ] != '\n' ) )
        {
            printf("%s:%d: line too long or last line missing newline\n Hint:$sed -i 's/\\x00//g' <sar_file>\n",filename,lnr);
            /* freeing object and setting it to NULL */
            free_sar_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }
        line [ i - 1 ] = '\0';
        /* ignore comment lines */
        if ( line [ 0 ] == '#' )
            continue;
        /* strip trailing spaces */
        for ( i--; ( i > 0 ) && isspace ( line [ i -1 ] ) ; i-- )
            line [ i -1 ] = '\0';
        /* count cpu all line and set numbers to cpu_as_paragraph */
        if ( strstr ( *(&line), "Average" ) != 0 )
            break;
        if ( ( strstr ( *(&line), "all" ) != 0 ) ) 
            _cpu_as_paragraph++;
        set_cpu_as_paragraph ( _cpu_as_paragraph );
    }
    /* after reading all lines, close the file pointer */
    fclose ( fp );
}

void read_sar ( int file_number, const char *filename, int SAR_OPTION, int REPORT, int MESSAGE_ONLY )
{
    int filename_len = ( int ) strlen ( filename );
    if ( filename_len <= 0 )
    {
        printf("no file name supplied (%s): %d %s\n",filename,filename_len,strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    if ( filename_len > MAX_FULL_PATH_LENGTH )
    {
        printf("file name too long (%s): %d %s\n",filename,filename_len,strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    FILE *fp;
    int lnr = 0;
    struct stat;
    char linebuf [ MAX_LINE_LENGTH ];
    char *line;
    int i;

    /* open sar file */
    if ( ( fp=fopen ( filename, "r" ) ) == NULL )
    {
        printf("can't open file (%s): %s\n",filename,strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    else
    {
        char str_num [ MAX_FILE_NAME_LENGTH + 1 ] = { '\0' };
        char str_tmp [ 18 ] = "--------filename:";
        strncpy ( str_num, str_tmp, 18 );
        strncat ( str_num, filename, MAX_FILE_NAME_LENGTH );
        if ( SAR_OPTION == 'Z' )
            append_list ( &line_obj, str_num );
        else
            append_list ( &line_all_obj, str_num );
    }

    /* read file and parse lines */
    while ( fgets ( linebuf,sizeof ( linebuf ),fp ) != NULL )
    {
        lnr++;
        line = linebuf;
        /* strip newline */
        i = ( int ) strlen ( line );
        if ( ( i <= 0 ) || ( line [ i - 1 ] != '\n' ) )
        {
            printf("%s:%d: line too long or last line missing newline\n Hint:$sed -i 's/\\x00//g' <sar_file>\n",filename,lnr);
            /* freeing object and setting it to NULL */
            free_sar_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }
        line [ i - 1 ] = '\0';
        /* ignore comment lines */
        if ( line [ 0 ] == '#' )
            continue;
        /* strip trailing spaces */
        for ( i--; ( i > 0 ) && isspace ( line [ i -1 ] ) ; i-- )
            line [ i -1 ] = '\0';
        /* file sanity check */
        sanity_check_file ( line, filename );
        /* get keyword from line and ignore empty lines */
        if ( get_word_line ( file_number, &line, SAR_OPTION, MESSAGE_ONLY ) != 0 )
            continue;
    }
    /* after reading all lines, close the file pointer */
    fclose ( fp );
}

void read_sar_check ( int file_number, const char *filename, int SAR_OPTION )
{
    int filename_len = ( int ) strlen ( filename );
    if ( filename_len <= 0 )
    {
        printf("no file name supplied (%s): %d %s\n",filename,filename_len,strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    if ( filename_len > MAX_FULL_PATH_LENGTH )
    {
        printf("file name too long (%s): %d %s\n",filename,filename_len,strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    FILE *fp;
    int lnr = 0;
    struct stat;
    char linebuf [ MAX_LINE_LENGTH ];
    char *line;
    int i;

    /* open sar file */
    if ( ( fp=fopen ( filename,"r" ) ) == NULL )
    {
        printf("can't open file (%s): %s\n",filename,strerror(errno));
        /* freeing object and setting it to NULL */
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    else
        append_list ( &line_obj, "" );

    /* read file and check healthness */
    while ( fgets ( linebuf,sizeof ( linebuf ),fp ) != NULL )
    {
        lnr++;
        line = linebuf;
        /* strip newline */
        i = ( int ) strlen ( line );
        if ( ( i <= 0 ) || ( line [ i - 1 ] != '\n' ) )
        {
            printf("%s:%d: line too long or last line missing newline\n Hint:$sed -i 's/\\x00//g' <sar_file>\n",filename,lnr);
            /* freeing object and setting it to NULL */
            free_sar_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }
        line [ i - 1 ] = '\0';
        /* ignore comment lines */
        if ( line [ 0 ] == '#' )
            continue;
        /* strip trailing spaces */
        for ( i--; ( i > 0 ) && isspace ( line [ i -1 ] ) ; i-- )
            line [ i -1 ] = '\0';
        /* file sanity check */
        sanity_check_file ( line, filename );
    }
    /* after reading all lines, close the file pointer */
    fclose ( fp );
    if ( cpu_avg_checked_int == 0 || proc_s_avg_checked_int == 0 || pswpin_s_avg_checked_int == 0 ||
        pgpgin_s_avg_checked_int == 0 || tps_avg_checked_int == 0 || kbmemfree_avg_checked_int == 0 ||
        kbswpfree_avg_checked_int == 0 || kbhugfree_avg_checked_int == 0 || dentunusd_avg_checked_int == 0 ||
        runq_sz_avg_checked_int == 0 || dev_avg_checked_int == 0 || rxpck_s_avg_checked_int == 0 ||
        rxerr_s_avg_checked_int == 0 || call_s_avg_checked_int == 0 || scall_s_avg_checked_int == 0 ||
        totsck_avg_checked_int == 0 || squeezd_avg_checked_int == 0 )
    {
        printf("'Average' line lacks in file (%s)'\n",filename);
        puts("Please check below items in file.");
        puts("Or, your locale is en_US and still try to read ja_JP file?");
        puts("If that is the case, you can tweak libsar-analyzer/Makefile.am to use jp files.");
        puts("Sanity check faild!");
        puts("--------");
        free_sar_analyzer_obj ( );
        printf("cpu_avg_checked (%s)\n",cpu_avg_checked);
        printf("proc_s_avg_checked (%s)\n",proc_s_avg_checked);
        printf("pswpin_s_avg_checked (%s)\n",pswpin_s_avg_checked);
        printf("pgpgin_s_avg_checked (%s)\n",pgpgin_s_avg_checked);
        printf("tps_avg_checked (%s)\n",tps_avg_checked);
        printf("kbmemfree_avg_checked (%s)\n",kbmemfree_avg_checked);
        printf("kbswpfree_avg_checked (%s)\n",kbswpfree_avg_checked);
        printf("kbhugfree_avg_checked (%s)\n",kbhugfree_avg_checked);
        printf("dentunusd_avg_checked (%s)\n",dentunusd_avg_checked);
        printf("runq_sz_avg_checked (%s)\n",runq_sz_avg_checked);
        printf("dev_avg_checked (%s)\n",dev_avg_checked);
        printf("rxpck_s_avg_checked (%s)\n",rxpck_s_avg_checked);
        printf("rxerr_s_avg_checked (%s)\n",rxerr_s_avg_checked);
        printf("call_s_avg_checked (%s)\n",call_s_avg_checked);
        printf("scall_s_avg_checked (%s)\n",scall_s_avg_checked);
        printf("totsck_avg_checked (%s)\n",totsck_avg_checked);
        printf("squeezd_avg_checked (%s)\n",squeezd_avg_checked);
        puts("--------");
        printf("cpu_avg_checked_int (%d)\n",cpu_avg_checked_int);
        printf("proc_s_avg_checked_int (%d)\n",proc_s_avg_checked_int);
        printf("pswpin_s_avg_checked_int (%d)\n",pswpin_s_avg_checked_int);
        printf("pgpgin_s_avg_checked_int (%d)\n",pgpgin_s_avg_checked_int);
        printf("tps_avg_checked_int (%d)\n",tps_avg_checked_int);
        printf("kbmemfree_avg_checked_int (%d)\n",kbmemfree_avg_checked_int);
        printf("kbswpfree_avg_checked_int (%d)\n",kbswpfree_avg_checked_int);
        printf("kbhugfree_avg_checked_int (%d)\n",kbhugfree_avg_checked_int);
        printf("dentunusd_avg_checked_int (%d)\n",dentunusd_avg_checked_int);
        printf("runq_sz_avg_checked_int (%d)\n",runq_sz_avg_checked_int);
        printf("dev_avg_checked_int (%d)\n",dev_avg_checked_int);
        printf("rxpck_s_avg_checked_int (%d)\n",rxpck_s_avg_checked_int);
        printf("rxerr_s_avg_checked_int (%d)\n",rxerr_s_avg_checked_int);
        printf("call_s_avg_checked_int (%d)\n",call_s_avg_checked_int);
        printf("scall_s_avg_checked_int (%d)\n",scall_s_avg_checked_int);
        printf("totsck_avg_checked_int (%d)\n",totsck_avg_checked_int);
        printf("squeezd_avg_checked_int (%d)\n",squeezd_avg_checked_int);
        exit ( EXIT_FAILURE );
    }
}

const char *get_dir_name_analyze ( void )
{
    return sar_analyzer_obj->dir_name_analyze;
}

char *get_hostname ( void )
{
    return sar_analyzer_all_obj->hostname;
}

int get_core_numbers ( void )
{
    return sar_analyzer_obj->cores_n;
}

int get_network_device_numbers ( void )
{
    /* ask get_network_device_names () string 'ignore' and it's number minus 1 should be the max network devices */
    int x = 0;
    for (x = 1; x < MAX_NETWORK_DEVICE_NUMBERS; x++ )
        if ( strcmp ( ( char * ) get_network_device_names ( x ), "ignore" ) == 0 )
            return x;
    return (1);
}

const char *get_network_device_names ( int x )
{
    return sar_analyzer_obj->network_device_names [ x ];
}

int get_block_device_numbers ( void )
{
    /* ask get_block_device_names () string 'ignore' and it's number minus 1 should be the max block devices */
    int x = 0;
    for (x = 1; x < MAX_BLOCK_DEVICE_NUMBERS; x++ )
        if ( strcmp ( ( char * ) get_block_device_names ( x ), "ignore" ) == 0 )
            return x;
    return (1);
}

const char *get_block_device_names ( int x )
{
    return sar_analyzer_obj->device_names [ x ];
}

void set_network_device_names ( const char *network_device_name )
{
    if ( search_network_device_name ( network_device_name ) == 0 )
        strcpy ( sar_analyzer_obj->network_device_names [ get_network_device_numbers ( ) ], network_device_name );
}

int get_files_n ( void )
{
    return sar_analyzer_obj->files_n;
}

int file_to_write ( int SAR_OPTION )
{
    char buff [ MAX_FILE_NAME_LENGTH ]; 
    char buff2 [ MAX_FILE_NAME_LENGTH ]; 
    char f_t [ 40 ];
    memset ( buff, '\0', MAX_FILE_NAME_LENGTH ); 
    memset ( buff2, '\0', MAX_FILE_NAME_LENGTH ); 
    memset ( f_t, '\0', 40 ); 
    strncpy ( buff, "sosreport-analyzer-results", MAX_FILE_NAME_LENGTH );
    strncpy ( buff2, "sosreport-analyzer-results", MAX_FILE_NAME_LENGTH );
    strncat ( buff, "/sar_result_all", 16 );
    strncat ( buff2, "/sar_result_all", 16 );

    struct tm *timenow;
    time_t now = time ( NULL );
    timenow = localtime ( &now );

    strftime ( f_t, sizeof ( f_t ), "_%Y%m%d%H%M%S", timenow );

    strncat ( buff, f_t, MAX_FILE_NAME_LENGTH - 1 );
    strncat ( buff2, f_t, MAX_FILE_NAME_LENGTH - 1 );

    /* here, we ommit .ps for buff2, which will be added later on in main.c */
    if ( SAR_OPTION ==  'u' )
    {
        strncat ( buff, "_CPU_utilization.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_CPU_utilization", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'B' )
    {
        strncat ( buff, "_paging_statistics.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_paging_statistics", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'd' )
    {
        strncat ( buff, "_activity_for_each_block_device.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_activity_for_each_block_device", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'b' )
    {
        strncat ( buff, "_IO_and_transfer_rate_statistics.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_IO_and_transfer_rate_statistics", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'H' )
    {
        strncat ( buff, "_hugepages_utilization_statistics.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_hugepages_utilization_statistics", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'n' )
    {
        strncat ( buff, "_network_statistics.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_network_statistics", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'm' )
    {
        strncat ( buff, "_network_statistics_error.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_network_statistics_error", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'q' )
    {
        strncat ( buff, "_queue_length_and_load_averages.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_queue_length_and_load_averages", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'r' )
    {
        strncat ( buff, "_memory_utilization_statistics.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_memory_utilization_statistics", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'S' )
    {
        strncat ( buff, "_swap_space_utilization_statistics.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_swap_space_utilization_statistics", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'v' )
    {
        strncat ( buff, "_kernel_tables.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_kernel_tables", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'W' )
    {
        strncat ( buff, "_swapping_statistics.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_swapping_statistics", MAX_FILE_NAME_LENGTH - 1 );

    }
    else if ( SAR_OPTION ==  'w' )
    {
        strncat ( buff, "_task_creation_and_system_switching_activity.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_task_creation_and_system_switching_activity", MAX_FILE_NAME_LENGTH - 1 );
    }
    else if ( SAR_OPTION ==  'y' )
    {
        strncat ( buff, "_TTY_devices_activity.txt", MAX_FILE_NAME_LENGTH - 1 );
        strncat ( buff2, "_TTY_devices_activity", MAX_FILE_NAME_LENGTH - 1 );
    }
    else
        strncat ( buff, ".txt", MAX_FILE_NAME_LENGTH - 1 );

    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */
    strcpy ( sar_analyzer_obj->file_name_to_be_written, buff );
    /* We create postscript file name too */
    strcpy ( sar_analyzer_all_obj->file_name_to_be_written, buff2 );

    return ( 0 );
}

void sanity_check_file ( char * line, const char * filename )
{
    if ( strstr ( line, "LINUX RESTART" ) != 0 )
        initialize_avg_checked_int ( );

    if ( ( cpu == 1 ) && ( proc_s == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        cpu_avg_checked_int = 1;
        cpu_avg_checked = "Checked";
    }
    if ( ( proc_s == 1 ) && ( pswpin_s == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        proc_s_avg_checked_int = 1;
        proc_s_avg_checked = "Checked";
    }
    if ( ( pswpin_s == 1 ) && ( pgpgin_s == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        pswpin_s_avg_checked_int = 1;
        pswpin_s_avg_checked = "Checked";
    }
    if ( ( pgpgin_s == 1 ) && ( tps == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        pgpgin_s_avg_checked_int = 1;
        pgpgin_s_avg_checked = "Checked";
    }
    if ( ( tps == 1 ) && ( kbmemfree == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        tps_avg_checked_int = 1;
        tps_avg_checked = "Checked";
    }
    if ( ( kbmemfree == 1 ) && ( kbswpfree == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        kbmemfree_avg_checked_int = 1;
        kbmemfree_avg_checked = "Checked";
    }
    if ( ( kbswpfree == 1 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        if ( ( kbhugfree == 1 ) || ( dentunusd == 0 ) )
        {
            kbswpfree_avg_checked_int = 1;
            kbswpfree_avg_checked = "Checked";
            kbhugfree_avg_checked_int = 1;
            kbhugfree_avg_checked = "Checked";
        }
    }
    if ( ( kbhugfree == 1 ) && ( dentunusd == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        kbhugfree_avg_checked_int = 1;
        kbhugfree_avg_checked = "Checked";
    }
    if ( ( dentunusd == 1 ) && ( runq_sz == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        dentunusd_avg_checked_int = 1;
        dentunusd_avg_checked = "Checked";
    }
    if ( ( runq_sz == 1 ) && ( dev == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        runq_sz_avg_checked_int = 1;
        runq_sz_avg_checked = "Checked";
    }
    if ( ( dev == 1 ) && ( rxpck_s == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        dev_avg_checked_int = 1;
        dev_avg_checked = "Checked";
    }
    if ( ( rxpck_s == 1 ) && ( rxerr_s == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        rxpck_s_avg_checked_int = 1;
        rxpck_s_avg_checked = "Checked";
    }
    if ( ( rxerr_s == 1 ) && ( call_s == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        rxerr_s_avg_checked_int = 1;
        rxerr_s_avg_checked = "Checked";
    }
    if ( ( call_s == 1 ) && ( scall_s == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        call_s_avg_checked_int = 1;
        call_s_avg_checked = "Checked";
    }
    if ( ( scall_s == 1 ) && ( totsck == 0 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        scall_s_avg_checked_int = 1;
        scall_s_avg_checked = "Checked";
    }
    if ( ( totsck == 1 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        if ( squeezd == 0 )
        {
            totsck_avg_checked_int = 1;
            totsck_avg_checked = "Checked";
            squeezd_avg_checked_int = 1;
            squeezd_avg_checked = "Checked";
        }
    }
    if ( ( squeezd == 1 ) && ( strstr ( line, "Average" ) != 0 ) )
    {
        squeezd_avg_checked_int = 1;
        squeezd_avg_checked = "Checked";
    }
    if ( strstr ( line, "iowait" ) != 0 )
        cpu = 1;
    if ( strstr ( line, "proc/s" ) != 0  )
        proc_s = 1;
    if ( strstr ( line, "pswpin/s" ) != 0 )
        pswpin_s = 1;
    if ( strstr ( line, "pgpgin/s" ) != 0 )
        pgpgin_s = 1;
    if ( strstr ( line, "tps" ) != 0 )
        tps = 1;
    if ( strstr ( line, "kbmemfree" ) != 0 )
        kbmemfree = 1;
    if ( strstr ( line, "kbswpfree" ) != 0 )
        kbswpfree = 1;
    if ( strstr ( line, "kbhugfree" ) != 0 )
        kbhugfree = 1;
    if ( strstr ( line, "dentunusd" ) != 0 )
        dentunusd = 1;
    if ( strstr ( line, "runq-sz" ) != 0 )
        runq_sz = 1;
    if ( strstr ( line, "DEV" ) != 0 )
        dev = 1;
    if ( strstr ( line, "rxpck/s" ) != 0 )
        rxpck_s = 1;
    if ( strstr ( line, "rxerr/s" ) != 0 )
        rxerr_s = 1;
    if ( strstr ( line, "retrans" ) != 0 )
        call_s = 1;
    if ( strstr ( line, "scall/s" ) != 0 )
        scall_s = 1;
    if ( strstr ( line, "totsck" ) != 0 )
        totsck = 1;
    if ( strstr ( line, "squeezd" ) != 0 )
        squeezd = 1;
}

int check_result_dir ( const char *dname )
{
    if ( dname != NULL )
    {
        /* if open directory fails, create it, if it fails, exit with error message */
        if ( !opendir ( dname ) ) 
        {
            printf("can't open directory %s\n",dname);
            printf("Creating directory %s\n",dname);
            if ( mkdir ( dname, 0755 ) == 0 )
                printf("Created directory %s\n",dname);
            else
            {
                printf("can't open directory %s\n",dname);
                free_sar_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
        }
    }
    return ( 0 );
}

void tar_pdf_files ( const char *pdf_file_pre )
{
    int err;
    char buff [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff, '\0', MAX_FILE_NAME_LENGTH ); 
    snprintf ( buff, MAX_FILE_NAME_LENGTH, "tar -zcvf %s.tar.gz %s*.pdf", pdf_file_pre, pdf_file_pre );
    err = system ( buff );
    if ( err )
    {
        fprintf(stderr, "command failed: %s (%d)\n", buff, err);
        free_sar_analyzer_obj ( );
        exit(EXIT_FAILURE);
    }
    else 
        printf ("did %s\n", buff);
}

void remove_unneeded_files ( const char *filename, const char *extension )
{
    int err;
    char buff [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff, '\0', MAX_FILE_NAME_LENGTH ); 
    snprintf ( buff, MAX_FILE_NAME_LENGTH, "rm -f %s*.%s", filename, extension );
    err = system ( buff );
    if ( err )
    {
        fprintf(stderr, "command failed: %s (%d)\n", buff, err);
        free_sar_analyzer_obj ( );
        exit(EXIT_FAILURE);
    }
    else 
        printf ("did %s\n", buff);
}

void postscript_to_pdf ( const char *filename )
{
    int err = 0;
    char buff [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff, '\0', MAX_FILE_NAME_LENGTH ); 
    snprintf ( buff, MAX_FILE_NAME_LENGTH, "gs -sDEVICE=pdfwrite -sOutputFile=%s.pdf -dBATCH -dNOPAUSE -sPAPERSIZE=a4 %s.ps", filename, filename );
    err = system ( buff );
    /* we just echo string and continue */
    if ( err )
        fprintf(stderr, "command failed: %s (%d)\n", buff, err);
    else 
        printf ("did %s\n", buff);
}

void sar_analyzer_init ( const char *dname, const char *fname, int SAR_OPTION, int REPORT, int MESSAGE_ONLY )
{
    if ( dname != NULL )
    {
        /* if open directory fails, exit with error message */
        DIR *dir;
        if ( ( dir = opendir ( dname ) ) == NULL ) 
        {
            printf("cannot open directory (%s): %s\n",dname,strerror(errno));
            free_sar_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }
        /* this is needed to suppress memory leak */
        closedir ( dir );
        /* now, creating object */
        create_sar_analyzer_obj ( );
        /* setting directory name */
        set_dir_name_analyze ( dname );

        /* read sa directory */
        read_sa_dir ( dname, SAR_OPTION, REPORT, MESSAGE_ONLY );
    }
    else if ( fname != NULL )
    {
        puts("this function is almost done, but right now, please use directory option...");
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    else
    {
        printf("file or directory name not present\n");
        free_sar_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
}

int create_sar_analyzer_obj ( )
{
    int i = 0;

    /* initialize some of the items here */

    initialize_block_device_name ( );
    initialize_network_device_name ( );

    /* for dates */
    set_this_date ( "1970/1/1" );
    set_this_date_all ( "1970/1/1" );

    /* these values should be small enough for the comparison */

    /* ---- Averages highest ---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for ( i = 0; i <= MAX_CORE_NUMBERS; i++ )
    {
        set_cpu_avg_highest_val ( -0.01, i, "usr" );
        set_cpu_avg_highest_val ( -0.01, i, "sys" );
        set_cpu_avg_highest_val ( -0.01, i, "iowait" );
        set_cpu_avg_highest_val ( -0.01, i, "idle" );
    }

    set_tasks_avg_highest_val ( -0.01, "proc" );
    set_tasks_avg_highest_val ( -0.01, "cswch" );
    set_pswap_avg_highest_val ( -1, "pswpin" );
    set_pswap_avg_highest_val ( -1, "pswpout" );
    set_paging_avg_highest_val ( -0.01, "pgpgin" );
    set_paging_avg_highest_val ( -0.01, "pgpgout" );
    set_paging_avg_highest_val ( -0.01, "fault" );
    set_paging_avg_highest_val ( -0.01, "majflt" );
    set_paging_avg_highest_val ( -0.01, "vmeff" );
    set_io_transfer_rate_avg_highest_val ( -0.01, "tps" );
    set_io_transfer_rate_avg_highest_val ( -0.01, "bread" );
    set_io_transfer_rate_avg_highest_val ( -0.01, "bwrtn" );
    set_memory_double_avg_highest_val ( -0.01, "memused" );
    set_memory_double_avg_highest_val ( -0.01, "commit" );
    set_memory_int_avg_highest_val ( -0.01, "kbcommit" );
    set_swpused_avg_highest_val ( -0.01 );
    set_kernel_table_avg_highest_val ( -1, "dentunusd" );
    set_kernel_table_avg_highest_val ( -1, "file" );
    set_kernel_table_avg_highest_val ( -1, "inode" );
    set_ldavg_int_avg_highest_val ( -1, "runq_sz" );
    set_ldavg_int_avg_highest_val ( -1, "plist_sz" );
    set_ldavg_double_avg_highest_val ( -0.01, "ldavg_one" );
    set_ldavg_double_avg_highest_val ( -0.01, "ldavg_five" );
    set_ldavg_double_avg_highest_val ( -0.01, "ldavg_15" );

    /* up to MAX_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++ )
    {
        set_block_device_avg_highest_val ( -0.01, i, "areqsz" );
        set_block_device_avg_highest_val ( -0.01, i, "util" );
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++ )
    {
        set_network_avg_highest_val ( -0.01, i, "rxpck" );
        set_network_avg_highest_val ( -0.01, i, "txpck" );
        set_network_avg_highest_val( -0.01, i, "rxkb" );
        set_network_avg_highest_val ( -0.01, i, "txkb" );
        set_network_avg_highest_val ( -0.01, i, "rxerr" );
        set_network_avg_highest_val ( -0.01, i, "txerr" );
        set_network_avg_highest_val ( -0.01, i, "rxdrop" );
        set_network_avg_highest_val ( -0.01, i, "txdrop" );
        set_network_former_val ( -0.01, i, "rxpck" );
        set_network_former_val ( -0.01, i, "txpck" );
        set_network_former_val ( -0.01, i, "rxkb" );
        set_network_former_val ( -0.01, i, "txkb" );
        set_network_former_val ( -0.01, i, "rxerr" );
        set_network_former_val ( -0.01, i, "txerr" );
        set_network_former_val ( -0.01, i, "rxdrop" );
        set_network_former_val ( -0.01, i, "txdrop" );
    }

    /*  initialize spike and former each file */

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for ( int x = 0; i < MAX_ANALYZE_FILES ; x++ )
    {
        for ( i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++ )
        {
            set_network_spike_val_each_file ( x, -0.01, i, "rxpck", "highest" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "rxpck", "highest" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "rxpck", "highest" );
            set_network_spike_val_each_file ( x, -0.01, i, "txpck", "highest" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "txpck", "highest" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "txpck", "highest" );
            set_network_spike_val_each_file ( x, -0.01, i, "rxkb", "highest" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "rxkb", "highest" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "rxkb", "highest" );
            set_network_spike_val_each_file ( x, -0.01, i, "txkb", "highest" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "txkb", "highest" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "txkb", "highest" );
            set_network_spike_val_each_file ( x, -0.01, i, "rxerr", "highest" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "rxerr", "highest" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "rxerr", "highest" );
            set_network_spike_val_each_file ( x, -0.01, i, "txerr", "highest" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "txerr", "highest" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "txerr", "highest" );
            set_network_spike_val_each_file ( x, -0.01, i, "rxdrop", "highest" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "rxdrop", "highest" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "rxdrop", "highest" );
            set_network_spike_val_each_file ( x, -0.01, i, "txdrop", "highest" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "txdrop", "highest" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "txdrop", "highest" );
            set_network_spike_val_each_file ( x, -0.01, i, "rxpck", "spike" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "rxpck", "spike" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "rxpck", "spike" );
            set_network_spike_val_each_file ( x, -0.01, i, "txpck", "spike" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "txpck", "spike" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "txpck", "spike" );
            set_network_spike_val_each_file ( x, -0.01, i, "rxkb", "spike" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "rxkb", "spike" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "rxkb", "spike" );
            set_network_spike_val_each_file ( x, -0.01, i, "txkb", "spike" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "txkb", "spike" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "txkb", "spike" );
            set_network_spike_val_each_file ( x, -0.01, i, "rxerr", "spike" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "rxerr", "spike" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "rxerr", "spike" );
            set_network_spike_val_each_file ( x, -0.01, i, "txerr", "spike" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "txerr", "spike" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "txerr", "spike" );
            set_network_spike_val_each_file ( x, -0.01, i, "rxdrop", "spike" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "rxdrop", "spike" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "rxdrop", "spike" );
            set_network_spike_val_each_file ( x, -0.01, i, "txdrop", "spike" );
            set_network_spike_date_each_file ( x, "1970/1/1", i, "txdrop", "spike" );
            set_network_spike_time_each_file ( x, "1970/1/1", i, "txdrop", "spike" );
            set_network_former_val_each_file ( x, -0.01, i, "rxerr" );
            set_network_former_val_each_file ( x, -0.01, i, "txerr" );
            set_network_former_val_each_file ( x, -0.01, i, "rxdrop" );
            set_network_former_val_each_file ( x, -0.01, i, "txdrop" );
        }
    }

    /* ---- spike and former---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for ( i = 0; i <= MAX_CORE_NUMBERS; i++ )
    {
        set_cpu_spike_val ( -0.01, i, "usr" );
        set_cpu_former_val ( -0.01, i, "usr" );
        set_cpu_spike_val ( -0.01, i, "sys" );
        set_cpu_former_val ( -0.01, i, "sys" );
        set_cpu_spike_val ( -0.01, i, "iowait" );
        set_cpu_former_val ( -0.01, i, "iowait" );
        set_cpu_spike_val ( -0.01, i, "idle" );
        set_cpu_former_val ( -0.01, i, "idle" );
    }

    set_tasks_spike_val ( -0.01, "proc" );
    set_tasks_former_val ( -0.01, "proc" );
    set_tasks_spike_val ( -0.01, "cswch" );
    set_tasks_former_val ( -0.01, "cswch" );
    set_pswap_spike_val ( 0.00, "pswpin" );
    set_pswap_former_val ( 0.00, "pswpin" );
    set_pswap_spike_val ( 0.00, "pswpout" );
    set_pswap_former_val ( 0.00, "pswpout" );
    set_paging_spike_val ( 0.00, "pgpgin" );
    set_paging_former_val ( 0.00, "pgpgin" );
    set_paging_spike_val ( 0.00, "pgpgout" );
    set_paging_former_val ( 0.00, "pgpgout" );
    set_paging_spike_val ( -0.01, "fault" );
    set_paging_former_val ( -0.01, "fault" );
    set_paging_spike_val ( -0.01, "majflt" );
    set_paging_former_val ( -0.01, "majflt" );
    set_paging_spike_val ( -0.01, "vmeff" );
    set_paging_former_val ( -0.01, "vmeff" );
    set_io_transfer_rate_spike_val ( -0.01, "tps" );
    set_io_transfer_rate_former_val ( -0.01, "tps" );
    set_io_transfer_rate_spike_val ( -0.01, "bread" );
    set_io_transfer_rate_former_val ( -0.01, "bread" );
    set_io_transfer_rate_spike_val ( -0.01, "bwrtn" );
    set_io_transfer_rate_former_val ( -0.01, "bwrtn" );
    set_memory_double_spike_val ( -0.01, "memused" );
    set_memory_double_former_val ( -0.01, "memused" );
    set_memory_double_spike_val ( -0.01, "commit" );
    set_memory_double_former_val ( -0.01, "commit" );
    set_memory_int_spike_val ( -1, "kbcommit" );
    set_memory_int_former_val ( -1, "kbcommit" );
    set_swpused_spike_val ( -0.01 );
    set_swpused_former_val ( -0.01 );
    set_kernel_table_spike_val ( -1, "dentunusd" );
    set_kernel_table_former_val ( -1, "dentunusd" );
    set_kernel_table_spike_val ( -1, "file" );
    set_kernel_table_former_val ( -1, "file" );
    set_kernel_table_spike_val ( -1, "inode" );
    set_kernel_table_former_val ( -1, "inode" );

    set_ldavg_int_spike_val ( -1, "runq_sz" );
    set_ldavg_int_former_val ( -1, "runq_sz" );
    set_ldavg_int_spike_val ( -1, "plist_sz" );
    set_ldavg_int_former_val ( -1, "plist_sz" );
    set_ldavg_double_spike_val ( -0.01, "ldavg_one" );
    set_ldavg_double_former_val ( -0.01, "ldavg_one" );
    set_ldavg_double_spike_val ( -0.01, "ldavg_five" );
    set_ldavg_double_former_val ( -0.01, "ldavg_five" );
    set_ldavg_double_spike_val ( -0.01, "ldavg_15" );
    set_ldavg_double_former_val ( -0.01, "ldavg_15" );

    /* up to MAX_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++ )
    {
        set_block_device_spike_val ( -0.01, i, "areqsz" );
        set_block_device_former_val ( -0.01, i, "areqsz" );
        set_block_device_spike_val ( -0.01, i, "util" );
        set_block_device_former_val ( -0.01, i, "util" );
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++ )
    {
        set_network_spike_val ( -0.01, i, "rxpck" );
        set_network_former_val ( -0.01, i, "rxpck" );
        set_network_spike_val ( -0.01, i, "txpck" );
        set_network_former_val ( -0.01, i, "txpck" );
        set_network_spike_val( -0.01, i, "rxkb" );
        set_network_former_val( -0.01, i, "rxkb" );
        set_network_spike_val ( -0.01, i, "txkb" );
        set_network_former_val ( -0.01, i, "txkb" );
        set_network_spike_val ( -0.01, i, "rxerr" );
        set_network_former_val ( -0.01, i, "rxerr" );
        set_network_spike_val ( -0.01, i, "txerr" );
        set_network_former_val ( -0.01, i, "txerr" );
        set_network_spike_val ( -0.01, i, "rxdrop" );
        set_network_former_val ( -0.01, i, "rxdrop" );
        set_network_spike_val ( -0.01, i, "txdrop" );
        set_network_former_val ( -0.01, i, "txdrop" );
    }

    /* ---- All highest ---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for ( i = 0; i <= MAX_CORE_NUMBERS; i++ )
    {
        set_cpu_highest_val ( -0.01, i, "usr" );
        set_cpu_highest_val ( -0.01, i, "sys" );
        set_cpu_highest_val ( -0.01, i, "iowait" );
        set_cpu_highest_val ( -0.01, i, "idle" );
    }

    set_tasks_highest_val ( -0.01, "proc" );
    set_tasks_highest_val ( -0.01, "cswch" );
    set_pswap_highest_val ( -1, "pswpin" );
    set_pswap_highest_val ( -1, "pswpout" );
    set_paging_highest_val ( -0.01, "pgpgin" );
    set_paging_highest_val ( -0.01, "pgpgout" );
    set_paging_highest_val ( -0.01, "fault" );
    set_paging_highest_val ( -0.01, "majflt" );
    set_paging_highest_val ( -0.01, "vmeff" );
    set_io_transfer_rate_highest_val ( -0.01, "tps" );
    set_io_transfer_rate_highest_val ( -0.01, "bread" );
    set_io_transfer_rate_highest_val ( -0.01, "bwrtn" );
    set_memory_double_highest_val ( -0.01, "memused" );
    set_memory_double_highest_val ( -0.01, "commit" );
    set_memory_int_highest_val ( -1, "kbcommit" );
    set_swpused_highest_val ( -0.01 );
    set_kernel_table_highest_val ( -1, "dentunusd" );
    set_kernel_table_highest_val ( -1, "file" );
    set_kernel_table_highest_val ( -1, "inode" );

    set_ldavg_int_highest_val ( -1, "runq_sz" );
    set_ldavg_int_highest_val ( -1, "plist_sz" );
    set_ldavg_double_highest_val ( -0.01, "ldavg_one" );
    set_ldavg_double_highest_val ( -0.01, "ldavg_five" );
    set_ldavg_double_highest_val ( -0.01, "ldavg_15" );

    /* up to MAX_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++ )
    {
        set_block_device_highest_val ( -0.01, i, "areqsz" );
        set_block_device_highest_val ( -0.01, i, "util" );
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++ )
    {
        set_network_highest_val ( -0.01, i, "rxpck" );
        set_network_highest_val ( -0.01, i, "txpck" );
        set_network_highest_val( -0.01, i, "rxkb" );
        set_network_highest_val ( -0.01, i, "txkb" );
        set_network_highest_val ( -0.01, i, "rxerr" );
        set_network_highest_val ( -0.01, i, "txerr" );
        set_network_highest_val ( -0.01, i, "rxdrop" );
        set_network_highest_val ( -0.01, i, "txdrop" );
    }

    /* these values should be big enough for the comparison */

    /* ---- Averages lowest ---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for ( i = 0; i <= MAX_CORE_NUMBERS; i++ )
    {
        set_cpu_avg_lowest_val ( 100.01, i, "usr" );
        set_cpu_avg_lowest_val ( 100.01, i, "sys" );
        set_cpu_avg_lowest_val ( 100.01, i, "iowait" );
        set_cpu_avg_lowest_val ( 100.01, i, "idle" );
    }

    set_tasks_avg_lowest_val ( 9999999999.99, "proc" );
    set_tasks_avg_lowest_val ( 9999999999.99, "cswch" );
    set_pswap_avg_lowest_val ( 999999999, "pswpin" );
    set_pswap_avg_lowest_val ( 999999999, "pswpout" );
    set_paging_avg_lowest_val ( 9999999999.99, "pgpgin" );
    set_paging_avg_lowest_val ( 9999999999.99, "pgpgout" );
    set_paging_avg_lowest_val ( 9999999999.99, "fault" );
    set_paging_avg_lowest_val ( 9999999999.99, "majflt" );
    set_paging_avg_lowest_val ( 100.01, "vmeff" );
    set_io_transfer_rate_avg_lowest_val ( 9999999999.99, "tps" );
    set_io_transfer_rate_avg_lowest_val ( 9999999999.99, "bread" );
    set_io_transfer_rate_avg_lowest_val ( 9999999999.99, "bwrtn" );
    set_memory_double_avg_lowest_val ( 100.01, "memused" );
    set_memory_double_avg_lowest_val ( 10000.01, "commit" );
    set_memory_int_avg_lowest_val ( 999999999, "kbcommit" );
    set_swpused_avg_lowest_val ( 100.01 );
    set_kernel_table_avg_lowest_val ( 999999999, "dentunusd" );
    set_kernel_table_avg_lowest_val ( 999999999, "file" );
    set_kernel_table_avg_lowest_val ( 999999999, "inode" );
    set_ldavg_int_avg_lowest_val ( 999999999, "runq_sz" );
    set_ldavg_int_avg_lowest_val ( 999999999, "plist_sz" );
    set_ldavg_double_avg_lowest_val ( 9999999999.99, "ldavg_one" );
    set_ldavg_double_avg_lowest_val ( 9999999999.99, "ldavg_five" );
    set_ldavg_double_avg_lowest_val ( 9999999999.99, "ldavg_15" );

    /* up to MAX_BLOCK_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++ )
    {
        set_block_device_avg_lowest_val ( 9999999999.99, i, "areqsz" );
        set_block_device_avg_lowest_val ( 9999999999.99, i, "util" );
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++ )
    {
        set_network_avg_lowest_val ( 999999999.99, i, "rxpck" );
        set_network_avg_lowest_val ( 999999999.99, i, "txpck" );
        set_network_avg_lowest_val ( 999999999.99, i, "rxkb" );
        set_network_avg_lowest_val ( 999999999.99, i, "txkb" );
        set_network_avg_lowest_val ( 999999999.99, i, "rxerr" );
        set_network_avg_lowest_val ( 999999999.99, i, "txerr" );
        set_network_avg_lowest_val ( 999999999.99, i, "rxdrop" );
        set_network_avg_lowest_val ( 999999999.99, i, "txdrop" );
    }

    /* ---- All lowest ---- */

    /* CPU all, 0 to MAX_CORE_NUMBERS */
    for ( i = 0; i <= MAX_CORE_NUMBERS; i++ )
    {
        set_cpu_lowest_val ( 100.01, i, "usr" );
        set_cpu_lowest_val ( 100.01, i, "sys" );
        set_cpu_lowest_val ( 100.01, i, "iowait" );
        set_cpu_lowest_val ( 100.01, i, "idle" );
    }

    set_tasks_lowest_val ( 9999999999.99, "proc" );
    set_tasks_lowest_val ( 9999999999.99, "cswch" );
    set_pswap_lowest_val ( 999999999, "pswpin" );
    set_pswap_lowest_val ( 999999999, "pswpout" );
    set_paging_lowest_val ( 9999999999.99, "pgpgin" );
    set_paging_lowest_val ( 9999999999.99, "pgpgout" );
    set_paging_lowest_val ( 9999999999.99, "fault" );
    set_paging_lowest_val ( 9999999999.99, "majflt" );
    set_paging_lowest_val ( 100.01, "vmeff" );
    set_io_transfer_rate_lowest_val ( 9999999999.99, "tps" );
    set_io_transfer_rate_lowest_val ( 9999999999.99, "bread" );
    set_io_transfer_rate_lowest_val ( 9999999999.99, "bwrtn" );
    set_memory_double_lowest_val ( 100.01, "memused" );
    set_memory_double_lowest_val ( 10000.01, "commit" );
    set_memory_int_lowest_val ( 999999999, "kbcommit" );
    set_swpused_lowest_val ( 100.01 );
    set_kernel_table_lowest_val ( 999999999, "dentunusd" );
    set_kernel_table_lowest_val ( 999999999, "file" );
    set_kernel_table_lowest_val ( 999999999, "inode" );
    set_ldavg_int_lowest_val ( 999999999, "runq_sz" );
    set_ldavg_int_lowest_val ( 999999999, "plist_sz" );
    set_ldavg_double_lowest_val ( 9999999999.99, "ldavg_one" );
    set_ldavg_double_lowest_val ( 9999999999.99, "ldavg_five" );
    set_ldavg_double_lowest_val ( 9999999999.99, "ldavg_15" );

    /* up to MAX_BLOCK_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_BLOCK_DEVICE_NUMBERS; i++ )
    {
        set_block_device_lowest_val ( 9999999999.99, i, "areqsz" );
        set_block_device_lowest_val ( 9999999999.99, i, "util" );
    }

    /* up to MAX_NETWORK_DEVICE_NUMBERS */
    for ( i = 0; i < MAX_NETWORK_DEVICE_NUMBERS; i++ )
    {
        set_network_lowest_val ( 999999999.99, i, "rxpck" );
        set_network_lowest_val ( 999999999.99, i, "txpck" );
        set_network_lowest_val ( 999999999.99, i, "rxkb" );
        set_network_lowest_val ( 999999999.99, i, "txkb" );
        set_network_lowest_val ( 999999999.99, i, "rxerr" );
        set_network_lowest_val ( 999999999.99, i, "txerr" );
        set_network_lowest_val ( 999999999.99, i, "rxdrop" );
        set_network_lowest_val ( 999999999.99, i, "txdrop" );
    }

    set_cpu_as_paragraph ( 0 );
    set_tmp_val ( 0 );
    set_tmp2_val ( 0 );
    set_tmp3_val ( 0 );

    /* initialize the line list object (node) */
    init_list ( &line_obj );
    init_list ( &line_all_obj );
    init_list ( &header_obj );
    init_list ( &report_obj );
    init_list ( &report_cpu_obj );
    for ( int v = 0; v < MAX_CORE_NUMBERS; v++ )
        init_list ( &report_cpu_spike_obj [ v ] );
    init_list ( &report_cpu_explanation_obj );
    init_list ( &report_tasks_obj );
    init_list ( &report_tasks_spike_obj );
    init_list ( &report_tasks_explanation_obj );
    init_list ( &report_pswap_obj );
    init_list ( &report_pswap_spike_obj );
    init_list ( &report_pswap_explanation_obj );
    init_list ( &report_paging_obj );
    init_list ( &report_paging_spike_obj );
    init_list ( &report_paging_explanation_obj );
    init_list ( &report_io_transfer_rate_obj );
    init_list ( &report_io_transfer_rate_spike_obj );
    init_list ( &report_io_transfer_rate_explanation_obj );
    init_list ( &report_memory_obj );
    init_list ( &report_memory_spike_obj );
    init_list ( &report_memory_explanation_obj );
    init_list ( &report_swpused_obj );
    init_list ( &report_swpused_spike_obj );
    init_list ( &report_swpused_explanation_obj );
    init_list ( &report_kernel_table_obj );
    init_list ( &report_kernel_table_spike_obj );
    init_list ( &report_kernel_table_explanation_obj );
    init_list ( &report_ldavg_obj );
    init_list ( &report_ldavg_spike_obj );
    init_list ( &report_ldavg_explanation_obj );
    init_list ( &report_block_device_obj );
    for ( int v = 0; v < MAX_BLOCK_DEVICE_NUMBERS; v++ )
        init_list ( &report_block_device_spike_obj [ v ] );
    init_list ( &report_block_device_explanation_obj );
    init_list ( &report_network_obj );
    for ( int v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++ )
        init_list ( &report_network_spike_obj [ v ] );
    init_list ( &report_network_explanation_obj );
    init_list ( &report_network_error_obj );
    for ( int v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++ )
        init_list ( &report_network_error_spike_obj [ v ] );
    init_list ( &report_network_error_explanation_obj );
    init_list ( &report_thrashing_obj );
    for ( int v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++ )
        init_list ( &report_network_down_obj [ v ] );
    for ( int v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for each file */
        init_list ( &ps_common_cpu_obj [ v ] );
        init_list ( &ps_common_memory_obj [ v ] );
        init_list ( &ps_common_ldavg_obj [ v ] );
        init_list ( &ps_common_io_transfer_rate_obj [ v ] );
        /* for file cpu */
        init_list ( &ps_cpu_label_obj [ v ]);
        init_list ( &ps_cpu_usr_obj [ v ]);
        init_list ( &ps_cpu_sys_obj [ v ] );
        init_list ( &ps_cpu_iowait_obj [ v ] );
        init_list ( &ps_cpu_idle_obj [ v ] );
        init_list ( &ps_paging_label_obj [ v ]);
        init_list ( &ps_paging_pgpgin_obj [ v ] );
        init_list ( &ps_paging_pgpgout_obj [ v ] );
        init_list ( &ps_paging_fault_obj [ v ] );
        init_list ( &ps_paging_mjflt_obj [ v ] );
        init_list ( &ps_paging_vmeff_obj [ v ] );
        /* for file mem */
        init_list ( &ps_memory_label_obj [ v ] );
        init_list ( &ps_memory_memused_obj [ v ] );
        init_list ( &ps_memory_kbcommit_obj [ v ] );
        init_list ( &ps_memory_commit_obj [ v ] );
        init_list ( &ps_swapping_label_obj [ v ] );
        init_list ( &ps_swapping_pswpin_obj [ v ] );
        init_list ( &ps_swapping_pswpout_obj [ v ] );
        /* for file ldv */
        init_list ( &ps_ldavg_label_obj [ v ] );
        init_list ( &ps_ldavg_runq_obj [ v ] );
        init_list ( &ps_ldavg_plist_obj [ v ] );
        init_list ( &ps_ldavg_ldavg_one_obj [ v ] );
        init_list ( &ps_ldavg_ldavg_five_obj [ v ] );
        init_list ( &ps_ldavg_ldavg_15_obj [ v ] );
        init_list ( &ps_tasks_label_obj [ v ] );
        init_list ( &ps_tasks_proc_obj [ v ] );
        init_list ( &ps_tasks_cswch_obj [ v ] );
        /* for file ior */
        init_list ( &ps_io_transfer_rate_label_obj [ v ] );
        init_list ( &ps_io_transfer_rate_tps_obj [ v ] );
        init_list ( &ps_io_transfer_rate_bread_obj [ v ] );
        init_list ( &ps_io_transfer_rate_bwrtn_obj [ v ] );
        init_list ( &ps_kernel_table_label_obj [ v ] );
        init_list ( &ps_kernel_table_dentunusd_obj [ v ] );
        init_list ( &ps_kernel_table_file_obj [ v ] );
        init_list ( &ps_kernel_table_inode_obj [ v ] );
        /* for linux restart string */
        init_list ( &ps_restart_obj [ v ] );
    }
    return ( 0 );
}

int free_sar_analyzer_obj ( )
{
    /* clear list */
    clear_list ( &line_obj );
    clear_list ( &line_all_obj );
    clear_list ( &header_obj );
    clear_list ( &report_obj );
    clear_list ( &report_cpu_obj );
    for ( int v = 0; v < MAX_CORE_NUMBERS; v++ )
        clear_list ( &report_cpu_spike_obj [ v ] );
    clear_list ( &report_cpu_explanation_obj );
    clear_list ( &report_tasks_obj );
    clear_list ( &report_tasks_spike_obj );
    clear_list ( &report_tasks_explanation_obj );
    clear_list ( &report_pswap_obj );
    clear_list ( &report_pswap_spike_obj );
    clear_list ( &report_pswap_explanation_obj );
    clear_list ( &report_paging_obj );
    clear_list ( &report_paging_spike_obj );
    clear_list ( &report_paging_explanation_obj );
    clear_list ( &report_io_transfer_rate_obj );
    clear_list ( &report_io_transfer_rate_spike_obj );
    clear_list ( &report_io_transfer_rate_explanation_obj );
    clear_list ( &report_memory_obj );
    clear_list ( &report_memory_spike_obj );
    clear_list ( &report_memory_explanation_obj );
    clear_list ( &report_swpused_obj );
    clear_list ( &report_swpused_spike_obj );
    clear_list ( &report_swpused_explanation_obj );
    clear_list ( &report_kernel_table_obj );
    clear_list ( &report_kernel_table_spike_obj );
    clear_list ( &report_kernel_table_explanation_obj );
    clear_list ( &report_ldavg_obj );
    clear_list ( &report_ldavg_spike_obj );
    clear_list ( &report_ldavg_explanation_obj );
    clear_list ( &report_block_device_obj );
    for ( int v = 0; v < MAX_BLOCK_DEVICE_NUMBERS; v++ )
        clear_list ( &report_block_device_spike_obj [ v ] );
    clear_list ( &report_block_device_explanation_obj );
    clear_list ( &report_network_obj );
    for ( int v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++ )
        clear_list ( &report_network_spike_obj [ v ] );
    clear_list ( &report_network_explanation_obj );
    clear_list ( &report_network_error_obj );
    for ( int v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++ )
        clear_list ( &report_network_error_spike_obj [ v ] );
    clear_list ( &report_network_error_explanation_obj );
    clear_list ( &report_thrashing_obj );
    for ( int v = 0; v < MAX_NETWORK_DEVICE_NUMBERS; v++ )
        clear_list ( &report_network_down_obj [ v ] );
    for ( int v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for each file */
        clear_list ( &ps_common_cpu_obj [ v ] );
        clear_list ( &ps_common_memory_obj [ v ] );
        clear_list ( &ps_common_ldavg_obj [ v ] );
        clear_list ( &ps_common_io_transfer_rate_obj [ v ] );
        /* for file cpu */
        clear_list ( &ps_cpu_label_obj [ v ] );
        clear_list ( &ps_cpu_usr_obj [ v ] );
        clear_list ( &ps_cpu_sys_obj [ v ] );
        clear_list ( &ps_cpu_iowait_obj [ v ] );
        clear_list ( &ps_cpu_idle_obj [ v ] );
        clear_list ( &ps_paging_label_obj [ v ] );
        clear_list ( &ps_paging_pgpgin_obj [ v ] );
        clear_list ( &ps_paging_pgpgout_obj [ v ] );
        clear_list ( &ps_paging_fault_obj [ v ] );
        clear_list ( &ps_paging_mjflt_obj [ v ] );
        clear_list ( &ps_paging_vmeff_obj [ v ] );
        /* for file mem */
        clear_list ( &ps_memory_label_obj [ v ] );
        clear_list ( &ps_memory_memused_obj [ v ] );
        clear_list ( &ps_memory_kbcommit_obj [ v ] );
        clear_list ( &ps_memory_commit_obj [ v ] );
        clear_list ( &ps_swapping_label_obj [ v ] );
        clear_list ( &ps_swapping_pswpin_obj [ v ] );
        clear_list ( &ps_swapping_pswpout_obj [ v ] );
        /* for file ldv */
        clear_list ( &ps_ldavg_label_obj [ v ] );
        clear_list ( &ps_ldavg_runq_obj [ v ] );
        clear_list ( &ps_ldavg_plist_obj [ v ] );
        clear_list ( &ps_ldavg_ldavg_one_obj [ v ] );
        clear_list ( &ps_ldavg_ldavg_five_obj [ v ] );
        clear_list ( &ps_ldavg_ldavg_15_obj [ v ] );
        clear_list ( &ps_tasks_label_obj [ v ] );
        clear_list ( &ps_tasks_proc_obj [ v ] );
        clear_list ( &ps_tasks_cswch_obj [ v ] );
        /* for file ior */
        clear_list ( &ps_io_transfer_rate_label_obj [ v ] );
        clear_list ( &ps_io_transfer_rate_tps_obj [ v ] );
        clear_list ( &ps_io_transfer_rate_bread_obj [ v ] );
        clear_list ( &ps_io_transfer_rate_bwrtn_obj [ v ] );
        clear_list ( &ps_kernel_table_label_obj [ v ] );
        clear_list ( &ps_kernel_table_dentunusd_obj [ v ] );
        clear_list ( &ps_kernel_table_file_obj [ v ] );
        clear_list ( &ps_kernel_table_inode_obj [ v ] );
        /* for linux restart string */
        clear_list ( &ps_restart_obj [ v ] );
    }
    return ( 0 );
}
