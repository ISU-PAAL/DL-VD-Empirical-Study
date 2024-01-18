// commit message FFmpeg@f6774f905f (target=1, prob=0.3440784, correct=False): mpegvideo: operate with pointers to AVFrames instead of whole structs
/*0  */ static int estimate_qp(MpegEncContext *s, int dry_run){                      // (12) 0.03711
/*2  */     if (s->next_lambda){                                                     // (22) 0.02148
/*4  */         s->current_picture_ptr->f.quality =                                  // (13) 0.03711
/*6  */         s->current_picture.f.quality = s->next_lambda;                       // (4) 0.04492
/*8  */         if(!dry_run) s->next_lambda= 0;                                      // (7) 0.04297
/*10 */     } else if (!s->fixed_qscale) {                                           // (18) 0.0293
/*12 */         s->current_picture_ptr->f.quality =                                  // (14) 0.03711
/*14 */         s->current_picture.f.quality = ff_rate_estimate_qscale(s, dry_run);  // (0) 0.06445
/*16 */         if (s->current_picture.f.quality < 0)                                // (8) 0.04102
/*18 */             return -1;                                                       // (17) 0.0293
/*20 */     }                                                                        // (25) 0.007813
/*24 */     if(s->adaptive_quant){                                                   // (21) 0.02344
/*26 */         switch(s->codec_id){                                                 // (16) 0.03125
/*28 */         case AV_CODEC_ID_MPEG4:                                              // (9) 0.03906
/*30 */             if (CONFIG_MPEG4_ENCODER)                                        // (3) 0.04688
/*32 */                 ff_clean_mpeg4_qscales(s);                                   // (1) 0.05469
/*34 */             break;                                                           // (19) 0.02539
/*36 */         case AV_CODEC_ID_H263:                                               // (15) 0.03711
/*38 */         case AV_CODEC_ID_H263P:                                              // (10) 0.03906
/*40 */         case AV_CODEC_ID_FLV1:                                               // (11) 0.03906
/*42 */             if (CONFIG_H263_ENCODER)                                         // (5) 0.04492
/*44 */                 ff_clean_h263_qscales(s);                                    // (2) 0.05469
/*46 */             break;                                                           // (20) 0.02539
/*48 */         default:                                                             // (23) 0.01758
/*50 */             ff_init_qscale_tab(s);                                           // (6) 0.04297
/*52 */         }                                                                    // (24) 0.01563
/*56 */         s->lambda= s->lambda_table[0];                                       // 0.0
/*58 */         //FIXME broken                                                       // 0.0
/*60 */     }else                                                                    // 0.0
/*62 */         s->lambda = s->current_picture.f.quality;                            // 0.0
/*64 */     update_qscale(s);                                                        // 0.0
/*66 */     return 0;                                                                // 0.0
/*68 */ }                                                                            // 0.0
