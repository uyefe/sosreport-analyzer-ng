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

#include "../common/global.h"
#include "../common/common_line_data.h"

/* the maximum line length in the configuration file */
#define MAX_LINE_LENGTH    4096

/* the maximum item numbers in the configuration file */
#define MAX_ITEM_NUMBERS    20 

/* the maximum item strings in the configuration file */
#define MAX_ITEM_STRINGS    30 

/* the delimiters of tokens */
#define TOKEN_DELIM "="

/* 20 items each 30 bytes */
typedef struct
{
    char item_name  [ MAX_ITEM_NUMBERS ] [ MAX_ITEM_STRINGS + 1 ];

} item_arr;

/* 488 files each 255 bytes */
typedef struct
{
    char file_name  [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ] [ MAX_FILE_NAME_LENGTH + 1 ];

} file_name_arr;

typedef struct
{
    char member [ MAX_LINE_LENGTH ];
    int item_num;
    int file_num;
    item_arr item_names;
    file_name_arr file_names;

} config_each;

/*
 *  The members which should be analyzed.
 */
struct sosreport_analyzer_config
{
    config_each mcinfo_boot_grub_;
    config_each mcinfo_cmdlog_;
    config_each date;
    config_each lsb_release;
    config_each uname;
    config_each hostname;
    config_each uptime;
    config_each proc_cpuinfo;
    config_each root_anaconda_ks_cfg;
    config_each dmidecode;
    config_each lsmod;
    config_each lspci;
    config_each df;
    config_each installed_rpms;
    config_each vgdisplay;
    config_each free;
    config_each ip_addr;
    config_each route;
    config_each last;
    config_each ps;
    config_each lsof;
    config_each netstat;
    config_each lib_;
    config_each dev_;
    config_each usr_lib_systemd_;
    config_each usr_;
    config_each sys_module_;
    config_each etc_NetworkManager_;
    config_each etc_anacrontab;
    config_each etc_audit_;
    config_each etc_crontab;
    config_each etc_cron_deny;
    config_each etc_cron_d_;
    config_each etc_cron_hourly_;
    config_each etc_cron_daily_;
    config_each etc_cron_weekly_;
    config_each etc_cron_monthly_;
    config_each etc_default_;
    config_each etc_dnf_;
    config_each etc_firewalld_;
    config_each etc_host;
    config_each etc_httpd_;
    config_each etc_kdump_conf;
    config_each etc_logrotate_conf;
    config_each etc_logrotate_d_;
    config_each etc_lvm_;
    config_each etc_modprobe_d_;
    config_each etc_nsswitch_conf;
    config_each etc_pam_d_;
    config_each etc_pki_;
    config_each etc_rsyslog_conf;
    config_each etc_selinux_;
    config_each etc_sysconfig_network_scripts_ifcfg_;
    config_each etc_sysconfig_;
    config_each etc_sysctl_conf;
    config_each etc_systemd_system_;
    config_each etc_systemd_;
    config_each etc_udev_;
    config_each etc_yum_conf;
    config_each etc_yum_repos_d_;
    config_each etc_yum_;
    config_each etc_;
    config_each sos_commands_apache_;
    config_each sos_commands_abrt_;
    config_each sos_commands_auditd_;
    config_each sos_commands_boot_;
    config_each sos_commands_devices_udevadm_info___export_db;
    config_each sos_commands_devicemapper_;
    config_each sos_commands_dnf_;
    config_each sos_commands_firewalld_;
    config_each sos_commands_ipmitool_;
    config_each sos_commands_kernel_sysctl__a;
    config_each sos_commands_logs_journalctl___no_pager;
    config_each sos_commands_lvm2_;
    config_each sos_commands_memory_;
    config_each sos_commands_networking_ethtool__S;
    config_each sos_commands_networking_ethtool__i;
    config_each sos_commands_networking_;
    config_each sos_commands_networkmanager_;
    config_each sos_commands_pam_;
    config_each sos_commands_sar_;
    config_each sos_commands_scsi_lsscsi;
    config_each sos_commands_selinux_;
    config_each sos_commands_usb_;
    config_each sos_commands_yum_;
    config_each sos_commands_virsh_;
    config_each sos_commands_wireless_;
    config_each sos_commands_;
    config_each var_crash_;
    config_each var_log_audit_;
    config_each var_log_dmesg;
    config_each var_log_messages;
    config_each var_log_secure;
    config_each var_spool_cron_;
    config_each var_;
    config_each proc_meminfo;
    config_each proc_net_dev;
    config_each proc_net_sockstat;
    config_each proc_interrupts;
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
