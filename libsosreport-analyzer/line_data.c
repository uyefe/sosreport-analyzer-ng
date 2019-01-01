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

#include "line_data.h"

int init_list ( node **obj )
{
    *obj = NULL;

    return ( 0 );
}

node *allocate_mem_to_one_node ( )
{
    return ( struct line_data * ) malloc ( sizeof ( struct line_data ) );
}

void set_list ( node *obj, char *line, node *obj_next )
{
    const char* test_line = "No good!";
    int len = 0;
    len = strlen ( line );
    if ( len > MAX_LINE_LENGTH + 1 )
        strncpy ( ( char* ) obj->_line, test_line, 10 );
    else
        strncpy ( ( char* ) obj->_line, line, MAX_LINE_LENGTH + 1 );
    obj->next = obj_next;
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
        /* next pointer should be NULL because nothing beyond it */
        set_list ( obj_new->next, line, NULL );
    }

    return ( 0 );
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

        str_len = strlen ( ptr_tmp->_line );
        if ( str_len != 0 )
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
}

int delete_obj ( node **obj )
{
    if ( *obj != NULL )
    {
        /* moving next, do something, moving next ... */
        node *obj_new = ( *obj ) -> next;
        free ( *obj );
        *obj = obj_new;
    } 

    return ( 0 );
}

int clear_list ( node **obj )
{
    while ( *obj != NULL )
    {
        delete_obj ( obj );
    }

    return ( 0 );
}
