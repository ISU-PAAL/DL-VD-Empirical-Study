// commit message FFmpeg@c58d45e004 (target=1, prob=0.5554252, correct=True): segafilm: Fix potential division by 0 on corrupted segafilm streams in the demuxer.
/*0   */ static int film_read_header(AVFormatContext *s,                                   // (16) 0.02734
/*2   */                             AVFormatParameters *ap)                               // (0) 0.06445
/*4   */ {                                                                                 // (30) 0.001954
/*6   */     FilmDemuxContext *film = s->priv_data;                                        // (11) 0.03125
/*8   */     AVIOContext *pb = s->pb;                                                      // (18) 0.02539
/*10  */     AVStream *st;                                                                 // (27) 0.01562
/*12  */     unsigned char scratch[256];                                                   // (26) 0.01758
/*14  */     int i;                                                                        // (28) 0.01172
/*16  */     unsigned int data_offset;                                                     // (25) 0.01758
/*18  */     unsigned int audio_frame_counter;                                             // (21) 0.02149
/*22  */     film->sample_table = NULL;                                                    // (22) 0.02148
/*24  */     film->stereo_buffer = NULL;                                                   // (20) 0.02344
/*26  */     film->stereo_buffer_size = 0;                                                 // (17) 0.02734
/*30  */     /* load the main FILM header */                                               // (24) 0.02148
/*32  */     if (avio_read(pb, scratch, 16) != 16)                                         // (6) 0.03711
/*34  */         return AVERROR(EIO);                                                      // (15) 0.0293
/*36  */     data_offset = AV_RB32(&scratch[4]);                                           // (9) 0.0332
/*38  */     film->version = AV_RB32(&scratch[8]);                                         // (10) 0.0332
/*42  */     /* load the FDSC chunk */                                                     // (23) 0.02148
/*44  */     if (film->version == 0) {                                                     // (19) 0.02344
/*46  */         /* special case for Lemmings .film files; 20-byte header */               // (2) 0.04492
/*48  */         if (avio_read(pb, scratch, 20) != 20)                                     // (4) 0.04492
/*50  */             return AVERROR(EIO);                                                  // (7) 0.03711
/*52  */         /* make some assumptions about the audio parameters */                    // (13) 0.03125
/*54  */         film->audio_type = CODEC_ID_PCM_S8;                                       // (1) 0.04883
/*56  */         film->audio_samplerate = 22050;                                           // (8) 0.03516
/*58  */         film->audio_channels = 1;                                                 // (12) 0.03125
/*60  */         film->audio_bits = 8;                                                     // (14) 0.0293
/*62  */     } else {                                                                      // (29) 0.01172
/*64  */         /* normal Saturn .cpk files; 32-byte header */                            // (5) 0.03907
/*66  */         if (avio_read(pb, scratch, 32) != 32)                                     // (3) 0.04492
/*68  */             return AVERROR(EIO);                                                  // 0.0
/*70  */         film->audio_samplerate = AV_RB16(&scratch[24]);                           // 0.0
/*72  */         film->audio_channels = scratch[21];                                       // 0.0
/*74  */         film->audio_bits = scratch[22];                                           // 0.0
/*76  */         if (scratch[23] == 2)                                                     // 0.0
/*78  */             film->audio_type = CODEC_ID_ADPCM_ADX;                                // 0.0
/*80  */         else if (film->audio_bits == 8)                                           // 0.0
/*82  */             film->audio_type = CODEC_ID_PCM_S8;                                   // 0.0
/*84  */         else if (film->audio_bits == 16)                                          // 0.0
/*86  */             film->audio_type = CODEC_ID_PCM_S16BE;                                // 0.0
/*88  */         else                                                                      // 0.0
/*90  */             film->audio_type = CODEC_ID_NONE;                                     // 0.0
/*92  */     }                                                                             // 0.0
/*96  */     if (AV_RB32(&scratch[0]) != FDSC_TAG)                                         // 0.0
/*98  */         return AVERROR_INVALIDDATA;                                               // 0.0
/*102 */     if (AV_RB32(&scratch[8]) == CVID_TAG) {                                       // 0.0
/*104 */         film->video_type = CODEC_ID_CINEPAK;                                      // 0.0
/*106 */     } else                                                                        // 0.0
/*108 */         film->video_type = CODEC_ID_NONE;                                         // 0.0
/*112 */     /* initialize the decoder streams */                                          // 0.0
/*114 */     if (film->video_type) {                                                       // 0.0
/*116 */         st = av_new_stream(s, 0);                                                 // 0.0
/*118 */         if (!st)                                                                  // 0.0
/*120 */             return AVERROR(ENOMEM);                                               // 0.0
/*122 */         film->video_stream_index = st->index;                                     // 0.0
/*124 */         st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                               // 0.0
/*126 */         st->codec->codec_id = film->video_type;                                   // 0.0
/*128 */         st->codec->codec_tag = 0;  /* no fourcc */                                // 0.0
/*130 */         st->codec->width = AV_RB32(&scratch[16]);                                 // 0.0
/*132 */         st->codec->height = AV_RB32(&scratch[12]);                                // 0.0
/*134 */     }                                                                             // 0.0
/*138 */     if (film->audio_type) {                                                       // 0.0
/*140 */         st = av_new_stream(s, 0);                                                 // 0.0
/*142 */         if (!st)                                                                  // 0.0
/*144 */             return AVERROR(ENOMEM);                                               // 0.0
/*146 */         film->audio_stream_index = st->index;                                     // 0.0
/*148 */         st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                               // 0.0
/*150 */         st->codec->codec_id = film->audio_type;                                   // 0.0
/*152 */         st->codec->codec_tag = 1;                                                 // 0.0
/*154 */         st->codec->channels = film->audio_channels;                               // 0.0
/*156 */         st->codec->sample_rate = film->audio_samplerate;                          // 0.0
/*160 */         if (film->audio_type == CODEC_ID_ADPCM_ADX) {                             // 0.0
/*162 */             st->codec->bits_per_coded_sample = 18 * 8 / 32;                       // 0.0
/*164 */             st->codec->block_align = st->codec->channels * 18;                    // 0.0
/*166 */         } else {                                                                  // 0.0
/*168 */             st->codec->bits_per_coded_sample = film->audio_bits;                  // 0.0
/*170 */             st->codec->block_align = st->codec->channels *                        // 0.0
/*172 */                 st->codec->bits_per_coded_sample / 8;                             // 0.0
/*174 */         }                                                                         // 0.0
/*178 */         st->codec->bit_rate = st->codec->channels * st->codec->sample_rate *      // 0.0
/*180 */             st->codec->bits_per_coded_sample;                                     // 0.0
/*182 */     }                                                                             // 0.0
/*186 */     /* load the sample table */                                                   // 0.0
/*188 */     if (avio_read(pb, scratch, 16) != 16)                                         // 0.0
/*190 */         return AVERROR(EIO);                                                      // 0.0
/*192 */     if (AV_RB32(&scratch[0]) != STAB_TAG)                                         // 0.0
/*194 */         return AVERROR_INVALIDDATA;                                               // 0.0
/*196 */     film->base_clock = AV_RB32(&scratch[8]);                                      // 0.0
/*198 */     film->sample_count = AV_RB32(&scratch[12]);                                   // 0.0
/*200 */     if(film->sample_count >= UINT_MAX / sizeof(film_sample))                      // 0.0
/*202 */         return -1;                                                                // 0.0
/*204 */     film->sample_table = av_malloc(film->sample_count * sizeof(film_sample));     // 0.0
/*206 */     if (!film->sample_table)                                                      // 0.0
/*208 */         return AVERROR(ENOMEM);                                                   // 0.0
/*212 */     for(i=0; i<s->nb_streams; i++)                                                // 0.0
/*214 */         av_set_pts_info(s->streams[i], 33, 1, film->base_clock);                  // 0.0
/*218 */     audio_frame_counter = 0;                                                      // 0.0
/*220 */     for (i = 0; i < film->sample_count; i++) {                                    // 0.0
/*222 */         /* load the next sample record and transfer it to an internal struct */   // 0.0
/*224 */         if (avio_read(pb, scratch, 16) != 16) {                                   // 0.0
/*226 */             av_free(film->sample_table);                                          // 0.0
/*228 */             return AVERROR(EIO);                                                  // 0.0
/*230 */         }                                                                         // 0.0
/*232 */         film->sample_table[i].sample_offset =                                     // 0.0
/*234 */             data_offset + AV_RB32(&scratch[0]);                                   // 0.0
/*236 */         film->sample_table[i].sample_size = AV_RB32(&scratch[4]);                 // 0.0
/*238 */         if (AV_RB32(&scratch[8]) == 0xFFFFFFFF) {                                 // 0.0
/*240 */             film->sample_table[i].stream = film->audio_stream_index;              // 0.0
/*242 */             film->sample_table[i].pts = audio_frame_counter;                      // 0.0
/*244 */             film->sample_table[i].pts *= film->base_clock;                        // 0.0
/*246 */             film->sample_table[i].pts /= film->audio_samplerate;                  // 0.0
/*250 */             if (film->audio_type == CODEC_ID_ADPCM_ADX)                           // 0.0
/*252 */                 audio_frame_counter += (film->sample_table[i].sample_size * 32 /  // 0.0
/*254 */                     (18 * film->audio_channels));                                 // 0.0
/*256 */             else                                                                  // 0.0
/*258 */                 audio_frame_counter += (film->sample_table[i].sample_size /       // 0.0
/*260 */                     (film->audio_channels * film->audio_bits / 8));               // 0.0
/*262 */         } else {                                                                  // 0.0
/*264 */             film->sample_table[i].stream = film->video_stream_index;              // 0.0
/*266 */             film->sample_table[i].pts = AV_RB32(&scratch[8]) & 0x7FFFFFFF;        // 0.0
/*268 */             film->sample_table[i].keyframe = (scratch[8] & 0x80) ? 0 : 1;         // 0.0
/*270 */         }                                                                         // 0.0
/*272 */     }                                                                             // 0.0
/*276 */     film->current_sample = 0;                                                     // 0.0
/*280 */     return 0;                                                                     // 0.0
/*282 */ }                                                                                 // 0.0
