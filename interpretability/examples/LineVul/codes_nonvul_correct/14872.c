// commit message FFmpeg@38bb5a5434 (target=0, prob=0.3855942, correct=True): mpeg4videoenc: Support negative timestamps.
/*0   */ void mpeg4_encode_picture_header(MpegEncContext * s, int picture_number)                                                     // (10) 0.04688
/*2   */ {                                                                                                                            // (19) 0.001953
/*4   */     int time_incr;                                                                                                           // (16) 0.01758
/*6   */     int time_div, time_mod;                                                                                                  // (14) 0.02344
/*10  */     if(s->pict_type==AV_PICTURE_TYPE_I){                                                                                     // (13) 0.04102
/*12  */         if(!(s->flags&CODEC_FLAG_GLOBAL_HEADER)){                                                                            // (7) 0.05664
/*14  */             if(s->strict_std_compliance < FF_COMPLIANCE_VERY_STRICT) //HACK, the reference sw is buggy                       // (1) 0.08594
/*16  */                 mpeg4_encode_visual_object_header(s);                                                                        // (6) 0.05859
/*18  */             if(s->strict_std_compliance < FF_COMPLIANCE_VERY_STRICT || picture_number==0) //HACK, the reference sw is buggy  // (0) 0.09766
/*20  */                 mpeg4_encode_vol_header(s, 0, 0);                                                                            // (5) 0.0625
/*22  */         }                                                                                                                    // (17) 0.01562
/*24  */         if(!(s->workaround_bugs & FF_BUG_MS))                                                                                // (11) 0.04687
/*26  */             mpeg4_encode_gop_header(s);                                                                                      // (9) 0.04883
/*28  */     }                                                                                                                        // (18) 0.007812
/*32  */     s->partitioned_frame= s->data_partitioning && s->pict_type!=AV_PICTURE_TYPE_B;                                           // (2) 0.07031
/*36  */     put_bits(&s->pb, 16, 0);                /* vop header */                                                                 // (3) 0.06836
/*38  */     put_bits(&s->pb, 16, VOP_STARTCODE);    /* vop header */                                                                 // (8) 0.05469
/*40  */     put_bits(&s->pb, 2, s->pict_type - 1);  /* pict type: I = 0 , P = 1 */                                                   // (4) 0.06641
/*44  */     assert(s->time>=0);                                                                                                      // (15) 0.02344
/*46  */     time_div= s->time/s->avctx->time_base.den;                                                                               // (12) 0.04297
/*48  */     time_mod= s->time%s->avctx->time_base.den;                                                                               // 0.0
/*50  */     time_incr= time_div - s->last_time_base;                                                                                 // 0.0
/*52  */     assert(time_incr >= 0);                                                                                                  // 0.0
/*54  */     while(time_incr--)                                                                                                       // 0.0
/*56  */         put_bits(&s->pb, 1, 1);                                                                                              // 0.0
/*60  */     put_bits(&s->pb, 1, 0);                                                                                                  // 0.0
/*64  */     put_bits(&s->pb, 1, 1);                             /* marker */                                                         // 0.0
/*66  */     put_bits(&s->pb, s->time_increment_bits, time_mod); /* time increment */                                                 // 0.0
/*68  */     put_bits(&s->pb, 1, 1);                             /* marker */                                                         // 0.0
/*70  */     put_bits(&s->pb, 1, 1);                             /* vop coded */                                                      // 0.0
/*72  */     if (    s->pict_type == AV_PICTURE_TYPE_P                                                                                // 0.0
/*74  */         || (s->pict_type == AV_PICTURE_TYPE_S && s->vol_sprite_usage==GMC_SPRITE)) {                                         // 0.0
/*76  */         put_bits(&s->pb, 1, s->no_rounding);    /* rounding type */                                                          // 0.0
/*78  */     }                                                                                                                        // 0.0
/*80  */     put_bits(&s->pb, 3, 0);     /* intra dc VLC threshold */                                                                 // 0.0
/*82  */     if(!s->progressive_sequence){                                                                                            // 0.0
/*84  */          put_bits(&s->pb, 1, s->current_picture_ptr->top_field_first);                                                       // 0.0
/*86  */          put_bits(&s->pb, 1, s->alternate_scan);                                                                             // 0.0
/*88  */     }                                                                                                                        // 0.0
/*90  */     //FIXME sprite stuff                                                                                                     // 0.0
/*94  */     put_bits(&s->pb, 5, s->qscale);                                                                                          // 0.0
/*98  */     if (s->pict_type != AV_PICTURE_TYPE_I)                                                                                   // 0.0
/*100 */         put_bits(&s->pb, 3, s->f_code); /* fcode_for */                                                                      // 0.0
/*102 */     if (s->pict_type == AV_PICTURE_TYPE_B)                                                                                   // 0.0
/*104 */         put_bits(&s->pb, 3, s->b_code); /* fcode_back */                                                                     // 0.0
/*106 */ }                                                                                                                            // 0.0
