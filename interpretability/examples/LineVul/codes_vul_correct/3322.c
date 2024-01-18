// commit message qemu@25e5e4c7e9 (target=1, prob=0.5898872, correct=True): rewrite iov_send_recv() and move it to iov.c
/*0  */ qemu_co_sendv_recvv(int sockfd, struct iovec *iov, unsigned iov_cnt,  // (2) 0.05859
/*2  */                     size_t offset, size_t bytes, bool do_send)        // (1) 0.06641
/*4  */ {                                                                     // (26) 0.001953
/*6  */     size_t done = 0;                                                  // (21) 0.01953
/*8  */     ssize_t ret;                                                      // (22) 0.01758
/*10 */     while (done < bytes) {                                            // (20) 0.01953
/*12 */         ret = iov_send_recv(sockfd, iov,                              // (5) 0.04688
/*14 */                             offset + done, bytes - done, do_send);    // (0) 0.07617
/*16 */         if (ret > 0) {                                                // (16) 0.02734
/*18 */             done += ret;                                              // (15) 0.0293
/*20 */         } else if (ret < 0) {                                         // (14) 0.03125
/*22 */             if (errno == EAGAIN) {                                    // (9) 0.04102
/*24 */                 qemu_coroutine_yield();                               // (4) 0.04883
/*26 */             } else if (done == 0) {                                   // (11) 0.03906
/*28 */                 return -1;                                            // (12) 0.03711
/*30 */             } else {                                                  // (17) 0.02734
/*32 */                 break;                                                // (13) 0.0332
/*34 */             }                                                         // (19) 0.02344
/*36 */         } else if (ret == 0 && !do_send) {                            // (10) 0.04102
/*38 */             /* write (send) should never return 0.                    // (8) 0.04102
/*40 */              * read (recv) returns 0 for end-of-file (-data).         // (3) 0.05664
/*42 */              * In both cases there's little point retrying,           // (7) 0.04492
/*44 */              * but we do for write anyway, just in case */            // (6) 0.04688
/*46 */             break;                                                    // (18) 0.02539
/*48 */         }                                                             // (23) 0.01562
/*50 */     }                                                                 // (25) 0.007812
/*52 */     return done;                                                      // (24) 0.01172
/*54 */ }                                                                     // (27) 0.001953
