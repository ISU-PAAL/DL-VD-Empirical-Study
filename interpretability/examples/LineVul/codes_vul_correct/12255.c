// commit message FFmpeg@fa74cdc60d (target=1, prob=0.99902546, correct=True): parser: add av_assert1 to make sure the codec matches
/*0  */ int av_parser_parse2(AVCodecParserContext *s, AVCodecContext *avctx,                                                   // (9) 0.04699
/*1  */                      uint8_t **poutbuf, int *poutbuf_size,                                                             // (2) 0.07225
/*2  */                      const uint8_t *buf, int buf_size,                                                                 // (5) 0.06444
/*3  */                      int64_t pts, int64_t dts, int64_t pos)                                                            // (1) 0.07621
/*4  */ {                                                                                                                      // (20) 0.001953
/*5  */     int index, i;                                                                                                      // (18) 0.01562
/*6  */     uint8_t dummy_buf[AV_INPUT_BUFFER_PADDING_SIZE];                                                                   // (7) 0.04882
/*7  */     if (!(s->flags & PARSER_FLAG_FETCHED_OFFSET)) {                                                                    // (8) 0.04882
/*8  */         s->next_frame_offset =                                                                                         // (14) 0.02929
/*9  */         s->cur_offset        = pos;                                                                                    // (12) 0.04296
/*10 */         s->flags            |= PARSER_FLAG_FETCHED_OFFSET;                                                             // (3) 0.07225
/*11 */     }                                                                                                                  // (19) 0.007811
/*12 */     if (buf_size == 0) {                                                                                               // (17) 0.02343
/*13 */         /* padding is always necessary even if EOF, so we add it here */                                               // (11) 0.04491
/*14 */         memset(dummy_buf, 0, sizeof(dummy_buf));                                                                       // (10) 0.04687
/*15 */         buf = dummy_buf;                                                                                               // (16) 0.02539
/*16 */     } else if (s->cur_offset + buf_size != s->cur_frame_end[s->cur_frame_start_index]) { /* skip remainder packets */  // (0) 0.08006
/*17 */         /* add a new packet descriptor */                                                                              // (15) 0.02734
/*18 */         i = (s->cur_frame_start_index + 1) & (AV_PARSER_PTS_NB - 1);                                                   // (4) 0.0703
/*19 */         s->cur_frame_start_index = i;                                                                                  // (13) 0.0371
/*20 */         s->cur_frame_offset[i]   = s->cur_offset;                                                                      // (6) 0.05077
/*21 */         s->cur_frame_end[i]      = s->cur_offset + buf_size;                                                           // 0.0
/*22 */         s->cur_frame_pts[i]      = pts;                                                                                // 0.0
/*23 */         s->cur_frame_dts[i]      = dts;                                                                                // 0.0
/*24 */         s->cur_frame_pos[i]      = pos;                                                                                // 0.0
/*25 */     }                                                                                                                  // 0.0
/*26 */     if (s->fetch_timestamp) {                                                                                          // 0.0
/*27 */         s->fetch_timestamp = 0;                                                                                        // 0.0
/*28 */         s->last_pts        = s->pts;                                                                                   // 0.0
/*29 */         s->last_dts        = s->dts;                                                                                   // 0.0
/*30 */         s->last_pos        = s->pos;                                                                                   // 0.0
/*31 */         ff_fetch_timestamp(s, 0, 0, 0);                                                                                // 0.0
/*32 */     }                                                                                                                  // 0.0
/*33 */     /* WARNING: the returned index can be negative */                                                                  // 0.0
/*34 */     index = s->parser->parser_parse(s, avctx, (const uint8_t **) poutbuf,                                              // 0.0
/*35 */                                     poutbuf_size, buf, buf_size);                                                      // 0.0
/*36 */     av_assert0(index > -0x20000000); // The API does not allow returning AVERROR codes                                 // 0.0
/*37 */     /* update the file pointer */                                                                                      // 0.0
/*38 */     if (*poutbuf_size) {                                                                                               // 0.0
/*39 */         /* fill the data for the current frame */                                                                      // 0.0
/*40 */         s->frame_offset = s->next_frame_offset;                                                                        // 0.0
/*41 */         /* offset of the next frame */                                                                                 // 0.0
/*42 */         s->next_frame_offset = s->cur_offset + index;                                                                  // 0.0
/*43 */         s->fetch_timestamp   = 1;                                                                                      // 0.0
/*44 */     }                                                                                                                  // 0.0
/*45 */     if (index < 0)                                                                                                     // 0.0
/*46 */         index = 0;                                                                                                     // 0.0
/*47 */     s->cur_offset += index;                                                                                            // 0.0
/*48 */     return index;                                                                                                      // 0.0
/*49 */ }                                                                                                                      // 0.0
