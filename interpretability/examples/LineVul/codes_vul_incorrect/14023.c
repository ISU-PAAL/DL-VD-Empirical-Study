// commit message qemu@d861b05ea3 (target=1, prob=0.12718083, correct=False): Avoid buffer overflow when sending slirp packets.
/*0   */ static void ne2000_receive(void *opaque, const uint8_t *buf, int size)  // (3) 0.04688
/*2   */ {                                                                       // (30) 0.001953
/*4   */     NE2000State *s = opaque;                                            // (20) 0.02148
/*6   */     uint8_t *p;                                                         // (21) 0.01953
/*8   */     int total_len, next, avail, len, index, mcast_idx;                  // (7) 0.04297
/*10  */     uint8_t buf1[60];                                                   // (19) 0.02344
/*12  */     static const uint8_t broadcast_macaddr[6] =                         // (10) 0.03516
/*14  */         { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };                         // (2) 0.05078
/*16  */                                                                         // (27) 0.007813
/*18  */ #if defined(DEBUG_NE2000)                                               // (22) 0.01758
/*20  */     printf("NE2000: received len=%d\n", size);                          // (9) 0.03516
/*22  */ #endif                                                                  // (29) 0.003906
/*26  */     if (!ne2000_can_receive(s))                                         // (14) 0.0293
/*28  */         return;                                                         // (23) 0.01758
/*30  */                                                                         // (28) 0.007812
/*32  */     /* XXX: check this */                                               // (24) 0.01758
/*34  */     if (s->rxcr & 0x10) {                                               // (18) 0.0293
/*36  */         /* promiscuous: receive all */                                  // (16) 0.0293
/*38  */     } else {                                                            // (26) 0.01172
/*40  */         if (!memcmp(buf,  broadcast_macaddr, 6)) {                      // (4) 0.04492
/*42  */             /* broadcast address */                                     // (15) 0.0293
/*44  */             if (!(s->rxcr & 0x04))                                      // (5) 0.04492
/*46  */                 return;                                                 // (11) 0.0332
/*48  */         } else if (buf[0] & 0x01) {                                     // (8) 0.04102
/*50  */             /* multicast */                                             // (17) 0.0293
/*52  */             if (!(s->rxcr & 0x08))                                      // (6) 0.04492
/*54  */                 return;                                                 // (12) 0.0332
/*56  */             mcast_idx = compute_mcast_idx(buf);                         // (1) 0.05273
/*58  */             if (!(s->mult[mcast_idx >> 3] & (1 << (mcast_idx & 7))))    // (0) 0.07617
/*60  */                 return;                                                 // (13) 0.0332
/*62  */         } else if (s->mem[0] == buf[0] &&                               // 0.0
/*64  */                    s->mem[2] == buf[1] &&                               // 0.0
/*66  */                    s->mem[4] == buf[2] &&                               // 0.0
/*68  */                    s->mem[6] == buf[3] &&                               // 0.0
/*70  */                    s->mem[8] == buf[4] &&                               // 0.0
/*72  */                    s->mem[10] == buf[5]) {                              // 0.0
/*74  */             /* match */                                                 // 0.0
/*76  */         } else {                                                        // 0.0
/*78  */             return;                                                     // 0.0
/*80  */         }                                                               // (25) 0.01562
/*82  */     }                                                                   // 0.0
/*88  */     /* if too small buffer, then expand it */                           // 0.0
/*90  */     if (size < MIN_BUF_SIZE) {                                          // 0.0
/*92  */         memcpy(buf1, buf, size);                                        // 0.0
/*94  */         memset(buf1 + size, 0, MIN_BUF_SIZE - size);                    // 0.0
/*96  */         buf = buf1;                                                     // 0.0
/*98  */         size = MIN_BUF_SIZE;                                            // 0.0
/*100 */     }                                                                   // 0.0
/*104 */     index = s->curpag << 8;                                             // 0.0
/*106 */     /* 4 bytes for header */                                            // 0.0
/*108 */     total_len = size + 4;                                               // 0.0
/*110 */     /* address for next packet (4 bytes for CRC) */                     // 0.0
/*112 */     next = index + ((total_len + 4 + 255) & ~0xff);                     // 0.0
/*114 */     if (next >= s->stop)                                                // 0.0
/*116 */         next -= (s->stop - s->start);                                   // 0.0
/*118 */     /* prepare packet header */                                         // 0.0
/*120 */     p = s->mem + index;                                                 // 0.0
/*122 */     s->rsr = ENRSR_RXOK; /* receive status */                           // 0.0
/*124 */     /* XXX: check this */                                               // 0.0
/*126 */     if (buf[0] & 0x01)                                                  // 0.0
/*128 */         s->rsr |= ENRSR_PHY;                                            // 0.0
/*130 */     p[0] = s->rsr;                                                      // 0.0
/*132 */     p[1] = next >> 8;                                                   // 0.0
/*134 */     p[2] = total_len;                                                   // 0.0
/*136 */     p[3] = total_len >> 8;                                              // 0.0
/*138 */     index += 4;                                                         // 0.0
/*142 */     /* write packet data */                                             // 0.0
/*144 */     while (size > 0) {                                                  // 0.0
/*146 */         avail = s->stop - index;                                        // 0.0
/*148 */         len = size;                                                     // 0.0
/*150 */         if (len > avail)                                                // 0.0
/*152 */             len = avail;                                                // 0.0
/*154 */         memcpy(s->mem + index, buf, len);                               // 0.0
/*156 */         buf += len;                                                     // 0.0
/*158 */         index += len;                                                   // 0.0
/*160 */         if (index == s->stop)                                           // 0.0
/*162 */             index = s->start;                                           // 0.0
/*164 */         size -= len;                                                    // 0.0
/*166 */     }                                                                   // 0.0
/*168 */     s->curpag = next >> 8;                                              // 0.0
/*172 */     /* now we can signal we have receive something */                   // 0.0
/*174 */     s->isr |= ENISR_RX;                                                 // 0.0
/*176 */     ne2000_update_irq(s);                                               // 0.0
/*178 */ }                                                                       // 0.0
