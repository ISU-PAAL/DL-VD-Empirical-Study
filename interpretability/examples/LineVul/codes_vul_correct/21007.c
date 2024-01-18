// commit message FFmpeg@e30b068ef7 (target=1, prob=0.9990465, correct=True): wmapro: make sure there is room to store the current packet
/*0  */ static void save_bits(WMAProDecodeCtx *s, GetBitContext* gb, int len,           // (4) 0.05078
/*1  */                       int append)                                               // (10) 0.04687
/*2  */ {                                                                               // (23) 0.001953
/*3  */     int buflen;                                                                 // (19) 0.01562
/*4  */     /** when the frame data does not need to be concatenated, the input buffer  // (13) 0.03906
/*5  */         is resetted and additional bits from the previous frame are copyed      // (12) 0.03906
/*6  */         and skipped later so that a fast byte copy is possible */               // (15) 0.03711
/*7  */     if (!append) {                                                              // (20) 0.01562
/*8  */         s->frame_offset = get_bits_count(gb) & 7;                               // (8) 0.04687
/*9  */         s->num_saved_bits = s->frame_offset;                                    // (11) 0.04297
/*10 */         init_put_bits(&s->pb, s->frame_data, MAX_FRAMESIZE);                    // (2) 0.05664
/*11 */     buflen = (s->num_saved_bits + len + 8) >> 3;                                // (7) 0.04687
/*12 */     if (len <= 0 || buflen > MAX_FRAMESIZE) {                                   // (14) 0.03906
/*13 */         avpriv_request_sample(s->avctx, "Too small input buffer");              // (5) 0.04883
/*14 */     s->num_saved_bits += len;                                                   // (17) 0.02734
/*15 */     if (!append) {                                                              // (21) 0.01562
/*16 */         avpriv_copy_bits(&s->pb, gb->buffer + (get_bits_count(gb) >> 3),        // (1) 0.06836
/*17 */                      s->num_saved_bits);                                        // (3) 0.05664
/*18 */     } else {                                                                    // (22) 0.01172
/*19 */         int align = 8 - (get_bits_count(gb) & 7);                               // (9) 0.04687
/*20 */         align = FFMIN(align, len);                                              // (16) 0.03125
/*21 */         put_bits(&s->pb, align, get_bits(gb, align));                           // (6) 0.04883
/*22 */         len -= align;                                                           // (18) 0.02148
/*23 */         avpriv_copy_bits(&s->pb, gb->buffer + (get_bits_count(gb) >> 3), len);  // (0) 0.07227
/*24 */     skip_bits_long(gb, len);                                                    // 0.0
/*25 */     {                                                                           // 0.0
/*26 */         PutBitContext tmp = s->pb;                                              // 0.0
/*27 */         flush_put_bits(&tmp);                                                   // 0.0
/*28 */     init_get_bits(&s->gb, s->frame_data, s->num_saved_bits);                    // 0.0
/*29 */     skip_bits(&s->gb, s->frame_offset);                                         // 0.0
