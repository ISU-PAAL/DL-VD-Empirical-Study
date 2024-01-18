// commit message FFmpeg@d7e9533aa0 (target=1, prob=0.27967033, correct=False): fixed msmpeg4 infinite loop if buggy stream rewrote quantizer  fixed bias (+10% compression/quality for h263 like codecs)  qscale=1 support  mpeg1 intra frames looks far less blocky added codec_id field
/*0   */ static int mpeg1_decode_sequence(AVCodecContext *avctx,             // (5) 0.03906
/*2   */                                  UINT8 *buf, int buf_size)          // (0) 0.08398
/*4   */ {                                                                   // (28) 0.001953
/*6   */     Mpeg1Context *s1 = avctx->priv_data;                            // (11) 0.03516
/*8   */     MpegEncContext *s = &s1->mpeg_enc_ctx;                          // (7) 0.03906
/*10  */     int width, height, i, v, j;                                     // (16) 0.02734
/*12  */                                                                     // (27) 0.007812
/*14  */     init_get_bits(&s->gb, buf, buf_size);                           // (10) 0.03711
/*18  */     width = get_bits(&s->gb, 12);                                   // (13) 0.0293
/*20  */     height = get_bits(&s->gb, 12);                                  // (14) 0.0293
/*22  */     skip_bits(&s->gb, 4);                                           // (18) 0.02539
/*24  */     s->frame_rate_index = get_bits(&s->gb, 4);                      // (4) 0.04102
/*26  */     if (s->frame_rate_index == 0)                                   // (15) 0.0293
/*28  */         return -1;                                                  // (23) 0.02148
/*30  */     s->bit_rate = get_bits(&s->gb, 18) * 400;                       // (3) 0.04297
/*32  */     if (get_bits1(&s->gb) == 0) /* marker */                        // (9) 0.03906
/*34  */         return -1;                                                  // (24) 0.02148
/*36  */     if (width <= 0 || height <= 0 ||                                // (19) 0.02539
/*38  */         (width % 2) != 0 || (height % 2) != 0)                      // (1) 0.04492
/*40  */         return -1;                                                  // (25) 0.02148
/*42  */     if (width != s->width ||                                        // (22) 0.02148
/*44  */         height != s->height) {                                      // (17) 0.02734
/*46  */         /* start new mpeg1 context decoding */                      // (12) 0.03125
/*48  */         s->out_format = FMT_MPEG1;                                  // (8) 0.03906
/*50  */         if (s1->mpeg_enc_ctx_allocated) {                           // (2) 0.04297
/*52  */             MPV_common_end(s);                                      // (6) 0.03906
/*54  */         }                                                           // (26) 0.01562
/*56  */         s->width = width;                                           // (21) 0.02539
/*58  */         s->height = height;                                         // (20) 0.02539
/*60  */         s->has_b_frames = 1;                                        // 0.0
/*62  */         s->avctx = avctx;                                           // 0.0
/*64  */         avctx->width = width;                                       // 0.0
/*66  */         avctx->height = height;                                     // 0.0
/*68  */         avctx->frame_rate = frame_rate_tab[s->frame_rate_index];    // 0.0
/*70  */         s->frame_rate = avctx->frame_rate;                          // 0.0
/*72  */         avctx->bit_rate = s->bit_rate;                              // 0.0
/*74  */                                                                     // 0.0
/*76  */         if (MPV_common_init(s) < 0)                                 // 0.0
/*78  */             return -1;                                              // 0.0
/*80  */         mpeg1_init_vlc(s);                                          // 0.0
/*82  */         s1->mpeg_enc_ctx_allocated = 1;                             // 0.0
/*84  */     }                                                               // 0.0
/*88  */     skip_bits(&s->gb, 10); /* vbv_buffer_size */                    // 0.0
/*90  */     skip_bits(&s->gb, 1);                                           // 0.0
/*94  */     /* get matrix */                                                // 0.0
/*96  */     if (get_bits1(&s->gb)) {                                        // 0.0
/*98  */         for(i=0;i<64;i++) {                                         // 0.0
/*100 */             v = get_bits(&s->gb, 8);                                // 0.0
/*102 */             j = zigzag_direct[i];                                   // 0.0
/*104 */             s->intra_matrix[j] = v;                                 // 0.0
/*106 */             s->chroma_intra_matrix[j] = v;                          // 0.0
/*108 */         }                                                           // 0.0
/*110 */ #ifdef DEBUG                                                        // 0.0
/*112 */         dprintf("intra matrix present\n");                          // 0.0
/*114 */         for(i=0;i<64;i++)                                           // 0.0
/*116 */             dprintf(" %d", s->intra_matrix[zigzag_direct[i]]);      // 0.0
/*118 */         printf("\n");                                               // 0.0
/*120 */ #endif                                                              // 0.0
/*122 */     } else {                                                        // 0.0
/*124 */         for(i=0;i<64;i++) {                                         // 0.0
/*126 */             v = default_intra_matrix[i];                            // 0.0
/*128 */             s->intra_matrix[i] = v;                                 // 0.0
/*130 */             s->chroma_intra_matrix[i] = v;                          // 0.0
/*132 */         }                                                           // 0.0
/*134 */     }                                                               // 0.0
/*136 */     if (get_bits1(&s->gb)) {                                        // 0.0
/*138 */         for(i=0;i<64;i++) {                                         // 0.0
/*140 */             v = get_bits(&s->gb, 8);                                // 0.0
/*142 */             j = zigzag_direct[i];                                   // 0.0
/*144 */             s->non_intra_matrix[j] = v;                             // 0.0
/*146 */             s->chroma_non_intra_matrix[j] = v;                      // 0.0
/*148 */         }                                                           // 0.0
/*150 */ #ifdef DEBUG                                                        // 0.0
/*152 */         dprintf("non intra matrix present\n");                      // 0.0
/*154 */         for(i=0;i<64;i++)                                           // 0.0
/*156 */             dprintf(" %d", s->non_intra_matrix[zigzag_direct[i]]);  // 0.0
/*158 */         printf("\n");                                               // 0.0
/*160 */ #endif                                                              // 0.0
/*162 */     } else {                                                        // 0.0
/*164 */         for(i=0;i<64;i++) {                                         // 0.0
/*166 */             v = default_non_intra_matrix[i];                        // 0.0
/*168 */             s->non_intra_matrix[i] = v;                             // 0.0
/*170 */             s->chroma_non_intra_matrix[i] = v;                      // 0.0
/*172 */         }                                                           // 0.0
/*174 */     }                                                               // 0.0
/*178 */     /* we set mpeg2 parameters so that it emulates mpeg1 */         // 0.0
/*180 */     s->progressive_sequence = 1;                                    // 0.0
/*182 */     s->progressive_frame = 1;                                       // 0.0
/*184 */     s->picture_structure = PICT_FRAME;                              // 0.0
/*186 */     s->frame_pred_frame_dct = 1;                                    // 0.0
/*188 */     s->mpeg2 = 0;                                                   // 0.0
/*190 */     return 0;                                                       // 0.0
/*192 */ }                                                                   // 0.0
