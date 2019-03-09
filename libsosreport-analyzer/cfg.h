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

typedef struct
{
    char member [ MAX_LINE_LENGTH ];
    int item_num;

} config_each;

/*
 *  The members which should be analyzed.
 */
struct sosreport_analyzer_config
{
    /* should be all */
    config_each mcinfo_boot_grub_;
    /* should be all */
    config_each mcinfo_cmdlog_;
    /* should be all */
    config_each date;
    /* should be all */
    config_each lsb_release;
    /* should be all */
    config_each uname;
    /* should be all */
    config_each hostname;
    /* should be all */
    config_each uptime;
    /* should be all */
    config_each root_anaconda_ks_cfg;
    /* allows word delimited by space */
    config_each dmidecode;
    /* allows word delimited by space */
    config_each lsmod;
    /* should be all */
    config_each etc_modprobe_d_;
    /* allows word delimited by space */
    config_each lspci;
    /* allows word delimited by space */
    config_each sos_commands_devices_udevadm_info___export_db;
    /* should be all */
    config_each sos_commands_scsi_lsscsi;
    /* allows word delimited by space */
    config_each installed_rpms;
    /* allows word delimited by space */
    config_each df;
    /* should be all */
    config_each vgdisplay;
    /* should be all */
    config_each free;
    /* should be all */
    config_each ip_addr;
    /* should be all */
    config_each route;
    /* should be all */
    config_each last;
    /* should be all */
    config_each ps;
    /* should be all */
    config_each lsof;
    /* should be all */
    config_each netstat;
    /* should be all */
    config_each etc_default_;
    /* allows word delimited by space */
    config_each etc_kdump_conf;
    /* allows word delimited by space */
    config_each etc_sysctl_conf;
    /* should be all */
    config_each etc_rsyslog_conf;
    /* should be all */
    config_each etc_sysconfig_network_scripts_ifcfg_;
    /* allows word delimited by space */
    config_each proc_meminfo;
    /* should be all */
    config_each proc_net_dev;
    /* should be all */
    config_each proc_net_sockstat;
    /* should be all */
    config_each proc_interrupts;
    /* should be all */
    config_each etc_logrotate_conf;
    /* should be all */
    config_each etc_logrotate_d_;
    /* should be all */
    config_each etc_pki_;
    /* should be all */
    config_each etc_cron_d_;
    /* should be all */
    config_each var_log_dmesg;
    /* allows word delimited by space */
    config_each var_log_messages;
    /* allows word delimited by space */
    config_each var_log_secure;
    /* allows word delimited by space */
    config_each var_log_audit_;
    /* allows word delimited by space */
    config_each var_crash_;
    /* allows word delimited by space */
    config_each sos_commands_kernel_sysctl__a;
    /* allows word delimited by space */
    config_each sos_commands_logs_journalctl___no_pager;
    /* allows word delimited by space */
    config_each sos_commands_networking_ethtool__S;
    /* allows word delimited by space */
    config_each sos_commands_networking_ethtool__i;
    /* allows word delimited by space */
    config_each sos_commands_boot_;
    /* should be all */
    config_each etc_httpd_;
    /* allows word delimited by space */
    config_each proc_;
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
