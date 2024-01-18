// commit message FFmpeg@155ec6edf8 (target=0, prob=0.21567714, correct=True): quad tree based motion compensation (currently only 16x16 & 8x8 OBMC blocks, but can be extended to other block sizes easily) different intra block coding (previous was just an ugly hack) 1.8% bitrate reduction -0.01PSNR (foreman@352x288 qscale=8) 1.5% bitrate reduction +0.05PSNR (foreman@352x288 qscale=1)
/*0   */ void ff_init_me(MpegEncContext *s){                                                                                                                // (13) 0.02734
/*2   */     MotionEstContext * const c= &s->me;                                                                                                            // (12) 0.0293
/*4   */     c->avctx= s->avctx;                                                                                                                            // (15) 0.02539
/*8   */     ff_set_cmp(&s->dsp, s->dsp.me_pre_cmp, c->avctx->me_pre_cmp);                                                                                  // (5) 0.07031
/*10  */     ff_set_cmp(&s->dsp, s->dsp.me_cmp, c->avctx->me_cmp);                                                                                          // (8) 0.0625
/*12  */     ff_set_cmp(&s->dsp, s->dsp.me_sub_cmp, c->avctx->me_sub_cmp);                                                                                  // (6) 0.07031
/*14  */     ff_set_cmp(&s->dsp, s->dsp.mb_cmp, c->avctx->mb_cmp);                                                                                          // (7) 0.0625
/*16  */                                                                                                                                                    // (17) 0.007812
/*18  */     c->flags    = get_flags(c, 0, c->avctx->me_cmp    &FF_CMP_CHROMA);                                                                             // (2) 0.07617
/*20  */     c->sub_flags= get_flags(c, 0, c->avctx->me_sub_cmp&FF_CMP_CHROMA);                                                                             // (4) 0.07227
/*22  */     c->mb_flags = get_flags(c, 0, c->avctx->mb_cmp    &FF_CMP_CHROMA);                                                                             // (3) 0.07422
/*26  */ /*FIXME s->no_rounding b_type*/                                                                                                                    // (14) 0.02539
/*28  */     if(s->flags&CODEC_FLAG_QPEL){                                                                                                                  // (11) 0.03711
/*30  */         c->sub_motion_search= qpel_motion_search;                                                                                                  // (10) 0.04297
/*32  */         c->qpel_avg= s->dsp.avg_qpel_pixels_tab;                                                                                                   // (9) 0.06055
/*34  */         if(s->no_rounding) c->qpel_put= s->dsp.put_no_rnd_qpel_pixels_tab;                                                                         // (1) 0.08398
/*36  */         else               c->qpel_put= s->dsp.put_qpel_pixels_tab;                                                                                // (0) 0.08594
/*38  */     }else{                                                                                                                                         // (16) 0.01172
/*40  */         if(c->avctx->me_sub_cmp&FF_CMP_CHROMA)                                                                                                     // 0.0
/*42  */             c->sub_motion_search= hpel_motion_search;                                                                                              // 0.0
/*44  */         else if(   c->avctx->me_sub_cmp == FF_CMP_SAD                                                                                              // 0.0
/*46  */                 && c->avctx->    me_cmp == FF_CMP_SAD                                                                                              // 0.0
/*48  */                 && c->avctx->    mb_cmp == FF_CMP_SAD)                                                                                             // 0.0
/*50  */             c->sub_motion_search= sad_hpel_motion_search; // 2050 vs. 2450 cycles                                                                  // 0.0
/*52  */         else                                                                                                                                       // 0.0
/*54  */             c->sub_motion_search= hpel_motion_search;                                                                                              // 0.0
/*56  */     }                                                                                                                                              // 0.0
/*58  */     c->hpel_avg= s->dsp.avg_pixels_tab;                                                                                                            // 0.0
/*60  */     if(s->no_rounding) c->hpel_put= s->dsp.put_no_rnd_pixels_tab;                                                                                  // 0.0
/*62  */     else               c->hpel_put= s->dsp.put_pixels_tab;                                                                                         // 0.0
/*66  */     if(s->linesize){                                                                                                                               // 0.0
/*68  */         c->stride  = s->linesize;                                                                                                                  // 0.0
/*70  */         c->uvstride= s->uvlinesize;                                                                                                                // 0.0
/*72  */     }else{                                                                                                                                         // 0.0
/*74  */         c->stride  = 16*s->mb_width + 32;                                                                                                          // 0.0
/*76  */         c->uvstride=  8*s->mb_width + 16;                                                                                                          // 0.0
/*78  */     }                                                                                                                                              // 0.0
/*82  */     // 8x8 fullpel search would need a 4x4 chroma compare, which we dont have yet, and even if we had the motion estimation code doesnt expect it  // 0.0
/*84  */     if((c->avctx->me_cmp&FF_CMP_CHROMA) && !s->dsp.me_cmp[2]){                                                                                     // 0.0
/*86  */         s->dsp.me_cmp[2]= zero_cmp;                                                                                                                // 0.0
/*88  */     }                                                                                                                                              // 0.0
/*90  */     if((c->avctx->me_sub_cmp&FF_CMP_CHROMA) && !s->dsp.me_sub_cmp[2]){                                                                             // 0.0
/*92  */         s->dsp.me_sub_cmp[2]= zero_cmp;                                                                                                            // 0.0
/*94  */     }                                                                                                                                              // 0.0
/*96  */     c->hpel_put[2][0]= c->hpel_put[2][1]=                                                                                                          // 0.0
/*98  */     c->hpel_put[2][2]= c->hpel_put[2][3]= zero_hpel;                                                                                               // 0.0
/*102 */     c->temp= c->scratchpad;                                                                                                                        // 0.0
/*104 */ }                                                                                                                                                  // 0.0
