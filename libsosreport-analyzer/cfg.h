/*
 *  cfg.h - configuration definition 
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

#ifndef SOSREPORT_ANALYZER__CFG_H
#define SOSREPORT_ANALYZER__CFG_H

/* the maximum line length in the configuration file */
#define MAX_LINE_LENGTH    4096

/* the delimiters of tokens */
#define TOKEN_DELIM "="

/*
 *  The members which should be analyzed.
 */
struct sosreport_analyzer_config
{
    /* should be all */
    char mcinfo_boot_grub_ [ MAX_LINE_LENGTH ];
    /* should be all */
    char mcinfo_cmdlog_ [ MAX_LINE_LENGTH ];
    /* should be all */
    char date [ MAX_LINE_LENGTH ];
    /* should be all */
    char lsb_release [ MAX_LINE_LENGTH ];
    /* should be all */
    char uname [ MAX_LINE_LENGTH ];
    /* should be all */
    char hostname [ MAX_LINE_LENGTH ];
    /* should be all */
    char uptime [ MAX_LINE_LENGTH ];
    /* should be all */
    char root_anaconda_ks_cfg [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char dmidecode [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char lsmod [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char lspci [ MAX_LINE_LENGTH ];
    /* should be all */
    char sos_commands_scsi_lsscsi [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char installed_rpms [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char df [ MAX_LINE_LENGTH ];
    /* should be all */
    char vgdisplay [ MAX_LINE_LENGTH ];
    /* should be all */
    char free [ MAX_LINE_LENGTH ];
    /* should be all */
    char ip_addr [ MAX_LINE_LENGTH ];
    /* should be all */
    char route [ MAX_LINE_LENGTH ];
    /* should be all */
    char last [ MAX_LINE_LENGTH ];
    /* should be all */
    char ps [ MAX_LINE_LENGTH ];
    /* should be all */
    char lsof [ MAX_LINE_LENGTH ];
    /* should be all */
    char netstat [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char etc_kdump_conf [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char etc_sysctl_conf [ MAX_LINE_LENGTH ];
    /* should be all */
    char etc_sysconfig_network_scripts_ifcfg_ [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char proc_meminfo [ MAX_LINE_LENGTH ];
    /* should be all */
    char proc_net_dev [ MAX_LINE_LENGTH ];
    /* should be all */
    char proc_net_sockstat [ MAX_LINE_LENGTH ];
    /* should be all */
    char proc_interrupts [ MAX_LINE_LENGTH ];
    /* should be all */
    char etc_logrotate_conf [ MAX_LINE_LENGTH ];
    /* should be all */
    char etc_cron_d_ [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char var_log_messages [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char var_log_secure [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char var_log_audit_ [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char sos_commands_kernel_sysctl__a [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char sos_commands_logs_journalctl___no_pager [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char sos_commands_networking_ethtool__S [ MAX_LINE_LENGTH ];
    /* allows word delimited by space */
    char sos_commands_boot_ [ MAX_LINE_LENGTH ];
};

/*  This is a pointer to the global configuration, it should be available
 *  once cfg_init() was called
 */
extern struct sosreport_analyzer_config *sosreport_analyzer_cfg;

/*  Initialize the configuration in sosreport-analyzer. This method
 *  will read the default configuration file and call exit()
 *  if an error occurs.
 */
void cfg_init ( const char *file_name, int mcinfo );

/* This function works like strtok() except that the original string is
 *  not modified and a pointer within str to where the next token begins
 *  is returned (this can be used to pass to the function on the next
 *  iteration). If no more tokens are found or the token will not fit in
 *  the buffer, NULL is returned. 
 */
char *get_token ( char **line, char *buf, size_t buflen );

/* Set the configuration information to the defaults after memory is allocated */
void cfg_defaults ( struct sosreport_analyzer_config *cfg );

/* This function reads config file. */
void cfg_read ( const char *file_name, struct sosreport_analyzer_config *cfg, int mcinfo );

/* This function sets member to appropriate struct. */
int set_member_to_struct ( const char *keyword, char *line, struct sosreport_analyzer_config *cfg, int mcinfo );

/*  This function frees the memory which had been allocated
 *  for config file.
 */
void cfg_clear ( void );

/*  This function appends member strigs to sos_header_obj with their items. */
void append_sos_header_obj ( const char *member, struct sosreport_analyzer_config *cfg, int mcinfo );

#endif /* SOSREPORT_ANALYZER__CFG_H */
