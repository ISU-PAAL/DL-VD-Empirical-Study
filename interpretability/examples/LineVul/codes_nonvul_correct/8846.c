// commit message qemu@494a8ebe71 (target=0, prob=0.13671124, correct=True): 9pfs: rename virtio-9p-proxy.{c,h} to 9p-proxy.{c,h}
/*0  */ static ssize_t socket_read(int sockfd, void *buff, size_t size)  // (0) 0.08302
/*2  */ {                                                                // (18) 0.003774
/*4  */     ssize_t retval, total = 0;                                   // (8) 0.05283
/*8  */     while (size) {                                               // (13) 0.03019
/*10 */         retval = read(sockfd, buff, size);                       // (2) 0.07547
/*12 */         if (retval == 0) {                                       // (6) 0.0566
/*14 */             return -EIO;                                         // (4) 0.06038
/*16 */         }                                                        // (14) 0.03019
/*18 */         if (retval < 0) {                                        // (7) 0.0566
/*20 */             if (errno == EINTR) {                                // (1) 0.07925
/*22 */                 continue;                                        // (3) 0.06415
/*24 */             }                                                    // (9) 0.04528
/*26 */             return -errno;                                       // (5) 0.06038
/*28 */         }                                                        // (15) 0.03019
/*30 */         size -= retval;                                          // (10) 0.04528
/*32 */         buff += retval;                                          // (11) 0.04528
/*34 */         total += retval;                                         // (12) 0.04528
/*36 */     }                                                            // (17) 0.01509
/*38 */     return total;                                                // (16) 0.02264
/*40 */ }                                                                // (19) 0.003774
