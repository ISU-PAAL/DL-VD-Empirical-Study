// commit message FFmpeg@3f8148911c (target=0, prob=0.49851975, correct=True): img2dec: check return value of av_new_packet()
/*0   */ static int read_packet(AVFormatContext *s1, AVPacket *pkt)                         // (7) 0.04102
/*2   */ {                                                                                  // (26) 0.001961
/*4   */     VideoDemuxData *s = s1->priv_data;                                             // (13) 0.0332
/*6   */     char filename_bytes[1024];                                                     // (19) 0.01953
/*8   */     char *filename = filename_bytes;                                               // (18) 0.02148
/*10  */     int i;                                                                         // (24) 0.01172
/*12  */     int size[3]={0}, ret[3]={0};                                                   // (12) 0.03516
/*14  */     AVIOContext *f[3] = {NULL};                                                    // (15) 0.0293
/*16  */     AVCodecContext *codec= s1->streams[0]->codec;                                  // (5) 0.04492
/*20  */     if (!s->is_pipe) {                                                             // (16) 0.02344
/*22  */         /* loop over input */                                                      // (17) 0.02344
/*24  */         if (s->loop && s->img_number > s->img_last) {                              // (4) 0.05078
/*26  */             s->img_number = s->img_first;                                          // (6) 0.04492
/*28  */         }                                                                          // (22) 0.01562
/*30  */         if (s->img_number > s->img_last)                                           // (8) 0.04101
/*32  */             return AVERROR_EOF;                                                    // (11) 0.03711
/*34  */         if (s->use_glob) {                                                         // (14) 0.0332
/*36  */ #if HAVE_GLOB                                                                      // (23) 0.01172
/*38  */             filename = s->globstate.gl_pathv[s->img_number];                       // (2) 0.05859
/*40  */ #endif                                                                             // (25) 0.003907
/*42  */         } else {                                                                   // (20) 0.01953
/*44  */         if (av_get_frame_filename(filename_bytes, sizeof(filename_bytes),          // (3) 0.05273
/*46  */                                   s->path, s->img_number)<0 && s->img_number > 1)  // (0) 0.1055
/*48  */             return AVERROR(EIO);                                                   // (10) 0.03711
/*50  */         }                                                                          // (21) 0.01562
/*52  */         for(i=0; i<3; i++){                                                        // (9) 0.03906
/*54  */             if (avio_open2(&f[i], filename, AVIO_FLAG_READ,                        // (1) 0.0625
/*56  */                            &s1->interrupt_callback, NULL) < 0) {                   // 0.0
/*58  */                 if(i>=1)                                                           // 0.0
/*60  */                     break;                                                         // 0.0
/*62  */                 av_log(s1, AV_LOG_ERROR, "Could not open file : %s\n",filename);   // 0.0
/*64  */                 return AVERROR(EIO);                                               // 0.0
/*66  */             }                                                                      // 0.0
/*68  */             size[i]= avio_size(f[i]);                                              // 0.0
/*72  */             if(!s->split_planes)                                                   // 0.0
/*74  */                 break;                                                             // 0.0
/*76  */             filename[ strlen(filename) - 1 ]= 'U' + i;                             // 0.0
/*78  */         }                                                                          // 0.0
/*82  */         if(codec->codec_id == AV_CODEC_ID_RAWVIDEO && !codec->width)               // 0.0
/*84  */             infer_size(&codec->width, &codec->height, size[0]);                    // 0.0
/*86  */     } else {                                                                       // 0.0
/*88  */         f[0] = s1->pb;                                                             // 0.0
/*90  */         if (url_feof(f[0]))                                                        // 0.0
/*92  */             return AVERROR(EIO);                                                   // 0.0
/*94  */         size[0]= 4096;                                                             // 0.0
/*96  */     }                                                                              // 0.0
/*100 */     av_new_packet(pkt, size[0] + size[1] + size[2]);                               // 0.0
/*102 */     pkt->stream_index = 0;                                                         // 0.0
/*104 */     pkt->flags |= AV_PKT_FLAG_KEY;                                                 // 0.0
/*108 */     pkt->size= 0;                                                                  // 0.0
/*110 */     for(i=0; i<3; i++){                                                            // 0.0
/*112 */         if(f[i]){                                                                  // 0.0
/*114 */             ret[i]= avio_read(f[i], pkt->data + pkt->size, size[i]);               // 0.0
/*116 */             if (!s->is_pipe)                                                       // 0.0
/*118 */                 avio_close(f[i]);                                                  // 0.0
/*120 */             if(ret[i]>0)                                                           // 0.0
/*122 */                 pkt->size += ret[i];                                               // 0.0
/*124 */         }                                                                          // 0.0
/*126 */     }                                                                              // 0.0
/*130 */     if (ret[0] <= 0 || ret[1]<0 || ret[2]<0) {                                     // 0.0
/*132 */         av_free_packet(pkt);                                                       // 0.0
/*134 */         return AVERROR(EIO); /* signal EOF */                                      // 0.0
/*136 */     } else {                                                                       // 0.0
/*138 */         s->img_count++;                                                            // 0.0
/*140 */         s->img_number++;                                                           // 0.0
/*142 */         return 0;                                                                  // 0.0
/*144 */     }                                                                              // 0.0
/*146 */ }                                                                                  // 0.0
