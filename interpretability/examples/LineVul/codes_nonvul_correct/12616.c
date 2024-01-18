// commit message FFmpeg@f21cf2b383 (target=0, prob=0.44208485, correct=True): vc2enc: remove useless alignment on slice encoding
/*0  */ static int encode_hq_slice(AVCodecContext *avctx, void *arg)                                  // (5) 0.04102
/*2  */ {                                                                                             // (24) 0.001953
/*4  */     SliceArgs *slice_dat = arg;                                                               // (21) 0.02539
/*6  */     VC2EncContext *s = slice_dat->ctx;                                                        // (14) 0.03125
/*8  */     PutBitContext *pb = &slice_dat->pb;                                                       // (16) 0.03125
/*10 */     const int slice_x = slice_dat->x;                                                         // (19) 0.0293
/*12 */     const int slice_y = slice_dat->y;                                                         // (18) 0.0293
/*14 */     const int quant_idx = slice_dat->quant_idx;                                               // (10) 0.03711
/*16 */     const int slice_bytes_max = slice_dat->bytes;                                             // (11) 0.0332
/*18 */     uint8_t quants[MAX_DWT_LEVELS][4];                                                        // (6) 0.04102
/*20 */     int p, level, orientation;                                                                // (23) 0.01953
/*24 */     avpriv_align_put_bits(pb);                                                                // (20) 0.02734
/*26 */     skip_put_bytes(pb, s->prefix_bytes);                                                      // (12) 0.0332
/*28 */     put_bits(pb, 8, quant_idx);                                                               // (17) 0.03125
/*32 */     /* Slice quantization (slice_quantizers() in the specs) */                                // (9) 0.03711
/*34 */     for (level = 0; level < s->wavelet_depth; level++)                                        // (8) 0.03906
/*36 */         for (orientation = !!level; orientation < 4; orientation++)                           // (7) 0.04102
/*38 */             quants[level][orientation] = FFMAX(quant_idx - s->quant[level][orientation], 0);  // (0) 0.07617
/*42 */     /* Luma + 2 Chroma planes */                                                              // (22) 0.02344
/*44 */     for (p = 0; p < 3; p++) {                                                                 // (15) 0.03125
/*46 */         int bytes_start, bytes_len, pad_s, pad_c;                                             // (3) 0.04687
/*48 */         bytes_start = put_bits_count(pb) >> 3;                                                // (4) 0.04297
/*50 */         put_bits(pb, 8, 0);                                                                   // (13) 0.0332
/*52 */         for (level = 0; level < s->wavelet_depth; level++) {                                  // (2) 0.04883
/*54 */             for (orientation = !!level; orientation < 4; orientation++) {                     // (1) 0.05078
/*56 */                 encode_subband(s, pb, slice_x, slice_y,                                       // 0.0
/*58 */                                &s->plane[p].band[level][orientation],                         // 0.0
/*60 */                                quants[level][orientation]);                                   // 0.0
/*62 */             }                                                                                 // 0.0
/*64 */         }                                                                                     // 0.0
/*66 */         avpriv_align_put_bits(pb);                                                            // 0.0
/*68 */         bytes_len = (put_bits_count(pb) >> 3) - bytes_start - 1;                              // 0.0
/*70 */         if (p == 2) {                                                                         // 0.0
/*72 */             int len_diff = slice_bytes_max - (put_bits_count(pb) >> 3);                       // 0.0
/*74 */             pad_s = FFALIGN((bytes_len + len_diff), s->size_scaler)/s->size_scaler;           // 0.0
/*76 */             pad_c = (pad_s*s->size_scaler) - bytes_len;                                       // 0.0
/*78 */         } else {                                                                              // 0.0
/*80 */             pad_s = FFALIGN(bytes_len, s->size_scaler)/s->size_scaler;                        // 0.0
/*82 */             pad_c = (pad_s*s->size_scaler) - bytes_len;                                       // 0.0
/*84 */         }                                                                                     // 0.0
/*86 */         pb->buf[bytes_start] = pad_s;                                                         // 0.0
/*88 */         flush_put_bits(pb);                                                                   // 0.0
/*90 */         skip_put_bytes(pb, pad_c);                                                            // 0.0
/*92 */     }                                                                                         // 0.0
/*96 */     return 0;                                                                                 // 0.0
/*98 */ }                                                                                             // 0.0
