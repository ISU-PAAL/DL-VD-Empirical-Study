// commit message FFmpeg@e45a2872fa (target=0, prob=0.030096203, correct=True): 1) remove TBL support in PPC performance. It's much more useful to use the     PMCs, and with Apple's CHUD it's fairly easy too. No reason to keep useless     code around 2) make the PPC perf stuff a configure option 3) make put_pixels16_altivec a bit faster by unrolling the loop by 4 patch by (Romain Dolbeau <dolbeau at irisa dot fr>)
/*0  */ void avg_pixels16_altivec(uint8_t *block, const uint8_t *pixels, int line_size, int h)   // (3) 0.06836
/*2  */ {                                                                                        // (21) 0.001953
/*4  */ POWERPC_TBL_DECLARE(altivec_avg_pixels16_num, 1);                                        // (8) 0.05078
/*6  */ #ifdef ALTIVEC_USE_REFERENCE_C_CODE                                                      // (13) 0.03516
/*8  */     int i;                                                                               // (19) 0.01172
/*12 */ POWERPC_TBL_START_COUNT(altivec_avg_pixels16_num, 1);                                    // (7) 0.05469
/*16 */     for(i=0; i<h; i++) {                                                                 // (15) 0.03125
/*18 */       op_avg(*((uint32_t*)(block)),(((const struct unaligned_32 *)(pixels))->l));        // (4) 0.06836
/*20 */       op_avg(*((uint32_t*)(block+4)),(((const struct unaligned_32 *)(pixels+4))->l));    // (1) 0.07617
/*22 */       op_avg(*((uint32_t*)(block+8)),(((const struct unaligned_32 *)(pixels+8))->l));    // (2) 0.07617
/*24 */       op_avg(*((uint32_t*)(block+12)),(((const struct unaligned_32 *)(pixels+12))->l));  // (0) 0.07617
/*26 */       pixels+=line_size;                                                                 // (16) 0.02148
/*28 */       block +=line_size;                                                                 // (17) 0.02148
/*30 */     }                                                                                    // (20) 0.007813
/*34 */ POWERPC_TBL_STOP_COUNT(altivec_avg_pixels16_num, 1);                                     // (6) 0.05469
/*38 */ #else /* ALTIVEC_USE_REFERENCE_C_CODE */                                                 // (11) 0.03711
/*40 */     register vector unsigned char pixelsv1, pixelsv2, pixelsv, blockv;                   // (10) 0.04102
/*42 */     register vector unsigned char perm = vec_lvsl(0, pixels);                            // (12) 0.03516
/*44 */     int i;                                                                               // (18) 0.01172
/*48 */ POWERPC_TBL_START_COUNT(altivec_avg_pixels16_num, 1);                                    // (5) 0.05469
/*52 */     for(i=0; i<h; i++) {                                                                 // (14) 0.03125
/*54 */       pixelsv1 = vec_ld(0, (unsigned char*)pixels);                                      // (9) 0.04297
/*56 */       pixelsv2 = vec_ld(16, (unsigned char*)pixels);                                     // 0.0
/*58 */       blockv = vec_ld(0, block);                                                         // 0.0
/*60 */       pixelsv = vec_perm(pixelsv1, pixelsv2, perm);                                      // 0.0
/*62 */       blockv = vec_avg(blockv,pixelsv);                                                  // 0.0
/*64 */       vec_st(blockv, 0, (unsigned char*)block);                                          // 0.0
/*66 */       pixels+=line_size;                                                                 // 0.0
/*68 */       block +=line_size;                                                                 // 0.0
/*70 */     }                                                                                    // 0.0
/*74 */ POWERPC_TBL_STOP_COUNT(altivec_avg_pixels16_num, 1);                                     // 0.0
/*78 */ #endif /* ALTIVEC_USE_REFERENCE_C_CODE */                                                // 0.0
/*80 */ }                                                                                        // 0.0
