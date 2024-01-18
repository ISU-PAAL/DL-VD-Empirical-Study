// commit message FFmpeg@073811cdd2 (target=0, prob=0.55458605, correct=False): fix forw_ptr crc check not really beautiful but i did not find a nice solution note, untested
/*0   */ static int decode_stream_header(NUTContext *nut){                                                    // (11) 0.02734
/*2   */     AVFormatContext *s= nut->avf;                                                                    // (12) 0.02734
/*4   */     ByteIOContext *bc = &s->pb;                                                                      // (13) 0.02734
/*6   */     StreamContext *stc;                                                                              // (23) 0.01758
/*8   */     int class, stream_id;                                                                            // (20) 0.01953
/*10  */     uint64_t tmp, end;                                                                               // (19) 0.02148
/*12  */     AVStream *st;                                                                                    // (24) 0.01563
/*16  */     end= get_packetheader(nut, bc, 1);                                                               // (7) 0.0332
/*18  */     end += url_ftell(bc);                                                                            // (16) 0.02344
/*22  */     GET_V(stream_id, tmp < s->nb_streams && !nut->stream[tmp].time_base);                            // (4) 0.06055
/*24  */     stc= &nut->stream[stream_id];                                                                    // (9) 0.0293
/*28  */     st = s->streams[stream_id];                                                                      // (14) 0.02734
/*30  */     if (!st)                                                                                         // (26) 0.01367
/*32  */         return AVERROR(ENOMEM);                                                                      // (8) 0.03125
/*36  */     class = get_v(bc);                                                                               // (18) 0.02148
/*38  */     tmp = get_fourcc(bc);                                                                            // (17) 0.02344
/*40  */     st->codec->codec_tag= tmp;                                                                       // (10) 0.0293
/*42  */     switch(class)                                                                                    // (25) 0.01367
/*44  */     {                                                                                                // (27) 0.007812
/*46  */         case 0:                                                                                      // (22) 0.01953
/*48  */             st->codec->codec_type = CODEC_TYPE_VIDEO;                                                // (6) 0.05664
/*50  */             st->codec->codec_id = codec_get_id(codec_bmp_tags, tmp);                                 // (0) 0.07227
/*52  */             if (st->codec->codec_id == CODEC_ID_NONE)                                                // (3) 0.0625
/*54  */                 av_log(s, AV_LOG_ERROR, "Unknown codec?!\n");                                        // (2) 0.06641
/*56  */             break;                                                                                   // (15) 0.02539
/*58  */         case 1:                                                                                      // (21) 0.01953
/*60  */             st->codec->codec_type = CODEC_TYPE_AUDIO;                                                // (5) 0.05859
/*62  */             st->codec->codec_id = codec_get_id(codec_wav_tags, tmp);                                 // (1) 0.07031
/*64  */             if (st->codec->codec_id == CODEC_ID_NONE)                                                // 0.0
/*66  */                 av_log(s, AV_LOG_ERROR, "Unknown codec?!\n");                                        // 0.0
/*68  */             break;                                                                                   // 0.0
/*70  */         case 2:                                                                                      // 0.0
/*72  */ //            st->codec->codec_type = CODEC_TYPE_TEXT;                                               // 0.0
/*74  */ //            break;                                                                                 // 0.0
/*76  */         case 3:                                                                                      // 0.0
/*78  */             st->codec->codec_type = CODEC_TYPE_DATA;                                                 // 0.0
/*80  */             break;                                                                                   // 0.0
/*82  */         default:                                                                                     // 0.0
/*84  */             av_log(s, AV_LOG_ERROR, "Unknown stream class (%d)\n", class);                           // 0.0
/*86  */             return -1;                                                                               // 0.0
/*88  */     }                                                                                                // 0.0
/*90  */     GET_V(stc->time_base_id    , tmp < nut->time_base_count);                                        // 0.0
/*92  */     GET_V(stc->msb_pts_shift   , tmp < 16);                                                          // 0.0
/*94  */     stc->max_pts_distance= get_v(bc);                                                                // 0.0
/*96  */     GET_V(stc->decode_delay    , tmp < 1000); //sanity limit, raise this if moors law is true        // 0.0
/*98  */     st->codec->has_b_frames= stc->decode_delay;                                                      // 0.0
/*100 */     get_v(bc); //stream flags                                                                        // 0.0
/*104 */     GET_V(st->codec->extradata_size, tmp < (1<<30));                                                 // 0.0
/*106 */     if(st->codec->extradata_size){                                                                   // 0.0
/*108 */         st->codec->extradata= av_mallocz(st->codec->extradata_size + FF_INPUT_BUFFER_PADDING_SIZE);  // 0.0
/*110 */         get_buffer(bc, st->codec->extradata, st->codec->extradata_size);                             // 0.0
/*112 */     }                                                                                                // 0.0
/*116 */     if (st->codec->codec_type == CODEC_TYPE_VIDEO){                                                  // 0.0
/*118 */         GET_V(st->codec->width , tmp > 0)                                                            // 0.0
/*120 */         GET_V(st->codec->height, tmp > 0)                                                            // 0.0
/*122 */         st->codec->sample_aspect_ratio.num= get_v(bc);                                               // 0.0
/*124 */         st->codec->sample_aspect_ratio.den= get_v(bc);                                               // 0.0
/*126 */         if((!st->codec->sample_aspect_ratio.num) != (!st->codec->sample_aspect_ratio.den)){          // 0.0
/*128 */             av_log(s, AV_LOG_ERROR, "invalid aspect ratio\n");                                       // 0.0
/*130 */             return -1;                                                                               // 0.0
/*132 */         }                                                                                            // 0.0
/*134 */         get_v(bc); /* csp type */                                                                    // 0.0
/*136 */     }else if (st->codec->codec_type == CODEC_TYPE_AUDIO){                                            // 0.0
/*138 */         GET_V(st->codec->sample_rate , tmp > 0)                                                      // 0.0
/*140 */         tmp= get_v(bc); // samplerate_den                                                            // 0.0
/*142 */         if(tmp > st->codec->sample_rate){                                                            // 0.0
/*144 */             av_log(s, AV_LOG_ERROR, "bleh, libnut muxed this ;)\n");                                 // 0.0
/*146 */             st->codec->sample_rate= tmp;                                                             // 0.0
/*148 */         }                                                                                            // 0.0
/*150 */         GET_V(st->codec->channels, tmp > 0)                                                          // 0.0
/*152 */     }                                                                                                // 0.0
/*154 */     if(skip_reserved(bc, end) || get_checksum(bc)){                                                  // 0.0
/*156 */         av_log(s, AV_LOG_ERROR, "Stream header %d checksum mismatch\n", stream_id);                  // 0.0
/*158 */         return -1;                                                                                   // 0.0
/*160 */     }                                                                                                // 0.0
/*162 */     stc->time_base= &nut->time_base[stc->time_base_id];                                              // 0.0
/*164 */     av_set_pts_info(s->streams[stream_id], 63, stc->time_base->num, stc->time_base->den);            // 0.0
/*166 */     return 0;                                                                                        // 0.0
/*168 */ }                                                                                                    // 0.0
