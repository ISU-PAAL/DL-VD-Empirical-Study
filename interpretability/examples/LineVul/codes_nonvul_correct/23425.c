// commit message FFmpeg@b3f9f7a333 (target=0, prob=0.44968683, correct=True): Let pmt override stream info when encoutered later in the ts file. Do not set codec id based on pes start code, this is unreliable. Fix gazeta-20090408-1456-aa.ts
/*0  */ static PESContext *add_pes_stream(MpegTSContext *ts, int pid, int pcr_pid, int stream_type)  // (0) 0.1046
/*2  */ {                                                                                            // (21) 0.003268
/*4  */     MpegTSFilter *tss;                                                                       // (10) 0.03595
/*6  */     PESContext *pes;                                                                         // (14) 0.02941
/*10 */     /* if no pid found, then add a pid context */                                            // (5) 0.04902
/*12 */     pes = av_mallocz(sizeof(PESContext));                                                    // (2) 0.05882
/*14 */     if (!pes)                                                                                // (18) 0.02288
/*16 */         return 0;                                                                            // (12) 0.03268
/*18 */     pes->ts = ts;                                                                            // (15) 0.02941
/*20 */     pes->stream = ts->stream;                                                                // (11) 0.03595
/*22 */     pes->pid = pid;                                                                          // (16) 0.02941
/*24 */     pes->pcr_pid = pcr_pid;                                                                  // (6) 0.04902
/*26 */     pes->stream_type = stream_type;                                                          // (8) 0.04248
/*28 */     pes->state = MPEGTS_SKIP;                                                                // (7) 0.04248
/*30 */     pes->pts = AV_NOPTS_VALUE;                                                               // (3) 0.05229
/*32 */     pes->dts = AV_NOPTS_VALUE;                                                               // (4) 0.05229
/*34 */     tss = mpegts_open_pes_filter(ts, pid, mpegts_push_data, pes);                            // (1) 0.09804
/*36 */     if (!tss) {                                                                              // (17) 0.02941
/*38 */         av_free(pes);                                                                        // (9) 0.04248
/*40 */         return 0;                                                                            // (13) 0.03268
/*42 */     }                                                                                        // (20) 0.01307
/*44 */     return pes;                                                                              // (19) 0.01961
/*46 */ }                                                                                            // (22) 0.003268
