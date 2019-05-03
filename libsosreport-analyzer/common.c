/*
 *  common.c - common functions 
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

#include <unistd.h> /* should be above for declaring macro */
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include "../common/global.c"
#include "common.h"
#include "cfg.h"
#include "setter_getter.h"

/* sos_dir_file_obj */
struct dir_file_name sos_dir_file_obj_raw = 
    {{ "test.txt", "test.txt", "test.txt", "test.txt" }};

/* sos_header_obj */
struct line_data sos_header_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_general_obj */
struct line_data sos_subtitle_general_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_cpu_obj */
struct line_data sos_subtitle_cpu_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_module_obj */
struct line_data sos_subtitle_module_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_device_obj */
struct line_data sos_subtitle_device_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_disk_usage_obj */
struct line_data sos_subtitle_disk_usage_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_memory_usage_obj */
struct line_data sos_subtitle_memory_usage_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_networking_obj */
struct line_data sos_subtitle_networking_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_process_obj */
struct line_data sos_subtitle_process_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_virtualization_obj */
struct line_data sos_subtitle_virtualization_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_files_obj */
struct line_data sos_subtitle_files_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_systemd_obj */
struct line_data sos_subtitle_systemd_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_security_obj */
struct line_data sos_subtitle_security_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_kernel_obj */
struct line_data sos_subtitle_kernel_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_yum_obj */
struct line_data sos_subtitle_yum_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_login_obj */
struct line_data sos_subtitle_login_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_cron_obj */
struct line_data sos_subtitle_cron_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_logrotate_obj */
struct line_data sos_subtitle_logrotate_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_logs_and_journals_obj */
struct line_data sos_subtitle_logs_and_journals_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_httpd_obj */
struct line_data sos_subtitle_httpd_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_subtitle_others_obj */
struct line_data sos_subtitle_others_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* line_obj */
struct line_data sos_line_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* tail_obj */
struct line_data sos_tail_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* mcinfo_boot_grub__obj */
struct line_data mcinfo_boot_grub__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* mcinfo_cmdlog__obj */
struct line_data mcinfo_cmdlog__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_pki__obj */
struct line_data etc_pki__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_cron_d__obj */
struct line_data etc_cron_d__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_sysconfig_network_scripts_ifcfg__obj */
struct line_data etc_sysconfig_network_scripts_ifcfg__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_log_messages_obj */
struct line_data var_log_messages_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_log_secure_obj */
struct line_data var_log_secure_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_log_audit__obj */
struct line_data var_log_audit__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_logs_journalctl___no_pager_obj */
struct line_data sos_commands_logs_journalctl___no_pager_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_networking_ethtool__S_obj */
struct line_data sos_commands_networking_ethtool__S_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_networking_ethtool__i_obj */
struct line_data sos_commands_networking_ethtool__i_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_boot__obj */
struct line_data sos_commands_boot__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_httpd__obj */
struct line_data etc_httpd__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* proc__obj */
struct line_data proc__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_crash__obj */
struct line_data var_crash__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_default__obj */
struct line_data etc_default__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_logrotate_d__obj */
struct line_data etc_logrotate_d__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_modprobe_d__obj */
struct line_data etc_modprobe_d__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_host_obj */
struct line_data etc_host_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_udev__obj */
struct line_data etc_udev__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_yum_repos_d__obj */
struct line_data etc_yum_repos_d__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_systemd_system__obj */
struct line_data etc_systemd_system__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_systemd__obj */
struct line_data etc_systemd__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* usr_lib_systemd__obj */
struct line_data usr_lib_systemd__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_sar__obj */
struct line_data sos_commands_sar__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_virsh__obj */
struct line_data sos_commands_virsh__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_usb__obj */
struct line_data sos_commands_usb__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* lib__obj */
struct line_data lib__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc__obj */
struct line_data etc__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_networking__obj */
struct line_data sos_commands_networking__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* dev__obj */
struct line_data dev__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* usr__obj */
struct line_data usr__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var__obj */
struct line_data var__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* var_spool_cron__obj */
struct line_data var_spool_cron__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_obj */
struct line_data sos_commands_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_abrt__obj */
struct line_data sos_commands_abrt__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sys_module__obj */
struct line_data sys_module__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_pam_d__obj */
struct line_data etc_pam_d__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_pam__obj */
struct line_data sos_commands_pam__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_apache__obj */
struct line_data sos_commands_apache__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_audit__obj */
struct line_data etc_audit__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_auditd__obj */
struct line_data sos_commands_auditd__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_memory__obj */
struct line_data sos_commands_memory__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_firewalld__obj */
struct line_data etc_firewalld__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_firewalld__obj */
struct line_data sos_commands_firewalld__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_devicemapper__obj */
struct line_data sos_commands_devicemapper__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_sysconfig__obj */
struct line_data etc_sysconfig__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_selinux__obj */
struct line_data etc_selinux__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_selinux__obj */
struct line_data sos_commands_selinux__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_yum__obj */
struct line_data etc_yum__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_yum__obj */
struct line_data sos_commands_yum__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_dnf__obj */
struct line_data etc_dnf__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_dnf__obj */
struct line_data sos_commands_dnf__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_cron_hourly__obj */
struct line_data etc_cron_hourly__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_cron_daily__obj */
struct line_data etc_cron_daily__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_cron_weekly__obj */
struct line_data etc_cron_weekly__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_cron_monthly__obj */
struct line_data etc_cron_monthly__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_networkmanager__obj */
struct line_data sos_commands_networkmanager__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* etc_networkmanager__obj */
struct line_data etc_networkmanager__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* sos_commands_ipmitool__obj */
struct line_data sos_commands_ipmitool__obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_1_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_2_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_3_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_4_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_5_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_6_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_7_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_8_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_9_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_10_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_11_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_12_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_13_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_14_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_15_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_16_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_17_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_18_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_19_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_20_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_21_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_22_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_23_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_24_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_25_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_26_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_27_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_28_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_29_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_30_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_31_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_32_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_33_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_34_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_35_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_36_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_37_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_38_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_39_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_40_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_41_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_42_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_43_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_44_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_45_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_46_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_47_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_48_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_49_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_50_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_51_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_52_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_53_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_54_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_55_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_56_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_57_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_58_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_59_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

struct line_data tmp_60_obj_raw =
    {
        "\0", /* each line */
        NULL /* next pointer */
    };

/* making pointers to the structs */
struct dir_file_name *sos_dir_file_obj = &sos_dir_file_obj_raw;
struct line_data *sos_header_obj = &sos_header_obj_raw;
struct line_data *sos_subtitle_general_obj = &sos_subtitle_general_obj_raw;
struct line_data *sos_subtitle_cpu_obj = &sos_subtitle_cpu_obj_raw;
struct line_data *sos_subtitle_module_obj = &sos_subtitle_module_obj_raw;
struct line_data *sos_subtitle_device_obj = &sos_subtitle_device_obj_raw;
struct line_data *sos_subtitle_disk_usage_obj = &sos_subtitle_disk_usage_obj_raw;
struct line_data *sos_subtitle_memory_usage_obj = &sos_subtitle_memory_usage_obj_raw;
struct line_data *sos_subtitle_networking_obj = &sos_subtitle_networking_obj_raw;
struct line_data *sos_subtitle_process_obj = &sos_subtitle_process_obj_raw;
struct line_data *sos_subtitle_virtualization_obj = &sos_subtitle_virtualization_obj_raw;
struct line_data *sos_subtitle_files_obj = &sos_subtitle_files_obj_raw;
struct line_data *sos_subtitle_systemd_obj = &sos_subtitle_systemd_obj_raw;
struct line_data *sos_subtitle_security_obj = &sos_subtitle_security_obj_raw;
struct line_data *sos_subtitle_kernel_obj = &sos_subtitle_kernel_obj_raw;
struct line_data *sos_subtitle_yum_obj = &sos_subtitle_yum_obj_raw;
struct line_data *sos_subtitle_login_obj = &sos_subtitle_login_obj_raw;
struct line_data *sos_subtitle_cron_obj = &sos_subtitle_cron_obj_raw;
struct line_data *sos_subtitle_logrotate_obj = &sos_subtitle_logrotate_obj_raw;
struct line_data *sos_subtitle_logs_and_journals_obj = &sos_subtitle_logs_and_journals_obj_raw;
struct line_data *sos_subtitle_httpd_obj = &sos_subtitle_httpd_obj_raw;
struct line_data *sos_subtitle_others_obj = &sos_subtitle_others_obj_raw;
struct line_data *sos_line_obj = &sos_line_obj_raw;
struct line_data *sos_tail_obj = &sos_tail_obj_raw;

struct line_data *tmp_1_obj = &tmp_1_obj_raw;
struct line_data *tmp_2_obj = &tmp_2_obj_raw;
struct line_data *tmp_3_obj = &tmp_3_obj_raw;
struct line_data *tmp_4_obj = &tmp_4_obj_raw;
struct line_data *tmp_5_obj = &tmp_5_obj_raw;
struct line_data *tmp_6_obj = &tmp_6_obj_raw;
struct line_data *tmp_7_obj = &tmp_7_obj_raw;
struct line_data *tmp_8_obj = &tmp_8_obj_raw;
struct line_data *tmp_9_obj = &tmp_9_obj_raw;
struct line_data *tmp_10_obj = &tmp_10_obj_raw;
struct line_data *tmp_11_obj = &tmp_11_obj_raw;
struct line_data *tmp_12_obj = &tmp_12_obj_raw;
struct line_data *tmp_13_obj = &tmp_13_obj_raw;
struct line_data *tmp_14_obj = &tmp_14_obj_raw;
struct line_data *tmp_15_obj = &tmp_15_obj_raw;
struct line_data *tmp_16_obj = &tmp_16_obj_raw;
struct line_data *tmp_17_obj = &tmp_17_obj_raw;
struct line_data *tmp_18_obj = &tmp_18_obj_raw;
struct line_data *tmp_19_obj = &tmp_19_obj_raw;
struct line_data *tmp_20_obj = &tmp_20_obj_raw;
struct line_data *tmp_21_obj = &tmp_21_obj_raw;
struct line_data *tmp_22_obj = &tmp_22_obj_raw;
struct line_data *tmp_23_obj = &tmp_23_obj_raw;
struct line_data *tmp_24_obj = &tmp_24_obj_raw;
struct line_data *tmp_25_obj = &tmp_25_obj_raw;
struct line_data *tmp_26_obj = &tmp_26_obj_raw;
struct line_data *tmp_27_obj = &tmp_27_obj_raw;
struct line_data *tmp_28_obj = &tmp_28_obj_raw;
struct line_data *tmp_29_obj = &tmp_29_obj_raw;
struct line_data *tmp_30_obj = &tmp_30_obj_raw;
struct line_data *tmp_31_obj = &tmp_31_obj_raw;
struct line_data *tmp_32_obj = &tmp_32_obj_raw;
struct line_data *tmp_33_obj = &tmp_33_obj_raw;
struct line_data *tmp_34_obj = &tmp_34_obj_raw;
struct line_data *tmp_35_obj = &tmp_35_obj_raw;
struct line_data *tmp_36_obj = &tmp_36_obj_raw;
struct line_data *tmp_37_obj = &tmp_37_obj_raw;
struct line_data *tmp_38_obj = &tmp_38_obj_raw;
struct line_data *tmp_39_obj = &tmp_39_obj_raw;
struct line_data *tmp_40_obj = &tmp_40_obj_raw;
struct line_data *tmp_41_obj = &tmp_41_obj_raw;
struct line_data *tmp_42_obj = &tmp_42_obj_raw;
struct line_data *tmp_43_obj = &tmp_43_obj_raw;
struct line_data *tmp_44_obj = &tmp_44_obj_raw;
struct line_data *tmp_45_obj = &tmp_45_obj_raw;
struct line_data *tmp_46_obj = &tmp_46_obj_raw;
struct line_data *tmp_47_obj = &tmp_47_obj_raw;
struct line_data *tmp_48_obj = &tmp_48_obj_raw;
struct line_data *tmp_49_obj = &tmp_49_obj_raw;
struct line_data *tmp_50_obj = &tmp_50_obj_raw;
struct line_data *tmp_51_obj = &tmp_51_obj_raw;
struct line_data *tmp_52_obj = &tmp_52_obj_raw;
struct line_data *tmp_53_obj = &tmp_53_obj_raw;
struct line_data *tmp_54_obj = &tmp_54_obj_raw;
struct line_data *tmp_55_obj = &tmp_55_obj_raw;
struct line_data *tmp_56_obj = &tmp_56_obj_raw;
struct line_data *tmp_57_obj = &tmp_57_obj_raw;
struct line_data *tmp_58_obj = &tmp_58_obj_raw;
struct line_data *tmp_59_obj = &tmp_59_obj_raw;
struct line_data *tmp_60_obj = &tmp_60_obj_raw;

struct line_data *mcinfo_boot_grub__obj = &mcinfo_boot_grub__obj_raw;
struct line_data *mcinfo_cmdlog__obj = &mcinfo_cmdlog__obj_raw;
struct line_data *etc_pki__obj = &etc_pki__obj_raw;
struct line_data *etc_cron_d__obj = &etc_cron_d__obj_raw;
struct line_data *etc_sysconfig_network_scripts_ifcfg__obj = &etc_sysconfig_network_scripts_ifcfg__obj_raw;
struct line_data *var_log_messages_obj = &var_log_messages_obj_raw;
struct line_data *var_log_secure_obj = &var_log_secure_obj_raw;
struct line_data *var_log_audit__obj = &var_log_audit__obj_raw;
struct line_data *sos_commands_logs_journalctl___no_pager_obj = &sos_commands_logs_journalctl___no_pager_obj_raw;
struct line_data *sos_commands_networking_ethtool__S_obj = &sos_commands_networking_ethtool__S_obj_raw;
struct line_data *sos_commands_networking_ethtool__i_obj = &sos_commands_networking_ethtool__i_obj_raw;
struct line_data *sos_commands_boot__obj = &sos_commands_boot__obj_raw;
struct line_data *etc_httpd__obj = &etc_httpd__obj_raw;
struct line_data *proc__obj = &proc__obj_raw;
struct line_data *var_crash__obj = &var_crash__obj_raw;
struct line_data *etc_default__obj = &etc_default__obj_raw;
struct line_data *etc_logrotate_d__obj = &etc_logrotate_d__obj_raw;
struct line_data *etc_modprobe_d__obj = &etc_modprobe_d__obj_raw;
struct line_data *etc_host_obj = &etc_host_obj_raw;
struct line_data *etc_udev__obj = &etc_udev__obj_raw;
struct line_data *etc_yum_repos_d__obj = &etc_yum_repos_d__obj_raw;
struct line_data *etc_systemd_system__obj = &etc_systemd_system__obj_raw;
struct line_data *etc_systemd__obj = &etc_systemd__obj_raw;
struct line_data *usr_lib_systemd__obj = &usr_lib_systemd__obj_raw;
struct line_data *sos_commands_sar__obj = &sos_commands_sar__obj_raw;
struct line_data *sos_commands_virsh__obj = &sos_commands_virsh__obj_raw;
struct line_data *sos_commands_usb__obj = &sos_commands_usb__obj_raw;
struct line_data *lib__obj = &lib__obj_raw;
struct line_data *etc__obj = &etc__obj_raw;
struct line_data *sos_commands_networking__obj = &sos_commands_networking__obj_raw;
struct line_data *dev__obj = &dev__obj_raw;
struct line_data *usr__obj = &usr__obj_raw;
struct line_data *var__obj = &var__obj_raw;
struct line_data *sos_commands_obj = &sos_commands_obj_raw;
struct line_data *var_spool_cron__obj = &var_spool_cron__obj_raw;
struct line_data *sos_commands_abrt__obj = &sos_commands_abrt__obj_raw;
struct line_data *sys_module__obj = &sys_module__obj_raw;
struct line_data *etc_pam_d__obj = &etc_pam_d__obj_raw;
struct line_data *sos_commands_pam__obj = &sos_commands_pam__obj_raw;
struct line_data *sos_commands_apache__obj = &sos_commands_apache__obj_raw;
struct line_data *etc_audit__obj = &etc_audit__obj_raw;
struct line_data *sos_commands_auditd__obj = &sos_commands_auditd__obj_raw;
struct line_data *sos_commands_memory__obj = &sos_commands_memory__obj_raw;
struct line_data *etc_firewalld__obj = &etc_firewalld__obj_raw;
struct line_data *sos_commands_firewalld__obj = &sos_commands_firewalld__obj_raw;
struct line_data *sos_commands_devicemapper__obj = &sos_commands_devicemapper__obj_raw;
struct line_data *etc_sysconfig__obj = &etc_firewalld__obj_raw;
struct line_data *etc_selinux__obj = &etc_selinux__obj_raw;
struct line_data *sos_commands_selinux__obj = &sos_commands_selinux__obj_raw;
struct line_data *etc_yum__obj = &etc_yum__obj_raw;
struct line_data *sos_commands_yum__obj = &sos_commands_yum__obj_raw;
struct line_data *etc_dnf__obj = &etc_dnf__obj_raw;
struct line_data *sos_commands_dnf__obj = &sos_commands_dnf__obj_raw;
struct line_data *etc_cron_hourly__obj = &etc_cron_hourly__obj_raw;
struct line_data *etc_cron_daily__obj = &etc_cron_daily__obj_raw;
struct line_data *etc_cron_weekly__obj = &etc_cron_weekly__obj_raw;
struct line_data *etc_cron_monthly__obj = &etc_cron_monthly__obj_raw;
struct line_data *sos_commands_networkmanager__obj = &sos_commands_networkmanager__obj_raw;
struct line_data *etc_networkmanager__obj = &etc_networkmanager__obj_raw;
struct line_data *sos_commands_ipmitool__obj = &sos_commands_ipmitool__obj_raw;

/* in near future, these should be replaced with structs in cfg.h */
char *str_arr_boot_grub [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_cmdlog [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_pki [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_cron_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_ifcfg [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_log_messages [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_log_secure [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_log_audit [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_logs_journalctl [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_ethtool_S [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_ethtool_i [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_boot [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_httpd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_proc [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_crash [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_default [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_logrotate_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_modprobe_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_host [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_udev [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_yum_repos_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_systemd_system [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_systemd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_usr_lib_systemd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_sar [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_virsh [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_usb [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_lib [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_networking [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_dev [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_usr [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_var_spool_cron [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_abrt [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sys_module [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_pam_d [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_pam [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_apache [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_audit [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_auditd [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_memory [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_firewalld [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_firewalld [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_devicemapper [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_sysconfig [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_selinux [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_selinux [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_yum [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_yum [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_dnf [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_dnf [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_cron_hourly [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_cron_daily [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_cron_weekly [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_cron_monthly [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_networkmanager [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_etc_networkmanager [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];
char *str_arr_sos_commands_ipmitool [ MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR ];

int read_analyze_dir ( const char *member, const char *dname, int recursive )
{
    DIR *dir = NULL;
    struct dirent *dp;
    int str_len = 0;
    int str_len_fname_part = 0;
    int str_len_dname_full = 0;
    char *fname_part, *dname_full;
    char full_path [ MAX_LINE_LENGTH ];  
    char read_path [ MAX_LINE_LENGTH ];  
    char str_ret [ MAX_LINE_LENGTH ];  
    char fname_part_path [ MAX_LINE_LENGTH ];  

    memset ( full_path, '\0', sizeof ( full_path ) ); 
    memset ( read_path, '\0', sizeof ( read_path ) ); 
    memset ( str_orig, '\0', sizeof ( str_orig ) ); 
    memset ( fname_part_path, '\0', sizeof ( fname_part_path ) ); 
    snprintf (full_path, MAX_LINE_LENGTH, "%s/%s", dname, member );
    str_len = ( int ) strlen ( full_path );
    if ( str_len <= 0 )
    {
        printf("Path 1 is too short (%s): %d %s\n",full_path, str_len, strerror(errno));
        free_sosreport_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    full_path [ str_len ] = '\0';
    strcpy ( str_orig, full_path );

    fname_part = cut_str_from_the_last_slash ( reverse_the_string ( full_path, str_len ), str_len, str_ret );

    snprintf (fname_part_path, MAX_LINE_LENGTH, "%s", fname_part );
    str_len_fname_part = ( int ) strlen ( fname_part );
    str_len_dname_full = str_len - str_len_fname_part;
    if ( str_len_dname_full <= 0 ) 
    {
        printf("Path 2 is too short %d %s\n",str_len_dname_full, strerror(errno));
        free_sosreport_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }

    if ( recursive == 0 )
        dname_full = cut_str_by_the_last_slash ( full_path, str_len_dname_full );
    else
        dname_full = ( char * ) dname;

    int var_crash_exists = 1; 

    if ( dname_full != NULL )
    {
        /* if open directory fails, exit with error message,
         * and print that the member should be set to 'skip'.
         */
        if ( ( dir = opendir ( dname_full ) ) == NULL ) 
        {
            printf("can't open directory (%s): %s\n",dname_full,strerror(errno));
            printf("You should set 'skip' to %s in conf file.\n",member);
            if ( strcmp ( member, "var/crash/" ) == 0 )
            {
                var_crash_exists = 0;                
                puts("I skip 'var/crash/' automatically.");
                puts("Do not set 'skip' to member 'var/crash/'.");
            }
            else
            {
                printf("Skip '%s' and go on.\n",member);
                /* free_sosreport_analyzer_obj ( ); */
                return ( 0 );
                /* exit ( EXIT_FAILURE ); */
            }
        }
    }
    char *str;
    int i = 0;
    /* limit of fname_part files to be analyzed */
    int str_arr_valid_size = 0;

    /* read from directory and set in an array */
    if ( var_crash_exists == 1 )
    {
        for ( dp = readdir ( dir ),i = 0; dp != NULL; dp = readdir ( dir ) )
        {
            char full_path_plus_str [ MAX_LINE_LENGTH ];  
            char filename [ MAX_LINE_LENGTH ];  
            memset ( full_path_plus_str, '\0', sizeof ( full_path_plus_str ) ); 
            memset ( filename, '\0', sizeof ( filename ) ); 

            str = dp->d_name;

            if ( ( dp->d_type != DT_REG ) && ( dp->d_type != DT_DIR ) )
                continue;

            /*###FIX ME
             * proc/kallsyms is a big file, so...
             * journal... is a big file, so...
             * cil or hll... is selinux stuff and human can't read, so...
             * messages* should be read by other member , so...
             * others have big one, compressed or selinux modules.
             * in proc/ there are some files which have only write permissions and couldn't be read.
             * file sos_commands/networking/ethtool_-d* is sometimes too big.
             *
             * we should check file with a function and if the file is too big, skip it. 
             * Now, if file size is over 50Mbytes, skip the file.
             */
            snprintf (filename, MAX_LINE_LENGTH, "%s%s", dname_full, str );
            struct stat st;
            stat(filename, &st);

            if ( access ( str, R_OK ) == 0 )
                continue;

            int size = 0;
            size = st.st_size;

            if ( (  size == 0 ) || ( size > MAX_ANALYZE_FILE_SIZE ) )
                continue;

            if ( ( ( strcmp ( member, "cmdlog/" ) == 0 ) && ( strstr ( str, "verbose" ) != NULL ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( ( strstr ( str, "cil" ) != NULL ) || ( strstr ( str, "hll" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( ( strstr ( str, ".bin" ) != NULL ) || ( strstr ( str, ".kern" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( ( strstr ( str, ".db" ) != NULL ) || ( strstr ( str, "policy." ) != NULL ) ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( ( strstr ( str, "lang_ext" ) != NULL ) || ( strstr ( str, ".pp" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "etc/" ) == 0 ) && ( strstr ( str, "commit_num" ) != NULL ) ) ||
                ( ( strcmp ( member, "proc/" ) == 0 ) && ( ( strstr ( str, "register" ) != NULL ) || ( strstr ( str, "compact_memory" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "proc/" ) == 0 ) && ( ( strstr ( str, "flush" ) != NULL ) || ( strstr ( str, "kallsyms" ) != NULL ) ) ) ||
                ( ( strcmp ( member, "proc/" ) == 0 ) && ( ( strstr ( str, "purge" ) != NULL ) || ( strstr ( str, "rebase" ) != NULL ) ) )||
                ( ( strcmp ( member, "var/log/messages" ) == 0 ) && ( strstr ( str, ".gz" ) != NULL ) ) || 
                ( ( strcmp ( member, "var/log/secure" ) == 0 ) && ( strstr ( str, ".gz" ) != NULL ) ) || 
                ( ( strcmp ( member, "var/" ) == 0 ) && (  strstr ( str, "journal" ) != NULL ) ) || 
                ( ( strcmp ( member, "var/") == 0 ) && ( strstr ( str, "messages" ) != NULL ) ) ||
                ( ( strcmp ( member, "var/") == 0 ) && ( ( strstr ( str, "sa" ) != NULL ) || ( strstr ( str, "crash" ) != NULL ) ) ) || 
                ( ( strcmp ( member, "var/") == 0 ) && ( strstr ( str, "nova" ) != NULL ) ) ||
                ( ( strcmp ( member, "sos_commands/networking/") == 0 ) && ( strstr ( str, "ethtool_-d" ) != NULL ) ) || 
                ( ( strcmp ( member, "sos_commands/") == 0 ) && ( strstr ( str, "journalctl" ) != NULL ) ) )
                continue;

            /* Here, we try to read files recursively */
            if ( (
                ( strcmp ( member, "dev/" ) == 0 ) || 
                ( strcmp ( member, "etc/dnf/" ) == 0 ) ||
                ( strcmp ( member, "etc/firewalld/" ) == 0 ) ||
                ( strcmp ( member, "etc/pki/" ) == 0 ) || 
                ( strcmp ( member, "etc/httpd/" ) == 0 ) ||
                ( strcmp ( member, "etc/selinux/" ) == 0 ) ||
                ( strcmp ( member, "etc/systemd/system/" ) == 0 ) ||
                ( strcmp ( member, "etc/yum/" ) == 0 ) ||
                ( strcmp ( member, "etc/udev/" ) == 0 ) ||
                ( strcmp ( member, "etc/" ) == 0 ) || 
                ( strcmp ( member, "lib/" ) == 0 ) ||
                ( strcmp ( member, "proc/" ) == 0 ) ||
                ( strcmp ( member, "sos_commands/networking/" ) == 0 ) ||
                ( strcmp ( member, "sos_commands/" ) == 0 ) ||
                ( strcmp ( member, "sys/module/" ) == 0 ) ||
                ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) || 
                ( strcmp ( member, "usr/" ) == 0 ) || 
                ( strcmp ( member, "var/crash/" ) == 0 ) ||
                ( strcmp ( member, "var/" ) == 0 ) ) 
                &&
                /* try to read all files in the directory */
                ( ( recursive == 0 ) || ( recursive == 1 ) )
            )
            {
                if ( dp->d_type == DT_DIR )
                {
                    snprintf (full_path_plus_str, MAX_LINE_LENGTH, "%s%s/", dname_full, str );
                    /* call myself and read files in the directory */
                    printf("Reading files in the directory '%s'\n",full_path_plus_str);
                    read_analyze_dir ( member, full_path_plus_str, 1 );
                }
            }
            /* Here are members of above and has files in the rootdir of itself
             *
             * do read etc/dnf/'s rootdir so, no need here
             * do read etc/systemd/system/'s rootdir so, no need here
             * do read etc/firewalld/'s rootdir so, no need here
             * do read etc/selinux/'s rootdir so, no need here
             * do read etc/sysconfig/'s rootdir so, no need here
             * do read etc/yum/'s rootdir so, no need here
             * do read etc/'s rootdir so, no need here
             * do read proc/'s rootdir so, no need here
             * do read sos_commands/networking/'s rootdir so, no need here
             */
            if ( (
                ( strcmp ( member, "dev/" ) == 0 ) || 
                ( strcmp ( member, "etc/httpd/" ) == 0 ) || 
                ( strcmp ( member, "etc/pki/" ) == 0 ) || 
                ( strcmp ( member, "etc/udev/" ) == 0 ) ||
                ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) || 
                ( strcmp ( member, "lib/" ) == 0 ) ||
                ( strcmp ( member, "sos_commands/" ) == 0 ) ||
                ( strcmp ( member, "sys/module/" ) == 0 ) ||
                ( strcmp ( member, "usr/" ) == 0 ) || 
                ( strcmp ( member, "var/crash/" ) == 0 ) || 
                ( strcmp ( member, "var/" ) == 0 ) )
                &&
                ( recursive == 0 )
                )
                continue;

            /*
             *  find files with name fname_part 
             */
            if ( strstr ( str, fname_part ) != NULL )
            {
                /* so, only fname_part files will remain */
                snprintf (read_path, MAX_LINE_LENGTH, "%s%s", dname_full, str );

                /* note that for the same directory, longest one will match first */
                if ( strstr ( read_path, "/boot/grub/" ) != 0 )
                    append_list ( &tmp_1_obj, read_path );
                else if ( strstr ( read_path, "/cmdlog/" ) != 0 )
                    append_list ( &tmp_2_obj, read_path );
                else if ( strstr ( read_path, "/etc/NetworkManager/" ) != 0 )
                    append_list ( &tmp_59_obj, read_path );
                else if ( strstr ( read_path, "/etc/audit/" ) != 0 )
                    append_list ( &tmp_41_obj, read_path );
                else if ( strstr ( read_path, "/etc/cron.d/" ) != 0 )
                    append_list ( &tmp_4_obj, read_path );
                else if ( strstr ( read_path, "/etc/cron.hourly/" ) != 0 )
                    append_list ( &tmp_54_obj, read_path );
                else if ( strstr ( read_path, "/etc/cron.daily/" ) != 0 )
                    append_list ( &tmp_55_obj, read_path );
                else if ( strstr ( read_path, "/etc/cron.weekly/" ) != 0 )
                    append_list ( &tmp_56_obj, read_path );
                else if ( strstr ( read_path, "/etc/cron.monthly/" ) != 0 )
                    append_list ( &tmp_57_obj, read_path );
                else if ( strstr ( read_path, "/etc/default/" ) != 0 )
                    append_list ( &tmp_16_obj, read_path );
                /* for etc/dnf/'s rootdir */
                else if ( strstr ( read_path, "/etc/dnf/" ) != 0 )
                    append_list ( &tmp_52_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/dnf/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_52_obj, read_path );
                /* for etc/firewalld/'s rootdir */
                else if ( strstr ( read_path, "/etc/firewalld/" ) != 0 )
                    append_list ( &tmp_44_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/firewalld/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_44_obj, read_path );
                else if ( strstr ( read_path, "/etc/host" ) != 0 )
                    append_list ( &tmp_19_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/httpd/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_13_obj, read_path );
                else if ( strstr ( read_path, "/etc/logrotate.d/" ) != 0 )
                    append_list ( &tmp_17_obj, read_path );
                else if ( strstr ( read_path, "/etc/modprobe.d/" ) != 0 )
                    append_list ( &tmp_18_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/pam.d/" ) != 0 ) )
                    append_list ( &tmp_38_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/pki/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_3_obj, read_path );
                /* for etc/selinux/'s rootdir */
                else if ( strstr ( read_path, "/etc/selinux/" ) != 0 )
                    append_list ( &tmp_48_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/selinux/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_48_obj, read_path );
                /* for etc/sysconfig/'s rootdir */
                else if ( strstr ( read_path, "/etc/sysconfig/" ) != 0 )
                    append_list ( &tmp_47_obj, read_path );
                else if ( strstr ( read_path, "/etc/sysconfig/network-scripts/ifcfg-" ) != 0 )
                    append_list ( &tmp_5_obj, read_path );
                /* for etc/systemd/system/'s rootdir */
                else if ( strstr ( read_path, "/etc/systemd/system/" ) != 0 )
                    append_list ( &tmp_22_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/systemd/system/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_22_obj, read_path );
                else if ( strstr ( read_path, "/etc/systemd/" ) != 0 )
                    append_list ( &tmp_23_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/udev/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_20_obj, read_path );
                else if ( strstr ( read_path, "/etc/yum/" ) != 0 )
                    append_list ( &tmp_50_obj, read_path );
                else if ( strstr ( read_path, "/etc/yum.repos.d/" ) != 0 )
                    append_list ( &tmp_21_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/abrt/" ) != 0 )
                    append_list ( &tmp_36_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/apache/" ) != 0 )
                    append_list ( &tmp_40_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/auditd/" ) != 0 )
                    append_list ( &tmp_42_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/boot/" ) != 0 )
                    append_list ( &tmp_12_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/devicemapper/" ) != 0 )
                    append_list ( &tmp_46_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/dnf/" ) != 0 )
                    append_list ( &tmp_53_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/logs/journalctl_--no-pager" ) != 0 )
                    append_list ( &tmp_9_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/firewalld/" ) != 0 )
                    append_list ( &tmp_45_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/ipmitool/" ) != 0 )
                    append_list ( &tmp_60_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/memory/" ) != 0 )
                    append_list ( &tmp_43_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/networking/ethtool_-S" ) != 0 )
                    append_list ( &tmp_10_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/networking/ethtool_-i" ) != 0 )
                    append_list ( &tmp_11_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/networking/" ) != 0 )
                    append_list ( &tmp_30_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/networkmanager/" ) != 0 )
                    append_list ( &tmp_58_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/pam/" ) != 0 )
                    append_list ( &tmp_39_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/sar/" ) != 0 )
                    append_list ( &tmp_25_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/selinux/" ) != 0 )
                    append_list ( &tmp_49_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/usb/" ) != 0 )
                    append_list ( &tmp_27_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/virsh/" ) != 0 )
                    append_list ( &tmp_26_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/yum/" ) != 0 )
                    append_list ( &tmp_51_obj, read_path );
                else if ( ( strstr ( read_path, "/sys/module/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_37_obj, read_path );
                else if ( ( strstr ( read_path, "/usr/lib/systemd/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_24_obj, read_path );
                else if ( strstr ( read_path, "/var/crash/" ) != 0 )
                    append_list ( &tmp_15_obj, read_path );
                else if ( strstr ( read_path, "/var/log/messages" ) != 0 )
                    append_list ( &tmp_6_obj, read_path );
                else if ( strstr ( read_path, "/var/log/secure" ) != 0 )
                    append_list ( &tmp_7_obj, read_path );
                else if ( strstr ( read_path, "/var/log/audit/" ) != 0 )
                    append_list ( &tmp_8_obj, read_path );
                else if ( strstr ( read_path, "/var/spool/cron/" ) != 0 )
                    append_list ( &tmp_35_obj, read_path );

                /* reading everything stuff should be the last */
                /* for etc/'s rootdir */
                else if ( strstr ( read_path, "/etc/" ) != 0 )
                    append_list ( &tmp_29_obj, read_path );
                else if ( ( strstr ( read_path, "/etc/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_29_obj, read_path );
                else if ( ( strstr ( read_path, "/dev/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_31_obj, read_path );
                else if ( ( strstr ( read_path, "/lib/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_28_obj, read_path );
                /* for proc/'s rootdir */
                else if ( strstr ( read_path, "/proc/" ) != 0 )
                    append_list ( &tmp_14_obj, read_path );
                else if ( ( strstr ( read_path, "/proc/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_14_obj, read_path );
                else if ( strstr ( read_path, "/sos_commands/" ) != 0 )
                    append_list ( &tmp_34_obj, read_path );
                else if ( ( strstr ( read_path, "/usr/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_32_obj, read_path );
                else if ( ( strstr ( read_path, "/var/" ) != 0 ) && ( recursive == 1 ) )
                    append_list ( &tmp_33_obj, read_path );
                i++; /* needed here */
                str_arr_valid_size++;
                if ( str_arr_valid_size == MAX_ANALYZE_FILES_FOR_SOSREPORT_DIR )
                    break;
            }
        }
    }
    /* close the directory */
    if ( var_crash_exists == 1 )
        closedir ( dir );

    return ( 0 );
}

int read_file_from_analyze_dir ( node **obj, const char *member )
{
    int files = 0;
    node *ptr_tmp = NULL;
    ptr_tmp = *obj;
    while ( ptr_tmp != NULL )
    {
        if ( strcmp ( ptr_tmp->_line, "" ) == 0 )
        {
            files ++;
            ptr_tmp = ptr_tmp->next;
            continue;
        }
        printf("Read '%s' \n",ptr_tmp->_line);
        read_file ( ptr_tmp->_line, member, files );
        files ++;
        ptr_tmp = ptr_tmp->next;
    }
    return ( 0 );
}

/* These are the items to be analyzed not statically nor checked by multi-lines */
static int bios_information = 0;
static int memory_array_information = 0;
static int memory_information = 0;

int read_file ( const char *file_name, const char *member, int files )
{
    int file_name_len = ( int ) strlen ( file_name );
    char *hairline2 = "<<<<";
    char *blank_line = "";
    if ( file_name_len <= 0 )
    {
        printf("no file name supplied (%s): %d %s\n",file_name,file_name_len,strerror(errno));
        free_sosreport_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    if ( file_name_len > MAX_FULL_PATH_LENGTH )
    {
        printf("file name too long (%s): %d %s\n",file_name,file_name_len,strerror(errno));
        free_sosreport_analyzer_obj ( );
        exit ( EXIT_FAILURE );
    }
    FILE *fp;
    int lnr = 0, i = 0;
    char linebuf [ MAX_LINE_LENGTH ];
    char *line;

    /* when this function had been called from 'read_analyze_dir()', items should be set only once */
    if ( files == 0)
        if ( set_token_to_item_arr ( file_name, member ) == 1 )
            printf("set_token_to_item_arr failed in (%s)\n",file_name);

    /* open file */
    if ( ( fp=fopen ( file_name, "r" ) ) == NULL )
    {
        printf("can't open file (%s): %s\n",file_name,strerror(errno));
        printf("Try set 'skip' to this member in config file.\n");
        printf("Also, please check lsb-release and use appropriate conf file in /usr/share/sosreport-analyzer.\n");
        printf("Skip '%s' and go on.\n",member);
        return ( 0 );
        /* free_sosreport_analyzer_obj ( ); */
        /* exit ( EXIT_FAILURE ); */
    }

    if (
        ( strcmp ( member, "boot/grub/" ) == 0 ) ||
        ( strcmp ( member, "cmdlog/" ) == 0 ) ||
        ( strcmp ( member, "etc/host" ) == 0 ) ||
        ( ( strcmp ( member, "etc/NetworkManager/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/audit/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/anacrontab" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( strcmp ( member, "etc/crontab" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.deny" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.hourly/" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.daily/" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.weekly/" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.monthly/" ) == 0 ) ||
        ( ( strcmp ( member, "etc/default/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/dnf/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/firewalld/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/httpd/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/logrotate.d/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/modprobe.d/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/pam.d/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/pki/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/selinux/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 ) ||
        ( ( strcmp ( member, "etc/sysconfig/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/systemd/system/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/systemd/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/udev/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/yum.repos.d/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/yum/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/abrt/" ) == 0 ) && ( strcmp ( member, "cmdlog/") != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/apache/" ) == 0 ) && ( strcmp ( member, "cmdlog/") != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/auditd/" ) == 0 ) && ( strcmp ( member, "cmdlog/") != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/boot/" ) == 0 ) && ( strcmp ( member, "cmdlog/") != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/devicemapper/" ) == 0 ) && ( strcmp ( member, "cmdlog/") != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/etc/" ) == 0 ) && ( strcmp ( member, "cmdlog/") != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/firewalld/" ) == 0 ) && ( strcmp ( member, "cmdlog/") != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/ipmitool/" ) == 0 ) && ( strcmp ( member, "cmdlog/") != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/memory/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networkmanager/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/pam/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/sar/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/selinux/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/usb/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/virsh/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/yum/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "sys/module/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/crash/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( strcmp ( member, "var/log/audit/" ) == 0 ) ||
        ( strcmp ( member, "var/log/messages" ) == 0 ) ||
        ( strcmp ( member, "var/log/secure" ) == 0 ) ||
        ( ( strcmp ( member, "var/spool/cron/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "dev/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "lib/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "usr/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/" ) == 0 ) && ( strcmp ( member, "cmdlog/" ) != 0 ) )
    )
    {
        append_list ( &sos_line_obj, blank_line );
        append_list ( &sos_line_obj, hairline2 );
        append_list ( &sos_line_obj, (char *)file_name );
        append_list ( &sos_line_obj, blank_line );
    }

    /* read file and parse lines */
    while ( fgets ( linebuf, sizeof ( linebuf ), fp ) != NULL )
    {
        lnr++;
        line = linebuf;
        int x = 1;

        /* strip newline */
        i = ( int ) strlen ( line );
        if ( (i > MAX_LINE_LENGTH ) || ( i <= 0 ) || ( line [ i - 1 ] != '\n' ) )
        {
            printf("%s:%d: line too long or last line missing newline. Skipping this line.\n",file_name,lnr);
            continue;
        }
        line [ i - 1 ] = '\0';
        /* ignore comment lines */
        if ( line [ 0 ] == '#' )
            continue;

        /* get item if any and append to object
         * this part should survive through while loop 
         */
        for ( x = 0; x < get_item_numbers_of_member ( member ) ; x++ )
            append_item_to_sos_line_obj ( line, member, get_item_arr_string ( member, x ) );

        /* strip trailing spaces */
        for ( i--; ( i > 0 ) && isspace ( line [ i -1 ] ) ; i-- )
            line [ i -1 ] = '\0';
    }
    /* after reading all lines, close the file pointer */
    fclose ( fp );

    return ( 0 );
}

int check_item_string_length ( const char *token, const char *member )
{
    int strlen_token = ( int ) strlen ( token );
    if ( strlen_token > MAX_ITEM_STRING_LENGTH ) 
    {
        printf("item '%s' for '%s' is too long (%d)\n",token,member,strlen_token);
        return ( 1 );
    }
    if ( strlen_token < MIN_ITEM_STRING_LENGTH ) 
    {
        printf("item '%s' for '%s' is too short (%d)\n",token,member,strlen_token);
        return ( 1 );
    }
    return ( 0 );
}

int set_token_to_item_arr ( const char *file_name, const char *member )
{
    /* These are array number limits for items of a member. */
    int arr_max1 = 1;
    int arr_max2 = 2;
    int arr_max12 = 12;
    int arr_max20 = 20;

    /* initialized item numbers of member here */
    init_item_numbers_of_member ( );

    int i = 0;

    const char s [ 8 ] = " \t\n\r"; /* this is the delimiter */
    char *token = NULL;

    if ( ( strstr ( file_name, member ) != NULL ) && ( member_item_exists ( member ) == 0 ) )
    {
        /* get the first token */
        token = strtok ( get_items_of_member ( member ), s );
        if ( check_item_string_length ( token, member ) != 0 )
        {
            free_sosreport_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }
        set_item_arr_string ( member, 0, token );

        if ( strcmp ( token, "all" ) == 0 )
            i ++;
        else
        {
            /* get the next token ... */
            while ( token != NULL )
            {
                if ( check_item_string_length ( token, member ) != 0 )
                {
                    free_sosreport_analyzer_obj ( );
                    exit ( EXIT_FAILURE );
                }
                if ( strcmp ( token, "all" ) == 0 )
                    break;
                set_item_numbers_of_member ( member, i ); 
                /* only one item stuff */
                if (
                    ( strcmp ( member, "date" ) == 0 ) ||
                    ( strcmp ( member, "free" ) == 0 ) ||
                    ( strcmp ( member, "hostname" ) == 0 ) ||
                    ( strcmp ( member, "ip_addr" ) == 0 ) ||
                    ( strcmp ( member, "lsb-release" ) == 0 ) ||
                    ( strcmp ( member, "uname" ) == 0 ) ||
                    ( strcmp ( member, "route" ) == 0 ) ||
                    ( strcmp ( member, "uptime" ) == 0 ) ||
                    ( strcmp ( member, "vgdisplay" ) == 0 ) ||
                    ( strcmp ( member, "etc/NetworkManager/" ) == 0 ) ||
                    ( strcmp ( member, "etc/anacrontab" ) == 0 ) ||
                    ( strcmp ( member, "etc/audit/" ) == 0 ) ||
                    ( strcmp ( member, "etc/crontab" ) == 0 ) ||
                    ( strcmp ( member, "etc/cron.deny" ) == 0 ) ||
                    ( strcmp ( member, "etc/cron.d/" ) == 0 ) ||
                    ( strcmp ( member, "etc/cron.hourly/" ) == 0 ) ||
                    ( strcmp ( member, "etc/cron.daily/" ) == 0 ) ||
                    ( strcmp ( member, "etc/cron.weekly/" ) == 0 ) ||
                    ( strcmp ( member, "etc/cron.monthly/" ) == 0 ) ||
                    ( strcmp ( member, "etc/default/" ) == 0 ) ||
                    ( strcmp ( member, "etc/dnf/" ) == 0 ) ||
                    ( strcmp ( member, "etc/firewalld/" ) == 0 ) ||
                    ( strcmp ( member, "etc/httpd/" ) == 0 ) ||
                    ( strcmp ( member, "etc/host" ) == 0 ) ||
                    ( strcmp ( member, "etc/kdump.conf" ) == 0 ) ||
                    ( strcmp ( member, "etc/logrotate.conf" ) == 0 ) ||
                    ( strcmp ( member, "etc/logrotate.d/" ) == 0 ) ||
                    ( strcmp ( member, "etc/modprobe.d/" ) == 0 ) ||
                    ( strcmp ( member, "etc/pam.d/" ) == 0 ) ||
                    ( strcmp ( member, "etc/pki/" ) == 0 ) ||
                    ( strcmp ( member, "etc/rsyslog.conf" ) == 0 ) ||
                    ( strcmp ( member, "etc/selinux/" ) == 0 ) ||
                    ( strcmp ( member, "etc/sysconfig/" ) == 0 ) ||
                    ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 ) ||
                    ( strcmp ( member, "etc/sysctl.conf" ) == 0 ) ||
                    ( strcmp ( member, "etc/systemd/system/" ) == 0 ) ||
                    ( strcmp ( member, "etc/systemd/" ) == 0 ) ||
                    ( strcmp ( member, "etc/udev/" ) == 0 ) ||
                    ( strcmp ( member, "etc/yum.conf" ) == 0 ) ||
                    ( strcmp ( member, "etc/yum.repos.d/" ) == 0 ) ||
                    ( strcmp ( member, "etc/yum/" ) == 0 ) ||
                    ( strcmp ( member, "etc/" ) == 0 ) ||
                    ( strcmp ( member, "dev/" ) == 0 ) ||
                    ( strcmp ( member, "lib/" ) == 0 ) ||
                    ( strcmp ( member, "root/anaconda-ks.cfg" ) == 0 ) ||
                    ( strcmp ( member, "proc/net/dev" ) == 0 ) ||
                    ( strcmp ( member, "proc/net/sockstat" ) == 0 ) ||
                    ( strcmp ( member, "proc/interrupts" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/apache/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/auditd/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/devicemapper/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/dnf/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/firewalld/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/ipmitool/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/memory/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/pam/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/scsi/lsscsi" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/sar/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/selinux/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/usb/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/virsh/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/yum/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/" ) == 0 ) ||
                    ( strcmp ( member, "sys/module/" ) == 0 ) ||
                    ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) ||
                    ( strcmp ( member, "usr/" ) == 0 ) ||
                    ( strcmp ( member, "var/spool/cron/" ) == 0 ) ||
                    ( strcmp ( member, "var/log/dmesg" ) == 0 ) ||
                    ( strcmp ( member, "var/" ) == 0 )
                )
                {
                    if ( get_item_numbers_of_member ( member ) >= arr_max1 )
                    {
                        printf("can't set items over %d for %s\n",arr_max1,member);
                        free_sosreport_analyzer_obj ( );
                        exit ( EXIT_FAILURE );
                    }
                }
                /* two items stuff */
                else if (
                    ( strcmp ( member, "df" ) == 0 )
                )
                {
                    if ( get_item_numbers_of_member ( member ) >= arr_max2 )
                    {
                        printf("can't set items over %d for %s\n",arr_max2,member);
                        free_sosreport_analyzer_obj ( );
                        exit ( EXIT_FAILURE );
                    }
                }
                /* twelve items stuff */
                else if (
                    ( strcmp ( member, "installed-rpms" ) == 0 ) ||
                    ( strcmp ( member, "last" ) == 0 ) ||
                    ( strcmp ( member, "lsmod" ) == 0 ) ||
                    ( strcmp ( member, "lsof" ) == 0 ) ||
                    ( strcmp ( member, "netstat" ) == 0 ) ||
                    ( strcmp ( member, "ps" ) == 0 ) ||
                    ( strcmp ( member, "proc/cpuinfo" ) == 0 ) ||
                    ( strcmp ( member, "proc/meminfo" ) == 0 ) ||
                    ( strcmp ( member, "proc/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/abrt/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/boot/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/devices/udevadm_info_--export-db" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/kernel/sysctl_-a" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/networking/" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/networkmanager/" ) == 0 ) ||
                    ( strcmp ( member, "var/crash/" ) == 0 ) ||
                    ( strcmp ( member, "var/log/audit/" ) == 0 ) ||
                    ( strcmp ( member, "var/log/secure" ) == 0 )
                )
                {
                    if ( get_item_numbers_of_member ( member ) >= arr_max12 )
                    {
                        printf("can't set items over %d for %s\n",arr_max12,member);
                        free_sosreport_analyzer_obj ( );
                        exit ( EXIT_FAILURE );
                    }
                }
                /* twenty items stuff */
                else if (
                    ( strcmp ( member, "dmidecode" ) == 0 ) ||
                    ( strcmp ( member, "lspci" ) == 0 ) ||
                    ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) ||
                    ( strcmp ( member, "var/log/messages" ) == 0 )
                )
                {
                    if ( get_item_numbers_of_member ( member ) >= arr_max20 )
                    {
                        printf("can't set items over %d for %s\n",arr_max20,member);
                        free_sosreport_analyzer_obj ( );
                        exit ( EXIT_FAILURE );
                    }
                }
                else
                {
                    printf("'%s' has no item number limit.\n",member);
                    free_sosreport_analyzer_obj ( );
                    exit( EXIT_FAILURE );
                }
                token = strtok ( NULL, s );
                i ++;
                set_item_arr_string ( member, i, token );
            }
        }
        set_item_numbers_of_member ( member, i ); 
        return (0);
    }
    else
        return (1);
    return (1);
}

void read_file_pre ( const char *member, const char *dir_name )
{
    char str_tmp [ MAX_LINE_LENGTH - 6 ]; 
    memset ( str_tmp, '\0', MAX_LINE_LENGTH - 6 ); 
    char str_tmp2 [ MAX_LINE_LENGTH ]; 
    memset ( str_tmp2, '\0', MAX_LINE_LENGTH ); 
    char result_tmp_pre [ MAX_LINE_LENGTH - 21 ]; 
    memset ( result_tmp_pre, '\0', MAX_LINE_LENGTH - 21 ); 
    char result_tmp [ MAX_LINE_LENGTH ]; 
    memset ( result_tmp, '\0', MAX_LINE_LENGTH ); 

    char str_tmp3 [ MAX_LINE_LENGTH ]; 
    memset ( str_tmp3, '\0', MAX_LINE_LENGTH ); 
    int i = 0;
    char *hairline1 = "####";
    char *hairline2 = "<<<<";

    if (
        ( ( strcmp ( member, "boot/grub/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->mcinfo_boot_grub_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "cmdlog/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->mcinfo_cmdlog_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "date") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->date.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "df") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->df.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "dmidecode") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->dmidecode.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsb-release") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsb_release.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "hostname") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->hostname.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "uptime") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->uptime.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsmod") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsmod.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lspci") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lspci.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "uname") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->uname.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "installed-rpms") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->installed_rpms.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "vgdisplay") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->vgdisplay.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "free") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->free.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "ip_addr") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->ip_addr.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "route") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->route.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "last") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->last.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "ps") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->ps.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lsof") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lsof.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "netstat") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->netstat.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "dev/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->dev_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/NetworkManager/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_NetworkManager_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/anacrontab") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_anacrontab.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/audit/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_audit_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/crontab") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_crontab.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/cron.deny") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_cron_deny.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/cron.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_cron_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/cron.hourly/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_cron_hourly_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/cron.daily/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_cron_daily_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/cron.weekly/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_cron_weekly_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/cron.monthly/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_cron_monthly_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/default/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_default_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/dnf/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_dnf_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/firewalld/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_firewalld_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/httpd/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_httpd_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/host") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_host.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/pki/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_pki_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/kdump.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_kdump_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/logrotate.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_logrotate_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/logrotate.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_logrotate_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/pam.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_pam_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/rsyslog.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_rsyslog_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/selinux/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_selinux_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/modprobe.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_modprobe_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/sysconfig/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysconfig_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/systemd/system/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_systemd_system_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/systemd/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_systemd_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/sysctl.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysctl_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_sysconfig_network_scripts_ifcfg_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/udev/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_udev_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/yum.conf") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_yum_conf.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/yum.repos.d/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_yum_repos_d_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/yum/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_yum_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "etc/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->etc_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "lib/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->lib_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/cpuinfo") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_cpuinfo.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/interrupts") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_interrupts.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/meminfo") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_meminfo.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/net/dev") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_dev.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/net/sockstat") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_net_sockstat.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "proc/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->proc_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "root/anaconda-ks.cfg") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->root_anaconda_ks_cfg.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/abrt/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_abrt_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/apache/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_apache_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/auditd/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_auditd_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/boot/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_boot_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/devicemapper/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_devicemapper_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/devices/udevadm_info_--export-db") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_devices_udevadm_info___export_db.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/dnf/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_dnf_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/firewalld/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_firewalld_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/ipmitool/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_ipmitool_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/kernel/sysctl_-a") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_kernel_sysctl__a.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_logs_journalctl___no_pager.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/memory/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_memory_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/ethtool_-S") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__S.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/ethtool_-i") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_ethtool__i.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networking/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networking_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/networkmanager/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_networkmanager_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/pam/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_pam_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/sar/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_sar_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/selinux/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_selinux_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/scsi/lsscsi") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_scsi_lsscsi.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/usb/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_usb_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/virsh/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_virsh_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/yum/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_yum_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sos_commands/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sos_commands_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "sys/module/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->sys_module_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "usr/lib/systemd/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->usr_lib_systemd_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "usr/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->usr_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/crash/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_crash_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/dmesg") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_dmesg.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/messages") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_messages.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/secure") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_secure.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/log/audit/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_log_audit_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/spool/cron/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_spool_cron_.member, "" ) != 0 ) ) ||
        ( ( strcmp ( member, "var/") == 0 ) && ( strcmp ( sosreport_analyzer_cfg->var_.member, "" ) != 0 ) )
    )
    {
        /* You should check the order of the member. For example, if '/etc' comes first, '/etc/xxx' will be '/etc'...  */
        search_list ( &sos_header_obj, member, result_tmp_pre );
        snprintf ( result_tmp, MAX_LINE_LENGTH, "(config setting is %s)", result_tmp_pre );
        snprintf (str_tmp, MAX_LINE_LENGTH, "%s/%s", get_dirname ( str_tmp3 ), member );
        snprintf ( str_tmp2, MAX_LINE_LENGTH, "file:%s", str_tmp );
        if ( strcmp ( member, "date" ) == 0 )
            append_list ( &sos_line_obj, "==== general ====" );
        if ( strcmp ( member, "proc/interrupts" ) == 0 )
            append_list ( &sos_line_obj, "==== cpu ====" );
        if ( strcmp ( member, "lsmod" ) == 0 )
            append_list ( &sos_line_obj, "==== module ====" );
        if ( strcmp ( member, "lspci" ) == 0 )
            append_list ( &sos_line_obj, "==== device ====" );
        if ( strcmp ( member, "df" ) == 0 )
            append_list ( &sos_line_obj, "==== disk usage ====" );
        if ( strcmp ( member, "free" ) == 0 )
            append_list ( &sos_line_obj, "==== memory usage ====" );
        if ( strcmp ( member, "etc/host" ) == 0 )
            append_list ( &sos_line_obj, "==== networking ====" );
        if ( strcmp ( member, "ps" ) == 0 )
            append_list ( &sos_line_obj, "==== process ====" );
        if ( strcmp ( member, "sos_commands/virsh/" ) == 0 )
            append_list ( &sos_line_obj, "==== virtualization ====" );
        if ( strcmp ( member, "lsof" ) == 0 )
            append_list ( &sos_line_obj, "==== files ====" );
        if ( strcmp ( member, "etc/systemd/system/" ) == 0 )
            append_list ( &sos_line_obj, "==== systemd ====" );
        if ( strcmp ( member, "etc/pam.d/" ) == 0 )
            append_list ( &sos_line_obj, "==== security ====" );
        if ( strcmp ( member, "etc/kdump.conf" ) == 0 )
            append_list ( &sos_line_obj, "==== kernel ====" );
        if ( strcmp ( member, "etc/yum.conf" ) == 0 )
            append_list ( &sos_line_obj, "==== dnf/yum ====" );
        if ( strcmp ( member, "last" ) == 0 )
            append_list ( &sos_line_obj, "==== login ====" );
        if ( strcmp ( member, "etc/anacrontab" ) == 0 )
            append_list ( &sos_line_obj, "==== cron ====" );
        if ( strcmp ( member, "etc/logrotate.conf" ) == 0 )
            append_list ( &sos_line_obj, "==== logrotate ====" );
        if ( strcmp ( member, "etc/rsyslog.conf" ) == 0 )
            append_list ( &sos_line_obj, "==== logs and journals ====" );
        if ( strcmp ( member, "etc/httpd/" ) == 0 )
            append_list ( &sos_line_obj, "==== httpd ====" );
        if ( strcmp ( member, "lib/" ) == 0 )
            append_list ( &sos_line_obj, "==== others ====" );
        append_list ( &sos_line_obj, "" );
        append_list ( &sos_line_obj, hairline1 );
        append_list ( &sos_line_obj, hairline2 );
        append_list ( &sos_line_obj, str_tmp2 );
        append_list ( &sos_line_obj, result_tmp );
        append_list ( &sos_line_obj, "" );

        /* for ones of which should read directory, or matched files in the directory */
        if (
            ( strcmp ( member, "boot/grub/" ) == 0 ) ||
            ( strcmp ( member, "cmdlog/" ) == 0 ) ||
            ( strcmp ( member, "dev/" ) == 0 ) ||
            ( strcmp ( member, "etc/NetworkManager/" ) == 0 ) ||
            ( strcmp ( member, "etc/audit/" ) == 0 ) ||
            ( strcmp ( member, "etc/cron.d/" ) == 0 ) ||
            ( strcmp ( member, "etc/cron.hourly/" ) == 0 ) ||
            ( strcmp ( member, "etc/cron.daily/" ) == 0 ) ||
            ( strcmp ( member, "etc/cron.weekly/" ) == 0 ) ||
            ( strcmp ( member, "etc/cron.monthly/" ) == 0 ) ||
            ( strcmp ( member, "etc/default/" ) == 0 ) ||
            ( strcmp ( member, "etc/dnf/" ) == 0 ) ||
            ( strcmp ( member, "etc/firewalld/" ) == 0 ) ||
            ( strcmp ( member, "etc/httpd/" ) == 0 ) ||
            ( strcmp ( member, "etc/host" ) == 0 ) ||
            ( strcmp ( member, "etc/logrotate.d/" ) == 0 ) ||
            ( strcmp ( member, "etc/pam.d/" ) == 0 ) ||
            ( strcmp ( member, "etc/pki/" ) == 0 ) ||
            ( strcmp ( member, "etc/modprobe.d/" ) == 0 ) ||
            ( strcmp ( member, "etc/selinux/" ) == 0 ) ||
            ( strcmp ( member, "etc/sysconfig/" ) == 0 ) ||
            ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 ) ||
            ( strcmp ( member, "etc/systemd/system/" ) == 0 ) ||
            ( strcmp ( member, "etc/systemd/" ) == 0 ) ||
            ( strcmp ( member, "etc/udev/" ) == 0 ) ||
            ( strcmp ( member, "etc/yum.repos.d/" ) == 0 ) ||
            ( strcmp ( member, "etc/yum/" ) == 0 ) ||
            ( strcmp ( member, "etc/" ) == 0 ) ||
            ( strcmp ( member, "lib/" ) == 0 ) ||
            ( strcmp ( member, "proc/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/abrt/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/apache/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/auditd/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/boot/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/devicemapper/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/dnf/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/firewalld/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/ipmitool/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/memory/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networking/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/networkmanager/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/pam/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/sar/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/selinux/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/usb/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/virsh/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/yum/" ) == 0 ) ||
            ( strcmp ( member, "sos_commands/" ) == 0 ) ||
            ( strcmp ( member, "sys/module/" ) == 0 ) ||
            ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) ||
            ( strcmp ( member, "usr/" ) == 0 ) ||
            ( strcmp ( member, "var/crash/" ) == 0 ) ||
            ( strcmp ( member, "var/log/audit/" ) == 0 ) ||
            ( strcmp ( member, "var/log/messages" ) == 0 ) ||
            ( strcmp ( member, "var/log/secure" ) == 0 ) ||
            ( strcmp ( member, "var/spool/cron/" ) == 0 ) ||
            ( strcmp ( member, "var/" ) == 0 )
           )
        {
            printf("analyze member '%s'\n",member);
            read_analyze_dir ( member, get_dirname ( str_tmp3 ), 0 );
        }
        else
            read_file ( str_tmp, member, 0 );
        /* now, we actually read files here for directory stuff */
        if ( strcmp ( member, "boot/grub/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_1_obj, str_arr_boot_grub ); i ++ )
                append_list ( &mcinfo_boot_grub__obj, str_arr_boot_grub [ i ] );
            read_file_from_analyze_dir ( &mcinfo_boot_grub__obj, "boot/grub/" );
        }
        else if ( strcmp ( member, "cmdlog/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_2_obj, str_arr_cmdlog ); i ++ )
                append_list ( &mcinfo_cmdlog__obj, str_arr_cmdlog [ i ] );
            read_file_from_analyze_dir ( &mcinfo_cmdlog__obj, "cmdlog/" );
        }
        else if ( strcmp ( member, "dev/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_31_obj, str_arr_dev ); i ++ )
                append_list ( &dev__obj, str_arr_dev [ i ] );
            read_file_from_analyze_dir ( &dev__obj, "dev/" );
        }
        else if ( strcmp ( member, "etc/NetworkManager/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_59_obj, str_arr_etc_networkmanager ); i ++ )
                append_list ( &etc_networkmanager__obj, str_arr_etc_networkmanager [ i ] );
            read_file_from_analyze_dir ( &etc_networkmanager__obj, "etc/NetworkManager/" );
        }
        else if ( strcmp ( member, "etc/audit/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_41_obj, str_arr_etc_audit ); i ++ )
                append_list ( &etc_audit__obj, str_arr_etc_audit [ i ] );
            read_file_from_analyze_dir ( &etc_audit__obj, "etc/audit/" );
        }
        else if ( strcmp ( member, "etc/cron.d/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_4_obj, str_arr_etc_cron_d ); i ++ )
                append_list ( &etc_cron_d__obj, str_arr_etc_cron_d [ i ] );
            read_file_from_analyze_dir ( &etc_cron_d__obj, "etc/cron.d/" );
        }
        else if ( strcmp ( member, "etc/cron.hourly/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_54_obj, str_arr_etc_cron_hourly ); i ++ )
                append_list ( &etc_cron_hourly__obj, str_arr_etc_cron_hourly [ i ] );
            read_file_from_analyze_dir ( &etc_cron_hourly__obj, "etc/cron.hourly/" );
        }
        else if ( strcmp ( member, "etc/cron.daily/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_55_obj, str_arr_etc_cron_daily ); i ++ )
                append_list ( &etc_cron_daily__obj, str_arr_etc_cron_daily [ i ] );
            read_file_from_analyze_dir ( &etc_cron_daily__obj, "etc/cron.daily/" );
        }
        else if ( strcmp ( member, "etc/cron.weekly/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_56_obj, str_arr_etc_cron_weekly ); i ++ )
                append_list ( &etc_cron_weekly__obj, str_arr_etc_cron_weekly [ i ] );
            read_file_from_analyze_dir ( &etc_cron_weekly__obj, "etc/cron.weekly/" );
        }
        else if ( strcmp ( member, "etc/cron.monthly/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_57_obj, str_arr_etc_cron_monthly ); i ++ )
                append_list ( &etc_cron_monthly__obj, str_arr_etc_cron_monthly [ i ] );
            read_file_from_analyze_dir ( &etc_cron_monthly__obj, "etc/cron.monthly/" );
        }
        else if ( strcmp ( member, "etc/default/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_16_obj, str_arr_etc_default ); i ++ )
                append_list ( &etc_default__obj, str_arr_etc_default [ i ] );
            read_file_from_analyze_dir ( &etc_default__obj, "etc/default/" );
        }
        else if ( strcmp ( member, "etc/dnf/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_52_obj, str_arr_etc_dnf ); i ++ )
                append_list ( &etc_dnf__obj, str_arr_etc_dnf [ i ] );
            read_file_from_analyze_dir ( &etc_dnf__obj, "etc/dnf/" );
        }
        else if ( strcmp ( member, "etc/firewalld/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_44_obj, str_arr_etc_firewalld ); i ++ )
                append_list ( &etc_firewalld__obj, str_arr_etc_firewalld [ i ] );
            read_file_from_analyze_dir ( &etc_firewalld__obj, "etc/firewalld/" );
        }
        else if ( strcmp ( member, "etc/httpd/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_13_obj, str_arr_etc_httpd ); i ++ )
                append_list ( &etc_httpd__obj, str_arr_etc_httpd [ i ] );
            read_file_from_analyze_dir ( &etc_httpd__obj, "etc/httpd/" );
        }
        else if ( strcmp ( member, "etc/host" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_19_obj, str_arr_etc_host ); i ++ )
                append_list ( &etc_host_obj, str_arr_etc_host [ i ] );
            read_file_from_analyze_dir ( &etc_host_obj, "etc/host" );
        }
        else if ( strcmp ( member, "etc/logrotate.d/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_17_obj, str_arr_etc_logrotate_d ); i ++ )
                append_list ( &etc_logrotate_d__obj, str_arr_etc_logrotate_d [ i ] );
            read_file_from_analyze_dir ( &etc_logrotate_d__obj, "etc/logrotate.d/" );
        }
        else if ( strcmp ( member, "etc/pam.d/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_38_obj, str_arr_etc_pam_d ); i ++ )
                append_list ( &etc_pam_d__obj, str_arr_etc_pam_d [ i ] );
            read_file_from_analyze_dir ( &etc_pam_d__obj, "etc/pam.d/" );
        }
        else if ( strcmp ( member, "etc/modprobe.d/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_18_obj, str_arr_etc_modprobe_d ); i ++ )
                append_list ( &etc_modprobe_d__obj, str_arr_etc_modprobe_d [ i ] );
            read_file_from_analyze_dir ( &etc_modprobe_d__obj, "etc/modprobe.d/" );
        }
        else if ( strcmp ( member, "etc/pki/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_3_obj, str_arr_pki ); i ++ )
                append_list ( &etc_pki__obj, str_arr_pki [ i ] );
            read_file_from_analyze_dir ( &etc_pki__obj, "etc/pki/" );
        }
        else if ( strcmp ( member, "etc/selinux/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_48_obj, str_arr_etc_selinux ); i ++ )
                append_list ( &etc_selinux__obj, str_arr_etc_selinux [ i ] );
            read_file_from_analyze_dir ( &etc_selinux__obj, "etc/selinux/" );
        }
        else if ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_5_obj, str_arr_ifcfg ); i ++ )
                append_list ( &etc_sysconfig_network_scripts_ifcfg__obj, str_arr_ifcfg [ i ] );
            read_file_from_analyze_dir ( &etc_sysconfig_network_scripts_ifcfg__obj, "etc/sysconfig/network-scripts/ifcfg-" );
        }
        else if ( strcmp ( member, "etc/sysconfig/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_47_obj, str_arr_etc_sysconfig ); i ++ )
                append_list ( &etc_sysconfig__obj, str_arr_etc_sysconfig [ i ] );
            read_file_from_analyze_dir ( &etc_sysconfig__obj, "etc/sysconfig/" );
        }
        else if ( strcmp ( member, "etc/systemd/system/" ) == 0 )
        {
            for ( i= 0; i < bubble_sort_object_by_the_string ( &tmp_22_obj, str_arr_etc_systemd_system ); i ++ )
                append_list ( &etc_systemd_system__obj, str_arr_etc_systemd_system [ i ] );
            read_file_from_analyze_dir ( &etc_systemd_system__obj, "etc/systemd/system/" );
        }
        else if ( strcmp ( member, "etc/systemd/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_23_obj, str_arr_etc_systemd ); i ++ )
                append_list ( &etc_systemd__obj, str_arr_etc_systemd [ i ] );
            read_file_from_analyze_dir ( &etc_systemd__obj, "etc/systemd/" );
        }
        else if ( strcmp ( member, "etc/udev/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_20_obj, str_arr_etc_udev ); i ++ )
                append_list ( &etc_udev__obj, str_arr_etc_udev [ i ] );
            read_file_from_analyze_dir ( &etc_udev__obj, "etc/udev/" );
        }
        else if ( strcmp ( member, "etc/yum.repos.d/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_21_obj, str_arr_etc_yum_repos_d ); i ++ )
                append_list ( &etc_yum_repos_d__obj, str_arr_etc_yum_repos_d [ i ] );
            read_file_from_analyze_dir ( &etc_yum_repos_d__obj, "etc/yum.repos.d/" );
        }
        else if ( strcmp ( member, "etc/yum/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_50_obj, str_arr_etc_yum ); i ++ )
                append_list ( &etc_yum__obj, str_arr_etc_yum [ i ] );
            read_file_from_analyze_dir ( &etc_yum__obj, "etc/yum/" );
        }
        else if ( strcmp ( member, "etc/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_29_obj, str_arr_etc ); i ++ )
                append_list ( &etc__obj, str_arr_etc [ i ] );
            read_file_from_analyze_dir ( &etc__obj, "etc/" );
        }
        else if ( strcmp ( member, "lib/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_28_obj, str_arr_lib ); i ++ )
                append_list ( &lib__obj, str_arr_lib [ i ] );
            read_file_from_analyze_dir ( &lib__obj, "lib/" );
        }
        else if ( strcmp ( member, "proc/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_14_obj, str_arr_proc ); i ++ )
                append_list ( &proc__obj, str_arr_proc [ i ] );
            read_file_from_analyze_dir ( &proc__obj, "proc/" );
        }
        else if ( strcmp ( member, "sos_commands/abrt/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_36_obj, str_arr_sos_commands_abrt ); i ++ )
                append_list ( &sos_commands_abrt__obj, str_arr_sos_commands_abrt [ i ] );
            read_file_from_analyze_dir ( &sos_commands_abrt__obj, "sos_commands/abrt/" );
        }
        else if ( strcmp ( member, "sos_commands/apache/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_40_obj, str_arr_sos_commands_apache ); i ++ )
                append_list ( &sos_commands_apache__obj, str_arr_sos_commands_apache [ i ] );
            read_file_from_analyze_dir ( &sos_commands_apache__obj, "sos_commands/apache/" );
        }
        else if ( strcmp ( member, "sos_commands/auditd/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_42_obj, str_arr_sos_commands_auditd ); i ++ )
                append_list ( &sos_commands_auditd__obj, str_arr_sos_commands_auditd [ i ] );
            read_file_from_analyze_dir ( &sos_commands_auditd__obj, "sos_commands/auditd/" );
        }
        else if ( strcmp ( member, "sos_commands/boot/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_12_obj, str_arr_boot ); i ++ )
                append_list ( &sos_commands_boot__obj, str_arr_boot [ i ] );
            read_file_from_analyze_dir ( &sos_commands_boot__obj, "sos_commands/boot/" );
        }
        else if ( strcmp ( member, "sos_commands/devicemapper/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_46_obj, str_arr_sos_commands_devicemapper ); i ++ )
                append_list ( &sos_commands_devicemapper__obj, str_arr_sos_commands_devicemapper [ i ] );
            read_file_from_analyze_dir ( &sos_commands_devicemapper__obj, "sos_commands/devicemapper/" );
        }
        else if ( strcmp ( member, "sos_commands/dnf/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_53_obj, str_arr_sos_commands_dnf ); i ++ )
                append_list ( &sos_commands_dnf__obj, str_arr_sos_commands_dnf [ i ] );
            read_file_from_analyze_dir ( &sos_commands_dnf__obj, "sos_commands/dnf/" );
        }
        else if ( strcmp ( member, "sos_commands/firewalld/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_45_obj, str_arr_sos_commands_firewalld ); i ++ )
                append_list ( &sos_commands_firewalld__obj, str_arr_sos_commands_firewalld [ i ] );
            read_file_from_analyze_dir ( &sos_commands_firewalld__obj, "sos_commands/firewalld/" );
        }
        else if ( strcmp ( member, "sos_commands/ipmitool/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_60_obj, str_arr_sos_commands_ipmitool ); i ++ )
                append_list ( &sos_commands_ipmitool__obj, str_arr_sos_commands_ipmitool [ i ] );
            read_file_from_analyze_dir ( &sos_commands_ipmitool__obj, "sos_commands/ipmitool/" );
        }
        else if ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_9_obj, str_arr_logs_journalctl ); i ++ )
                append_list ( &sos_commands_logs_journalctl___no_pager_obj, str_arr_logs_journalctl [ i ] );
            read_file_from_analyze_dir ( &sos_commands_logs_journalctl___no_pager_obj, "sos_commands/logs/journalctl_--no-pager" );
        }
        else if ( strcmp ( member, "sos_commands/memory/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_43_obj, str_arr_sos_commands_memory ); i ++ )
                append_list ( &sos_commands_memory__obj, str_arr_sos_commands_memory [ i ] );
            read_file_from_analyze_dir ( &sos_commands_memory__obj, "sos_commands/memory/" );
        }
        else if ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_10_obj, str_arr_ethtool_S ); i ++ )
                append_list ( &sos_commands_networking_ethtool__S_obj, str_arr_ethtool_S [ i ] );
            read_file_from_analyze_dir ( &sos_commands_networking_ethtool__S_obj, "sos_commands/networking/ethtool_-S" );
        }
        else if ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_11_obj, str_arr_ethtool_i ); i ++ )
                append_list ( &sos_commands_networking_ethtool__i_obj, str_arr_ethtool_i [ i ] );
            read_file_from_analyze_dir ( &sos_commands_networking_ethtool__i_obj, "sos_commands/networking/ethtool_-i" );
        }
        else if ( strcmp ( member, "sos_commands/networking/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_30_obj, str_arr_sos_commands_networking ); i ++ )
                append_list ( &sos_commands_networking__obj, str_arr_sos_commands_networking [ i ] );
            read_file_from_analyze_dir ( &sos_commands_networking__obj, "sos_commands/networking/" );
        }
        else if ( strcmp ( member, "sos_commands/networkmanager/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_58_obj, str_arr_sos_commands_networkmanager ); i ++ )
                append_list ( &sos_commands_networkmanager__obj, str_arr_sos_commands_networkmanager [ i ] );
            read_file_from_analyze_dir ( &sos_commands_networkmanager__obj, "sos_commands/networkmanager/" );
        }
        else if ( strcmp ( member, "sos_commands/pam/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_39_obj, str_arr_sos_commands_pam ); i ++ )
                append_list ( &sos_commands_pam__obj, str_arr_sos_commands_pam [ i ] );
            read_file_from_analyze_dir ( &sos_commands_pam__obj, "sos_commands/pam/" );
        }
        else if ( strcmp ( member, "sos_commands/sar/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_25_obj, str_arr_sos_commands_sar ); i ++ )
                append_list ( &sos_commands_sar__obj, str_arr_sos_commands_sar [ i ] );
            read_file_from_analyze_dir ( &sos_commands_sar__obj, "sos_commands/sar/" );
        }
        else if ( strcmp ( member, "sos_commands/selinux/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_49_obj, str_arr_sos_commands_selinux ); i ++ )
                append_list ( &sos_commands_selinux__obj, str_arr_sos_commands_selinux [ i ] );
            read_file_from_analyze_dir ( &sos_commands_selinux__obj, "sos_commands/selinux/" );
        }
        else if ( strcmp ( member, "sos_commands/usb/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_27_obj, str_arr_sos_commands_usb ); i ++ )
                append_list ( &sos_commands_usb__obj, str_arr_sos_commands_usb [ i ] );
            read_file_from_analyze_dir ( &sos_commands_usb__obj, "sos_commands/usb/" );
        }
        else if ( strcmp ( member, "sos_commands/virsh/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_26_obj, str_arr_sos_commands_virsh ); i ++ )
                append_list ( &sos_commands_virsh__obj, str_arr_sos_commands_virsh [ i ] );
            read_file_from_analyze_dir ( &sos_commands_virsh__obj, "sos_commands/virsh/" );
        }
        else if ( strcmp ( member, "sos_commands/yum/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_51_obj, str_arr_sos_commands_yum ); i ++ )
                append_list ( &sos_commands_yum__obj, str_arr_sos_commands_yum [ i ] );
            read_file_from_analyze_dir ( &sos_commands_yum__obj, "sos_commands/yum/" );
        }
        else if ( strcmp ( member, "sos_commands/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_34_obj, str_arr_sos_commands ); i ++ )
                append_list ( &sos_commands_obj, str_arr_sos_commands [ i ] );
            read_file_from_analyze_dir ( &sos_commands_obj, "sos_commands/" );
        }
        else if ( strcmp ( member, "sys/module/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_37_obj, str_arr_sys_module ); i ++ )
                append_list ( &sys_module__obj, str_arr_sys_module [ i ] );
            read_file_from_analyze_dir ( &sys_module__obj, "sys/module/" );
        }
        else if ( strcmp ( member, "usr/lib/systemd/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_24_obj, str_arr_usr_lib_systemd ); i ++ )
                append_list ( &usr_lib_systemd__obj, str_arr_usr_lib_systemd [ i ] );
            read_file_from_analyze_dir ( &usr_lib_systemd__obj, "usr/lib/systemd/" );
        }
        else if ( strcmp ( member, "usr/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_32_obj, str_arr_usr ); i ++ )
                append_list ( &usr__obj, str_arr_usr [ i ] );
            read_file_from_analyze_dir ( &usr__obj, "usr/" );
        }
        else if ( strcmp ( member, "var/crash/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_15_obj, str_arr_var_crash ); i ++ )
                append_list ( &var_crash__obj, str_arr_var_crash [ i ] );
            read_file_from_analyze_dir ( &var_crash__obj, "var/crash/" );
        }
        else if ( strcmp ( member, "var/log/messages" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_6_obj, str_arr_var_log_messages ); i ++ )
                append_list ( &var_log_messages_obj, str_arr_var_log_messages [ i ] );
            read_file_from_analyze_dir ( &var_log_messages_obj, "var/log/messages" );
        }
        else if ( strcmp ( member, "var/log/secure" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_7_obj, str_arr_var_log_secure ); i ++ )
                append_list ( &var_log_secure_obj, str_arr_var_log_secure [ i ] );
            read_file_from_analyze_dir ( &var_log_secure_obj, "var/log/secure" );
        }
        else if ( strcmp ( member, "var/log/audit/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_8_obj, str_arr_var_log_audit ); i ++ )
                append_list ( &var_log_audit__obj, str_arr_var_log_audit [ i ] );
            read_file_from_analyze_dir ( &var_log_audit__obj, "var/log/audit/" );
        }
        else if ( strcmp ( member, "var/spool/cron/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_35_obj, str_arr_var_spool_cron ); i ++ )
                append_list ( &var_spool_cron__obj, str_arr_var_spool_cron [ i ] );
            read_file_from_analyze_dir ( &var_spool_cron__obj, "var/spool/cron/" );
        }
        else if ( strcmp ( member, "var/" ) == 0 )
        {
            for ( i = 0; i < bubble_sort_object_by_the_string ( &tmp_33_obj, str_arr_var ); i ++ )
                append_list ( &var__obj, str_arr_var [ i ] );
            read_file_from_analyze_dir ( &var__obj, "var/" );
        }
    }
}

int check_time_span_str ( const char *time_span_str )
{
    char str_tmp [ 12 ];
    memset ( str_tmp, '\0', sizeof ( str_tmp ) ); 
    strncpy ( str_tmp, time_span_str, 11 );
    int i = 0;
    for ( i = 0; i < 11; i++ )
    {
        if ( ( i == 0 ) || ( i == 6 ) )
            if ( ( str_tmp [ i ] != '0' ) && ( str_tmp [ i ] != '1' ) && ( str_tmp [ i ] != '2' ) )
                return 0;
        if ( ( i == 2 ) || ( i == 8 ) )
            if ( str_tmp [ i ] != ':' )
                return 0;
        if ( i == 5 )
            if ( str_tmp [ i ] != '-' )
                return 0;
        if ( ( i == 1 ) || ( i == 3 ) || ( i == 4 ) || ( i == 7 ) || ( i == 9 ) || ( i == 10 ) )
            if (
                ( str_tmp [ i ] != '0' ) && ( str_tmp [ i ] != '1' ) && ( str_tmp [ i ] != '2' ) && 
                ( str_tmp [ i ] != '3' ) && ( str_tmp [ i ] != '4' ) && ( str_tmp [ i ] != '5' ) && 
                ( str_tmp [ i ] != '6' ) && ( str_tmp [ i ] != '7' ) && ( str_tmp [ i ] != '8' ) && 
                ( str_tmp [ i ] != '9' )
               )
                   return 0;
    }

    if ( str_tmp [ 0 ] == '2' )
    {
        if ( ( str_tmp [ 1 ] != '0' ) && ( str_tmp [ 1 ] != '1' ) && ( str_tmp [ 1 ] != '2' ) && ( str_tmp [ 1 ] != '3' ) )
            return 0;
        if ( ( str_tmp [ 1 ] == '2' ) && ( ( str_tmp [ 6 ] == '1' ) || ( str_tmp [ 6 ] == '0' ) ) )
            return 0;
        if ( ( str_tmp [ 1 ] == '1' ) && ( str_tmp [ 6 ] == '0' ) )
            return 0;
    }

    if ( str_tmp [ 0 ] == str_tmp [ 6 ] )
    {
        if ( str_tmp [ 1 ] == '9' )
            if ( str_tmp [ 7 ] != '9' )
                return 0;
        if ( str_tmp [ 1 ] == '8' )
            if ( ( str_tmp [ 7 ] != '9' ) && ( str_tmp [ 7 ] != '8' ) )
                return 0;
        if ( str_tmp [ 1 ] == '7' )
            if ( ( str_tmp [ 7 ] != '9' ) && ( str_tmp [ 7 ] != '8' ) && ( str_tmp [ 7 ] != '7' ) )
                return 0;
        if ( str_tmp [ 1 ] == '6' )
            if ( ( str_tmp [ 7 ] != '9' ) && ( str_tmp [ 7 ] != '8' ) && ( str_tmp [ 7 ] != '7' ) && ( str_tmp [ 7 ] != '6' ) )
                return 0;
        if ( str_tmp [ 1 ] == '5' )
            if ( ( str_tmp [ 7 ] == '4' ) || ( str_tmp [ 7 ] == '3' ) || ( str_tmp [ 7 ] == '2' ) || ( str_tmp [ 7 ] == '1' ) || ( str_tmp [ 7 ] == '0' ) )
                return 0;
        if ( str_tmp [ 1 ] == '4' )
            if ( ( str_tmp [ 7 ] == '3' ) || ( str_tmp [ 7 ] == '2' ) || ( str_tmp [ 7 ] == '1' ) || ( str_tmp [ 7 ] == '0' ) )
                return 0;
        if ( str_tmp [ 1 ] == '3' )
            if ( ( str_tmp [ 7 ] == '2' ) || ( str_tmp [ 7 ] == '1' ) || ( str_tmp [ 7 ] == '0' ) )
                return 0;
        if ( str_tmp [ 1 ] == '2' )
            if ( ( str_tmp [ 7 ] == '1' ) || ( str_tmp [ 7 ] == '0' ) )
                return 0;
        if ( str_tmp [ 1 ] == '1' )
            if ( str_tmp [ 7 ] == '0' )
                return 0;

        if ( str_tmp [ 1 ] == str_tmp [ 7 ] )
        {
            if ( str_tmp [ 3 ] == '9' )
                if ( str_tmp [ 9 ] != '9' )
                    return 0;
            if ( str_tmp [ 3 ] == '8' )
                if ( ( str_tmp [ 9 ] != '9' ) && ( str_tmp [ 9 ] != '8' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '7' )
                if ( ( str_tmp [ 9 ] != '9' ) && ( str_tmp [ 9 ] != '8' ) && ( str_tmp [ 9 ] != '7' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '6' )
                if ( ( str_tmp [ 9 ] != '9' ) && ( str_tmp [ 9 ] != '8' ) && ( str_tmp [ 9 ] != '7' ) && ( str_tmp [ 9 ] != '6' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '5' )
                if ( ( str_tmp [ 9 ] == '4' ) || ( str_tmp [ 9 ] == '3' ) || ( str_tmp [ 9 ] == '2' ) || ( str_tmp [ 9 ] == '1' ) || ( str_tmp [ 9 ] == '0' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '4' )
                if ( ( str_tmp [ 9 ] == '3' ) || ( str_tmp [ 9 ] == '2' ) || ( str_tmp [ 9 ] == '1' ) || ( str_tmp [ 9 ] == '0' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '3' )
                if ( ( str_tmp [ 9 ] == '2' ) || ( str_tmp [ 9 ] == '1' ) || ( str_tmp [ 9 ] == '0' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '2' )
                if ( ( str_tmp [ 9 ] == '1' ) || ( str_tmp [ 9 ] == '0' ) )
                    return 0;
            if ( str_tmp [ 3 ] == '1' )
                if ( str_tmp [ 9 ] == '0' )
                    return 0;
        }
    }

    if ( str_tmp [ 6 ] == '2' )
        if ( ( str_tmp [ 7 ] != '0' ) && ( str_tmp [ 7 ] != '1' ) && ( str_tmp [ 7 ] != '2' ) && ( str_tmp [ 7 ] != '3' ) ) 
            return 0;
    if ( ( ( str_tmp [ 0 ] == '1' ) || ( str_tmp [ 0 ] == '2' ) ) && ( str_tmp [ 6 ] == '0' ) ) 
        return 0;
    if ( ( ( str_tmp [ 0 ] == '2' ) ) && ( ( str_tmp [ 6 ] == '0' ) || ( str_tmp [ 6 ] == '1' ) ) )
        return 0;

    if (
        ( str_tmp [ 0 ] == str_tmp [ 6 ] ) &&
        ( str_tmp [ 1 ] == str_tmp [ 7 ] ) && 
        ( str_tmp [ 3 ] == str_tmp [ 9 ] )
       )
    {
        if ( str_tmp [ 4 ] == '9' )
            if ( str_tmp [ 10 ] != '9' )
                return 0;
        if ( str_tmp [ 4 ] == '8' )
            if ( ( str_tmp [ 10 ] != '9' ) && ( str_tmp [ 10 ] != '8' ) )
                return 0;
        if ( str_tmp [ 4 ] == '7' )
            if ( ( str_tmp [ 10 ] != '9' ) && ( str_tmp [ 10 ] != '8' ) && ( str_tmp [ 10 ] != '7' ) )
                return 0;
        if ( str_tmp [ 4 ] == '6' )
            if ( ( str_tmp [ 10 ] != '9' ) && ( str_tmp [ 10 ] != '8' ) && ( str_tmp [ 10 ] != '7' ) && ( str_tmp [ 10 ] != '6' ) )
                return 0;
        if ( str_tmp [ 4 ] == '5' )
            if ( ( str_tmp [ 10 ] == '4' ) || ( str_tmp [ 10 ] == '3' ) || ( str_tmp [ 10 ] == '2' ) || ( str_tmp [ 10 ] == '1' ) || ( str_tmp [ 10 ] == '0' ) )
                return 0;
        if ( str_tmp [ 4 ] == '4' )
            if ( ( str_tmp [ 10 ] == '3' ) || ( str_tmp [ 10 ] == '2' ) || ( str_tmp [ 10 ] == '1' ) || ( str_tmp [ 10 ] == '0' ) )
                return 0;
        if ( str_tmp [ 4 ] == '3' )
            if ( ( str_tmp [ 10 ] == '2' ) || ( str_tmp [ 10 ] == '1' ) || ( str_tmp [ 10 ] == '0' ) )
                return 0;
        if ( str_tmp [ 4 ] == '2' )
            if ( ( str_tmp [ 10 ] == '1' ) || ( str_tmp [ 10 ] == '0' ) )
                return 0;
        if ( str_tmp [ 4 ] == '1' )
            if ( str_tmp [ 10 ] == '0' )
                return 0;
    }

    return 1;
}

const char *get_dirname ( char str_tmp [ MAX_LINE_LENGTH ] )
{
    strncpy ( str_tmp, sos_dir_file_obj->dir_file_names.dirname, MAX_LINE_LENGTH );
    return str_tmp;
}

const char *get_sos_file_name_to_be_written ( void )
{
    return sos_dir_file_obj->dir_file_names.sos_file_name_to_be_written;
}

const char *get_sar_file_name_to_be_written ( void )
{
    return sos_dir_file_obj->dir_file_names.sar_file_name_to_be_written;
}

const char *get_ps_file_name_to_be_written ( void )
{
    return sos_dir_file_obj->dir_file_names.ps_file_name_to_be_written;
}

int is_dir_present ( const char *dname )
{
    int strlen_dname = ( int )strlen ( dname );

    if ( strlen_dname <= 0 )
    {
        printf("Directory (%s) name is too short.: %s\n",dname,strerror(errno));
        return ( 0 );
    }
    if ( strlen_dname > NAME_MAX )
    {
        printf("Directory (%s) name is too long.: %s\n",dname,strerror(errno));
        return ( 0 );
    }
    if ( dname != NULL )
    {
        DIR *dir = NULL;
        /* if open directory fails, return 1 */
        char str_tmp [ NAME_MAX ];
        strncpy ( str_tmp, dname, NAME_MAX - 1 );
        if ( ( dir = opendir ( str_tmp ) ) == NULL ) 
        {
            printf("can't open directory (%s): %s\n",dname,strerror(errno));
            free_sosreport_analyzer_obj ( );
            return 1;
        }
        else
        closedir ( dir );
    }
    return ( 0 );
}

int check_result_dir ( const char *dname )
{
    int strlen_dname = ( int )strlen ( dname );

    if ( strlen_dname <= 0 )
    {
        printf("Directory (%s) name is too short.: %s\n",dname,strerror(errno));
        return ( 0 );
    }
    if ( strlen_dname > NAME_MAX )
    {
        printf("Directory (%s) name is too long.: %s\n",dname,strerror(errno));
        return ( 0 );
    }
    if ( dname != NULL )
    {
        DIR *dir = NULL;
        /* if open directory fails, create it, if it fails, exit with error message */
        char str_tmp [ NAME_MAX ];
        strncpy ( str_tmp, dname, NAME_MAX - 1 );
        if ( ( dir = opendir ( str_tmp ) ) == NULL ) 
        {
            printf("can't open directory (%s): %s\n",dname,strerror(errno));
            printf("creating directory %s\n",dname);
            if ( mkdir ( dname, 0755 ) == 0 )
            {
                printf("created directory %s\n",dname);
            }
            else
            {
                printf("can't open directory %s\n",dname);
                free_sosreport_analyzer_obj ( );
                exit ( EXIT_FAILURE );
            }
        }
        else
            printf("directory %s exists\n",dname);
        closedir ( dir );
    }
    return ( 0 );
}

void sos_file_to_write ( void )
{
    char * result_dir = "sosreport-analyzer-results";
    char * result_dir_with_slash = "sosreport-analyzer-results/";
    char buff_dir [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_dir, '\0', MAX_FILE_NAME_LENGTH ); 
    strcpy ( buff_dir, result_dir );
    char buff_dir_analyzed [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_dir_analyzed, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff_dir_analyzed_graph [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_dir_analyzed_graph, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff_sos [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_sos, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff_sar [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_sar, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff_ps [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff_ps, '\0', MAX_FILE_NAME_LENGTH ); 
    char buff2 [ MAX_FILE_NAME_LENGTH ]; 
    memset ( buff2, '\0', MAX_FILE_NAME_LENGTH ); 
    char f_t [ 40 ];
    memset ( f_t, '\0', 40 ); 
    char f_t2 [ 40 ];
    memset ( f_t2, '\0', 40 ); 
    char f_t3 [ 40 ];
    memset ( f_t3, '\0', 40 ); 
    char str_tmp [ MAX_LINE_LENGTH ]; 
    memset ( str_tmp, '\0', MAX_LINE_LENGTH ); 

    strcpy ( buff2, get_dirname ( str_tmp ) );
    /* firstly, we create results directory */
    check_result_dir ( buff_dir );
    char str_ret [ MAX_FILE_NAME_LENGTH ]; 
    /* secondly, we create sosreport directory which has been analyed in the results directory we've just created */
    if ( strstr ( buff2, "/" ) != NULL )
    {
        int strlen_buff2 = ( int ) strlen ( buff2 );
        if ( strlen_buff2 <= 0 )
        {
            printf("buff2 is too short (%s): %d %s\n",buff2, strlen_buff2, strerror(errno));
            free_sosreport_analyzer_obj ( );
            exit ( EXIT_FAILURE );
        }
        strcpy ( buff_dir_analyzed, cut_str_from_the_last_slash ( reverse_the_string ( buff2, strlen_buff2 ), strlen_buff2, str_ret ) );
    }
    else
        strcpy ( buff_dir_analyzed, buff2 );
    strcat ( buff_dir, "/" );
    strcat ( buff_dir, buff_dir_analyzed );
    check_result_dir ( buff_dir );
    strcpy ( buff_dir_analyzed_graph, buff_dir );
    strcat ( buff_dir_analyzed_graph, "/graphs" );
    check_result_dir ( buff_dir_analyzed_graph );
    /* thirdly, we set file name */
    strcat ( buff_sos, result_dir_with_slash );
    strcat ( buff_sar, result_dir_with_slash );
    strcat ( buff_sos, buff_dir_analyzed );
    strcat ( buff_sar, buff_dir_analyzed );
    strcat ( buff_ps, buff_dir_analyzed_graph );
    strcat ( buff_sos, "/" );
    strcat ( buff_sar, "/" );
    strcat ( buff_ps, "/" );
    strcat ( buff_sos, buff_dir_analyzed );
    strcat ( buff_sar, buff_dir_analyzed );
    strcat ( buff_ps, buff_dir_analyzed );
    /* each analyed file should have unique name */
    struct tm *timenow;
    time_t now = time ( NULL );
    timenow = localtime ( &now );
    /* for sos file */
    strftime ( f_t, sizeof ( f_t ), "_%Y%m%d%H%M%S", timenow );
    strncat ( buff_sos, f_t, MAX_FILE_NAME_LENGTH - 1 );
    strncat ( buff_sos, ".txt", MAX_FILE_NAME_LENGTH - 1);
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strcpy ( sos_dir_file_obj->dir_file_names.sos_file_name_to_be_written, buff_sos );
    /* for sar file */
    strftime ( f_t2, sizeof ( f_t2 ), "_sar_%Y%m%d%H%M%S", timenow );
    strncat ( buff_sar, f_t2, MAX_FILE_NAME_LENGTH - 1 );
    strncat ( buff_sar, ".txt", MAX_FILE_NAME_LENGTH - 1 );
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strcpy ( sos_dir_file_obj->dir_file_names.sar_file_name_to_be_written, buff_sar );
    /* for ps file */
    strftime ( f_t3, sizeof ( f_t3 ), "_ps_%Y%m%d%H%M%S", timenow );
    strncat ( buff_ps, f_t3, MAX_FILE_NAME_LENGTH - 1 );
    /* Here we use strcpy. No worry, buff is surely under MAX_FILE_NAME_LENGTH */;
    strcpy ( sos_dir_file_obj->dir_file_names.ps_file_name_to_be_written, buff_ps );
}

int append_item_to_sos_line_obj ( char *line, const char *member, const char *item )
{
    /* These should echo only needed lines, note item number is limited by
     * set_token_to_item_arr.
     */
    /* First, check if item has 'all'. When item is 'all', should echo every lines */
    if ( strcmp ( item, "all" ) == 0 )
            append_list ( &sos_line_obj, line );
    if ( ( strcmp ( member, "dmidecode" ) == 0 ) && ( strcmp ( item, "bios" ) == 0 ) )
    {
        if ( strcmp ( line, "BIOS Information" ) == 0 )
            bios_information = 1;
        if ( strstr ( line , "Characteristics:" ) != 0 )
        {
            bios_information = 0;
            return 1;
        }
        if ( bios_information == 1 )
            append_list ( &sos_line_obj, line );
        if ( strstr ( line , "BIOS Revision:" ) != NULL )
            append_list ( &sos_line_obj, line );
    }
    else if ( ( strcmp ( member, "dmidecode" ) == 0 ) && ( strcmp ( item, "memory" ) == 0 ) )
    {
        if ( strcmp ( line, "Physical Memory Array" ) == 0 )
            memory_array_information = 1;
        if ( strstr ( line, "Handle" ) != NULL )
            memory_array_information = 0;
        if ( strcmp ( line, "Memory Device" ) == 0 )
        {
            append_list ( &sos_line_obj, line );
            memory_information = 1;
        }
        if ( strcmp ( line, "OEM" ) == 0 )
            memory_information = 0;
        if ( memory_array_information == 1 )
            append_list ( &sos_line_obj, line );
        if ( memory_information == 1 )
        {
            if ( strstr ( line , "Size:" ) != NULL )
                append_list ( &sos_line_obj, line );
        }
    }
    /* These should echo matched lines which had been set by config file, note item number is 
     * limited by set_token_to_item_arr. members which could have only one item is excluded here.
     * Another way of saying is, these may have item 'all' or others.
     */
    else if ( 
        ( strcmp ( member, "df" ) == 0 ) ||
        ( strcmp ( member, "dmidecode" ) == 0 ) ||
        ( strcmp ( member, "installed-rpms" ) == 0 ) ||
        ( strcmp ( member, "last" ) == 0 ) ||
        ( strcmp ( member, "lsmod" ) == 0 ) ||
        ( strcmp ( member, "lsof" ) == 0 ) ||
        ( strcmp ( member, "lspci" ) == 0 ) ||
        ( strcmp ( member, "netstat" ) == 0 ) ||
        ( strcmp ( member, "proc/cpuinfo" ) == 0 ) ||
        ( strcmp ( member, "ps" ) == 0 ) ||
        ( strcmp ( member, "dev/" ) == 0 ) ||
        ( strcmp ( member, "etc/pki/" ) == 0 ) ||
        ( strcmp ( member, "etc/NetworkManager/" ) == 0 ) ||
        ( strcmp ( member, "etc/anacrontab" ) == 0 ) ||
        ( strcmp ( member, "etc/audit/" ) == 0 ) ||
        ( strcmp ( member, "etc/crontab" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.deny" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.hourly/" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.daily/" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.weekly/" ) == 0 ) ||
        ( strcmp ( member, "etc/cron.monthly/" ) == 0 ) ||
        ( strcmp ( member, "etc/default/" ) == 0 ) ||
        ( strcmp ( member, "etc/dnf/" ) == 0 ) ||
        ( strcmp ( member, "etc/firewalld/" ) == 0 ) ||
        ( strcmp ( member, "etc/httpd/" ) == 0 ) ||
        ( strcmp ( member, "etc/host" ) == 0 ) ||
        ( strcmp ( member, "etc/logrotate.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/pam.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/modprobe.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/selinux/" ) == 0 ) ||
        ( strcmp ( member, "etc/sysconfig/network-scripts/ifcfg-" ) == 0 ) ||
        ( strcmp ( member, "etc/sysconfig/" ) == 0 ) ||
        ( strcmp ( member, "etc/systemd/system/" ) == 0 ) ||
        ( strcmp ( member, "etc/systemd/" ) == 0 ) ||
        ( strcmp ( member, "etc/udev/" ) == 0 ) ||
        ( strcmp ( member, "etc/yum.repos.d/" ) == 0 ) ||
        ( strcmp ( member, "etc/yum/" ) == 0 ) ||
        ( strcmp ( member, "etc/" ) == 0 ) ||
        ( strcmp ( member, "lib/" ) == 0 ) ||
        ( strcmp ( member, "proc/meminfo" ) == 0 ) ||
        ( strcmp ( member, "proc/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/abrt/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/apache/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/auditd/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/boot/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/devicemapper/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/dnf/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/devices/udevadm_info_--export-db" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/firewalld/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/ipmitool/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/kernel/sysctl_-a" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/logs/journalctl_--no-pager" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networking/ethtool_-S" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networking/ethtool_-i" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networking/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/networkmanager/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/memory/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/pam/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/sar/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/selinux/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/scsi/lsscsi" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/usb/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/virsh/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/yum/" ) == 0 ) ||
        ( strcmp ( member, "sos_commands/" ) == 0 ) ||
        ( strcmp ( member, "sys/module/" ) == 0 ) ||
        ( strcmp ( member, "usr/lib/systemd/" ) == 0 ) ||
        ( strcmp ( member, "usr/" ) == 0 ) ||
        ( strcmp ( member, "var/crash/" ) == 0 ) ||
        ( strcmp ( member, "var/log/audit/" ) == 0 ) ||
        ( strcmp ( member, "var/log/messages" ) == 0 ) ||
        ( strcmp ( member, "var/log/secure" ) == 0 ) ||
        ( strcmp ( member, "var/spool/cron/" ) == 0 ) ||
        ( strcmp ( member, "var/" ) == 0 )
    )
    {
        if ( strstr ( line , item ) != NULL )
            append_list ( &sos_line_obj, line );
        else
            return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

void free_sosreport_analyzer_obj ( void )
{
    if ( sos_header_obj != NULL ) 
        clear_list ( &sos_header_obj ); 
    if ( sos_subtitle_general_obj != NULL ) 
        clear_list ( &sos_subtitle_general_obj ); 
    if ( sos_subtitle_cpu_obj != NULL ) 
        clear_list ( &sos_subtitle_cpu_obj ); 
    if ( sos_subtitle_module_obj != NULL ) 
        clear_list ( &sos_subtitle_module_obj ); 
    if ( sos_subtitle_device_obj != NULL ) 
        clear_list ( &sos_subtitle_device_obj ); 
    if ( sos_subtitle_disk_usage_obj != NULL ) 
        clear_list ( &sos_subtitle_disk_usage_obj ); 
    if ( sos_subtitle_memory_usage_obj != NULL ) 
        clear_list ( &sos_subtitle_memory_usage_obj ); 
    if ( sos_subtitle_networking_obj != NULL ) 
        clear_list ( &sos_subtitle_networking_obj ); 
    if ( sos_subtitle_process_obj != NULL ) 
        clear_list ( &sos_subtitle_process_obj ); 
    if ( sos_subtitle_virtualization_obj != NULL ) 
        clear_list ( &sos_subtitle_virtualization_obj ); 
    if ( sos_subtitle_files_obj != NULL ) 
        clear_list ( &sos_subtitle_files_obj ); 
    if ( sos_subtitle_systemd_obj != NULL ) 
        clear_list ( &sos_subtitle_systemd_obj ); 
    if ( sos_subtitle_security_obj != NULL ) 
        clear_list ( &sos_subtitle_security_obj ); 
    if ( sos_subtitle_kernel_obj != NULL ) 
        clear_list ( &sos_subtitle_kernel_obj ); 
    if ( sos_subtitle_yum_obj != NULL ) 
        clear_list ( &sos_subtitle_yum_obj ); 
    if ( sos_subtitle_login_obj != NULL ) 
        clear_list ( &sos_subtitle_login_obj ); 
    if ( sos_subtitle_cron_obj != NULL ) 
        clear_list ( &sos_subtitle_cron_obj ); 
    if ( sos_subtitle_logrotate_obj != NULL ) 
        clear_list ( &sos_subtitle_logrotate_obj ); 
    if ( sos_subtitle_logs_and_journals_obj != NULL ) 
        clear_list ( &sos_subtitle_logs_and_journals_obj ); 
    if ( sos_subtitle_httpd_obj != NULL ) 
        clear_list ( &sos_subtitle_httpd_obj ); 
    if ( sos_subtitle_others_obj != NULL ) 
        clear_list ( &sos_subtitle_others_obj ); 
    if ( sos_line_obj != NULL ) 
        clear_list ( &sos_line_obj ); 
    if ( sos_tail_obj != NULL ) 
        clear_list ( &sos_tail_obj ); 

    if ( tmp_1_obj != NULL ) 
        clear_list ( &tmp_1_obj ); 
    if ( tmp_2_obj != NULL ) 
        clear_list ( &tmp_2_obj ); 
    if ( tmp_3_obj != NULL ) 
        clear_list ( &tmp_3_obj ); 
    if ( tmp_4_obj != NULL ) 
        clear_list ( &tmp_4_obj ); 
    if ( tmp_5_obj != NULL ) 
        clear_list ( &tmp_5_obj ); 
    if ( tmp_6_obj != NULL ) 
        clear_list ( &tmp_6_obj ); 
    if ( tmp_7_obj != NULL ) 
        clear_list ( &tmp_7_obj ); 
    if ( tmp_8_obj != NULL ) 
        clear_list ( &tmp_8_obj ); 
    if ( tmp_9_obj != NULL ) 
        clear_list ( &tmp_9_obj ); 
    if ( tmp_10_obj != NULL ) 
        clear_list ( &tmp_10_obj ); 
    if ( tmp_11_obj != NULL ) 
        clear_list ( &tmp_11_obj ); 
    if ( tmp_12_obj != NULL ) 
        clear_list ( &tmp_12_obj ); 
    if ( tmp_13_obj != NULL ) 
        clear_list ( &tmp_13_obj ); 
    if ( tmp_14_obj != NULL ) 
        clear_list ( &tmp_14_obj ); 
    if ( tmp_15_obj != NULL ) 
        clear_list ( &tmp_15_obj ); 
    if ( tmp_16_obj != NULL ) 
        clear_list ( &tmp_16_obj ); 
    if ( tmp_17_obj != NULL ) 
        clear_list ( &tmp_17_obj ); 
    if ( tmp_18_obj != NULL ) 
        clear_list ( &tmp_18_obj ); 
    if ( tmp_19_obj != NULL ) 
        clear_list ( &tmp_19_obj ); 
    if ( tmp_20_obj != NULL ) 
        clear_list ( &tmp_20_obj ); 
    if ( tmp_21_obj != NULL ) 
        clear_list ( &tmp_21_obj ); 
    if ( tmp_22_obj != NULL ) 
        clear_list ( &tmp_22_obj ); 
    if ( tmp_23_obj != NULL ) 
        clear_list ( &tmp_23_obj ); 
    if ( tmp_24_obj != NULL ) 
        clear_list ( &tmp_24_obj ); 
    if ( tmp_25_obj != NULL ) 
        clear_list ( &tmp_25_obj ); 
    if ( tmp_26_obj != NULL ) 
        clear_list ( &tmp_26_obj ); 
    if ( tmp_27_obj != NULL ) 
        clear_list ( &tmp_27_obj ); 
    if ( tmp_28_obj != NULL ) 
        clear_list ( &tmp_28_obj ); 
    if ( tmp_29_obj != NULL ) 
        clear_list ( &tmp_29_obj ); 
    if ( tmp_30_obj != NULL ) 
        clear_list ( &tmp_30_obj ); 
    if ( tmp_31_obj != NULL ) 
        clear_list ( &tmp_31_obj ); 
    if ( tmp_32_obj != NULL ) 
        clear_list ( &tmp_32_obj ); 
    if ( tmp_33_obj != NULL ) 
        clear_list ( &tmp_33_obj ); 
    if ( tmp_34_obj != NULL ) 
        clear_list ( &tmp_34_obj ); 
    if ( tmp_35_obj != NULL ) 
        clear_list ( &tmp_35_obj ); 
    if ( tmp_36_obj != NULL ) 
        clear_list ( &tmp_36_obj ); 
    if ( tmp_37_obj != NULL ) 
        clear_list ( &tmp_37_obj ); 
    if ( tmp_38_obj != NULL ) 
        clear_list ( &tmp_38_obj ); 
    if ( tmp_39_obj != NULL ) 
        clear_list ( &tmp_39_obj ); 
    if ( tmp_40_obj != NULL ) 
        clear_list ( &tmp_40_obj ); 
    if ( tmp_41_obj != NULL ) 
        clear_list ( &tmp_41_obj ); 
    if ( tmp_42_obj != NULL ) 
        clear_list ( &tmp_42_obj ); 
    if ( tmp_43_obj != NULL ) 
        clear_list ( &tmp_43_obj ); 
    if ( tmp_44_obj != NULL ) 
        clear_list ( &tmp_44_obj ); 
    if ( tmp_45_obj != NULL ) 
        clear_list ( &tmp_45_obj ); 
    if ( tmp_46_obj != NULL ) 
        clear_list ( &tmp_46_obj ); 
    if ( tmp_47_obj != NULL ) 
        clear_list ( &tmp_47_obj ); 
    if ( tmp_48_obj != NULL ) 
        clear_list ( &tmp_48_obj ); 
    if ( tmp_49_obj != NULL ) 
        clear_list ( &tmp_49_obj ); 
    if ( tmp_49_obj != NULL ) 
        clear_list ( &tmp_49_obj ); 
    if ( tmp_50_obj != NULL ) 
        clear_list ( &tmp_50_obj ); 
    if ( tmp_51_obj != NULL ) 
        clear_list ( &tmp_51_obj ); 
    if ( tmp_52_obj != NULL ) 
        clear_list ( &tmp_52_obj ); 
    if ( tmp_53_obj != NULL ) 
        clear_list ( &tmp_53_obj ); 
    if ( tmp_54_obj != NULL ) 
        clear_list ( &tmp_54_obj ); 
    if ( tmp_55_obj != NULL ) 
        clear_list ( &tmp_55_obj ); 
    if ( tmp_56_obj != NULL ) 
        clear_list ( &tmp_56_obj ); 
    if ( tmp_57_obj != NULL ) 
        clear_list ( &tmp_57_obj ); 
    if ( tmp_58_obj != NULL ) 
        clear_list ( &tmp_58_obj ); 
    if ( tmp_59_obj != NULL ) 
        clear_list ( &tmp_59_obj ); 
    if ( tmp_60_obj != NULL ) 
        clear_list ( &tmp_60_obj ); 

    if ( etc_pki__obj != NULL ) 
        clear_list ( &etc_pki__obj ); 
    if ( etc_cron_d__obj != NULL ) 
        clear_list ( &etc_cron_d__obj ); 
    if ( etc_sysconfig_network_scripts_ifcfg__obj != NULL ) 
        clear_list ( &etc_sysconfig_network_scripts_ifcfg__obj ); 
    if ( var_log_messages_obj != NULL ) 
        clear_list ( &var_log_messages_obj ); 
    if ( var_log_secure_obj != NULL ) 
        clear_list ( &var_log_secure_obj ); 
    if ( var_log_audit__obj != NULL ) 
        clear_list ( &var_log_audit__obj ); 
    if ( sos_commands_logs_journalctl___no_pager_obj != NULL ) 
        clear_list ( &sos_commands_logs_journalctl___no_pager_obj ); 
    if ( sos_commands_networking_ethtool__S_obj != NULL ) 
        clear_list ( &sos_commands_networking_ethtool__S_obj ); 
    if ( sos_commands_networking_ethtool__i_obj != NULL ) 
        clear_list ( &sos_commands_networking_ethtool__i_obj ); 
    if ( sos_commands_boot__obj != NULL ) 
        clear_list ( &sos_commands_boot__obj ); 
    if ( mcinfo_boot_grub__obj != NULL )
        clear_list ( &mcinfo_boot_grub__obj );
    if ( mcinfo_cmdlog__obj != NULL )
        clear_list ( &mcinfo_cmdlog__obj );
    if ( etc_httpd__obj != NULL ) 
        clear_list ( &etc_httpd__obj ); 
    if ( proc__obj != NULL ) 
        clear_list ( &proc__obj ); 
    if ( var_crash__obj != NULL ) 
        clear_list ( &var_crash__obj ); 
    if ( etc_default__obj != NULL ) 
        clear_list ( &etc_default__obj ); 
    if ( etc_logrotate_d__obj != NULL ) 
        clear_list ( &etc_logrotate_d__obj ); 
    if ( etc_modprobe_d__obj != NULL ) 
        clear_list ( &etc_modprobe_d__obj ); 
    if ( etc_host_obj != NULL ) 
        clear_list ( &etc_host_obj ); 
    if ( etc_udev__obj != NULL ) 
        clear_list ( &etc_udev__obj ); 
    if ( etc_yum_repos_d__obj != NULL ) 
        clear_list ( &etc_yum_repos_d__obj ); 
    if ( etc_systemd_system__obj != NULL ) 
        clear_list ( &etc_systemd_system__obj ); 
    if ( etc_systemd__obj != NULL ) 
        clear_list ( &etc_systemd__obj ); 
    if ( usr_lib_systemd__obj != NULL ) 
        clear_list ( &usr_lib_systemd__obj ); 
    if ( sos_commands_sar__obj != NULL ) 
        clear_list ( &sos_commands_sar__obj ); 
    if ( sos_commands_virsh__obj != NULL ) 
        clear_list ( &sos_commands_virsh__obj ); 
    if ( sos_commands_usb__obj != NULL ) 
        clear_list ( &sos_commands_usb__obj ); 
    if ( lib__obj != NULL ) 
        clear_list ( &lib__obj ); 
    if ( etc__obj != NULL ) 
        clear_list ( &etc__obj ); 
    if ( sos_commands_networking__obj != NULL ) 
        clear_list ( &sos_commands_networking__obj ); 
    if ( dev__obj != NULL ) 
        clear_list ( &dev__obj ); 
    if ( usr__obj != NULL ) 
        clear_list ( &usr__obj ); 
    if ( var__obj != NULL ) 
        clear_list ( &var__obj ); 
    if ( sos_commands_obj != NULL ) 
        clear_list ( &sos_commands_obj ); 
    if ( var_spool_cron__obj != NULL ) 
        clear_list ( &var_spool_cron__obj ); 
    if ( sos_commands_abrt__obj != NULL ) 
        clear_list ( &sos_commands_abrt__obj ); 
    if ( sys_module__obj != NULL ) 
        clear_list ( &sys_module__obj ); 
    if ( etc_pam_d__obj != NULL ) 
        clear_list ( &etc_pam_d__obj ); 
    if ( sos_commands_pam__obj != NULL ) 
        clear_list ( &sos_commands_pam__obj ); 
    if ( sos_commands_apache__obj != NULL ) 
        clear_list ( &sos_commands_apache__obj ); 
    if ( etc_audit__obj != NULL ) 
        clear_list ( &etc_audit__obj ); 
    if ( sos_commands_auditd__obj != NULL ) 
        clear_list ( &sos_commands_auditd__obj ); 
    if ( sos_commands_memory__obj != NULL ) 
        clear_list ( &sos_commands_memory__obj ); 
    if ( etc_firewalld__obj != NULL ) 
        clear_list ( &etc_firewalld__obj ); 
    if ( sos_commands_firewalld__obj != NULL ) 
        clear_list ( &sos_commands_firewalld__obj ); 
    if ( sos_commands_devicemapper__obj != NULL ) 
        clear_list ( &sos_commands_devicemapper__obj ); 
    if ( etc_sysconfig__obj != NULL ) 
        clear_list ( &etc_sysconfig__obj ); 
    if ( etc_selinux__obj != NULL ) 
        clear_list ( &etc_selinux__obj ); 
    if ( sos_commands_selinux__obj != NULL ) 
        clear_list ( &sos_commands_selinux__obj ); 
    if ( etc_yum__obj != NULL ) 
        clear_list ( &etc_yum__obj ); 
    if ( sos_commands_yum__obj != NULL ) 
        clear_list ( &sos_commands_yum__obj ); 
    if ( etc_dnf__obj != NULL ) 
        clear_list ( &etc_dnf__obj ); 
    if ( sos_commands_dnf__obj != NULL ) 
        clear_list ( &sos_commands_dnf__obj ); 
    if ( etc_cron_hourly__obj != NULL ) 
        clear_list ( &etc_cron_hourly__obj ); 
    if ( etc_cron_daily__obj != NULL ) 
        clear_list ( &etc_cron_daily__obj ); 
    if ( etc_cron_weekly__obj != NULL ) 
        clear_list ( &etc_cron_weekly__obj ); 
    if ( etc_cron_monthly__obj != NULL ) 
        clear_list ( &etc_cron_monthly__obj ); 
    if ( sos_commands_networkmanager__obj != NULL ) 
        clear_list ( &sos_commands_networkmanager__obj ); 
    if ( etc_networkmanager__obj != NULL ) 
        clear_list ( &etc_networkmanager__obj ); 
    if ( sos_commands_ipmitool__obj != NULL ) 
        clear_list ( &sos_commands_ipmitool__obj ); 
}
