// commit message FFmpeg@c5f15f40b9 (target=1, prob=0.44914022, correct=False): avformat/rtpdec_h264: fix null pointer dereferences
/*0   */ static int h264_handle_packet(AVFormatContext *ctx, PayloadContext *data,               // (8) 0.04297
/*2   */                               AVStream *st, AVPacket *pkt, uint32_t *timestamp,         // (0) 0.0957
/*4   */                               const uint8_t *buf, int len, uint16_t seq,                // (1) 0.08984
/*6   */                               int flags)                                                // (2) 0.0625
/*8   */ {                                                                                       // (27) 0.001953
/*10  */     uint8_t nal;                                                                        // (17) 0.01953
/*12  */     uint8_t type;                                                                       // (18) 0.01758
/*14  */     int result = 0;                                                                     // (20) 0.01563
/*18  */     if (!len) {                                                                         // (21) 0.01562
/*20  */         av_log(ctx, AV_LOG_ERROR, "Empty H264 RTP packet\n");                           // (4) 0.05664
/*22  */         return AVERROR_INVALIDDATA;                                                     // (11) 0.0332
/*24  */     }                                                                                   // (26) 0.007812
/*26  */     nal  = buf[0];                                                                      // (15) 0.02148
/*28  */     type = nal & 0x1f;                                                                  // (12) 0.02539
/*32  */     assert(data);                                                                       // (24) 0.01367
/*34  */     assert(buf);                                                                        // (23) 0.01367
/*38  */     /* Simplify the case (these are all the nal types used internally by                // (10) 0.03711
/*40  */      * the h264 codec). */                                                              // (14) 0.02148
/*42  */     if (type >= 1 && type <= 23)                                                        // (13) 0.02539
/*44  */         type = 1;                                                                       // (16) 0.02148
/*46  */     switch (type) {                                                                     // (22) 0.01562
/*48  */     case 0:                    // undefined, but pass them through                      // (3) 0.0625
/*50  */     case 1:                                                                             // (25) 0.01172
/*52  */         av_new_packet(pkt, len + sizeof(start_sequence));                               // (7) 0.04883
/*54  */         memcpy(pkt->data, start_sequence, sizeof(start_sequence));                      // (6) 0.05078
/*56  */         memcpy(pkt->data + sizeof(start_sequence), buf, len);                           // (5) 0.05078
/*58  */         COUNT_NAL_TYPE(data, nal);                                                      // (9) 0.03906
/*60  */         break;                                                                          // (19) 0.01758
/*64  */     case 24:                   // STAP-A (one packet, multiple nals)                    // 0.0
/*66  */         // consume the STAP-A NAL                                                       // 0.0
/*68  */         buf++;                                                                          // 0.0
/*70  */         len--;                                                                          // 0.0
/*72  */         // first we are going to figure out the total size                              // 0.0
/*74  */         {                                                                               // 0.0
/*76  */             int pass         = 0;                                                       // 0.0
/*78  */             int total_length = 0;                                                       // 0.0
/*80  */             uint8_t *dst     = NULL;                                                    // 0.0
/*84  */             for (pass = 0; pass < 2; pass++) {                                          // 0.0
/*86  */                 const uint8_t *src = buf;                                               // 0.0
/*88  */                 int src_len        = len;                                               // 0.0
/*92  */                 while (src_len > 2) {                                                   // 0.0
/*94  */                     uint16_t nal_size = AV_RB16(src);                                   // 0.0
/*98  */                     // consume the length of the aggregate                              // 0.0
/*100 */                     src     += 2;                                                       // 0.0
/*102 */                     src_len -= 2;                                                       // 0.0
/*106 */                     if (nal_size <= src_len) {                                          // 0.0
/*108 */                         if (pass == 0) {                                                // 0.0
/*110 */                             // counting                                                 // 0.0
/*112 */                             total_length += sizeof(start_sequence) + nal_size;          // 0.0
/*114 */                         } else {                                                        // 0.0
/*116 */                             // copying                                                  // 0.0
/*118 */                             assert(dst);                                                // 0.0
/*120 */                             memcpy(dst, start_sequence, sizeof(start_sequence));        // 0.0
/*122 */                             dst += sizeof(start_sequence);                              // 0.0
/*124 */                             memcpy(dst, src, nal_size);                                 // 0.0
/*126 */                             COUNT_NAL_TYPE(data, *src);                                 // 0.0
/*128 */                             dst += nal_size;                                            // 0.0
/*130 */                         }                                                               // 0.0
/*132 */                     } else {                                                            // 0.0
/*134 */                         av_log(ctx, AV_LOG_ERROR,                                       // 0.0
/*136 */                                "nal size exceeds length: %d %d\n", nal_size, src_len);  // 0.0
/*138 */                     }                                                                   // 0.0
/*142 */                     // eat what we handled                                              // 0.0
/*144 */                     src     += nal_size;                                                // 0.0
/*146 */                     src_len -= nal_size;                                                // 0.0
/*150 */                     if (src_len < 0)                                                    // 0.0
/*152 */                         av_log(ctx, AV_LOG_ERROR,                                       // 0.0
/*154 */                                "Consumed more bytes than we got! (%d)\n", src_len);     // 0.0
/*156 */                 }                                                                       // 0.0
/*160 */                 if (pass == 0) {                                                        // 0.0
/*162 */                     /* now we know the total size of the packet (with the               // 0.0
/*164 */                      * start sequences added) */                                        // 0.0
/*166 */                     av_new_packet(pkt, total_length);                                   // 0.0
/*168 */                     dst = pkt->data;                                                    // 0.0
/*170 */                 } else {                                                                // 0.0
/*172 */                     assert(dst - pkt->data == total_length);                            // 0.0
/*174 */                 }                                                                       // 0.0
/*176 */             }                                                                           // 0.0
/*178 */         }                                                                               // 0.0
/*180 */         break;                                                                          // 0.0
/*184 */     case 25:                   // STAP-B                                                // 0.0
/*186 */     case 26:                   // MTAP-16                                               // 0.0
/*188 */     case 27:                   // MTAP-24                                               // 0.0
/*190 */     case 29:                   // FU-B                                                  // 0.0
/*192 */         av_log(ctx, AV_LOG_ERROR,                                                       // 0.0
/*194 */                "Unhandled type (%d) (See RFC for implementation details\n",             // 0.0
/*196 */                type);                                                                   // 0.0
/*198 */         result = AVERROR(ENOSYS);                                                       // 0.0
/*200 */         break;                                                                          // 0.0
/*204 */     case 28:                   // FU-A (fragmented nal)                                 // 0.0
/*206 */         buf++;                                                                          // 0.0
/*208 */         len--;                 // skip the fu_indicator                                 // 0.0
/*210 */         if (len > 1) {                                                                  // 0.0
/*212 */             // these are the same as above, we just redo them here for clarity          // 0.0
/*214 */             uint8_t fu_indicator      = nal;                                            // 0.0
/*216 */             uint8_t fu_header         = *buf;                                           // 0.0
/*218 */             uint8_t start_bit         = fu_header >> 7;                                 // 0.0
/*220 */             uint8_t av_unused end_bit = (fu_header & 0x40) >> 6;                        // 0.0
/*222 */             uint8_t nal_type          = fu_header & 0x1f;                               // 0.0
/*224 */             uint8_t reconstructed_nal;                                                  // 0.0
/*228 */             // Reconstruct this packet's true nal; only the data follows.               // 0.0
/*230 */             /* The original nal forbidden bit and NRI are stored in this                // 0.0
/*232 */              * packet's nal. */                                                         // 0.0
/*234 */             reconstructed_nal  = fu_indicator & 0xe0;                                   // 0.0
/*236 */             reconstructed_nal |= nal_type;                                              // 0.0
/*240 */             // skip the fu_header                                                       // 0.0
/*242 */             buf++;                                                                      // 0.0
/*244 */             len--;                                                                      // 0.0
/*248 */             if (start_bit)                                                              // 0.0
/*250 */                 COUNT_NAL_TYPE(data, nal_type);                                         // 0.0
/*252 */             if (start_bit) {                                                            // 0.0
/*254 */                 /* copy in the start sequence, and the reconstructed nal */             // 0.0
/*256 */                 av_new_packet(pkt, sizeof(start_sequence) + sizeof(nal) + len);         // 0.0
/*258 */                 memcpy(pkt->data, start_sequence, sizeof(start_sequence));              // 0.0
/*260 */                 pkt->data[sizeof(start_sequence)] = reconstructed_nal;                  // 0.0
/*262 */                 memcpy(pkt->data + sizeof(start_sequence) + sizeof(nal), buf, len);     // 0.0
/*264 */             } else {                                                                    // 0.0
/*266 */                 av_new_packet(pkt, len);                                                // 0.0
/*268 */                 memcpy(pkt->data, buf, len);                                            // 0.0
/*270 */             }                                                                           // 0.0
/*272 */         } else {                                                                        // 0.0
/*274 */             av_log(ctx, AV_LOG_ERROR, "Too short data for FU-A H264 RTP packet\n");     // 0.0
/*276 */             result = AVERROR_INVALIDDATA;                                               // 0.0
/*278 */         }                                                                               // 0.0
/*280 */         break;                                                                          // 0.0
/*284 */     case 30:                   // undefined                                             // 0.0
/*286 */     case 31:                   // undefined                                             // 0.0
/*288 */     default:                                                                            // 0.0
/*290 */         av_log(ctx, AV_LOG_ERROR, "Undefined type (%d)\n", type);                       // 0.0
/*292 */         result = AVERROR_INVALIDDATA;                                                   // 0.0
/*294 */         break;                                                                          // 0.0
/*296 */     }                                                                                   // 0.0
/*300 */     pkt->stream_index = st->index;                                                      // 0.0
/*304 */     return result;                                                                      // 0.0
/*306 */ }                                                                                       // 0.0
