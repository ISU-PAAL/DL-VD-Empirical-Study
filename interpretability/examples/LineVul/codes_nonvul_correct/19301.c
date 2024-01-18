// commit message qemu@b63c7f6b77 (target=0, prob=0.43263906, correct=True): slirp: Handle DHCP requests for specific IP (Jan Kiszka)
/*0  */ static void dhcp_decode(const uint8_t *buf, int size,        // (7) 0.03711
/*2  */                         int *pmsg_type)                      // (1) 0.05859
/*4  */ {                                                            // (30) 0.001953
/*6  */     const uint8_t *p, *p_end;                                // (12) 0.03125
/*8  */     int len, tag;                                            // (27) 0.01562
/*12 */     *pmsg_type = 0;                                          // (22) 0.02148
/*16 */     p = buf;                                                 // (28) 0.01367
/*18 */     p_end = buf + size;                                      // (21) 0.02148
/*20 */     if (size < 5)                                            // (24) 0.01758
/*22 */         return;                                              // (25) 0.01758
/*24 */     if (memcmp(p, rfc1533_cookie, 4) != 0)                   // (3) 0.04297
/*26 */         return;                                              // (26) 0.01758
/*28 */     p += 4;                                                  // (29) 0.01367
/*30 */     while (p < p_end) {                                      // (20) 0.02344
/*32 */         tag = p[0];                                          // (17) 0.02539
/*34 */         if (tag == RFC1533_PAD) {                            // (8) 0.03711
/*36 */             p++;                                             // (15) 0.02539
/*38 */         } else if (tag == RFC1533_END) {                     // (6) 0.03906
/*40 */             break;                                           // (18) 0.02539
/*42 */         } else {                                             // (23) 0.01953
/*44 */             p++;                                             // (16) 0.02539
/*46 */             if (p >= p_end)                                  // (9) 0.03711
/*48 */                 break;                                       // (10) 0.0332
/*50 */             len = *p++;                                      // (13) 0.03125
/*52 */             dprintf("dhcp: tag=0x%02x len=%d\n", tag, len);  // (0) 0.06836
/*56 */             switch(tag) {                                    // (14) 0.03125
/*58 */             case RFC2132_MSG_TYPE:                           // (4) 0.04102
/*60 */                 if (len >= 1)                                // (5) 0.04102
/*62 */                     *pmsg_type = p[0];                       // (2) 0.05664
/*64 */                 break;                                       // (11) 0.0332
/*66 */             default:                                         // (19) 0.02539
/*68 */                 break;                                       // 0.0
/*70 */             }                                                // 0.0
/*72 */             p += len;                                        // 0.0
/*74 */         }                                                    // 0.0
/*76 */     }                                                        // 0.0
/*78 */ }                                                            // 0.0
