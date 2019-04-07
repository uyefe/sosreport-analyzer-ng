/*
 *  setter_getter.h - setter_getter definitions
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

#include "cfg.h"

#ifndef SOSREPORT_ANALYZER_SETTER_GETTER_H
#define SOSREPORT_ANALYZER_SETTER_GETTER_H


/* 
 *  Function Name: get_items_of_member ()
 *
 *  This function returns items of certain member.
 *  If nothing exists, returns -1.
 *
 *  Caller : 
 *
 *  Calls : none
 *
 */
char *get_items_of_member ( const char *member );

/* 
 *  Function Name: get_item_numbers_of_member ()
 *
 *  This function returns item numbers of certain member.
 *  If nothing exists, returns -1.
 *
 *  Caller : 
 *
 *  Calls : none
 *
 */
int get_item_numbers_of_member ( const char *member );

/* 
 *  Function Name: get_file_numbers_of_member ()
 *
 *  This function returns file numbers of certain member.
 *  If nothing exists, returns -1.
 *
 *  Caller : 
 *
 *  Calls : none
 *
 */
int get_file_numbers_of_member ( const char *member );

/* 
 *  Function Name: set_item_numbers_of_member ()
 *
 *  This function sets item numbers of certain member.
 *
 *  Caller : 
 *
 *  Calls : none
 *
 */
int set_item_numbers_of_member ( const char *member, int x );

/* 
 *  Function Name: set_file_numbers_of_member ()
 *
 *  This function sets file numbers of certain member.
 *
 *  Caller : 
 *
 *  Calls : none
 *
 */
int set_file_numbers_of_member ( const char *member, int x );

/* 
 *  Function Name: member_item_exists ()
 *
 *  This function returns 0 if certain member has any item.
 *
 *  Caller : 
 *
 *  Calls : none
 *
 */
int member_item_exists ( const char *member );

/* 
 *  Function Name: init_item_numbers_of_member ()
 *
 *  This function sets 0 to each item numbers of member.
 *
 *  Caller : 
 *
 *  Calls : none
 *
 */
int init_item_numbers_of_member ( void );

/* 
 *  Function Name: set_item_arr_string ()
 *
 *  This function sets item string for a member which had been set in config file.
 *
 *  Caller : 
 *
 *  Calls : none
 *
 */
int set_item_arr_string ( const char *member, int x, const char *item );

/* 
 *  Function Name: get_item_arr_string ()
 *
 *  This function gets item string for a member which had been set in config file.
 *
 *  Caller : 
 *
 *  Calls : none
 *
 */
char *get_item_arr_string ( const char *member, int x );

#endif /* SOSREPORT_ANALYZER_SETTER_GETTER_H */
