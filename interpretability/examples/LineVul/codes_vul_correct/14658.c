// commit message FFmpeg@b12d92efd6 (target=1, prob=0.5089356, correct=True): avoid "0xFF << 24" as it is considered a integer overflow in C99
/*0  */ static av_cold int rl2_decode_init(AVCodecContext *avctx)                    // (9) 0.04297
/*2  */ {                                                                            // (27) 0.001954
/*4  */     Rl2Context *s = avctx->priv_data;                                        // (13) 0.0332
/*6  */     int back_size;                                                           // (22) 0.01562
/*8  */     int i;                                                                   // (24) 0.01172
/*10 */     s->avctx = avctx;                                                        // (16) 0.02148
/*12 */     avctx->pix_fmt = AV_PIX_FMT_PAL8;                                        // (5) 0.04687
/*14 */     avcodec_get_frame_defaults(&s->frame);                                   // (12) 0.03516
/*18 */     /** parse extra data */                                                  // (21) 0.01562
/*20 */     if(!avctx->extradata || avctx->extradata_size < EXTRADATA1_SIZE){        // (1) 0.05859
/*22 */         av_log(avctx, AV_LOG_ERROR, "invalid extradata size\n");             // (3) 0.05664
/*24 */         return -1;                                                           // (18) 0.02148
/*26 */     }                                                                        // (25) 0.007812
/*30 */     /** get frame_offset */                                                  // (20) 0.01758
/*32 */     s->video_base = AV_RL16(&avctx->extradata[0]);                           // (8) 0.04492
/*34 */     s->clr_count = AV_RL32(&avctx->extradata[2]);                            // (6) 0.04687
/*38 */     if(s->video_base >= avctx->width * avctx->height){                       // (11) 0.04102
/*40 */         av_log(avctx, AV_LOG_ERROR, "invalid video_base\n");                 // (4) 0.05664
/*42 */         return -1;                                                           // (17) 0.02148
/*44 */     }                                                                        // (26) 0.007812
/*48 */     /** initialize palette */                                                // (23) 0.01367
/*50 */     for(i=0;i<AVPALETTE_COUNT;i++)                                           // (10) 0.04297
/*52 */         s->palette[i] = 0xFF << 24 | AV_RB24(&avctx->extradata[6 + i * 3]);  // (0) 0.07617
/*56 */     /** decode background frame if present */                                // (19) 0.01953
/*58 */     back_size = avctx->extradata_size - EXTRADATA1_SIZE;                     // (7) 0.04687
/*62 */     if(back_size > 0){                                                       // (15) 0.02148
/*64 */         unsigned char* back_frame = av_mallocz(avctx->width*avctx->height);  // (2) 0.05859
/*66 */         if(!back_frame)                                                      // (14) 0.02734
/*68 */             return -1;                                                       // 0.0
/*70 */         rl2_rle_decode(s,avctx->extradata + EXTRADATA1_SIZE,back_size,       // 0.0
/*72 */                            back_frame,avctx->width,0);                       // 0.0
/*74 */         s->back_frame = back_frame;                                          // 0.0
/*76 */     }                                                                        // 0.0
/*78 */     return 0;                                                                // 0.0
/*80 */ }                                                                            // 0.0
