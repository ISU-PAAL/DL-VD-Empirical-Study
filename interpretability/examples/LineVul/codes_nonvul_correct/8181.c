// commit message FFmpeg@08a747afb9 (target=0, prob=0.30515382, correct=True): eac3enc: use frame exponent strategy when applicable.
/*0   */ static void count_frame_bits_fixed(AC3EncodeContext *s)               // (5) 0.03516
/*2   */ {                                                                     // (35) 0.001953
/*4   */     static const int frame_bits_inc[8] = { 0, 0, 2, 2, 2, 4, 2, 4 };  // (1) 0.0625
/*6   */     int blk;                                                          // (29) 0.01367
/*8   */     int frame_bits;                                                   // (27) 0.01562
/*12  */     /* assumptions:                                                   // (30) 0.01172
/*14  */      *   no dynamic range codes                                       // (23) 0.02148
/*16  */      *   bit allocation parameters do not change between blocks       // (7) 0.0293
/*18  */      *   no delta bit allocation                                      // (22) 0.02148
/*20  */      *   no skipped data                                              // (26) 0.01953
/*22  */      *   no auxilliary data                                           // (16) 0.02344
/*24  */      *   no E-AC-3 metadata                                           // (8) 0.02734
/*26  */      */                                                               // (33) 0.009766
/*30  */     /* header */                                                      // (31) 0.01172
/*32  */     frame_bits = 16; /* sync info */                                  // (9) 0.02539
/*34  */     if (s->eac3) {                                                    // (19) 0.02344
/*36  */         /* bitstream info header */                                   // (10) 0.02539
/*38  */         frame_bits += 35;                                             // (11) 0.02539
/*40  */         frame_bits += 1 + 1 + 1;                                      // (6) 0.0332
/*42  */         /* audio frame header */                                      // (18) 0.02344
/*44  */         frame_bits += 2;                                              // (12) 0.02539
/*46  */         frame_bits += 10;                                             // (13) 0.02539
/*48  */         /* exponent strategy */                                       // (24) 0.02148
/*50  */         for (blk = 0; blk < AC3_MAX_BLOCKS; blk++)                    // (2) 0.05664
/*52  */             frame_bits += 2 * s->fbw_channels + s->lfe_on;            // (0) 0.0625
/*54  */         /* converter exponent strategy */                             // (20) 0.02344
/*56  */         frame_bits += s->fbw_channels * 5;                            // (4) 0.04102
/*58  */         /* snr offsets */                                             // (21) 0.02344
/*60  */         frame_bits += 10;                                             // (14) 0.02539
/*62  */         /* block start info */                                        // (17) 0.02344
/*64  */         frame_bits++;                                                 // (25) 0.02148
/*66  */     } else {                                                          // (32) 0.01172
/*68  */         frame_bits += 49;                                             // (15) 0.02539
/*70  */         frame_bits += frame_bits_inc[s->channel_mode];                // (3) 0.04492
/*72  */     }                                                                 // (34) 0.007813
/*76  */     /* audio blocks */                                                // (28) 0.01367
/*78  */     for (blk = 0; blk < AC3_MAX_BLOCKS; blk++) {                      // 0.0
/*80  */         if (!s->eac3) {                                               // 0.0
/*82  */             /* block switch flags */                                  // 0.0
/*84  */             frame_bits += s->fbw_channels;                            // 0.0
/*88  */             /* dither flags */                                        // 0.0
/*90  */             frame_bits += s->fbw_channels;                            // 0.0
/*92  */         }                                                             // 0.0
/*96  */         /* dynamic range */                                           // 0.0
/*98  */         frame_bits++;                                                 // 0.0
/*102 */         /* spectral extension */                                      // 0.0
/*104 */         if (s->eac3)                                                  // 0.0
/*106 */             frame_bits++;                                             // 0.0
/*110 */         if (!s->eac3) {                                               // 0.0
/*112 */             /* exponent strategy */                                   // 0.0
/*114 */             frame_bits += 2 * s->fbw_channels;                        // 0.0
/*116 */             if (s->lfe_on)                                            // 0.0
/*118 */                 frame_bits++;                                         // 0.0
/*122 */             /* bit allocation params */                               // 0.0
/*124 */             frame_bits++;                                             // 0.0
/*126 */             if (!blk)                                                 // 0.0
/*128 */                 frame_bits += 2 + 2 + 2 + 2 + 3;                      // 0.0
/*130 */         }                                                             // 0.0
/*134 */         /* converter snr offset */                                    // 0.0
/*136 */         if (s->eac3)                                                  // 0.0
/*138 */             frame_bits++;                                             // 0.0
/*142 */         if (!s->eac3) {                                               // 0.0
/*144 */             /* delta bit allocation */                                // 0.0
/*146 */             frame_bits++;                                             // 0.0
/*150 */             /* skipped data */                                        // 0.0
/*152 */             frame_bits++;                                             // 0.0
/*154 */         }                                                             // 0.0
/*156 */     }                                                                 // 0.0
/*160 */     /* auxiliary data */                                              // 0.0
/*162 */     frame_bits++;                                                     // 0.0
/*166 */     /* CRC */                                                         // 0.0
/*168 */     frame_bits += 1 + 16;                                             // 0.0
/*172 */     s->frame_bits_fixed = frame_bits;                                 // 0.0
/*174 */ }                                                                     // 0.0
