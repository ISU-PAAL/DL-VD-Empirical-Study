// commit message FFmpeg@d094052c8e (target=1, prob=0.9991405, correct=True): fix a crash in SVQ1 with cmp!=sad
/*0  */ static av_cold int svq1_encode_init(AVCodecContext *avctx)                                   // (9) 0.04472
/*2  */ {                                                                                            // (19) 0.002033
/*4  */     SVQ1Context * const s = avctx->priv_data;                                                // (12) 0.03659
/*8  */     dsputil_init(&s->dsp, avctx);                                                            // (13) 0.03659
/*10 */     avctx->coded_frame= (AVFrame*)&s->picture;                                               // (11) 0.03862
/*14 */     s->frame_width = avctx->width;                                                           // (14) 0.02846
/*16 */     s->frame_height = avctx->height;                                                         // (15) 0.02846
/*20 */     s->y_block_width = (s->frame_width + 15) / 16;                                           // (7) 0.04675
/*22 */     s->y_block_height = (s->frame_height + 15) / 16;                                         // (8) 0.04675
/*26 */     s->c_block_width = (s->frame_width / 4 + 15) / 16;                                       // (5) 0.05081
/*28 */     s->c_block_height = (s->frame_height / 4 + 15) / 16;                                     // (6) 0.05081
/*32 */     s->avctx= avctx;                                                                         // (17) 0.02236
/*34 */     s->m.avctx= avctx;                                                                       // (16) 0.02642
/*37 */     s->m.me.scratchpad= av_mallocz((avctx->width+64)*2*16*2*sizeof(uint8_t));                // (2) 0.0813
/*39 */     s->m.me.map       = av_mallocz(ME_MAP_SIZE*sizeof(uint32_t));                            // (3) 0.0752
/*41 */     s->m.me.score_map = av_mallocz(ME_MAP_SIZE*sizeof(uint32_t));                            // (4) 0.06707
/*43 */     s->mb_type        = av_mallocz((s->y_block_width+1)*s->y_block_height*sizeof(int16_t));  // (1) 0.09756
/*45 */     s->dummy          = av_mallocz((s->y_block_width+1)*s->y_block_height*sizeof(int32_t));  // (0) 0.09959
/*47 */     h263_encode_init(&s->m); //mv_penalty                                                    // (10) 0.04268
/*51 */     return 0;                                                                                // (18) 0.0122
/*53 */ }                                                                                            // (20) 0.002033
