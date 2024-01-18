// commit message FFmpeg@365ef88d5d (target=1, prob=0.6442697, correct=True): avcodec/wma: Print more details in case of spectral RLE overflows
/*0   */ int ff_wma_run_level_decode(AVCodecContext *avctx, GetBitContext *gb,         // (9) 0.05273
/*2   */                             VLC *vlc, const float *level_table,               // (3) 0.07812
/*4   */                             const uint16_t *run_table, int version,           // (2) 0.07813
/*6   */                             WMACoef *ptr, int offset, int num_coefs,          // (0) 0.08594
/*8   */                             int block_len, int frame_len_bits,                // (4) 0.07617
/*10  */                             int coef_nb_bits)                                 // (6) 0.06836
/*12  */ {                                                                             // (18) 0.001953
/*14  */     int code, level, sign;                                                    // (16) 0.01953
/*16  */     const uint32_t *ilvl = (const uint32_t *) level_table;                    // (10) 0.04492
/*18  */     uint32_t *iptr = (uint32_t *) ptr;                                        // (11) 0.03711
/*20  */     const unsigned int coef_mask = block_len - 1;                             // (13) 0.0332
/*22  */     for (; offset < num_coefs; offset++) {                                    // (12) 0.0332
/*24  */         code = get_vlc2(gb, vlc->table, VLCBITS, VLCMAX);                     // (8) 0.06055
/*26  */         if (code > 1) {                                                       // (15) 0.02734
/*28  */             /** normal code */                                                // (14) 0.0293
/*30  */             offset                  += run_table[code];                       // (5) 0.07031
/*32  */             sign                     = get_bits1(gb) - 1;                     // (1) 0.08398
/*34  */             iptr[offset & coef_mask] = ilvl[code] ^ sign << 31;               // (7) 0.0625
/*36  */         } else if (code == 1) {                                               // 0.0
/*38  */             /** EOB */                                                        // 0.0
/*40  */             break;                                                            // 0.0
/*42  */         } else {                                                              // 0.0
/*44  */             /** escape */                                                     // 0.0
/*46  */             if (!version) {                                                   // 0.0
/*48  */                 level = get_bits(gb, coef_nb_bits);                           // 0.0
/*50  */                 /** NOTE: this is rather suboptimal. reading                  // 0.0
/*52  */                  *  block_len_bits would be better */                         // 0.0
/*54  */                 offset += get_bits(gb, frame_len_bits);                       // 0.0
/*56  */             } else {                                                          // 0.0
/*58  */                 level = ff_wma_get_large_val(gb);                             // 0.0
/*60  */                 /** escape decode */                                          // 0.0
/*62  */                 if (get_bits1(gb)) {                                          // 0.0
/*64  */                     if (get_bits1(gb)) {                                      // 0.0
/*66  */                         if (get_bits1(gb)) {                                  // 0.0
/*68  */                             av_log(avctx, AV_LOG_ERROR,                       // 0.0
/*70  */                                    "broken escape sequence\n");               // 0.0
/*72  */                             return -1;                                        // 0.0
/*74  */                         } else                                                // 0.0
/*76  */                             offset += get_bits(gb, frame_len_bits) + 4;       // 0.0
/*78  */                     } else                                                    // 0.0
/*80  */                         offset += get_bits(gb, 2) + 1;                        // 0.0
/*82  */                 }                                                             // 0.0
/*84  */             }                                                                 // 0.0
/*86  */             sign                    = get_bits1(gb) - 1;                      // 0.0
/*88  */             ptr[offset & coef_mask] = (level ^ sign) - sign;                  // 0.0
/*90  */         }                                                                     // (17) 0.01562
/*92  */     }                                                                         // 0.0
/*94  */     /** NOTE: EOB can be omitted */                                           // 0.0
/*96  */     if (offset > num_coefs) {                                                 // 0.0
/*98  */         av_log(avctx, AV_LOG_ERROR, "overflow in spectral RLE, ignoring\n");  // 0.0
/*100 */         return -1;                                                            // 0.0
/*102 */     }                                                                         // 0.0
/*106 */     return 0;                                                                 // 0.0
/*108 */ }                                                                             // 0.0
