// commit message FFmpeg@84f0aba18d (target=1, prob=0.55355656, correct=True): handler can be NULL if we did not support this dynamic format (codec). Fixes issue 1658 (the crasher), although the format itself is obviously still unsupported.
/*0  */ ff_rdt_parse_open(AVFormatContext *ic, int first_stream_of_set_idx,             // (3) 0.07988
/*2  */                   void *priv_data, RTPDynamicProtocolHandler *handler)          // (1) 0.09467
/*4  */ {                                                                               // (17) 0.002959
/*6  */     RDTDemuxContext *s = av_mallocz(sizeof(RDTDemuxContext));                   // (4) 0.07692
/*8  */     if (!s)                                                                     // (14) 0.02071
/*10 */         return NULL;                                                            // (12) 0.02959
/*14 */     s->ic = ic;                                                                 // (13) 0.02663
/*16 */     s->streams = &ic->streams[first_stream_of_set_idx];                         // (5) 0.07396
/*18 */     do {                                                                        // (16) 0.01479
/*20 */         s->n_streams++;                                                         // (9) 0.04142
/*22 */     } while (first_stream_of_set_idx + s->n_streams < ic->nb_streams &&         // (2) 0.09172
/*24 */              s->streams[s->n_streams]->priv_data == s->streams[0]->priv_data);  // (0) 0.1213
/*26 */     s->prev_set_id    = -1;                                                     // (7) 0.0503
/*28 */     s->prev_stream_id = -1;                                                     // (10) 0.04142
/*30 */     s->prev_timestamp = -1;                                                     // (11) 0.03846
/*32 */     s->parse_packet = handler->parse_packet;                                    // (6) 0.0503
/*34 */     s->dynamic_protocol_context = priv_data;                                    // (8) 0.0503
/*38 */     return s;                                                                   // (15) 0.01775
/*40 */ }                                                                               // (18) 0.002959
