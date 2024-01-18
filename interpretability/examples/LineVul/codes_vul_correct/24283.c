// commit message FFmpeg@ad5807f8aa (target=1, prob=0.6798813, correct=True): avformat: fix overflows during bit rate calculation
/*0   */ static int wsd_read_header(AVFormatContext *s)                                             // (13) 0.0293
/*2   */ {                                                                                          // (28) 0.001953
/*4   */     AVIOContext *pb = s->pb;                                                               // (16) 0.02539
/*6   */     AVStream *st;                                                                          // (23) 0.01563
/*8   */     int version;                                                                           // (25) 0.01172
/*10  */     uint32_t text_offset, data_offset, channel_assign;                                     // (6) 0.03906
/*12  */     char playback_time[AV_TIMECODE_STR_SIZE];                                              // (7) 0.03711
/*16  */     st = avformat_new_stream(s, NULL);                                                     // (10) 0.03125
/*18  */     if (!st)                                                                               // (24) 0.01367
/*20  */         return AVERROR(ENOMEM);                                                            // (11) 0.03125
/*24  */     avio_skip(pb, 8);                                                                      // (20) 0.02344
/*26  */     version = avio_r8(pb);                                                                 // (17) 0.02539
/*28  */     av_log(s, AV_LOG_DEBUG, "version: %i.%i\n", version >> 4, version & 0xF);              // (0) 0.07031
/*30  */     avio_skip(pb, 11);                                                                     // (19) 0.02344
/*34  */     if (version < 0x10) {                                                                  // (18) 0.02344
/*36  */         text_offset = 0x80;                                                                // (14) 0.0293
/*38  */         data_offset = 0x800;                                                               // (15) 0.0293
/*40  */         avio_skip(pb, 8);                                                                  // (12) 0.03125
/*42  */     } else {                                                                               // (26) 0.01172
/*44  */         text_offset = avio_rb32(pb);                                                       // (8) 0.03711
/*46  */         data_offset = avio_rb32(pb);                                                       // (9) 0.03711
/*48  */     }                                                                                      // (27) 0.007812
/*52  */     avio_skip(pb, 4);                                                                      // (21) 0.02344
/*54  */     av_timecode_make_smpte_tc_string(playback_time, avio_rb32(pb), 0);                     // (1) 0.06445
/*56  */     av_dict_set(&s->metadata, "playback_time", playback_time, 0);                          // (3) 0.04883
/*60  */     st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;                                        // (4) 0.04687
/*62  */     st->codecpar->codec_id    = s->iformat->raw_codec_id;                                  // (2) 0.05664
/*64  */     st->codecpar->sample_rate = avio_rb32(pb) / 8;                                         // (5) 0.04687
/*66  */     avio_skip(pb, 4);                                                                      // (22) 0.02344
/*68  */     st->codecpar->channels    = avio_r8(pb) & 0xF;                                         // 0.0
/*70  */     st->codecpar->bit_rate    = st->codecpar->channels * st->codecpar->sample_rate * 8LL;  // 0.0
/*72  */     if (!st->codecpar->channels)                                                           // 0.0
/*74  */         return AVERROR_INVALIDDATA;                                                        // 0.0
/*78  */     avio_skip(pb, 3);                                                                      // 0.0
/*80  */     channel_assign         = avio_rb32(pb);                                                // 0.0
/*82  */     if (!(channel_assign & 1)) {                                                           // 0.0
/*84  */         int i;                                                                             // 0.0
/*86  */         for (i = 1; i < 32; i++)                                                           // 0.0
/*88  */             if (channel_assign & (1 << i))                                                 // 0.0
/*90  */                 st->codecpar->channel_layout |= wsd_to_av_channel_layoyt(s, i);            // 0.0
/*92  */     }                                                                                      // 0.0
/*96  */     avio_skip(pb, 16);                                                                     // 0.0
/*98  */     if (avio_rb32(pb))                                                                     // 0.0
/*100 */        avpriv_request_sample(s, "emphasis");                                               // 0.0
/*104 */     if (avio_seek(pb, text_offset, SEEK_SET) >= 0) {                                       // 0.0
/*106 */         get_metadata(s, "title",       128);                                               // 0.0
/*108 */         get_metadata(s, "composer",    128);                                               // 0.0
/*110 */         get_metadata(s, "song_writer", 128);                                               // 0.0
/*112 */         get_metadata(s, "artist",      128);                                               // 0.0
/*114 */         get_metadata(s, "album",       128);                                               // 0.0
/*116 */         get_metadata(s, "genre",        32);                                               // 0.0
/*118 */         get_metadata(s, "date",         32);                                               // 0.0
/*120 */         get_metadata(s, "location",     32);                                               // 0.0
/*122 */         get_metadata(s, "comment",     512);                                               // 0.0
/*124 */         get_metadata(s, "user",        512);                                               // 0.0
/*126 */     }                                                                                      // 0.0
/*130 */     return avio_seek(pb, data_offset, SEEK_SET);                                           // 0.0
/*132 */ }                                                                                          // 0.0
