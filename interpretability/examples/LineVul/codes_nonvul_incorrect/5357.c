// commit message FFmpeg@03847eb825 (target=0, prob=0.5239407, correct=False): lavf: compute probe buffer size more reliably.
/*0   */ int av_probe_input_buffer(AVIOContext *pb, AVInputFormat **fmt,                                                                                 // (8) 0.04492
/*2   */                           const char *filename, void *logctx,                                                                                   // (4) 0.06836
/*4   */                           unsigned int offset, unsigned int max_probe_size)                                                                     // (0) 0.07422
/*6   */ {                                                                                                                                               // (22) 0.001953
/*8   */     AVProbeData pd = { filename ? filename : "", NULL, -offset };                                                                               // (11) 0.04297
/*10  */     unsigned char *buf = NULL;                                                                                                                  // (19) 0.01953
/*12  */     int ret = 0, probe_size;                                                                                                                    // (18) 0.02344
/*16  */     if (!max_probe_size) {                                                                                                                      // (17) 0.02539
/*18  */         max_probe_size = PROBE_BUF_MAX;                                                                                                         // (9) 0.04492
/*20  */     } else if (max_probe_size > PROBE_BUF_MAX) {                                                                                                // (6) 0.04687
/*22  */         max_probe_size = PROBE_BUF_MAX;                                                                                                         // (10) 0.04492
/*24  */     } else if (max_probe_size < PROBE_BUF_MIN) {                                                                                                // (7) 0.04687
/*26  */         return AVERROR(EINVAL);                                                                                                                 // (13) 0.03125
/*28  */     }                                                                                                                                           // (21) 0.007812
/*32  */     if (offset >= max_probe_size) {                                                                                                             // (15) 0.0293
/*34  */         return AVERROR(EINVAL);                                                                                                                 // (14) 0.03125
/*36  */     }                                                                                                                                           // (20) 0.007812
/*40  */     for(probe_size= PROBE_BUF_MIN; probe_size<=max_probe_size && !*fmt;                                                                         // (3) 0.07031
/*42  */         probe_size = FFMIN(probe_size<<1, FFMAX(max_probe_size, probe_size+1))) {                                                               // (1) 0.07422
/*44  */         int score = probe_size < max_probe_size ? AVPROBE_SCORE_RETRY : 0;                                                                      // (5) 0.06641
/*46  */         int buf_offset = (probe_size == PROBE_BUF_MIN) ? 0 : probe_size>>1;                                                                     // (2) 0.07031
/*48  */         void *buftmp;                                                                                                                           // (16) 0.02539
/*52  */         if (probe_size < offset) {                                                                                                              // (12) 0.0332
/*54  */             continue;                                                                                                                           // 0.0
/*56  */         }                                                                                                                                       // 0.0
/*60  */         /* read probe data */                                                                                                                   // 0.0
/*62  */         buftmp = av_realloc(buf, probe_size + AVPROBE_PADDING_SIZE);                                                                            // 0.0
/*64  */         if(!buftmp){                                                                                                                            // 0.0
/*66  */             av_free(buf);                                                                                                                       // 0.0
/*68  */             return AVERROR(ENOMEM);                                                                                                             // 0.0
/*70  */         }                                                                                                                                       // 0.0
/*72  */         buf=buftmp;                                                                                                                             // 0.0
/*74  */         if ((ret = avio_read(pb, buf + buf_offset, probe_size - buf_offset)) < 0) {                                                             // 0.0
/*76  */             /* fail if error was not end of file, otherwise, lower score */                                                                     // 0.0
/*78  */             if (ret != AVERROR_EOF) {                                                                                                           // 0.0
/*80  */                 av_free(buf);                                                                                                                   // 0.0
/*82  */                 return ret;                                                                                                                     // 0.0
/*84  */             }                                                                                                                                   // 0.0
/*86  */             score = 0;                                                                                                                          // 0.0
/*88  */             ret = 0;            /* error was end of file, nothing read */                                                                       // 0.0
/*90  */         }                                                                                                                                       // 0.0
/*92  */         pd.buf_size += ret;                                                                                                                     // 0.0
/*94  */         pd.buf = &buf[offset];                                                                                                                  // 0.0
/*98  */         memset(pd.buf + pd.buf_size, 0, AVPROBE_PADDING_SIZE);                                                                                  // 0.0
/*102 */         /* guess file format */                                                                                                                 // 0.0
/*104 */         *fmt = av_probe_input_format2(&pd, 1, &score);                                                                                          // 0.0
/*106 */         if(*fmt){                                                                                                                               // 0.0
/*108 */             if(score <= AVPROBE_SCORE_RETRY){ //this can only be true in the last iteration                                                     // 0.0
/*110 */                 av_log(logctx, AV_LOG_WARNING, "Format %s detected only with low score of %d, misdetection possible!\n", (*fmt)->name, score);  // 0.0
/*112 */             }else                                                                                                                               // 0.0
/*114 */                 av_log(logctx, AV_LOG_DEBUG, "Format %s probed with size=%d and score=%d\n", (*fmt)->name, probe_size, score);                  // 0.0
/*116 */         }                                                                                                                                       // 0.0
/*118 */     }                                                                                                                                           // 0.0
/*122 */     if (!*fmt) {                                                                                                                                // 0.0
/*124 */         av_free(buf);                                                                                                                           // 0.0
/*126 */         return AVERROR_INVALIDDATA;                                                                                                             // 0.0
/*128 */     }                                                                                                                                           // 0.0
/*132 */     /* rewind. reuse probe buffer to avoid seeking */                                                                                           // 0.0
/*134 */     ret = ffio_rewind_with_probe_data(pb, &buf, pd.buf_size);                                                                                   // 0.0
/*138 */     return ret;                                                                                                                                 // 0.0
/*140 */ }                                                                                                                                               // 0.0
