// commit message qemu@fef6070eff (target=0, prob=0.22592632, correct=True): block: vpc - use block layer ops in vpc_create, instead of posix calls
/*0  */ static int create_fixed_disk(int fd, uint8_t *buf, int64_t total_size)  // (0) 0.1227
/*2  */ {                                                                       // (17) 0.004545
/*4  */     int ret = -EIO;                                                     // (6) 0.04545
/*8  */     /* Add footer to total size */                                      // (5) 0.05
/*10 */     total_size += 512;                                                  // (10) 0.04091
/*12 */     if (ftruncate(fd, total_size) != 0) {                               // (3) 0.09091
/*14 */         ret = -errno;                                                   // (4) 0.05909
/*16 */         goto fail;                                                      // (7) 0.04545
/*18 */     }                                                                   // (13) 0.01818
/*20 */     if (lseek(fd, -512, SEEK_END) < 0) {                                // (2) 0.1
/*22 */         goto fail;                                                      // (8) 0.04545
/*24 */     }                                                                   // (14) 0.01818
/*26 */     if (write(fd, buf, HEADER_SIZE) != HEADER_SIZE) {                   // (1) 0.1045
/*28 */         goto fail;                                                      // (9) 0.04545
/*30 */     }                                                                   // (15) 0.01818
/*34 */     ret = 0;                                                            // (11) 0.03182
/*38 */  fail:                                                                  // (16) 0.009091
/*40 */     return ret;                                                         // (12) 0.02727
/*42 */ }                                                                       // (18) 0.004545
