// commit message FFmpeg@d6604b29ef (target=0, prob=0.005034222, correct=True): Gather all coded_frame allocations and free functions to a single place
/*0 */ static av_cold int pam_encode_close(AVCodecContext *avctx)  // (0) 0.3889
/*2 */ {                                                           // (3) 0.01852
/*4 */     av_frame_free(&avctx->coded_frame);                     // (1) 0.2963
/*6 */     return 0;                                               // (2) 0.1111
/*8 */ }                                                           // (4) 0.01852
