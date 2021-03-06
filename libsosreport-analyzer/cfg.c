/*
 *  cfg.c - configuration functions 
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

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* for is_space */
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include "common.h"
#include "cfg.h"

/* should be set to NULL, this will be checked in cfg_init() */
struct sosreport_analyzer_config *sosreport_analyzer_cfg = NULL;

const char msg_cfg_read [ 36 ] = "cfg_read was called by SIG_VALUE !\n";
const char msg_cfg_read_ok [ 40 ] = "file value was reloaded by SIG_VALUE !\n";

void cfg_defaults ( struct sosreport_analyzer_config *cfg )
{
    memset ( cfg, 0, sizeof ( struct sosreport_analyzer_config ) );
    if ( cfg == NULL )
    {
        printf("cfg.c: cfg_defaults() failed to memset");
        exit(EXIT_FAILURE);
    }
}

char *get_token ( char **line, char *buf, size_t buflen )
{
    size_t len;

    if ( ( line == NULL ) || ( *line == NULL ) || ( **line == '\0' ) || ( buf == NULL ) )
        return NULL;

    /* find the beginning and length of the token */
    *line += strspn ( *line, TOKEN_DELIM );
    len = strcspn ( *line, TOKEN_DELIM );

    /* check if there is a token */
    if ( len == 0 )
    {
        *line = NULL ;
        return NULL;
    }

    /* limit the token length */
    if ( len >= buflen )
        len = buflen - 1;

    /* copy the token */
    strncpy ( buf, *line, len );
    buf [ len ] = '\0';

    /* skip to the next token */
    *line += len;
    *line += strspn ( *line, TOKEN_DELIM );

    /* return the token */
    return buf;
}

int set_member_to_struct ( const char *keyword, char *line, struct sosreport_analyzer_config *cfg, int mcinfo )
{
    if ( strstr ( line, "skip" ) != NULL )
            printf("skip member '%s'.\n",keyword);
    else
    {
        /* common members for both mcinfo and sosreport */
        if ( strcmp ( keyword, "etc/host" ) == 0 )
            strncpy ( cfg->etc_host.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/modprobe.d/" ) == 0 )
            strncpy ( cfg->etc_modprobe_d_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 )
            strncpy ( cfg->etc_sysconfig_network_scripts_ifcfg_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/crontab" ) == 0 )
            strncpy ( cfg->etc_crontab.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/cron.deny" ) == 0 )
            strncpy ( cfg->etc_cron_deny.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/cron.d/" ) == 0 )
            strncpy ( cfg->etc_cron_d_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/cron.hourly/" ) == 0 )
            strncpy ( cfg->etc_cron_hourly_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/cron.daily/" ) == 0 )
            strncpy ( cfg->etc_cron_daily_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/cron.weekly/" ) == 0 )
            strncpy ( cfg->etc_cron_weekly_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/cron.monthly/" ) == 0 )
            strncpy ( cfg->etc_cron_monthly_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/buddyinfo" ) == 0 )
            strncpy ( cfg->proc_buddyinfo.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/cpuinfo" ) == 0 )
            strncpy ( cfg->proc_cpuinfo.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/interrupts" ) == 0 )
            strncpy ( cfg->proc_interrupts.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/meminfo" ) == 0 )
            strncpy ( cfg->proc_meminfo.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/slabinfo" ) == 0 )
            strncpy ( cfg->proc_slabinfo.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/vmstat" ) == 0 )
            strncpy ( cfg->proc_vmstat.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/zoneinfo" ) == 0 )
            strncpy ( cfg->proc_zoneinfo.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "var/crash/" ) == 0 )
            strncpy ( cfg->var_crash_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "var/log/dmesg" ) == 0 )
            strncpy ( cfg->var_log_dmesg.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "var/log/messages" ) == 0 )
            strncpy ( cfg->var_log_messages.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "var/spool/cron/" ) == 0 )
            strncpy ( cfg->var_spool_cron_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "etc/" ) == 0 )
            strncpy ( cfg->etc_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "var/" ) == 0 )
            strncpy ( cfg->var_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/" ) == 0 )
            strncpy ( cfg->proc_.member, line, MAX_LINE_LENGTH - 1 );

        /* mcinfo only */
        if ( mcinfo == 1 )
        {
            if ( strcmp ( keyword, "boot/grub/" ) == 0 )
                strncpy ( cfg->mcinfo_boot_grub_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "cmdlog/" ) == 0 )
                strncpy ( cfg->mcinfo_cmdlog_.member, line, MAX_LINE_LENGTH - 1 );
        }
        /* sosreport only */
        else if ( mcinfo == 0 )
        {
            if ( strcmp ( keyword, "date" ) == 0 )
                strncpy ( cfg->date.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "df" ) == 0 )
                strncpy ( cfg->df.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "dmidecode" ) == 0 )
                strncpy ( cfg->dmidecode.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "free" ) == 0 )
                strncpy ( cfg->free.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "hostname" ) == 0 )
                strncpy ( cfg->hostname.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "installed-rpms" ) == 0 )
                strncpy ( cfg->installed_rpms.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "ip_addr" ) == 0 )
                strncpy ( cfg->ip_addr.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "last" ) == 0 )
                strncpy ( cfg->last.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "lsb-release" ) == 0 )
                strncpy ( cfg->lsb_release.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "lsof" ) == 0 )
                strncpy ( cfg->lsof.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "lsmod" ) == 0 )
                strncpy ( cfg->lsmod.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "lspci" ) == 0 )
                strncpy ( cfg->lspci.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "netstat" ) == 0 )
                strncpy ( cfg->netstat.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "ps" ) == 0 )
                strncpy ( cfg->ps.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "route" ) == 0 )
                strncpy ( cfg->route.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "uname" ) == 0 )
                strncpy ( cfg->uname.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "uptime" ) == 0 )
                strncpy ( cfg->uptime.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "vgdisplay" ) == 0 )
                strncpy ( cfg->vgdisplay.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/NetworkManager/" ) == 0 )
                strncpy ( cfg->etc_NetworkManager_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/anacrontab" ) == 0 )
                strncpy ( cfg->etc_anacrontab.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/audit/" ) == 0 )
                strncpy ( cfg->etc_audit_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/default/" ) == 0 )
                strncpy ( cfg->etc_default_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/dnf/" ) == 0 )
                strncpy ( cfg->etc_dnf_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/firewalld/" ) == 0 )
                strncpy ( cfg->etc_firewalld_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/httpd/" ) == 0 )
                strncpy ( cfg->etc_httpd_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/kdump.conf" ) == 0 )
                strncpy ( cfg->etc_kdump_conf.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/logrotate.conf" ) == 0 )
                strncpy ( cfg->etc_logrotate_conf.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/logrotate.d/" ) == 0 )
                strncpy ( cfg->etc_logrotate_d_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/lvm/" ) == 0 )
                strncpy ( cfg->etc_lvm_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/nsswitch.conf" ) == 0 )
                strncpy ( cfg->etc_nsswitch_conf.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/pam.d/" ) == 0 )
                strncpy ( cfg->etc_pam_d_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/pki/" ) == 0 )
                strncpy ( cfg->etc_pki_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/rsyslog.conf" ) == 0 )
                strncpy ( cfg->etc_rsyslog_conf.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/selinux/" ) == 0 )
                strncpy ( cfg->etc_selinux_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/sysconfig/" ) == 0 )
                strncpy ( cfg->etc_sysconfig_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/sysctl.conf" ) == 0 )
                strncpy ( cfg->etc_sysctl_conf.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/systemd/" ) == 0 )
                strncpy ( cfg->etc_systemd_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/systemd/system/" ) == 0 )
                strncpy ( cfg->etc_systemd_system_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/udev/" ) == 0 )
                strncpy ( cfg->etc_udev_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/yum.conf" ) == 0 )
                strncpy ( cfg->etc_yum_conf.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/yum/" ) == 0 )
                strncpy ( cfg->etc_yum_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/yum.repos.d/" ) == 0 )
                strncpy ( cfg->etc_yum_repos_d_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "proc/net/dev" ) == 0 )
                strncpy ( cfg->proc_net_dev.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "proc/net/sockstat" ) == 0 )
                strncpy ( cfg->proc_net_sockstat.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "root/anaconda-ks.cfg" ) == 0 )
                strncpy ( cfg->root_anaconda_ks_cfg.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/abrt/" ) == 0 )
                strncpy ( cfg->sos_commands_abrt_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/auditd/" ) == 0 )
                strncpy ( cfg->sos_commands_auditd_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/apache/" ) == 0 )
                strncpy ( cfg->sos_commands_apache_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/boot/" ) == 0 )
                strncpy ( cfg->sos_commands_boot_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/devicemapper/" ) == 0 )
                strncpy ( cfg->sos_commands_devicemapper_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/devices/udevadm_info_--export-db" ) == 0 )
                strncpy ( cfg->sos_commands_devices_udevadm_info___export_db.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/dnf/" ) == 0 )
                strncpy ( cfg->sos_commands_dnf_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/firewalld/" ) == 0 )
                strncpy ( cfg->sos_commands_firewalld_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/ipmitool/" ) == 0 )
                strncpy ( cfg->sos_commands_ipmitool_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/kernel/sysctl_-a" ) == 0 )
                strncpy ( cfg->sos_commands_kernel_sysctl__a.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/logs/journalctl_--no-pager" ) == 0 )
                strncpy ( cfg->sos_commands_logs_journalctl___no_pager.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/lvm2/" ) == 0 )
                strncpy ( cfg->sos_commands_lvm2_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/memory/" ) == 0 )
                strncpy ( cfg->sos_commands_memory_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/networking/ethtool_-S" ) == 0 )
                strncpy ( cfg->sos_commands_networking_ethtool__S.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/networking/ethtool_-i" ) == 0 )
                strncpy ( cfg->sos_commands_networking_ethtool__i.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/networking/" ) == 0 )
                strncpy ( cfg->sos_commands_networking_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/networkmanager/" ) == 0 )
                strncpy ( cfg->sos_commands_networkmanager_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/pam/" ) == 0 )
                strncpy ( cfg->sos_commands_pam_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/sar/" ) == 0 )
                strncpy ( cfg->sos_commands_sar_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/scsi/lsscsi" ) == 0 )
                strncpy ( cfg->sos_commands_scsi_lsscsi.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/selinux/" ) == 0 )
                strncpy ( cfg->sos_commands_selinux_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/usb/" ) == 0 )
                strncpy ( cfg->sos_commands_usb_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/virsh/" ) == 0 )
                strncpy ( cfg->sos_commands_virsh_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/yum/" ) == 0 )
                strncpy ( cfg->sos_commands_yum_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/wireless/" ) == 0 )
                strncpy ( cfg->sos_commands_wireless_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/" ) == 0 )
                strncpy ( cfg->sos_commands_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sys/module/" ) == 0 )
                strncpy ( cfg->sys_module_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "usr/lib/systemd/" ) == 0 )
                strncpy ( cfg->usr_lib_systemd_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "var/log/secure" ) == 0 )
                strncpy ( cfg->var_log_secure.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "var/log/audit/" ) == 0 )
                strncpy ( cfg->var_log_audit_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "dev/" ) == 0 )
                strncpy ( cfg->dev_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "lib/" ) == 0 )
                strncpy ( cfg->lib_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "usr/" ) == 0 )
                strncpy ( cfg->usr_.member, line, MAX_LINE_LENGTH - 1 );
        }
        else
            return ( 1 );
    }
    return ( 0 );
}

void cfg_read ( const char *file_name, struct sosreport_analyzer_config *cfg, int mcinfo )
{
    FILE *fp;
    int fd, rc, lnr = 0;
    struct stat st;
    char linebuf [ MAX_LINE_LENGTH ];
    char *line;
    char keyword [ 1024 ];
    int i;

    /* open the file */
    rc = open ( file_name, O_NOFOLLOW | O_RDONLY );
    if ( rc < 0 ) {
        if ( errno != ENOENT )
        {
            printf("Error opening %s (%s)",
                file_name,strerror(errno));
	    printf("Config file %s doesn't exist.\n",file_name);
            exit ( EXIT_FAILURE );
	}
    }
    fd = rc;

    /* check the file's permissions: owned by root, not world writable,
     * not symlink.
     */
    char str_tmp2 [ MAX_FILE_NAME_LENGTH ]; 
    memset ( str_tmp2, '\0', sizeof ( str_tmp2 ) ); 
    snprintf ( str_tmp2, MAX_LINE_LENGTH, "Config file %s opened for parsing",file_name );
    append_list ( &sos_header_obj, str_tmp2 );
    append_list ( &sos_header_obj, "--------" );

    if ( fstat ( fd, &st ) < 0) {
        printf("Error fstat'ing %s (%s)\n",file_name,strerror(errno)); 
        if ( close ( fd ) == -1 )
            printf("Error closing file pointer %d (%s)\n",(int)fd,strerror(errno)); 
        exit ( EXIT_FAILURE );
    }
    if ( st.st_uid != 0 ) {
        printf("Error - %s isn't owned by root\n",file_name); 
        if ( close ( fd ) == -1 )
            printf("Error closing file pointer %d (%s)\n",(int)fd,strerror(errno)); 
        exit ( EXIT_FAILURE );
    }
    if ( ( st.st_mode & S_IWOTH ) == S_IWOTH ) {
        printf("Error - %s is world writable",file_name );
        if ( close ( fd ) == -1 )
            printf("Error closing file pointer %d (%s)\n",(int)fd,strerror(errno)); 
        exit ( EXIT_FAILURE );
    }
    /* using macro to check file*/
    if ( !S_ISREG ( st.st_mode ) ) {
        printf("Error - %s is not a regular file",file_name );
        if ( close ( fd ) == -1 )
            printf("Error closing file pointer %d (%s)\n",(int)fd,strerror(errno)); 
        exit ( EXIT_FAILURE );
    }
    /* open config file */
    if ( ( fp = fopen ( file_name,"r" ) ) == NULL )
    {
        printf("can't open config file (%s): %s", file_name, strerror ( errno ) );
        if ( close ( fd ) == -1 )
            printf("Error closing file pointer %d (%s)\n",(int)fd,strerror(errno)); 
        exit ( EXIT_FAILURE );
    }
    /* read file and parse lines */
    while ( fgets ( linebuf, sizeof ( linebuf ), fp ) != NULL )
    {
        lnr++;
        line = linebuf;
        /* strip newline */
        i = ( int ) strlen ( line );
        if ( ( i <= 0 ) || ( line [ i - 1 ] != '\n' ) )
        {
            printf("%s:%d: line too long or last line missing newline\n", file_name, lnr);
            if ( close ( fd ) == -1 )
                printf("Error closing file pointer %d (%s)\n",(int)fd,strerror(errno)); 
            exit ( EXIT_FAILURE );
        }
        line [ i - 1 ] = '\0';
        /* ignore comment lines */
        if ( line [ 0 ] == '#' )
            continue;
        /* strip trailing spaces */
        for ( i--; ( i > 0 ) && isspace ( line [ i - 1 ] ); i-- )
            line [ i - 1 ] = '\0';

        /* get keyword from line and ignore empty lines */
        if ( get_token ( &line, keyword, sizeof ( keyword ) ) == NULL )
            continue;
        /* runtime options */
        if ( set_member_to_struct ( keyword, line, cfg, mcinfo ) != 0 )
        /* fallthrough */
        {
            printf("%s:%d: unknown keyword: '%s'\n", file_name, lnr, keyword );
            if ( close ( fd ) == -1 )
                printf("Error closing file pointer %d (%s)\n",(int)fd,strerror(errno)); 
            exit ( EXIT_FAILURE );
        }
    }
    /* we're done reading file, close */
    fclose ( fp );

    /* appending member strigs with their items which had been set by config file */
    /* the order of these are appended to object, so, don't mingle them */
    if ( mcinfo == 1 ) 
    {
        append_sos_header_obj ( "proc/cpuinfo", cfg, mcinfo );
        append_sos_header_obj ( "boot/grub/", cfg, mcinfo );
        append_sos_header_obj ( "cmdlog/", cfg, mcinfo );
        append_sos_header_obj ( "etc/host", cfg, mcinfo );
        append_sos_header_obj ( "etc/sysconfig/network-scripts/ifcfg-", cfg, mcinfo );
        append_sos_header_obj ( "etc/crontab", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.deny", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.d/", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.hourly/", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.daily/", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.weekly/", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.monthly/", cfg, mcinfo );
        append_sos_header_obj ( "etc/", cfg, mcinfo );
        append_sos_header_obj ( "proc/meminfo", cfg, mcinfo );
        append_sos_header_obj ( "proc/zoneinfo", cfg, mcinfo );
        append_sos_header_obj ( "proc/buddyinfo", cfg, mcinfo );
        append_sos_header_obj ( "proc/slabinfo", cfg, mcinfo );
        append_sos_header_obj ( "proc/vmstat", cfg, mcinfo );
        append_sos_header_obj ( "proc/interrupts", cfg, mcinfo );
        append_sos_header_obj ( "var/log/dmesg", cfg, mcinfo );
        append_sos_header_obj ( "var/spool/cron/", cfg, mcinfo );
        append_sos_header_obj ( "var/log/messages", cfg, mcinfo );
        append_sos_header_obj ( "var/crash/", cfg, mcinfo );
    }
    if ( mcinfo == 0 ) 
    {
        /* general */
        append_sos_header_obj ( "==== general ====", cfg, mcinfo );
        append_sos_header_obj ( "date", cfg, mcinfo );
        append_sos_header_obj ( "lsb-release", cfg, mcinfo );
        append_sos_header_obj ( "uname", cfg, mcinfo );
        append_sos_header_obj ( "hostname", cfg, mcinfo );
        append_sos_header_obj ( "uptime", cfg, mcinfo );
        append_sos_header_obj ( "etc/nsswitch.conf", cfg, mcinfo );
        append_sos_header_obj ( "installed-rpms", cfg, mcinfo );
        append_sos_header_obj ( "proc/cpuinfo", cfg, mcinfo );
        append_sos_header_obj ( "root/anaconda-ks.cfg", cfg, mcinfo );
        append_sos_header_obj ( "dmidecode", cfg, mcinfo );
        append_sos_header_obj ( "etc/default/", cfg, mcinfo );
        append_sos_header_obj ( "etc/sysconfig/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/boot/", cfg, mcinfo );
        /* cpu */
        append_sos_header_obj ( "==== cpu ====", cfg, mcinfo );
        append_sos_header_obj ( "proc/interrupts", cfg, mcinfo );
        /* module */
        append_sos_header_obj ( "==== module ====", cfg, mcinfo );
        append_sos_header_obj ( "lsmod", cfg, mcinfo );
        append_sos_header_obj ( "etc/modprobe.d/", cfg, mcinfo );
        append_sos_header_obj ( "sys/module/", cfg, mcinfo );
        /* device */
        append_sos_header_obj ( "==== device ====", cfg, mcinfo );
        append_sos_header_obj ( "lspci", cfg, mcinfo );
        append_sos_header_obj ( "etc/udev/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/devicemapper/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/devices/udevadm_info_--export-db", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/ipmitool/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/scsi/lsscsi", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/usb/", cfg, mcinfo );
        /* file systems */
        append_sos_header_obj ( "==== file systems ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/lvm/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/lvm2/", cfg, mcinfo );
        /* disk usage */
        append_sos_header_obj ( "==== disk usage ====", cfg, mcinfo );
        append_sos_header_obj ( "df", cfg, mcinfo );
        append_sos_header_obj ( "vgdisplay", cfg, mcinfo );
        /* memory usage */
        append_sos_header_obj ( "==== memory usage ====", cfg, mcinfo );
        append_sos_header_obj ( "free", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/memory/", cfg, mcinfo );
        append_sos_header_obj ( "proc/meminfo", cfg, mcinfo );
        append_sos_header_obj ( "proc/zoneinfo", cfg, mcinfo );
        append_sos_header_obj ( "proc/buddyinfo", cfg, mcinfo );
        append_sos_header_obj ( "proc/slabinfo", cfg, mcinfo );
        append_sos_header_obj ( "proc/vmstat", cfg, mcinfo );
        /* networking */
        append_sos_header_obj ( "==== networking ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/host", cfg, mcinfo );
        append_sos_header_obj ( "ip_addr", cfg, mcinfo );
        append_sos_header_obj ( "route", cfg, mcinfo );
        append_sos_header_obj ( "etc/sysconfig/network-scripts/ifcfg-", cfg, mcinfo );
        append_sos_header_obj ( "etc/firewalld/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/firewalld/", cfg, mcinfo );
        append_sos_header_obj ( "proc/net/dev", cfg, mcinfo );
        append_sos_header_obj ( "proc/net/sockstat", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/networking/ethtool_-S", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/networking/ethtool_-i", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/networking/", cfg, mcinfo );
        append_sos_header_obj ( "etc/NetworkManager/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/networkmanager/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/wireless/", cfg, mcinfo );
        append_sos_header_obj ( "netstat", cfg, mcinfo );
        /* process */
        append_sos_header_obj ( "==== process ====", cfg, mcinfo );
        append_sos_header_obj ( "ps", cfg, mcinfo );
        /* virtualization */
        append_sos_header_obj ( "==== virtualization ====", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/virsh/", cfg, mcinfo );
        /* files */
        append_sos_header_obj ( "==== files ====", cfg, mcinfo );
        append_sos_header_obj ( "lsof", cfg, mcinfo );
        /* systemd */
        append_sos_header_obj ( "==== systemd ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/systemd/system/", cfg, mcinfo );
        append_sos_header_obj ( "etc/systemd/", cfg, mcinfo );
        append_sos_header_obj ( "usr/lib/systemd/", cfg, mcinfo );
        /* security */
        append_sos_header_obj ( "==== security ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/pam.d/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/pam/", cfg, mcinfo );
        append_sos_header_obj ( "var/log/secure", cfg, mcinfo );
        append_sos_header_obj ( "etc/audit/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/auditd/", cfg, mcinfo );
        append_sos_header_obj ( "var/log/audit/", cfg, mcinfo );
        append_sos_header_obj ( "etc/pki/", cfg, mcinfo );
        append_sos_header_obj ( "etc/selinux/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/selinux/", cfg, mcinfo );
        /* kernel */
        append_sos_header_obj ( "==== kernel ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/kdump.conf", cfg, mcinfo );
        append_sos_header_obj ( "etc/sysctl.conf", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/kernel/sysctl_-a", cfg, mcinfo );
        append_sos_header_obj ( "var/crash/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/abrt/", cfg, mcinfo );
        /* dnf/yum */
        append_sos_header_obj ( "==== dnf/yum ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/dnf/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/dnf/", cfg, mcinfo );
        append_sos_header_obj ( "etc/yum.conf", cfg, mcinfo );
        append_sos_header_obj ( "etc/yum.repos.d/", cfg, mcinfo );
        append_sos_header_obj ( "etc/yum/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/yum/", cfg, mcinfo );
        /* login */
        append_sos_header_obj ( "==== login ====", cfg, mcinfo );
        append_sos_header_obj ( "last", cfg, mcinfo );
        /* cron */
        append_sos_header_obj ( "==== cron ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/anacrontab", cfg, mcinfo );
        append_sos_header_obj ( "etc/crontab", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.deny", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.d/", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.hourly/", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.daily/", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.weekly/", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.monthly/", cfg, mcinfo );
        append_sos_header_obj ( "var/spool/cron/", cfg, mcinfo );
        /* logrotate */
        append_sos_header_obj ( "==== logrotate ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/logrotate.conf", cfg, mcinfo );
        append_sos_header_obj ( "etc/logrotate.d/", cfg, mcinfo );
        /* logs and journals */
        append_sos_header_obj ( "==== logs and journals ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/rsyslog.conf", cfg, mcinfo );
        append_sos_header_obj ( "var/log/dmesg", cfg, mcinfo );
        append_sos_header_obj ( "var/log/messages", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/logs/journalctl_--no-pager", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/sar/", cfg, mcinfo );
        /* httpd */
        append_sos_header_obj ( "==== httpd ====", cfg, mcinfo );
        append_sos_header_obj ( "etc/httpd/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/apache/", cfg, mcinfo );
        /* others ( default items is 'skip' ) */
        append_sos_header_obj ( "==== others ( default item is 'skip' ) ====", cfg, mcinfo );
        append_sos_header_obj ( "lib/", cfg, mcinfo );
        append_sos_header_obj ( "etc/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/", cfg, mcinfo );
        append_sos_header_obj ( "dev/", cfg, mcinfo );
        append_sos_header_obj ( "usr/", cfg, mcinfo );
    }
    append_sos_header_obj ( "var/", cfg, mcinfo );
    append_sos_header_obj ( "proc/", cfg, mcinfo );
    append_list ( &sos_header_obj, "--------" );
}

void append_sos_header_obj ( const char *member, struct sosreport_analyzer_config *cfg, int mcinfo )
{
    char str_tmp [ MAX_FILE_NAME_LENGTH ]; 
    memset ( str_tmp, '\0', MAX_FILE_NAME_LENGTH ); 
    snprintf (str_tmp, strlen ( member ) + 2, "%s=", member );

    /* common members for both mcinfo and sosreport */
    if ( strcmp ( member, "etc/host" ) == 0 )
        strcat ( str_tmp, cfg->etc_host.member );
    else if ( strcmp ( member, "etc/crontab" ) == 0 )
        strcat ( str_tmp, cfg->etc_crontab.member );
    else if ( strcmp ( member, "etc/cron.deny" ) == 0 )
        strcat ( str_tmp, cfg->etc_cron_deny.member );
    else if ( strcmp ( member, "etc/cron.d/" ) == 0 )
        strcat ( str_tmp, cfg->etc_cron_d_.member );
    else if ( strcmp ( member, "etc/cron.hourly/" ) == 0 )
        strcat ( str_tmp, cfg->etc_cron_hourly_.member );
    else if ( strcmp ( member, "etc/cron.daily/" ) == 0 )
        strcat ( str_tmp, cfg->etc_cron_daily_.member );
    else if ( strcmp ( member, "etc/cron.weekly/" ) == 0 )
        strcat ( str_tmp, cfg->etc_cron_weekly_.member );
    else if ( strcmp ( member, "etc/cron.monthly/" ) == 0 )
        strcat ( str_tmp, cfg->etc_cron_monthly_.member );
    else if ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 )
        strcat ( str_tmp, cfg->etc_sysconfig_network_scripts_ifcfg_.member );
    else if ( strcmp ( member, "proc/cpuinfo" ) == 0 )
        strcat ( str_tmp, cfg->proc_cpuinfo.member );
    else if ( strcmp ( member, "proc/meminfo" ) == 0 )
        strcat ( str_tmp, cfg->proc_meminfo.member );
    else if ( strcmp ( member, "proc/zoneinfo" ) == 0 )
        strcat ( str_tmp, cfg->proc_zoneinfo.member );
    else if ( strcmp ( member, "proc/buddyinfo" ) == 0 )
        strcat ( str_tmp, cfg->proc_buddyinfo.member );
    else if ( strcmp ( member, "proc/slabinfo" ) == 0 )
        strcat ( str_tmp, cfg->proc_slabinfo.member );
    else if ( strcmp ( member, "proc/vmstat" ) == 0 )
        strcat ( str_tmp, cfg->proc_vmstat.member );
    else if ( strcmp ( member, "proc/interrupts" ) == 0 )
        strcat ( str_tmp, cfg->proc_interrupts.member );
    else if ( strcmp ( member, "var/log/dmesg" ) == 0 )
        strcat ( str_tmp, cfg->var_log_dmesg.member );
    else if ( strcmp ( member, "var/spool/cron/" ) == 0 )
        strcat ( str_tmp, cfg->var_spool_cron_.member );
    else if ( strcmp ( member, "var/log/messages" ) == 0 )
        strcat ( str_tmp, cfg->var_log_messages.member );
    else if ( strcmp ( member, "var/crash/" ) == 0 )
        strcat ( str_tmp, cfg->var_crash_.member );
    else if ( strcmp ( member, "etc/" ) == 0 )
        strcat ( str_tmp, cfg->etc_.member );
    else if ( strcmp ( member, "var/" ) == 0 )
        strcat ( str_tmp, cfg->var_.member );
    else if ( strcmp ( member, "proc/" ) == 0 )
        strcat ( str_tmp, cfg->proc_.member );

    /* mcinfo only */
    if ( mcinfo == 1 )
    {
        if ( strcmp ( member, "boot/grub/" ) == 0 )
            strcat ( str_tmp, cfg->mcinfo_boot_grub_.member );
        else if ( strcmp ( member, "cmdlog/" ) == 0 )
            strcat ( str_tmp, cfg->mcinfo_cmdlog_.member );
    }
    /* sosreport only */
    else if ( mcinfo == 0 )
    {
        if ( strcmp ( member, "date" ) == 0 )
            strcat ( str_tmp, cfg->date.member );
        else if ( strcmp ( member, "df" ) == 0 )
            strcat ( str_tmp, cfg->df.member );
        else if ( strcmp ( member, "dmidecode" ) == 0 )
            strcat ( str_tmp, cfg->dmidecode.member );
        else if ( strcmp ( member, "free" ) == 0 )
            strcat ( str_tmp, cfg->free.member );
        else if ( strcmp ( member, "hostname" ) == 0 )
            strcat ( str_tmp, cfg->hostname.member );
        else if ( strcmp ( member, "installed-rpms" ) == 0 )
            strcat ( str_tmp, cfg->installed_rpms.member );
        else if ( strcmp ( member, "ip_addr" ) == 0 )
            strcat ( str_tmp, cfg->ip_addr.member );
        else if ( strcmp ( member, "last" ) == 0 )
            strcat ( str_tmp, cfg->last.member );
        else if ( strcmp ( member, "lsb-release" ) == 0 )
            strcat ( str_tmp, cfg->lsb_release.member );
        else if ( strcmp ( member, "lsmod" ) == 0 )
            strcat ( str_tmp, cfg->lsmod.member );
        else if ( strcmp ( member, "lsof" ) == 0 )
            strcat ( str_tmp, cfg->lsof.member );
        else if ( strcmp ( member, "lspci" ) == 0 )
            strcat ( str_tmp, cfg->lspci.member );
        else if ( strcmp ( member, "route" ) == 0 )
            strcat ( str_tmp, cfg->route.member );
        else if ( strcmp ( member, "netstat" ) == 0 )
            strcat ( str_tmp, cfg->netstat.member );
        else if ( strcmp ( member, "ps" ) == 0 )
            strcat ( str_tmp, cfg->ps.member );
        else if ( strcmp ( member, "uname" ) == 0 )
            strcat ( str_tmp, cfg->uname.member );
        else if ( strcmp ( member, "uptime" ) == 0 )
            strcat ( str_tmp, cfg->uptime.member );
        else if ( strcmp ( member, "vgdisplay" ) == 0 )
            strcat ( str_tmp, cfg->vgdisplay.member );
        else if ( strcmp ( member, "etc/NetworkManager/" ) == 0 )
            strcat ( str_tmp, cfg->etc_NetworkManager_.member );
        else if ( strcmp ( member, "etc/anacrontab" ) == 0 )
            strcat ( str_tmp, cfg->etc_anacrontab.member );
        else if ( strcmp ( member, "etc/audit/" ) == 0 )
            strcat ( str_tmp, cfg->etc_audit_.member );
        else if ( strcmp ( member, "etc/default/" ) == 0 )
            strcat ( str_tmp, cfg->etc_default_.member );
        else if ( strcmp ( member, "etc/dnf/" ) == 0 )
            strcat ( str_tmp, cfg->etc_dnf_.member );
        else if ( strcmp ( member, "etc/firewalld/" ) == 0 )
            strcat ( str_tmp, cfg->etc_firewalld_.member );
        else if ( strcmp ( member, "etc/httpd/" ) == 0 )
            strcat ( str_tmp, cfg->etc_httpd_.member );
        else if ( strcmp ( member, "etc/kdump.conf" ) == 0 )
            strcat ( str_tmp, cfg->etc_kdump_conf.member );
        else if ( strcmp ( member, "etc/logrotate.conf" ) == 0 )
            strcat ( str_tmp, cfg->etc_logrotate_conf.member );
        else if ( strcmp ( member, "etc/logrotate.d/" ) == 0 )
            strcat ( str_tmp, cfg->etc_logrotate_d_.member );
        else if ( strcmp ( member, "etc/lvm/" ) == 0 )
            strcat ( str_tmp, cfg->etc_lvm_.member );
        else if ( strcmp ( member, "etc/pki/" ) == 0 )
            strcat ( str_tmp, cfg->etc_pki_.member );
        else if ( strcmp ( member, "etc/pam.d/" ) == 0 )
            strcat ( str_tmp, cfg->etc_pam_d_.member );
        else if ( strcmp ( member, "etc/modprobe.d/" ) == 0 )
            strcat ( str_tmp, cfg->etc_modprobe_d_.member );
        else if ( strcmp ( member, "etc/nsswitch.conf" ) == 0 )
            strcat ( str_tmp, cfg->etc_nsswitch_conf.member );
        else if ( strcmp ( member, "etc/rsyslog.conf" ) == 0 )
            strcat ( str_tmp, cfg->etc_rsyslog_conf.member );
        else if ( strcmp ( member, "etc/selinux/" ) == 0 )
            strcat ( str_tmp, cfg->etc_selinux_.member );
        else if ( strcmp ( member, "etc/sysconfig/" ) == 0 )
            strcat ( str_tmp, cfg->etc_sysconfig_.member );
        else if ( strcmp ( member, "etc/sysctl.conf" ) == 0 )
            strcat ( str_tmp, cfg->etc_sysctl_conf.member );
        else if ( strcmp ( member, "etc/systemd/" ) == 0 )
            strcat ( str_tmp, cfg->etc_systemd_.member );
        else if ( strcmp ( member, "etc/systemd/system/" ) == 0 )
            strcat ( str_tmp, cfg->etc_systemd_system_.member );
        else if ( strcmp ( member, "etc/udev/" ) == 0 )
            strcat ( str_tmp, cfg->etc_udev_.member );
        else if ( strcmp ( member, "etc/yum.conf" ) == 0 )
            strcat ( str_tmp, cfg->etc_yum_conf.member );
        else if ( strcmp ( member, "etc/yum/" ) == 0 )
            strcat ( str_tmp, cfg->etc_yum_.member );
        else if ( strcmp ( member, "etc/yum.repos.d/" ) == 0 )
            strcat ( str_tmp, cfg->etc_yum_repos_d_.member );
        else if ( strcmp ( member, "proc/net/dev" ) == 0 )
            strcat ( str_tmp, cfg->proc_net_dev.member );
        else if ( strcmp ( member, "proc/net/sockstat" ) == 0 )
            strcat ( str_tmp, cfg->proc_net_sockstat.member );
        else if ( strcmp ( member, "root/anaconda-ks.cfg" ) == 0 )
            strcat ( str_tmp, cfg->root_anaconda_ks_cfg.member );
        else if ( strcmp ( member, "sos_commands/abrt/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_abrt_.member );
        else if ( strcmp ( member, "sos_commands/apache/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_apache_.member );
        else if ( strcmp ( member, "sos_commands/auditd/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_auditd_.member );
        else if ( strcmp ( member, "sos_commands/boot/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_boot_.member );
        else if ( strcmp ( member, "sos_commands/devicemapper/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_devicemapper_.member );
        else if ( strcmp ( member, "sos_commands/devices/udevadm_info_--export-db" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_devices_udevadm_info___export_db.member );
        else if ( strcmp ( member, "sos_commands/dnf/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_dnf_.member );
        else if ( strcmp ( member, "sos_commands/firewalld/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_firewalld_.member );
        else if ( strcmp ( member, "sos_commands/ipmitool/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_ipmitool_.member );
        else if ( strcmp ( member, "sos_commands/kernel/sysctl_-a" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_kernel_sysctl__a.member );
        else if ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_logs_journalctl___no_pager.member );
        else if ( strcmp ( member, "sos_commands/lvm2/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_lvm2_.member );
        else if ( strcmp ( member, "sos_commands/memory/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_memory_.member );
        else if ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_networking_ethtool__S.member );
        else if ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_networking_ethtool__i.member );
        else if ( strcmp ( member, "sos_commands/networking/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_networking_.member );
        else if ( strcmp ( member, "sos_commands/networkmanager/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_networkmanager_.member );
        else if ( strcmp ( member, "sos_commands/pam/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_pam_.member );
        else if ( strcmp ( member, "sos_commands/sar/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_sar_.member );
        else if ( strcmp ( member, "sos_commands/scsi/lsscsi" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_scsi_lsscsi.member );
        else if ( strcmp ( member, "sos_commands/selinux/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_selinux_.member );
        else if ( strcmp ( member, "sos_commands/usb/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_usb_.member );
        else if ( strcmp ( member, "sos_commands/virsh/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_virsh_.member );
        else if ( strcmp ( member, "sos_commands/yum/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_yum_.member );
        else if ( strcmp ( member, "sos_commands/wireless/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_wireless_.member );
        else if ( strcmp ( member, "sos_commands/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_.member );
        else if ( strcmp ( member, "sys/module/" ) == 0 )
            strcat ( str_tmp, cfg->sys_module_.member );
        else if ( strcmp ( member, "usr/lib/systemd/" ) == 0 )
            strcat ( str_tmp, cfg->usr_lib_systemd_.member );
        else if ( strcmp ( member, "var/log/secure" ) == 0 )
            strcat ( str_tmp, cfg->var_log_secure.member );
        else if ( strcmp ( member, "var/log/audit/" ) == 0 )
            strcat ( str_tmp, cfg->var_log_audit_.member );
        else if ( strcmp ( member, "dev/" ) == 0 )
            strcat ( str_tmp, cfg->dev_.member );
        else if ( strcmp ( member, "lib/" ) == 0 )
            strcat ( str_tmp, cfg->lib_.member );
        else if ( strcmp ( member, "usr/" ) == 0 )
            strcat ( str_tmp, cfg->usr_.member );
    }
    append_list ( &sos_header_obj, str_tmp );
}

void cfg_init ( const char *file_name, int mcinfo )
{
    /* check if we were called before */
    if ( sosreport_analyzer_cfg != NULL )
        printf("cfg_init() may only be called once.\n");
    /* allocate the memory (this memory is not freed anywhere, it's ok, outside this socpe, it's NULL) */
    sosreport_analyzer_cfg = (struct sosreport_analyzer_config * ) malloc ( sizeof ( struct sosreport_analyzer_config ) );
    if ( sosreport_analyzer_cfg == NULL )
        printf("malloc() failed to allocate memory.\n");
    /* clear configuration */
    cfg_defaults ( sosreport_analyzer_cfg );
    /* read configfile */
    cfg_read ( file_name, sosreport_analyzer_cfg, mcinfo );
}

void cfg_clear ( )
{
    /* printf("freeing the config pointer, because we have already read stuff -- sosreport_analyzer_cfg:%p\n",sosreport_analyzer_cfg); */
    free ( sosreport_analyzer_cfg );
    sosreport_analyzer_cfg = NULL;
}
