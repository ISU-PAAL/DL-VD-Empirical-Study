// commit message FFmpeg@49c8132b17 (target=1, prob=0.41388083, correct=False): not checking error return, resulting double free returning uninitalized pointers
/*0  */ static int ipmovie_read_packet(AVFormatContext *s,         // (5) 0.06107
/*2  */                                AVPacket *pkt)              // (0) 0.1412
/*4  */ {                                                          // (15) 0.003817
/*6  */     IPMVEContext *ipmovie = (IPMVEContext *)s->priv_data;  // (1) 0.09924
/*8  */     ByteIOContext *pb = &s->pb;                            // (9) 0.05344
/*10 */     int ret;                                               // (12) 0.0229
/*14 */     ret = process_ipmovie_chunk(ipmovie, pb, pkt);         // (2) 0.08397
/*16 */     if (ret == CHUNK_BAD)                                  // (10) 0.05344
/*18 */         ret = AVERROR_INVALIDDATA;                         // (3) 0.0687
/*20 */     else if (ret == CHUNK_EOF)                             // (7) 0.05725
/*22 */         ret = AVERROR_IO;                                  // (8) 0.05725
/*24 */     else if (ret == CHUNK_NOMEM)                           // (6) 0.06107
/*26 */         ret = AVERROR_NOMEM;                               // (4) 0.06489
/*28 */     else                                                   // (14) 0.01527
/*30 */         ret = 0;                                           // (11) 0.04198
/*34 */     return ret;                                            // (13) 0.0229
/*36 */ }                                                          // (16) 0.003817
