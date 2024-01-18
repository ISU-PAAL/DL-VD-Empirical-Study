// commit message FFmpeg@d82eccea2b (target=1, prob=0.64879733, correct=True): avcodec/mpeg12dec: check block index in mpeg2_fast_decode_block_non_intra()
/*0   */ static inline int mpeg2_fast_decode_block_non_intra(MpegEncContext *s,                // (5) 0.05078
/*2   */                                                     int16_t *block, int n)            // (0) 0.1191
/*4   */ {                                                                                     // (23) 0.001953
/*6   */     int level, i, j, run;                                                             // (17) 0.02344
/*8   */     RLTable *rl = &ff_rl_mpeg1;                                                       // (11) 0.03125
/*10  */     uint8_t * const scantable = s->intra_scantable.permutated;                        // (6) 0.04883
/*12  */     const int qscale          = s->qscale;                                            // (7) 0.04297
/*14  */     OPEN_READER(re, &s->gb);                                                          // (14) 0.0293
/*16  */     i = -1;                                                                           // (20) 0.01562
/*20  */     // special case for first coefficient, no need to add second VLC table            // (9) 0.03516
/*22  */     UPDATE_CACHE(re, &s->gb);                                                         // (12) 0.03125
/*24  */     if (((int32_t)GET_CACHE(re, &s->gb)) < 0) {                                       // (3) 0.05469
/*26  */         level = (3 * qscale) >> 1;                                                    // (10) 0.03516
/*28  */         if (GET_CACHE(re, &s->gb) & 0x40000000)                                       // (4) 0.05469
/*30  */             level = -level;                                                           // (13) 0.03125
/*32  */         block[0] = level;                                                             // (15) 0.02734
/*34  */         i++;                                                                          // (19) 0.01758
/*36  */         SKIP_BITS(re, &s->gb, 2);                                                     // (8) 0.04297
/*38  */         if (((int32_t)GET_CACHE(re, &s->gb)) <= (int32_t)0xBFFFFFFF)                  // (2) 0.08203
/*40  */             goto end;                                                                 // (16) 0.02734
/*42  */     }                                                                                 // (22) 0.007812
/*46  */     /* now quantify & encode AC coefficients */                                       // (18) 0.02148
/*48  */     for (;;) {                                                                        // (21) 0.01562
/*50  */         GET_RL_VLC(level, run, re, &s->gb, rl->rl_vlc[0], TEX_VLC_BITS, 2, 0);        // (1) 0.09375
/*54  */         if (level != 0) {                                                             // 0.0
/*56  */             i += run;                                                                 // 0.0
/*58  */             j  = scantable[i];                                                        // 0.0
/*60  */             level = ((level * 2 + 1) * qscale) >> 1;                                  // 0.0
/*62  */             level = (level ^ SHOW_SBITS(re, &s->gb, 1)) - SHOW_SBITS(re, &s->gb, 1);  // 0.0
/*64  */             SKIP_BITS(re, &s->gb, 1);                                                 // 0.0
/*66  */         } else {                                                                      // 0.0
/*68  */             /* escape */                                                              // 0.0
/*70  */             run = SHOW_UBITS(re, &s->gb, 6) + 1; LAST_SKIP_BITS(re, &s->gb, 6);       // 0.0
/*72  */             UPDATE_CACHE(re, &s->gb);                                                 // 0.0
/*74  */             level = SHOW_SBITS(re, &s->gb, 12); SKIP_BITS(re, &s->gb, 12);            // 0.0
/*78  */             i += run;                                                                 // 0.0
/*80  */             j  = scantable[i];                                                        // 0.0
/*82  */             if (level < 0) {                                                          // 0.0
/*84  */                 level = ((-level * 2 + 1) * qscale) >> 1;                             // 0.0
/*86  */                 level = -level;                                                       // 0.0
/*88  */             } else {                                                                  // 0.0
/*90  */                 level = ((level * 2 + 1) * qscale) >> 1;                              // 0.0
/*92  */             }                                                                         // 0.0
/*94  */         }                                                                             // 0.0
/*98  */         block[j] = level;                                                             // 0.0
/*100 */         if (((int32_t)GET_CACHE(re, &s->gb)) <= (int32_t)0xBFFFFFFF)                  // 0.0
/*102 */             break;                                                                    // 0.0
/*104 */         UPDATE_CACHE(re, &s->gb);                                                     // 0.0
/*106 */     }                                                                                 // 0.0
/*108 */ end:                                                                                  // 0.0
/*110 */     LAST_SKIP_BITS(re, &s->gb, 2);                                                    // 0.0
/*112 */     CLOSE_READER(re, &s->gb);                                                         // 0.0
/*114 */     s->block_last_index[n] = i;                                                       // 0.0
/*116 */     return 0;                                                                         // 0.0
/*118 */ }                                                                                     // 0.0
