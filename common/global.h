/*
 *  global.h - common definitions
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

#ifndef SOSREPORT_ANALYZER_GLOBAL_H
#define SOSREPORT_ANALYZER_GLOBAL_H

#define PROGRAM_VERSION 1
#define PROGRAM_RELEASE 0
#define PROGRAM_SUB_RELEASE 1

/* the maximum line length of file name */
#define MAX_FULL_PATH_LENGTH  512

/* the maximum line length in the sar file */
#define MAX_LINE_LENGTH  4096

/* the maximum line length of file name */
#define MAX_FILE_NAME_LENGTH  255

/* the maximum analyze files */
#define MAX_ANALYZE_FILES 31 

#endif /* SOSREPORT_ANALYZER_GLOBAL_H */
