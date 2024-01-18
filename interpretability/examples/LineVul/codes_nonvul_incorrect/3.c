// commit message FFmpeg@32bf6550cb (target=0, prob=0.5876859, correct=False): avformat/riffdec: Initialize bitrate
/*0   */ int ff_get_wav_header(AVFormatContext *s, AVIOContext *pb,                                  // (10) 0.04102
/*2   */                       AVCodecContext *codec, int size, int big_endian)                      // (0) 0.07422
/*4   */ {                                                                                           // (24) 0.001953
/*6   */     int id;                                                                                 // (20) 0.01172
/*8   */     uint64_t bitrate;                                                                       // (18) 0.01953
/*12  */     if (size < 14) {                                                                        // (17) 0.01953
/*14  */         avpriv_request_sample(codec, "wav header size < 14");                               // (8) 0.04687
/*16  */         return AVERROR_INVALIDDATA;                                                         // (14) 0.0332
/*18  */     }                                                                                       // (22) 0.007812
/*22  */     codec->codec_type  = AVMEDIA_TYPE_AUDIO;                                                // (13) 0.03906
/*24  */     if (!big_endian) {                                                                      // (16) 0.02148
/*26  */         id                 = avio_rl16(pb);                                                 // (2) 0.06445
/*28  */         if (id != 0x0165) {                                                                 // (15) 0.0332
/*30  */             codec->channels    = avio_rl16(pb);                                             // (5) 0.05273
/*32  */             codec->sample_rate = avio_rl32(pb);                                             // (7) 0.04883
/*34  */             bitrate            = avio_rl32(pb) * 8LL;                                       // (1) 0.07227
/*36  */             codec->block_align = avio_rl16(pb);                                             // (6) 0.04883
/*38  */         }                                                                                   // (19) 0.01562
/*40  */     } else {                                                                                // (21) 0.01172
/*42  */         id                 = avio_rb16(pb);                                                 // (4) 0.06445
/*44  */         codec->channels    = avio_rb16(pb);                                                 // (9) 0.04492
/*46  */         codec->sample_rate = avio_rb32(pb);                                                 // (12) 0.04102
/*48  */         bitrate            = avio_rb32(pb) * 8LL;                                           // (3) 0.06445
/*50  */         codec->block_align = avio_rb16(pb);                                                 // (11) 0.04102
/*52  */     }                                                                                       // (23) 0.007812
/*54  */     if (size == 14) {  /* We're dealing with plain vanilla WAVEFORMAT */                    // 0.0
/*56  */         codec->bits_per_coded_sample = 8;                                                   // 0.0
/*58  */     } else {                                                                                // 0.0
/*60  */         if (!big_endian) {                                                                  // 0.0
/*62  */             codec->bits_per_coded_sample = avio_rl16(pb);                                   // 0.0
/*64  */         } else {                                                                            // 0.0
/*66  */             codec->bits_per_coded_sample = avio_rb16(pb);                                   // 0.0
/*68  */         }                                                                                   // 0.0
/*70  */     }                                                                                       // 0.0
/*72  */     if (id == 0xFFFE) {                                                                     // 0.0
/*74  */         codec->codec_tag = 0;                                                               // 0.0
/*76  */     } else {                                                                                // 0.0
/*78  */         codec->codec_tag = id;                                                              // 0.0
/*80  */         codec->codec_id  = ff_wav_codec_get_id(id,                                          // 0.0
/*82  */                                                codec->bits_per_coded_sample);               // 0.0
/*84  */     }                                                                                       // 0.0
/*86  */     if (size >= 18 && id != 0x0165) {  /* We're obviously dealing with WAVEFORMATEX */      // 0.0
/*88  */         int cbSize = avio_rl16(pb); /* cbSize */                                            // 0.0
/*90  */         if (big_endian) {                                                                   // 0.0
/*92  */             avpriv_report_missing_feature(codec, "WAVEFORMATEX support for RIFX files\n");  // 0.0
/*94  */             return AVERROR_PATCHWELCOME;                                                    // 0.0
/*96  */         }                                                                                   // 0.0
/*98  */         size  -= 18;                                                                        // 0.0
/*100 */         cbSize = FFMIN(size, cbSize);                                                       // 0.0
/*102 */         if (cbSize >= 22 && id == 0xfffe) { /* WAVEFORMATEXTENSIBLE */                      // 0.0
/*104 */             parse_waveformatex(pb, codec);                                                  // 0.0
/*106 */             cbSize -= 22;                                                                   // 0.0
/*108 */             size   -= 22;                                                                   // 0.0
/*110 */         }                                                                                   // 0.0
/*112 */         if (cbSize > 0) {                                                                   // 0.0
/*114 */             av_freep(&codec->extradata);                                                    // 0.0
/*116 */             if (ff_get_extradata(codec, pb, cbSize) < 0)                                    // 0.0
/*118 */                 return AVERROR(ENOMEM);                                                     // 0.0
/*120 */             size -= cbSize;                                                                 // 0.0
/*122 */         }                                                                                   // 0.0
/*126 */         /* It is possible for the chunk to contain garbage at the end */                    // 0.0
/*128 */         if (size > 0)                                                                       // 0.0
/*130 */             avio_skip(pb, size);                                                            // 0.0
/*132 */     } else if (id == 0x0165 && size >= 32) {                                                // 0.0
/*134 */         int nb_streams, i;                                                                  // 0.0
/*138 */         size -= 4;                                                                          // 0.0
/*140 */         av_freep(&codec->extradata);                                                        // 0.0
/*142 */         if (ff_get_extradata(codec, pb, size) < 0)                                          // 0.0
/*144 */             return AVERROR(ENOMEM);                                                         // 0.0
/*146 */         nb_streams         = AV_RL16(codec->extradata + 4);                                 // 0.0
/*148 */         codec->sample_rate = AV_RL32(codec->extradata + 12);                                // 0.0
/*150 */         codec->channels    = 0;                                                             // 0.0
/*152 */         bitrate            = 0;                                                             // 0.0
/*154 */         if (size < 8 + nb_streams * 20)                                                     // 0.0
/*156 */             return AVERROR_INVALIDDATA;                                                     // 0.0
/*158 */         for (i = 0; i < nb_streams; i++)                                                    // 0.0
/*160 */             codec->channels += codec->extradata[8 + i * 20 + 17];                           // 0.0
/*162 */     }                                                                                       // 0.0
/*166 */     if (bitrate > INT_MAX) {                                                                // 0.0
/*168 */         if (s->error_recognition & AV_EF_EXPLODE) {                                         // 0.0
/*170 */             av_log(s, AV_LOG_ERROR,                                                         // 0.0
/*172 */                    "The bitrate %"PRIu64" is too large.\n",                                 // 0.0
/*174 */                     bitrate);                                                               // 0.0
/*176 */             return AVERROR_INVALIDDATA;                                                     // 0.0
/*178 */         } else {                                                                            // 0.0
/*180 */             av_log(s, AV_LOG_WARNING,                                                       // 0.0
/*182 */                    "The bitrate %"PRIu64" is too large, resetting to 0.",                   // 0.0
/*184 */                    bitrate);                                                                // 0.0
/*186 */             codec->bit_rate = 0;                                                            // 0.0
/*188 */         }                                                                                   // 0.0
/*190 */     } else {                                                                                // 0.0
/*192 */         codec->bit_rate = bitrate;                                                          // 0.0
/*194 */     }                                                                                       // 0.0
/*198 */     if (codec->sample_rate <= 0) {                                                          // 0.0
/*200 */         av_log(s, AV_LOG_ERROR,                                                             // 0.0
/*202 */                "Invalid sample rate: %d\n", codec->sample_rate);                            // 0.0
/*204 */         return AVERROR_INVALIDDATA;                                                         // 0.0
/*206 */     }                                                                                       // 0.0
/*208 */     if (codec->codec_id == AV_CODEC_ID_AAC_LATM) {                                          // 0.0
/*210 */         /* Channels and sample_rate values are those prior to applying SBR                  // 0.0
/*212 */          * and/or PS. */                                                                    // 0.0
/*214 */         codec->channels    = 0;                                                             // 0.0
/*216 */         codec->sample_rate = 0;                                                             // 0.0
/*218 */     }                                                                                       // 0.0
/*220 */     /* override bits_per_coded_sample for G.726 */                                          // 0.0
/*222 */     if (codec->codec_id == AV_CODEC_ID_ADPCM_G726 && codec->sample_rate)                    // 0.0
/*224 */         codec->bits_per_coded_sample = codec->bit_rate / codec->sample_rate;                // 0.0
/*228 */     return 0;                                                                               // 0.0
/*230 */ }                                                                                           // 0.0
