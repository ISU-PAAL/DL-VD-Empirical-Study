// commit message FFmpeg@80ca19f766 (target=0, prob=0.070677064, correct=True): Make CHECK_STREAM_PTR macro in Interplay Video decoder usable with non-default pointers, it will be useful for checking motion values data in 16-bit variant of this codec.
/*0   */ static int ipvideo_decode_block_opcode_0x8(IpvideoContext *s)                // (5) 0.04688
/*2   */ {                                                                            // (25) 0.001953
/*4   */     int x, y;                                                                // (23) 0.01563
/*6   */     unsigned char P[2];                                                      // (20) 0.01758
/*8   */     unsigned int flags = 0;                                                  // (21) 0.01758
/*12  */     /* 2-color encoding for each 4x4 quadrant, or 2-color encoding on        // (7) 0.04297
/*14  */      * either top and bottom or left and right halves */                     // (13) 0.0293
/*16  */     CHECK_STREAM_PTR(2);                                                     // (18) 0.02734
/*20  */     P[0] = *s->stream_ptr++;                                                 // (15) 0.0293
/*22  */     P[1] = *s->stream_ptr++;                                                 // (14) 0.0293
/*26  */     if (P[0] <= P[1]) {                                                      // (17) 0.0293
/*30  */         CHECK_STREAM_PTR(14);                                                // (11) 0.03516
/*32  */         s->stream_ptr -= 2;                                                  // (16) 0.0293
/*36  */         for (y = 0; y < 16; y++) {                                           // (9) 0.03906
/*38  */             // new values for each 4x4 block                                 // (8) 0.03906
/*40  */             if (!(y & 3)) {                                                  // (10) 0.03711
/*42  */                 P[0] = *s->stream_ptr++; P[1] = *s->stream_ptr++;            // (0) 0.07617
/*44  */                 flags = bytestream_get_le16(&s->stream_ptr);                 // (2) 0.0625
/*46  */             }                                                                // (19) 0.02344
/*50  */             for (x = 0; x < 4; x++, flags >>= 1)                             // (4) 0.05664
/*52  */                 *s->pixel_ptr++ = P[flags & 1];                              // (3) 0.05664
/*54  */             s->pixel_ptr += s->stride - 4;                                   // (6) 0.04687
/*56  */             // switch to right half                                          // (12) 0.03125
/*58  */             if (y == 7) s->pixel_ptr -= 8 * s->stride - 4;                   // (1) 0.0625
/*60  */         }                                                                    // (22) 0.01563
/*64  */     } else {                                                                 // (24) 0.01172
/*68  */         /* need 10 more bytes */                                             // 0.0
/*70  */         CHECK_STREAM_PTR(10);                                                // 0.0
/*74  */         if (s->stream_ptr[4] <= s->stream_ptr[5]) {                          // 0.0
/*78  */             flags = bytestream_get_le32(&s->stream_ptr);                     // 0.0
/*82  */             /* vertical split; left & right halves are 2-color encoded */    // 0.0
/*86  */             for (y = 0; y < 16; y++) {                                       // 0.0
/*88  */                 for (x = 0; x < 4; x++, flags >>= 1)                         // 0.0
/*90  */                     *s->pixel_ptr++ = P[flags & 1];                          // 0.0
/*92  */                 s->pixel_ptr += s->stride - 4;                               // 0.0
/*94  */                 // switch to right half                                      // 0.0
/*96  */                 if (y == 7) {                                                // 0.0
/*98  */                     s->pixel_ptr -= 8 * s->stride - 4;                       // 0.0
/*100 */                     P[0] = *s->stream_ptr++; P[1] = *s->stream_ptr++;        // 0.0
/*102 */                     flags = bytestream_get_le32(&s->stream_ptr);             // 0.0
/*104 */                 }                                                            // 0.0
/*106 */             }                                                                // 0.0
/*110 */         } else {                                                             // 0.0
/*114 */             /* horizontal split; top & bottom halves are 2-color encoded */  // 0.0
/*118 */             for (y = 0; y < 8; y++) {                                        // 0.0
/*120 */                 if (y == 4) {                                                // 0.0
/*122 */                     P[0] = *s->stream_ptr++;                                 // 0.0
/*124 */                     P[1] = *s->stream_ptr++;                                 // 0.0
/*126 */                 }                                                            // 0.0
/*128 */                 flags = *s->stream_ptr++ | 0x100;                            // 0.0
/*132 */                 for (; flags != 1; flags >>= 1)                              // 0.0
/*134 */                     *s->pixel_ptr++ = P[flags & 1];                          // 0.0
/*136 */                 s->pixel_ptr += s->line_inc;                                 // 0.0
/*138 */             }                                                                // 0.0
/*140 */         }                                                                    // 0.0
/*142 */     }                                                                        // 0.0
/*146 */     /* report success */                                                     // 0.0
/*148 */     return 0;                                                                // 0.0
/*150 */ }                                                                            // 0.0
