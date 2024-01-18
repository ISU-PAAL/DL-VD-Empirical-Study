// commit message qemu@2e50326c44 (target=1, prob=0.9990852, correct=True): net: check for TUNSETOFFLOAD support before trying to enable offload features
/*0  */ void tap_fd_set_offload(int fd, int csum, int tso4,                // (8) 0.05651
/*1  */                         int tso6, int ecn, int ufo)                // (0) 0.08845
/*2  */ {                                                                  // (18) 0.002457
/*3  */     unsigned int offload = 0;                                      // (16) 0.02457
/*4  */     if (csum) {                                                    // (17) 0.02211
/*5  */         offload |= TUN_F_CSUM;                                     // (12) 0.04668
/*6  */         if (tso4)                                                  // (13) 0.03194
/*7  */             offload |= TUN_F_TSO4;                                 // (6) 0.05897
/*8  */         if (tso6)                                                  // (14) 0.03194
/*9  */             offload |= TUN_F_TSO6;                                 // (7) 0.05897
/*10 */         if ((tso4 || tso6) && ecn)                                 // (10) 0.0516
/*11 */             offload |= TUN_F_TSO_ECN;                              // (4) 0.06388
/*12 */         if (ufo)                                                   // (15) 0.02948
/*13 */             offload |= TUN_F_UFO;                                  // (9) 0.05651
/*14 */     if (ioctl(fd, TUNSETOFFLOAD, offload) != 0) {                  // (5) 0.05897
/*15 */         offload &= ~TUN_F_UFO;                                     // (11) 0.04914
/*16 */         if (ioctl(fd, TUNSETOFFLOAD, offload) != 0) {              // (2) 0.0688
/*17 */             fprintf(stderr, "TUNSETOFFLOAD ioctl() failed: %s\n",  // (1) 0.08599
/*18 */                     strerror(errno));                              // (3) 0.06388
