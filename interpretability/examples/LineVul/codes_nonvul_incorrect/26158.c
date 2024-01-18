// commit message qemu@4be746345f (target=0, prob=0.8839504, correct=False): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static inline int onenand_prog_main(OneNANDState *s, int sec, int secn,  // (2) 0.05078
/*2  */                 void *src)                                               // (10) 0.03711
/*4  */ {                                                                        // (25) 0.001953
/*6  */     int result = 0;                                                      // (23) 0.01562
/*10 */     if (secn > 0) {                                                      // (21) 0.02148
/*12 */         uint32_t size = (uint32_t)secn * 512;                            // (5) 0.04688
/*14 */         const uint8_t *sp = (const uint8_t *)src;                        // (6) 0.04688
/*16 */         uint8_t *dp = 0;                                                 // (15) 0.03125
/*18 */         if (s->bdrv_cur) {                                               // (13) 0.03516
/*20 */             dp = g_malloc(size);                                         // (9) 0.04102
/*22 */             if (!dp || bdrv_read(s->bdrv_cur, sec, dp, secn) < 0) {      // (0) 0.08008
/*24 */                 result = 1;                                              // (11) 0.03711
/*26 */             }                                                            // (17) 0.02344
/*28 */         } else {                                                         // (22) 0.01953
/*30 */             if (sec + secn > s->secs_cur) {                              // (3) 0.05078
/*32 */                 result = 1;                                              // (12) 0.03711
/*34 */             } else {                                                     // (16) 0.02734
/*36 */                 dp = (uint8_t *)s->current + (sec << 9);                 // (1) 0.06445
/*38 */             }                                                            // (18) 0.02344
/*40 */         }                                                                // (24) 0.01562
/*42 */         if (!result) {                                                   // (19) 0.02344
/*44 */             uint32_t i;                                                  // (14) 0.0332
/*46 */             for (i = 0; i < size; i++) {                                 // (7) 0.04688
/*48 */                 dp[i] &= sp[i];                                          // (4) 0.05078
/*50 */             }                                                            // (20) 0.02344
/*52 */             if (s->bdrv_cur) {                                           // (8) 0.04297
/*54 */                 result = bdrv_write(s->bdrv_cur, sec, dp, secn) < 0;     // 0.0
/*56 */             }                                                            // 0.0
/*58 */         }                                                                // 0.0
/*60 */         if (dp && s->bdrv_cur) {                                         // 0.0
/*62 */             g_free(dp);                                                  // 0.0
/*64 */         }                                                                // 0.0
/*66 */     }                                                                    // 0.0
/*70 */     return result;                                                       // 0.0
/*72 */ }                                                                        // 0.0
