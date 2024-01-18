// commit message FFmpeg@0d021cc8b3 (target=0, prob=0.07837782, correct=True): avcodec/nvenc: rework library load and GPU selection
/*0  */ static av_cold int check_cuda_errors(AVCodecContext *avctx, CUresult err, const char *func)  // (1) 0.2417
/*2  */ {                                                                                            // (6) 0.008333
/*4  */     if (err != CUDA_SUCCESS) {                                                               // (2) 0.125
/*6  */         av_log(avctx, AV_LOG_FATAL, ">> %s - failed with error code 0x%x\n", func, err);     // (0) 0.35
/*8  */         return 0;                                                                            // (3) 0.08333
/*10 */     }                                                                                        // (5) 0.03333
/*12 */     return 1;                                                                                // (4) 0.05
/*14 */ }                                                                                            // (7) 0.008333
