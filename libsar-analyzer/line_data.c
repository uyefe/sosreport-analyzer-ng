/*
 * line_data.c - object functions 
 * This file contains the contents of sar-analyzer.
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

int move_obj_to_the_last ( node **obj, int x )
{
    if ( x == 0 )
        return ( 0 );

    int files_n;
    files_n = 0;
    files_n = get_files_n ( );

    if ( x >= files_n )
    {
        puts ( "Can't move files." );
        return ( 0 );
    }

    int x_tmp, y;
    x_tmp = 0, y = 0;
    char s [ MAX_LINE_LENGTH ] = { '\0' };
    node *ptr_tmp = *obj, **ptr_tmp_pre;
    x_tmp = x; 
    /* should be incremented so... */
    x_tmp++;
     
    snprintf (s, MAX_FILE_NAME_LENGTH, "file no.%d", x_tmp );

    while ( strstr ( ptr_tmp->_line, s ) == 0 )
    {
        append_list ( obj, ( char * ) ptr_tmp->_line );
        ptr_tmp = ptr_tmp->next;
        ptr_tmp_pre = obj;
        delete_obj ( ptr_tmp_pre );
        y++;
    }
    printf ( "Moved %d file(s) which listed at the top to the bottom.\n\n", x );
    return ( 0 );
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
