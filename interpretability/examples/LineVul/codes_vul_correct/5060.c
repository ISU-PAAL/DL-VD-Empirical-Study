// commit message FFmpeg@eedd914873 (target=1, prob=0.55440134, correct=True): avformat/pva: Make sure the header is large enough before reading the timestamp from it
/*0   */ static int read_part_of_packet(AVFormatContext *s, int64_t *pts,                                // (1) 0.1922
/*2   */                                int *len, int *strid, int read_packet) {                         // (3) 0.05361
/*4   */     AVIOContext *pb = s->pb;                                                                    // (15) 0.007114
/*6   */     PVAContext *pvactx = s->priv_data;                                                          // (6) 0.01437
/*8   */     int syncword, streamid, reserved, flags, length, pts_flag;                                  // (5) 0.01647
/*10  */     int64_t pva_pts = AV_NOPTS_VALUE, startpos;                                                 // (2) 0.1529
/*12  */     int ret;                                                                                    // (4) 0.02282
/*16  */ recover:                                                                                        // (8) 0.01266
/*18  */     startpos = avio_tell(pb);                                                                   // (0) 0.3599
/*22  */     syncword = avio_rb16(pb);                                                                   // (7) 0.01328
/*24  */     streamid = avio_r8(pb);                                                                     // (20) 0.004733
/*26  */     avio_r8(pb);               /* counter not used */                                           // (14) 0.007559
/*28  */     reserved = avio_r8(pb);                                                                     // (19) 0.004931
/*30  */     flags    = avio_r8(pb);                                                                     // (21) 0.004437
/*32  */     length   = avio_rb16(pb);                                                                   // (17) 0.006866
/*36  */     pts_flag = flags & 0x10;                                                                    // (16) 0.006889
/*40  */     if (syncword != PVA_MAGIC) {                                                                // (11) 0.009096
/*42  */         pva_log(s, AV_LOG_ERROR, "invalid syncword\n");                                         // (10) 0.009899
/*44  */         return AVERROR(EIO);                                                                    // (18) 0.005501
/*46  */     }                                                                                           // (26) 0.0006675
/*48  */     if (streamid != PVA_VIDEO_PAYLOAD && streamid != PVA_AUDIO_PAYLOAD) {                       // (9) 0.01067
/*50  */         pva_log(s, AV_LOG_ERROR, "invalid streamid\n");                                         // (12) 0.008961
/*52  */         return AVERROR(EIO);                                                                    // (22) 0.003551
/*54  */     }                                                                                           // (25) 0.0006945
/*56  */     if (reserved != 0x55) {                                                                     // (23) 0.003141
/*58  */         pva_log(s, AV_LOG_WARNING, "expected reserved byte to be 0x55\n");                      // (13) 0.008426
/*60  */     }                                                                                           // (24) 0.0007731
/*62  */     if (length > PVA_MAX_PAYLOAD_LENGTH) {                                                      // 0.0
/*64  */         pva_log(s, AV_LOG_ERROR, "invalid payload length %u\n", length);                        // 0.0
/*66  */         return AVERROR(EIO);                                                                    // 0.0
/*68  */     }                                                                                           // 0.0
/*72  */     if (streamid == PVA_VIDEO_PAYLOAD && pts_flag) {                                            // 0.0
/*74  */         pva_pts = avio_rb32(pb);                                                                // 0.0
/*76  */         length -= 4;                                                                            // 0.0
/*78  */     } else if (streamid == PVA_AUDIO_PAYLOAD) {                                                 // 0.0
/*80  */         /* PVA Audio Packets either start with a signaled PES packet or                         // 0.0
/*82  */          * are a continuation of the previous PES packet. New PES packets                       // 0.0
/*84  */          * always start at the beginning of a PVA Packet, never somewhere in                    // 0.0
/*86  */          * the middle. */                                                                       // 0.0
/*88  */         if (!pvactx->continue_pes) {                                                            // 0.0
/*90  */             int pes_signal, pes_header_data_length, pes_packet_length,                          // 0.0
/*92  */                 pes_flags;                                                                      // 0.0
/*94  */             unsigned char pes_header_data[256];                                                 // 0.0
/*98  */             pes_signal             = avio_rb24(pb);                                             // 0.0
/*100 */             avio_r8(pb);                                                                        // 0.0
/*102 */             pes_packet_length      = avio_rb16(pb);                                             // 0.0
/*104 */             pes_flags              = avio_rb16(pb);                                             // 0.0
/*106 */             pes_header_data_length = avio_r8(pb);                                               // 0.0
/*110 */             if (pes_signal != 1 || pes_header_data_length == 0) {                               // 0.0
/*112 */                 pva_log(s, AV_LOG_WARNING, "expected non empty signaled PES packet, "           // 0.0
/*114 */                                           "trying to recover\n");                               // 0.0
/*116 */                 avio_skip(pb, length - 9);                                                      // 0.0
/*118 */                 if (!read_packet)                                                               // 0.0
/*120 */                     return AVERROR(EIO);                                                        // 0.0
/*122 */                 goto recover;                                                                   // 0.0
/*124 */             }                                                                                   // 0.0
/*128 */             ret = avio_read(pb, pes_header_data, pes_header_data_length);                       // 0.0
/*130 */             if (ret != pes_header_data_length)                                                  // 0.0
/*132 */                 return ret < 0 ? ret : AVERROR_INVALIDDATA;                                     // 0.0
/*134 */             length -= 9 + pes_header_data_length;                                               // 0.0
/*138 */             pes_packet_length -= 3 + pes_header_data_length;                                    // 0.0
/*142 */             pvactx->continue_pes = pes_packet_length;                                           // 0.0
/*146 */             if (pes_flags & 0x80 && (pes_header_data[0] & 0xf0) == 0x20)                        // 0.0
/*148 */                 pva_pts = ff_parse_pes_pts(pes_header_data);                                    // 0.0
/*150 */         }                                                                                       // 0.0
/*154 */         pvactx->continue_pes -= length;                                                         // 0.0
/*158 */         if (pvactx->continue_pes < 0) {                                                         // 0.0
/*160 */             pva_log(s, AV_LOG_WARNING, "audio data corruption\n");                              // 0.0
/*162 */             pvactx->continue_pes = 0;                                                           // 0.0
/*164 */         }                                                                                       // 0.0
/*166 */     }                                                                                           // 0.0
/*170 */     if (pva_pts != AV_NOPTS_VALUE)                                                              // 0.0
/*172 */         av_add_index_entry(s->streams[streamid-1], startpos, pva_pts, 0, 0, AVINDEX_KEYFRAME);  // 0.0
/*176 */     *pts   = pva_pts;                                                                           // 0.0
/*178 */     *len   = length;                                                                            // 0.0
/*180 */     *strid = streamid;                                                                          // 0.0
/*182 */     return 0;                                                                                   // 0.0
/*184 */ }                                                                                               // 0.0
