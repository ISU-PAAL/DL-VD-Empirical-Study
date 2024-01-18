// commit message FFmpeg@ca402f32e3 (target=1, prob=0.62442064, correct=True): handle malloc failures in ff_get_wav_header
/*0  */ static int w64_read_header(AVFormatContext *s, AVFormatParameters *ap)             // (6) 0.04102
/*2  */ {                                                                                  // (29) 0.001953
/*4  */     int64_t size;                                                                  // (24) 0.01758
/*6  */     AVIOContext *pb  = s->pb;                                                      // (15) 0.02734
/*8  */     WAVContext    *wav = s->priv_data;                                             // (9) 0.03516
/*10 */     AVStream *st;                                                                  // (25) 0.01563
/*12 */     uint8_t guid[16];                                                              // (18) 0.02148
/*16 */     avio_read(pb, guid, 16);                                                       // (16) 0.02734
/*18 */     if (memcmp(guid, guid_riff, 16))                                               // (10) 0.03516
/*20 */         return -1;                                                                 // (19) 0.02148
/*24 */     if (avio_rl64(pb) < 16 + 8 + 16 + 8 + 16 + 8) /* riff + wave + fmt + sizes */  // (0) 0.06836
/*26 */         return -1;                                                                 // (20) 0.02148
/*30 */     avio_read(pb, guid, 16);                                                       // (17) 0.02734
/*32 */     if (memcmp(guid, guid_wave, 16)) {                                             // (11) 0.03516
/*34 */         av_log(s, AV_LOG_ERROR, "could not find wave guid\n");                     // (1) 0.05469
/*36 */         return -1;                                                                 // (21) 0.02148
/*38 */     }                                                                              // (28) 0.007812
/*42 */     size = find_guid(pb, guid_fmt);                                                // (12) 0.0332
/*44 */     if (size < 0) {                                                                // (23) 0.01953
/*46 */         av_log(s, AV_LOG_ERROR, "could not find fmt guid\n");                      // (2) 0.05469
/*48 */         return -1;                                                                 // (22) 0.02148
/*50 */     }                                                                              // (27) 0.007812
/*54 */     st = av_new_stream(s, 0);                                                      // (14) 0.0293
/*56 */     if (!st)                                                                       // (26) 0.01367
/*58 */         return AVERROR(ENOMEM);                                                    // (13) 0.03125
/*62 */     /* subtract chunk header size - normal wav file doesn't count it */            // (8) 0.03516
/*64 */     ff_get_wav_header(pb, st->codec, size - 24);                                   // (5) 0.04297
/*66 */     avio_skip(pb, FFALIGN(size, INT64_C(8)) - size);                               // (4) 0.05078
/*70 */     st->need_parsing = AVSTREAM_PARSE_FULL;                                        // (7) 0.04102
/*74 */     av_set_pts_info(st, 64, 1, st->codec->sample_rate);                            // (3) 0.05273
/*78 */     size = find_guid(pb, guid_data);                                               // 0.0
/*80 */     if (size < 0) {                                                                // 0.0
/*82 */         av_log(s, AV_LOG_ERROR, "could not find data guid\n");                     // 0.0
/*84 */         return -1;                                                                 // 0.0
/*86 */     }                                                                              // 0.0
/*88 */     wav->data_end = avio_tell(pb) + size - 24;                                     // 0.0
/*90 */     wav->w64      = 1;                                                             // 0.0
/*94 */     return 0;                                                                      // 0.0
/*96 */ }                                                                                  // 0.0
