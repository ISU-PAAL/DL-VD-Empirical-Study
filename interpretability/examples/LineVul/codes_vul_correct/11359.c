// commit message qemu@968fc24d84 (target=1, prob=0.9557687, correct=True): xbzrle.c: Avoid undefined behaviour with signed arithmetic
/*0   */ int xbzrle_encode_buffer(uint8_t *old_buf, uint8_t *new_buf, int slen,       // (2) 0.06641
/*2   */                          uint8_t *dst, int dlen)                             // (1) 0.07032
/*4   */ {                                                                            // (25) 0.001953
/*6   */     uint32_t zrun_len = 0, nzrun_len = 0;                                    // (5) 0.04297
/*8   */     int d = 0, i = 0;                                                        // (18) 0.02344
/*10  */     long res, xor;                                                           // (22) 0.01758
/*12  */     uint8_t *nzrun_start = NULL;                                             // (14) 0.0293
/*16  */     g_assert(!(((uintptr_t)old_buf | (uintptr_t)new_buf | slen) %            // (3) 0.06445
/*18  */                sizeof(long)));                                               // (8) 0.03711
/*22  */     while (i < slen) {                                                       // (20) 0.02148
/*24  */         /* overflow */                                                       // (21) 0.01953
/*26  */         if (d + 2 > dlen) {                                                  // (10) 0.0332
/*28  */             return -1;                                                       // (15) 0.0293
/*30  */         }                                                                    // (23) 0.01562
/*34  */         /* not aligned to sizeof(long) */                                    // (11) 0.03125
/*36  */         res = (slen - i) % sizeof(long);                                     // (7) 0.03906
/*38  */         while (res && old_buf[i] == new_buf[i]) {                            // (4) 0.04883
/*40  */             zrun_len++;                                                      // (12) 0.03125
/*42  */             i++;                                                             // (17) 0.02539
/*44  */             res--;                                                           // (16) 0.02734
/*46  */         }                                                                    // (24) 0.01562
/*50  */         /* word at a time for speed */                                       // (13) 0.0293
/*52  */         if (!res) {                                                          // (19) 0.02344
/*54  */             while (i < slen &&                                               // (9) 0.03516
/*56  */                    (*(long *)(old_buf + i)) == (*(long *)(new_buf + i))) {   // (0) 0.08203
/*58  */                 i += sizeof(long);                                           // (6) 0.04102
/*60  */                 zrun_len += sizeof(long);                                    // 0.0
/*62  */             }                                                                // 0.0
/*66  */             /* go over the rest */                                           // 0.0
/*68  */             while (i < slen && old_buf[i] == new_buf[i]) {                   // 0.0
/*70  */                 zrun_len++;                                                  // 0.0
/*72  */                 i++;                                                         // 0.0
/*74  */             }                                                                // 0.0
/*76  */         }                                                                    // 0.0
/*80  */         /* buffer unchanged */                                               // 0.0
/*82  */         if (zrun_len == slen) {                                              // 0.0
/*84  */             return 0;                                                        // 0.0
/*86  */         }                                                                    // 0.0
/*90  */         /* skip last zero run */                                             // 0.0
/*92  */         if (i == slen) {                                                     // 0.0
/*94  */             return d;                                                        // 0.0
/*96  */         }                                                                    // 0.0
/*100 */         d += uleb128_encode_small(dst + d, zrun_len);                        // 0.0
/*104 */         zrun_len = 0;                                                        // 0.0
/*106 */         nzrun_start = new_buf + i;                                           // 0.0
/*110 */         /* overflow */                                                       // 0.0
/*112 */         if (d + 2 > dlen) {                                                  // 0.0
/*114 */             return -1;                                                       // 0.0
/*116 */         }                                                                    // 0.0
/*118 */         /* not aligned to sizeof(long) */                                    // 0.0
/*120 */         res = (slen - i) % sizeof(long);                                     // 0.0
/*122 */         while (res && old_buf[i] != new_buf[i]) {                            // 0.0
/*124 */             i++;                                                             // 0.0
/*126 */             nzrun_len++;                                                     // 0.0
/*128 */             res--;                                                           // 0.0
/*130 */         }                                                                    // 0.0
/*134 */         /* word at a time for speed, use of 32-bit long okay */              // 0.0
/*136 */         if (!res) {                                                          // 0.0
/*138 */             /* truncation to 32-bit long okay */                             // 0.0
/*140 */             long mask = (long)0x0101010101010101ULL;                         // 0.0
/*142 */             while (i < slen) {                                               // 0.0
/*144 */                 xor = *(long *)(old_buf + i) ^ *(long *)(new_buf + i);       // 0.0
/*146 */                 if ((xor - mask) & ~xor & (mask << 7)) {                     // 0.0
/*148 */                     /* found the end of an nzrun within the current long */  // 0.0
/*150 */                     while (old_buf[i] != new_buf[i]) {                       // 0.0
/*152 */                         nzrun_len++;                                         // 0.0
/*154 */                         i++;                                                 // 0.0
/*156 */                     }                                                        // 0.0
/*158 */                     break;                                                   // 0.0
/*160 */                 } else {                                                     // 0.0
/*162 */                     i += sizeof(long);                                       // 0.0
/*164 */                     nzrun_len += sizeof(long);                               // 0.0
/*166 */                 }                                                            // 0.0
/*168 */             }                                                                // 0.0
/*170 */         }                                                                    // 0.0
/*174 */         d += uleb128_encode_small(dst + d, nzrun_len);                       // 0.0
/*176 */         /* overflow */                                                       // 0.0
/*178 */         if (d + nzrun_len > dlen) {                                          // 0.0
/*180 */             return -1;                                                       // 0.0
/*182 */         }                                                                    // 0.0
/*184 */         memcpy(dst + d, nzrun_start, nzrun_len);                             // 0.0
/*186 */         d += nzrun_len;                                                      // 0.0
/*188 */         nzrun_len = 0;                                                       // 0.0
/*190 */     }                                                                        // 0.0
/*194 */     return d;                                                                // 0.0
/*196 */ }                                                                            // 0.0
