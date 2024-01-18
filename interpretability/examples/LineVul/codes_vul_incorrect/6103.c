// commit message FFmpeg@1eaff98c83 (target=1, prob=0.27575967, correct=False): flvenc: Check whether seeking back to the header succeeded
/*0  */ static int flv_write_trailer(AVFormatContext *s)          // (10) 0.04082
/*2  */ {                                                         // (21) 0.002551
/*4  */     int64_t file_size;                                    // (15) 0.02806
/*8  */     AVIOContext *pb = s->pb;                              // (14) 0.03316
/*10 */     FLVContext *flv = s->priv_data;                       // (11) 0.04082
/*12 */     int i;                                                // (18) 0.01531
/*16 */     /* Add EOS tag */                                     // (16) 0.02296
/*18 */     for (i = 0; i < s->nb_streams; i++) {                 // (8) 0.05357
/*20 */         AVCodecContext *enc = s->streams[i]->codec;       // (3) 0.06378
/*22 */         FLVStreamContext *sc = s->streams[i]->priv_data;  // (2) 0.06633
/*24 */         if (enc->codec_type == AVMEDIA_TYPE_VIDEO &&      // (4) 0.06122
/*26 */             enc->codec_id == AV_CODEC_ID_H264)            // (0) 0.07398
/*28 */             put_avc_eos_tag(pb, sc->last_ts);             // (1) 0.07398
/*30 */     }                                                     // (20) 0.0102
/*34 */     file_size = avio_tell(pb);                            // (13) 0.03571
/*38 */     /* update information */                              // (17) 0.01786
/*40 */     avio_seek(pb, flv->duration_offset, SEEK_SET);        // (6) 0.05612
/*42 */     put_amf_double(pb, flv->duration / (double)1000);     // (7) 0.05612
/*44 */     avio_seek(pb, flv->filesize_offset, SEEK_SET);        // (5) 0.05867
/*46 */     put_amf_double(pb, file_size);                        // (12) 0.04082
/*50 */     avio_seek(pb, file_size, SEEK_SET);                   // (9) 0.04847
/*52 */     return 0;                                             // (19) 0.01531
/*54 */ }                                                         // (22) 0.002551
