// commit message FFmpeg@9a0f60a0f8 (target=0, prob=0.26465803, correct=True): avcodec/mpeg4videodec: Use check_marker()
/*0  */ static int mpeg4_decode_gop_header(MpegEncContext *s, GetBitContext *gb)  // (1) 0.1227
/*2  */ {                                                                         // (14) 0.004545
/*4  */     int hours, minutes, seconds;                                          // (8) 0.04545
/*8  */     if (!show_bits(gb, 23)) {                                             // (4) 0.06364
/*10 */         av_log(s->avctx, AV_LOG_WARNING, "GOP header invalid\n");         // (0) 0.1318
/*12 */         return -1;                                                        // (7) 0.05
/*14 */     }                                                                     // (13) 0.01818
/*18 */     hours   = get_bits(gb, 5);                                            // (3) 0.06818
/*20 */     minutes = get_bits(gb, 6);                                            // (5) 0.05909
/*22 */     skip_bits1(gb);                                                       // (9) 0.04545
/*24 */     seconds = get_bits(gb, 6);                                            // (6) 0.05909
/*28 */     s->time_base = seconds + 60*(minutes + 60*hours);                     // (2) 0.09545
/*32 */     skip_bits1(gb);                                                       // (10) 0.04545
/*34 */     skip_bits1(gb);                                                       // (11) 0.04545
/*38 */     return 0;                                                             // (12) 0.02727
/*40 */ }                                                                         // (15) 0.004545
