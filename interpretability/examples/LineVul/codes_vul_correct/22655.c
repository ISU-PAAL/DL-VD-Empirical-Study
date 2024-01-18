// commit message FFmpeg@2711cb28f4 (target=1, prob=0.9991191, correct=True): prevent assert failure with negative quant_offset
/*0  */ static double get_diff_limited_q(MpegEncContext *s, RateControlEntry *rce, double q){           // (10) 0.05273
/*2  */     RateControlContext *rcc= &s->rc_context;                                                    // (14) 0.0332
/*4  */     AVCodecContext *a= s->avctx;                                                                // (15) 0.0293
/*6  */     const int pict_type= rce->new_pict_type;                                                    // (13) 0.03516
/*8  */     const double last_p_q    = rcc->last_qscale_for[P_TYPE];                                    // (9) 0.05469
/*10 */     const double last_non_b_q= rcc->last_qscale_for[rcc->last_non_b_pict_type];                 // (3) 0.07031
/*14 */     if     (pict_type==I_TYPE && (a->i_quant_factor>0.0 || rcc->last_non_b_pict_type==P_TYPE))  // (0) 0.0918
/*16 */         q= last_p_q    *FFABS(a->i_quant_factor) + a->i_quant_offset;                           // (1) 0.07617
/*18 */     else if(pict_type==B_TYPE && a->b_quant_factor>0.0)                                         // (11) 0.05078
/*20 */         q= last_non_b_q*    a->b_quant_factor  + a->b_quant_offset;                             // (2) 0.07227
/*25 */     /* last qscale / qdiff stuff */                                                             // (16) 0.02344
/*27 */     if(rcc->last_non_b_pict_type==pict_type || pict_type!=I_TYPE){                              // (4) 0.06055
/*29 */         double last_q= rcc->last_qscale_for[pict_type];                                         // (12) 0.05078
/*31 */         const int maxdiff= FF_QP2LAMBDA * a->max_qdiff;                                         // (6) 0.05664
/*35 */         if     (q > last_q + maxdiff) q= last_q + maxdiff;                                      // (5) 0.06055
/*37 */         else if(q < last_q - maxdiff) q= last_q - maxdiff;                                      // (8) 0.05469
/*39 */     }                                                                                           // (17) 0.007813
/*43 */     rcc->last_qscale_for[pict_type]= q; //Note we cannot do that after blurring                 // (7) 0.05469
/*47 */     if(pict_type!=B_TYPE)                                                                       // 0.0
/*49 */         rcc->last_non_b_pict_type= pict_type;                                                   // 0.0
/*53 */     return q;                                                                                   // 0.0
/*55 */ }                                                                                               // 0.0
