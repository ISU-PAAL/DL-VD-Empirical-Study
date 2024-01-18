// commit message FFmpeg@d1f3e475f9 (target=1, prob=0.9990206, correct=True): avformat/test/fifo_muxer: add check for FailingMuxerPacketData alloc
/*0  */ static int prepare_packet(AVPacket *pkt,const FailingMuxerPacketData *pkt_data, int64_t pts)  // (0) 0.2071
/*2  */ {                                                                                             // (8) 0.005917
/*4  */     int ret;                                                                                  // (7) 0.0355
/*6  */     FailingMuxerPacketData *data = av_malloc(sizeof(*data));                                  // (3) 0.142
/*11 */     memcpy(data, pkt_data, sizeof(FailingMuxerPacketData));                                   // (2) 0.1479
/*13 */     ret = av_packet_from_data(pkt, (uint8_t*) data, sizeof(*data));                           // (1) 0.1716
/*17 */     pkt->pts = pkt->dts = pts;                                                                // (4) 0.1006
/*19 */     pkt->duration = 1;                                                                        // (5) 0.05917
/*23 */     return ret;                                                                               // (6) 0.0355
