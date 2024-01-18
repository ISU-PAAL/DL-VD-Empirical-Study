// commit message qemu@b224e5e216 (target=1, prob=0.5626197, correct=True): qapi: convert add_client
/*0  */ static int add_graphics_client(Monitor *mon, const QDict *qdict, QObject **ret_data)  // (5) 0.05469
/*2  */ {                                                                                     // (25) 0.001953
/*4  */     const char *protocol  = qdict_get_str(qdict, "protocol");                         // (8) 0.04688
/*6  */     const char *fdname = qdict_get_str(qdict, "fdname");                              // (10) 0.04492
/*8  */     CharDriverState *s;                                                               // (19) 0.01758
/*12 */     if (strcmp(protocol, "spice") == 0) {                                             // (12) 0.03711
/*14 */         int fd = monitor_get_fd(mon, fdname, NULL);                                   // (6) 0.04883
/*16 */         int skipauth = qdict_get_try_bool(qdict, "skipauth", 0);                      // (2) 0.05664
/*18 */         int tls = qdict_get_try_bool(qdict, "tls", 0);                                // (3) 0.05664
/*20 */         if (!using_spice) {                                                           // (15) 0.0293
/*22 */             /* correct one? spice isn't a device ,,, */                               // (9) 0.04492
/*24 */             qerror_report(QERR_DEVICE_NOT_ACTIVE, "spice");                           // (1) 0.0625
/*26 */             return -1;                                                                // (16) 0.0293
/*28 */         }                                                                             // (20) 0.01562
/*30 */         if (qemu_spice_display_add_client(fd, skipauth, tls) < 0) {                   // (0) 0.06641
/*32 */             close(fd);                                                                // (17) 0.0293
/*34 */         }                                                                             // (21) 0.01562
/*36 */         return 0;                                                                     // (18) 0.01953
/*38 */ #ifdef CONFIG_VNC                                                                     // (22) 0.01367
/*40 */     } else if (strcmp(protocol, "vnc") == 0) {                                        // (11) 0.04102
/*42 */ 	int fd = monitor_get_fd(mon, fdname, NULL);                                          // (13) 0.03711
/*44 */         int skipauth = qdict_get_try_bool(qdict, "skipauth", 0);                      // (4) 0.05664
/*46 */ 	vnc_display_add_client(NULL, fd, skipauth);                                          // (14) 0.03516
/*48 */ 	return 0;                                                                            // (23) 0.007812
/*50 */ #endif                                                                                // (24) 0.003906
/*52 */     } else if ((s = qemu_chr_find(protocol)) != NULL) {                               // (7) 0.04883
/*54 */ 	int fd = monitor_get_fd(mon, fdname, NULL);                                          // 0.0
/*56 */ 	if (qemu_chr_add_client(s, fd) < 0) {                                                // 0.0
/*58 */ 	    qerror_report(QERR_ADD_CLIENT_FAILED);                                           // 0.0
/*60 */ 	    return -1;                                                                       // 0.0
/*62 */ 	}                                                                                    // 0.0
/*64 */ 	return 0;                                                                            // 0.0
/*66 */     }                                                                                 // 0.0
/*70 */     qerror_report(QERR_INVALID_PARAMETER, "protocol");                                // 0.0
/*72 */     return -1;                                                                        // 0.0
/*74 */ }                                                                                     // 0.0
