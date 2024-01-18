// commit message FFmpeg@bfeb83a8b7 (target=1, prob=0.57271624, correct=True): rtpdec_hevc: Drop extra sanity check for size of input packet
/*0   */ static int hevc_handle_packet(AVFormatContext *ctx, PayloadContext *rtp_hevc_ctx,                  // (4) 0.05468
/*2   */                               AVStream *st, AVPacket *pkt, uint32_t *timestamp,                    // (0) 0.0957
/*4   */                               const uint8_t *buf, int len, uint16_t seq,                           // (1) 0.08983
/*6   */                               int flags)                                                           // (3) 0.0625
/*8   */ {                                                                                                  // (24) 0.001982
/*10  */     const uint8_t *rtp_pl = buf;                                                                   // (14) 0.03125
/*12  */     int tid, lid, nal_type;                                                                        // (16) 0.02539
/*14  */     int first_fragment, last_fragment, fu_type;                                                    // (10) 0.03906
/*16  */     uint8_t new_nal_header[2];                                                                     // (15) 0.03125
/*18  */     int res = 0;                                                                                   // (19) 0.01562
/*22  */     /* sanity check for size of input packet: 1 byte payload at least */                           // (11) 0.03515
/*24  */     if (len < RTP_HEVC_PAYLOAD_HEADER_SIZE + 1) {                                                  // (7) 0.04882
/*26  */         av_log(ctx, AV_LOG_ERROR, "Too short RTP/HEVC packet, got %d bytes\n", len);               // (2) 0.07421
/*28  */         return AVERROR_INVALIDDATA;                                                                // (13) 0.0332
/*30  */     }                                                                                              // (23) 0.007812
/*34  */     /*                                                                                             // (22) 0.007812
/*36  */      * decode the HEVC payload header according to section 4 of draft version 6:                   // (9) 0.03906
/*38  */      *                                                                                             // (21) 0.009764
/*40  */      *    0                   1                                                                    // (5) 0.05468
/*42  */      *    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5                                                          // (8) 0.04687
/*44  */      *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                                                         // (18) 0.02343
/*46  */      *   |F|   Type    |  LayerId  | TID |                                                         // (6) 0.04883
/*48  */      *   +-------------+-----------------+                                                         // (17) 0.02344
/*50  */      *                                                                                             // (20) 0.009765
/*52  */      *      Forbidden zero (F): 1 bit                                                              // (12) 0.0332
/*54  */      *      NAL unit type (Type): 6 bits                                                           // 0.0
/*56  */      *      NUH layer ID (LayerId): 6 bits                                                         // 0.0
/*58  */      *      NUH temporal ID plus 1 (TID): 3 bits                                                   // 0.0
/*60  */      */                                                                                            // 0.0
/*62  */     nal_type =  (buf[0] >> 1) & 0x3f;                                                              // 0.0
/*64  */     lid  = ((buf[0] << 5) & 0x20) | ((buf[1] >> 3) & 0x1f);                                        // 0.0
/*66  */     tid  =   buf[1] & 0x07;                                                                        // 0.0
/*70  */     /* sanity check for correct layer ID */                                                        // 0.0
/*72  */     if (lid) {                                                                                     // 0.0
/*74  */         /* future scalable or 3D video coding extensions */                                        // 0.0
/*76  */         avpriv_report_missing_feature(ctx, "Multi-layer HEVC coding\n");                           // 0.0
/*78  */         return AVERROR_PATCHWELCOME;                                                               // 0.0
/*80  */     }                                                                                              // 0.0
/*84  */     /* sanity check for correct temporal ID */                                                     // 0.0
/*86  */     if (!tid) {                                                                                    // 0.0
/*88  */         av_log(ctx, AV_LOG_ERROR, "Illegal temporal ID in RTP/HEVC packet\n");                     // 0.0
/*90  */         return AVERROR_INVALIDDATA;                                                                // 0.0
/*92  */     }                                                                                              // 0.0
/*96  */     /* sanity check for correct NAL unit type */                                                   // 0.0
/*98  */     if (nal_type > 50) {                                                                           // 0.0
/*100 */         av_log(ctx, AV_LOG_ERROR, "Unsupported (HEVC) NAL type (%d)\n", nal_type);                 // 0.0
/*102 */         return AVERROR_INVALIDDATA;                                                                // 0.0
/*104 */     }                                                                                              // 0.0
/*108 */     switch (nal_type) {                                                                            // 0.0
/*110 */     /* video parameter set (VPS) */                                                                // 0.0
/*112 */     case 32:                                                                                       // 0.0
/*114 */     /* sequence parameter set (SPS) */                                                             // 0.0
/*116 */     case 33:                                                                                       // 0.0
/*118 */     /* picture parameter set (PPS) */                                                              // 0.0
/*120 */     case 34:                                                                                       // 0.0
/*122 */     /*  supplemental enhancement information (SEI) */                                              // 0.0
/*124 */     case 39:                                                                                       // 0.0
/*126 */     /* single NAL unit packet */                                                                   // 0.0
/*128 */     default:                                                                                       // 0.0
/*130 */         /* sanity check for size of input packet: 1 byte payload at least */                       // 0.0
/*132 */         if (len < 1) {                                                                             // 0.0
/*134 */             av_log(ctx, AV_LOG_ERROR,                                                              // 0.0
/*136 */                    "Too short RTP/HEVC packet, got %d bytes of NAL unit type %d\n",                // 0.0
/*138 */                    len, nal_type);                                                                 // 0.0
/*140 */             return AVERROR_INVALIDDATA;                                                            // 0.0
/*142 */         }                                                                                          // 0.0
/*146 */         /* create A/V packet */                                                                    // 0.0
/*148 */         if ((res = av_new_packet(pkt, sizeof(start_sequence) + len)) < 0)                          // 0.0
/*150 */             return res;                                                                            // 0.0
/*152 */         /* A/V packet: copy start sequence */                                                      // 0.0
/*154 */         memcpy(pkt->data, start_sequence, sizeof(start_sequence));                                 // 0.0
/*156 */         /* A/V packet: copy NAL unit data */                                                       // 0.0
/*158 */         memcpy(pkt->data + sizeof(start_sequence), buf, len);                                      // 0.0
/*162 */         break;                                                                                     // 0.0
/*164 */     /* aggregated packet (AP) - with two or more NAL units */                                      // 0.0
/*166 */     case 48:                                                                                       // 0.0
/*168 */         /* pass the HEVC payload header */                                                         // 0.0
/*170 */         buf += RTP_HEVC_PAYLOAD_HEADER_SIZE;                                                       // 0.0
/*172 */         len -= RTP_HEVC_PAYLOAD_HEADER_SIZE;                                                       // 0.0
/*176 */         /* pass the HEVC DONL field */                                                             // 0.0
/*178 */         if (rtp_hevc_ctx->using_donl_field) {                                                      // 0.0
/*180 */             buf += RTP_HEVC_DONL_FIELD_SIZE;                                                       // 0.0
/*182 */             len -= RTP_HEVC_DONL_FIELD_SIZE;                                                       // 0.0
/*184 */         }                                                                                          // 0.0
/*188 */         res = ff_h264_handle_aggregated_packet(ctx, pkt, buf, len,                                 // 0.0
/*190 */                                                rtp_hevc_ctx->using_donl_field ?                    // 0.0
/*192 */                                                RTP_HEVC_DOND_FIELD_SIZE : 0,                       // 0.0
/*194 */                                                NULL, 0);                                           // 0.0
/*196 */         if (res < 0)                                                                               // 0.0
/*198 */             return res;                                                                            // 0.0
/*200 */         break;                                                                                     // 0.0
/*202 */     /* fragmentation unit (FU) */                                                                  // 0.0
/*204 */     case 49:                                                                                       // 0.0
/*206 */         /* pass the HEVC payload header */                                                         // 0.0
/*208 */         buf += RTP_HEVC_PAYLOAD_HEADER_SIZE;                                                       // 0.0
/*210 */         len -= RTP_HEVC_PAYLOAD_HEADER_SIZE;                                                       // 0.0
/*214 */         /*                                                                                         // 0.0
/*216 */          *    decode the FU header                                                                 // 0.0
/*218 */          *                                                                                         // 0.0
/*220 */          *     0 1 2 3 4 5 6 7                                                                     // 0.0
/*222 */          *    +-+-+-+-+-+-+-+-+                                                                    // 0.0
/*224 */          *    |S|E|  FuType   |                                                                    // 0.0
/*226 */          *    +---------------+                                                                    // 0.0
/*228 */          *                                                                                         // 0.0
/*230 */          *       Start fragment (S): 1 bit                                                         // 0.0
/*232 */          *       End fragment (E): 1 bit                                                           // 0.0
/*234 */          *       FuType: 6 bits                                                                    // 0.0
/*236 */          */                                                                                        // 0.0
/*238 */         first_fragment = buf[0] & 0x80;                                                            // 0.0
/*240 */         last_fragment  = buf[0] & 0x40;                                                            // 0.0
/*242 */         fu_type        = buf[0] & 0x3f;                                                            // 0.0
/*246 */         /* pass the HEVC FU header */                                                              // 0.0
/*248 */         buf += RTP_HEVC_FU_HEADER_SIZE;                                                            // 0.0
/*250 */         len -= RTP_HEVC_FU_HEADER_SIZE;                                                            // 0.0
/*254 */         /* pass the HEVC DONL field */                                                             // 0.0
/*256 */         if (rtp_hevc_ctx->using_donl_field) {                                                      // 0.0
/*258 */             buf += RTP_HEVC_DONL_FIELD_SIZE;                                                       // 0.0
/*260 */             len -= RTP_HEVC_DONL_FIELD_SIZE;                                                       // 0.0
/*262 */         }                                                                                          // 0.0
/*266 */         av_dlog(ctx, " FU type %d with %d bytes\n", fu_type, len);                                 // 0.0
/*270 */         if (len <= 0) {                                                                            // 0.0
/*272 */             /* sanity check for size of input packet: 1 byte payload at least */                   // 0.0
/*274 */             av_log(ctx, AV_LOG_ERROR,                                                              // 0.0
/*276 */                    "Too short RTP/HEVC packet, got %d bytes of NAL unit type %d\n",                // 0.0
/*278 */                    len, nal_type);                                                                 // 0.0
/*280 */             return AVERROR_INVALIDDATA;                                                            // 0.0
/*282 */         }                                                                                          // 0.0
/*286 */         if (first_fragment && last_fragment) {                                                     // 0.0
/*288 */             av_log(ctx, AV_LOG_ERROR, "Illegal combination of S and E bit in RTP/HEVC packet\n");  // 0.0
/*290 */             return AVERROR_INVALIDDATA;                                                            // 0.0
/*292 */         }                                                                                          // 0.0
/*296 */         new_nal_header[0] = (rtp_pl[0] & 0x81) | (fu_type << 1);                                   // 0.0
/*298 */         new_nal_header[1] = rtp_pl[1];                                                             // 0.0
/*302 */         res = ff_h264_handle_frag_packet(pkt, buf, len, first_fragment,                            // 0.0
/*304 */                                          new_nal_header, sizeof(new_nal_header));                  // 0.0
/*308 */         break;                                                                                     // 0.0
/*310 */     /* PACI packet */                                                                              // 0.0
/*312 */     case 50:                                                                                       // 0.0
/*314 */         /* Temporal scalability control information (TSCI) */                                      // 0.0
/*316 */         avpriv_report_missing_feature(ctx, "PACI packets for RTP/HEVC\n");                         // 0.0
/*318 */         res = AVERROR_PATCHWELCOME;                                                                // 0.0
/*320 */         break;                                                                                     // 0.0
/*322 */     }                                                                                              // 0.0
/*326 */     pkt->stream_index = st->index;                                                                 // 0.0
/*330 */     return res;                                                                                    // 0.0
/*332 */ }                                                                                                  // 0.0
