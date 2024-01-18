// commit message FFmpeg@af7d13ee4a (target=1, prob=0.9990126, correct=True): asink_nullsink: plug a memory leak.
/*0 */ static int null_filter_samples(AVFilterLink *link, AVFilterBufferRef *samplesref)  // (0) 0.6
/*2 */ {                                                                                  // (2) 0.025
/*5 */     return 0;                                                                      // (1) 0.15
/*7 */ }                                                                                  // (3) 0.025
