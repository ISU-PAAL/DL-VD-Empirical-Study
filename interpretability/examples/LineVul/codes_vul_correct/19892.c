// commit message FFmpeg@e3123856c7 (target=1, prob=0.56562984, correct=True): vqa: fix double free on corrupted streams
/*0   */ static int wsvqa_read_header(AVFormatContext *s,                                           // (15) 0.03125
/*2   */                              AVFormatParameters *ap)                                       // (1) 0.06641
/*4   */ {                                                                                          // (26) 0.001953
/*6   */     WsVqaDemuxContext *wsvqa = s->priv_data;                                               // (6) 0.04102
/*8   */     AVIOContext *pb = s->pb;                                                               // (19) 0.02539
/*10  */     AVStream *st;                                                                          // (23) 0.01563
/*12  */     unsigned char *header;                                                                 // (24) 0.01562
/*14  */     unsigned char scratch[VQA_PREAMBLE_SIZE];                                              // (12) 0.0332
/*16  */     unsigned int chunk_tag;                                                                // (22) 0.01758
/*18  */     unsigned int chunk_size;                                                               // (21) 0.01758
/*22  */     /* initialize the video decoder stream */                                              // (20) 0.02148
/*24  */     st = av_new_stream(s, 0);                                                              // (18) 0.0293
/*26  */     if (!st)                                                                               // (25) 0.01367
/*28  */         return AVERROR(ENOMEM);                                                            // (16) 0.03125
/*30  */     av_set_pts_info(st, 33, 1, VQA_FRAMERATE);                                             // (3) 0.05273
/*32  */     wsvqa->video_stream_index = st->index;                                                 // (13) 0.0332
/*34  */     st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                                            // (7) 0.04102
/*36  */     st->codec->codec_id = CODEC_ID_WS_VQA;                                                 // (4) 0.04883
/*38  */     st->codec->codec_tag = 0;  /* no fourcc */                                             // (8) 0.04102
/*42  */     /* skip to the start of the VQA header */                                              // (17) 0.0293
/*44  */     avio_seek(pb, 20, SEEK_SET);                                                           // (10) 0.0332
/*48  */     /* the VQA header needs to go to the decoder */                                        // (11) 0.0332
/*50  */     st->codec->extradata_size = VQA_HEADER_SIZE;                                           // (5) 0.04492
/*52  */     st->codec->extradata = av_mallocz(VQA_HEADER_SIZE + FF_INPUT_BUFFER_PADDING_SIZE);     // (0) 0.08008
/*54  */     header = (unsigned char *)st->codec->extradata;                                        // (9) 0.03516
/*56  */     if (avio_read(pb, st->codec->extradata, VQA_HEADER_SIZE) !=                            // (2) 0.06055
/*58  */         VQA_HEADER_SIZE) {                                                                 // (14) 0.0332
/*60  */         av_free(st->codec->extradata);                                                     // 0.0
/*62  */         return AVERROR(EIO);                                                               // 0.0
/*64  */     }                                                                                      // 0.0
/*66  */     st->codec->width = AV_RL16(&header[6]);                                                // 0.0
/*68  */     st->codec->height = AV_RL16(&header[8]);                                               // 0.0
/*72  */     /* initialize the audio decoder stream for VQA v1 or nonzero samplerate */             // 0.0
/*74  */     if (AV_RL16(&header[24]) || (AV_RL16(&header[0]) == 1 && AV_RL16(&header[2]) == 1)) {  // 0.0
/*76  */         st = av_new_stream(s, 0);                                                          // 0.0
/*78  */         if (!st)                                                                           // 0.0
/*80  */             return AVERROR(ENOMEM);                                                        // 0.0
/*82  */         av_set_pts_info(st, 33, 1, VQA_FRAMERATE);                                         // 0.0
/*84  */         st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                        // 0.0
/*86  */         if (AV_RL16(&header[0]) == 1)                                                      // 0.0
/*88  */             st->codec->codec_id = CODEC_ID_WESTWOOD_SND1;                                  // 0.0
/*90  */         else                                                                               // 0.0
/*92  */             st->codec->codec_id = CODEC_ID_ADPCM_IMA_WS;                                   // 0.0
/*94  */         st->codec->codec_tag = 0;  /* no tag */                                            // 0.0
/*96  */         st->codec->sample_rate = AV_RL16(&header[24]);                                     // 0.0
/*98  */         if (!st->codec->sample_rate)                                                       // 0.0
/*100 */             st->codec->sample_rate = 22050;                                                // 0.0
/*102 */         st->codec->channels = header[26];                                                  // 0.0
/*104 */         if (!st->codec->channels)                                                          // 0.0
/*106 */             st->codec->channels = 1;                                                       // 0.0
/*108 */         st->codec->bits_per_coded_sample = 16;                                             // 0.0
/*110 */         st->codec->bit_rate = st->codec->channels * st->codec->sample_rate *               // 0.0
/*112 */             st->codec->bits_per_coded_sample / 4;                                          // 0.0
/*114 */         st->codec->block_align = st->codec->channels * st->codec->bits_per_coded_sample;   // 0.0
/*118 */         wsvqa->audio_stream_index = st->index;                                             // 0.0
/*120 */         wsvqa->audio_samplerate = st->codec->sample_rate;                                  // 0.0
/*122 */         wsvqa->audio_channels = st->codec->channels;                                       // 0.0
/*124 */         wsvqa->audio_frame_counter = 0;                                                    // 0.0
/*126 */     }                                                                                      // 0.0
/*130 */     /* there are 0 or more chunks before the FINF chunk; iterate until                     // 0.0
/*132 */      * FINF has been skipped and the file will be ready to be demuxed */                   // 0.0
/*134 */     do {                                                                                   // 0.0
/*136 */         if (avio_read(pb, scratch, VQA_PREAMBLE_SIZE) != VQA_PREAMBLE_SIZE) {              // 0.0
/*138 */             av_free(st->codec->extradata);                                                 // 0.0
/*140 */             return AVERROR(EIO);                                                           // 0.0
/*142 */         }                                                                                  // 0.0
/*144 */         chunk_tag = AV_RB32(&scratch[0]);                                                  // 0.0
/*146 */         chunk_size = AV_RB32(&scratch[4]);                                                 // 0.0
/*150 */         /* catch any unknown header tags, for curiousity */                                // 0.0
/*152 */         switch (chunk_tag) {                                                               // 0.0
/*154 */         case CINF_TAG:                                                                     // 0.0
/*156 */         case CINH_TAG:                                                                     // 0.0
/*158 */         case CIND_TAG:                                                                     // 0.0
/*160 */         case PINF_TAG:                                                                     // 0.0
/*162 */         case PINH_TAG:                                                                     // 0.0
/*164 */         case PIND_TAG:                                                                     // 0.0
/*166 */         case FINF_TAG:                                                                     // 0.0
/*168 */         case CMDS_TAG:                                                                     // 0.0
/*170 */             break;                                                                         // 0.0
/*174 */         default:                                                                           // 0.0
/*176 */             av_log (s, AV_LOG_ERROR, " note: unknown chunk seen (%c%c%c%c)\n",             // 0.0
/*178 */                 scratch[0], scratch[1],                                                    // 0.0
/*180 */                 scratch[2], scratch[3]);                                                   // 0.0
/*182 */             break;                                                                         // 0.0
/*184 */         }                                                                                  // 0.0
/*188 */         avio_skip(pb, chunk_size);                                                         // 0.0
/*190 */     } while (chunk_tag != FINF_TAG);                                                       // 0.0
/*194 */     return 0;                                                                              // 0.0
/*196 */ }                                                                                          // 0.0
