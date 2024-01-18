// commit message FFmpeg@8370e426e4 (target=1, prob=0.34555075, correct=False): vp3: fix oob read for negative tokens and memleaks on error.
/*0  */ static av_cold int vp3_decode_end(AVCodecContext *avctx)                      // (5) 0.04297
/*2  */ {                                                                             // (28) 0.001953
/*4  */     Vp3DecodeContext *s = avctx->priv_data;                                   // (9) 0.03711
/*6  */     int i;                                                                    // (26) 0.01172
/*10 */     if (avctx->is_copy && !s->current_frame.data[0])                          // (0) 0.04492
/*12 */         return 0;                                                             // (24) 0.01953
/*16 */     av_free(s->superblock_coding);                                            // (22) 0.0293
/*18 */     av_free(s->all_fragments);                                                // (23) 0.0293
/*20 */     av_free(s->coded_fragment_list[0]);                                       // (10) 0.03711
/*22 */     av_free(s->dct_tokens_base);                                              // (11) 0.03516
/*24 */     av_free(s->superblock_fragments);                                         // (18) 0.03125
/*26 */     av_free(s->macroblock_coding);                                            // (17) 0.03125
/*28 */     av_free(s->motion_val[0]);                                                // (19) 0.0293
/*30 */     av_free(s->motion_val[1]);                                                // (20) 0.0293
/*32 */     av_free(s->edge_emu_buffer);                                              // (15) 0.03125
/*36 */     if (avctx->is_copy) return 0;                                             // (21) 0.0293
/*40 */     for (i = 0; i < 16; i++) {                                                // (16) 0.03125
/*42 */         free_vlc(&s->dc_vlc[i]);                                              // (7) 0.04102
/*44 */         free_vlc(&s->ac_vlc_1[i]);                                            // (3) 0.04492
/*46 */         free_vlc(&s->ac_vlc_2[i]);                                            // (4) 0.04492
/*48 */         free_vlc(&s->ac_vlc_3[i]);                                            // (2) 0.04492
/*50 */         free_vlc(&s->ac_vlc_4[i]);                                            // (1) 0.04492
/*52 */     }                                                                         // (27) 0.007812
/*56 */     free_vlc(&s->superblock_run_length_vlc);                                  // (8) 0.03906
/*58 */     free_vlc(&s->fragment_run_length_vlc);                                    // (6) 0.04102
/*60 */     free_vlc(&s->mode_code_vlc);                                              // (13) 0.0332
/*62 */     free_vlc(&s->motion_vector_vlc);                                          // (12) 0.0332
/*66 */     /* release all frames */                                                  // (25) 0.01562
/*68 */     if (s->golden_frame.data[0])                                              // (14) 0.03125
/*70 */         ff_thread_release_buffer(avctx, &s->golden_frame);                    // 0.0
/*72 */     if (s->last_frame.data[0] && s->last_frame.type != FF_BUFFER_TYPE_COPY)   // 0.0
/*74 */         ff_thread_release_buffer(avctx, &s->last_frame);                      // 0.0
/*76 */     /* no need to release the current_frame since it will always be pointing  // 0.0
/*78 */      * to the same frame as either the golden or last frame */                // 0.0
/*82 */     return 0;                                                                 // 0.0
/*84 */ }                                                                             // 0.0
