// commit message FFmpeg@8d857c5434 (target=1, prob=0.9991755, correct=True): Add a few size checks when decoding rtjpeg blocks. Might avoid crashes in unlikely cases, but mostly avoids ugly artefacts for partial frames.
/*0  */ static inline int get_block(GetBitContext *gb, DCTELEM *block, const uint8_t *scan,  // (4) 0.04727
/*2  */                             const uint32_t *quant) {                                 // (2) 0.05585
/*4  */     int coeff, i, n;                                                                 // (18) 0.01726
/*6  */     int8_t ac;                                                                       // (20) 0.01415
/*8  */     uint8_t dc = get_bits(gb, 8);                                                    // (11) 0.0267
/*12 */     // block not coded                                                               // (28) 0.0126
/*14 */     if (dc == 255)                                                                   // (19) 0.0143
/*19 */     // number of non-zero coefficients                                               // (17) 0.01806
/*21 */     coeff = get_bits(gb, 6);                                                         // (14) 0.02201
/*23 */     if (get_bits_count(gb) + (coeff << 1) >= gb->size_in_bits)                       // (3) 0.04975
/*28 */     // normally we would only need to clear the (63 - coeff) last values,            // (0) 0.119
/*30 */     // but since we do not know where they are we just clear the whole block         // (1) 0.0613
/*32 */     memset(block, 0, 64 * sizeof(DCTELEM));                                          // (6) 0.03339
/*36 */     // 2 bits per coefficient                                                        // (25) 0.01306
/*38 */     while (coeff) {                                                                  // (21) 0.01415
/*40 */         ac = get_sbits(gb, 2);                                                       // (9) 0.02798
/*42 */         if (ac == -2)                                                                // (16) 0.02171
/*44 */             break; // continue with more bits                                        // (7) 0.0283
/*46 */         PUT_COEFF(ac);                                                               // (12) 0.02352
/*48 */     }                                                                                // (30) 0.006441
/*52 */     // 4 bits per coefficient                                                        // (24) 0.01334
/*54 */     ALIGN(4);                                                                        // (29) 0.0125
/*58 */     while (coeff) {                                                                  // (23) 0.01401
/*60 */         ac = get_sbits(gb, 4);                                                       // (10) 0.02794
/*62 */         if (ac == -8)                                                                // (15) 0.02171
/*64 */             break; // continue with more bits                                        // (8) 0.02817
/*66 */         PUT_COEFF(ac);                                                               // (13) 0.02327
/*68 */     }                                                                                // (31) 0.006318
/*72 */     // 8 bits per coefficient                                                        // (26) 0.01289
/*74 */     ALIGN(8);                                                                        // (27) 0.01267
/*76 */     if (get_bits_count(gb) + (coeff << 3) >= gb->size_in_bits)                       // (5) 0.04668
/*79 */     while (coeff) {                                                                  // (22) 0.01402
/*81 */         ac = get_sbits(gb, 8);                                                       // 0.0
/*83 */         PUT_COEFF(ac);                                                               // 0.0
/*85 */     }                                                                                // 0.0
/*89 */     PUT_COEFF(dc);                                                                   // 0.0
/*91 */     return 1;                                                                        // 0.0
/*93 */ }                                                                                    // 0.0
