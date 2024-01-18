// commit message FFmpeg@0dbb48d91e (target=1, prob=0.3692748, correct=False): better and simpler logic for MPEG muxing - fixed rare MPEG muxing PTS generation bug (stuffing is added in such rare cases) - fixed AC3 payload size generation - generate correct AC3 frame header (need spec checking)
/*0  */ static int mpeg_mux_write_packet(AVFormatContext *ctx, int stream_index,      // (4) 0.04687
/*2  */                                  const uint8_t *buf, int size, int64_t pts)   // (0) 0.0957
/*4  */ {                                                                             // (28) 0.001954
/*6  */     MpegMuxContext *s = ctx->priv_data;                                       // (10) 0.03516
/*8  */     AVStream *st = ctx->streams[stream_index];                                // (9) 0.03516
/*10 */     StreamInfo *stream = st->priv_data;                                       // (17) 0.02734
/*12 */     int64_t dts;                                                              // (21) 0.01953
/*14 */     int len;                                                                  // (22) 0.01172
/*18 */     /* XXX: system clock should be computed precisely, especially for         // (15) 0.0293
/*20 */        CBR case. The current mode gives at least something coherent */        // (6) 0.03711
/*22 */     if (stream_index == s->scr_stream_index)                                  // (11) 0.03516
/*24 */         s->last_scr = pts;                                                    // (13) 0.03125
/*26 */                                                                               // (23) 0.007821
/*28 */ #if 0                                                                         // (26) 0.005859
/*30 */     printf("%d: pts=%0.3f scr=%0.3f\n",                                       // (2) 0.05078
/*32 */            stream_index, pts / 90000.0, s->last_scr / 90000.0);               // (1) 0.06445
/*34 */ #endif                                                                        // (27) 0.003906
/*36 */                                                                               // (25) 0.007812
/*38 */     /* XXX: currently no way to pass dts, will change soon */                 // (7) 0.03516
/*40 */     dts = AV_NOPTS_VALUE;                                                     // (18) 0.02734
/*44 */     /* we assume here that pts != AV_NOPTS_VALUE */                           // (8) 0.03516
/*46 */     if (stream->start_pts == AV_NOPTS_VALUE) {                                // (5) 0.04101
/*48 */         stream->start_pts = pts;                                              // (14) 0.03125
/*50 */         stream->start_dts = dts;                                              // (12) 0.0332
/*52 */     }                                                                         // (24) 0.007812
/*54 */     while (size > 0) {                                                        // (20) 0.01953
/*56 */         len = s->packet_data_max_size - stream->buffer_ptr;                   // (3) 0.05078
/*58 */         if (len > size)                                                       // (19) 0.02539
/*60 */             len = size;                                                       // (16) 0.0293
/*62 */         memcpy(stream->buffer + stream->buffer_ptr, buf, len);                // 0.0
/*64 */         stream->buffer_ptr += len;                                            // 0.0
/*66 */         buf += len;                                                           // 0.0
/*68 */         size -= len;                                                          // 0.0
/*70 */         while (stream->buffer_ptr >= s->packet_data_max_size) {               // 0.0
/*72 */             /* output the packet */                                           // 0.0
/*74 */             flush_packet(ctx, stream_index,                                   // 0.0
/*76 */                          stream->start_pts, stream->start_dts, s->last_scr);  // 0.0
/*78 */             /* Make sure only the FIRST pes packet for this frame has         // 0.0
/*80 */                a timestamp */                                                 // 0.0
/*82 */             stream->start_pts = AV_NOPTS_VALUE;                               // 0.0
/*84 */             stream->start_dts = AV_NOPTS_VALUE;                               // 0.0
/*86 */         }                                                                     // 0.0
/*88 */     }                                                                         // 0.0
/*90 */     return 0;                                                                 // 0.0
/*92 */ }                                                                             // 0.0
