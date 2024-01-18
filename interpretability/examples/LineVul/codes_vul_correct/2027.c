// commit message FFmpeg@604c9b1196 (target=1, prob=0.55786693, correct=True): rtsp: move the CONFIG_ macros to the beginning of the check
/*0  */ void ff_rtsp_undo_setup(AVFormatContext *s, int send_packets)                 // (10) 0.04492
/*2  */ {                                                                             // (18) 0.001953
/*4  */     RTSPState *rt = s->priv_data;                                             // (14) 0.0293
/*6  */     int i;                                                                    // (17) 0.01172
/*10 */     for (i = 0; i < rt->nb_rtsp_streams; i++) {                               // (7) 0.05078
/*12 */         RTSPStream *rtsp_st = rt->rtsp_streams[i];                            // (5) 0.05664
/*14 */         if (!rtsp_st)                                                         // (15) 0.0293
/*16 */             continue;                                                         // (16) 0.02539
/*18 */         if (rtsp_st->transport_priv) {                                        // (11) 0.04102
/*20 */             if (s->oformat) {                                                 // (12) 0.03711
/*22 */                 AVFormatContext *rtpctx = rtsp_st->transport_priv;            // (4) 0.06641
/*24 */                 av_write_trailer(rtpctx);                                     // (6) 0.05078
/*26 */                 if (rt->lower_transport == RTSP_LOWER_TRANSPORT_TCP) {        // (2) 0.07617
/*28 */                     uint8_t *ptr;                                             // (8) 0.05078
/*30 */                     if (CONFIG_RTSP_MUXER && rtpctx->pb && send_packets)      // (1) 0.08203
/*32 */                         ff_rtsp_tcp_write_packet(s, rtsp_st);                 // (0) 0.08789
/*34 */                     avio_close_dyn_buf(rtpctx->pb, &ptr);                     // (3) 0.07422
/*36 */                     av_free(ptr);                                             // (9) 0.04883
/*38 */                 } else {                                                      // (13) 0.03516
/*40 */                     avio_close(rtpctx->pb);                                   // 0.0
/*42 */                 }                                                             // 0.0
/*44 */                 avformat_free_context(rtpctx);                                // 0.0
/*46 */             } else if (rt->transport == RTSP_TRANSPORT_RDT && CONFIG_RTPDEC)  // 0.0
/*48 */                 ff_rdt_parse_close(rtsp_st->transport_priv);                  // 0.0
/*50 */             else if (rt->transport == RTSP_TRANSPORT_RTP && CONFIG_RTPDEC)    // 0.0
/*52 */                 ff_rtp_parse_close(rtsp_st->transport_priv);                  // 0.0
/*54 */         }                                                                     // 0.0
/*56 */         rtsp_st->transport_priv = NULL;                                       // 0.0
/*58 */         if (rtsp_st->rtp_handle)                                              // 0.0
/*60 */             ffurl_close(rtsp_st->rtp_handle);                                 // 0.0
/*62 */         rtsp_st->rtp_handle = NULL;                                           // 0.0
/*64 */     }                                                                         // 0.0
/*66 */ }                                                                             // 0.0
