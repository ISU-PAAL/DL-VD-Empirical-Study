// commit message qemu@30b8b68eb5 (target=0, prob=0.54627293, correct=False): linux-user: support target-to-host SCM_CREDENTIALS
/*0   */ static inline abi_long target_to_host_cmsg(struct msghdr *msgh,                                  // (7) 0.04492
/*2   */                                            struct target_msghdr *target_msgh)                    // (0) 0.1055
/*4   */ {                                                                                                // (23) 0.001953
/*6   */     struct cmsghdr *cmsg = CMSG_FIRSTHDR(msgh);                                                  // (8) 0.04492
/*8   */     abi_long msg_controllen;                                                                     // (18) 0.02539
/*10  */     abi_ulong target_cmsg_addr;                                                                  // (15) 0.0293
/*12  */     struct target_cmsghdr *target_cmsg;                                                          // (14) 0.0293
/*14  */     socklen_t space = 0;                                                                         // (20) 0.02148
/*16  */                                                                                                  // (22) 0.007812
/*18  */     msg_controllen = tswapal(target_msgh->msg_controllen);                                       // (4) 0.04883
/*20  */     if (msg_controllen < sizeof (struct target_cmsghdr))                                         // (9) 0.04102
/*22  */         goto the_end;                                                                            // (19) 0.02344
/*24  */     target_cmsg_addr = tswapal(target_msgh->msg_control);                                        // (6) 0.04688
/*26  */     target_cmsg = lock_user(VERIFY_READ, target_cmsg_addr, msg_controllen, 1);                   // (2) 0.06445
/*28  */     if (!target_cmsg)                                                                            // (21) 0.01953
/*30  */         return -TARGET_EFAULT;                                                                   // (16) 0.0293
/*34  */     while (cmsg && target_cmsg) {                                                                // (17) 0.02734
/*36  */         void *data = CMSG_DATA(cmsg);                                                            // (12) 0.03711
/*38  */         void *target_data = TARGET_CMSG_DATA(target_cmsg);                                       // (3) 0.05273
/*42  */         int len = tswapal(target_cmsg->cmsg_len)                                                 // (5) 0.04883
/*44  */                   - TARGET_CMSG_ALIGN(sizeof (struct target_cmsghdr));                           // (1) 0.07422
/*48  */         space += CMSG_SPACE(len);                                                                // (13) 0.0332
/*50  */         if (space > msgh->msg_controllen) {                                                      // (10) 0.04102
/*52  */             space -= CMSG_SPACE(len);                                                            // (11) 0.04102
/*54  */             gemu_log("Host cmsg overflow\n");                                                    // 0.0
/*56  */             break;                                                                               // 0.0
/*58  */         }                                                                                        // 0.0
/*62  */         if (tswap32(target_cmsg->cmsg_level) == TARGET_SOL_SOCKET) {                             // 0.0
/*64  */             cmsg->cmsg_level = SOL_SOCKET;                                                       // 0.0
/*66  */         } else {                                                                                 // 0.0
/*68  */             cmsg->cmsg_level = tswap32(target_cmsg->cmsg_level);                                 // 0.0
/*70  */         }                                                                                        // 0.0
/*72  */         cmsg->cmsg_type = tswap32(target_cmsg->cmsg_type);                                       // 0.0
/*74  */         cmsg->cmsg_len = CMSG_LEN(len);                                                          // 0.0
/*78  */         if (cmsg->cmsg_level != SOL_SOCKET || cmsg->cmsg_type != SCM_RIGHTS) {                   // 0.0
/*80  */             gemu_log("Unsupported ancillary data: %d/%d\n", cmsg->cmsg_level, cmsg->cmsg_type);  // 0.0
/*82  */             memcpy(data, target_data, len);                                                      // 0.0
/*84  */         } else {                                                                                 // 0.0
/*86  */             int *fd = (int *)data;                                                               // 0.0
/*88  */             int *target_fd = (int *)target_data;                                                 // 0.0
/*90  */             int i, numfds = len / sizeof(int);                                                   // 0.0
/*94  */             for (i = 0; i < numfds; i++)                                                         // 0.0
/*96  */                 fd[i] = tswap32(target_fd[i]);                                                   // 0.0
/*98  */         }                                                                                        // 0.0
/*102 */         cmsg = CMSG_NXTHDR(msgh, cmsg);                                                          // 0.0
/*104 */         target_cmsg = TARGET_CMSG_NXTHDR(target_msgh, target_cmsg);                              // 0.0
/*106 */     }                                                                                            // 0.0
/*108 */     unlock_user(target_cmsg, target_cmsg_addr, 0);                                               // 0.0
/*110 */  the_end:                                                                                        // 0.0
/*112 */     msgh->msg_controllen = space;                                                                // 0.0
/*114 */     return 0;                                                                                    // 0.0
/*116 */ }                                                                                                // 0.0
