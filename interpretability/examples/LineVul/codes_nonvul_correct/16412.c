// commit message FFmpeg@d6604b29ef (target=0, prob=0.005813926, correct=True): Gather all coded_frame allocations and free functions to a single place
/*0 */ static av_cold int encode_close(AVCodecContext *avctx)  // (0) 0.34
/*2 */ {                                                       // (3) 0.02
/*4 */     av_frame_free(&avctx->coded_frame);                 // (1) 0.32
/*6 */     return 0;                                           // (2) 0.12
/*8 */ }                                                       // (4) 0.02
