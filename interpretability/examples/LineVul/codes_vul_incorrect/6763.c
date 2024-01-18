// commit message FFmpeg@1f361124d9 (target=1, prob=0.4514996, correct=False): avformat/img2dec: zero probe buffer
/*0   */ int ff_img_read_packet(AVFormatContext *s1, AVPacket *pkt)                                    // (6) 0.04688
/*2   */ {                                                                                             // (25) 0.001953
/*4   */     VideoDemuxData *s = s1->priv_data;                                                        // (13) 0.0332
/*6   */     char filename_bytes[1024];                                                                // (18) 0.01953
/*8   */     char *filename = filename_bytes;                                                          // (17) 0.02148
/*10  */     int i;                                                                                    // (23) 0.01172
/*12  */     int size[3]           = { 0 }, ret[3] = { 0 };                                            // (2) 0.05859
/*14  */     AVIOContext *f[3]     = { NULL };                                                         // (10) 0.03711
/*16  */     AVCodecContext *codec = s1->streams[0]->codec;                                            // (7) 0.04492
/*20  */     if (!s->is_pipe) {                                                                        // (15) 0.02344
/*22  */         /* loop over input */                                                                 // (16) 0.02344
/*24  */         if (s->loop && s->img_number > s->img_last) {                                         // (5) 0.05078
/*26  */             s->img_number = s->img_first;                                                     // (8) 0.04492
/*28  */         }                                                                                     // (21) 0.01562
/*30  */         if (s->img_number > s->img_last)                                                      // (9) 0.04102
/*32  */             return AVERROR_EOF;                                                               // (12) 0.03711
/*34  */         if (s->use_glob) {                                                                    // (14) 0.0332
/*36  */ #if HAVE_GLOB                                                                                 // (22) 0.01172
/*38  */             filename = s->globstate.gl_pathv[s->img_number];                                  // (3) 0.05859
/*40  */ #endif                                                                                        // (24) 0.003906
/*42  */         } else {                                                                              // (19) 0.01953
/*44  */         if (av_get_frame_filename(filename_bytes, sizeof(filename_bytes),                     // (4) 0.05273
/*46  */                                   s->path,                                                    // (1) 0.07227
/*48  */                                   s->img_number) < 0 && s->img_number > 1)                    // (0) 0.09766
/*50  */             return AVERROR(EIO);                                                              // (11) 0.03711
/*52  */         }                                                                                     // (20) 0.01562
/*54  */         for (i = 0; i < 3; i++) {                                                             // 0.0
/*56  */             if (avio_open2(&f[i], filename, AVIO_FLAG_READ,                                   // 0.0
/*58  */                            &s1->interrupt_callback, NULL) < 0) {                              // 0.0
/*60  */                 if (i >= 1)                                                                   // 0.0
/*62  */                     break;                                                                    // 0.0
/*64  */                 av_log(s1, AV_LOG_ERROR, "Could not open file : %s\n",                        // 0.0
/*66  */                        filename);                                                             // 0.0
/*68  */                 return AVERROR(EIO);                                                          // 0.0
/*70  */             }                                                                                 // 0.0
/*72  */             size[i] = avio_size(f[i]);                                                        // 0.0
/*76  */             if (!s->split_planes)                                                             // 0.0
/*78  */                 break;                                                                        // 0.0
/*80  */             filename[strlen(filename) - 1] = 'U' + i;                                         // 0.0
/*82  */         }                                                                                     // 0.0
/*86  */         if (codec->codec_id == AV_CODEC_ID_NONE) {                                            // 0.0
/*88  */             AVProbeData pd;                                                                   // 0.0
/*90  */             AVInputFormat *ifmt;                                                              // 0.0
/*92  */             uint8_t header[PROBE_BUF_MIN + AVPROBE_PADDING_SIZE];                             // 0.0
/*94  */             int ret;                                                                          // 0.0
/*96  */             int score = 0;                                                                    // 0.0
/*100 */             ret = avio_read(f[0], header, PROBE_BUF_MIN);                                     // 0.0
/*102 */             if (ret < 0)                                                                      // 0.0
/*104 */                 return ret;                                                                   // 0.0
/*107 */             avio_skip(f[0], -ret);                                                            // 0.0
/*109 */             pd.buf = header;                                                                  // 0.0
/*111 */             pd.buf_size = ret;                                                                // 0.0
/*113 */             pd.filename = filename;                                                           // 0.0
/*117 */             ifmt = av_probe_input_format3(&pd, 1, &score);                                    // 0.0
/*119 */             if (ifmt && ifmt->read_packet == ff_img_read_packet && ifmt->raw_codec_id)        // 0.0
/*121 */                 codec->codec_id = ifmt->raw_codec_id;                                         // 0.0
/*123 */         }                                                                                     // 0.0
/*127 */         if (codec->codec_id == AV_CODEC_ID_RAWVIDEO && !codec->width)                         // 0.0
/*129 */             infer_size(&codec->width, &codec->height, size[0]);                               // 0.0
/*131 */     } else {                                                                                  // 0.0
/*133 */         f[0] = s1->pb;                                                                        // 0.0
/*135 */         if (url_feof(f[0]))                                                                   // 0.0
/*137 */             return AVERROR(EIO);                                                              // 0.0
/*139 */         if (s->frame_size > 0) {                                                              // 0.0
/*141 */             size[0] = s->frame_size;                                                          // 0.0
/*143 */         } else {                                                                              // 0.0
/*145 */             size[0] = 4096;                                                                   // 0.0
/*147 */         }                                                                                     // 0.0
/*149 */     }                                                                                         // 0.0
/*153 */     if (av_new_packet(pkt, size[0] + size[1] + size[2]) < 0)                                  // 0.0
/*155 */         return AVERROR(ENOMEM);                                                               // 0.0
/*157 */     pkt->stream_index = 0;                                                                    // 0.0
/*159 */     pkt->flags       |= AV_PKT_FLAG_KEY;                                                      // 0.0
/*161 */     if (s->ts_from_file) {                                                                    // 0.0
/*163 */         struct stat img_stat;                                                                 // 0.0
/*165 */         if (stat(filename, &img_stat))                                                        // 0.0
/*167 */             return AVERROR(EIO);                                                              // 0.0
/*169 */         pkt->pts = (int64_t)img_stat.st_mtime;                                                // 0.0
/*171 */         av_add_index_entry(s1->streams[0], s->img_number, pkt->pts, 0, 0, AVINDEX_KEYFRAME);  // 0.0
/*173 */     } else if (!s->is_pipe) {                                                                 // 0.0
/*175 */         pkt->pts      = s->pts;                                                               // 0.0
/*177 */     }                                                                                         // 0.0
/*181 */     pkt->size = 0;                                                                            // 0.0
/*183 */     for (i = 0; i < 3; i++) {                                                                 // 0.0
/*185 */         if (f[i]) {                                                                           // 0.0
/*187 */             ret[i] = avio_read(f[i], pkt->data + pkt->size, size[i]);                         // 0.0
/*189 */             if (!s->is_pipe)                                                                  // 0.0
/*191 */                 avio_close(f[i]);                                                             // 0.0
/*193 */             if (ret[i] > 0)                                                                   // 0.0
/*195 */                 pkt->size += ret[i];                                                          // 0.0
/*197 */         }                                                                                     // 0.0
/*199 */     }                                                                                         // 0.0
/*203 */     if (ret[0] <= 0 || ret[1] < 0 || ret[2] < 0) {                                            // 0.0
/*205 */         av_free_packet(pkt);                                                                  // 0.0
/*207 */         return AVERROR(EIO); /* signal EOF */                                                 // 0.0
/*209 */     } else {                                                                                  // 0.0
/*211 */         s->img_count++;                                                                       // 0.0
/*213 */         s->img_number++;                                                                      // 0.0
/*215 */         s->pts++;                                                                             // 0.0
/*217 */         return 0;                                                                             // 0.0
/*219 */     }                                                                                         // 0.0
/*221 */ }                                                                                             // 0.0
