// commit message qemu@494a8ebe71 (target=0, prob=0.447347, correct=True): 9pfs: rename virtio-9p-proxy.{c,h} to 9p-proxy.{c,h}
/*0  */ static int v9fs_receivefd(int sockfd, int *status)                            // (6) 0.03516
/*2  */ {                                                                             // (34) 0.001953
/*4  */     struct iovec iov;                                                         // (24) 0.01953
/*6  */     struct msghdr msg;                                                        // (26) 0.01758
/*8  */     struct cmsghdr *cmsg;                                                     // (17) 0.02344
/*10 */     int retval, data, fd;                                                     // (16) 0.02344
/*12 */     union MsgControl msg_control;                                             // (21) 0.02148
/*16 */     iov.iov_base = &data;                                                     // (15) 0.02539
/*18 */     iov.iov_len = sizeof(data);                                               // (12) 0.02734
/*22 */     memset(&msg, 0, sizeof(msg));                                             // (11) 0.02734
/*24 */     msg.msg_iov = &iov;                                                       // (19) 0.02344
/*26 */     msg.msg_iovlen = 1;                                                       // (18) 0.02344
/*28 */     msg.msg_control = &msg_control;                                           // (13) 0.02734
/*30 */     msg.msg_controllen = sizeof(msg_control);                                 // (9) 0.0332
/*34 */     do {                                                                      // (28) 0.009766
/*36 */         retval = recvmsg(sockfd, &msg, 0);                                    // (2) 0.04492
/*38 */     } while (retval < 0 && errno == EINTR);                                   // (7) 0.03516
/*40 */     if (retval <= 0) {                                                        // (23) 0.02148
/*42 */         return retval;                                                        // (22) 0.02148
/*44 */     }                                                                         // (32) 0.007812
/*46 */     /*                                                                        // (31) 0.007813
/*48 */      * data is set to V9FS_FD_VALID, if ancillary data is sent.  If this      // (1) 0.05664
/*50 */      * request doesn't need ancillary data (fd) or an error occurred,         // (4) 0.04102
/*52 */      * data is set to negative errno value.                                   // (14) 0.02734
/*54 */      */                                                                       // (29) 0.009766
/*56 */     if (data != V9FS_FD_VALID) {                                              // (8) 0.0332
/*58 */         *status = data;                                                       // (20) 0.02344
/*60 */         return 0;                                                             // (25) 0.01953
/*62 */     }                                                                         // (33) 0.007812
/*64 */     /*                                                                        // (30) 0.007813
/*66 */      * File descriptor (fd) is sent in the ancillary data. Check if we        // (3) 0.04297
/*68 */      * indeed received it. One of the reasons to fail to receive it is if     // (5) 0.03906
/*70 */      * we exceeded the maximum number of file descriptors!                    // (10) 0.0293
/*72 */      */                                                                       // (27) 0.009766
/*74 */     for (cmsg = CMSG_FIRSTHDR(&msg); cmsg; cmsg = CMSG_NXTHDR(&msg, cmsg)) {  // (0) 0.07422
/*76 */         if (cmsg->cmsg_len != CMSG_LEN(sizeof(int)) ||                        // 0.0
/*78 */             cmsg->cmsg_level != SOL_SOCKET ||                                 // 0.0
/*80 */             cmsg->cmsg_type != SCM_RIGHTS) {                                  // 0.0
/*82 */             continue;                                                         // 0.0
/*84 */         }                                                                     // 0.0
/*86 */         fd = *((int *)CMSG_DATA(cmsg));                                       // 0.0
/*88 */         *status = fd;                                                         // 0.0
/*90 */         return 0;                                                             // 0.0
/*92 */     }                                                                         // 0.0
/*94 */     *status = -ENFILE;  /* Ancillary data sent but not received */            // 0.0
/*96 */     return 0;                                                                 // 0.0
/*98 */ }                                                                             // 0.0
