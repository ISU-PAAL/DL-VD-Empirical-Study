// commit message qemu@4be746345f (target=0, prob=0.6181729, correct=False): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static inline int onenand_erase(OneNANDState *s, int sec, int num)   // (6) 0.04492
/*2  */ {                                                                    // (27) 0.001953
/*4  */     uint8_t *blankbuf, *tmpbuf;                                      // (12) 0.0293
/*6  */     blankbuf = g_malloc(512);                                        // (15) 0.02539
/*8  */     if (!blankbuf) {                                                 // (23) 0.01758
/*10 */         return 1;                                                    // (20) 0.01953
/*12 */     }                                                                // (25) 0.007812
/*14 */     tmpbuf = g_malloc(512);                                          // (16) 0.02539
/*16 */     if (!tmpbuf) {                                                   // (24) 0.01758
/*18 */         g_free(blankbuf);                                            // (14) 0.02734
/*20 */         return 1;                                                    // (21) 0.01953
/*22 */     }                                                                // (26) 0.007812
/*24 */     memset(blankbuf, 0xff, 512);                                     // (13) 0.02734
/*26 */     for (; num > 0; num--, sec++) {                                  // (11) 0.03125
/*28 */         if (s->bdrv_cur) {                                           // (7) 0.03516
/*30 */             int erasesec = s->secs_cur + (sec >> 5);                 // (4) 0.05469
/*32 */             if (bdrv_write(s->bdrv_cur, sec, blankbuf, 1) < 0) {     // (2) 0.07422
/*34 */                 goto fail;                                           // (8) 0.03516
/*36 */             }                                                        // (17) 0.02344
/*38 */             if (bdrv_read(s->bdrv_cur, erasesec, tmpbuf, 1) < 0) {   // (0) 0.07812
/*40 */                 goto fail;                                           // (9) 0.03516
/*42 */             }                                                        // (18) 0.02344
/*44 */             memcpy(tmpbuf + ((sec & 31) << 4), blankbuf, 1 << 4);    // (3) 0.06445
/*46 */             if (bdrv_write(s->bdrv_cur, erasesec, tmpbuf, 1) < 0) {  // (1) 0.07812
/*48 */                 goto fail;                                           // (10) 0.03516
/*50 */             }                                                        // (19) 0.02344
/*52 */         } else {                                                     // (22) 0.01953
/*54 */             if (sec + 1 > s->secs_cur) {                             // (5) 0.04883
/*56 */                 goto fail;                                           // 0.0
/*58 */             }                                                        // 0.0
/*60 */             memcpy(s->current + (sec << 9), blankbuf, 512);          // 0.0
/*62 */             memcpy(s->current + (s->secs_cur << 9) + (sec << 4),     // 0.0
/*64 */                    blankbuf, 1 << 4);                                // 0.0
/*66 */         }                                                            // 0.0
/*68 */     }                                                                // 0.0
/*72 */     g_free(tmpbuf);                                                  // 0.0
/*74 */     g_free(blankbuf);                                                // 0.0
/*76 */     return 0;                                                        // 0.0
/*80 */ fail:                                                                // 0.0
/*82 */     g_free(tmpbuf);                                                  // 0.0
/*84 */     g_free(blankbuf);                                                // 0.0
/*86 */     return 1;                                                        // 0.0
/*88 */ }                                                                    // 0.0
