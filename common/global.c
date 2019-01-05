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
#include "global.h"

char str_orig [ MAX_LINE_LENGTH ];  
char str [ MAX_LINE_LENGTH ];  
char str2 [ MAX_LINE_LENGTH ];  
char str3 [ MAX_LINE_LENGTH ];  

/* file_data_obj */
struct file_data file_data_obj_raw =
    {
        "",
    };

/* initialise */
struct file_data *file_data_obj = &file_data_obj_raw;

char *reverse_the_string ( char *str_tmp, int str_len )
{
    int i = 0, j = 0;
    char tmp;
    memset ( str, '\0', sizeof ( str ) ); 
    j = strlen ( str_tmp ) - 1;
    strncpy ( str, str_tmp, str_len );
    while ( i < j )
    {
        tmp = str [ i ];
        str [ i ] = str [ j ];
        str [ j ] = tmp;
        i++;
        j--;
    }
    return str;
}

char *cut_str_by_the_last_slash ( char *str_tmp, int str_len )
{
    int i = 0;
    memset ( str3, '\0', sizeof ( str3 ) ); 
    strncpy ( str3, str_tmp, str_len );
    for ( i = 0; i < str_len; i ++ )
        str3 [ i ] = str_orig [ i ];
    str3 [ i + 1 ] = '\0';

    return str3;
}

char *cut_str_from_the_last_slash ( char *str_tmp, int str_len, char str_ret [ MAX_FILE_NAME_LENGTH ] )
{
    int i = 0, l = 0;
    memset ( str2, '\0', sizeof ( str2 ) ); 
    strncpy ( str2, str_tmp, str_len );
    memset ( str_ret, '\0', MAX_FILE_NAME_LENGTH ); 
    for ( i = 0; i < str_len; i ++ )
    {
        /* 47 means '/' */
        if ( str2 [ i ] == 47 )
        {
            l = i;
            break;
        }
    }
    memset ( str2, '\0', sizeof ( str2 ) ); 
    for ( i = 0; i < l; i ++ )
        str2 [ i ] = str_tmp [ i ];
    strcpy ( str_ret, reverse_the_string ( str2, strlen ( str2 ) ) );

    return str_ret;
}

const char *get_dirname ( void )
{
    return file_data_obj->dirname;
}

