// commit message FFmpeg@0dbb48d91e (target=1, prob=0.31161177, correct=False): better and simpler logic for MPEG muxing - fixed rare MPEG muxing PTS generation bug (stuffing is added in such rare cases) - fixed AC3 payload size generation - generate correct AC3 frame header (need spec checking)
/*0   */ static int mpeg_mux_init(AVFormatContext *ctx)                       // (12) 0.03125
/*2   */ {                                                                    // (31) 0.001954
/*4   */     MpegMuxContext *s = ctx->priv_data;                              // (10) 0.03516
/*6   */     int bitrate, i, mpa_id, mpv_id, ac3_id;                          // (2) 0.04687
/*8   */     AVStream *st;                                                    // (26) 0.01563
/*10  */     StreamInfo *stream;                                              // (27) 0.01562
/*14  */     s->packet_number = 0;                                            // (20) 0.02344
/*16  */     s->is_vcd = (ctx->oformat == &mpeg1vcd_mux);                     // (1) 0.04883
/*18  */     s->is_mpeg2 = (ctx->oformat == &mpeg2vob_mux);                   // (0) 0.04883
/*20  */                                                                      // (30) 0.007812
/*22  */     if (s->is_vcd)                                                   // (22) 0.02344
/*24  */         s->packet_size = 2324; /* VCD packet size */                 // (3) 0.04492
/*26  */     else                                                             // (29) 0.007812
/*28  */         s->packet_size = 2048;                                       // (13) 0.03125
/*30  */                                                                      // (28) 0.01562
/*32  */     /* startcode(4) + length(2) + flags(1) */                        // (7) 0.03907
/*34  */     s->packet_data_max_size = s->packet_size - 7;                    // (4) 0.04492
/*36  */     if (s->is_mpeg2)                                                 // (19) 0.02344
/*38  */         s->packet_data_max_size -= 2;                                // (9) 0.03906
/*40  */     s->audio_bound = 0;                                              // (23) 0.02148
/*42  */     s->video_bound = 0;                                              // (24) 0.02148
/*44  */     mpa_id = AUDIO_ID;                                               // (17) 0.02539
/*46  */     ac3_id = 0x80;                                                   // (21) 0.02344
/*48  */     mpv_id = VIDEO_ID;                                               // (18) 0.02344
/*50  */     s->scr_stream_index = -1;                                        // (15) 0.0293
/*52  */     for(i=0;i<ctx->nb_streams;i++) {                                 // (5) 0.04102
/*54  */         st = ctx->streams[i];                                        // (11) 0.0332
/*56  */         stream = av_mallocz(sizeof(StreamInfo));                     // (6) 0.04102
/*58  */         if (!stream)                                                 // (25) 0.02148
/*60  */             goto fail;                                               // (16) 0.02734
/*62  */         st->priv_data = stream;                                      // (14) 0.0293
/*66  */         switch(st->codec.codec_type) {                               // (8) 0.03906
/*68  */         case CODEC_TYPE_AUDIO:                                       // 0.0
/*70  */             if (st->codec.codec_id == CODEC_ID_AC3)                  // 0.0
/*72  */                 stream->id = ac3_id++;                               // 0.0
/*74  */             else                                                     // 0.0
/*76  */                 stream->id = mpa_id++;                               // 0.0
/*78  */             stream->max_buffer_size = 4 * 1024;                      // 0.0
/*80  */             s->audio_bound++;                                        // 0.0
/*82  */             break;                                                   // 0.0
/*84  */         case CODEC_TYPE_VIDEO:                                       // 0.0
/*86  */             /* by default, video is used for the SCR computation */  // 0.0
/*88  */             if (s->scr_stream_index == -1)                           // 0.0
/*90  */                 s->scr_stream_index = i;                             // 0.0
/*92  */             stream->id = mpv_id++;                                   // 0.0
/*94  */             stream->max_buffer_size = 46 * 1024;                     // 0.0
/*96  */             s->video_bound++;                                        // 0.0
/*98  */             break;                                                   // 0.0
/*100 */         default:                                                     // 0.0
/*102 */             av_abort();                                              // 0.0
/*104 */         }                                                            // 0.0
/*106 */     }                                                                // 0.0
/*108 */     /* if no SCR, use first stream (audio) */                        // 0.0
/*110 */     if (s->scr_stream_index == -1)                                   // 0.0
/*112 */         s->scr_stream_index = 0;                                     // 0.0
/*116 */     /* we increase slightly the bitrate to take into account the     // 0.0
/*118 */        headers. XXX: compute it exactly */                           // 0.0
/*120 */     bitrate = 2000;                                                  // 0.0
/*122 */     for(i=0;i<ctx->nb_streams;i++) {                                 // 0.0
/*124 */         st = ctx->streams[i];                                        // 0.0
/*126 */         bitrate += st->codec.bit_rate;                               // 0.0
/*128 */     }                                                                // 0.0
/*130 */     s->mux_rate = (bitrate + (8 * 50) - 1) / (8 * 50);               // 0.0
/*132 */                                                                      // 0.0
/*134 */     if (s->is_vcd || s->is_mpeg2)                                    // 0.0
/*136 */         /* every packet */                                           // 0.0
/*138 */         s->pack_header_freq = 1;                                     // 0.0
/*140 */     else                                                             // 0.0
/*142 */         /* every 2 seconds */                                        // 0.0
/*144 */         s->pack_header_freq = 2 * bitrate / s->packet_size / 8;      // 0.0
/*148 */     /* the above seems to make pack_header_freq zero sometimes */    // 0.0
/*150 */     if (s->pack_header_freq == 0)                                    // 0.0
/*152 */        s->pack_header_freq = 1;                                      // 0.0
/*154 */                                                                      // 0.0
/*156 */     if (s->is_mpeg2)                                                 // 0.0
/*158 */         /* every 200 packets. Need to look at the spec.  */          // 0.0
/*160 */         s->system_header_freq = s->pack_header_freq * 40;            // 0.0
/*162 */     else if (s->is_vcd)                                              // 0.0
/*164 */         /* every 40 packets, this is my invention */                 // 0.0
/*166 */         s->system_header_freq = s->pack_header_freq * 40;            // 0.0
/*168 */     else                                                             // 0.0
/*170 */         s->system_header_freq = s->pack_header_freq * 5;             // 0.0
/*172 */                                                                      // 0.0
/*174 */     for(i=0;i<ctx->nb_streams;i++) {                                 // 0.0
/*176 */         stream = ctx->streams[i]->priv_data;                         // 0.0
/*178 */         stream->buffer_ptr = 0;                                      // 0.0
/*180 */         stream->packet_number = 0;                                   // 0.0
/*182 */         stream->start_pts = AV_NOPTS_VALUE;                          // 0.0
/*184 */         stream->start_dts = AV_NOPTS_VALUE;                          // 0.0
/*186 */     }                                                                // 0.0
/*188 */     s->last_scr = 0;                                                 // 0.0
/*190 */     return 0;                                                        // 0.0
/*192 */  fail:                                                               // 0.0
/*194 */     for(i=0;i<ctx->nb_streams;i++) {                                 // 0.0
/*196 */         av_free(ctx->streams[i]->priv_data);                         // 0.0
/*198 */     }                                                                // 0.0
/*200 */     return -ENOMEM;                                                  // 0.0
/*202 */ }                                                                    // 0.0
