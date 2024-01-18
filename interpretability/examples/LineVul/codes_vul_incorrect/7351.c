// commit message FFmpeg@3b9a913db4 (target=1, prob=0.18198553, correct=False): simplify seek() failure check
/*0  */ offset_t url_fseek(ByteIOContext *s, offset_t offset, int whence)           // (4) 0.04297
/*2  */ {                                                                           // (30) 0.001953
/*4  */     offset_t offset1;                                                       // (23) 0.01758
/*6  */     offset_t pos= s->pos - (s->write_flag ? 0 : (s->buf_end - s->buffer));  // (1) 0.0625
/*10 */     if (whence != SEEK_CUR && whence != SEEK_SET)                           // (5) 0.04102
/*12 */         return -EINVAL;                                                     // (17) 0.02539
/*16 */     if (whence == SEEK_CUR) {                                               // (14) 0.0293
/*18 */         offset1 = pos + (s->buf_ptr - s->buffer);                           // (3) 0.04492
/*20 */         if (offset == 0)                                                    // (18) 0.02539
/*22 */             return offset1;                                                 // (15) 0.0293
/*24 */         offset += offset1;                                                  // (19) 0.02344
/*26 */     }                                                                       // (29) 0.007812
/*28 */     offset1 = offset - pos;                                                 // (21) 0.01953
/*30 */     if (!s->must_flush &&                                                   // (20) 0.02148
/*32 */         offset1 >= 0 && offset1 < (s->buf_end - s->buffer)) {               // (2) 0.05273
/*34 */         /* can do the seek inside the buffer */                             // (12) 0.03125
/*36 */         s->buf_ptr = s->buffer + offset1;                                   // (7) 0.03906
/*38 */     } else {                                                                // (28) 0.01172
/*40 */         if (!s->seek)                                                       // (16) 0.02539
/*42 */             return -EPIPE;                                                  // (9) 0.0332
/*46 */ #ifdef CONFIG_MUXERS                                                        // (25) 0.01563
/*48 */         if (s->write_flag) {                                                // (13) 0.03125
/*50 */             flush_buffer(s);                                                // (11) 0.0332
/*52 */             s->must_flush = 1;                                              // (8) 0.03711
/*54 */         } else                                                              // (24) 0.01758
/*56 */ #endif //CONFIG_MUXERS                                                      // (22) 0.01758
/*58 */         {                                                                   // (27) 0.01562
/*60 */             s->buf_end = s->buffer;                                         // (6) 0.04102
/*62 */         }                                                                   // (26) 0.01562
/*64 */         s->buf_ptr = s->buffer;                                             // (10) 0.0332
/*66 */         if (s->seek(s->opaque, offset, SEEK_SET) == (offset_t)-EPIPE)       // (0) 0.06836
/*68 */             return -EPIPE;                                                  // 0.0
/*70 */         s->pos = offset;                                                    // 0.0
/*72 */     }                                                                       // 0.0
/*74 */     s->eof_reached = 0;                                                     // 0.0
/*76 */     return offset;                                                          // 0.0
/*78 */ }                                                                           // 0.0
