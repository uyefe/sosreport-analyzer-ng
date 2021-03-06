/*
 * line_data.c - object functions 
 * This file contains the contents of sosreport-analyzer.
 *
 * Copyright (C) 2018-2019 Shintaro Fujiwara
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#include "common.h"
#include "line_data.h"

/* tmp_obj */
struct line_data tmp_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data *tmp_obj = &tmp_obj_raw;


int init_list ( node **obj )
{
    *obj = NULL;

    return ( 0 );
}

node *allocate_mem_to_one_node ( void )
{
    return ( struct line_data * ) calloc ( 1, sizeof ( struct line_data ) );
}

void set_list ( node *obj, char *line, node *obj_next )
{
    const char* test_line = "\0";
    int len = 0;
    len = ( int ) strlen ( line );
    if ( len < 0 )
    {
        printf("can't set %s\n",line);
        exit ( EXIT_FAILURE );
    }
    if ( len > MAX_LINE_LENGTH )
        strncpy ( ( char* ) obj->_line, test_line, 1 );
    else
        strncpy ( ( char* ) obj->_line, line, MAX_LINE_LENGTH - 1 );
    obj->next = obj_next;
    free( obj_next );
}

int insert_node_top_of_the_list ( node **obj, char *line )
{
    /* setting current obj to the new obj */
    node *obj_next = *obj;
    *obj = allocate_mem_to_one_node ( );
    /* setting current obj the the next pointer, this makes new object to the top of the list */
    set_list ( *obj, line, obj_next );

    return ( 0 );
}

int append_list ( node **obj, char *line )
{
    /* if no node found in the object, insert node in the very top of it */
    if ( *obj == NULL )
    {
        insert_node_top_of_the_list ( obj, line );
    }
    /* if some node exists in the object, find the very last of it and appending the new node */
    else
    {
        node *obj_new = *obj;
        while ( obj_new->next != NULL )
            obj_new = obj_new->next;
        obj_new->next = allocate_mem_to_one_node ( );
        set_list ( obj_new->next, line, NULL );
    }

    return ( 0 );
}

int bubble_sort_object_by_the_string ( node **obj, char *str_arr [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ] ) 
{
    
    node *ptr_tmp = *obj;
    char str_cmp_line  [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ] [ MAX_LINE_LENGTH ];
    int i = 0;
    for ( i = 0; i < MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR; i++ )
        memset ( str_cmp_line [ i ], '\0', sizeof ( str_cmp_line [ i ] ) ); 
    char *str_tmp;
    int obj_size = 0, j = 0, ii = 0;

    /* read from object and copy strings to an array */
    while ( ptr_tmp != NULL )
    {
        str_arr [ obj_size ] = ( char * ) & ( ptr_tmp->_line [ 0 ] ); 
        obj_size++;
        ptr_tmp = ptr_tmp->next;
    }
    /* bubble sort the array */
    for ( j= 0; j < obj_size; j++ )
    {
        /* This makes largest item to the end of an array. */
        for ( i = 0; i < obj_size - ( 1 + j ); i++ )
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
    return ( obj_size );
}

char *search_list ( node **obj, const char *line, char result [ MAX_LINE_LENGTH ] )
{
    node *ptr_tmp = *obj;
    char str_cmp_line [ MAX_LINE_LENGTH ];
    memset ( str_cmp_line, '\0', MAX_LINE_LENGTH ); 
    char str_cmp__line [ MAX_LINE_LENGTH ];
    memset ( str_cmp__line, '\0', MAX_LINE_LENGTH ); 
    strcpy ( str_cmp_line, line );
    memset ( result, '\0', MAX_LINE_LENGTH ); 
    char *result_p = & ( result [ MAX_LINE_LENGTH ] );

    const char s [ 8 ] = "="; /* this is the delimiter */

    while ( ptr_tmp != NULL )
    {
        strcpy ( str_cmp__line, ptr_tmp->_line );

        char *token = NULL;
        token = strtok ( ( char * ) str_cmp__line, s );

        if ( ( strcmp ( str_cmp__line, "" ) != 0 ) && ( strstr ( str_cmp_line, token) != NULL ) )
        {
            strcpy ( result, ptr_tmp->_line );
            return ( result_p );
        }
        ptr_tmp = ptr_tmp->next;
    }

    return ( result_p );
}

int print_and_file_write_analyzed_files ( node **obj, const char *expression , const char *word, FILE *fp_w )
{
    node *ptr_tmp = *obj;

    while ( ptr_tmp != NULL )
    {
        /* moving next, do something, moving next ... */
        char str_tmp [ MAX_LINE_LENGTH ] = "#";
        int str_len = 0;
        str_len = ( int ) strlen ( ptr_tmp->_line );
        if ( str_len < 0 )
        {
            printf("can't set %s\n",ptr_tmp->_line);
            exit ( EXIT_FAILURE );
        }
        if ( str_len >= 0 )
        {
            strncpy ( str_tmp, ptr_tmp->_line, MAX_LINE_LENGTH - 1 ); 
        }

        if ( strstr ( str_tmp, expression ) != NULL )
        {
          if ( word != NULL )
          {
              printf("%s\n",str_tmp);
          }
          if ( fp_w != NULL )
              fprintf ( fp_w, "%s\n", str_tmp );
        }
        ptr_tmp = ptr_tmp->next;
    }

    return ( 0 );
}

void print_list ( node **obj )
{
    node *ptr_tmp = *obj;
    while ( ptr_tmp != NULL )
    {
        printf("%s\n", ptr_tmp->_line);
        ptr_tmp = ptr_tmp->next;
    }
}

void file_write_list ( node **obj, FILE *fp_w )
{
    node *ptr_tmp = *obj;
    while ( ptr_tmp != NULL )
    {
        fprintf ( fp_w, "%s\n", ptr_tmp->_line );
        ptr_tmp = ptr_tmp->next;
    }
    ptr_tmp = NULL;
    free ( ptr_tmp );
}

int delete_obj ( node **obj )
{
    node *obj_new = ( *obj ) -> next;
    free ( *obj );
    *obj = obj_new;

    return ( 0 );
}

int clear_list ( node **obj )
{
    while ( *obj != NULL )
    {
        node *obj_new = ( *obj ) -> next;
        free ( *obj );
        *obj = obj_new;
    }
    return ( 0 );
}
