// commit message FFmpeg@a4fec9a7ea (target=1, prob=0.9991153, correct=True): rtmppkt: Check for packet size mismatches
/*0  */ static int rtmp_packet_read_one_chunk(URLContext *h, RTMPPacket *p,               // (1) 0.09954
/*1  */                                       int chunk_size, RTMPPacket **prev_pkt_ptr,  // (3) 0.06638
/*2  */                                       int *nb_prev_pkt, uint8_t hdr)              // (4) 0.05951
/*3  */ {                                                                                 // (23) 0.001439
/*4  */     uint8_t buf[16];                                                              // (14) 0.01929
/*5  */     int channel_id, timestamp, size;                                              // (0) 0.1644
/*6  */     uint32_t ts_field; // non-extended timestamp or delta field                   // (2) 0.08452
/*7  */     uint32_t extra = 0;                                                           // (20) 0.01426
/*8  */     enum RTMPPacketType type;                                                     // (17) 0.01641
/*9  */     int written = 0;                                                              // (21) 0.01217
/*10 */     int ret, toread;                                                              // (8) 0.03359
/*11 */     RTMPPacket *prev_pkt;                                                         // (19) 0.01534
/*12 */     written++;                                                                    // (22) 0.006252
/*13 */     channel_id = hdr & 0x3F;                                                      // (16) 0.01719
/*14 */     if (channel_id < 2) { //special case for channel number >= 64                 // (11) 0.0253
/*15 */         buf[1] = 0;                                                               // (15) 0.01835
/*16 */         if (ffurl_read_complete(h, buf, channel_id + 1) != channel_id + 1)        // (7) 0.0414
/*17 */             return AVERROR(EIO);                                                  // (12) 0.02161
/*18 */         written += channel_id + 1;                                                // (18) 0.01614
/*19 */         channel_id = AV_RL16(buf) + 64;                                           // (10) 0.02567
/*20 */     if ((ret = ff_rtmp_check_alloc_array(prev_pkt_ptr, nb_prev_pkt,               // (5) 0.05334
/*21 */                                          channel_id)) < 0)                        // (6) 0.05003
/*22 */         return ret;                                                               // (9) 0.02821
/*23 */     prev_pkt = *prev_pkt_ptr;                                                     // (13) 0.02114
/*24 */     size  = prev_pkt[channel_id].size;                                            // 0.0
/*25 */     type  = prev_pkt[channel_id].type;                                            // 0.0
/*26 */     extra = prev_pkt[channel_id].extra;                                           // 0.0
/*27 */     hdr >>= 6; // header size indicator                                           // 0.0
/*28 */     if (hdr == RTMP_PS_ONEBYTE) {                                                 // 0.0
/*29 */         ts_field = prev_pkt[channel_id].ts_field;                                 // 0.0
/*30 */     } else {                                                                      // 0.0
/*31 */         if (ffurl_read_complete(h, buf, 3) != 3)                                  // 0.0
/*32 */             return AVERROR(EIO);                                                  // 0.0
/*33 */         written += 3;                                                             // 0.0
/*34 */         ts_field = AV_RB24(buf);                                                  // 0.0
/*35 */         if (hdr != RTMP_PS_FOURBYTES) {                                           // 0.0
/*36 */             if (ffurl_read_complete(h, buf, 3) != 3)                              // 0.0
/*37 */                 return AVERROR(EIO);                                              // 0.0
/*38 */             written += 3;                                                         // 0.0
/*39 */             size = AV_RB24(buf);                                                  // 0.0
/*40 */             if (ffurl_read_complete(h, buf, 1) != 1)                              // 0.0
/*41 */                 return AVERROR(EIO);                                              // 0.0
/*42 */             written++;                                                            // 0.0
/*43 */             type = buf[0];                                                        // 0.0
/*44 */             if (hdr == RTMP_PS_TWELVEBYTES) {                                     // 0.0
/*45 */                 if (ffurl_read_complete(h, buf, 4) != 4)                          // 0.0
/*46 */                     return AVERROR(EIO);                                          // 0.0
/*47 */                 written += 4;                                                     // 0.0
/*48 */                 extra = AV_RL32(buf);                                             // 0.0
/*49 */     if (ts_field == 0xFFFFFF) {                                                   // 0.0
/*50 */         if (ffurl_read_complete(h, buf, 4) != 4)                                  // 0.0
/*51 */             return AVERROR(EIO);                                                  // 0.0
/*52 */         timestamp = AV_RB32(buf);                                                 // 0.0
/*53 */     } else {                                                                      // 0.0
/*54 */         timestamp = ts_field;                                                     // 0.0
/*55 */     if (hdr != RTMP_PS_TWELVEBYTES)                                               // 0.0
/*56 */         timestamp += prev_pkt[channel_id].timestamp;                              // 0.0
/*57 */     if (!prev_pkt[channel_id].read) {                                             // 0.0
/*58 */         if ((ret = ff_rtmp_packet_create(p, channel_id, type, timestamp,          // 0.0
/*59 */                                          size)) < 0)                              // 0.0
/*60 */             return ret;                                                           // 0.0
/*61 */         p->read = written;                                                        // 0.0
/*62 */         p->offset = 0;                                                            // 0.0
/*63 */         prev_pkt[channel_id].ts_field   = ts_field;                               // 0.0
/*64 */         prev_pkt[channel_id].timestamp  = timestamp;                              // 0.0
/*65 */     } else {                                                                      // 0.0
/*66 */         // previous packet in this channel hasn't completed reading               // 0.0
/*67 */         RTMPPacket *prev = &prev_pkt[channel_id];                                 // 0.0
/*68 */         p->data          = prev->data;                                            // 0.0
/*69 */         p->size          = prev->size;                                            // 0.0
/*70 */         p->channel_id    = prev->channel_id;                                      // 0.0
/*71 */         p->type          = prev->type;                                            // 0.0
/*72 */         p->ts_field      = prev->ts_field;                                        // 0.0
/*73 */         p->extra         = prev->extra;                                           // 0.0
/*74 */         p->offset        = prev->offset;                                          // 0.0
/*75 */         p->read          = prev->read + written;                                  // 0.0
/*76 */         p->timestamp     = prev->timestamp;                                       // 0.0
/*77 */         prev->data       = NULL;                                                  // 0.0
/*78 */     p->extra = extra;                                                             // 0.0
/*79 */     // save history                                                               // 0.0
/*80 */     prev_pkt[channel_id].channel_id = channel_id;                                 // 0.0
/*81 */     prev_pkt[channel_id].type       = type;                                       // 0.0
/*82 */     prev_pkt[channel_id].size       = size;                                       // 0.0
/*83 */     prev_pkt[channel_id].extra      = extra;                                      // 0.0
/*84 */     size = size - p->offset;                                                      // 0.0
/*85 */     toread = FFMIN(size, chunk_size);                                             // 0.0
/*86 */     if (ffurl_read_complete(h, p->data + p->offset, toread) != toread) {          // 0.0
/*87 */         ff_rtmp_packet_destroy(p);                                                // 0.0
/*88 */         return AVERROR(EIO);                                                      // 0.0
/*89 */     size      -= toread;                                                          // 0.0
/*90 */     p->read   += toread;                                                          // 0.0
/*91 */     p->offset += toread;                                                          // 0.0
/*92 */     if (size > 0) {                                                               // 0.0
/*93 */        RTMPPacket *prev = &prev_pkt[channel_id];                                  // 0.0
/*94 */        prev->data = p->data;                                                      // 0.0
/*95 */        prev->read = p->read;                                                      // 0.0
/*96 */        prev->offset = p->offset;                                                  // 0.0
/*97 */        return AVERROR(EAGAIN);                                                    // 0.0
/*98 */     prev_pkt[channel_id].read = 0; // read complete; reset if needed              // 0.0
/*99 */     return p->read;                                                               // 0.0
