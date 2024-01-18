// commit message qemu@c9add62195 (target=1, prob=0.5896992, correct=True): trace: Try using tracefs first
/*0  */ bool ftrace_init(void)                                                     // (24) 0.01563
/*2  */ {                                                                          // (26) 0.001953
/*4  */     char mount_point[PATH_MAX];                                            // (16) 0.02344
/*6  */     char path[PATH_MAX];                                                   // (21) 0.01953
/*8  */     int debugfs_found;                                                     // (23) 0.01758
/*10 */     int trace_fd = -1;                                                     // (20) 0.02148
/*14 */     debugfs_found = find_mount(mount_point, "debugfs");                    // (10) 0.03906
/*16 */     if (debugfs_found) {                                                   // (19) 0.02148
/*18 */         snprintf(path, PATH_MAX, "%s/tracing/tracing_on", mount_point);    // (1) 0.06055
/*20 */         trace_fd = open(path, O_WRONLY);                                   // (7) 0.04102
/*22 */         if (trace_fd < 0) {                                                // (13) 0.03125
/*24 */             if (errno == EACCES) {                                         // (8) 0.04102
/*26 */                 trace_marker_fd = open("/dev/null", O_WRONLY);             // (0) 0.06836
/*28 */                 if (trace_marker_fd != -1) {                               // (4) 0.05469
/*30 */                     return true;                                           // (6) 0.04297
/*32 */                 }                                                          // (14) 0.03125
/*34 */             }                                                              // (17) 0.02344
/*36 */             perror("Could not open ftrace 'tracing_on' file");             // (5) 0.05273
/*38 */             return false;                                                  // (15) 0.02734
/*40 */         } else {                                                           // (22) 0.01953
/*42 */             if (write(trace_fd, "1", 1) < 0) {                             // (3) 0.05469
/*44 */                 perror("Could not write to 'tracing_on' file");            // (2) 0.05859
/*46 */                 close(trace_fd);                                           // (9) 0.04102
/*48 */                 return false;                                              // (11) 0.03516
/*50 */             }                                                              // (18) 0.02344
/*52 */             close(trace_fd);                                               // (12) 0.0332
/*54 */         }                                                                  // (25) 0.01562
/*56 */         snprintf(path, PATH_MAX, "%s/tracing/trace_marker", mount_point);  // 0.0
/*58 */         trace_marker_fd = open(path, O_WRONLY);                            // 0.0
/*60 */         if (trace_marker_fd < 0) {                                         // 0.0
/*62 */             perror("Could not open ftrace 'trace_marker' file");           // 0.0
/*64 */             return false;                                                  // 0.0
/*66 */         }                                                                  // 0.0
/*68 */     } else {                                                               // 0.0
/*70 */         fprintf(stderr, "debugfs is not mounted\n");                       // 0.0
/*72 */         return false;                                                      // 0.0
/*74 */     }                                                                      // 0.0
/*78 */     return true;                                                           // 0.0
/*80 */ }                                                                          // 0.0
