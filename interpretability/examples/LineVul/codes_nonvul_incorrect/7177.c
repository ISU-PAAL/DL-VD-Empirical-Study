// commit message FFmpeg@ba15aab4a4 (target=0, prob=0.76894706, correct=False): libavformat/mtv: make clear we assume bpp is always 16
/*0   */ static int mtv_read_header(AVFormatContext *s)                                                                                       // (15) 0.0293
/*2   */ {                                                                                                                                    // (22) 0.00196
/*4   */     MTVDemuxContext *mtv = s->priv_data;                                                                                             // (13) 0.0332
/*6   */     AVIOContext   *pb  = s->pb;                                                                                                      // (14) 0.03125
/*8   */     AVStream        *st;                                                                                                             // (16) 0.0293
/*10  */     unsigned int    audio_subsegments;                                                                                               // (18) 0.02735
/*14  */     avio_skip(pb, 3);                                                                                                                // (20) 0.02344
/*16  */     mtv->file_size         = avio_rl32(pb);                                                                                          // (5) 0.05078
/*18  */     mtv->segments          = avio_rl32(pb);                                                                                          // (4) 0.05078
/*20  */     avio_skip(pb, 32);                                                                                                               // (21) 0.02344
/*22  */     mtv->audio_identifier  = avio_rl24(pb);                                                                                          // (10) 0.03906
/*24  */     mtv->audio_br          = avio_rl16(pb);                                                                                          // (3) 0.05273
/*26  */     mtv->img_colorfmt      = avio_rl24(pb);                                                                                          // (8) 0.04883
/*28  */     mtv->img_bpp           = avio_r8(pb);                                                                                            // (2) 0.05664
/*30  */     mtv->img_width         = avio_rl16(pb);                                                                                          // (6) 0.05078
/*32  */     mtv->img_height        = avio_rl16(pb);                                                                                          // (7) 0.04883
/*34  */     mtv->img_segment_size  = avio_rl16(pb);                                                                                          // (9) 0.04297
/*38  */     /* Calculate width and height if missing from header */                                                                          // (19) 0.02734
/*42  */     if(mtv->img_bpp>>3){                                                                                                             // (17) 0.0293
/*44  */     if(!mtv->img_width && mtv->img_height)                                                                                           // (11) 0.03906
/*46  */         mtv->img_width=mtv->img_segment_size / (mtv->img_bpp>>3)                                                                     // (0) 0.06836
/*48  */                         / mtv->img_height;                                                                                           // (1) 0.06054
/*52  */     if(!mtv->img_height && mtv->img_width)                                                                                           // (12) 0.03906
/*54  */         mtv->img_height=mtv->img_segment_size / (mtv->img_bpp>>3)                                                                    // 0.0
/*56  */                         / mtv->img_width;                                                                                            // 0.0
/*58  */     }                                                                                                                                // 0.0
/*60  */     if(!mtv->img_height || !mtv->img_width || !mtv->img_segment_size){                                                               // 0.0
/*62  */         av_log(s, AV_LOG_ERROR, "width or height or segment_size is invalid and I cannot calculate them from other information\n");  // 0.0
/*64  */         return AVERROR(EINVAL);                                                                                                      // 0.0
/*66  */     }                                                                                                                                // 0.0
/*70  */     avio_skip(pb, 4);                                                                                                                // 0.0
/*72  */     audio_subsegments = avio_rl16(pb);                                                                                               // 0.0
/*76  */     if (audio_subsegments == 0) {                                                                                                    // 0.0
/*78  */         avpriv_request_sample(s, "MTV files without audio");                                                                         // 0.0
/*80  */         return AVERROR_PATCHWELCOME;                                                                                                 // 0.0
/*82  */     }                                                                                                                                // 0.0
/*86  */     mtv->full_segment_size =                                                                                                         // 0.0
/*88  */         audio_subsegments * (MTV_AUDIO_PADDING_SIZE + MTV_ASUBCHUNK_DATA_SIZE) +                                                     // 0.0
/*90  */         mtv->img_segment_size;                                                                                                       // 0.0
/*92  */     mtv->video_fps         = (mtv->audio_br / 4) / audio_subsegments;                                                                // 0.0
/*96  */     // FIXME Add sanity check here                                                                                                   // 0.0
/*100 */     // all systems go! init decoders                                                                                                 // 0.0
/*104 */     // video - raw rgb565                                                                                                            // 0.0
/*108 */     st = avformat_new_stream(s, NULL);                                                                                               // 0.0
/*110 */     if(!st)                                                                                                                          // 0.0
/*112 */         return AVERROR(ENOMEM);                                                                                                      // 0.0
/*116 */     avpriv_set_pts_info(st, 64, 1, mtv->video_fps);                                                                                  // 0.0
/*118 */     st->codec->codec_type      = AVMEDIA_TYPE_VIDEO;                                                                                 // 0.0
/*120 */     st->codec->codec_id        = AV_CODEC_ID_RAWVIDEO;                                                                               // 0.0
/*122 */     st->codec->pix_fmt         = AV_PIX_FMT_RGB565BE;                                                                                // 0.0
/*124 */     st->codec->width           = mtv->img_width;                                                                                     // 0.0
/*126 */     st->codec->height          = mtv->img_height;                                                                                    // 0.0
/*128 */     st->codec->sample_rate     = mtv->video_fps;                                                                                     // 0.0
/*130 */     st->codec->extradata       = av_strdup("BottomUp");                                                                              // 0.0
/*132 */     st->codec->extradata_size  = 9;                                                                                                  // 0.0
/*136 */     // audio - mp3                                                                                                                   // 0.0
/*140 */     st = avformat_new_stream(s, NULL);                                                                                               // 0.0
/*142 */     if(!st)                                                                                                                          // 0.0
/*144 */         return AVERROR(ENOMEM);                                                                                                      // 0.0
/*148 */     avpriv_set_pts_info(st, 64, 1, AUDIO_SAMPLING_RATE);                                                                             // 0.0
/*150 */     st->codec->codec_type      = AVMEDIA_TYPE_AUDIO;                                                                                 // 0.0
/*152 */     st->codec->codec_id        = AV_CODEC_ID_MP3;                                                                                    // 0.0
/*154 */     st->codec->bit_rate        = mtv->audio_br;                                                                                      // 0.0
/*156 */     st->need_parsing           = AVSTREAM_PARSE_FULL;                                                                                // 0.0
/*160 */     // Jump over header                                                                                                              // 0.0
/*164 */     if(avio_seek(pb, MTV_HEADER_SIZE, SEEK_SET) != MTV_HEADER_SIZE)                                                                  // 0.0
/*166 */         return AVERROR(EIO);                                                                                                         // 0.0
/*170 */     return 0;                                                                                                                        // 0.0
/*174 */ }                                                                                                                                    // 0.0
