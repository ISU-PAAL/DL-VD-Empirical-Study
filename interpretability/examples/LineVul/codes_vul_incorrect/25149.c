// commit message FFmpeg@b86651a208 (target=1, prob=0.34225944, correct=False): Check the return value of ff_rv34_decode_init() in rv30.c and rv40.c
/*0  */ static av_cold int rv40_decode_init(AVCodecContext *avctx)  // (5) 0.07942
/*2  */ {                                                           // (13) 0.00361
/*4  */     RV34DecContext *r = avctx->priv_data;                   // (7) 0.06137
/*8  */     r->rv30 = 0;                                            // (11) 0.03971
/*10 */     ff_rv34_decode_init(avctx);                             // (8) 0.06137
/*12 */     if(!aic_top_vlc.bits)                                   // (10) 0.05415
/*14 */         rv40_init_tables();                                 // (9) 0.05776
/*16 */     r->parse_slice_header = rv40_parse_slice_header;        // (6) 0.07581
/*18 */     r->decode_intra_types = rv40_decode_intra_types;        // (3) 0.09025
/*20 */     r->decode_mb_info     = rv40_decode_mb_info;            // (0) 0.09747
/*22 */     r->loop_filter        = rv40_loop_filter;               // (4) 0.08664
/*24 */     r->luma_dc_quant_i = rv40_luma_dc_quant[0];             // (1) 0.09747
/*26 */     r->luma_dc_quant_p = rv40_luma_dc_quant[1];             // (2) 0.09747
/*28 */     return 0;                                               // (12) 0.02166
/*30 */ }                                                           // (14) 0.00361
