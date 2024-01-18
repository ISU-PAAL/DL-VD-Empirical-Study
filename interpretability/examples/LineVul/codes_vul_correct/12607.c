// commit message FFmpeg@f5be84cfbc (target=1, prob=0.99914527, correct=True): ipmovie: do not read audio packets before the codec is known
/*0   */ static int load_ipmovie_packet(IPMVEContext *s, AVIOContext *pb,                     // (6) 0.04884
/*2   */     AVPacket *pkt) {                                                                 // (18) 0.02148
/*6   */     int chunk_type;                                                                  // (19) 0.01563
/*10  */     if (s->audio_chunk_offset) {                                                     // (16) 0.0293
/*19  */         /* adjust for PCM audio by skipping chunk header */                          // (14) 0.03516
/*21  */         if (s->audio_type != CODEC_ID_INTERPLAY_DPCM) {                              // (3) 0.05664
/*23  */             s->audio_chunk_offset += 6;                                              // (9) 0.04297
/*25  */             s->audio_chunk_size -= 6;                                                // (8) 0.04297
/*30  */         avio_seek(pb, s->audio_chunk_offset, SEEK_SET);                              // (4) 0.05469
/*32  */         s->audio_chunk_offset = 0;                                                   // (15) 0.03516
/*36  */         if (s->audio_chunk_size != av_get_packet(pb, pkt, s->audio_chunk_size))      // (0) 0.07617
/*38  */             return CHUNK_EOF;                                                        // (11) 0.03711
/*42  */         pkt->stream_index = s->audio_stream_index;                                   // (7) 0.04297
/*44  */         pkt->pts = s->audio_frame_count;                                             // (10) 0.04101
/*48  */         /* audio frame maintenance */                                                // (17) 0.02344
/*50  */         if (s->audio_type != CODEC_ID_INTERPLAY_DPCM)                                // (5) 0.05469
/*52  */             s->audio_frame_count +=                                                  // (13) 0.03711
/*54  */             (s->audio_chunk_size / s->audio_channels / (s->audio_bits / 8));         // (1) 0.07226
/*56  */         else                                                                         // (20) 0.01562
/*58  */             s->audio_frame_count +=                                                  // (12) 0.03711
/*60  */                 (s->audio_chunk_size - 6) / s->audio_channels;                       // (2) 0.06836
/*64  */         av_dlog(NULL, "sending audio frame with pts %"PRId64" (%d audio frames)\n",  // 0.0
/*66  */                 pkt->pts, s->audio_frame_count);                                     // 0.0
/*70  */         chunk_type = CHUNK_VIDEO;                                                    // 0.0
/*74  */     } else if (s->decode_map_chunk_offset) {                                         // 0.0
/*78  */         /* send both the decode map and the video data together */                   // 0.0
/*82  */         if (av_new_packet(pkt, s->decode_map_chunk_size + s->video_chunk_size))      // 0.0
/*84  */             return CHUNK_NOMEM;                                                      // 0.0
/*88  */         if (s->has_palette) {                                                        // 0.0
/*90  */             uint8_t *pal;                                                            // 0.0
/*94  */             pal = av_packet_new_side_data(pkt, AV_PKT_DATA_PALETTE,                  // 0.0
/*96  */                                           AVPALETTE_SIZE);                           // 0.0
/*98  */             if (pal) {                                                               // 0.0
/*100 */                 memcpy(pal, s->palette, AVPALETTE_SIZE);                             // 0.0
/*102 */                 s->has_palette = 0;                                                  // 0.0
/*108 */         pkt->pos= s->decode_map_chunk_offset;                                        // 0.0
/*110 */         avio_seek(pb, s->decode_map_chunk_offset, SEEK_SET);                         // 0.0
/*112 */         s->decode_map_chunk_offset = 0;                                              // 0.0
/*116 */         if (avio_read(pb, pkt->data, s->decode_map_chunk_size) !=                    // 0.0
/*118 */             s->decode_map_chunk_size) {                                              // 0.0
/*120 */             av_free_packet(pkt);                                                     // 0.0
/*122 */             return CHUNK_EOF;                                                        // 0.0
/*127 */         avio_seek(pb, s->video_chunk_offset, SEEK_SET);                              // 0.0
/*129 */         s->video_chunk_offset = 0;                                                   // 0.0
/*133 */         if (avio_read(pb, pkt->data + s->decode_map_chunk_size,                      // 0.0
/*135 */             s->video_chunk_size) != s->video_chunk_size) {                           // 0.0
/*137 */             av_free_packet(pkt);                                                     // 0.0
/*139 */             return CHUNK_EOF;                                                        // 0.0
/*144 */         pkt->stream_index = s->video_stream_index;                                   // 0.0
/*146 */         pkt->pts = s->video_pts;                                                     // 0.0
/*150 */         av_dlog(NULL, "sending video frame with pts %"PRId64"\n", pkt->pts);         // 0.0
/*154 */         s->video_pts += s->frame_pts_inc;                                            // 0.0
/*158 */         chunk_type = CHUNK_VIDEO;                                                    // 0.0
/*162 */     } else {                                                                         // 0.0
/*166 */         avio_seek(pb, s->next_chunk_offset, SEEK_SET);                               // 0.0
/*168 */         chunk_type = CHUNK_DONE;                                                     // 0.0
/*175 */     return chunk_type;                                                               // 0.0
