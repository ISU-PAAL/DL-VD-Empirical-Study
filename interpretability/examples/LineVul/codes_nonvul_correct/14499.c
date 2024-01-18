// commit message FFmpeg@fc8fa007fb (target=0, prob=0.15352221, correct=True): Implement librtmp seek support.
/*0  */ static int64_t rtmp_read_seek(URLContext *s, int stream_index,  // (1) 0.1158
/*2  */                               int64_t timestamp, int flags)     // (0) 0.2
/*4  */ {                                                               // (10) 0.005263
/*6  */     RTMP *r = s->priv_data;                                     // (6) 0.07368
/*10 */     if (flags & AVSEEK_FLAG_BYTE)                               // (5) 0.08421
/*12 */         return AVERROR(ENOSYS);                                 // (4) 0.08421
/*16 */     /* seeks are in milliseconds */                             // (8) 0.04737
/*18 */     timestamp = av_rescale(timestamp, AV_TIME_BASE, 1000);      // (2) 0.1158
/*20 */     if (!RTMP_SendSeek(r, timestamp))                           // (3) 0.08421
/*22 */         return -1;                                              // (7) 0.05789
/*24 */     return timestamp;                                           // (9) 0.03158
/*26 */ }                                                               // (11) 0.005263
