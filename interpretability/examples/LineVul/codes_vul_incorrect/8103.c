// commit message FFmpeg@3932ccc472 (target=1, prob=0.45499063, correct=False): ppc: pixblockdsp: do unaligned block accesses correctly again
/*0   */ static void diff_pixels_altivec(int16_t *restrict block, const uint8_t *s1,     // (7) 0.01482
/*2   */                                 const uint8_t *s2, int stride)                  // (16) 0.002576
/*4   */ {                                                                               // (22) 0.0002616
/*6   */     int i;                                                                      // (21) 0.0007123
/*8   */     vec_u8 perm1 = vec_lvsl(0, s1);                                             // (19) 0.002249
/*10  */     vec_u8 perm2 = vec_lvsl(0, s2);                                             // (20) 0.001736
/*12  */     const vec_u8 zero = (const vec_u8)vec_splat_u8(0);                          // (10) 0.005305
/*14  */     vec_s16 shorts1, shorts2;                                                   // (15) 0.002629
/*18  */     for (i = 0; i < 4; i++) {                                                   // (18) 0.002254
/*20  */         /* Read potentially unaligned pixels.                                   // (6) 0.01532
/*22  */          * We're reading 16 pixels, and actually only want 8,                   // (13) 0.004475
/*24  */          * but we simply ignore the extras. */                                  // (4) 0.03432
/*26  */         vec_u8 pixl  = vec_ld(0,  s1);                                          // (14) 0.004014
/*28  */         vec_u8 pixr  = vec_ld(15, s1);                                          // (17) 0.002516
/*30  */         vec_u8 bytes = vec_perm(pixl, pixr, perm1);                             // (12) 0.004682
/*34  */         // Convert the bytes into shorts.                                       // (3) 0.03745
/*36  */         shorts1 = (vec_s16)vec_mergeh(zero, bytes);                             // (1) 0.07638
/*40  */         // Do the same for the second block of pixels.                          // (0) 0.4217
/*42  */         pixl  = vec_ld(0,  s2);                                                 // (8) 0.01237
/*44  */         pixr  = vec_ld(15, s2);                                                 // (11) 0.004693
/*46  */         bytes = vec_perm(pixl, pixr, perm2);                                    // (9) 0.007327
/*50  */         // Convert the bytes into shorts.                                       // (2) 0.04026
/*52  */         shorts2 = (vec_s16)vec_mergeh(zero, bytes);                             // (5) 0.02525
/*56  */         // Do the subtraction.                                                  // 0.0
/*58  */         shorts1 = vec_sub(shorts1, shorts2);                                    // 0.0
/*62  */         // Save the data to the block, we assume the block is 16-byte aligned.  // 0.0
/*64  */         vec_st(shorts1, 0, (vec_s16 *)block);                                   // 0.0
/*68  */         s1    += stride;                                                        // 0.0
/*70  */         s2    += stride;                                                        // 0.0
/*72  */         block += 8;                                                             // 0.0
/*76  */         /* The code below is a copy of the code above...                        // 0.0
/*78  */          * This is a manual unroll. */                                          // 0.0
/*82  */         /* Read potentially unaligned pixels.                                   // 0.0
/*84  */          * We're reading 16 pixels, and actually only want 8,                   // 0.0
/*86  */          * but we simply ignore the extras. */                                  // 0.0
/*88  */         pixl  = vec_ld(0,  s1);                                                 // 0.0
/*90  */         pixr  = vec_ld(15, s1);                                                 // 0.0
/*92  */         bytes = vec_perm(pixl, pixr, perm1);                                    // 0.0
/*96  */         // Convert the bytes into shorts.                                       // 0.0
/*98  */         shorts1 = (vec_s16)vec_mergeh(zero, bytes);                             // 0.0
/*102 */         // Do the same for the second block of pixels.                          // 0.0
/*104 */         pixl  = vec_ld(0,  s2);                                                 // 0.0
/*106 */         pixr  = vec_ld(15, s2);                                                 // 0.0
/*108 */         bytes = vec_perm(pixl, pixr, perm2);                                    // 0.0
/*112 */         // Convert the bytes into shorts.                                       // 0.0
/*114 */         shorts2 = (vec_s16)vec_mergeh(zero, bytes);                             // 0.0
/*118 */         // Do the subtraction.                                                  // 0.0
/*120 */         shorts1 = vec_sub(shorts1, shorts2);                                    // 0.0
/*124 */         // Save the data to the block, we assume the block is 16-byte aligned.  // 0.0
/*126 */         vec_st(shorts1, 0, (vec_s16 *)block);                                   // 0.0
/*130 */         s1    += stride;                                                        // 0.0
/*132 */         s2    += stride;                                                        // 0.0
/*134 */         block += 8;                                                             // 0.0
/*136 */     }                                                                           // 0.0
/*138 */ }                                                                               // 0.0
