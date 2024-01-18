// commit message FFmpeg@8332321c57 (target=1, prob=0.49116504, correct=False): dv: Check return value of avio_seek and avoid modifying state if it fails
/*0  */ static int dv_read_seek(AVFormatContext *s, int stream_index,     // (4) 0.1058
/*2  */                        int64_t timestamp, int flags)              // (0) 0.164
/*4  */ {                                                                 // (8) 0.005291
/*6  */     RawDVContext *r   = s->priv_data;                             // (6) 0.09524
/*8  */     DVDemuxContext *c = r->dv_demux;                              // (5) 0.09524
/*10 */     int64_t offset    = dv_frame_offset(s, c, timestamp, flags);  // (1) 0.1429
/*14 */     dv_offset_reset(c, offset / c->sys->frame_size);              // (2) 0.1164
/*18 */     offset = avio_seek(s->pb, offset, SEEK_SET);                  // (3) 0.1111
/*20 */     return (offset < 0) ? offset : 0;                             // (7) 0.07407
/*22 */ }                                                                 // (9) 0.005291
