/*
 *  line_data.h - object definitions
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../libsar-analyzer/common.h" 
#include "../common/common_line_data.h" 

#ifndef SOSREPORT_ANALYZER_LINE_DATA_H
#define SOSREPORT_ANALYZER_LINE_DATA_H

int init_list ( node **obj );
node *allocate_mem_to_one_node ( void );
void set_list ( node *obj, char *line, node *obj_next );
int append_list ( node **obj, char *line );
int *bubble_sort_object_by_the_string ( node **obj );
int print_and_file_write_analyzed_files ( node **obj, const char *expression , const char *word, FILE *fp_w );
void print_list ( node **obj );
void file_write_list ( node **obj, FILE *fp_w );
int delete_obj ( node **obj );
int clear_list ( node **obj );

/*
 * Function Name: search_list ()
 *
 * This function search given string from the node and if found, set string to char array
 *
 *  Caller : read_file_pre ()
 *
 *  Calls : none
 *
 */
char *search_list ( node **obj, const char *line, char result [ MAX_LINE_LENGTH ] );


#endif /* SOSREPORT_ALANYZER_LINE_DATA_H */
