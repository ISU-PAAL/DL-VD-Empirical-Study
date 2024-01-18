// commit message FFmpeg@5127f465bd (target=1, prob=0.9343941, correct=True): Prevent out of bound read in lz_unpack in vmd video decoder.
/*0   */ static void lz_unpack(const unsigned char *src, unsigned char *dest, int dest_len)  // (2) 0.04688
/*2   */ {                                                                                   // (34) 0.001953
/*4   */     const unsigned char *s;                                                         // (22) 0.01758
/*6   */     unsigned char *d;                                                               // (26) 0.01562
/*8   */     unsigned char *d_end;                                                           // (19) 0.01953
/*10  */     unsigned char queue[QUEUE_SIZE];                                                // (14) 0.02539
/*12  */     unsigned int qpos;                                                              // (27) 0.01562
/*14  */     unsigned int dataleft;                                                          // (21) 0.01758
/*16  */     unsigned int chainofs;                                                          // (20) 0.01758
/*18  */     unsigned int chainlen;                                                          // (25) 0.01563
/*20  */     unsigned int speclen;                                                           // (24) 0.01758
/*22  */     unsigned char tag;                                                              // (29) 0.01367
/*24  */     unsigned int i, j;                                                              // (23) 0.01758
/*28  */     s = src;                                                                        // (30) 0.01367
/*30  */     d = dest;                                                                       // (28) 0.01367
/*32  */     d_end = d + dest_len;                                                           // (15) 0.02539
/*34  */     dataleft = AV_RL32(s);                                                          // (12) 0.02734
/*36  */     s += 4;                                                                         // (31) 0.01367
/*38  */     memset(queue, 0x20, QUEUE_SIZE);                                                // (8) 0.03516
/*40  */     if (AV_RL32(s) == 0x56781234) {                                                 // (5) 0.04102
/*42  */         s += 4;                                                                     // (18) 0.02148
/*44  */         qpos = 0x111;                                                               // (13) 0.02734
/*46  */         speclen = 0xF + 3;                                                          // (9) 0.0332
/*48  */     } else {                                                                        // (32) 0.01172
/*50  */         qpos = 0xFEE;                                                               // (11) 0.0293
/*52  */         speclen = 100;  /* no speclen */                                            // (7) 0.03906
/*54  */     }                                                                               // (33) 0.007812
/*58  */     while (dataleft > 0) {                                                          // (16) 0.02344
/*60  */         tag = *s++;                                                                 // (17) 0.02344
/*62  */         if ((tag == 0xFF) && (dataleft > 8)) {                                      // (3) 0.04687
/*64  */             if (d + 8 > d_end)                                                      // (6) 0.04102
/*66  */                 return;                                                             // (10) 0.0332
/*68  */             for (i = 0; i < 8; i++) {                                               // (4) 0.04687
/*70  */                 queue[qpos++] = *d++ = *s++;                                        // (0) 0.05664
/*72  */                 qpos &= QUEUE_MASK;                                                 // (1) 0.05078
/*74  */             }                                                                       // 0.0
/*76  */             dataleft -= 8;                                                          // 0.0
/*78  */         } else {                                                                    // 0.0
/*80  */             for (i = 0; i < 8; i++) {                                               // 0.0
/*82  */                 if (dataleft == 0)                                                  // 0.0
/*84  */                     break;                                                          // 0.0
/*86  */                 if (tag & 0x01) {                                                   // 0.0
/*88  */                     if (d + 1 > d_end)                                              // 0.0
/*90  */                         return;                                                     // 0.0
/*92  */                     queue[qpos++] = *d++ = *s++;                                    // 0.0
/*94  */                     qpos &= QUEUE_MASK;                                             // 0.0
/*96  */                     dataleft--;                                                     // 0.0
/*98  */                 } else {                                                            // 0.0
/*100 */                     chainofs = *s++;                                                // 0.0
/*102 */                     chainofs |= ((*s & 0xF0) << 4);                                 // 0.0
/*104 */                     chainlen = (*s++ & 0x0F) + 3;                                   // 0.0
/*106 */                     if (chainlen == speclen)                                        // 0.0
/*108 */                         chainlen = *s++ + 0xF + 3;                                  // 0.0
/*110 */                     if (d + chainlen > d_end)                                       // 0.0
/*112 */                         return;                                                     // 0.0
/*114 */                     for (j = 0; j < chainlen; j++) {                                // 0.0
/*116 */                         *d = queue[chainofs++ & QUEUE_MASK];                        // 0.0
/*118 */                         queue[qpos++] = *d++;                                       // 0.0
/*120 */                         qpos &= QUEUE_MASK;                                         // 0.0
/*122 */                     }                                                               // 0.0
/*124 */                     dataleft -= chainlen;                                           // 0.0
/*126 */                 }                                                                   // 0.0
/*128 */                 tag >>= 1;                                                          // 0.0
/*130 */             }                                                                       // 0.0
/*132 */         }                                                                           // 0.0
/*134 */     }                                                                               // 0.0
/*136 */ }                                                                                   // 0.0
