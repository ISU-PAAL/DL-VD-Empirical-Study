// commit message qemu@0752706de2 (target=1, prob=0.607484, correct=True): Don't exit() in config_error()
/*0   */ static void slirp_smb(SlirpState* s, Monitor *mon, const char *exported_dir,  // (4) 0.05469
/*2   */                       struct in_addr vserver_addr)                            // (3) 0.05859
/*4   */ {                                                                             // (25) 0.001953
/*6   */     static int instance;                                                      // (21) 0.01367
/*8   */     char smb_conf[128];                                                       // (16) 0.02148
/*10  */     char smb_cmdline[128];                                                    // (15) 0.02344
/*12  */     FILE *f;                                                                  // (22) 0.01367
/*16  */     snprintf(s->smb_dir, sizeof(s->smb_dir), "/tmp/qemu-smb.%ld-%d",          // (0) 0.07422
/*18  */              (long)getpid(), instance++);                                     // (8) 0.04102
/*20  */     if (mkdir(s->smb_dir, 0700) < 0) {                                        // (7) 0.04297
/*22  */         config_error(mon, "could not create samba server dir '%s'\n",         // (5) 0.05469
/*24  */                      s->smb_dir);                                             // (6) 0.05273
/*26  */         return;                                                               // (17) 0.01758
/*28  */     }                                                                         // (23) 0.007812
/*30  */     snprintf(smb_conf, sizeof(smb_conf), "%s/%s", s->smb_dir, "smb.conf");    // (1) 0.07227
/*34  */     f = fopen(smb_conf, "w");                                                 // (14) 0.03125
/*36  */     if (!f) {                                                                 // (19) 0.01562
/*38  */         slirp_smb_cleanup(s);                                                 // (12) 0.03711
/*40  */         config_error(mon, "could not create samba server "                    // (9) 0.04102
/*42  */                      "configuration file '%s'\n", smb_conf);                  // (2) 0.07031
/*44  */         return;                                                               // (18) 0.01758
/*46  */     }                                                                         // (24) 0.007812
/*48  */     fprintf(f,                                                                // (20) 0.01562
/*50  */             "[global]\n"                                                      // (13) 0.0332
/*52  */             "private dir=%s\n"                                                // (10) 0.03906
/*54  */             "smb ports=0\n"                                                   // (11) 0.03906
/*56  */             "socket address=127.0.0.1\n"                                      // 0.0
/*58  */             "pid directory=%s\n"                                              // 0.0
/*60  */             "lock directory=%s\n"                                             // 0.0
/*62  */             "log file=%s/log.smbd\n"                                          // 0.0
/*64  */             "smb passwd file=%s/smbpasswd\n"                                  // 0.0
/*66  */             "security = share\n"                                              // 0.0
/*68  */             "[qemu]\n"                                                        // 0.0
/*70  */             "path=%s\n"                                                       // 0.0
/*72  */             "read only=no\n"                                                  // 0.0
/*74  */             "guest ok=yes\n",                                                 // 0.0
/*76  */             s->smb_dir,                                                       // 0.0
/*78  */             s->smb_dir,                                                       // 0.0
/*80  */             s->smb_dir,                                                       // 0.0
/*82  */             s->smb_dir,                                                       // 0.0
/*84  */             s->smb_dir,                                                       // 0.0
/*86  */             exported_dir                                                      // 0.0
/*88  */             );                                                                // 0.0
/*90  */     fclose(f);                                                                // 0.0
/*94  */     snprintf(smb_cmdline, sizeof(smb_cmdline), "%s -s %s",                    // 0.0
/*96  */              SMBD_COMMAND, smb_conf);                                         // 0.0
/*100 */     if (slirp_add_exec(s->slirp, 0, smb_cmdline, &vserver_addr, 139) < 0) {   // 0.0
/*102 */         slirp_smb_cleanup(s);                                                 // 0.0
/*104 */         config_error(mon, "conflicting/invalid smbserver address\n");         // 0.0
/*106 */     }                                                                         // 0.0
/*108 */ }                                                                             // 0.0
