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
            printf("skip file '%s'.\n",keyword);
    else
    {
        /* common stuff for both mcinfo and sosreport */
        if ( strcmp ( keyword, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 )
            strncpy ( cfg->etc_sysconfig_network_scripts_ifcfg_.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "var/log/dmesg" ) == 0 )
            strncpy ( cfg->var_log_dmesg.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "var/log/messages" ) == 0 )
            strncpy ( cfg->var_log_messages.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/meminfo" ) == 0 )
            strncpy ( cfg->proc_meminfo.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/interrupts" ) == 0 )
            strncpy ( cfg->proc_interrupts.member, line, MAX_LINE_LENGTH - 1 );
        else if ( strcmp ( keyword, "proc/" ) == 0 )
            strncpy ( cfg->proc_.member, line, MAX_LINE_LENGTH - 1 );

        if ( mcinfo == 1 )
        {
          if ( strcmp ( keyword, "boot/grub/" ) == 0 )
            strncpy ( cfg->mcinfo_boot_grub_.member, line, MAX_LINE_LENGTH - 1 );
          else if ( strcmp ( keyword, "cmdlog/" ) == 0 )
            strncpy ( cfg->mcinfo_cmdlog_.member, line, MAX_LINE_LENGTH - 1 );
        }
        else if ( mcinfo == 0 )
        {
            if ( strcmp ( keyword, "date" ) == 0 )
                strncpy ( cfg->date.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "lsb-release" ) == 0 )
                strncpy ( cfg->lsb_release.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "uname" ) == 0 )
                strncpy ( cfg->uname.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "hostname" ) == 0 )
                strncpy ( cfg->hostname.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "uptime" ) == 0 )
                strncpy ( cfg->uptime.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "root/anaconda-ks.cfg" ) == 0 )
                strncpy ( cfg->root_anaconda_ks_cfg.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "dmidecode" ) == 0 )
                strncpy ( cfg->dmidecode.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "lsmod" ) == 0 )
                strncpy ( cfg->lsmod.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "lspci" ) == 0 )
                strncpy ( cfg->lspci.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/devices/udevadm_info_--export-db" ) == 0 )
                strncpy ( cfg->sos_commands_devices_udevadm_info___export_db.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/scsi/lsscsi" ) == 0 )
                strncpy ( cfg->sos_commands_scsi_lsscsi.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "installed-rpms" ) == 0 )
                strncpy ( cfg->installed_rpms.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "df" ) == 0 )
                strncpy ( cfg->df.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "vgdisplay" ) == 0 )
                strncpy ( cfg->vgdisplay.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "free" ) == 0 )
                strncpy ( cfg->free.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "ip_addr" ) == 0 )
                strncpy ( cfg->ip_addr.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "route" ) == 0 )
                strncpy ( cfg->route.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "last" ) == 0 )
                strncpy ( cfg->last.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "ps" ) == 0 )
                strncpy ( cfg->ps.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "lsof" ) == 0 )
                strncpy ( cfg->lsof.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "netstat" ) == 0 )
                strncpy ( cfg->netstat.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/kdump.conf" ) == 0 )
                strncpy ( cfg->etc_kdump_conf.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/sysctl.conf" ) == 0 )
                strncpy ( cfg->etc_sysctl_conf.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "proc/net/dev" ) == 0 )
                strncpy ( cfg->proc_net_dev.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "proc/net/sockstat" ) == 0 )
                strncpy ( cfg->proc_net_sockstat.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/logrotate.conf" ) == 0 )
                strncpy ( cfg->etc_logrotate_conf.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/pki/" ) == 0 )
                strncpy ( cfg->etc_pki_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/cron.d/" ) == 0 )
                strncpy ( cfg->etc_cron_d_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "var/log/secure" ) == 0 )
                strncpy ( cfg->var_log_secure.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "var/log/audit/" ) == 0 )
                strncpy ( cfg->var_log_audit_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/kernel/sysctl_-a" ) == 0 )
                strncpy ( cfg->sos_commands_kernel_sysctl__a.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/logs/journalctl_--no-pager" ) == 0 )
                strncpy ( cfg->sos_commands_logs_journalctl___no_pager.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/networking/ethtool_-S" ) == 0 )
                strncpy ( cfg->sos_commands_networking_ethtool__S.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/networking/ethtool_-i" ) == 0 )
                strncpy ( cfg->sos_commands_networking_ethtool__i.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "sos_commands/boot/" ) == 0 )
                strncpy ( cfg->sos_commands_boot_.member, line, MAX_LINE_LENGTH - 1 );
            else if ( strcmp ( keyword, "etc/httpd/" ) == 0 )
                strncpy ( cfg->etc_httpd_.member, line, MAX_LINE_LENGTH - 1 );
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
        append_sos_header_obj ( "boot/grub/", cfg, mcinfo );
        append_sos_header_obj ( "cmdlog/", cfg, mcinfo );
    }
    if ( mcinfo == 0 ) 
    {
        append_sos_header_obj ( "date", cfg, mcinfo );
        append_sos_header_obj ( "lsb-release", cfg, mcinfo );
        append_sos_header_obj ( "uname", cfg, mcinfo );
        append_sos_header_obj ( "hostname", cfg, mcinfo );
        append_sos_header_obj ( "uptime", cfg, mcinfo );
        append_sos_header_obj ( "root/anaconda-ks.cfg", cfg, mcinfo );
        append_sos_header_obj ( "dmidecode", cfg, mcinfo );
        append_sos_header_obj ( "lsmod", cfg, mcinfo );
        append_sos_header_obj ( "lspci", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/devices/udevadm_info_--export-db", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/scsi/lsscsi", cfg, mcinfo );
        append_sos_header_obj ( "installed-rpms", cfg, mcinfo );
        append_sos_header_obj ( "df", cfg, mcinfo );
        append_sos_header_obj ( "vgdisplay", cfg, mcinfo );
        append_sos_header_obj ( "free", cfg, mcinfo );
        append_sos_header_obj ( "ip_addr", cfg, mcinfo );
        append_sos_header_obj ( "route", cfg, mcinfo );
        append_sos_header_obj ( "last", cfg, mcinfo );
        append_sos_header_obj ( "ps", cfg, mcinfo );
        append_sos_header_obj ( "lsof", cfg, mcinfo );
        append_sos_header_obj ( "netstat", cfg, mcinfo );
        append_sos_header_obj ( "etc/kdump.conf", cfg, mcinfo );
        append_sos_header_obj ( "etc/sysctl.conf", cfg, mcinfo );
    }
    append_sos_header_obj ( "etc/sysconfig/network-scripts/ifcfg-", cfg, mcinfo );
    append_sos_header_obj ( "proc/meminfo", cfg, mcinfo );
    append_sos_header_obj ( "proc/interrupts", cfg, mcinfo );
    if ( mcinfo == 0 ) 
    {
        append_sos_header_obj ( "sos_commands/boot/", cfg, mcinfo );
        append_sos_header_obj ( "proc/net/dev", cfg, mcinfo );
        append_sos_header_obj ( "proc/net/sockstat", cfg, mcinfo );
        append_sos_header_obj ( "etc/logrotate.conf", cfg, mcinfo );
        append_sos_header_obj ( "etc/pki/", cfg, mcinfo );
        append_sos_header_obj ( "etc/cron.d/", cfg, mcinfo );
    }
    append_sos_header_obj ( "var/log/dmesg", cfg, mcinfo );
    append_sos_header_obj ( "var/log/messages", cfg, mcinfo );
    if ( mcinfo == 0 ) 
    {
        append_sos_header_obj ( "var/log/secure", cfg, mcinfo );
        append_sos_header_obj ( "var/log/audit/", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/kernel/sysctl_-a", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/logs/journalctl_--no-pager", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/networking/ethtool_-S", cfg, mcinfo );
        append_sos_header_obj ( "sos_commands/networking/ethtool_-i", cfg, mcinfo );
        append_sos_header_obj ( "etc/httpd/", cfg, mcinfo );
    }
    append_sos_header_obj ( "proc/", cfg, mcinfo );
    append_list ( &sos_header_obj, "--------" );
}

void append_sos_header_obj ( const char *member, struct sosreport_analyzer_config *cfg, int mcinfo )
{
    char str_tmp [ MAX_FILE_NAME_LENGTH ]; 
    memset ( str_tmp, '\0', MAX_FILE_NAME_LENGTH ); 
    snprintf (str_tmp, strlen ( member ) + 2, "%s=", member );

    /* these members are those included in sosreport and mcinfo */
    if ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 )
        strcat ( str_tmp, cfg->etc_sysconfig_network_scripts_ifcfg_.member );
    else if ( strcmp ( member, "proc/meminfo" ) == 0 )
        strcat ( str_tmp, cfg->proc_meminfo.member );
    else if ( strcmp ( member, "proc/interrupts" ) == 0 )
        strcat ( str_tmp, cfg->proc_interrupts.member );
    else if ( strcmp ( member, "var/log/dmesg" ) == 0 )
        strcat ( str_tmp, cfg->var_log_dmesg.member );
    else if ( strcmp ( member, "var/log/messages" ) == 0 )
        strcat ( str_tmp, cfg->var_log_messages.member );
    else if ( strcmp ( member, "proc/" ) == 0 )
        strcat ( str_tmp, cfg->proc_.member );

    /* mcinfo only and sosreport only ones */
    if ( mcinfo == 1 )
    {
        if ( strcmp ( member, "boot/grub/" ) == 0 )
            strcat ( str_tmp, cfg->mcinfo_boot_grub_.member );
        else if ( strcmp ( member, "cmdlog/" ) == 0 )
            strcat ( str_tmp, cfg->mcinfo_cmdlog_.member );
    }
    else if ( mcinfo == 0 )
    {
        if ( strcmp ( member, "date" ) == 0 )
            strcat ( str_tmp, cfg->date.member );
        else if ( strcmp ( member, "lsb-release" ) == 0 )
            strcat ( str_tmp, cfg->lsb_release.member );
        else if ( strcmp ( member, "uname" ) == 0 )
            strcat ( str_tmp, cfg->uname.member );
        else if ( strcmp ( member, "hostname" ) == 0 )
            strcat ( str_tmp, cfg->hostname.member );
        else if ( strcmp ( member, "uptime" ) == 0 )
            strcat ( str_tmp, cfg->uptime.member );
        else if ( strcmp ( member, "root/anaconda-ks.cfg" ) == 0 )
            strcat ( str_tmp, cfg->root_anaconda_ks_cfg.member );
        else if ( strcmp ( member, "dmidecode" ) == 0 )
            strcat ( str_tmp, cfg->dmidecode.member );
        else if ( strcmp ( member, "lsmod" ) == 0 )
            strcat ( str_tmp, cfg->lsmod.member );
        else if ( strcmp ( member, "lspci" ) == 0 )
            strcat ( str_tmp, cfg->lspci.member );
        else if ( strcmp ( member, "sos_commands/devices/udevadm_info_--export-db" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_devices_udevadm_info___export_db.member );
        else if ( strcmp ( member, "sos_commands/scsi/lsscsi" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_scsi_lsscsi.member );
        else if ( strcmp ( member, "installed-rpms" ) == 0 )
            strcat ( str_tmp, cfg->installed_rpms.member );
        else if ( strcmp ( member, "df" ) == 0 )
            strcat ( str_tmp, cfg->df.member );
        else if ( strcmp ( member, "vgdisplay" ) == 0 )
            strcat ( str_tmp, cfg->vgdisplay.member );
        else if ( strcmp ( member, "free" ) == 0 )
            strcat ( str_tmp, cfg->free.member );
        else if ( strcmp ( member, "ip_addr" ) == 0 )
            strcat ( str_tmp, cfg->ip_addr.member );
        else if ( strcmp ( member, "route" ) == 0 )
            strcat ( str_tmp, cfg->route.member );
        else if ( strcmp ( member, "last" ) == 0 )
            strcat ( str_tmp, cfg->last.member );
        else if ( strcmp ( member, "ps" ) == 0 )
            strcat ( str_tmp, cfg->ps.member );
        else if ( strcmp ( member, "lsof" ) == 0 )
            strcat ( str_tmp, cfg->lsof.member );
        else if ( strcmp ( member, "netstat" ) == 0 )
            strcat ( str_tmp, cfg->netstat.member );
        else if ( strcmp ( member, "etc/kdump.conf" ) == 0 )
            strcat ( str_tmp, cfg->etc_kdump_conf.member );
        else if ( strcmp ( member, "etc/sysctl.conf" ) == 0 )
            strcat ( str_tmp, cfg->etc_sysctl_conf.member );
        else if ( strcmp ( member, "proc/net/dev" ) == 0 )
            strcat ( str_tmp, cfg->proc_net_dev.member );
        else if ( strcmp ( member, "proc/net/sockstat" ) == 0 )
            strcat ( str_tmp, cfg->proc_net_sockstat.member );
        else if ( strcmp ( member, "etc/logrotate.conf" ) == 0 )
            strcat ( str_tmp, cfg->etc_logrotate_conf.member );
        else if ( strcmp ( member, "etc/pki/" ) == 0 )
            strcat ( str_tmp, cfg->etc_pki_.member );
        else if ( strcmp ( member, "etc/cron.d/" ) == 0 )
            strcat ( str_tmp, cfg->etc_cron_d_.member );
        else if ( strcmp ( member, "var/log/secure" ) == 0 )
            strcat ( str_tmp, cfg->var_log_secure.member );
        else if ( strcmp ( member, "var/log/audit/" ) == 0 )
            strcat ( str_tmp, cfg->var_log_audit_.member );
        else if ( strcmp ( member, "sos_commands/kernel/sysctl_-a" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_kernel_sysctl__a.member );
        else if ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_logs_journalctl___no_pager.member );
        else if ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_networking_ethtool__S.member );
        else if ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_networking_ethtool__i.member );
        else if ( strcmp ( member, "sos_commands/boot/" ) == 0 )
            strcat ( str_tmp, cfg->sos_commands_boot_.member );
        else if ( strcmp ( member, "etc/httpd/" ) == 0 )
            strcat ( str_tmp, cfg->etc_httpd_.member );
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
