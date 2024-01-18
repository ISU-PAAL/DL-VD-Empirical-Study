// commit message FFmpeg@da34e4e132 (target=1, prob=0.6027674, correct=True): swresample/soxr: fix invalid use of linear_interp
/*0  */ static struct ResampleContext *create(struct ResampleContext *c, int out_rate, int in_rate, int filter_size, int phase_shift, int linear,                 // (3) 0.07421
/*2  */         double cutoff, enum AVSampleFormat format, enum SwrFilterType filter_type, double kaiser_beta, double precision, int cheby, int exact_rational){  // (2) 0.08402
/*4  */     soxr_error_t error;                                                                                                                                   // (15) 0.02365
/*8  */     soxr_datatype_t type =                                                                                                                                // (14) 0.02734
/*10 */         format == AV_SAMPLE_FMT_S16P? SOXR_INT16_S :                                                                                                      // (7) 0.05857
/*12 */         format == AV_SAMPLE_FMT_S16 ? SOXR_INT16_I :                                                                                                      // (10) 0.05662
/*14 */         format == AV_SAMPLE_FMT_S32P? SOXR_INT32_S :                                                                                                      // (8) 0.05857
/*16 */         format == AV_SAMPLE_FMT_S32 ? SOXR_INT32_I :                                                                                                      // (9) 0.05662
/*18 */         format == AV_SAMPLE_FMT_FLTP? SOXR_FLOAT32_S :                                                                                                    // (6) 0.06052
/*20 */         format == AV_SAMPLE_FMT_FLT ? SOXR_FLOAT32_I :                                                                                                    // (5) 0.06052
/*22 */         format == AV_SAMPLE_FMT_DBLP? SOXR_FLOAT64_S :                                                                                                    // (4) 0.06247
/*24 */         format == AV_SAMPLE_FMT_DBL ? SOXR_FLOAT64_I : (soxr_datatype_t)-1;                                                                               // (1) 0.0859
/*28 */     soxr_io_spec_t io_spec = soxr_io_spec(type, type);                                                                                                    // (11) 0.05467
/*32 */     soxr_quality_spec_t q_spec = soxr_quality_spec((int)((precision-2)/4), (SOXR_HI_PREC_CLOCK|SOXR_ROLLOFF_NONE)*!!cheby);                               // (0) 0.1211
/*34 */     q_spec.precision = linear? 0 : precision;                                                                                                             // (13) 0.03125
/*36 */ #if !defined SOXR_VERSION /* Deprecated @ March 2013: */                                                                                                  // (12) 0.03321
/*38 */     q_spec.bw_pc = cutoff? FFMAX(FFMIN(cutoff,.995),.8)*100 : q_spec.bw_pc;                                                                               // 0.0
/*40 */ #else                                                                                                                                                     // 0.0
/*42 */     q_spec.passband_end = cutoff? FFMAX(FFMIN(cutoff,.995),.8) : q_spec.passband_end;                                                                     // 0.0
/*44 */ #endif                                                                                                                                                    // 0.0
/*48 */     soxr_delete((soxr_t)c);                                                                                                                               // 0.0
/*50 */     c = (struct ResampleContext *)                                                                                                                        // 0.0
/*52 */         soxr_create(in_rate, out_rate, 0, &error, &io_spec, &q_spec, 0);                                                                                  // 0.0
/*54 */     if (!c)                                                                                                                                               // 0.0
/*56 */         av_log(NULL, AV_LOG_ERROR, "soxr_create: %s\n", error);                                                                                           // 0.0
/*58 */     return c;                                                                                                                                             // 0.0
/*60 */ }                                                                                                                                                         // 0.0
