// commit message FFmpeg@68f593b484 (target=0, prob=0.3325827, correct=True): GetBitContext.size is allways multiplied by 8 -> use size_in_bits to avoid useless *8 in a few inner loops
/*0   */ static int mpeg1_decode_sequence(AVCodecContext *avctx,                         // (7) 0.03906
/*2   */                                  UINT8 *buf, int buf_size)                      // (0) 0.08398
/*4   */ {                                                                               // (27) 0.001953
/*6   */     Mpeg1Context *s1 = avctx->priv_data;                                        // (12) 0.03516
/*8   */     MpegEncContext *s = &s1->mpeg_enc_ctx;                                      // (8) 0.03906
/*10  */     int width, height, i, v, j;                                                 // (17) 0.02734
/*12  */     float aspect;                                                               // (25) 0.01172
/*16  */     init_get_bits(&s->gb, buf, buf_size);                                       // (11) 0.03711
/*20  */     width = get_bits(&s->gb, 12);                                               // (15) 0.0293
/*22  */     height = get_bits(&s->gb, 12);                                              // (16) 0.0293
/*24  */     s->aspect_ratio_info= get_bits(&s->gb, 4);                                  // (3) 0.04492
/*26  */     if(!s->mpeg2){                                                              // (21) 0.02148
/*28  */         aspect= mpeg1_aspect[s->aspect_ratio_info];                             // (2) 0.05078
/*30  */         if(aspect!=0.0) avctx->aspect_ratio= width/(aspect*height);             // (1) 0.06445
/*32  */     }                                                                           // (26) 0.007812
/*36  */     s->frame_rate_index = get_bits(&s->gb, 4);                                  // (6) 0.04102
/*38  */     if (s->frame_rate_index == 0)                                               // (14) 0.0293
/*40  */         return -1;                                                              // (22) 0.02148
/*42  */     s->bit_rate = get_bits(&s->gb, 18) * 400;                                   // (5) 0.04297
/*44  */     if (get_bits1(&s->gb) == 0) /* marker */                                    // (10) 0.03906
/*46  */         return -1;                                                              // (23) 0.02148
/*48  */     if (width <= 0 || height <= 0 ||                                            // (19) 0.02539
/*50  */         (width % 2) != 0 || (height % 2) != 0)                                  // (4) 0.04492
/*52  */         return -1;                                                              // (24) 0.02148
/*54  */     if (width != s->width ||                                                    // (20) 0.02148
/*56  */         height != s->height) {                                                  // (18) 0.02734
/*58  */         /* start new mpeg1 context decoding */                                  // (13) 0.03125
/*60  */         s->out_format = FMT_MPEG1;                                              // (9) 0.03906
/*62  */         if (s1->mpeg_enc_ctx_allocated) {                                       // 0.0
/*64  */             MPV_common_end(s);                                                  // 0.0
/*66  */         }                                                                       // 0.0
/*68  */         s->width = width;                                                       // 0.0
/*70  */         s->height = height;                                                     // 0.0
/*72  */         avctx->has_b_frames= 1;                                                 // 0.0
/*74  */         s->avctx = avctx;                                                       // 0.0
/*76  */         avctx->width = width;                                                   // 0.0
/*78  */         avctx->height = height;                                                 // 0.0
/*80  */         if (s->frame_rate_index >= 9) {                                         // 0.0
/*82  */             /* at least give a valid frame rate (some old mpeg1 have this) */   // 0.0
/*84  */             avctx->frame_rate = 25 * FRAME_RATE_BASE;                           // 0.0
/*86  */         } else {                                                                // 0.0
/*88  */             avctx->frame_rate = frame_rate_tab[s->frame_rate_index];            // 0.0
/*90  */         }                                                                       // 0.0
/*92  */         s->frame_rate = avctx->frame_rate;                                      // 0.0
/*94  */         avctx->bit_rate = s->bit_rate;                                          // 0.0
/*96  */                                                                                 // 0.0
/*98  */         if (MPV_common_init(s) < 0)                                             // 0.0
/*100 */             return -1;                                                          // 0.0
/*102 */         s1->mpeg_enc_ctx_allocated = 1;                                         // 0.0
/*104 */     }                                                                           // 0.0
/*108 */     skip_bits(&s->gb, 10); /* vbv_buffer_size */                                // 0.0
/*110 */     skip_bits(&s->gb, 1);                                                       // 0.0
/*114 */     /* get matrix */                                                            // 0.0
/*116 */     if (get_bits1(&s->gb)) {                                                    // 0.0
/*118 */         for(i=0;i<64;i++) {                                                     // 0.0
/*120 */             v = get_bits(&s->gb, 8);                                            // 0.0
/*122 */             j = s->intra_scantable.permutated[i];                               // 0.0
/*124 */             s->intra_matrix[j] = v;                                             // 0.0
/*126 */             s->chroma_intra_matrix[j] = v;                                      // 0.0
/*128 */         }                                                                       // 0.0
/*130 */ #ifdef DEBUG                                                                    // 0.0
/*132 */         dprintf("intra matrix present\n");                                      // 0.0
/*134 */         for(i=0;i<64;i++)                                                       // 0.0
/*136 */             dprintf(" %d", s->intra_matrix[s->intra_scantable.permutated[i]]);  // 0.0
/*138 */         printf("\n");                                                           // 0.0
/*140 */ #endif                                                                          // 0.0
/*142 */     } else {                                                                    // 0.0
/*144 */         for(i=0;i<64;i++) {                                                     // 0.0
/*146 */             int j= s->idct_permutation[i];                                      // 0.0
/*148 */             v = ff_mpeg1_default_intra_matrix[i];                               // 0.0
/*150 */             s->intra_matrix[j] = v;                                             // 0.0
/*152 */             s->chroma_intra_matrix[j] = v;                                      // 0.0
/*154 */         }                                                                       // 0.0
/*156 */     }                                                                           // 0.0
/*158 */     if (get_bits1(&s->gb)) {                                                    // 0.0
/*160 */         for(i=0;i<64;i++) {                                                     // 0.0
/*162 */             v = get_bits(&s->gb, 8);                                            // 0.0
/*164 */             j = s->intra_scantable.permutated[i];                               // 0.0
/*166 */             s->inter_matrix[j] = v;                                             // 0.0
/*168 */             s->chroma_inter_matrix[j] = v;                                      // 0.0
/*170 */         }                                                                       // 0.0
/*172 */ #ifdef DEBUG                                                                    // 0.0
/*174 */         dprintf("non intra matrix present\n");                                  // 0.0
/*176 */         for(i=0;i<64;i++)                                                       // 0.0
/*178 */             dprintf(" %d", s->inter_matrix[s->intra_scantable.permutated[i]]);  // 0.0
/*180 */         printf("\n");                                                           // 0.0
/*182 */ #endif                                                                          // 0.0
/*184 */     } else {                                                                    // 0.0
/*186 */         for(i=0;i<64;i++) {                                                     // 0.0
/*188 */             int j= s->idct_permutation[i];                                      // 0.0
/*190 */             v = ff_mpeg1_default_non_intra_matrix[i];                           // 0.0
/*192 */             s->inter_matrix[j] = v;                                             // 0.0
/*194 */             s->chroma_inter_matrix[j] = v;                                      // 0.0
/*196 */         }                                                                       // 0.0
/*198 */     }                                                                           // 0.0
/*202 */     /* we set mpeg2 parameters so that it emulates mpeg1 */                     // 0.0
/*204 */     s->progressive_sequence = 1;                                                // 0.0
/*206 */     s->progressive_frame = 1;                                                   // 0.0
/*208 */     s->picture_structure = PICT_FRAME;                                          // 0.0
/*210 */     s->frame_pred_frame_dct = 1;                                                // 0.0
/*212 */     s->mpeg2 = 0;                                                               // 0.0
/*214 */     avctx->sub_id = 1; /* indicates mpeg1 */                                    // 0.0
/*216 */     return 0;                                                                   // 0.0
/*218 */ }                                                                               // 0.0
