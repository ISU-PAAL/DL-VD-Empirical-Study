// commit message FFmpeg@e15824e75b (target=1, prob=0.5326243, correct=True): avformat/rtpdec_h261: Fix sanity checks
/*0   */ int ff_h261_handle_packet(AVFormatContext *ctx, PayloadContext *data,                        // (6) 0.04492
/*2   */                           AVStream *st, AVPacket *pkt, uint32_t *timestamp,                  // (1) 0.08782
/*4   */                           const uint8_t *buf, int len, uint16_t seq, int flags)              // (2) 0.08781
/*6   */ {                                                                                            // (20) 0.001956
/*8   */     int sbit, ebit, gobn, mbap, quant;                                                       // (12) 0.03709
/*10  */     int res;                                                                                 // (16) 0.01172
/*14  */     //av_log(ctx, AV_LOG_DEBUG, "got h261 RTP packet with time: %u\n", timestamp);           // (4) 0.06508
/*18  */     /* drop data of previous packets in case of non-continuous (loss) packet stream */       // (8) 0.04297
/*20  */     if (data->buf && data->timestamp != *timestamp) {                                        // (13) 0.03708
/*22  */         h261_free_dyn_buffer(&data->buf);                                                    // (10) 0.04098
/*24  */     }                                                                                        // (19) 0.007806
/*28  */     /* sanity check for size of input packet */                                              // (15) 0.02342
/*30  */     if (len < 5 /* 4 bytes header and 1 byte payload at least */) {                          // (9) 0.041
/*32  */         av_log(ctx, AV_LOG_ERROR, "Too short H.261 RTP packet\n");                           // (5) 0.06051
/*34  */         return AVERROR_INVALIDDATA;                                                          // (14) 0.03317
/*36  */     }                                                                                        // (18) 0.007807
/*40  */     /*                                                                                       // (17) 0.007808
/*42  */       decode the H.261 payload header according to section 4.1 of RFC 4587:                  // (7) 0.04489
/*44  */       (uses 4 bytes between RTP header and H.261 stream per packet)                          // (11) 0.04098
/*48  */          0                   1                   2                   3                       // (0) 0.1288
/*50  */          0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1                     // (3) 0.07805
/*52  */         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                    // 0.0
/*54  */         |SBIT |EBIT |I|V| GOBN  |   MBAP  |  QUANT  |  HMVD   |  VMVD   |                    // 0.0
/*56  */         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                    // 0.0
/*60  */            Start bit position (SBIT): 3 bits                                                 // 0.0
/*62  */            End bit position (EBIT): 3 bits                                                   // 0.0
/*64  */            INTRA-frame encoded data (I): 1 bit                                               // 0.0
/*66  */            Motion Vector flag (V): 1 bit                                                     // 0.0
/*68  */            GOB number (GOBN): 4 bits                                                         // 0.0
/*70  */            Macroblock address predictor (MBAP): 5 bits                                       // 0.0
/*72  */            Quantizer (QUANT): 5 bits                                                         // 0.0
/*74  */            Horizontal motion vector data (HMVD): 5 bits                                      // 0.0
/*76  */            Vertical motion vector data (VMVD): 5 bits                                        // 0.0
/*80  */     */                                                                                       // 0.0
/*82  */     sbit  =  (buf[0] >> 5) & 0x07;                                                           // 0.0
/*84  */     ebit  =  (buf[0] >> 2) & 0x07;                                                           // 0.0
/*86  */     gobn  =  (buf[1] >> 4) & 0x0f;                                                           // 0.0
/*88  */     mbap  = ((buf[1] << 1) & 0x1e) | ((buf[1] >> 7) & 0x01);                                 // 0.0
/*90  */     quant =  (buf[1] >> 4) & 0x0f;                                                           // 0.0
/*94  */     /* pass the H.261 payload header and continue with the actual payload */                 // 0.0
/*96  */     buf += RTP_H261_PAYLOAD_HEADER_SIZE;                                                     // 0.0
/*98  */     len -= RTP_H261_PAYLOAD_HEADER_SIZE;                                                     // 0.0
/*102 */     /* start frame buffering with new dynamic buffer */                                      // 0.0
/*104 */     if (!data->buf) {                                                                        // 0.0
/*106 */         /* sanity check: a new frame starts with gobn=0, sbit=0, mbap=0, uqnat=0 */          // 0.0
/*108 */         if (!gobn  && !sbit && !mbap && !quant){                                             // 0.0
/*110 */             res = avio_open_dyn_buf(&data->buf);                                             // 0.0
/*112 */             if (res < 0)                                                                     // 0.0
/*114 */                 return res;                                                                  // 0.0
/*116 */             /* update the timestamp in the frame packet with the one from the RTP packet */  // 0.0
/*118 */             data->timestamp = *timestamp;                                                    // 0.0
/*120 */         } else {                                                                             // 0.0
/*122 */             /* frame not started yet, need more packets */                                   // 0.0
/*124 */             return AVERROR(EAGAIN);                                                          // 0.0
/*126 */         }                                                                                    // 0.0
/*128 */     }                                                                                        // 0.0
/*132 */     /* do the "byte merging" at the boundaries of two consecutive frame fragments */         // 0.0
/*134 */     if (data->endbyte_bits || sbit) {                                                        // 0.0
/*136 */         if (data->endbyte_bits == sbit) {                                                    // 0.0
/*138 */             data->endbyte |= buf[0] & (0xff >> sbit);                                        // 0.0
/*140 */             data->endbyte_bits = 0;                                                          // 0.0
/*142 */             buf++;                                                                           // 0.0
/*144 */             len--;                                                                           // 0.0
/*146 */             avio_w8(data->buf, data->endbyte);                                               // 0.0
/*148 */         } else {                                                                             // 0.0
/*150 */             /* ebit/sbit values inconsistent, assuming packet loss */                        // 0.0
/*152 */             GetBitContext gb;                                                                // 0.0
/*154 */             init_get_bits(&gb, buf, len*8 - ebit);                                           // 0.0
/*156 */             skip_bits(&gb, sbit);                                                            // 0.0
/*158 */             if (data->endbyte_bits) {                                                        // 0.0
/*160 */                 data->endbyte |= get_bits(&gb, 8 - data->endbyte_bits);                      // 0.0
/*162 */                 avio_w8(data->buf, data->endbyte);                                           // 0.0
/*164 */             }                                                                                // 0.0
/*166 */             while (get_bits_left(&gb) >= 8)                                                  // 0.0
/*168 */                 avio_w8(data->buf, get_bits(&gb, 8));                                        // 0.0
/*170 */             data->endbyte_bits = get_bits_left(&gb);                                         // 0.0
/*172 */             if (data->endbyte_bits)                                                          // 0.0
/*174 */                 data->endbyte = get_bits(&gb, data->endbyte_bits) <<                         // 0.0
/*176 */                                 (8 - data->endbyte_bits);                                    // 0.0
/*178 */             ebit = 0;                                                                        // 0.0
/*180 */             len = 0;                                                                         // 0.0
/*182 */         }                                                                                    // 0.0
/*184 */     }                                                                                        // 0.0
/*186 */     if (ebit) {                                                                              // 0.0
/*188 */         if (len > 0)                                                                         // 0.0
/*190 */             avio_write(data->buf, buf, len - 1);                                             // 0.0
/*192 */         data->endbyte_bits = 8 - ebit;                                                       // 0.0
/*194 */         data->endbyte = buf[len - 1] & (0xff << ebit);                                       // 0.0
/*196 */     } else {                                                                                 // 0.0
/*198 */         avio_write(data->buf, buf, len);                                                     // 0.0
/*200 */     }                                                                                        // 0.0
/*204 */     /* RTP marker bit means: last fragment of current frame was received;                    // 0.0
/*206 */        otherwise, an additional fragment is needed for the current frame */                  // 0.0
/*208 */     if (!(flags & RTP_FLAG_MARKER))                                                          // 0.0
/*210 */         return AVERROR(EAGAIN);                                                              // 0.0
/*214 */     /* write the completed last byte from the "byte merging" */                              // 0.0
/*216 */     if (data->endbyte_bits)                                                                  // 0.0
/*218 */         avio_w8(data->buf, data->endbyte);                                                   // 0.0
/*220 */     data->endbyte_bits = 0;                                                                  // 0.0
/*224 */     /* close frame buffering and create resulting A/V packet */                              // 0.0
/*226 */     res = ff_rtp_finalize_packet(pkt, &data->buf, st->index);                                // 0.0
/*228 */     if (res < 0)                                                                             // 0.0
/*230 */         return res;                                                                          // 0.0
/*234 */     return 0;                                                                                // 0.0
/*236 */ }                                                                                            // 0.0
