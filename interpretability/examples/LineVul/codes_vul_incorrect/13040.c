// commit message FFmpeg@073c2593c9 (target=1, prob=0.43001428, correct=False): Memory leak fix patch by (Burkhard Plaum <plaum >at< ipf.uni-stuttgart )dot( de>)
/*0   */ void h263_encode_init(MpegEncContext *s)                                                      // (9) 0.03125
/*2   */ {                                                                                             // (20) 0.001953
/*4   */     static int done = 0;                                                                      // (15) 0.01758
/*8   */     if (!done) {                                                                              // (16) 0.01562
/*10  */         done = 1;                                                                             // (14) 0.02148
/*14  */         init_uni_dc_tab();                                                                    // (11) 0.0293
/*18  */         init_rl(&rl_inter);                                                                   // (12) 0.0293
/*20  */         init_rl(&rl_intra);                                                                   // (10) 0.03125
/*22  */         init_rl(&rl_intra_aic);                                                               // (8) 0.03516
/*24  */                                                                                               // (17) 0.01562
/*26  */         init_uni_mpeg4_rl_tab(&rl_intra, uni_mpeg4_intra_rl_bits, uni_mpeg4_intra_rl_len);    // (0) 0.0957
/*28  */         init_uni_mpeg4_rl_tab(&rl_inter, uni_mpeg4_inter_rl_bits, uni_mpeg4_inter_rl_len);    // (2) 0.08984
/*32  */         init_uni_h263_rl_tab(&rl_intra_aic, NULL, uni_h263_intra_aic_rl_len);                 // (4) 0.08203
/*34  */         init_uni_h263_rl_tab(&rl_inter    , NULL, uni_h263_inter_rl_len);                     // (5) 0.07617
/*38  */         init_mv_penalty_and_fcode(s);                                                         // (7) 0.04297
/*40  */     }                                                                                         // (18) 0.007813
/*42  */     s->me.mv_penalty= mv_penalty; //FIXME exact table for msmpeg4 & h263p                     // (6) 0.06445
/*44  */                                                                                               // (19) 0.007812
/*46  */     s->intra_ac_vlc_length     =s->inter_ac_vlc_length     = uni_h263_inter_rl_len;           // (1) 0.08984
/*48  */     s->intra_ac_vlc_last_length=s->inter_ac_vlc_last_length= uni_h263_inter_rl_len + 128*64;  // (3) 0.08984
/*50  */     if(s->h263_aic){                                                                          // (13) 0.02344
/*52  */         s->intra_ac_vlc_length     = uni_h263_intra_aic_rl_len;                               // 0.0
/*54  */         s->intra_ac_vlc_last_length= uni_h263_intra_aic_rl_len + 128*64;                      // 0.0
/*56  */     }                                                                                         // 0.0
/*58  */     s->ac_esc_length= 7+1+6+8;                                                                // 0.0
/*62  */     // use fcodes >1 only for mpeg4 & h263 & h263p FIXME                                      // 0.0
/*64  */     switch(s->codec_id){                                                                      // 0.0
/*66  */     case CODEC_ID_MPEG4:                                                                      // 0.0
/*68  */         s->fcode_tab= fcode_tab;                                                              // 0.0
/*70  */         s->min_qcoeff= -2048;                                                                 // 0.0
/*72  */         s->max_qcoeff=  2047;                                                                 // 0.0
/*74  */         s->intra_ac_vlc_length     = uni_mpeg4_intra_rl_len;                                  // 0.0
/*76  */         s->intra_ac_vlc_last_length= uni_mpeg4_intra_rl_len + 128*64;                         // 0.0
/*78  */         s->inter_ac_vlc_length     = uni_mpeg4_inter_rl_len;                                  // 0.0
/*80  */         s->inter_ac_vlc_last_length= uni_mpeg4_inter_rl_len + 128*64;                         // 0.0
/*82  */         s->luma_dc_vlc_length= uni_DCtab_lum_len;                                             // 0.0
/*84  */         s->chroma_dc_vlc_length= uni_DCtab_chrom_len;                                         // 0.0
/*86  */         s->ac_esc_length= 7+2+1+6+1+12+1;                                                     // 0.0
/*88  */         s->y_dc_scale_table= ff_mpeg4_y_dc_scale_table;                                       // 0.0
/*90  */         s->c_dc_scale_table= ff_mpeg4_c_dc_scale_table;                                       // 0.0
/*94  */         if(s->flags & CODEC_FLAG_GLOBAL_HEADER){                                              // 0.0
/*98  */             s->avctx->extradata= av_malloc(1024);                                             // 0.0
/*100 */             init_put_bits(&s->pb, s->avctx->extradata, 1024);                                 // 0.0
/*102 */                                                                                               // 0.0
/*104 */             mpeg4_encode_visual_object_header(s);                                             // 0.0
/*106 */             mpeg4_encode_vol_header(s, 0, 0);                                                 // 0.0
/*110 */ //            ff_mpeg4_stuffing(&s->pb); ?                                                    // 0.0
/*112 */             flush_put_bits(&s->pb);                                                           // 0.0
/*114 */             s->avctx->extradata_size= (put_bits_count(&s->pb)+7)>>3;                          // 0.0
/*116 */         }                                                                                     // 0.0
/*118 */                                                                                               // 0.0
/*120 */         break;                                                                                // 0.0
/*122 */     case CODEC_ID_H263P:                                                                      // 0.0
/*124 */         if(s->umvplus)                                                                        // 0.0
/*126 */             s->fcode_tab= umv_fcode_tab;                                                      // 0.0
/*128 */         if(s->modified_quant){                                                                // 0.0
/*130 */             s->min_qcoeff= -2047;                                                             // 0.0
/*132 */             s->max_qcoeff=  2047;                                                             // 0.0
/*134 */         }else{                                                                                // 0.0
/*136 */             s->min_qcoeff= -127;                                                              // 0.0
/*138 */             s->max_qcoeff=  127;                                                              // 0.0
/*140 */         }                                                                                     // 0.0
/*142 */         break;                                                                                // 0.0
/*144 */         //Note for mpeg4 & h263 the dc-scale table will be set per frame as needed later      // 0.0
/*146 */     case CODEC_ID_FLV1:                                                                       // 0.0
/*148 */         if (s->h263_flv > 1) {                                                                // 0.0
/*150 */             s->min_qcoeff= -1023;                                                             // 0.0
/*152 */             s->max_qcoeff=  1023;                                                             // 0.0
/*154 */         } else {                                                                              // 0.0
/*156 */             s->min_qcoeff= -127;                                                              // 0.0
/*158 */             s->max_qcoeff=  127;                                                              // 0.0
/*160 */         }                                                                                     // 0.0
/*162 */         s->y_dc_scale_table=                                                                  // 0.0
/*164 */         s->c_dc_scale_table= ff_mpeg1_dc_scale_table;                                         // 0.0
/*166 */         break;                                                                                // 0.0
/*168 */     default: //nothing needed default table allready set in mpegvideo.c                       // 0.0
/*170 */         s->min_qcoeff= -127;                                                                  // 0.0
/*172 */         s->max_qcoeff=  127;                                                                  // 0.0
/*174 */         s->y_dc_scale_table=                                                                  // 0.0
/*176 */         s->c_dc_scale_table= ff_mpeg1_dc_scale_table;                                         // 0.0
/*178 */     }                                                                                         // 0.0
/*180 */ }                                                                                             // 0.0
