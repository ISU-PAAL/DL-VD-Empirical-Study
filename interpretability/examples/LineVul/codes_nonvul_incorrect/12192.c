// commit message FFmpeg@0065d2d520 (target=0, prob=0.6954919, correct=False): vp9: fix mt-related hang a parser infinite loop.
/*0   */ static int parse(AVCodecParserContext *ctx,                                     // (18) 0.0236
/*2   */                  AVCodecContext *avctx,                                         // (6) 0.04691
/*4   */                  const uint8_t **out_data, int *out_size,                       // (3) 0.06246
/*6   */                  const uint8_t *data, int size)                                 // (5) 0.05271
/*8   */ {                                                                               // (25) 0.001956
/*10  */     VP9ParseContext *s = ctx->priv_data;                                        // (10) 0.03517
/*12  */     int marker;                                                                 // (22) 0.01171
/*16  */     if (size <= 0) {                                                            // (20) 0.01952
/*18  */         *out_size = 0;                                                          // (17) 0.02733
/*20  */         *out_data = data;                                                       // (16) 0.02733
/*24  */         return 0;                                                               // (21) 0.01952
/*26  */     }                                                                           // (23) 0.00781
/*30  */     if (s->n_frames > 0) {                                                      // (14) 0.02734
/*32  */         *out_data = data;                                                       // (15) 0.02733
/*34  */         *out_size = s->size[--s->n_frames];                                     // (9) 0.0449
/*36  */         parse_frame(ctx, *out_data, *out_size);                                 // (8) 0.04497
/*40  */         return s->n_frames > 0 ? *out_size : size /* i.e. include idx tail */;  // (1) 0.06442
/*42  */     }                                                                           // (24) 0.007808
/*46  */     marker = data[size - 1];                                                    // (19) 0.02147
/*48  */     if ((marker & 0xe0) == 0xc0) {                                              // (11) 0.03514
/*50  */         int nbytes = 1 + ((marker >> 3) & 0x3);                                 // (7) 0.04685
/*52  */         int n_frames = 1 + (marker & 0x7), idx_sz = 2 + n_frames * nbytes;      // (0) 0.07222
/*56  */         if (size >= idx_sz && data[size - idx_sz] == marker) {                  // (4) 0.06051
/*58  */             const uint8_t *idx = data + size + 1 - idx_sz;                      // (2) 0.06247
/*60  */             int first = 1;                                                      // (13) 0.03132
/*64  */             switch (nbytes) {                                                   // (12) 0.03319
/*66  */ #define case_n(a, rd) \                                                         // 0.0
/*68  */             case a: \                                                           // 0.0
/*70  */                 while (n_frames--) { \                                          // 0.0
/*72  */                     int sz = rd; \                                              // 0.0
/*74  */                     idx += a; \                                                 // 0.0
/*76  */                     if (sz > size) { \                                          // 0.0
/*78  */                         s->n_frames = 0; \                                      // 0.0
/*80  */                         av_log(avctx, AV_LOG_ERROR, \                           // 0.0
/*82  */                                "Superframe packet size too big: %d > %d\n", \   // 0.0
/*84  */                                sz, size); \                                     // 0.0
/*86  */                         return AVERROR_INVALIDDATA; \                           // 0.0
/*88  */                     } \                                                         // 0.0
/*90  */                     if (first) { \                                              // 0.0
/*92  */                         first = 0; \                                            // 0.0
/*94  */                         *out_data = data; \                                     // 0.0
/*96  */                         *out_size = sz; \                                       // 0.0
/*98  */                         s->n_frames = n_frames; \                               // 0.0
/*100 */                     } else { \                                                  // 0.0
/*102 */                         s->size[n_frames] = sz; \                               // 0.0
/*104 */                     } \                                                         // 0.0
/*106 */                     data += sz; \                                               // 0.0
/*108 */                     size -= sz; \                                               // 0.0
/*110 */                 } \                                                             // 0.0
/*112 */                 parse_frame(ctx, *out_data, *out_size); \                       // 0.0
/*114 */                 return *out_size                                                // 0.0
/*118 */                 case_n(1, *idx);                                                // 0.0
/*120 */                 case_n(2, AV_RL16(idx));                                        // 0.0
/*122 */                 case_n(3, AV_RL24(idx));                                        // 0.0
/*124 */                 case_n(4, AV_RL32(idx));                                        // 0.0
/*126 */             }                                                                   // 0.0
/*128 */         }                                                                       // 0.0
/*130 */     }                                                                           // 0.0
/*134 */     *out_data = data;                                                           // 0.0
/*136 */     *out_size = size;                                                           // 0.0
/*138 */     parse_frame(ctx, data, size);                                               // 0.0
/*142 */     return size;                                                                // 0.0
/*144 */ }                                                                               // 0.0
