// commit message FFmpeg@c61b28e042 (target=0, prob=0.43576333, correct=True): avcodec/atrac3: Add multichannel joint stereo ATRAC3
/*0   */ static int decode_frame(AVCodecContext *avctx, const uint8_t *databuf,                      // (9) 0.04688
/*2   */                         float **out_samples)                                                // (7) 0.05859
/*4   */ {                                                                                           // (20) 0.001953
/*6   */     ATRAC3Context *q = avctx->priv_data;                                                    // (13) 0.03516
/*8   */     int ret, i;                                                                             // (19) 0.01562
/*10  */     uint8_t *ptr1;                                                                          // (18) 0.02148
/*14  */     if (q->coding_mode == JOINT_STEREO) {                                                   // (12) 0.03711
/*16  */         /* channel coupling mode */                                                         // (17) 0.02344
/*18  */         /* decode Sound Unit 1 */                                                           // (15) 0.02539
/*20  */         init_get_bits(&q->gb, databuf, avctx->block_align * 8);                             // (6) 0.05859
/*24  */         ret = decode_channel_sound_unit(q, &q->gb, q->units, out_samples[0], 0,             // (2) 0.07227
/*26  */                                         JOINT_STEREO);                                      // (0) 0.08789
/*28  */         if (ret != 0)                                                                       // (16) 0.02539
/*30  */             return ret;                                                                     // (14) 0.02734
/*34  */         /* Framedata of the su2 in the joint-stereo mode is encoded in                      // (8) 0.04883
/*36  */          * reverse byte order so we need to swap it first. */                               // (11) 0.04102
/*38  */         if (databuf == q->decoded_bytes_buffer) {                                           // (10) 0.04492
/*40  */             uint8_t *ptr2 = q->decoded_bytes_buffer + avctx->block_align - 1;               // (3) 0.07227
/*42  */             ptr1          = q->decoded_bytes_buffer;                                        // (5) 0.0625
/*44  */             for (i = 0; i < avctx->block_align / 2; i++, ptr1++, ptr2--)                    // (1) 0.07617
/*46  */                 FFSWAP(uint8_t, *ptr1, *ptr2);                                              // (4) 0.06445
/*48  */         } else {                                                                            // 0.0
/*50  */             const uint8_t *ptr2 = databuf + avctx->block_align - 1;                         // 0.0
/*52  */             for (i = 0; i < avctx->block_align; i++)                                        // 0.0
/*54  */                 q->decoded_bytes_buffer[i] = *ptr2--;                                       // 0.0
/*56  */         }                                                                                   // 0.0
/*60  */         /* Skip the sync codes (0xF8). */                                                   // 0.0
/*62  */         ptr1 = q->decoded_bytes_buffer;                                                     // 0.0
/*64  */         for (i = 4; *ptr1 == 0xF8; i++, ptr1++) {                                           // 0.0
/*66  */             if (i >= avctx->block_align)                                                    // 0.0
/*68  */                 return AVERROR_INVALIDDATA;                                                 // 0.0
/*70  */         }                                                                                   // 0.0
/*76  */         /* set the bitstream reader at the start of the second Sound Unit*/                 // 0.0
/*78  */         init_get_bits8(&q->gb, ptr1, q->decoded_bytes_buffer + avctx->block_align - ptr1);  // 0.0
/*82  */         /* Fill the Weighting coeffs delay buffer */                                        // 0.0
/*84  */         memmove(q->weighting_delay, &q->weighting_delay[2],                                 // 0.0
/*86  */                 4 * sizeof(*q->weighting_delay));                                           // 0.0
/*88  */         q->weighting_delay[4] = get_bits1(&q->gb);                                          // 0.0
/*90  */         q->weighting_delay[5] = get_bits(&q->gb, 3);                                        // 0.0
/*94  */         for (i = 0; i < 4; i++) {                                                           // 0.0
/*96  */             q->matrix_coeff_index_prev[i] = q->matrix_coeff_index_now[i];                   // 0.0
/*98  */             q->matrix_coeff_index_now[i]  = q->matrix_coeff_index_next[i];                  // 0.0
/*100 */             q->matrix_coeff_index_next[i] = get_bits(&q->gb, 2);                            // 0.0
/*102 */         }                                                                                   // 0.0
/*106 */         /* Decode Sound Unit 2. */                                                          // 0.0
/*108 */         ret = decode_channel_sound_unit(q, &q->gb, &q->units[1],                            // 0.0
/*110 */                                         out_samples[1], 1, JOINT_STEREO);                   // 0.0
/*112 */         if (ret != 0)                                                                       // 0.0
/*114 */             return ret;                                                                     // 0.0
/*118 */         /* Reconstruct the channel coefficients. */                                         // 0.0
/*120 */         reverse_matrixing(out_samples[0], out_samples[1],                                   // 0.0
/*122 */                           q->matrix_coeff_index_prev,                                       // 0.0
/*124 */                           q->matrix_coeff_index_now);                                       // 0.0
/*128 */         channel_weighting(out_samples[0], out_samples[1], q->weighting_delay);              // 0.0
/*130 */     } else {                                                                                // 0.0
/*132 */         /* single channels */                                                               // 0.0
/*134 */         /* Decode the channel sound units. */                                               // 0.0
/*136 */         for (i = 0; i < avctx->channels; i++) {                                             // 0.0
/*138 */             /* Set the bitstream reader at the start of a channel sound unit. */            // 0.0
/*140 */             init_get_bits(&q->gb,                                                           // 0.0
/*142 */                           databuf + i * avctx->block_align / avctx->channels,               // 0.0
/*144 */                           avctx->block_align * 8 / avctx->channels);                        // 0.0
/*148 */             ret = decode_channel_sound_unit(q, &q->gb, &q->units[i],                        // 0.0
/*150 */                                             out_samples[i], i, q->coding_mode);             // 0.0
/*152 */             if (ret != 0)                                                                   // 0.0
/*154 */                 return ret;                                                                 // 0.0
/*156 */         }                                                                                   // 0.0
/*158 */     }                                                                                       // 0.0
/*162 */     /* Apply the iQMF synthesis filter. */                                                  // 0.0
/*164 */     for (i = 0; i < avctx->channels; i++) {                                                 // 0.0
/*166 */         float *p1 = out_samples[i];                                                         // 0.0
/*168 */         float *p2 = p1 + 256;                                                               // 0.0
/*170 */         float *p3 = p2 + 256;                                                               // 0.0
/*172 */         float *p4 = p3 + 256;                                                               // 0.0
/*174 */         ff_atrac_iqmf(p1, p2, 256, p1, q->units[i].delay_buf1, q->temp_buf);                // 0.0
/*176 */         ff_atrac_iqmf(p4, p3, 256, p3, q->units[i].delay_buf2, q->temp_buf);                // 0.0
/*178 */         ff_atrac_iqmf(p1, p3, 512, p1, q->units[i].delay_buf3, q->temp_buf);                // 0.0
/*180 */     }                                                                                       // 0.0
/*184 */     return 0;                                                                               // 0.0
/*186 */ }                                                                                           // 0.0
