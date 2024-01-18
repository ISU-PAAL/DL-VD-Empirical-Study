// commit message FFmpeg@6e1b1a27a4 (target=1, prob=0.3661283, correct=False): avcodec/avpacket: Use av_free_packet() in error cleanups
/*0  */ static int copy_packet_data(AVPacket *pkt, AVPacket *src, int dup)  // (1) 0.06203
/*2  */ {                                                                   // (26) 0.002481
/*4  */     pkt->data      = NULL;                                          // (9) 0.03722
/*6  */     pkt->side_data = NULL;                                          // (14) 0.02978
/*8  */     if (pkt->buf) {                                                 // (18) 0.0273
/*10 */         AVBufferRef *ref = av_buffer_ref(src->buf);                 // (3) 0.05707
/*12 */         if (!ref)                                                   // (19) 0.0273
/*14 */             return AVERROR(ENOMEM);                                 // (4) 0.04963
/*16 */         pkt->buf  = ref;                                            // (10) 0.03722
/*18 */         pkt->data = ref->data;                                      // (8) 0.0397
/*20 */     } else {                                                        // (20) 0.01489
/*22 */         DUP_DATA(pkt->data, src->data, pkt->size, 1, ALLOC_BUF);    // (0) 0.08189
/*24 */     }                                                               // (22) 0.009926
/*26 */ #if FF_API_DESTRUCT_PACKET                                          // (12) 0.03226
/*28 */ FF_DISABLE_DEPRECATION_WARNINGS                                     // (16) 0.0273
/*30 */     pkt->destruct = dummy_destruct_packet;                          // (11) 0.03722
/*32 */ FF_ENABLE_DEPRECATION_WARNINGS                                      // (17) 0.0273
/*34 */ #endif                                                              // (25) 0.004963
/*36 */     if (pkt->side_data_elems && dup)                                // (7) 0.04218
/*38 */         pkt->side_data = src->side_data;                            // (5) 0.04963
/*40 */     if (pkt->side_data_elems && !dup) {                             // (6) 0.04963
/*42 */         return av_copy_packet_side_data(pkt, src);                  // (2) 0.05955
/*44 */     }                                                               // (23) 0.009926
/*46 */     return 0;                                                       // (21) 0.01489
/*50 */ failed_alloc:                                                       // (24) 0.009926
/*52 */     av_destruct_packet(pkt);                                        // (13) 0.03226
/*54 */     return AVERROR(ENOMEM);                                         // (15) 0.02978
/*56 */ }                                                                   // (27) 0.002481
