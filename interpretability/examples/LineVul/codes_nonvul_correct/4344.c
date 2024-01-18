// commit message FFmpeg@43a4cb070b (target=0, prob=0.38104093, correct=True): alacenc: remove unneeded frame_size check in alac_encode_frame()
/*0  */ static int alac_encode_frame(AVCodecContext *avctx, uint8_t *frame,  // (4) 0.04883
/*2  */                              int buf_size, void *data)               // (0) 0.07226
/*4  */ {                                                                    // (28) 0.001953
/*6  */     AlacEncodeContext *s = avctx->priv_data;                         // (10) 0.03516
/*8  */     PutBitContext *pb = &s->pbctx;                                   // (17) 0.0293
/*10 */     int i, out_bytes, verbatim_flag = 0;                             // (9) 0.03516
/*14 */     if (avctx->frame_size > DEFAULT_FRAME_SIZE) {                    // (8) 0.04102
/*16 */         av_log(avctx, AV_LOG_ERROR, "input frame size exceeded\n");  // (3) 0.05469
/*18 */         return -1;                                                   // (21) 0.02148
/*20 */     }                                                                // (26) 0.007812
/*24 */     if (buf_size < 2 * s->max_coded_frame_size) {                    // (6) 0.04297
/*26 */         av_log(avctx, AV_LOG_ERROR, "buffer size is too small\n");   // (2) 0.05664
/*28 */         return -1;                                                   // (20) 0.02148
/*30 */     }                                                                // (25) 0.007813
/*34 */ verbatim:                                                            // (24) 0.007814
/*36 */     init_put_bits(pb, frame, buf_size);                              // (13) 0.0332
/*40 */     if (s->compression_level == 0 || verbatim_flag) {                // (7) 0.04102
/*42 */         // Verbatim mode                                             // (19) 0.02344
/*44 */         const int16_t *samples = data;                               // (11) 0.03516
/*46 */         write_frame_header(s, 1);                                    // (15) 0.0332
/*48 */         for (i = 0; i < avctx->frame_size * avctx->channels; i++) {  // (1) 0.06055
/*50 */             put_sbits(pb, 16, *samples++);                           // (5) 0.04883
/*52 */         }                                                            // (22) 0.01562
/*54 */     } else {                                                         // (23) 0.01172
/*56 */         init_sample_buffers(s, data);                                // (12) 0.03516
/*58 */         write_frame_header(s, 0);                                    // (14) 0.0332
/*60 */         write_compressed_frame(s);                                   // (16) 0.03125
/*62 */     }                                                                // (27) 0.007812
/*66 */     put_bits(pb, 3, 7);                                              // (18) 0.02539
/*68 */     flush_put_bits(pb);                                              // 0.0
/*70 */     out_bytes = put_bits_count(pb) >> 3;                             // 0.0
/*74 */     if (out_bytes > s->max_coded_frame_size) {                       // 0.0
/*76 */         /* frame too large. use verbatim mode */                     // 0.0
/*78 */         if (verbatim_flag || s->compression_level == 0) {            // 0.0
/*80 */             /* still too large. must be an error. */                 // 0.0
/*82 */             av_log(avctx, AV_LOG_ERROR, "error encoding frame\n");   // 0.0
/*84 */             return -1;                                               // 0.0
/*86 */         }                                                            // 0.0
/*88 */         verbatim_flag = 1;                                           // 0.0
/*90 */         goto verbatim;                                               // 0.0
/*92 */     }                                                                // 0.0
/*96 */     return out_bytes;                                                // 0.0
/*98 */ }                                                                    // 0.0
