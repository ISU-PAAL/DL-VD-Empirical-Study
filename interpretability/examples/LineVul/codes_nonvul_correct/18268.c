// commit message FFmpeg@5e5f75cf8a (target=0, prob=0.22309533, correct=True): remove pts set hack, this is no more correct
/*0  */ static void ffm_write_data(AVFormatContext *s,                                // (13) 0.03125
/*2  */                            const uint8_t *buf, int size,                      // (0) 0.07708
/*4  */                            int64_t pts, int header)                           // (2) 0.07292
/*6  */ {                                                                             // (25) 0.002083
/*8  */     FFMContext *ffm = s->priv_data;                                           // (12) 0.03333
/*10 */     int len;                                                                  // (22) 0.0125
/*14 */     if (header && ffm->frame_offset == 0) {                                   // (10) 0.03542
/*16 */         ffm->frame_offset = ffm->packet_ptr - ffm->packet + FFM_HEADER_SIZE;  // (1) 0.075
/*18 */         ffm->pts = pts;                                                       // (14) 0.03125
/*20 */     }                                                                         // (23) 0.008333
/*24 */     /* write as many packets as needed */                                     // (17) 0.02292
/*26 */     while (size > 0) {                                                        // (20) 0.02083
/*28 */         len = ffm->packet_end - ffm->packet_ptr;                              // (5) 0.05208
/*30 */         if (len > size)                                                       // (16) 0.02708
/*32 */             len = size;                                                       // (15) 0.03125
/*34 */         memcpy(ffm->packet_ptr, buf, len);                                    // (6) 0.04792
/*38 */         ffm->packet_ptr += len;                                               // (11) 0.03542
/*40 */         buf += len;                                                           // (18) 0.02292
/*42 */         size -= len;                                                          // (19) 0.02292
/*44 */         if (ffm->packet_ptr >= ffm->packet_end) {                             // (3) 0.05417
/*46 */             /* special case : no pts in packet : we leave the current one */  // (4) 0.05417
/*48 */             if (ffm->pts == 0)                                                // (8) 0.04375
/*50 */                 ffm->pts = pts;                                               // (7) 0.04792
/*54 */             flush_packet(s);                                                  // (9) 0.0375
/*56 */         }                                                                     // (21) 0.01667
/*58 */     }                                                                         // (24) 0.008333
/*60 */ }                                                                             // (26) 0.002083
