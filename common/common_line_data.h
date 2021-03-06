/*
 *  common_line_data.h - object definitions
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef SOSREPORT_ANALYZER_COMMON_LINE_DATA_H
#define SOSREPORT_ANALYZER_COMMON_LINE_DATA_H

/* --max-stackframe=2007048 / 4096 = 489, so... */
#define MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR 488

/* the maximum line length in the sar file */
#define MAX_LINE_LENGTH  4096 

/* ---------- macros ( tweak if needed ) ---------- */

/*
 * Type for line retrieved from a file.
 */

typedef struct line_data
{
    const char _line [ MAX_LINE_LENGTH - 1 ];
    struct line_data *next;

} node;

/*
 * Declare type of file_data which should contain dir or file name 
 */
typedef struct
{
    /* file name to be written */
    char dirname [ MAX_LINE_LENGTH ];
    /* sos file name to be written */
    char sos_file_name_to_be_written [ MAX_LINE_LENGTH ];
    /* sar file name to be written */
    char sar_file_name_to_be_written [ MAX_LINE_LENGTH ];
    /* sar file name to be written */
    char ps_file_name_to_be_written [ MAX_LINE_LENGTH ];
} file_data;

/*
 * This should becom living object
 *
 */
struct dir_file_name
{
    file_data dir_file_names;
};

/**** line_data things ****/

/*
 * Function Name: allocate_mem_to_one_node ()
 *
 * This function allocates the new memory newly to the line list object (node) 
 *
 *  Caller : insert_node_top_of_the_list ()
 *  Caller : append_list ()
 *           
 */
node *allocate_mem_to_one_node ();

/*
 * Function Name: set_list ()
 *
 * This function sets values to the list object (node) 
 *
 *  Caller : insert_node_top_of_the_list ()
 *  Caller : append_list ()
 *
 */
void set_list ( node *obj, char *line, node *obj_next );

/*
 * Function Name: insert_node_top_of_the_list ()
 *
 * This function inserts list object (node) at the top of the list
 *
 *  Calls : allocate_mem_to_one_node()
 *  Calls : set_list()
 *
 */
int insert_node_top_of_the_list ( node **obj, char *line );

/*
 * Function Name: append_list ()
 *
 * This function appends new object to the list object (node) 
 *
 *  Caller : allocate_mem_to_one_node ()
 *  Caller : set_list ()
 *
 *  Calls : allocate_mem_to_one_node ()
 *  Calls : insert_node_top_of_the_list ()
 *
 */
int append_list ( node **obj, char *line );

/*
 * Function Name: move_obj_to_the_last ()
 *
 * This function moves some objects to the last by file no.x  
 *
 * Caller : main ()
 *
 */
int move_obj_to_the_last ( node **obj, int x );

/*
 * Function Name: print_and_file_write_analyzed_files ()
 *
 * This function searchs list object (node) by the given expression and print and write to file 
 *
 *  Caller : main ()
 *
 */
int print_and_file_write_analyzed_files ( node **obj, const char *expression , const char *word, FILE *fp_w );

/*
 * Function Name: append_header_to_ps_objs ()
 *
 * This function appends postscript header to ps files
 *
 *  Caller : common.c ()
 *
 */
int append_header_to_ps_objs ( node **obj, FILE *fp_w );

/*
 * Function Name: append_rectangular_to_ps_objs ()
 *
 * This function appends rectangular to ps files
 *
 *  Caller : common.c ()
 *
 */
int append_rectangular_to_ps_objs ( node **obj, FILE *fp_w, const char *element );

/*
 * Function Name: append_labels_to_ps_obj ()
 *
 * This function appends postscript labels to ps file 
 *
 *  Caller : main ()
 *
 */
int append_labels_to_ps_obj ( node **obj, FILE *fp_w, const char *item );

/*
 * Function Name: print_list ()
 *
 * This function prints the list nodes
 *
 *  Caller : main ()
 *
 */
void print_list ( node **obj );

/*
 * Function Name: file_write_list ()
 * 
 * This function writes list nodes to the file
 *
 *  Caller : main ()
 *
 */
void file_write_list ( node **obj, FILE *fp_w );

/*
 * Function Name: init_list ()
 *
 * This function initializes the line list object ( node ) 
 *
 *  Caller : create_sar_analyzer_obj ()
 *
 */
int init_list ( node **obj );

/*
 * Function Name: delete_obj ()
 *
 * This function clears the list object (node) 
 *
 *  Caller : clear_list ()
 *
 */
int delete_obj ( node **obj  );

/*
 * Function Name: clear_list ()
 *
 * This function clears the line list object (node) 
 *
 *  Caller : free_sar_analyzer_obj ()
 *
 *  Calls : delete_obj ()
 *
 */
int clear_list ( node **obj  );

#endif /* SOSREPORT_ALANYZER_COMMON_LINE_DATA_H */
