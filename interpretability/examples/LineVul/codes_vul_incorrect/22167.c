// commit message qemu@6958349085 (target=1, prob=0.46777555, correct=False): file-posix: clean up max_segments buffer termination
/*0  */ static int hdev_get_max_segments(const struct stat *st)                     // (7) 0.03523
/*2  */ {                                                                           // (37) 0.001957
/*4  */ #ifdef CONFIG_LINUX                                                         // (27) 0.0137
/*6  */     char buf[32];                                                           // (25) 0.01566
/*8  */     const char *end;                                                        // (26) 0.01566
/*10 */     char *sysfspath;                                                        // (16) 0.01957
/*12 */     int ret;                                                                // (28) 0.01174
/*14 */     int fd = -1;                                                            // (17) 0.01957
/*16 */     long max_segments;                                                      // (23) 0.01761
/*20 */     sysfspath = g_strdup_printf("/sys/dev/block/%u:%u/queue/max_segments",  // (1) 0.07045
/*22 */                                 major(st->st_rdev), minor(st->st_rdev));    // (0) 0.09589
/*24 */     fd = open(sysfspath, O_RDONLY);                                         // (4) 0.03718
/*26 */     if (fd == -1) {                                                         // (15) 0.02153
/*28 */         ret = -errno;                                                       // (10) 0.02544
/*30 */         goto out;                                                           // (18) 0.01957
/*32 */     }                                                                       // (31) 0.007828
/*34 */     do {                                                                    // (30) 0.009785
/*36 */         ret = read(fd, buf, sizeof(buf));                                   // (5) 0.03718
/*38 */     } while (ret == -1 && errno == EINTR);                                  // (8) 0.03523
/*40 */     if (ret < 0) {                                                          // (19) 0.01957
/*42 */         ret = -errno;                                                       // (11) 0.02544
/*44 */         goto out;                                                           // (20) 0.01957
/*46 */     } else if (ret == 0) {                                                  // (13) 0.02348
/*48 */         ret = -EIO;                                                         // (12) 0.02544
/*50 */         goto out;                                                           // (21) 0.01957
/*52 */     }                                                                       // (32) 0.007828
/*54 */     buf[ret] = 0;                                                           // (22) 0.01957
/*56 */     /* The file is ended with '\n', pass 'end' to accept that. */           // (3) 0.04305
/*58 */     ret = qemu_strtol(buf, &end, 10, &max_segments);                        // (2) 0.05088
/*60 */     if (ret == 0 && end && *end == '\n') {                                  // (6) 0.03718
/*62 */         ret = max_segments;                                                 // (9) 0.0274
/*64 */     }                                                                       // (33) 0.007828
/*68 */ out:                                                                        // (34) 0.003914
/*70 */     g_free(sysfspath);                                                      // (14) 0.02348
/*72 */     return ret;                                                             // (29) 0.01174
/*74 */ #else                                                                       // (35) 0.003914
/*76 */     return -ENOTSUP;                                                        // (24) 0.01761
/*78 */ #endif                                                                      // (36) 0.003914
/*80 */ }                                                                           // (38) 0.001957
