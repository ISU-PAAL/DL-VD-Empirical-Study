// commit message FFmpeg@33f58c3616 (target=1, prob=0.99925345, correct=True): idcin: check for integer overflow when calling av_get_packet()
/*0   */ static int idcin_read_packet(AVFormatContext *s,                                 // (14) 0.03125
/*2   */                              AVPacket *pkt)                                      // (0) 0.06836
/*4   */ {                                                                                // (28) 0.001953
/*6   */     int ret;                                                                     // (26) 0.01172
/*8   */     unsigned int command;                                                        // (25) 0.01367
/*10  */     unsigned int chunk_size;                                                     // (23) 0.01758
/*12  */     IdcinDemuxContext *idcin = s->priv_data;                                     // (8) 0.03516
/*14  */     AVIOContext *pb = s->pb;                                                     // (19) 0.02539
/*16  */     int i;                                                                       // (27) 0.01172
/*18  */     int palette_scale;                                                           // (24) 0.01562
/*20  */     unsigned char r, g, b;                                                       // (22) 0.02148
/*22  */     unsigned char palette_buffer[768];                                           // (20) 0.02148
/*24  */     uint32_t palette[256];                                                       // (21) 0.02148
/*28  */     if (s->pb->eof_reached)                                                      // (16) 0.0293
/*30  */         return AVERROR(EIO);                                                     // (17) 0.0293
/*34  */     if (idcin->next_chunk_is_video) {                                            // (9) 0.03516
/*36  */         command = avio_rl32(pb);                                                 // (12) 0.0332
/*38  */         if (command == 2) {                                                      // (18) 0.02734
/*40  */             return AVERROR(EIO);                                                 // (7) 0.03711
/*42  */         } else if (command == 1) {                                               // (15) 0.03125
/*44  */             /* trigger a palette change */                                       // (11) 0.0332
/*46  */             if (avio_read(pb, palette_buffer, 768) != 768)                       // (1) 0.05664
/*48  */                 return AVERROR(EIO);                                             // (5) 0.04492
/*50  */             /* scale the palette as necessary */                                 // (10) 0.03516
/*52  */             palette_scale = 2;                                                   // (13) 0.0332
/*54  */             for (i = 0; i < 768; i++)                                            // (4) 0.04492
/*56  */                 if (palette_buffer[i] > 63) {                                    // (2) 0.05469
/*58  */                     palette_scale = 0;                                           // (3) 0.04883
/*60  */                     break;                                                       // (6) 0.04102
/*65  */             for (i = 0; i < 256; i++) {                                          // 0.0
/*67  */                 r = palette_buffer[i * 3    ] << palette_scale;                  // 0.0
/*69  */                 g = palette_buffer[i * 3 + 1] << palette_scale;                  // 0.0
/*71  */                 b = palette_buffer[i * 3 + 2] << palette_scale;                  // 0.0
/*73  */                 palette[i] = (r << 16) | (g << 8) | (b);                         // 0.0
/*79  */         chunk_size = avio_rl32(pb);                                              // 0.0
/*85  */         /* skip the number of decoded bytes (always equal to width * height) */  // 0.0
/*87  */         avio_skip(pb, 4);                                                        // 0.0
/*89  */         chunk_size -= 4;                                                         // 0.0
/*91  */         ret= av_get_packet(pb, pkt, chunk_size);                                 // 0.0
/*93  */         if (ret < 0)                                                             // 0.0
/*95  */             return ret;                                                          // 0.0
/*97  */         if (command == 1) {                                                      // 0.0
/*99  */             uint8_t *pal;                                                        // 0.0
/*103 */             pal = av_packet_new_side_data(pkt, AV_PKT_DATA_PALETTE,              // 0.0
/*105 */                                           AVPALETTE_SIZE);                       // 0.0
/*107 */             if (ret < 0)                                                         // 0.0
/*109 */                 return ret;                                                      // 0.0
/*111 */             memcpy(pal, palette, AVPALETTE_SIZE);                                // 0.0
/*113 */             pkt->flags |= AV_PKT_FLAG_KEY;                                       // 0.0
/*116 */         pkt->stream_index = idcin->video_stream_index;                           // 0.0
/*118 */         pkt->duration     = 1;                                                   // 0.0
/*120 */     } else {                                                                     // 0.0
/*122 */         /* send out the audio chunk */                                           // 0.0
/*124 */         if (idcin->current_audio_chunk)                                          // 0.0
/*126 */             chunk_size = idcin->audio_chunk_size2;                               // 0.0
/*128 */         else                                                                     // 0.0
/*130 */             chunk_size = idcin->audio_chunk_size1;                               // 0.0
/*132 */         ret= av_get_packet(pb, pkt, chunk_size);                                 // 0.0
/*134 */         if (ret < 0)                                                             // 0.0
/*136 */             return ret;                                                          // 0.0
/*138 */         pkt->stream_index = idcin->audio_stream_index;                           // 0.0
/*140 */         pkt->duration     = chunk_size / idcin->block_align;                     // 0.0
/*144 */         idcin->current_audio_chunk ^= 1;                                         // 0.0
/*149 */     if (idcin->audio_present)                                                    // 0.0
/*151 */         idcin->next_chunk_is_video ^= 1;                                         // 0.0
/*155 */     return ret;                                                                  // 0.0
