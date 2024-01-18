// commit message FFmpeg@066ad0926a (target=1, prob=0.42705598, correct=False): tmv: Check return value of avio_seek and avoid modifying state if it fails
/*0  */ static int tmv_read_seek(AVFormatContext *s, int stream_index,             // (3) 0.09953
/*2  */                          int64_t timestamp, int flags)                     // (1) 0.1564
/*4  */ {                                                                          // (11) 0.004739
/*6  */     TMVContext *tmv = s->priv_data;                                        // (4) 0.07583
/*8  */     int64_t pos;                                                           // (7) 0.04265
/*12 */     if (stream_index)                                                      // (8) 0.04265
/*14 */         return -1;                                                         // (6) 0.05213
/*18 */     pos = timestamp *                                                      // (9) 0.03318
/*20 */           (tmv->audio_chunk_size + tmv->video_chunk_size + tmv->padding);  // (0) 0.1754
/*24 */     avio_seek(s->pb, pos + TMV_HEADER_SIZE, SEEK_SET);                     // (2) 0.128
/*26 */     tmv->stream_index = 0;                                                 // (5) 0.06161
/*28 */     return 0;                                                              // (10) 0.02844
/*30 */ }                                                                          // (12) 0.004739
