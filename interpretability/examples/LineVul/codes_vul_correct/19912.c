// commit message FFmpeg@12dea8a5a1 (target=1, prob=0.99908936, correct=True): avcodec/ivi: Free custom blk_vlc
/*0 */ av_cold int ff_ivi_decode_close(AVCodecContext *avctx)  // (1) 0.1629
/*1 */ {                                                       // (8) 0.007406
/*2 */     IVI45DecContext *ctx = avctx->priv_data;            // (3) 0.1333
/*3 */     ivi_free_buffers(&ctx->planes[0]);                  // (4) 0.1261
/*4 */     if (ctx->mb_vlc.cust_tab.table)                     // (2) 0.1407
/*5 */         ff_free_vlc(&ctx->mb_vlc.cust_tab);             // (0) 0.1926
/*6 */     av_frame_free(&ctx->p_frame);                       // (5) 0.1111
/*7 */     return 0;                                           // (6) 0.04444
/*8 */ }                                                       // (7) 0.007409
