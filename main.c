/*
 * main.c - main file for sosreport-analyzer.
 * This file contains the contents of sosreport-analyzer.
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
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libsosreport-analyzer/cfg.h"
#include "libsosreport-analyzer/common.h"
#include "libsosreport-analyzer/line_data.h"
#include "libsar-analyzer/common.h"

/* configuration file of this program/library */
static const char *fname = "/etc/sosreport-analyzer.conf";
static const char *fname_mcinfo = "/etc/sosreport-analyzer-mcinfo.conf";
static const char *fname_example = "/usr/share/sosreport-analyzer/sosreport-analyzer.conf.example";
static const char *fname_mcinfo_example = "/usr/share/sosreport-analyzer/sosreport-analyzer-mcinfo.conf.example";

const char *app_name = "sosreport-analyzer";

/* brief Print help for this application */
static void print_help ( void )
{
    printf("\n VERSION %d.%d.%d\n",PROGRAM_VERSION,PROGRAM_RELEASE,PROGRAM_SUB_RELEASE);
    printf("\n Configuration:\n");
    printf("\n   For sosreport\n");
    printf("\n     Edit '%s'. \n",fname);
    printf("     If you are unsure, copy from '%s' to %s.\n",fname_example,fname);
    printf("\n   For mcinfo\n");
    printf("\n     Edit '%s'.\n",fname_mcinfo);
    printf("     If you are unsure, copy from '%s' to %s.\n",fname_mcinfo_example,fname_mcinfo);
    printf("\n Options:\n\n");
    printf("   -D|--directory <path_to_sosreport_directory>\n");
    printf("                     Analyze files in the directory\n");
    printf("   -M|--mcinfo       Analyze mcinfo files\n");
    printf("   -S|--sar-only     Analyze sar files only\n");
    printf("   -T|--time-span    Analyze time-span on sar files\n");
    printf("   -h|--help         Print this help\n");
    printf("\n Usage:\n\n");
    printf("   To analyze sosreport (including sar analyzing)\n\n");
    printf("     $ %s -D <path_to_sosreport_directory>\n\n",app_name);
    printf("   To analyze  mcinfo (including sar analyzing)\n\n");
    printf("     $ %s -M -D <path_to_mcinfo_directory>\n\n",app_name);
    printf("   For only sar analyzing\n\n");
    printf("     $ %s -S -D <path_to_sa_directory>\n\n",app_name);
    printf("   For time-span sar analyzing\n\n");
    printf("     ex. $ %s -T 09:00-10:00 -D <path_to_sa_directory>\n\n",app_name);
    printf("   Directory 'sar-analyzer-results' will be made in the current directory with files.\n");
    printf("\n Note:\n\n");
    printf("   Use appropriate config file which is stored in /usr/share/sosreport-analyzer\n");
    printf("   and copy it as '/etc/sosreport-analyzer.conf'.\n");
    printf("   You can set items to each member in conf file.\n");
    printf("\n");
}

/* Main function */
int main ( int argc, char *argv [ ] )
{
    if ( ! isatty ( fileno ( stdout ) ) )
    {
        fprintf(stderr,"You are not a terminal!\n");
        fprintf(stderr,"You are not allowed to redirect to a file.\n");
        return EXIT_FAILURE;
    }
    if ( argc <=2 )
    {
        print_help ( );
        return EXIT_FAILURE;
    }

    /* sosreport-analyzer */

    /* initialize the line list object (node) */
    /* sos_dir_file_obj doesn't need to be initialized */
    init_list ( &sos_header_obj );
    init_list ( &sos_subtitle_general_obj );
    init_list ( &sos_subtitle_cpu_obj );
    init_list ( &sos_subtitle_module_obj );
    init_list ( &sos_subtitle_device_obj );
    init_list ( &sos_subtitle_file_systems_obj );
    init_list ( &sos_subtitle_disk_usage_obj );
    init_list ( &sos_subtitle_memory_usage_obj );
    init_list ( &sos_subtitle_networking_obj );
    init_list ( &sos_subtitle_process_obj );
    init_list ( &sos_subtitle_virtualization_obj );
    init_list ( &sos_subtitle_files_obj );
    init_list ( &sos_subtitle_systemd_obj );
    init_list ( &sos_subtitle_security_obj );
    init_list ( &sos_subtitle_kernel_obj );
    init_list ( &sos_subtitle_yum_obj );
    init_list ( &sos_subtitle_login_obj );
    init_list ( &sos_subtitle_cron_obj );
    init_list ( &sos_subtitle_logrotate_obj );
    init_list ( &sos_subtitle_logs_and_journals_obj );
    init_list ( &sos_subtitle_httpd_obj );
    init_list ( &sos_subtitle_others_obj );
    init_list ( &sos_line_obj );
    init_list ( &sos_tail_obj );

    init_list ( &tmp_1_obj );
    init_list ( &tmp_2_obj );
    init_list ( &tmp_3_obj );
    init_list ( &tmp_4_obj );
    init_list ( &tmp_5_obj );
    init_list ( &tmp_6_obj );
    init_list ( &tmp_7_obj );
    init_list ( &tmp_8_obj );
    init_list ( &tmp_9_obj );
    init_list ( &tmp_10_obj );
    init_list ( &tmp_11_obj );
    init_list ( &tmp_12_obj );
    init_list ( &tmp_13_obj );
    init_list ( &tmp_14_obj );
    init_list ( &tmp_15_obj );
    init_list ( &tmp_16_obj );
    init_list ( &tmp_17_obj );
    init_list ( &tmp_18_obj );
    init_list ( &tmp_19_obj );
    init_list ( &tmp_20_obj );
    init_list ( &tmp_21_obj );
    init_list ( &tmp_22_obj );
    init_list ( &tmp_23_obj );
    init_list ( &tmp_24_obj );
    init_list ( &tmp_25_obj );
    init_list ( &tmp_26_obj );
    init_list ( &tmp_27_obj );
    init_list ( &tmp_28_obj );
    init_list ( &tmp_29_obj );
    init_list ( &tmp_30_obj );
    init_list ( &tmp_31_obj );
    init_list ( &tmp_32_obj );
    init_list ( &tmp_33_obj );
    init_list ( &tmp_34_obj );
    init_list ( &tmp_35_obj );
    init_list ( &tmp_36_obj );
    init_list ( &tmp_37_obj );
    init_list ( &tmp_38_obj );
    init_list ( &tmp_39_obj );
    init_list ( &tmp_40_obj );
    init_list ( &tmp_41_obj );
    init_list ( &tmp_42_obj );
    init_list ( &tmp_43_obj );
    init_list ( &tmp_44_obj );
    init_list ( &tmp_45_obj );
    init_list ( &tmp_46_obj );
    init_list ( &tmp_47_obj );
    init_list ( &tmp_48_obj );
    init_list ( &tmp_49_obj );
    init_list ( &tmp_50_obj );
    init_list ( &tmp_51_obj );
    init_list ( &tmp_52_obj );
    init_list ( &tmp_53_obj );
    init_list ( &tmp_54_obj );
    init_list ( &tmp_55_obj );
    init_list ( &tmp_56_obj );
    init_list ( &tmp_57_obj );
    init_list ( &tmp_58_obj );
    init_list ( &tmp_59_obj );
    init_list ( &tmp_60_obj );
    init_list ( &tmp_61_obj );
    init_list ( &tmp_62_obj );
    init_list ( &tmp_63_obj );

    init_list ( &mcinfo_boot_grub__obj );
    init_list ( &mcinfo_cmdlog__obj );
    init_list ( &etc_pki__obj );
    init_list ( &etc_cron_d__obj );
    init_list ( &etc_sysconfig_network_scripts_ifcfg__obj );
    init_list ( &var_log_messages_obj );
    init_list ( &var_log_secure_obj );
    init_list ( &var_log_audit__obj );
    init_list ( &sos_commands_logs_journalctl___no_pager_obj );
    init_list ( &sos_commands_networking_ethtool__S_obj );
    init_list ( &sos_commands_networking_ethtool__i_obj );
    init_list ( &sos_commands_boot__obj );
    init_list ( &etc_httpd__obj );
    init_list ( &proc__obj );
    init_list ( &var_crash__obj );
    init_list ( &etc_default__obj );
    init_list ( &etc_logrotate_d__obj );
    init_list ( &etc_modprobe_d__obj );
    init_list ( &etc_host_obj );
    init_list ( &etc_udev__obj );
    init_list ( &etc_yum_repos_d__obj );
    init_list ( &etc_systemd_system__obj );
    init_list ( &etc_systemd__obj );
    init_list ( &usr_lib_systemd__obj );
    init_list ( &sos_commands_sar__obj );
    init_list ( &sos_commands_virsh__obj );
    init_list ( &sos_commands_usb__obj );
    init_list ( &lib__obj );
    init_list ( &etc__obj );
    init_list ( &sos_commands_networking__obj );
    init_list ( &dev__obj );
    init_list ( &usr__obj );
    init_list ( &var__obj );
    init_list ( &sos_commands_obj );
    init_list ( &var_spool_cron__obj );
    init_list ( &sos_commands_abrt__obj );
    init_list ( &sys_module__obj );
    init_list ( &etc_pam_d__obj );
    init_list ( &sos_commands_pam__obj );
    init_list ( &sos_commands_apache__obj );
    init_list ( &etc_audit__obj );
    init_list ( &sos_commands_auditd__obj );
    init_list ( &sos_commands_memory__obj );
    init_list ( &etc_firewalld__obj );
    init_list ( &sos_commands_firewalld__obj );
    init_list ( &sos_commands_devicemapper__obj );
    init_list ( &etc_sysconfig__obj );
    init_list ( &etc_selinux__obj );
    init_list ( &sos_commands_selinux__obj );
    init_list ( &etc_yum__obj );
    init_list ( &sos_commands_yum__obj );
    init_list ( &etc_dnf__obj );
    init_list ( &sos_commands_dnf__obj );
    init_list ( &etc_cron_hourly__obj );
    init_list ( &etc_cron_daily__obj );
    init_list ( &etc_cron_weekly__obj );
    init_list ( &etc_cron_monthly__obj );
    init_list ( &sos_commands_networkmanager__obj );
    init_list ( &etc_networkmanager__obj );
    init_list ( &sos_commands_ipmitool__obj );
    init_list ( &sos_commands_wireless__obj );
    init_list ( &etc_lvm__obj );
    init_list ( &sos_commands_lvm2__obj );

    char str_tmp [ MAX_FILE_NAME_LENGTH ]; 
    char str_tmp2 [ MAX_FILE_NAME_LENGTH ]; 
    char str_tmp3 [ MAX_FILE_NAME_LENGTH ]; 
    char dir_sa [ MAX_FILE_NAME_LENGTH ]; 
    memset ( str_tmp, '\0', sizeof ( str_tmp ) ); 
    memset ( str_tmp2, '\0', sizeof ( str_tmp2 ) ); 
    memset ( str_tmp3, '\0', sizeof ( str_tmp3 ) ); 
    memset ( dir_sa, '\0', sizeof ( dir_sa ) ); 
    append_list ( &sos_header_obj, "####" );
    snprintf ( str_tmp2, MAX_FILE_NAME_LENGTH, "%s: Version-%d.%d.%d", app_name, PROGRAM_VERSION, PROGRAM_RELEASE, PROGRAM_SUB_RELEASE ); 
    append_list ( &sos_header_obj, str_tmp2 );
    append_list ( &sos_header_obj, "####" );
    append_list ( &sos_tail_obj, "####" );
    memset ( str_tmp2, '\0', sizeof ( str_tmp2 ) ); 
    snprintf ( str_tmp2, MAX_FILE_NAME_LENGTH, "%s ends.", app_name ); 
    append_list ( &sos_tail_obj, str_tmp2 );

    int dir_len_check = 255;
    int dir_len = 0;
    int value = 0;
    int mcinfo = 0;
    int sar_only = 0;
    int i = 0;
    int v = 0;
    int x = 0;
    int time_span_str_len = 0;
    const char *dir_name = NULL;
    const char *time_span = NULL;

    while(1)
    {
        int option_index = 0;
        static struct option long_options [ ] = {
            { "directory", required_argument, 0, 'D' },
            { "mcinfo", no_argument, 0, 'M' },
            { "sar-only", no_argument, 0, 'S' },
            { "time-span", required_argument, 0, 'T' },
            { "help", no_argument, 0, 'h' },
            { NULL, 0, 0, 0 }
        };

        /* Try to process all command line arguments */
        value = getopt_long ( argc, argv, "hMST:D:", long_options, &option_index );
        if ( value == -1 )
            break;
        switch ( value ) {
            case 'h':
                print_help ( );
                return EXIT_SUCCESS;
                break;
            case '?':
                print_help ( );
                return EXIT_FAILURE;
                break;
            case 'D':
                dir_name = optarg;
                if ( dir_name == NULL )
                {
                    printf("Please set directory name.\n");
                    print_help ( );
                    return EXIT_FAILURE;
                }
                dir_len = ( int ) strlen ( dir_name );
                if ( dir_len <= 0 )
                {
                    print_help ( );
                    return EXIT_FAILURE;
                }
                if ( strstr ( dir_name,"\n" ) != NULL || ( dir_len > dir_len_check ) )
                {
                    printf("Can't analyze this directory.\n");
                    print_help ( );
                    return EXIT_FAILURE;
                }else{
                    strcpy ( sos_dir_file_obj->dir_file_names.dirname, dir_name );
                    strcpy ( str_tmp2, reverse_the_string ( ( char * ) dir_name, dir_len ) );
                    for ( i = 0; i < dir_len; i++ )
                    {
                    if ( i > 0 )
                        str_tmp2[i] = '\0';
                    }
                    if ( strcmp ( str_tmp2, "/" ) == 0 )
                    {
                        strcpy ( str_tmp2, ( char * ) dir_name );
                        str_tmp2 [ dir_len -1 ] = '\0';
                        strcpy ( sos_dir_file_obj->dir_file_names.dirname, str_tmp2 );
                    }
                    snprintf ( str_tmp2, MAX_FILE_NAME_LENGTH, "dirname:%s",dir_name );
                    append_list ( &sos_header_obj, str_tmp2 );
                    append_list ( &sos_header_obj, "" );
                }
                break;
            case 'M':
                fname = "/etc/sosreport-analyzer-mcinfo.conf";
                mcinfo = 1;
                break;
            case 'S':
                sar_only = 1;
                break;
            case 'T':
                time_span = optarg;
                time_span_str_len = ( int ) strlen ( time_span );
                if ( ( time_span_str_len <= 0 ) || ( time_span_str_len > 11 ) )
                {
                    print_help ( );
                    return EXIT_FAILURE;
                }
                if ( ! ( check_time_span_str ( time_span ) ) )
                {
                    print_help ( );
                    return EXIT_FAILURE;
                }
                break;
            default:
                print_help ( );
                return EXIT_FAILURE;
                break;
        }
    }

    if ( dir_name == NULL )
    {
        printf("\nOoops! You forgot setting directory...\n");
        print_help ( );
        return EXIT_FAILURE;
    }
    /* sosreport-analyzer */

    /* read sosreport files */
    cfg_init ( fname, mcinfo );

    char *hairline = "----";

    printf("\nNotice: You can set 'skip' to the member in the conf file when there is no such directory.\n\n");
    if ( sar_only != 1 )
    {
        /* this is the actual order which each member will be written to a file */
        /* it should be the same order as one which had been set in cfg.c */
        if ( mcinfo == 1 )
        {
            read_file_pre ( "proc/cpuinfo", dir_name );
            read_file_pre ( "boot/grub/", dir_name );
            read_file_pre ( "etc/sysconfig/network-scripts/ifcfg-", dir_name );
            read_file_pre ( "cmdlog/", dir_name );
            read_file_pre ( "etc/host", dir_name );
            read_file_pre ( "proc/meminfo", dir_name );
            read_file_pre ( "proc/zoneinfo", dir_name );
            read_file_pre ( "proc/buddyinfo", dir_name );
            read_file_pre ( "proc/slabinfo", dir_name );
            read_file_pre ( "proc/vmstat", dir_name );
            read_file_pre ( "proc/interrupts", dir_name );
            read_file_pre ( "var/log/dmesg", dir_name );
            read_file_pre ( "etc/crontab", dir_name );
            read_file_pre ( "etc/cron.deny", dir_name );
            read_file_pre ( "etc/cron.d/", dir_name );
            read_file_pre ( "etc/cron.hourly/", dir_name );
            read_file_pre ( "etc/cron.daily/", dir_name );
            read_file_pre ( "etc/cron.weekly/", dir_name );
            read_file_pre ( "etc/cron.monthly/", dir_name );
            read_file_pre ( "var/spool/cron/", dir_name );
            read_file_pre ( "var/log/messages", dir_name );
            read_file_pre ( "var/crash/", dir_name );
            read_file_pre ( "etc/", dir_name );
            read_file_pre ( "dev/", dir_name );
            read_file_pre ( "usr/", dir_name );
            read_file_pre ( "var/", dir_name );
            read_file_pre ( "proc/", dir_name );
            append_list ( &sos_header_obj, "Also, read these files." );
            append_list ( &sos_header_obj, hairline );
            append_list ( &mcinfo_boot_grub__obj, hairline );
            append_list ( &etc_sysconfig_network_scripts_ifcfg__obj, hairline );
            append_list ( &mcinfo_cmdlog__obj, hairline );
            append_list ( &etc_host_obj, hairline );
            append_list ( &etc_cron_d__obj, hairline );
            append_list ( &etc_cron_hourly__obj, hairline );
            append_list ( &etc_cron_daily__obj, hairline );
            append_list ( &etc_cron_weekly__obj, hairline );
            append_list ( &etc_cron_monthly__obj, hairline );
            append_list ( &var_spool_cron__obj, hairline );
            append_list ( &var_log_messages_obj, hairline );
            append_list ( &var_crash__obj, hairline );
            append_list ( &proc__obj, hairline );
            append_list ( &etc__obj, hairline );
            append_list ( &dev__obj, hairline );
            append_list ( &usr__obj, hairline );
            append_list ( &var__obj, hairline );
        }
        if ( mcinfo == 0 )
        {
            /* general */
            read_file_pre ( "date", dir_name );
            read_file_pre ( "lsb-release", dir_name );
            read_file_pre ( "uname", dir_name );
            read_file_pre ( "hostname", dir_name );
            read_file_pre ( "uptime", dir_name );
            read_file_pre ( "etc/nsswitch.conf", dir_name );
            read_file_pre ( "installed-rpms", dir_name );
            read_file_pre ( "proc/cpuinfo", dir_name );
            read_file_pre ( "root/anaconda-ks.cfg", dir_name );
            read_file_pre ( "dmidecode", dir_name );
            read_file_pre ( "etc/default/", dir_name );
            read_file_pre ( "etc/sysconfig/", dir_name );
            read_file_pre ( "sos_commands/boot/", dir_name );
            /* cpu */
            read_file_pre ( "proc/interrupts", dir_name );
            /* module */
            read_file_pre ( "lsmod", dir_name );
            read_file_pre ( "etc/modprobe.d/", dir_name );
            read_file_pre ( "sys/module/", dir_name );
            /* device */
            read_file_pre ( "lspci", dir_name );
            read_file_pre ( "etc/udev/", dir_name );
            read_file_pre ( "sos_commands/devicemapper/", dir_name );
            read_file_pre ( "sos_commands/devices/udevadm_info_--export-db", dir_name );
            read_file_pre ( "sos_commands/ipmitool/", dir_name );
            read_file_pre ( "sos_commands/scsi/lsscsi", dir_name );
            read_file_pre ( "sos_commands/usb/", dir_name );
            /* file systems */
            read_file_pre ( "etc/lvm/", dir_name );
            read_file_pre ( "sos_commands/lvm2/", dir_name );
            /* disk usage */
            read_file_pre ( "df", dir_name );
            read_file_pre ( "vgdisplay", dir_name );
            /* memory usage */
            read_file_pre ( "free", dir_name );
            read_file_pre ( "sos_commands/memory/", dir_name );
            read_file_pre ( "proc/meminfo", dir_name );
            read_file_pre ( "proc/zoneinfo", dir_name );
            read_file_pre ( "proc/buddyinfo", dir_name );
            read_file_pre ( "proc/slabinfo", dir_name );
            read_file_pre ( "proc/vmstat", dir_name );
            /* networking */
            read_file_pre ( "etc/host", dir_name );
            read_file_pre ( "ip_addr", dir_name );
            read_file_pre ( "route", dir_name );
            read_file_pre ( "etc/sysconfig/network-scripts/ifcfg-", dir_name );
            read_file_pre ( "etc/firewalld/", dir_name );
            read_file_pre ( "sos_commands/firewalld/", dir_name );
            read_file_pre ( "proc/net/dev", dir_name );
            read_file_pre ( "proc/net/sockstat", dir_name );
            read_file_pre ( "sos_commands/networking/ethtool_-S", dir_name );
            read_file_pre ( "sos_commands/networking/ethtool_-i", dir_name );
            read_file_pre ( "sos_commands/networking/", dir_name );
            read_file_pre ( "etc/NetworkManager/", dir_name );
            read_file_pre ( "sos_commands/networkmanager/", dir_name );
            read_file_pre ( "sos_commands/wireless/", dir_name );
            read_file_pre ( "netstat", dir_name );
            /* process */
            read_file_pre ( "ps", dir_name );
            /* virtualization */
            read_file_pre ( "sos_commands/virsh/", dir_name );
            /* files */
            read_file_pre ( "lsof", dir_name );
            /* systemd */
            read_file_pre ( "etc/systemd/system/", dir_name );
            read_file_pre ( "etc/systemd/", dir_name );
            read_file_pre ( "usr/lib/systemd/", dir_name );
            /* security */
            read_file_pre ( "etc/pam.d/", dir_name );
            read_file_pre ( "sos_commands/pam/", dir_name );
            read_file_pre ( "var/log/secure", dir_name );
            read_file_pre ( "etc/audit/", dir_name );
            read_file_pre ( "sos_commands/auditd/", dir_name );
            read_file_pre ( "var/log/audit/", dir_name );
            read_file_pre ( "etc/pki/", dir_name );
            read_file_pre ( "etc/selinux/", dir_name );
            read_file_pre ( "sos_commands/selinux/", dir_name );
            /* kernel */
            read_file_pre ( "etc/kdump.conf", dir_name );
            read_file_pre ( "etc/sysctl.conf", dir_name );
            read_file_pre ( "sos_commands/kernel/sysctl_-a", dir_name );
            read_file_pre ( "var/crash/", dir_name );
            read_file_pre ( "sos_commands/abrt/", dir_name );
            /* dnf/yum */
            read_file_pre ( "etc/yum.conf", dir_name );
            read_file_pre ( "etc/yum.repos.d/", dir_name );
            read_file_pre ( "etc/yum/", dir_name );
            read_file_pre ( "sos_commands/yum/", dir_name );
            read_file_pre ( "etc/dnf/", dir_name );
            read_file_pre ( "sos_commands/dnf/", dir_name );
            /* login */
            read_file_pre ( "last", dir_name );
            /* cron */
            read_file_pre ( "etc/anacrontab", dir_name );
            read_file_pre ( "etc/crontab", dir_name );
            read_file_pre ( "etc/cron.deny", dir_name );
            read_file_pre ( "etc/cron.d/", dir_name );
            read_file_pre ( "etc/cron.hourly/", dir_name );
            read_file_pre ( "etc/cron.daily/", dir_name );
            read_file_pre ( "etc/cron.weekly/", dir_name );
            read_file_pre ( "etc/cron.monthly/", dir_name );
            read_file_pre ( "var/spool/cron/", dir_name );
            /* logrotate */
            read_file_pre ( "etc/logrotate.conf", dir_name );
            read_file_pre ( "etc/logrotate.d/", dir_name );
            /* logs and journals */
            read_file_pre ( "etc/rsyslog.conf", dir_name );
            read_file_pre ( "var/log/dmesg", dir_name );
            read_file_pre ( "var/log/messages", dir_name );
            read_file_pre ( "sos_commands/logs/journalctl_--no-pager", dir_name );
            read_file_pre ( "sos_commands/sar/", dir_name );
            /* httpd */
            read_file_pre ( "etc/httpd/", dir_name );
            read_file_pre ( "sos_commands/apache/", dir_name );
            /* others ( default item is 'skip') */
            read_file_pre ( "lib/", dir_name );
            read_file_pre ( "etc/", dir_name );
            read_file_pre ( "sos_commands/", dir_name );
            read_file_pre ( "dev/", dir_name );
            read_file_pre ( "usr/", dir_name );
            read_file_pre ( "var/", dir_name );
            read_file_pre ( "proc/", dir_name );
            append_list ( &sos_header_obj, "Also, read these files." );
            /* general */
            append_list ( &sos_header_obj, hairline );
            append_list ( &sos_commands_boot__obj, hairline );
            append_list ( &etc_host_obj, hairline );
            append_list ( &etc_default__obj, hairline );
            append_list ( &etc_sysconfig__obj, hairline );
            /* cpu */
            /* module */
            append_list ( &etc_modprobe_d__obj, hairline );
            append_list ( &sys_module__obj, hairline );
            /* device */
            append_list ( &etc_udev__obj, hairline );
            append_list ( &sos_commands_devicemapper__obj, hairline );
            append_list ( &sos_commands_usb__obj, hairline );
            /* disk usage */
            /* memory usage */
            append_list ( &sos_commands_memory__obj, hairline );
            /* networking */
            append_list ( &etc_sysconfig_network_scripts_ifcfg__obj, hairline );
            append_list ( &sos_commands_networking_ethtool__S_obj, hairline );
            append_list ( &sos_commands_networking_ethtool__i_obj, hairline );
            append_list ( &sos_commands_networking__obj, hairline );
            append_list ( &etc_firewalld__obj, hairline );
            append_list ( &sos_commands_firewalld__obj, hairline );
            append_list ( &etc_networkmanager__obj, hairline );
            append_list ( &sos_commands_networkmanager__obj, hairline );
            append_list ( &sos_commands_wireless__obj, hairline );
            /* process */
            /* virtualization */
            append_list ( &sos_commands_virsh__obj, hairline );
            /* files */
            /* systemd */
            append_list ( &etc_systemd_system__obj, hairline );
            append_list ( &etc_systemd__obj, hairline );
            append_list ( &usr_lib_systemd__obj, hairline );
            /* security */
            append_list ( &etc_audit__obj, hairline );
            append_list ( &var_log_audit__obj, hairline );
            append_list ( &sos_commands_auditd__obj, hairline );
            append_list ( &etc_pam_d__obj, hairline );
            append_list ( &sos_commands_pam__obj, hairline );
            append_list ( &etc_selinux__obj, hairline );
            append_list ( &sos_commands_selinux__obj, hairline );
            append_list ( &var_log_secure_obj, hairline );
            /* kernel */
            append_list ( &sos_commands_abrt__obj, hairline );
            append_list ( &var_crash__obj, hairline );
            /* dnf/yum */
            append_list ( &etc_yum_repos_d__obj, hairline );
            append_list ( &sos_commands_yum__obj, hairline );
            append_list ( &etc_yum__obj, hairline );
            append_list ( &etc_dnf__obj, hairline );
            append_list ( &sos_commands_dnf__obj, hairline );
            /* login */
            /* cron */
            append_list ( &etc_cron_d__obj, hairline );
            append_list ( &etc_cron_hourly__obj, hairline );
            append_list ( &etc_cron_daily__obj, hairline );
            append_list ( &etc_cron_weekly__obj, hairline );
            append_list ( &etc_cron_monthly__obj, hairline );
            append_list ( &var_spool_cron__obj, hairline );
            /* logrotate */
            append_list ( &etc_logrotate_d__obj, hairline );
            /* logs and journals */
            append_list ( &sos_commands_logs_journalctl___no_pager_obj, hairline );
            append_list ( &var_log_messages_obj, hairline );
            append_list ( &sos_commands_sar__obj, hairline );
            append_list ( &etc_pki__obj, hairline );
            /* httpd */
            append_list ( &etc_httpd__obj, hairline );
            append_list ( &sos_commands_apache__obj, hairline );
            /* others ( default item is 'skip') */
            append_list ( &lib__obj, hairline );
            append_list ( &etc__obj, hairline );
            append_list ( &sos_commands_obj, hairline );
            append_list ( &dev__obj, hairline );
            append_list ( &usr__obj, hairline );
            append_list ( &var__obj, hairline );
            append_list ( &proc__obj, hairline );
        }
    }

    sos_file_to_write ( );

    const char *sos_file_write = ""; 
    FILE *fp_w;
    /* --------  for file write --------*/
    sos_file_write = get_sos_file_name_to_be_written ( );

    /* open result directory */
    char str_dir_result [ MAX_FILE_NAME_LENGTH ]; 
    memset ( str_dir_result, '\0', sizeof ( str_dir_result ) ); 
    strncpy ( str_dir_result, "./sosreport-analyzer-results", MAX_FILE_NAME_LENGTH );
    if ( check_result_dir ( str_dir_result ) != 0 )
        printf("can't open dir %s (%s)\n",str_dir_result,strerror(errno));

    if ( sar_only == 0 )
    {
        /* open result file */
        if ( ( fp_w = fopen ( sos_file_write, "a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n",sos_file_write,strerror(errno));
            exit ( EXIT_FAILURE );
        }

        /* header and config related lines and 'also read these files' stuff */
        /* keep the order same as cfg.c */
        file_write_list ( &sos_header_obj, fp_w );
        if ( mcinfo == 1 )
        {
            file_write_list ( &mcinfo_boot_grub__obj, fp_w );
            file_write_list ( &etc_host_obj, fp_w );
            file_write_list ( &etc_sysconfig_network_scripts_ifcfg__obj, fp_w );
            file_write_list ( &mcinfo_cmdlog__obj, fp_w );
            file_write_list ( &etc_cron_d__obj, fp_w );
            file_write_list ( &etc_cron_hourly__obj, fp_w );
            file_write_list ( &etc_cron_daily__obj, fp_w );
            file_write_list ( &etc_cron_weekly__obj, fp_w );
            file_write_list ( &etc_cron_monthly__obj, fp_w );
            file_write_list ( &var_spool_cron__obj, fp_w );
            file_write_list ( &var_log_messages_obj, fp_w );
            file_write_list ( &var_log_secure_obj, fp_w );
            file_write_list ( &var_crash__obj, fp_w );
            file_write_list ( &etc__obj, fp_w );
            file_write_list ( &dev__obj, fp_w );
            file_write_list ( &usr__obj, fp_w );
            file_write_list ( &var__obj, fp_w );
            file_write_list ( &proc__obj, fp_w );
        }
        if ( mcinfo == 0 )
        {
            /* general */
            append_list ( &sos_subtitle_general_obj, "==== general ====" );
            file_write_list ( &sos_subtitle_general_obj, fp_w );
            file_write_list ( &etc_default__obj, fp_w );
            file_write_list ( &etc_sysconfig__obj, fp_w );
            file_write_list ( &sos_commands_boot__obj, fp_w );
            /* cpu */
            append_list ( &sos_subtitle_cpu_obj, "==== cpu ====" );
            file_write_list ( &sos_subtitle_cpu_obj, fp_w );
            /* module */
            append_list ( &sos_subtitle_module_obj, "==== module ====" );
            file_write_list ( &sos_subtitle_module_obj, fp_w );
            file_write_list ( &etc_modprobe_d__obj, fp_w );
            file_write_list ( &sys_module__obj, fp_w );
            /* device */
            append_list ( &sos_subtitle_device_obj, "==== device ====" );
            file_write_list ( &sos_subtitle_device_obj, fp_w );
            file_write_list ( &etc_udev__obj, fp_w );
            file_write_list ( &sos_commands_devicemapper__obj, fp_w );
            file_write_list ( &sos_commands_usb__obj, fp_w );
            /* file systems */
            file_write_list ( &etc_lvm__obj, fp_w );
            file_write_list ( &sos_commands_lvm2__obj, fp_w );
            /* disk usage */
            append_list ( &sos_subtitle_disk_usage_obj, "==== disk_usage ====" );
            file_write_list ( &sos_subtitle_disk_usage_obj, fp_w );
            /* memory usage */
            append_list ( &sos_subtitle_memory_usage_obj, "==== memory_usage ====" );
            file_write_list ( &sos_subtitle_memory_usage_obj, fp_w );
            file_write_list ( &sos_commands_memory__obj, fp_w );
            /* networking */
            append_list ( &sos_subtitle_networking_obj, "==== networking ====" );
            file_write_list ( &sos_subtitle_networking_obj, fp_w );
            file_write_list ( &etc_host_obj, fp_w );
            file_write_list ( &etc_sysconfig_network_scripts_ifcfg__obj, fp_w );
            file_write_list ( &etc_firewalld__obj, fp_w );
            file_write_list ( &sos_commands_firewalld__obj, fp_w );
            file_write_list ( &sos_commands_networking_ethtool__S_obj, fp_w );
            file_write_list ( &sos_commands_networking_ethtool__i_obj, fp_w );
            file_write_list ( &sos_commands_networking__obj, fp_w );
            file_write_list ( &etc_networkmanager__obj, fp_w );
            file_write_list ( &sos_commands_networkmanager__obj, fp_w );
            file_write_list ( &sos_commands_wireless__obj, fp_w );
            /* process */
            append_list ( &sos_subtitle_process_obj, "==== process ====" );
            file_write_list ( &sos_subtitle_process_obj, fp_w );
            /* virtualization */
            append_list ( &sos_subtitle_virtualization_obj, "==== virtualization ====" );
            file_write_list ( &sos_subtitle_virtualization_obj, fp_w );
            file_write_list ( &sos_commands_virsh__obj, fp_w );
            /* files */
            append_list ( &sos_subtitle_files_obj, "==== files ====" );
            file_write_list ( &sos_subtitle_files_obj, fp_w );
            /* systemd */
            append_list ( &sos_subtitle_systemd_obj, "==== systemd ====" );
            file_write_list ( &sos_subtitle_systemd_obj, fp_w );
            file_write_list ( &etc_systemd_system__obj, fp_w );
            file_write_list ( &etc_systemd__obj, fp_w );
            file_write_list ( &usr_lib_systemd__obj, fp_w );
            /* security */
            append_list ( &sos_subtitle_security_obj, "==== security ====" );
            file_write_list ( &sos_subtitle_security_obj, fp_w );
            file_write_list ( &etc_pam_d__obj, fp_w );
            file_write_list ( &sos_commands_pam__obj, fp_w );
            file_write_list ( &var_log_secure_obj, fp_w );
            file_write_list ( &etc_audit__obj, fp_w );
            file_write_list ( &sos_commands_auditd__obj, fp_w );
            file_write_list ( &var_log_audit__obj, fp_w );
            file_write_list ( &etc_pki__obj, fp_w );
            file_write_list ( &etc_selinux__obj, fp_w );
            file_write_list ( &sos_commands_selinux__obj, fp_w );
            /* kernel */
            append_list ( &sos_subtitle_kernel_obj, "==== kernel ====" );
            file_write_list ( &sos_subtitle_kernel_obj, fp_w );
            file_write_list ( &var_crash__obj, fp_w );
            file_write_list ( &sos_commands_abrt__obj, fp_w );
            /* dnf/yum */
            append_list ( &sos_subtitle_yum_obj, "==== dnf/yum ====" );
            file_write_list ( &sos_subtitle_yum_obj, fp_w );
            file_write_list ( &etc_dnf__obj, fp_w );
            file_write_list ( &sos_commands_dnf__obj, fp_w );
            file_write_list ( &etc_yum_repos_d__obj, fp_w );
            file_write_list ( &etc_yum__obj, fp_w );
            file_write_list ( &sos_commands_yum__obj, fp_w );
            /* login */
            append_list ( &sos_subtitle_login_obj, "==== login ====" );
            file_write_list ( &sos_subtitle_login_obj, fp_w );
            /* cron */
            append_list ( &sos_subtitle_cron_obj, "==== cron ====" );
            file_write_list ( &sos_subtitle_cron_obj, fp_w );
            file_write_list ( &etc_cron_d__obj, fp_w );
            file_write_list ( &etc_cron_hourly__obj, fp_w );
            file_write_list ( &etc_cron_daily__obj, fp_w );
            file_write_list ( &etc_cron_weekly__obj, fp_w );
            file_write_list ( &etc_cron_monthly__obj, fp_w );
            file_write_list ( &var_spool_cron__obj, fp_w );
            /* logrotate */
            append_list ( &sos_subtitle_logrotate_obj, "==== logrotate ====" );
            file_write_list ( &sos_subtitle_logrotate_obj, fp_w );
            file_write_list ( &etc_logrotate_d__obj, fp_w );
            /* logs and journals */
            append_list ( &sos_subtitle_logs_and_journals_obj, "==== logs_and_journals ====" );
            file_write_list ( &sos_subtitle_logs_and_journals_obj, fp_w );
            file_write_list ( &var_log_messages_obj, fp_w );
            file_write_list ( &sos_commands_logs_journalctl___no_pager_obj, fp_w );
            file_write_list ( &sos_commands_sar__obj, fp_w );
            /* httpd */
            append_list ( &sos_subtitle_httpd_obj, "==== httpd ====" );
            file_write_list ( &sos_subtitle_httpd_obj, fp_w );
            file_write_list ( &etc_httpd__obj, fp_w );
            file_write_list ( &sos_commands_apache__obj, fp_w );
            /* others ( default item is 'skip' ) */
            append_list ( &sos_subtitle_others_obj, "==== others ====" );
            file_write_list ( &sos_subtitle_others_obj, fp_w );
            file_write_list ( &lib__obj, fp_w );
            file_write_list ( &etc__obj, fp_w );
            file_write_list ( &sos_commands_obj, fp_w );
            file_write_list ( &dev__obj, fp_w );
            file_write_list ( &usr__obj, fp_w );
            file_write_list ( &var__obj, fp_w );
            file_write_list ( &proc__obj, fp_w );
        }
        /* real lines ( this comes all lines analyzed for both ) */
        file_write_list ( &sos_line_obj, fp_w );
        /* tail lines */
        file_write_list ( &sos_tail_obj, fp_w );
    
        /* close the file pointer */
        fclose ( fp_w );
    }
    snprintf ( dir_sa, MAX_FILE_NAME_LENGTH, "%s/var/log/sa", dir_name ); 
    
    if ( is_dir_present ( dir_sa ) == 1 && sar_only == 0 )
    {
        printf("Please check result file ./%s\n",sos_file_write);
        printf("%s does not exist. Program ends.\n",dir_sa);
        /* freeing sosreport-analyzer objects */
        free_sosreport_analyzer_obj ( );
        return EXIT_SUCCESS;
    }

    /* for sar-analyzer stuff */
    printf("analyzing sar files.\n");
    int SAR_OPTION = 'Z';
    int REPORT = 0;
    int MESSAGE_ONLY = 1;
    /*
     *  initialize sar_analyzer object, line object
     *  also, starts analyzing
     */
    const char *file_name = NULL;
    memset ( str_tmp, '\0', sizeof ( str_tmp ) ); 

    if ( sar_only == 1 )
        snprintf ( str_tmp, MAX_FILE_NAME_LENGTH, "%s", ( char * ) dir_name ); 
    else if ( sar_only == 0 )
        snprintf ( str_tmp, MAX_FILE_NAME_LENGTH, "%s/var/log/sa", ( char * ) get_dirname ( str_tmp3 ) ); 

    sar_analyzer_init ( str_tmp, file_name, SAR_OPTION, REPORT, MESSAGE_ONLY, time_span );

    char str_num [ MAX_FILE_NAME_LENGTH + 1 ] = { '\0' };
    char str_tmp_sar [ 10 ] = "dir_name:";
    strncpy ( str_num, str_tmp_sar, 10 );
    strncat ( str_num, get_dir_name_analyze ( ), MAX_DIR_NAME_LENGTH );
    append_list ( &report_obj, "--------" );
    append_list ( &report_obj, str_num );
    append_list ( &report_obj, "--------" );

    /* creating file name to be written from SAR_OPTION */
    file_to_write ( SAR_OPTION );

    const char *sar_file_write = ""; 
    char *file_ps_write = "";
    /* --------  for file write --------*/
    sar_file_write = get_sar_file_name_to_be_written ( );
    file_ps_write = ( char * ) get_ps_file_name_to_be_written ( );
    FILE *fp_sar_w;

    FILE *fp_ps_w [ MAX_ANALYZE_FILES ];
    FILE *fp_ps2_w [ MAX_ANALYZE_FILES ];
    FILE *fp_ps3_w [ MAX_ANALYZE_FILES ];
    FILE *fp_ps4_w [ MAX_ANALYZE_FILES ];

    /* open result file */
    if ( ( fp_sar_w = fopen ( sar_file_write, "a" ) ) == NULL )
    {
        printf("can't open file (%s): %s\n",sar_file_write,strerror(errno));
        exit ( EXIT_FAILURE );
    }

    print_and_file_write_analyzed_files ( &line_all_obj, "filename", NULL, fp_sar_w );

    /* writing report object to result file */
    file_write_list ( &line_all_obj, fp_sar_w );
    file_write_list ( &header_obj, fp_sar_w );
    file_write_list ( &report_cpu_obj, fp_sar_w );
    for ( v = 0; v <= get_core_numbers ( ); v++ )
    {
        file_write_list ( &report_cpu_spike_obj [ v ], fp_sar_w );
        file_write_list ( &report_cpu_time_span_spike_obj [ v ], fp_sar_w );
    }
    file_write_list ( &report_cpu_explanation_obj, fp_sar_w );
    file_write_list ( &report_tasks_obj, fp_sar_w );
    file_write_list ( &report_tasks_spike_obj, fp_sar_w );
    file_write_list ( &report_tasks_time_span_spike_obj, fp_sar_w );
    file_write_list ( &report_tasks_explanation_obj, fp_sar_w );
    file_write_list ( &report_pswap_obj, fp_sar_w );
    file_write_list ( &report_pswap_spike_obj, fp_sar_w );
    file_write_list ( &report_pswap_time_span_spike_obj, fp_sar_w );
    file_write_list ( &report_pswap_explanation_obj, fp_sar_w );
    file_write_list ( &report_paging_obj, fp_sar_w );
    file_write_list ( &report_paging_spike_obj, fp_sar_w );
    file_write_list ( &report_paging_time_span_spike_obj, fp_sar_w );
    file_write_list ( &report_paging_explanation_obj, fp_sar_w );
    file_write_list ( &report_io_transfer_rate_obj, fp_sar_w );
    file_write_list ( &report_io_transfer_rate_spike_obj, fp_sar_w );
    file_write_list ( &report_io_transfer_rate_time_span_spike_obj, fp_sar_w );
    file_write_list ( &report_io_transfer_rate_explanation_obj, fp_sar_w );
    file_write_list ( &report_memory_obj, fp_sar_w );
    file_write_list ( &report_memory_spike_obj, fp_sar_w );
    file_write_list ( &report_memory_time_span_spike_obj, fp_sar_w );
    file_write_list ( &report_memory_explanation_obj, fp_sar_w );
    file_write_list ( &report_swpused_obj, fp_sar_w );
    file_write_list ( &report_swpused_spike_obj, fp_sar_w );
    file_write_list ( &report_swpused_time_span_spike_obj, fp_sar_w );
    file_write_list ( &report_swpused_explanation_obj, fp_sar_w );
    file_write_list ( &report_kernel_table_obj, fp_sar_w );
    file_write_list ( &report_kernel_table_spike_obj, fp_sar_w );
    file_write_list ( &report_kernel_table_time_span_spike_obj, fp_sar_w );
    file_write_list ( &report_kernel_table_explanation_obj, fp_sar_w );
    file_write_list ( &report_ldavg_obj, fp_sar_w );
    file_write_list ( &report_ldavg_spike_obj, fp_sar_w );
    file_write_list ( &report_ldavg_time_span_spike_obj, fp_sar_w );
    file_write_list ( &report_ldavg_explanation_obj, fp_sar_w );
    file_write_list ( &report_block_device_obj, fp_sar_w );
    for ( v = 0; v <= get_block_device_numbers ( ); v++ )
    {
        file_write_list ( &report_block_device_spike_obj [ v ], fp_sar_w );
        file_write_list ( &report_block_device_time_span_spike_obj [ v ], fp_sar_w );
    }
    file_write_list ( &report_block_device_explanation_obj, fp_sar_w );
    file_write_list ( &report_network_obj, fp_sar_w );
    for ( v = 0; v <= get_network_device_numbers ( ); v++ )
    {
        file_write_list ( &report_network_spike_obj [ v ], fp_sar_w );
        file_write_list ( &report_network_time_span_spike_obj [ v ], fp_sar_w );
    }
    file_write_list ( &report_network_explanation_obj, fp_sar_w );
    file_write_list ( &report_network_error_obj, fp_sar_w );
    for ( v = 0; v <= get_network_device_numbers ( ); v++ )
    {
        file_write_list ( &report_network_error_spike_obj [ v ], fp_sar_w );
        file_write_list ( &report_network_error_time_span_spike_obj [ v ], fp_sar_w );
    }
    file_write_list ( &report_network_error_explanation_obj, fp_sar_w );
    file_write_list ( &report_thrashing_obj, fp_sar_w );
    for ( v = 0; v <= get_network_device_numbers ( ); v++ )
        file_write_list ( &report_network_down_obj [ v ], fp_sar_w );
    file_write_list ( &report_obj, fp_sar_w );

    /* writing "Linux" lines (top of sar file) to result file */
    print_and_file_write_analyzed_files ( &line_all_obj, "Linux", NULL, fp_sar_w );

    puts("------------------------");

    if ( sar_only == 1 )
    {
        printf("Please check sar result file ./%s\n",sar_file_write);
    }
    if ( sar_only == 0 )
    {
        printf("Please check result file ./%s\n",sos_file_write);
        printf("Also check sar result file ./%s\n\n",sar_file_write);
        printf("You can try reading all files which is set 'skip' by setting 'all' in conf file.\n");
        printf("Note that when you done that, it'll take many minutes to be finished depending on cpu power.\n\n");
    }

    if ( sar_only == 0 )
    {
        /* freeing sosreport-analyzer objects */
        free_sosreport_analyzer_obj ( );
    }

    /* close the file pointer */
    fclose ( fp_sar_w );

    for ( v = 0, x = 1; v < MAX_ANALYZE_FILES; v++, x++ )
    {
        char str_tmp [ MAX_LINE_LENGTH ] = { '\0' };
        memset ( str_tmp, '\0', sizeof ( str_tmp ) );
        snprintf ( str_tmp, MAX_LINE_LENGTH, "%s%s%d%s", file_ps_write, "-cpu-", x, ".ps" );
        if ( ( fp_ps_w [ v ] = fopen ( str_tmp,"a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n",str_tmp,strerror(errno));
            exit ( EXIT_FAILURE );
        }
        snprintf ( str_tmp, MAX_LINE_LENGTH, "%s%s%d%s", file_ps_write, "-mem-", x, ".ps" );
        if ( ( fp_ps2_w [ v ] = fopen ( str_tmp,"a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n",str_tmp,strerror(errno));
            exit ( EXIT_FAILURE );
        }
        snprintf ( str_tmp, MAX_LINE_LENGTH, "%s%s%d%s", file_ps_write, "-ldv-", x, ".ps" );
        if ( ( fp_ps3_w [ v ] = fopen ( str_tmp,"a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n",str_tmp,strerror(errno));
            exit ( EXIT_FAILURE );
        }
        snprintf ( str_tmp, MAX_LINE_LENGTH, "%s%s%d%s", file_ps_write, "-ior-", x, ".ps" );
        if ( ( fp_ps4_w [ v ] = fopen ( str_tmp,"a" ) ) == NULL )
        {
            printf("can't open file (%s): %s\n",str_tmp,strerror(errno));
            exit ( EXIT_FAILURE );
        }
    }
    /* appending needed lines to ps obj -- this is needed we don't know the last line of each graph when drawing */
    for ( v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for file cpu */
        append_list ( &ps_cpu_usr_obj [ v ], "stroke");
        append_list ( &ps_cpu_sys_obj [ v ] , "stroke");
        append_list ( &ps_cpu_iowait_obj [ v ], "stroke");
        append_list ( &ps_cpu_idle_obj [ v ], "stroke");
        append_list ( &ps_paging_pgpgin_obj [ v ], "stroke");
        append_list ( &ps_paging_pgpgout_obj [ v ], "stroke");
        append_list ( &ps_paging_fault_obj [ v ], "stroke");
        append_list ( &ps_paging_mjflt_obj [ v ], "stroke");
        append_list ( &ps_paging_vmeff_obj [ v ], "stroke");
        /* for file mem */
        append_list ( &ps_memory_memused_obj [ v ], "stroke");
        append_list ( &ps_memory_kbcommit_obj [ v ], "stroke");
        append_list ( &ps_memory_commit_obj [ v ], "stroke");
        append_list ( &ps_swapping_pswpin_obj [ v ], "stroke");
        append_list ( &ps_swapping_pswpout_obj [ v ], "stroke");
        /* for file ldv */
        append_list ( &ps_ldavg_runq_obj [ v ], "stroke");
        append_list ( &ps_ldavg_plist_obj [ v ], "stroke");
        append_list ( &ps_ldavg_ldavg_one_obj [ v ], "stroke");
        append_list ( &ps_ldavg_ldavg_five_obj [ v ], "stroke");
        append_list ( &ps_ldavg_ldavg_15_obj [ v ], "stroke");
        append_list ( &ps_tasks_proc_obj [ v ], "stroke");
        append_list ( &ps_tasks_cswch_obj [ v ], "stroke");
        /* for file ior */
        append_list ( &ps_io_transfer_rate_tps_obj [ v ], "stroke");
        append_list ( &ps_io_transfer_rate_bread_obj [ v ], "stroke");
        append_list ( &ps_io_transfer_rate_bwrtn_obj [ v ], "stroke");
        append_list ( &ps_kernel_table_dentunusd_obj [ v ], "stroke");
        append_list ( &ps_kernel_table_file_obj [ v ], "stroke");
        append_list ( &ps_kernel_table_inode_obj [ v ], "stroke");
        /* for linux restart string */
        append_list ( &ps_restart_obj [ v ], "stroke");
        append_list ( &ps_restart_obj [ v ], "%");
    }
    /* appending needed lines to ps obj -- adding % to the very last of each ps file */
    for ( v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for file cpu */
        append_list ( &ps_paging_vmeff_obj [ v ], "%");
        /* for file mem */
        append_list ( &ps_swapping_pswpout_obj [ v ], "%");
        /* for file ldv */
        append_list ( &ps_ldavg_ldavg_15_obj [ v ], "%");
        /* for file ior */
        append_list ( &ps_kernel_table_inode_obj [ v ], "%");
    }
    /* appending needed lines to ps obj -- adding % to the very last of each box */
    for ( v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for file cpu */
        append_list ( &ps_cpu_label_obj [ v ], "stroke");
        append_list ( &ps_cpu_label_obj [ v ], "%");
        append_list ( &ps_paging_label_obj [ v ], "stroke");
        append_list ( &ps_paging_label_obj [ v ], "%");
        /* for file mem */
        append_list ( &ps_memory_label_obj [ v ], "stroke");
        append_list ( &ps_memory_label_obj [ v ], "%");
        append_list ( &ps_swapping_label_obj [ v ], "stroke");
        append_list ( &ps_swapping_label_obj [ v ], "%");
        /* for file ldv */
        append_list ( &ps_ldavg_label_obj [ v ], "stroke");
        append_list ( &ps_ldavg_label_obj [ v ], "%");
        append_list ( &ps_tasks_label_obj [ v ], "stroke");
        append_list ( &ps_tasks_label_obj [ v ], "%");
        /* for file ior */
        append_list ( &ps_io_transfer_rate_label_obj [ v ], "stroke");
        append_list ( &ps_io_transfer_rate_label_obj [ v ], "%");
        append_list ( &ps_kernel_table_label_obj [ v ], "stroke");
        append_list ( &ps_kernel_table_label_obj [ v ], "%");
    }
    /* now we write obj to postscript (.ps) file */
    for ( v = 0; v < MAX_ANALYZE_FILES; v++ )
    {
        /* for file cpu */
        file_write_list ( &ps_common_cpu_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_label_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_usr_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_sys_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_iowait_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_cpu_idle_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_label_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_pgpgin_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_pgpgout_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_fault_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_mjflt_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_paging_vmeff_obj [ v ], fp_ps_w [ v ] );
        /* for file mem */
        file_write_list ( &ps_common_memory_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_memory_label_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_memory_memused_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_memory_kbcommit_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_memory_commit_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_swapping_label_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_swapping_pswpin_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_swapping_pswpout_obj [ v ], fp_ps2_w [ v ] );
        /* for file ldv */
        file_write_list ( &ps_common_ldavg_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_label_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_runq_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_plist_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_ldavg_one_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_ldavg_five_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_ldavg_ldavg_15_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_tasks_label_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_tasks_proc_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_tasks_cswch_obj [ v ], fp_ps3_w [ v ] );
        /* for file ior */
        file_write_list ( &ps_common_io_transfer_rate_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_io_transfer_rate_label_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_io_transfer_rate_tps_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_io_transfer_rate_bread_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_io_transfer_rate_bwrtn_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_kernel_table_label_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_kernel_table_dentunusd_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_kernel_table_file_obj [ v ], fp_ps4_w [ v ] );
        file_write_list ( &ps_kernel_table_inode_obj [ v ], fp_ps4_w [ v ] );
        /* for linux restart string */
        file_write_list ( &ps_restart_obj [ v ], fp_ps_w [ v ] );
        file_write_list ( &ps_restart_obj [ v ], fp_ps2_w [ v ] );
        file_write_list ( &ps_restart_obj [ v ], fp_ps3_w [ v ] );
        file_write_list ( &ps_restart_obj [ v ], fp_ps4_w [ v ] );
    }
    char str_tmp_echo [ MAX_LINE_LENGTH ] = { '\0' };
    memset ( str_tmp_echo, '\0', sizeof ( str_tmp_echo) );
    snprintf ( str_tmp_echo, MAX_LINE_LENGTH, "%s%s", file_ps_write, "-<item>-<no>.ps" );
    printf("Please check graphs in the ps file: %s\n\n",str_tmp_echo);
    /* close the file pointers */
    for ( v = 0; v < MAX_ANALYZE_FILES; v++ )
    { 
        fclose ( fp_ps_w [ v ] );
        fclose ( fp_ps2_w [ v ] );
        fclose ( fp_ps3_w [ v ] );
        fclose ( fp_ps4_w [ v ] );
    }

    cfg_clear (); 

    /* freeing sar-analyzer objects */
    free_sar_analyzer_obj ( );

    return EXIT_SUCCESS;
}
