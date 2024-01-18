// commit message FFmpeg@55815edca0 (target=0, prob=0.46113098, correct=True): prefer avio_check() over url_exist()
/*0   */ static void build_feed_streams(void)                                                                                      // (20) 0.02148
/*2   */ {                                                                                                                         // (29) 0.001953
/*4   */     FFStream *stream, *feed;                                                                                              // (19) 0.02148
/*6   */     int i;                                                                                                                // (26) 0.01172
/*10  */     /* gather all streams */                                                                                              // (22) 0.01563
/*12  */     for(stream = first_stream; stream != NULL; stream = stream->next) {                                                   // (6) 0.04297
/*14  */         feed = stream->feed;                                                                                              // (12) 0.02539
/*16  */         if (feed) {                                                                                                       // (14) 0.02344
/*18  */             if (!stream->is_feed) {                                                                                       // (9) 0.03906
/*20  */                 /* we handle a stream coming from a feed */                                                               // (4) 0.04883
/*22  */                 for(i=0;i<stream->nb_streams;i++)                                                                         // (2) 0.0625
/*24  */                     stream->feed_streams[i] = add_av_stream(feed, stream->streams[i]);                                    // (0) 0.08594
/*26  */             }                                                                                                             // (15) 0.02344
/*28  */         }                                                                                                                 // (23) 0.01562
/*30  */     }                                                                                                                     // (27) 0.007812
/*34  */     /* gather all streams */                                                                                              // (24) 0.01562
/*36  */     for(stream = first_stream; stream != NULL; stream = stream->next) {                                                   // (7) 0.04297
/*38  */         feed = stream->feed;                                                                                              // (13) 0.02539
/*40  */         if (feed) {                                                                                                       // (16) 0.02344
/*42  */             if (stream->is_feed) {                                                                                        // (10) 0.03906
/*44  */                 for(i=0;i<stream->nb_streams;i++)                                                                         // (1) 0.0625
/*46  */                     stream->feed_streams[i] = i;                                                                          // (3) 0.06055
/*48  */             }                                                                                                             // (17) 0.02344
/*50  */         }                                                                                                                 // (25) 0.01562
/*52  */     }                                                                                                                     // (28) 0.007812
/*56  */     /* create feed files if needed */                                                                                     // (21) 0.01953
/*58  */     for(feed = first_feed; feed != NULL; feed = feed->next_feed) {                                                        // (5) 0.04688
/*60  */         int fd;                                                                                                           // (18) 0.02148
/*64  */         if (url_exist(feed->feed_filename)) {                                                                             // (8) 0.03906
/*66  */             /* See if it matches */                                                                                       // (11) 0.0332
/*68  */             AVFormatContext *s;                                                                                           // 0.0
/*70  */             int matches = 0;                                                                                              // 0.0
/*74  */             if (av_open_input_file(&s, feed->feed_filename, NULL, FFM_PACKET_SIZE, NULL) >= 0) {                          // 0.0
/*76  */                 /* Now see if it matches */                                                                               // 0.0
/*78  */                 if (s->nb_streams == feed->nb_streams) {                                                                  // 0.0
/*80  */                     matches = 1;                                                                                          // 0.0
/*82  */                     for(i=0;i<s->nb_streams;i++) {                                                                        // 0.0
/*84  */                         AVStream *sf, *ss;                                                                                // 0.0
/*86  */                         sf = feed->streams[i];                                                                            // 0.0
/*88  */                         ss = s->streams[i];                                                                               // 0.0
/*92  */                         if (sf->index != ss->index ||                                                                     // 0.0
/*94  */                             sf->id != ss->id) {                                                                           // 0.0
/*96  */                             http_log("Index & Id do not match for stream %d (%s)\n",                                      // 0.0
/*98  */                                    i, feed->feed_filename);                                                               // 0.0
/*100 */                             matches = 0;                                                                                  // 0.0
/*102 */                         } else {                                                                                          // 0.0
/*104 */                             AVCodecContext *ccf, *ccs;                                                                    // 0.0
/*108 */                             ccf = sf->codec;                                                                              // 0.0
/*110 */                             ccs = ss->codec;                                                                              // 0.0
/*112 */ #define CHECK_CODEC(x)  (ccf->x != ccs->x)                                                                                // 0.0
/*116 */                             if (CHECK_CODEC(codec_id) || CHECK_CODEC(codec_type)) {                                       // 0.0
/*118 */                                 http_log("Codecs do not match for stream %d\n", i);                                       // 0.0
/*120 */                                 matches = 0;                                                                              // 0.0
/*122 */                             } else if (CHECK_CODEC(bit_rate) || CHECK_CODEC(flags)) {                                     // 0.0
/*124 */                                 http_log("Codec bitrates do not match for stream %d\n", i);                               // 0.0
/*126 */                                 matches = 0;                                                                              // 0.0
/*128 */                             } else if (ccf->codec_type == AVMEDIA_TYPE_VIDEO) {                                           // 0.0
/*130 */                                 if (CHECK_CODEC(time_base.den) ||                                                         // 0.0
/*132 */                                     CHECK_CODEC(time_base.num) ||                                                         // 0.0
/*134 */                                     CHECK_CODEC(width) ||                                                                 // 0.0
/*136 */                                     CHECK_CODEC(height)) {                                                                // 0.0
/*138 */                                     http_log("Codec width, height and framerate do not match for stream %d\n", i);        // 0.0
/*140 */                                     matches = 0;                                                                          // 0.0
/*142 */                                 }                                                                                         // 0.0
/*144 */                             } else if (ccf->codec_type == AVMEDIA_TYPE_AUDIO) {                                           // 0.0
/*146 */                                 if (CHECK_CODEC(sample_rate) ||                                                           // 0.0
/*148 */                                     CHECK_CODEC(channels) ||                                                              // 0.0
/*150 */                                     CHECK_CODEC(frame_size)) {                                                            // 0.0
/*152 */                                     http_log("Codec sample_rate, channels, frame_size do not match for stream %d\n", i);  // 0.0
/*154 */                                     matches = 0;                                                                          // 0.0
/*156 */                                 }                                                                                         // 0.0
/*158 */                             } else {                                                                                      // 0.0
/*160 */                                 http_log("Unknown codec type\n");                                                         // 0.0
/*162 */                                 matches = 0;                                                                              // 0.0
/*164 */                             }                                                                                             // 0.0
/*166 */                         }                                                                                                 // 0.0
/*168 */                         if (!matches)                                                                                     // 0.0
/*170 */                             break;                                                                                        // 0.0
/*172 */                     }                                                                                                     // 0.0
/*174 */                 } else                                                                                                    // 0.0
/*176 */                     http_log("Deleting feed file '%s' as stream counts differ (%d != %d)\n",                              // 0.0
/*178 */                         feed->feed_filename, s->nb_streams, feed->nb_streams);                                            // 0.0
/*182 */                 av_close_input_file(s);                                                                                   // 0.0
/*184 */             } else                                                                                                        // 0.0
/*186 */                 http_log("Deleting feed file '%s' as it appears to be corrupt\n",                                         // 0.0
/*188 */                         feed->feed_filename);                                                                             // 0.0
/*192 */             if (!matches) {                                                                                               // 0.0
/*194 */                 if (feed->readonly) {                                                                                     // 0.0
/*196 */                     http_log("Unable to delete feed file '%s' as it is marked readonly\n",                                // 0.0
/*198 */                         feed->feed_filename);                                                                             // 0.0
/*200 */                     exit(1);                                                                                              // 0.0
/*202 */                 }                                                                                                         // 0.0
/*204 */                 unlink(feed->feed_filename);                                                                              // 0.0
/*206 */             }                                                                                                             // 0.0
/*208 */         }                                                                                                                 // 0.0
/*210 */         if (!url_exist(feed->feed_filename)) {                                                                            // 0.0
/*212 */             AVFormatContext s1 = {0}, *s = &s1;                                                                           // 0.0
/*216 */             if (feed->readonly) {                                                                                         // 0.0
/*218 */                 http_log("Unable to create feed file '%s' as it is marked readonly\n",                                    // 0.0
/*220 */                     feed->feed_filename);                                                                                 // 0.0
/*222 */                 exit(1);                                                                                                  // 0.0
/*224 */             }                                                                                                             // 0.0
/*228 */             /* only write the header of the ffm file */                                                                   // 0.0
/*230 */             if (avio_open(&s->pb, feed->feed_filename, AVIO_FLAG_WRITE) < 0) {                                            // 0.0
/*232 */                 http_log("Could not open output feed file '%s'\n",                                                        // 0.0
/*234 */                          feed->feed_filename);                                                                            // 0.0
/*236 */                 exit(1);                                                                                                  // 0.0
/*238 */             }                                                                                                             // 0.0
/*240 */             s->oformat = feed->fmt;                                                                                       // 0.0
/*242 */             s->nb_streams = feed->nb_streams;                                                                             // 0.0
/*244 */             for(i=0;i<s->nb_streams;i++) {                                                                                // 0.0
/*246 */                 AVStream *st;                                                                                             // 0.0
/*248 */                 st = feed->streams[i];                                                                                    // 0.0
/*250 */                 s->streams[i] = st;                                                                                       // 0.0
/*252 */             }                                                                                                             // 0.0
/*254 */             av_set_parameters(s, NULL);                                                                                   // 0.0
/*256 */             if (av_write_header(s) < 0) {                                                                                 // 0.0
/*258 */                 http_log("Container doesn't supports the required parameters\n");                                         // 0.0
/*260 */                 exit(1);                                                                                                  // 0.0
/*262 */             }                                                                                                             // 0.0
/*264 */             /* XXX: need better api */                                                                                    // 0.0
/*266 */             av_freep(&s->priv_data);                                                                                      // 0.0
/*268 */             avio_close(s->pb);                                                                                            // 0.0
/*270 */         }                                                                                                                 // 0.0
/*272 */         /* get feed size and write index */                                                                               // 0.0
/*274 */         fd = open(feed->feed_filename, O_RDONLY);                                                                         // 0.0
/*276 */         if (fd < 0) {                                                                                                     // 0.0
/*278 */             http_log("Could not open output feed file '%s'\n",                                                            // 0.0
/*280 */                     feed->feed_filename);                                                                                 // 0.0
/*282 */             exit(1);                                                                                                      // 0.0
/*284 */         }                                                                                                                 // 0.0
/*288 */         feed->feed_write_index = FFMAX(ffm_read_write_index(fd), FFM_PACKET_SIZE);                                        // 0.0
/*290 */         feed->feed_size = lseek(fd, 0, SEEK_END);                                                                         // 0.0
/*292 */         /* ensure that we do not wrap before the end of file */                                                           // 0.0
/*294 */         if (feed->feed_max_size && feed->feed_max_size < feed->feed_size)                                                 // 0.0
/*296 */             feed->feed_max_size = feed->feed_size;                                                                        // 0.0
/*300 */         close(fd);                                                                                                        // 0.0
/*302 */     }                                                                                                                     // 0.0
/*304 */ }                                                                                                                         // 0.0
