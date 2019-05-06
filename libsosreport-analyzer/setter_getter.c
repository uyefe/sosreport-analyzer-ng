/*
 *  setter_getter.c - setter and getter functions 
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

#include <string.h>
#include "setter_getter.h" 

int init_item_numbers_of_member ( void )
{
    sosreport_analyzer_cfg->df.item_num = 0;
    sosreport_analyzer_cfg->date.item_num = 0;
    sosreport_analyzer_cfg->dmidecode.item_num = 0;
    sosreport_analyzer_cfg->free.item_num = 0;
    sosreport_analyzer_cfg->hostname.item_num = 0;
    sosreport_analyzer_cfg->installed_rpms.item_num = 0;
    sosreport_analyzer_cfg->ip_addr.item_num = 0;
    sosreport_analyzer_cfg->last.item_num = 0;
    sosreport_analyzer_cfg->lsb_release.item_num = 0;
    sosreport_analyzer_cfg->lsmod.item_num = 0;
    sosreport_analyzer_cfg->lsof.item_num = 0;
    sosreport_analyzer_cfg->lspci.item_num = 0;
    sosreport_analyzer_cfg->ps.item_num = 0;
    sosreport_analyzer_cfg->route.item_num = 0;
    sosreport_analyzer_cfg->netstat.item_num = 0;
    sosreport_analyzer_cfg->uname.item_num = 0;
    sosreport_analyzer_cfg->uptime.item_num = 0;
    sosreport_analyzer_cfg->vgdisplay.item_num = 0;
    sosreport_analyzer_cfg->mcinfo_boot_grub_.item_num = 0;
    sosreport_analyzer_cfg->mcinfo_cmdlog_.item_num = 0;
    sosreport_analyzer_cfg->dev_.item_num = 0;
    sosreport_analyzer_cfg->etc_.item_num = 0;
    sosreport_analyzer_cfg->etc_NetworkManager_.item_num = 0;
    sosreport_analyzer_cfg->etc_audit_.item_num = 0;
    sosreport_analyzer_cfg->etc_anacrontab.item_num = 0;
    sosreport_analyzer_cfg->etc_crontab.item_num = 0;
    sosreport_analyzer_cfg->etc_cron_deny.item_num = 0;
    sosreport_analyzer_cfg->etc_cron_d_.item_num = 0;
    sosreport_analyzer_cfg->etc_cron_hourly_.item_num = 0;
    sosreport_analyzer_cfg->etc_cron_daily_.item_num = 0;
    sosreport_analyzer_cfg->etc_cron_weekly_.item_num = 0;
    sosreport_analyzer_cfg->etc_cron_monthly_.item_num = 0;
    sosreport_analyzer_cfg->etc_default_.item_num = 0;
    sosreport_analyzer_cfg->etc_dnf_.item_num = 0;
    sosreport_analyzer_cfg->etc_firewalld_.item_num = 0;
    sosreport_analyzer_cfg->etc_host.item_num = 0;
    sosreport_analyzer_cfg->etc_httpd_.item_num = 0;
    sosreport_analyzer_cfg->etc_kdump_conf.item_num = 0;
    sosreport_analyzer_cfg->etc_logrotate_conf.item_num = 0;
    sosreport_analyzer_cfg->etc_logrotate_d_.item_num = 0;
    sosreport_analyzer_cfg->etc_lvm_.item_num = 0;
    sosreport_analyzer_cfg->etc_modprobe_d_.item_num = 0;
    sosreport_analyzer_cfg->etc_nsswitch_conf.item_num = 0;
    sosreport_analyzer_cfg->etc_pam_d_.item_num = 0;
    sosreport_analyzer_cfg->etc_pki_.item_num = 0;
    sosreport_analyzer_cfg->etc_rsyslog_conf.item_num = 0;
    sosreport_analyzer_cfg->etc_selinux_.item_num = 0;
    sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.item_num = 0;
    sosreport_analyzer_cfg->etc_sysconfig_.item_num = 0;
    sosreport_analyzer_cfg->etc_sysctl_conf.item_num = 0;
    sosreport_analyzer_cfg->etc_systemd_system_.item_num = 0;
    sosreport_analyzer_cfg->etc_systemd_.item_num = 0;
    sosreport_analyzer_cfg->etc_udev_.item_num = 0;
    sosreport_analyzer_cfg->etc_yum_conf.item_num = 0;
    sosreport_analyzer_cfg->etc_yum_repos_d_.item_num = 0;
    sosreport_analyzer_cfg->etc_yum_.item_num = 0;
    sosreport_analyzer_cfg->lib_.item_num = 0;
    sosreport_analyzer_cfg->proc_.item_num = 0;
    sosreport_analyzer_cfg->proc_cpuinfo.item_num = 0;
    sosreport_analyzer_cfg->proc_interrupts.item_num = 0;
    sosreport_analyzer_cfg->proc_meminfo.item_num = 0;
    sosreport_analyzer_cfg->proc_net_dev.item_num = 0;
    sosreport_analyzer_cfg->proc_net_sockstat.item_num = 0;
    sosreport_analyzer_cfg->root_anaconda_ks_cfg.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_abrt_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_apache_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_auditd_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_boot_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_devicemapper_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_dnf_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_firewalld_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_ipmitool_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_lvm2_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_memory_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_networking_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_pam_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_sar_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_selinux_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_usb_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_virsh_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_yum_.item_num = 0;
    sosreport_analyzer_cfg->sys_module_.item_num = 0;
    sosreport_analyzer_cfg->usr_.item_num = 0;
    sosreport_analyzer_cfg->usr_lib_systemd_.item_num = 0;
    sosreport_analyzer_cfg->var_.item_num = 0;
    sosreport_analyzer_cfg->var_crash_.item_num = 0;
    sosreport_analyzer_cfg->var_log_audit_.item_num = 0;
    sosreport_analyzer_cfg->var_log_dmesg.item_num = 0;
    sosreport_analyzer_cfg->var_log_messages.item_num = 0;
    sosreport_analyzer_cfg->var_log_secure.item_num = 0;
    sosreport_analyzer_cfg->var_spool_cron_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_networkmanager_.item_num = 0;
    sosreport_analyzer_cfg->sos_commands_wireless_.item_num = 0;

    return ( 0 );
}

int get_item_numbers_of_member ( const char *member )
{
    if ( strcmp ( "df", member ) == 0 )
        return sosreport_analyzer_cfg->df.item_num;
    else if ( strcmp ( "date", member ) == 0 )
        return sosreport_analyzer_cfg->date.item_num;
    else if ( strcmp ( "dmidecode", member ) == 0 )
        return sosreport_analyzer_cfg->dmidecode.item_num;
    else if ( strcmp ( "free", member ) == 0 )
        return sosreport_analyzer_cfg->free.item_num;
    else if ( strcmp ( "hostname", member ) == 0 )
        return sosreport_analyzer_cfg->hostname.item_num;
    else if ( strcmp ( "installed-rpms", member ) == 0 )
        return sosreport_analyzer_cfg->installed_rpms.item_num;
    else if ( strcmp ( "ip_addr", member ) == 0 )
        return sosreport_analyzer_cfg->ip_addr.item_num;
    else if ( strcmp ( "last", member ) == 0 )
        return sosreport_analyzer_cfg->last.item_num;
    else if ( strcmp ( "lsb-release", member ) == 0 )
        return sosreport_analyzer_cfg->lsb_release.item_num;
    else if ( strcmp ( "lsmod", member ) == 0 )
        return sosreport_analyzer_cfg->lsmod.item_num;
    else if ( strcmp ( "lsof", member ) == 0 )
        return sosreport_analyzer_cfg->lsof.item_num;
    else if ( strcmp ( "lspci", member ) == 0 )
        return sosreport_analyzer_cfg->lspci.item_num;
    else if ( strcmp ( "ps", member ) == 0 )
        return sosreport_analyzer_cfg->ps.item_num;
    else if ( strcmp ( "route", member ) == 0 )
        return sosreport_analyzer_cfg->route.item_num;
    else if ( strcmp ( "netstat", member ) == 0 )
        return sosreport_analyzer_cfg->netstat.item_num;
    else if ( strcmp ( "uname", member ) == 0 )
        return sosreport_analyzer_cfg->uname.item_num;
    else if ( strcmp ( "uptime", member ) == 0 )
        return sosreport_analyzer_cfg->uptime.item_num;
    else if ( strcmp ( "vgdisplay", member ) == 0 )
        return sosreport_analyzer_cfg->vgdisplay.item_num;
    else if ( strcmp ( "boot/grub/", member ) == 0 )
        return sosreport_analyzer_cfg->mcinfo_boot_grub_.item_num;
    else if ( strcmp ( "cmdlog/", member ) == 0 )
        return sosreport_analyzer_cfg->mcinfo_cmdlog_.item_num;
    else if ( strcmp ( "dev/", member ) == 0 )
        return sosreport_analyzer_cfg->dev_.item_num;
    else if ( strcmp ( "etc/NetworkManager/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_NetworkManager_.item_num;
    else if ( strcmp ( "etc/audit/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_audit_.item_num;
    else if ( strcmp ( "etc/anacrontab", member ) == 0 )
        return sosreport_analyzer_cfg->etc_anacrontab.item_num;
    else if ( strcmp ( "etc/crontab", member ) == 0 )
        return sosreport_analyzer_cfg->etc_crontab.item_num;
    else if ( strcmp ( "etc/cron.deny", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_deny.item_num;
    else if ( strcmp ( "etc/cron.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_d_.item_num;
    else if ( strcmp ( "etc/cron.hourly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_hourly_.item_num;
    else if ( strcmp ( "etc/cron.daily/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_daily_.item_num;
    else if ( strcmp ( "etc/cron.weekly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_weekly_.item_num;
    else if ( strcmp ( "etc/cron.monthly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_monthly_.item_num;
    else if ( strcmp ( "etc/default/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_default_.item_num;
    else if ( strcmp ( "etc/dnf/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_dnf_.item_num;
    else if ( strcmp ( "etc/firewalld/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_firewalld_.item_num;
    else if ( strcmp ( "etc/host", member ) == 0 )
        return sosreport_analyzer_cfg->etc_host.item_num;
    else if ( strcmp ( "etc/httpd/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_httpd_.item_num;
    else if ( strcmp ( "etc/kdump.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_kdump_conf.item_num;
    else if ( strcmp ( "etc/logrotate.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_logrotate_conf.item_num;
    else if ( strcmp ( "etc/logrotate.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_logrotate_d_.item_num;
    else if ( strcmp ( "etc/lvm/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_lvm_.item_num;
    else if ( strcmp ( "etc/modprobe.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_modprobe_d_.item_num;
    else if ( strcmp ( "etc/nsswitch.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_nsswitch_conf.item_num;
    else if ( strcmp ( "etc/pam.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_pam_d_.item_num;
    else if ( strcmp ( "etc/pki/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_pki_.item_num;
    else if ( strcmp ( "etc/rsyslog.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_rsyslog_conf.item_num;
    else if ( strcmp ( "etc/selinux/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_selinux_.item_num;
    else if ( strcmp ( "etc/sysconfig/network-scripts/ifcfg-", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.item_num;
    else if ( strcmp ( "etc/sysconfig/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysconfig_.item_num;
    else if ( strcmp ( "etc/sysctl.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysctl_conf.item_num;
    else if ( strcmp ( "etc/systemd/system/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_systemd_system_.item_num;
    else if ( strcmp ( "etc/systemd/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_systemd_.item_num;
    else if ( strcmp ( "etc/udev/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_udev_.item_num;
    else if ( strcmp ( "etc/yum.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_conf.item_num;
    else if ( strcmp ( "etc/yum.repos.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_repos_d_.item_num;
    else if ( strcmp ( "etc/yum/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_.item_num;
    else if ( strcmp ( "etc/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_.item_num;
    else if ( strcmp ( "lib/", member ) == 0 )
        return sosreport_analyzer_cfg->lib_.item_num;
    else if ( strcmp ( "proc/", member ) == 0 )
        return sosreport_analyzer_cfg->proc_.item_num;
    else if ( strcmp ( "proc/cpuinfo", member ) == 0 )
        return sosreport_analyzer_cfg->proc_cpuinfo.item_num;
    else if ( strcmp ( "proc/interrupts", member ) == 0 )
        return sosreport_analyzer_cfg->proc_interrupts.item_num;
    else if ( strcmp ( "proc/meminfo", member ) == 0 )
        return sosreport_analyzer_cfg->proc_meminfo.item_num;
    else if ( strcmp ( "proc/net/dev", member ) == 0 )
        return sosreport_analyzer_cfg->proc_net_dev.item_num;
    else if ( strcmp ( "proc/net/sockstat", member ) == 0 )
        return sosreport_analyzer_cfg->proc_net_sockstat.item_num;
    else if ( strcmp ( "root/anaconda-ks.cfg", member ) == 0 )
        return sosreport_analyzer_cfg->root_anaconda_ks_cfg.item_num;
    else if ( strcmp ( "sos_commands/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_.item_num;
    else if ( strcmp ( "sos_commands/abrt/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_abrt_.item_num;
    else if ( strcmp ( "sos_commands/apache/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_apache_.item_num;
    else if ( strcmp ( "sos_commands/auditd/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_auditd_.item_num;
    else if ( strcmp ( "sos_commands/boot/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_boot_.item_num;
    else if ( strcmp ( "sos_commands/devicemapper/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_devicemapper_.item_num;
    else if ( strcmp ( "sos_commands/dnf/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_dnf_.item_num;
    else if ( strcmp ( "sos_commands/devices/udevadm_info_--export-db", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.item_num;
    else if ( strcmp ( "sos_commands/firewalld/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_firewalld_.item_num;
    else if ( strcmp ( "sos_commands/ipmitool/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_ipmitool_.item_num;
    else if ( strcmp ( "sos_commands/kernel/sysctl_-a", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_num;
    else if ( strcmp ( "sos_commands/logs/journalctl_--no-pager", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_num;
    else if ( strcmp ( "sos_commands/lvm2/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_lvm2_.item_num;
    else if ( strcmp ( "sos_commands/memory/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_memory_.item_num;
    else if ( strcmp ( "sos_commands/networking/ethtool_-S", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_num;
    else if ( strcmp ( "sos_commands/networking/ethtool_-i", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_num;
    else if ( strcmp ( "sos_commands/networking/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_.item_num;
    else if ( strcmp ( "sos_commands/networkmanager/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networkmanager_.item_num;
    else if ( strcmp ( "sos_commands/pam/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_pam_.item_num;
    else if ( strcmp ( "sos_commands/sar/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_sar_.item_num;
    else if ( strcmp ( "sos_commands/scsi/lsscsi", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.item_num;
    else if ( strcmp ( "sos_commands/selinux/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_selinux_.item_num;
    else if ( strcmp ( "sos_commands/usb/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_usb_.item_num;
    else if ( strcmp ( "sos_commands/virsh/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_virsh_.item_num;
    else if ( strcmp ( "sos_commands/yum/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_yum_.item_num;
    else if ( strcmp ( "sos_commands/wireless/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_wireless_.item_num;
    else if ( strcmp ( "sys/module/", member ) == 0 )
        return sosreport_analyzer_cfg->sys_module_.item_num;
    else if ( strcmp ( "usr/", member ) == 0 )
        return sosreport_analyzer_cfg->usr_.item_num;
    else if ( strcmp ( "usr/lib/systemd/", member ) == 0 )
        return sosreport_analyzer_cfg->usr_lib_systemd_.item_num;
    else if ( strcmp ( "var/", member ) == 0 )
        return sosreport_analyzer_cfg->var_.item_num;
    else if ( strcmp ( "var/crash/", member ) == 0 )
        return sosreport_analyzer_cfg->var_crash_.item_num;
    else if ( strcmp ( "var/log/audit/", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_audit_.item_num;
    else if ( strcmp ( "var/log/dmesg", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_dmesg.item_num;
    else if ( strcmp ( "var/log/messages", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_messages.item_num;
    else if ( strcmp ( "var/log/secure", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_secure.item_num;
    else if ( strcmp ( "var/spool/cron/", member ) == 0 )
        return sosreport_analyzer_cfg->var_spool_cron_.item_num;
    else
        return -1;
}

char *get_items_of_member ( const char *member )
{
    if ( strcmp ( "df", member ) == 0 )
        return sosreport_analyzer_cfg->df.member;
    else if ( strcmp ( "date", member ) == 0 )
        return sosreport_analyzer_cfg->date.member;
    else if ( strcmp ( "dmidecode", member ) == 0 )
        return sosreport_analyzer_cfg->dmidecode.member;
    else if ( strcmp ( "free", member ) == 0 )
        return sosreport_analyzer_cfg->free.member;
    else if ( strcmp ( "hostname", member ) == 0 )
        return sosreport_analyzer_cfg->hostname.member;
    else if ( strcmp ( "installed-rpms", member ) == 0 )
        return sosreport_analyzer_cfg->installed_rpms.member;
    else if ( strcmp ( "ip_addr", member ) == 0 )
        return sosreport_analyzer_cfg->ip_addr.member;
    else if ( strcmp ( "last", member ) == 0 )
        return sosreport_analyzer_cfg->last.member;
    else if ( strcmp ( "lsb-release", member ) == 0 )
        return sosreport_analyzer_cfg->lsb_release.member;
    else if ( strcmp ( "lsmod", member ) == 0 )
        return sosreport_analyzer_cfg->lsmod.member;
    else if ( strcmp ( "lsof", member ) == 0 )
        return sosreport_analyzer_cfg->lsof.member;
    else if ( strcmp ( "lspci", member ) == 0 )
        return sosreport_analyzer_cfg->lspci.member;
    else if ( strcmp ( "ps", member ) == 0 )
        return sosreport_analyzer_cfg->ps.member;
    else if ( strcmp ( "route", member ) == 0 )
        return sosreport_analyzer_cfg->route.member;
    else if ( strcmp ( "netstat", member ) == 0 )
        return sosreport_analyzer_cfg->netstat.member;
    else if ( strcmp ( "uname", member ) == 0 )
        return sosreport_analyzer_cfg->uname.member;
    else if ( strcmp ( "uptime", member ) == 0 )
        return sosreport_analyzer_cfg->uptime.member;
    else if ( strcmp ( "vgdisplay", member ) == 0 )
        return sosreport_analyzer_cfg->vgdisplay.member;
    else if ( strcmp ( "boot/grub/", member ) == 0 )
        return sosreport_analyzer_cfg->mcinfo_boot_grub_.member;
    else if ( strcmp ( "cmdlog/", member ) == 0 )
        return sosreport_analyzer_cfg->mcinfo_cmdlog_.member;
    else if ( strcmp ( "dev/", member ) == 0 )
        return sosreport_analyzer_cfg->dev_.member;
    else if ( strcmp ( "etc/NetworkManager/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_NetworkManager_.member;
    else if ( strcmp ( "etc/audit/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_audit_.member;
    else if ( strcmp ( "etc/anacrontab", member ) == 0 )
        return sosreport_analyzer_cfg->etc_anacrontab.member;
    else if ( strcmp ( "etc/crontab", member ) == 0 )
        return sosreport_analyzer_cfg->etc_crontab.member;
    else if ( strcmp ( "etc/cron.deny", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_deny.member;
    else if ( strcmp ( "etc/cron.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_d_.member;
    else if ( strcmp ( "etc/cron.hourly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_hourly_.member;
    else if ( strcmp ( "etc/cron.daily/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_daily_.member;
    else if ( strcmp ( "etc/cron.weekly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_weekly_.member;
    else if ( strcmp ( "etc/cron.monthly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_monthly_.member;
    else if ( strcmp ( "etc/default/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_default_.member;
    else if ( strcmp ( "etc/dnf/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_dnf_.member;
    else if ( strcmp ( "etc/firewalld/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_firewalld_.member;
    else if ( strcmp ( "etc/host", member ) == 0 )
        return sosreport_analyzer_cfg->etc_host.member;
    else if ( strcmp ( "etc/httpd/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_httpd_.member;
    else if ( strcmp ( "etc/kdump.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_kdump_conf.member;
    else if ( strcmp ( "etc/logrotate.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_logrotate_conf.member;
    else if ( strcmp ( "etc/logrotate.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_logrotate_d_.member;
    else if ( strcmp ( "etc/lvm/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_lvm_.member;
    else if ( strcmp ( "etc/modprobe.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_modprobe_d_.member;
    else if ( strcmp ( "etc/nsswitch.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_nsswitch_conf.member;
    else if ( strcmp ( "etc/pam.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_pam_d_.member;
    else if ( strcmp ( "etc/pki/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_pki_.member;
    else if ( strcmp ( "etc/rsyslog.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_rsyslog_conf.member;
    else if ( strcmp ( "etc/selinux/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_selinux_.member;
    else if ( strcmp ( "etc/sysconfig/network-scripts/ifcfg-", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.member;
    else if ( strcmp ( "etc/sysconfig/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysconfig_.member;
    else if ( strcmp ( "etc/sysctl.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysctl_conf.member;
    else if ( strcmp ( "etc/systemd/system/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_systemd_system_.member;
    else if ( strcmp ( "etc/systemd/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_systemd_.member;
    else if ( strcmp ( "etc/udev/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_udev_.member;
    else if ( strcmp ( "etc/yum.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_conf.member;
    else if ( strcmp ( "etc/yum.repos.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_repos_d_.member;
    else if ( strcmp ( "etc/yum/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_.member;
    else if ( strcmp ( "etc/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_.member;
    else if ( strcmp ( "lib/", member ) == 0 )
        return sosreport_analyzer_cfg->lib_.member;
    else if ( strcmp ( "proc/", member ) == 0 )
        return sosreport_analyzer_cfg->proc_.member;
    else if ( strcmp ( "proc/cpuinfo", member ) == 0 )
        return sosreport_analyzer_cfg->proc_cpuinfo.member;
    else if ( strcmp ( "proc/interrupts", member ) == 0 )
        return sosreport_analyzer_cfg->proc_interrupts.member;
    else if ( strcmp ( "proc/meminfo", member ) == 0 )
        return sosreport_analyzer_cfg->proc_meminfo.member;
    else if ( strcmp ( "proc/net/dev", member ) == 0 )
        return sosreport_analyzer_cfg->proc_net_dev.member;
    else if ( strcmp ( "proc/net/sockstat", member ) == 0 )
        return sosreport_analyzer_cfg->proc_net_sockstat.member;
    else if ( strcmp ( "root/anaconda-ks.cfg", member ) == 0 )
        return sosreport_analyzer_cfg->root_anaconda_ks_cfg.member;
    else if ( strcmp ( "sos_commands/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_.member;
    else if ( strcmp ( "sos_commands/auditd/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_auditd_.member;
    else if ( strcmp ( "sos_commands/abrt/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_abrt_.member;
    else if ( strcmp ( "sos_commands/apache/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_apache_.member;
    else if ( strcmp ( "sos_commands/boot/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_boot_.member;
    else if ( strcmp ( "sos_commands/devicemapper/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_devicemapper_.member;
    else if ( strcmp ( "sos_commands/devices/udevadm_info_--export-db", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.member;
    else if ( strcmp ( "sos_commands/dnf/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_dnf_.member;
    else if ( strcmp ( "sos_commands/firewalld/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_firewalld_.member;
    else if ( strcmp ( "sos_commands/ipmitool/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_ipmitool_.member;
    else if ( strcmp ( "sos_commands/kernel/sysctl_-a", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.member;
    else if ( strcmp ( "sos_commands/logs/journalctl_--no-pager", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.member;
    else if ( strcmp ( "sos_commands/lvm2/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_lvm2_.member;
    else if ( strcmp ( "sos_commands/memory/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_memory_.member;
    else if ( strcmp ( "sos_commands/networking/ethtool_-S", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.member;
    else if ( strcmp ( "sos_commands/networking/ethtool_-i", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.member;
    else if ( strcmp ( "sos_commands/networking/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_.member;
    else if ( strcmp ( "sos_commands/networkmanager/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networkmanager_.member;
    else if ( strcmp ( "sos_commands/pam/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_pam_.member;
    else if ( strcmp ( "sos_commands/sar/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_sar_.member;
    else if ( strcmp ( "sos_commands/scsi/lsscsi", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.member;
    else if ( strcmp ( "sos_commands/selinux/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_selinux_.member;
    else if ( strcmp ( "sos_commands/usb/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_usb_.member;
    else if ( strcmp ( "sos_commands/virsh/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_virsh_.member;
    else if ( strcmp ( "sos_commands/yum/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_yum_.member;
    else if ( strcmp ( "sos_commands/wireless/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_wireless_.member;
    else if ( strcmp ( "sys/module/", member ) == 0 )
        return sosreport_analyzer_cfg->sys_module_.member;
    else if ( strcmp ( "usr/", member ) == 0 )
        return sosreport_analyzer_cfg->usr_.member;
    else if ( strcmp ( "usr/lib/systemd/", member ) == 0 )
        return sosreport_analyzer_cfg->usr_lib_systemd_.member;
    else if ( strcmp ( "var/", member ) == 0 )
        return sosreport_analyzer_cfg->var_.member;
    else if ( strcmp ( "var/crash/", member ) == 0 )
        return sosreport_analyzer_cfg->var_crash_.member;
    else if ( strcmp ( "var/log/audit/", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_audit_.member;
    else if ( strcmp ( "var/log/dmesg", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_dmesg.member;
    else if ( strcmp ( "var/log/messages", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_messages.member;
    else if ( strcmp ( "var/log/secure", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_secure.member;
    else if ( strcmp ( "var/spool/cron/", member ) == 0 )
        return sosreport_analyzer_cfg->var_spool_cron_.member;
    else
        return "nothing";
}

int get_file_numbers_of_member ( const char *member )
{
    if ( strcmp ( "df", member ) == 0 )
        return sosreport_analyzer_cfg->df.file_num;
    else if ( strcmp ( "date", member ) == 0 )
        return sosreport_analyzer_cfg->date.file_num;
    else if ( strcmp ( "dmidecode", member ) == 0 )
        return sosreport_analyzer_cfg->dmidecode.file_num;
    else if ( strcmp ( "free", member ) == 0 )
        return sosreport_analyzer_cfg->free.file_num;
    else if ( strcmp ( "hostname", member ) == 0 )
        return sosreport_analyzer_cfg->hostname.file_num;
    else if ( strcmp ( "installed-rpms", member ) == 0 )
        return sosreport_analyzer_cfg->installed_rpms.file_num;
    else if ( strcmp ( "ip_addr", member ) == 0 )
        return sosreport_analyzer_cfg->ip_addr.file_num;
    else if ( strcmp ( "last", member ) == 0 )
        return sosreport_analyzer_cfg->last.file_num;
    else if ( strcmp ( "lsb-release", member ) == 0 )
        return sosreport_analyzer_cfg->lsb_release.file_num;
    else if ( strcmp ( "lsmod", member ) == 0 )
        return sosreport_analyzer_cfg->lsmod.file_num;
    else if ( strcmp ( "lsof", member ) == 0 )
        return sosreport_analyzer_cfg->lsof.file_num;
    else if ( strcmp ( "lspci", member ) == 0 )
        return sosreport_analyzer_cfg->lspci.file_num;
    else if ( strcmp ( "ps", member ) == 0 )
        return sosreport_analyzer_cfg->ps.file_num;
    else if ( strcmp ( "route", member ) == 0 )
        return sosreport_analyzer_cfg->route.file_num;
    else if ( strcmp ( "netstat", member ) == 0 )
        return sosreport_analyzer_cfg->netstat.file_num;
    else if ( strcmp ( "uname", member ) == 0 )
        return sosreport_analyzer_cfg->uname.file_num;
    else if ( strcmp ( "uptime", member ) == 0 )
        return sosreport_analyzer_cfg->uptime.file_num;
    else if ( strcmp ( "vgdisplay", member ) == 0 )
        return sosreport_analyzer_cfg->vgdisplay.file_num;
    else if ( strcmp ( "boot/grub/", member ) == 0 )
        return sosreport_analyzer_cfg->mcinfo_boot_grub_.file_num;
    else if ( strcmp ( "cmdlog/", member ) == 0 )
        return sosreport_analyzer_cfg->mcinfo_cmdlog_.file_num;
    else if ( strcmp ( "dev/", member ) == 0 )
        return sosreport_analyzer_cfg->dev_.file_num;
    else if ( strcmp ( "etc/NetworkManager/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_NetworkManager_.file_num;
    else if ( strcmp ( "etc/audit/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_audit_.file_num;
    else if ( strcmp ( "etc/anacrontab", member ) == 0 )
        return sosreport_analyzer_cfg->etc_anacrontab.file_num;
    else if ( strcmp ( "etc/crontab", member ) == 0 )
        return sosreport_analyzer_cfg->etc_crontab.file_num;
    else if ( strcmp ( "etc/cron.deny", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_deny.file_num;
    else if ( strcmp ( "etc/cron.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_d_.file_num;
    else if ( strcmp ( "etc/cron.hourly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_hourly_.file_num;
    else if ( strcmp ( "etc/cron.daily/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_daily_.file_num;
    else if ( strcmp ( "etc/cron.weekly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_weekly_.file_num;
    else if ( strcmp ( "etc/cron.monthly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_monthly_.file_num;
    else if ( strcmp ( "etc/default/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_default_.file_num;
    else if ( strcmp ( "etc/dnf/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_dnf_.file_num;
    else if ( strcmp ( "etc/firewalld/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_firewalld_.file_num;
    else if ( strcmp ( "etc/host", member ) == 0 )
        return sosreport_analyzer_cfg->etc_host.file_num;
    else if ( strcmp ( "etc/httpd/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_httpd_.file_num;
    else if ( strcmp ( "etc/kdump.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_kdump_conf.file_num;
    else if ( strcmp ( "etc/logrotate.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_logrotate_conf.file_num;
    else if ( strcmp ( "etc/logrotate.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_logrotate_d_.file_num;
    else if ( strcmp ( "etc/lvm/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_lvm_.file_num;
    else if ( strcmp ( "etc/modprobe.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_modprobe_d_.file_num;
    else if ( strcmp ( "etc/nsswitch.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_nsswitch_conf.file_num;
    else if ( strcmp ( "etc/pam.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_pam_d_.file_num;
    else if ( strcmp ( "etc/pki/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_pki_.file_num;
    else if ( strcmp ( "etc/rsyslog.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_rsyslog_conf.file_num;
    else if ( strcmp ( "etc/selinux/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_selinux_.file_num;
    else if ( strcmp ( "etc/sysconfig/network-scripts/ifcfg-", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.file_num;
    else if ( strcmp ( "etc/sysconfig/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysconfig_.file_num;
    else if ( strcmp ( "etc/sysctl.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysctl_conf.file_num;
    else if ( strcmp ( "etc/systemd/system/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_systemd_system_.file_num;
    else if ( strcmp ( "etc/systemd/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_systemd_.file_num;
    else if ( strcmp ( "etc/udev/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_udev_.file_num;
    else if ( strcmp ( "etc/yum.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_conf.file_num;
    else if ( strcmp ( "etc/yum.repos.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_repos_d_.file_num;
    else if ( strcmp ( "etc/yum/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_.file_num;
    else if ( strcmp ( "etc/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_.file_num;
    else if ( strcmp ( "lib/", member ) == 0 )
        return sosreport_analyzer_cfg->lib_.file_num;
    else if ( strcmp ( "proc/", member ) == 0 )
        return sosreport_analyzer_cfg->proc_.file_num;
    else if ( strcmp ( "proc/cpuinfo", member ) == 0 )
        return sosreport_analyzer_cfg->proc_cpuinfo.file_num;
    else if ( strcmp ( "proc/interrupts", member ) == 0 )
        return sosreport_analyzer_cfg->proc_interrupts.file_num;
    else if ( strcmp ( "proc/meminfo", member ) == 0 )
        return sosreport_analyzer_cfg->proc_meminfo.file_num;
    else if ( strcmp ( "proc/net/dev", member ) == 0 )
        return sosreport_analyzer_cfg->proc_net_dev.file_num;
    else if ( strcmp ( "proc/net/sockstat", member ) == 0 )
        return sosreport_analyzer_cfg->proc_net_sockstat.file_num;
    else if ( strcmp ( "root/anaconda-ks.cfg", member ) == 0 )
        return sosreport_analyzer_cfg->root_anaconda_ks_cfg.file_num;
    else if ( strcmp ( "sos_commands/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_.file_num;
    else if ( strcmp ( "sos_commands/abrt/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_abrt_.file_num;
    else if ( strcmp ( "sos_commands/apache/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_apache_.file_num;
    else if ( strcmp ( "sos_commands/auditd/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_auditd_.file_num;
    else if ( strcmp ( "sos_commands/boot/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_boot_.file_num;
    else if ( strcmp ( "sos_commands/devicemapper/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_devicemapper_.file_num;
    else if ( strcmp ( "sos_commands/devices/udevadm_info_--export-db", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.file_num;
    else if ( strcmp ( "sos_commands/dnf/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_dnf_.file_num;
    else if ( strcmp ( "sos_commands/firewalld/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_firewalld_.file_num;
    else if ( strcmp ( "sos_commands/ipmitool/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_ipmitool_.file_num;
    else if ( strcmp ( "sos_commands/kernel/sysctl_-a", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.file_num;
    else if ( strcmp ( "sos_commands/logs/journalctl_--no-pager", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.file_num;
    else if ( strcmp ( "sos_commands/lvm2/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_lvm2_.file_num;
    else if ( strcmp ( "sos_commands/memory/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_memory_.file_num;
    else if ( strcmp ( "sos_commands/networking/ethtool_-S", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.file_num;
    else if ( strcmp ( "sos_commands/networking/ethtool_-i", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.file_num;
    else if ( strcmp ( "sos_commands/networking/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_.file_num;
    else if ( strcmp ( "sos_commands/networkmanager/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networkmanager_.file_num;
    else if ( strcmp ( "sos_commands/pam/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_pam_.file_num;
    else if ( strcmp ( "sos_commands/sar/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_sar_.file_num;
    else if ( strcmp ( "sos_commands/scsi/lsscsi", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.file_num;
    else if ( strcmp ( "sos_commands/selinux/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_selinux_.file_num;
    else if ( strcmp ( "sos_commands/usb/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_usb_.file_num;
    else if ( strcmp ( "sos_commands/virsh/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_virsh_.file_num;
    else if ( strcmp ( "sos_commands/yum/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_yum_.file_num;
    else if ( strcmp ( "sos_commands/wireless/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_wireless_.file_num;
    else if ( strcmp ( "sys/module/", member ) == 0 )
        return sosreport_analyzer_cfg->sys_module_.file_num;
    else if ( strcmp ( "usr/", member ) == 0 )
        return sosreport_analyzer_cfg->usr_.file_num;
    else if ( strcmp ( "usr/lib/systemd/", member ) == 0 )
        return sosreport_analyzer_cfg->usr_lib_systemd_.file_num;
    else if ( strcmp ( "var/", member ) == 0 )
        return sosreport_analyzer_cfg->var_.file_num;
    else if ( strcmp ( "var/crash/", member ) == 0 )
        return sosreport_analyzer_cfg->var_crash_.file_num;
    else if ( strcmp ( "var/log/audit/", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_audit_.file_num;
    else if ( strcmp ( "var/log/dmesg", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_dmesg.file_num;
    else if ( strcmp ( "var/log/messages", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_messages.file_num;
    else if ( strcmp ( "var/log/secure", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_secure.file_num;
    else if ( strcmp ( "var/spool/cron/", member ) == 0 )
        return sosreport_analyzer_cfg->var_spool_cron_.file_num;
    else
        return -1;
}

int set_item_numbers_of_member ( const char *member, int x )
{
    if ( strcmp ( "df", member ) == 0 )
        sosreport_analyzer_cfg->df.item_num = x; 
    else if ( strcmp ( "date", member ) == 0 )
        sosreport_analyzer_cfg->date.item_num = x; 
    else if ( strcmp ( "dmidecode", member ) == 0 )
        sosreport_analyzer_cfg->dmidecode.item_num = x; 
    else if ( strcmp ( "free", member ) == 0 )
        sosreport_analyzer_cfg->free.item_num = x; 
    else if ( strcmp ( "hostname", member ) == 0 )
        sosreport_analyzer_cfg->hostname.item_num = x; 
    else if ( strcmp ( "installed-rpms", member ) == 0 )
        sosreport_analyzer_cfg->installed_rpms.item_num = x; 
    else if ( strcmp ( "ip_addr", member ) == 0 )
        sosreport_analyzer_cfg->ip_addr.item_num = x; 
    else if ( strcmp ( "last", member ) == 0 )
        sosreport_analyzer_cfg->last.item_num = x; 
    else if ( strcmp ( "lsb-release", member ) == 0 )
        sosreport_analyzer_cfg->lsb_release.item_num = x; 
    else if ( strcmp ( "lsmod", member ) == 0 )
        sosreport_analyzer_cfg->lsmod.item_num = x; 
    else if ( strcmp ( "lsof", member ) == 0 )
        sosreport_analyzer_cfg->lsof.item_num = x; 
    else if ( strcmp ( "lspci", member ) == 0 )
        sosreport_analyzer_cfg->lspci.item_num = x; 
    else if ( strcmp ( "ps", member ) == 0 )
        sosreport_analyzer_cfg->ps.item_num = x; 
    else if ( strcmp ( "route", member ) == 0 )
        sosreport_analyzer_cfg->route.item_num = x; 
    else if ( strcmp ( "netstat", member ) == 0 )
        sosreport_analyzer_cfg->netstat.item_num = x; 
    else if ( strcmp ( "uname", member ) == 0 )
        sosreport_analyzer_cfg->uname.item_num = x; 
    else if ( strcmp ( "uptime", member ) == 0 )
        sosreport_analyzer_cfg->uptime.item_num = x; 
    else if ( strcmp ( "vgdisplay", member ) == 0 )
        sosreport_analyzer_cfg->vgdisplay.item_num = x; 
    else if ( strcmp ( "boot/grub/", member ) == 0 )
        sosreport_analyzer_cfg->mcinfo_boot_grub_.item_num = x; 
    else if ( strcmp ( "cmdlog/", member ) == 0 )
        sosreport_analyzer_cfg->mcinfo_cmdlog_.item_num = x; 
    else if ( strcmp ( "dev/", member ) == 0 )
        sosreport_analyzer_cfg->dev_.item_num = x; 
    else if ( strcmp ( "etc/NetworkManager/", member ) == 0 )
        sosreport_analyzer_cfg->etc_NetworkManager_.item_num = x; 
    else if ( strcmp ( "etc/audit/", member ) == 0 )
        sosreport_analyzer_cfg->etc_audit_.item_num = x; 
    else if ( strcmp ( "etc/anacrontab", member ) == 0 )
        sosreport_analyzer_cfg->etc_anacrontab.item_num = x; 
    else if ( strcmp ( "etc/crontab", member ) == 0 )
        sosreport_analyzer_cfg->etc_crontab.item_num = x; 
    else if ( strcmp ( "etc/cron.deny", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_deny.item_num = x; 
    else if ( strcmp ( "etc/cron.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_d_.item_num = x; 
    else if ( strcmp ( "etc/cron.hourly/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_hourly_.item_num = x; 
    else if ( strcmp ( "etc/cron.daily/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_daily_.item_num = x; 
    else if ( strcmp ( "etc/cron.weekly/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_weekly_.item_num = x; 
    else if ( strcmp ( "etc/cron.monthly/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_monthly_.item_num = x; 
    else if ( strcmp ( "etc/default/", member ) == 0 )
        sosreport_analyzer_cfg->etc_default_.item_num = x; 
    else if ( strcmp ( "etc/dnf/", member ) == 0 )
        sosreport_analyzer_cfg->etc_dnf_.item_num = x; 
    else if ( strcmp ( "etc/firewalld/", member ) == 0 )
        sosreport_analyzer_cfg->etc_firewalld_.item_num = x; 
    else if ( strcmp ( "etc/host", member ) == 0 )
        sosreport_analyzer_cfg->etc_host.item_num = x; 
    else if ( strcmp ( "etc/httpd/", member ) == 0 )
        sosreport_analyzer_cfg->etc_httpd_.item_num = x; 
    else if ( strcmp ( "etc/kdump.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_kdump_conf.item_num = x; 
    else if ( strcmp ( "etc/logrotate.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_logrotate_conf.item_num = x; 
    else if ( strcmp ( "etc/logrotate.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_logrotate_d_.item_num = x; 
    else if ( strcmp ( "etc/lvm/", member ) == 0 )
        sosreport_analyzer_cfg->etc_lvm_.item_num = x; 
    else if ( strcmp ( "etc/modprobe.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_modprobe_d_.item_num = x; 
    else if ( strcmp ( "etc/nsswitch.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_nsswitch_conf.item_num = x; 
    else if ( strcmp ( "etc/pam.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_pam_d_.item_num = x; 
    else if ( strcmp ( "etc/pki/", member ) == 0 )
        sosreport_analyzer_cfg->etc_pki_.item_num = x; 
    else if ( strcmp ( "etc/rsyslog.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_rsyslog_conf.item_num = x; 
    else if ( strcmp ( "etc/selinux/", member ) == 0 )
        sosreport_analyzer_cfg->etc_selinux_.item_num = x; 
    else if ( strcmp ( "etc/sysconfig/network-scripts/ifcfg-", member ) == 0 )
        sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.item_num = x; 
    else if ( strcmp ( "etc/sysconfig/", member ) == 0 )
        sosreport_analyzer_cfg->etc_sysconfig_.item_num = x; 
    else if ( strcmp ( "etc/sysctl.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_sysctl_conf.item_num = x; 
    else if ( strcmp ( "etc/systemd/system/", member ) == 0 )
        sosreport_analyzer_cfg->etc_systemd_system_.item_num = x; 
    else if ( strcmp ( "etc/systemd/", member ) == 0 )
        sosreport_analyzer_cfg->etc_systemd_.item_num = x; 
    else if ( strcmp ( "etc/udev/", member ) == 0 )
        sosreport_analyzer_cfg->etc_udev_.item_num = x; 
    else if ( strcmp ( "etc/yum.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_yum_conf.item_num = x; 
    else if ( strcmp ( "etc/yum.repos.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_yum_repos_d_.item_num = x; 
    else if ( strcmp ( "etc/yum/", member ) == 0 )
        sosreport_analyzer_cfg->etc_yum_.item_num = x; 
    else if ( strcmp ( "etc/", member ) == 0 )
        sosreport_analyzer_cfg->etc_.item_num = x; 
    else if ( strcmp ( "lib/", member ) == 0 )
        sosreport_analyzer_cfg->lib_.item_num = x; 
    else if ( strcmp ( "proc/", member ) == 0 )
        sosreport_analyzer_cfg->proc_.item_num = x; 
    else if ( strcmp ( "proc/cpuinfo", member ) == 0 )
        sosreport_analyzer_cfg->proc_cpuinfo.item_num = x; 
    else if ( strcmp ( "proc/interrupts", member ) == 0 )
        sosreport_analyzer_cfg->proc_interrupts.item_num = x; 
    else if ( strcmp ( "proc/meminfo", member ) == 0 )
        sosreport_analyzer_cfg->proc_meminfo.item_num = x; 
    else if ( strcmp ( "proc/net/dev", member ) == 0 )
        sosreport_analyzer_cfg->proc_net_dev.item_num = x; 
    else if ( strcmp ( "proc/net/sockstat", member ) == 0 )
        sosreport_analyzer_cfg->proc_net_sockstat.item_num = x; 
    else if ( strcmp ( "root/anaconda-ks.cfg", member ) == 0 )
        sosreport_analyzer_cfg->root_anaconda_ks_cfg.item_num = x; 
    else if ( strcmp ( "sos_commands/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_.item_num = x; 
    else if ( strcmp ( "sos_commands/abrt/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_abrt_.item_num = x; 
    else if ( strcmp ( "sos_commands/apache/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_apache_.item_num = x; 
    else if ( strcmp ( "sos_commands/auditd/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_auditd_.item_num = x; 
    else if ( strcmp ( "sos_commands/boot/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_boot_.item_num = x; 
    else if ( strcmp ( "sos_commands/devicemapper/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_devicemapper_.item_num = x; 
    else if ( strcmp ( "sos_commands/devices/udevadm_info_--export-db", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.item_num = x; 
    else if ( strcmp ( "sos_commands/dnf/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_dnf_.item_num = x; 
    else if ( strcmp ( "sos_commands/firewalld/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_firewalld_.item_num = x; 
    else if ( strcmp ( "sos_commands/ipmitool/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_ipmitool_.item_num = x; 
    else if ( strcmp ( "sos_commands/kernel/sysctl_-a", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_num = x; 
    else if ( strcmp ( "sos_commands/logs/journalctl_--no-pager", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_num = x; 
    else if ( strcmp ( "sos_commands/lvm2/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_lvm2_.item_num = x; 
    else if ( strcmp ( "sos_commands/memory/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_memory_.item_num = x; 
    else if ( strcmp ( "sos_commands/networking/ethtool_-S", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_num = x; 
    else if ( strcmp ( "sos_commands/networking/ethtool_-i", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_num = x; 
    else if ( strcmp ( "sos_commands/networking/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_networking_.item_num = x; 
    else if ( strcmp ( "sos_commands/networkmanager/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_networkmanager_.item_num = x; 
    else if ( strcmp ( "sos_commands/pam/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_pam_.item_num = x; 
    else if ( strcmp ( "sos_commands/sar/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_sar_.item_num = x; 
    else if ( strcmp ( "sos_commands/scsi/lsscsi", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.item_num = x; 
    else if ( strcmp ( "sos_commands/selinux/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_selinux_.item_num = x; 
    else if ( strcmp ( "sos_commands/usb/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_usb_.item_num = x; 
    else if ( strcmp ( "sos_commands/virsh/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_virsh_.item_num = x; 
    else if ( strcmp ( "sos_commands/yum/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_yum_.item_num = x; 
    else if ( strcmp ( "sos_commands/wireless/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_wireless_.item_num = x; 
    else if ( strcmp ( "sys/module/", member ) == 0 )
        sosreport_analyzer_cfg->sys_module_.item_num = x; 
    else if ( strcmp ( "usr/", member ) == 0 )
        sosreport_analyzer_cfg->usr_.item_num = x; 
    else if ( strcmp ( "usr/lib/systemd/", member ) == 0 )
        sosreport_analyzer_cfg->usr_lib_systemd_.item_num = x; 
    else if ( strcmp ( "var/", member ) == 0 )
        sosreport_analyzer_cfg->var_.item_num = x; 
    else if ( strcmp ( "var/crash/", member ) == 0 )
        sosreport_analyzer_cfg->var_crash_.item_num = x; 
    else if ( strcmp ( "var/log/audit/", member ) == 0 )
        sosreport_analyzer_cfg->var_log_audit_.item_num = x; 
    else if ( strcmp ( "var/log/dmesg", member ) == 0 )
        sosreport_analyzer_cfg->var_log_dmesg.item_num = x; 
    else if ( strcmp ( "var/log/messages", member ) == 0 )
        sosreport_analyzer_cfg->var_log_messages.item_num = x; 
    else if ( strcmp ( "var/log/secure", member ) == 0 )
        sosreport_analyzer_cfg->var_log_secure.item_num = x; 
    else if ( strcmp ( "var/spool/cron/", member ) == 0 )
        sosreport_analyzer_cfg->var_spool_cron_.item_num = x; 

    return ( 0 );
}

int set_file_numbers_of_member ( const char *member, int x )
{
    if ( strcmp ( "df", member ) == 0 )
        sosreport_analyzer_cfg->df.file_num = x; 
    else if ( strcmp ( "date", member ) == 0 )
        sosreport_analyzer_cfg->date.file_num = x; 
    else if ( strcmp ( "dmidecode", member ) == 0 )
        sosreport_analyzer_cfg->dmidecode.file_num = x; 
    else if ( strcmp ( "free", member ) == 0 )
        sosreport_analyzer_cfg->free.file_num = x; 
    else if ( strcmp ( "hostname", member ) == 0 )
        sosreport_analyzer_cfg->hostname.file_num = x; 
    else if ( strcmp ( "installed-rpms", member ) == 0 )
        sosreport_analyzer_cfg->installed_rpms.file_num = x; 
    else if ( strcmp ( "ip_addr", member ) == 0 )
        sosreport_analyzer_cfg->ip_addr.file_num = x; 
    else if ( strcmp ( "last", member ) == 0 )
        sosreport_analyzer_cfg->last.file_num = x; 
    else if ( strcmp ( "lsb-release", member ) == 0 )
        sosreport_analyzer_cfg->lsb_release.file_num = x; 
    else if ( strcmp ( "lsmod", member ) == 0 )
        sosreport_analyzer_cfg->lsmod.file_num = x; 
    else if ( strcmp ( "lsof", member ) == 0 )
        sosreport_analyzer_cfg->lsof.file_num = x; 
    else if ( strcmp ( "lspci", member ) == 0 )
        sosreport_analyzer_cfg->lspci.file_num = x; 
    else if ( strcmp ( "ps", member ) == 0 )
        sosreport_analyzer_cfg->ps.file_num = x; 
    else if ( strcmp ( "route", member ) == 0 )
        sosreport_analyzer_cfg->route.file_num = x; 
    else if ( strcmp ( "netstat", member ) == 0 )
        sosreport_analyzer_cfg->netstat.file_num = x; 
    else if ( strcmp ( "uname", member ) == 0 )
        sosreport_analyzer_cfg->uname.file_num = x; 
    else if ( strcmp ( "uptime", member ) == 0 )
        sosreport_analyzer_cfg->uptime.file_num = x; 
    else if ( strcmp ( "vgdisplay", member ) == 0 )
        sosreport_analyzer_cfg->vgdisplay.file_num = x; 
    else if ( strcmp ( "boot/grub/", member ) == 0 )
        sosreport_analyzer_cfg->mcinfo_boot_grub_.file_num = x; 
    else if ( strcmp ( "cmdlog/", member ) == 0 )
        sosreport_analyzer_cfg->mcinfo_cmdlog_.file_num = x; 
    else if ( strcmp ( "dev/", member ) == 0 )
        sosreport_analyzer_cfg->dev_.file_num = x; 
    else if ( strcmp ( "etc/NetworkManager/", member ) == 0 )
        sosreport_analyzer_cfg->etc_NetworkManager_.file_num = x; 
    else if ( strcmp ( "etc/audit/", member ) == 0 )
        sosreport_analyzer_cfg->etc_audit_.file_num = x; 
    else if ( strcmp ( "etc/anacrontab", member ) == 0 )
        sosreport_analyzer_cfg->etc_anacrontab.file_num = x; 
    else if ( strcmp ( "etc/crontab", member ) == 0 )
        sosreport_analyzer_cfg->etc_crontab.file_num = x; 
    else if ( strcmp ( "etc/cron.deny", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_deny.file_num = x; 
    else if ( strcmp ( "etc/cron.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_d_.file_num = x; 
    else if ( strcmp ( "etc/cron.hourly/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_hourly_.file_num = x; 
    else if ( strcmp ( "etc/cron.daily/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_daily_.file_num = x; 
    else if ( strcmp ( "etc/cron.weekly/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_weekly_.file_num = x; 
    else if ( strcmp ( "etc/cron.monthly/", member ) == 0 )
        sosreport_analyzer_cfg->etc_cron_monthly_.file_num = x; 
    else if ( strcmp ( "etc/default/", member ) == 0 )
        sosreport_analyzer_cfg->etc_default_.file_num = x; 
    else if ( strcmp ( "etc/dnf/", member ) == 0 )
        sosreport_analyzer_cfg->etc_dnf_.file_num = x; 
    else if ( strcmp ( "etc/firewalld/", member ) == 0 )
        sosreport_analyzer_cfg->etc_firewalld_.file_num = x; 
    else if ( strcmp ( "etc/host", member ) == 0 )
        sosreport_analyzer_cfg->etc_host.file_num = x; 
    else if ( strcmp ( "etc/httpd/", member ) == 0 )
        sosreport_analyzer_cfg->etc_httpd_.file_num = x; 
    else if ( strcmp ( "etc/kdump.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_kdump_conf.file_num = x; 
    else if ( strcmp ( "etc/logrotate.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_logrotate_conf.file_num = x; 
    else if ( strcmp ( "etc/logrotate.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_logrotate_d_.file_num = x; 
    else if ( strcmp ( "etc/lvm/", member ) == 0 )
        sosreport_analyzer_cfg->etc_lvm_.file_num = x; 
    else if ( strcmp ( "etc/modprobe.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_modprobe_d_.file_num = x; 
    else if ( strcmp ( "etc/nsswitch.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_nsswitch_conf.file_num = x; 
    else if ( strcmp ( "etc/pam.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_pam_d_.file_num = x; 
    else if ( strcmp ( "etc/pki/", member ) == 0 )
        sosreport_analyzer_cfg->etc_pki_.file_num = x; 
    else if ( strcmp ( "etc/rsyslog.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_rsyslog_conf.file_num = x; 
    else if ( strcmp ( "etc/selinux/", member ) == 0 )
        sosreport_analyzer_cfg->etc_selinux_.file_num = x; 
    else if ( strcmp ( "etc/sysconfig/network-scripts/ifcfg-", member ) == 0 )
        sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.file_num = x; 
    else if ( strcmp ( "etc/sysconfig/", member ) == 0 )
        sosreport_analyzer_cfg->etc_sysconfig_.file_num = x; 
    else if ( strcmp ( "etc/sysctl.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_sysctl_conf.file_num = x; 
    else if ( strcmp ( "etc/systemd/system/", member ) == 0 )
        sosreport_analyzer_cfg->etc_systemd_system_.file_num = x; 
    else if ( strcmp ( "etc/systemd/", member ) == 0 )
        sosreport_analyzer_cfg->etc_systemd_.file_num = x; 
    else if ( strcmp ( "etc/udev/", member ) == 0 )
        sosreport_analyzer_cfg->etc_udev_.file_num = x; 
    else if ( strcmp ( "etc/yum.conf", member ) == 0 )
        sosreport_analyzer_cfg->etc_yum_conf.file_num = x; 
    else if ( strcmp ( "etc/yum.repos.d/", member ) == 0 )
        sosreport_analyzer_cfg->etc_yum_repos_d_.file_num = x; 
    else if ( strcmp ( "etc/yum/", member ) == 0 )
        sosreport_analyzer_cfg->etc_yum_.file_num = x; 
    else if ( strcmp ( "etc/", member ) == 0 )
        sosreport_analyzer_cfg->etc_.file_num = x; 
    else if ( strcmp ( "lib/", member ) == 0 )
        sosreport_analyzer_cfg->lib_.file_num = x; 
    else if ( strcmp ( "proc/", member ) == 0 )
        sosreport_analyzer_cfg->proc_.file_num = x; 
    else if ( strcmp ( "proc/cpuinfo", member ) == 0 )
        sosreport_analyzer_cfg->proc_cpuinfo.file_num = x; 
    else if ( strcmp ( "proc/interrupts", member ) == 0 )
        sosreport_analyzer_cfg->proc_interrupts.file_num = x; 
    else if ( strcmp ( "proc/meminfo", member ) == 0 )
        sosreport_analyzer_cfg->proc_meminfo.file_num = x; 
    else if ( strcmp ( "proc/net/dev", member ) == 0 )
        sosreport_analyzer_cfg->proc_net_dev.file_num = x; 
    else if ( strcmp ( "proc/net/sockstat", member ) == 0 )
        sosreport_analyzer_cfg->proc_net_sockstat.file_num = x; 
    else if ( strcmp ( "root/anaconda-ks.cfg", member ) == 0 )
        sosreport_analyzer_cfg->root_anaconda_ks_cfg.file_num = x; 
    else if ( strcmp ( "sos_commands/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_.file_num = x; 
    else if ( strcmp ( "sos_commands/abrt/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_abrt_.file_num = x; 
    else if ( strcmp ( "sos_commands/apache/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_apache_.file_num = x; 
    else if ( strcmp ( "sos_commands/auditd/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_auditd_.file_num = x; 
    else if ( strcmp ( "sos_commands/boot/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_boot_.file_num = x; 
    else if ( strcmp ( "sos_commands/devicemapper/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_devicemapper_.file_num = x; 
    else if ( strcmp ( "sos_commands/devices/udevadm_info_--export-db", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.file_num = x; 
    else if ( strcmp ( "sos_commands/dnf/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_dnf_.file_num = x; 
    else if ( strcmp ( "sos_commands/firewalld/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_firewalld_.file_num = x; 
    else if ( strcmp ( "sos_commands/ipmitool/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_ipmitool_.file_num = x; 
    else if ( strcmp ( "sos_commands/kernel/sysctl_-a", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.file_num = x; 
    else if ( strcmp ( "sos_commands/logs/journalctl_--no-pager", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.file_num = x; 
    else if ( strcmp ( "sos_commands/lvm2/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_lvm2_.file_num = x; 
    else if ( strcmp ( "sos_commands/memory/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_memory_.file_num = x; 
    else if ( strcmp ( "sos_commands/networking/ethtool_-S", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.file_num = x; 
    else if ( strcmp ( "sos_commands/networking/ethtool_-i", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.file_num = x; 
    else if ( strcmp ( "sos_commands/networking/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_networking_.file_num = x; 
    else if ( strcmp ( "sos_commands/networkmanager/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_networkmanager_.file_num = x; 
    else if ( strcmp ( "sos_commands/pam/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_pam_.file_num = x; 
    else if ( strcmp ( "sos_commands/sar/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_sar_.file_num = x; 
    else if ( strcmp ( "sos_commands/scsi/lsscsi", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.file_num = x; 
    else if ( strcmp ( "sos_commands/selinux/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_selinux_.file_num = x; 
    else if ( strcmp ( "sos_commands/usb/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_usb_.file_num = x; 
    else if ( strcmp ( "sos_commands/virsh/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_virsh_.file_num = x; 
    else if ( strcmp ( "sos_commands/yum/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_yum_.file_num = x; 
    else if ( strcmp ( "sos_commands/wireless/", member ) == 0 )
        sosreport_analyzer_cfg->sos_commands_wireless_.file_num = x; 
    else if ( strcmp ( "sys/module/", member ) == 0 )
        sosreport_analyzer_cfg->sys_module_.file_num = x; 
    else if ( strcmp ( "usr/", member ) == 0 )
        sosreport_analyzer_cfg->usr_.file_num = x; 
    else if ( strcmp ( "usr/lib/systemd/", member ) == 0 )
        sosreport_analyzer_cfg->usr_lib_systemd_.file_num = x; 
    else if ( strcmp ( "var/", member ) == 0 )
        sosreport_analyzer_cfg->var_.file_num = x; 
    else if ( strcmp ( "var/crash/", member ) == 0 )
        sosreport_analyzer_cfg->var_crash_.file_num = x; 
    else if ( strcmp ( "var/log/audit/", member ) == 0 )
        sosreport_analyzer_cfg->var_log_audit_.file_num = x; 
    else if ( strcmp ( "var/log/dmesg", member ) == 0 )
        sosreport_analyzer_cfg->var_log_dmesg.file_num = x; 
    else if ( strcmp ( "var/log/messages", member ) == 0 )
        sosreport_analyzer_cfg->var_log_messages.file_num = x; 
    else if ( strcmp ( "var/log/secure", member ) == 0 )
        sosreport_analyzer_cfg->var_log_secure.file_num = x; 
    else if ( strcmp ( "var/spool/cron/", member ) == 0 )
        sosreport_analyzer_cfg->var_spool_cron_.file_num = x; 

    return ( 0 );
}

int set_item_arr_string ( const char *member, int x, const char *item_name )
{
    if ( item_name == NULL )
        return ( 0 );
    if ( x > MAX_ITEM_NUMBERS )
        return ( 1 );
    if ( strcmp ( "df", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->df.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "date", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->date.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "dmidecode", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->dmidecode.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "free", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->free.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "hostname", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->hostname.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "installed-rpms", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->installed_rpms.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "ip_addr", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->ip_addr.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "last", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->last.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "lsb-release", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->lsb_release.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "lsmod", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->lsmod.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "lsof", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->lsof.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "lspci", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->lspci.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "ps", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->ps.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "route", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->route.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "netstat", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->netstat.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "uname", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->uname.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "uptime", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->uptime.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "vgdisplay", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->vgdisplay.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "boot/grub/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->mcinfo_boot_grub_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "cmdlog/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->mcinfo_cmdlog_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "dev/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->dev_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/NetworkManager/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_NetworkManager_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/audit/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_audit_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/anacrontab", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_anacrontab.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/crontab", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_crontab.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/cron.deny", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_cron_deny.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/cron.d/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_cron_d_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/cron.hourly/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_cron_hourly_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/cron.daily/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_cron_daily_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/cron.weekly/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_cron_weekly_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/cron.monthly/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_cron_monthly_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/default/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_default_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/dnf/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_dnf_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/firewalld/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_firewalld_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/host", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_host.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/httpd/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_httpd_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/kdump.conf", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_kdump_conf.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/logrotate.conf", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_logrotate_conf.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/logrotate.d/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_logrotate_d_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/lvm/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_lvm_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/modprobe.d/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_modprobe_d_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/nsswitch.conf", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_nsswitch_conf.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/pam.d/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_pam_d_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/pki/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_pki_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/rsyslog.conf", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_rsyslog_conf.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/sysconfig/network-scripts/ifcfg-", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/selinux/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_selinux_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/sysconfig/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_sysconfig_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/sysctl.conf", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_sysctl_conf.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/systemd/system/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_systemd_system_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/systemd/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_systemd_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/udev/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_udev_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/yum.conf", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_yum_conf.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/yum.repos.d/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_yum_repos_d_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/yum/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_yum_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "etc/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->etc_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "lib/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->lib_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "proc/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->proc_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "proc/cpuinfo", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->proc_cpuinfo.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "proc/interrupts", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->proc_interrupts.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "proc/meminfo", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->proc_meminfo.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "proc/net/dev", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->proc_net_dev.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "proc/net/sockstat", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->proc_net_sockstat.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "root/anaconda-ks.cfg", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->root_anaconda_ks_cfg.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/abrt/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_abrt_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/apache/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_apache_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/auditd/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_auditd_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/boot/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_boot_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/devicemapper/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_devicemapper_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/devices/udevadm_info_--export-db", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/dnf/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_dnf_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/firewalld/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_firewalld_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/ipmitool/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_ipmitool_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/kernel/sysctl_-a", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/logs/journalctl_--no-pager", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/lvm2/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_lvm2_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/memory/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_memory_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/networking/ethtool_-S", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/networking/ethtool_-i", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/networking/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_networking_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/networkmanager/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_networkmanager_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/pam/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_pam_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/sar/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_sar_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/scsi/lsscsi", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/selinux/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_selinux_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/usb/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_usb_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/virsh/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_virsh_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/yum/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_yum_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sos_commands/wireless/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sos_commands_wireless_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "sys/module/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->sys_module_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "usr/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->usr_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "usr/lib/systemd/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->usr_lib_systemd_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "var/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->var_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "var/crash/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->var_crash_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "var/log/audit/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->var_log_audit_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "var/log/dmesg", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->var_log_dmesg.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "var/log/messages", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->var_log_messages.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "var/log/secure", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->var_log_secure.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    else if ( strcmp ( "var/spool/cron/", member ) == 0 )
    {
        strncpy ( sosreport_analyzer_cfg->var_spool_cron_.item_names.item_name [ x ], item_name, MAX_ITEM_STRINGS );
        return ( 0 );
    }
    return ( 1 );
}

char *get_item_arr_string ( const char *member, int x )
{
    if ( strcmp ( "df", member ) == 0 )
        return sosreport_analyzer_cfg->df.item_names.item_name [ x ]; 
    else if ( strcmp ( "date", member ) == 0 )
        return sosreport_analyzer_cfg->date.item_names.item_name [ x ]; 
    else if ( strcmp ( "dmidecode", member ) == 0 )
        return sosreport_analyzer_cfg->dmidecode.item_names.item_name [ x ]; 
    else if ( strcmp ( "free", member ) == 0 )
        return sosreport_analyzer_cfg->free.item_names.item_name [ x ]; 
    else if ( strcmp ( "hostname", member ) == 0 )
        return sosreport_analyzer_cfg->hostname.item_names.item_name [ x ]; 
    else if ( strcmp ( "installed-rpms", member ) == 0 )
        return sosreport_analyzer_cfg->installed_rpms.item_names.item_name [ x ]; 
    else if ( strcmp ( "ip_addr", member ) == 0 )
        return sosreport_analyzer_cfg->ip_addr.item_names.item_name [ x ]; 
    else if ( strcmp ( "last", member ) == 0 )
        return sosreport_analyzer_cfg->last.item_names.item_name [ x ]; 
    else if ( strcmp ( "lsb-release", member ) == 0 )
        return sosreport_analyzer_cfg->lsb_release.item_names.item_name [ x ]; 
    else if ( strcmp ( "lsmod", member ) == 0 )
        return sosreport_analyzer_cfg->lsmod.item_names.item_name [ x ]; 
    else if ( strcmp ( "lsof", member ) == 0 )
        return sosreport_analyzer_cfg->lsof.item_names.item_name [ x ]; 
    else if ( strcmp ( "lspci", member ) == 0 )
        return sosreport_analyzer_cfg->lspci.item_names.item_name [ x ]; 
    else if ( strcmp ( "ps", member ) == 0 )
        return sosreport_analyzer_cfg->ps.item_names.item_name [ x ]; 
    else if ( strcmp ( "route", member ) == 0 )
        return sosreport_analyzer_cfg->route.item_names.item_name [ x ]; 
    else if ( strcmp ( "netstat", member ) == 0 )
        return sosreport_analyzer_cfg->netstat.item_names.item_name [ x ]; 
    else if ( strcmp ( "uname", member ) == 0 )
        return sosreport_analyzer_cfg->uname.item_names.item_name [ x ]; 
    else if ( strcmp ( "uptime", member ) == 0 )
        return sosreport_analyzer_cfg->uptime.item_names.item_name [ x ]; 
    else if ( strcmp ( "vgdisplay", member ) == 0 )
        return sosreport_analyzer_cfg->vgdisplay.item_names.item_name [ x ]; 
    else if ( strcmp ( "boot/grub/", member ) == 0 )
        return sosreport_analyzer_cfg->mcinfo_boot_grub_.item_names.item_name [ x ]; 
    else if ( strcmp ( "cmdlog/", member ) == 0 )
        return sosreport_analyzer_cfg->mcinfo_cmdlog_.item_names.item_name [ x ]; 
    else if ( strcmp ( "dev/", member ) == 0 )
        return sosreport_analyzer_cfg->dev_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/NetworkManager/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_NetworkManager_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/audit/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_audit_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/anacrontab", member ) == 0 )
        return sosreport_analyzer_cfg->etc_anacrontab.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/crontab", member ) == 0 )
        return sosreport_analyzer_cfg->etc_crontab.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/cron.deny", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_deny.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/cron.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_d_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/cron.hourly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_hourly_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/cron.daily/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_daily_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/cron.weekly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_weekly_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/cron.monthly/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_cron_monthly_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/default/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_default_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/dnf/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_dnf_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/firewalld/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_firewalld_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/host", member ) == 0 )
        return sosreport_analyzer_cfg->etc_host.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/httpd/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_httpd_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/kdump.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_kdump_conf.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/logrotate.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_logrotate_conf.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/logrotate.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_logrotate_d_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/lvm/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_lvm_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/modprobe.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_modprobe_d_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/nsswitch.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_nsswitch_conf.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/pam.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_pam_d_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/pki/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_pki_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/rsyslog.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_rsyslog_conf.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/selinux/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_selinux_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/sysconfig/network-scripts/ifcfg-", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/sysconfig/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysconfig_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/sysctl.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_sysctl_conf.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/systemd/system/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_systemd_system_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/systemd/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_systemd_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/udev/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_udev_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/yum.conf", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_conf.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/yum.repos.d/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_repos_d_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/yum/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_yum_.item_names.item_name [ x ]; 
    else if ( strcmp ( "etc/", member ) == 0 )
        return sosreport_analyzer_cfg->etc_.item_names.item_name [ x ]; 
    else if ( strcmp ( "lib/", member ) == 0 )
        return sosreport_analyzer_cfg->lib_.item_names.item_name [ x ]; 
    else if ( strcmp ( "proc/", member ) == 0 )
        return sosreport_analyzer_cfg->proc_.item_names.item_name [ x ]; 
    else if ( strcmp ( "proc/cpuinfo", member ) == 0 )
        return sosreport_analyzer_cfg->proc_cpuinfo.item_names.item_name [ x ]; 
    else if ( strcmp ( "proc/interrupts", member ) == 0 )
        return sosreport_analyzer_cfg->proc_interrupts.item_names.item_name [ x ]; 
    else if ( strcmp ( "proc/meminfo", member ) == 0 )
        return sosreport_analyzer_cfg->proc_meminfo.item_names.item_name [ x ]; 
    else if ( strcmp ( "proc/net/dev", member ) == 0 )
        return sosreport_analyzer_cfg->proc_net_dev.item_names.item_name [ x ]; 
    else if ( strcmp ( "proc/net/sockstat", member ) == 0 )
        return sosreport_analyzer_cfg->proc_net_sockstat.item_names.item_name [ x ]; 
    else if ( strcmp ( "root/anaconda-ks.cfg", member ) == 0 )
        return sosreport_analyzer_cfg->root_anaconda_ks_cfg.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/abrt/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_abrt_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/apache/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_apache_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/auditd/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_auditd_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/boot/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_boot_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/devicemapper/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_devicemapper_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/devices/udevadm_info_--export-db", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/dnf/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_dnf_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/firewalld/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_firewalld_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/ipmitool/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_ipmitool_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/kernel/sysctl_-a", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/logs/journalctl_--no-pager", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/lvm2/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_lvm2_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/memory/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_memory_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/networking/ethtool_-S", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/networking/ethtool_-i", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/networking/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networking_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/networkmanager/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_networkmanager_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/pam/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_pam_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/sar/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_sar_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/scsi/lsscsi", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/selinux/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_selinux_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/usb/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_usb_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/virsh/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_virsh_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/yum/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_yum_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sos_commands/wireless/", member ) == 0 )
        return sosreport_analyzer_cfg->sos_commands_wireless_.item_names.item_name [ x ]; 
    else if ( strcmp ( "sys/module/", member ) == 0 )
        return sosreport_analyzer_cfg->sys_module_.item_names.item_name [ x ]; 
    else if ( strcmp ( "usr/", member ) == 0 )
        return sosreport_analyzer_cfg->usr_.item_names.item_name [ x ]; 
    else if ( strcmp ( "usr/lib/systemd/", member ) == 0 )
        return sosreport_analyzer_cfg->usr_lib_systemd_.item_names.item_name [ x ]; 
    else if ( strcmp ( "var/", member ) == 0 )
        return sosreport_analyzer_cfg->var_.item_names.item_name [ x ]; 
    else if ( strcmp ( "var/crash/", member ) == 0 )
        return sosreport_analyzer_cfg->var_crash_.item_names.item_name [ x ]; 
    else if ( strcmp ( "var/log/audit/", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_audit_.item_names.item_name [ x ]; 
    else if ( strcmp ( "var/log/dmesg", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_dmesg.item_names.item_name [ x ]; 
    else if ( strcmp ( "var/log/messages", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_messages.item_names.item_name [ x ]; 
    else if ( strcmp ( "var/log/secure", member ) == 0 )
        return sosreport_analyzer_cfg->var_log_secure.item_names.item_name [ x ]; 
    else if ( strcmp ( "var/spool/cron/", member ) == 0 )
        return sosreport_analyzer_cfg->var_spool_cron_.item_names.item_name [ x ]; 
    return "skip";
}

int member_item_exists ( const char *member )
{
    if ( strcmp ( "df", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->df.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "date", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->date.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "dmidecode", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->dmidecode.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "free", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->free.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "hostname", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->hostname.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "installed-rpms", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->installed_rpms.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "ip_addr", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->ip_addr.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "last", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->last.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "lsb-release", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->lsb_release.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "lsmod", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->lsmod.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "lsof", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->lsof.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "lspci", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->lspci.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "ps", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->ps.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "route", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->route.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "netstat", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->netstat.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "uname", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->uname.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "uptime", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->uptime.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "vgdisplay", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->vgdisplay.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "boot/grub/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->mcinfo_boot_grub_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "cmdlog/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->mcinfo_cmdlog_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "dev/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->dev_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/NetworkManager/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_NetworkManager_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/audit/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_audit_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/anacrontab", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_anacrontab.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/crontab", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_crontab.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/cron.deny", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_cron_deny.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/cron.d/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_cron_d_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/cron.hourly/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_cron_hourly_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/cron.daily/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_cron_daily_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/cron.weekly/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_cron_weekly_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/cron.monthly/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_cron_monthly_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/default/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_default_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/dnf/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_dnf_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/firewalld/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_firewalld_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/host", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_host.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/httpd/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_httpd_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/kdump.conf", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_kdump_conf.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/logrotate.conf", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_logrotate_conf.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/logrotate.d/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_logrotate_d_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/lvm/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_lvm_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/modprobe.d/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_modprobe_d_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/nsswitch.conf", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_nsswitch_conf.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/pam.d/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_pam_d_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/pki/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_pki_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/rsyslog.conf", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_rsyslog_conf.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/selinux/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_selinux_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/sysconfig/network-scripts/ifcfg-", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/sysconfig/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_sysconfig_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/sysctl.conf", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_sysctl_conf.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/systemd/system/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_systemd_system_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/systemd/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_systemd_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/udev/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_udev_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/yum.conf", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_yum_conf.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/yum.repos.d/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_yum_repos_d_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/yum/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_yum_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "etc/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->etc_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "lib/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->lib_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "proc/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->proc_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "proc/cpuinfo", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->proc_cpuinfo.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "proc/interrupts", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->proc_interrupts.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "proc/meminfo", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->proc_meminfo.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "proc/net/dev", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->proc_net_dev.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "proc/net/sockstat", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->proc_net_sockstat.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "root/anaconda-ks.cfg", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->root_anaconda_ks_cfg.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/abrt/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_abrt_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/apache/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_apache_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/auditd/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_auditd_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/boot/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_boot_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/devicemapper/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_devicemapper_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/devices/udevadm_info_--export-db", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/dnf/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_dnf_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/firewalld/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_firewalld_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/ipmitool/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_ipmitool_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/kernel/sysctl_-a", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/logs/journalctl_--no-pager", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/lvm2/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_lvm2_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/memory/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_memory_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/networking/ethtool_-S", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/networking/ethtool_-i", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/networking/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/networkmanager/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_networkmanager_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/pam/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_pam_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/sar/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_sar_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/scsi/lsscsi", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/selinux/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_selinux_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/usb/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_usb_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/virsh/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_virsh_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/yum/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_yum_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sos_commands/wireless/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sos_commands_wireless_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "sys/module/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->sys_module_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "usr/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->usr_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "usr/lib/systemd/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->usr_lib_systemd_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "var/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->var_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "var/crash/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->var_crash_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "var/log/audit/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->var_log_audit_.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "var/log/dmesg", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->var_log_dmesg.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "var/log/messages", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->var_log_messages.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "var/log/secure", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->var_log_secure.member, "" ) != 0 )
            return ( 0 );
    }
    else if ( strcmp ( "var/spool/cron/", member ) == 0 )
    {
        if ( strcmp ( sosreport_analyzer_cfg->var_spool_cron_.member, "" ) != 0 )
            return ( 0 );
    }
    else
        return ( 1 );
    return ( 1 );
}
