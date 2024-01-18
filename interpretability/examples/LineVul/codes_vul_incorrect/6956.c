// commit message FFmpeg@f6774f905f (target=1, prob=0.0972441, correct=False): mpegvideo: operate with pointers to AVFrames instead of whole structs
/*0   */ static int slice_end(AVCodecContext *avctx, AVFrame *pict)                // (9) 0.03711
/*2   */ {                                                                         // (24) 0.001953
/*4   */     Mpeg1Context *s1  = avctx->priv_data;                                 // (12) 0.03711
/*6   */     MpegEncContext *s = &s1->mpeg_enc_ctx;                                // (8) 0.03906
/*10  */     if (!s1->mpeg_enc_ctx_allocated || !s->current_picture_ptr)           // (6) 0.05078
/*12  */         return 0;                                                         // (20) 0.01953
/*16  */     if (s->avctx->hwaccel) {                                              // (15) 0.0293
/*18  */         if (s->avctx->hwaccel->end_frame(s->avctx) < 0)                   // (4) 0.05859
/*20  */             av_log(avctx, AV_LOG_ERROR,                                   // (7) 0.04688
/*22  */                    "hardware accelerator failed to decode picture\n");    // (5) 0.05664
/*24  */     }                                                                     // (23) 0.007812
/*28  */ #if FF_API_XVMC                                                           // (21) 0.01758
/*30  */ FF_DISABLE_DEPRECATION_WARNINGS                                           // (18) 0.02148
/*32  */     if (CONFIG_MPEG_XVMC_DECODER && s->avctx->xvmc_acceleration)          // (2) 0.0625
/*34  */         ff_xvmc_field_end(s);                                             // (10) 0.03711
/*36  */ FF_ENABLE_DEPRECATION_WARNINGS                                            // (17) 0.02148
/*38  */ #endif /* FF_API_XVMC */                                                  // (19) 0.02148
/*42  */     /* end of slice reached */                                            // (22) 0.01758
/*44  */     if (/* s->mb_y << field_pic == s->mb_height && */ !s->first_field) {  // (3) 0.06055
/*46  */         /* end of image */                                                // (16) 0.02344
/*50  */         ff_er_frame_end(&s->er);                                          // (11) 0.03711
/*54  */         ff_MPV_frame_end(s);                                              // (13) 0.03516
/*58  */         if (s->pict_type == AV_PICTURE_TYPE_B || s->low_delay) {          // (1) 0.0625
/*60  */             int ret = av_frame_ref(pict, &s->current_picture_ptr->f);     // (0) 0.06445
/*62  */             if (ret < 0)                                                  // (14) 0.0332
/*64  */                 return ret;                                               // 0.0
/*66  */             ff_print_debug_info(s, s->current_picture_ptr);               // 0.0
/*68  */         } else {                                                          // 0.0
/*70  */             if (avctx->active_thread_type & FF_THREAD_FRAME)              // 0.0
/*72  */                 s->picture_number++;                                      // 0.0
/*74  */             /* latency of 1 frame for I- and P-frames */                  // 0.0
/*76  */             /* XXX: use another variable than picture_number */           // 0.0
/*78  */             if (s->last_picture_ptr != NULL) {                            // 0.0
/*80  */                 int ret = av_frame_ref(pict, &s->last_picture_ptr->f);    // 0.0
/*82  */                 if (ret < 0)                                              // 0.0
/*84  */                     return ret;                                           // 0.0
/*86  */                 ff_print_debug_info(s, s->last_picture_ptr);              // 0.0
/*88  */             }                                                             // 0.0
/*90  */         }                                                                 // 0.0
/*94  */         return 1;                                                         // 0.0
/*96  */     } else {                                                              // 0.0
/*98  */         return 0;                                                         // 0.0
/*100 */     }                                                                     // 0.0
/*102 */ }                                                                         // 0.0
