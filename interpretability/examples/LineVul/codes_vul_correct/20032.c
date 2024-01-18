// commit message qemu@3e80bf9351 (target=1, prob=0.6621518, correct=True): rename qemu_sendv to iov_send, change proto and move declarations to iov.h
/*0   */ static int do_sendv_recvv(int sockfd, struct iovec *iov, int len, int offset,  // (2) 0.05273
/*2   */                           int do_sendv)                                        // (0) 0.06055
/*4   */ {                                                                              // (32) 0.001953
/*6   */     int ret, diff, iovlen;                                                     // (18) 0.02344
/*8   */     struct iovec *last_iov;                                                    // (19) 0.02344
/*12  */     /* last_iov is inclusive, so count from one.  */                           // (7) 0.0332
/*14  */     iovlen = 1;                                                                // (26) 0.01758
/*16  */     last_iov = iov;                                                            // (24) 0.01953
/*18  */     len += offset;                                                             // (28) 0.01367
/*22  */     while (last_iov->iov_len < len) {                                          // (9) 0.03125
/*24  */         len -= last_iov->iov_len;                                              // (8) 0.0332
/*28  */         last_iov++;                                                            // (22) 0.02148
/*30  */         iovlen++;                                                              // (23) 0.02148
/*32  */     }                                                                          // (29) 0.007812
/*36  */     diff = last_iov->iov_len - len;                                            // (12) 0.0293
/*38  */     last_iov->iov_len -= diff;                                                 // (16) 0.02539
/*42  */     while (iov->iov_len <= offset) {                                           // (13) 0.02734
/*44  */         offset -= iov->iov_len;                                                // (10) 0.03125
/*48  */         iov++;                                                                 // (25) 0.01953
/*50  */         iovlen--;                                                              // (20) 0.02344
/*52  */     }                                                                          // (30) 0.007812
/*56  */     iov->iov_base = (char *) iov->iov_base + offset;                           // (3) 0.04297
/*58  */     iov->iov_len -= offset;                                                    // (21) 0.02344
/*62  */     {                                                                          // (31) 0.007812
/*64  */ #if defined CONFIG_IOVEC && defined CONFIG_POSIX                               // (14) 0.02734
/*66  */         struct msghdr msg;                                                     // (17) 0.02539
/*68  */         memset(&msg, 0, sizeof(msg));                                          // (5) 0.03516
/*70  */         msg.msg_iov = iov;                                                     // (11) 0.03125
/*72  */         msg.msg_iovlen = iovlen;                                               // (6) 0.03516
/*76  */         do {                                                                   // (27) 0.01758
/*78  */             if (do_sendv) {                                                    // (4) 0.03711
/*80  */                 ret = sendmsg(sockfd, &msg, 0);                                // (1) 0.05664
/*82  */             } else {                                                           // (15) 0.02734
/*84  */                 ret = recvmsg(sockfd, &msg, 0);                                // 0.0
/*86  */             }                                                                  // 0.0
/*88  */         } while (ret == -1 && errno == EINTR);                                 // 0.0
/*90  */ #else                                                                          // 0.0
/*92  */         struct iovec *p = iov;                                                 // 0.0
/*94  */         ret = 0;                                                               // 0.0
/*96  */         while (iovlen > 0) {                                                   // 0.0
/*98  */             int rc;                                                            // 0.0
/*100 */             if (do_sendv) {                                                    // 0.0
/*102 */                 rc = send(sockfd, p->iov_base, p->iov_len, 0);                 // 0.0
/*104 */             } else {                                                           // 0.0
/*106 */                 rc = qemu_recv(sockfd, p->iov_base, p->iov_len, 0);            // 0.0
/*108 */             }                                                                  // 0.0
/*110 */             if (rc == -1) {                                                    // 0.0
/*112 */                 if (errno == EINTR) {                                          // 0.0
/*114 */                     continue;                                                  // 0.0
/*116 */                 }                                                              // 0.0
/*118 */                 if (ret == 0) {                                                // 0.0
/*120 */                     ret = -1;                                                  // 0.0
/*122 */                 }                                                              // 0.0
/*124 */                 break;                                                         // 0.0
/*126 */             }                                                                  // 0.0
/*128 */             if (rc == 0) {                                                     // 0.0
/*130 */                 break;                                                         // 0.0
/*132 */             }                                                                  // 0.0
/*134 */             ret += rc;                                                         // 0.0
/*136 */             iovlen--, p++;                                                     // 0.0
/*138 */         }                                                                      // 0.0
/*140 */ #endif                                                                         // 0.0
/*142 */     }                                                                          // 0.0
/*146 */     /* Undo the changes above */                                               // 0.0
/*148 */     iov->iov_base = (char *) iov->iov_base - offset;                           // 0.0
/*150 */     iov->iov_len += offset;                                                    // 0.0
/*152 */     last_iov->iov_len += diff;                                                 // 0.0
/*154 */     return ret;                                                                // 0.0
/*156 */ }                                                                              // 0.0
