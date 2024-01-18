// commit message FFmpeg@4381bddc9f (target=0, prob=0.57555133, correct=False): lavfi: consistently use int for sample_rate in AVFilterLink and AVFilterBufferRefAudioProps
/*0  */ int ff_parse_sample_rate(unsigned *ret, const char *arg, void *log_ctx)    // (1) 0.1529
/*2  */ {                                                                          // (9) 0.006369
/*4  */     char *tail;                                                            // (6) 0.04459
/*6  */     double srate = av_strtod(arg, &tail);                                  // (3) 0.1146
/*8  */     if (*tail || srate < 1 || (int)srate != srate) {                       // (2) 0.1401
/*10 */         av_log(log_ctx, AV_LOG_ERROR, "Invalid sample rate '%s'\n", arg);  // (0) 0.2166
/*12 */         return AVERROR(EINVAL);                                            // (4) 0.1019
/*14 */     }                                                                      // (8) 0.02548
/*16 */     *ret = srate;                                                          // (5) 0.05732
/*18 */     return 0;                                                              // (7) 0.03822
/*20 */ }                                                                          // (10) 0.006369
