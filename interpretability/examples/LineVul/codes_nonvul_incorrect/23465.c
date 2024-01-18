// commit message FFmpeg@dde0af2df1 (target=0, prob=0.51857495, correct=False): vble: move get_bits_left() check out of inner loop, we can perform the check completely before the loop.
/*0  */ static int vble_unpack(VBLEContext *ctx, GetBitContext *gb)                    // (6) 0.03907
/*2  */ {                                                                              // (9) 0.001953
/*4  */     int i;                                                                     // (8) 0.01172
/*6  */     static const uint8_t LUT[256] = {                                          // (7) 0.03125
/*8  */         8,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,       // (0) 0.1387
/*10 */         5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,       // (1) 0.1387
/*12 */         6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,       // (2) 0.1387
/*14 */         5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,       // (5) 0.1387
/*16 */         7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,       // (4) 0.1387
/*18 */         5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,       // (3) 0.1387
/*20 */         6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,       // 0.0
/*22 */         5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,       // 0.0
/*24 */     };                                                                         // 0.0
/*28 */     /* Read all the lengths in first */                                        // 0.0
/*30 */     for (i = 0; i < ctx->size; i++) {                                          // 0.0
/*32 */         /* At most we need to read 9 bits total to get indices up to 8 */      // 0.0
/*34 */         int val = show_bits(gb, 8);                                            // 0.0
/*38 */         // read reverse unary                                                  // 0.0
/*40 */         if (val) {                                                             // 0.0
/*42 */             val = LUT[val];                                                    // 0.0
/*44 */             skip_bits(gb, val + 1);                                            // 0.0
/*46 */             ctx->len[i] = val;                                                 // 0.0
/*48 */         } else {                                                               // 0.0
/*50 */             skip_bits(gb, 8);                                                  // 0.0
/*52 */             if (!get_bits1(gb))                                                // 0.0
/*54 */                 return -1;                                                     // 0.0
/*56 */             ctx->len[i] = 8;                                                   // 0.0
/*58 */         }                                                                      // 0.0
/*60 */     }                                                                          // 0.0
/*64 */     /* For any values that have length 0 */                                    // 0.0
/*66 */     memset(ctx->val, 0, ctx->size);                                            // 0.0
/*70 */     for (i = 0; i < ctx->size; i++) {                                          // 0.0
/*72 */         /* Check we have enough bits left */                                   // 0.0
/*74 */         if (get_bits_left(gb) < ctx->len[i])                                   // 0.0
/*76 */             return -1;                                                         // 0.0
/*80 */         /* get_bits can't take a length of 0 */                                // 0.0
/*82 */         if (ctx->len[i])                                                       // 0.0
/*84 */             ctx->val[i] = (1 << ctx->len[i]) + get_bits(gb, ctx->len[i]) - 1;  // 0.0
/*86 */     }                                                                          // 0.0
/*90 */     return 0;                                                                  // 0.0
/*92 */ }                                                                              // 0.0
