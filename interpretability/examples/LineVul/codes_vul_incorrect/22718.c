// commit message FFmpeg@cea9eb9520 (target=1, prob=0.46377644, correct=False): avcodec/dnxhddec: Make mb_scan_index a fixed length array
/*0  */ static av_cold int dnxhd_decode_close(AVCodecContext *avctx)  // (0) 0.1597
/*2  */ {                                                             // (8) 0.006944
/*4  */     DNXHDContext *ctx = avctx->priv_data;                     // (1) 0.1181
/*8  */     ff_free_vlc(&ctx->ac_vlc);                                // (3) 0.1181
/*10 */     ff_free_vlc(&ctx->dc_vlc);                                // (2) 0.1181
/*12 */     ff_free_vlc(&ctx->run_vlc);                               // (4) 0.1181
/*16 */     av_freep(&ctx->mb_scan_index);                            // (5) 0.1111
/*18 */     av_freep(&ctx->rows);                                     // (6) 0.08333
/*22 */     return 0;                                                 // (7) 0.04167
/*24 */ }                                                             // (9) 0.006944
