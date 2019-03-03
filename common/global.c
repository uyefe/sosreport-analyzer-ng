/*
 *  global.c - common functions 
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
#include "../libsar-analyzer/common.h" 

char str_orig [ MAX_LINE_LENGTH ];  
char str [ MAX_LINE_LENGTH ];  
char str2 [ MAX_LINE_LENGTH ];  
char str3 [ MAX_LINE_LENGTH ];  


char *reverse_the_string ( char *str_tmp, int str_len )
{
    int i = 0, j = 0, strlen_str_tmp = 0;
    char tmp;
    memset ( str, '\0', sizeof ( str ) ); 
    strlen_str_tmp = ( int ) strlen ( str_tmp );
    j = strlen_str_tmp - 1;
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
    int i = 0, l = 0, strlen_str2 = 0;
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
    strlen_str2 = ( int ) strlen ( str2 );
    strcpy ( str_ret, reverse_the_string ( str2, strlen_str2 ) );

    return str_ret;
}

int set_network_spike_val_each_file ( int x,  double var, int y, const char *element, const char *analyze_item )
{
    if ( strcmp ( "spike", analyze_item ) == 0 )
    {
        if ( strcmp ( "rxpck", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxpck_spike_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txpck", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txpck_spike_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxkb", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxkb_spike_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txkb", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txkb_spike_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxerr", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxerr_spike_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txerr", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txerr_spike_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxdrop", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_spike_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txdrop", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txdrop_spike_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
    else if ( strcmp ( "highest", analyze_item ) == 0 )
    {
        if ( strcmp ( "rxpck", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxpck_highest_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txpck", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txpck_highest_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxkb", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxkb_highest_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txkb", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txkb_highest_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxerr", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxerr_highest_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txerr", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txerr_highest_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxdrop", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_highest_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txdrop", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txdrop_highest_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
    else if ( strcmp ( "down", analyze_item ) == 0 )
    {
        if ( strcmp ( "rxpck", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxpck_down_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txpck", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txpck_down_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxkb", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxkb_down_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txkb", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txkb_down_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxerr", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxerr_down_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txerr", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txerr_down_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxdrop", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_down_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txdrop", element ) == 0 )
        {
            sar_analyzer_spike_obj->networks_spike_each_file.txdrop_down_val_each_file [ x ] [ y ] = var;
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
    else
        return EXIT_FAILURE;
}

int set_network_spike_date_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item )
{
    if ( strcmp ( "spike", analyze_item ) == 0 )
    {
        if ( strcmp ( "rxpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_spike_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_spike_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_spike_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_spike_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_spike_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_spike_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_spike_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_spike_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
    else if ( strcmp ( "highest", analyze_item ) == 0 )
    {
        if ( strcmp ( "rxpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_highest_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_highest_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_highest_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_highest_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_highest_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_highest_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_highest_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_highest_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
    else if ( strcmp ( "down", analyze_item ) == 0 )
    {
        if ( strcmp ( "rxpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_down_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_down_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_down_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_down_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_down_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_down_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_down_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_down_date_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
    else
        return EXIT_FAILURE;
}

int set_network_spike_time_each_file ( int x, const char *date_string, int y, const char *element, const char *analyze_item )
{
    if ( strcmp ( "spike", analyze_item ) == 0 )
    {
        if ( strcmp ( "rxpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_spike_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_spike_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_spike_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_spike_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_spike_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_spike_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_spike_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_spike_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
    else if ( strcmp ( "highest", analyze_item ) == 0 )
    {
        if ( strcmp ( "rxpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_highest_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_highest_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_highest_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_highest_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_highest_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_highest_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_highest_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_highest_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
    else if ( strcmp ( "down", analyze_item ) == 0 )
    {
        if ( strcmp ( "rxpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxpck_down_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txpck", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txpck_down_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxkb_down_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txkb", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txkb_down_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxerr_down_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txerr", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txerr_down_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "rxdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.rxdrop_down_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else if ( strcmp ( "txdrop", element ) == 0 )
        {
            strncpy ( sar_analyzer_spike_obj->date_networks_spike_each_file.txdrop_down_time_each_file [ x ] [ y ], date_string, MAX_DATE_STRINGS );
            return EXIT_SUCCESS;
        }
        else
            return EXIT_FAILURE;
    }
    else
        return EXIT_FAILURE;
}

int set_network_former_val_each_file ( int x,  double var, int y, const char *element )
{
    if ( strcmp ( "rxpck", element ) == 0 )
    {
        sar_analyzer_spike_obj->networks_spike_each_file.rxpck_former_val_each_file [ x ] [ y ] = var;
        return EXIT_SUCCESS;
    }
    else if ( strcmp ( "txpck", element ) == 0 )
    {
        sar_analyzer_spike_obj->networks_spike_each_file.txpck_former_val_each_file [ x ] [ y ] = var;
        return EXIT_SUCCESS;
    }
    else if ( strcmp ( "rxkb", element ) == 0 )
    {
        sar_analyzer_spike_obj->networks_spike_each_file.rxkb_former_val_each_file [ x ] [ y ] = var;
        return EXIT_SUCCESS;
    }
    else if ( strcmp ( "txkb", element ) == 0 )
    {
        sar_analyzer_spike_obj->networks_spike_each_file.txkb_former_val_each_file [ x ] [ y ] = var;
        return EXIT_SUCCESS;
    }
    else if ( strcmp ( "rxerr", element ) == 0 )
    {
        sar_analyzer_spike_obj->networks_spike_each_file.rxerr_former_val_each_file [ x ] [ y ] = var;
        return EXIT_SUCCESS;
    }
    else if ( strcmp ( "txerr", element ) == 0 )
    {
        sar_analyzer_spike_obj->networks_spike_each_file.txerr_former_val_each_file [ x ] [ y ] = var;
        return EXIT_SUCCESS;
    }
    else if ( strcmp ( "rxdrop", element ) == 0 )
    {
        sar_analyzer_spike_obj->networks_spike_each_file.rxdrop_former_val_each_file [ x ] [ y ] = var;
        return EXIT_SUCCESS;
    }
    else if ( strcmp ( "txdrop", element ) == 0 )
    {
        sar_analyzer_spike_obj->networks_spike_each_file.txdrop_former_val_each_file [ x ] [ y ] = var;
        return EXIT_SUCCESS;
    }
    else
        return EXIT_FAILURE;
}
