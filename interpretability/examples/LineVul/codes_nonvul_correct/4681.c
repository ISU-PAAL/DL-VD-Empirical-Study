// commit message FFmpeg@4b9ac0b5f0 (target=0, prob=0.49597842, correct=True): require a few valid and equal mp3 headers for resync
/*0   */ static int mpegaudio_parse(AVCodecParserContext *s1,                          // (11) 0.03321
/*2   */                            AVCodecContext *avctx,                             // (5) 0.0664
/*4   */                            uint8_t **poutbuf, int *poutbuf_size,              // (0) 0.08594
/*6   */                            const uint8_t *buf, int buf_size)                  // (1) 0.07617
/*8   */ {                                                                             // (21) 0.001955
/*10  */     MpegAudioParseContext *s = s1->priv_data;                                 // (10) 0.03711
/*12  */     int len, ret;                                                             // (20) 0.01563
/*14  */     uint32_t header;                                                          // (18) 0.01758
/*16  */     const uint8_t *buf_ptr;                                                   // (13) 0.02539
/*20  */     *poutbuf = NULL;                                                          // (17) 0.01953
/*22  */     *poutbuf_size = 0;                                                        // (16) 0.02344
/*24  */     buf_ptr = buf;                                                            // (19) 0.01758
/*26  */     while (buf_size > 0) {                                                    // (14) 0.02344
/*28  */ 	len = s->inbuf_ptr - s->inbuf;                                               // (12) 0.0293
/*30  */ 	if (s->frame_size == 0) {                                                    // (15) 0.02344
/*32  */             /* special case for next header for first frame in free           // (9) 0.04297
/*34  */                format case (XXX: find a simpler method) */                    // (8) 0.04883
/*36  */             if (s->free_format_next_header != 0) {                            // (7) 0.05078
/*38  */                 s->inbuf[0] = s->free_format_next_header >> 24;               // (2) 0.06836
/*40  */                 s->inbuf[1] = s->free_format_next_header >> 16;               // (3) 0.06836
/*42  */                 s->inbuf[2] = s->free_format_next_header >> 8;                // (4) 0.06836
/*44  */                 s->inbuf[3] = s->free_format_next_header;                     // (6) 0.06445
/*46  */                 s->inbuf_ptr = s->inbuf + 4;                                  // 0.0
/*48  */                 s->free_format_next_header = 0;                               // 0.0
/*50  */                 goto got_header;                                              // 0.0
/*52  */             }                                                                 // 0.0
/*54  */ 	    /* no header seen : find one. We need at least MPA_HEADER_SIZE           // 0.0
/*56  */                bytes to parse it */                                           // 0.0
/*58  */ 	    len = MPA_HEADER_SIZE - len;                                             // 0.0
/*60  */ 	    if (len > buf_size)                                                      // 0.0
/*62  */ 		len = buf_size;                                                             // 0.0
/*64  */ 	    if (len > 0) {                                                           // 0.0
/*66  */ 		memcpy(s->inbuf_ptr, buf_ptr, len);                                         // 0.0
/*68  */ 		buf_ptr += len;                                                             // 0.0
/*70  */ 		buf_size -= len;                                                            // 0.0
/*72  */ 		s->inbuf_ptr += len;                                                        // 0.0
/*74  */ 	    }                                                                        // 0.0
/*76  */ 	    if ((s->inbuf_ptr - s->inbuf) >= MPA_HEADER_SIZE) {                      // 0.0
/*78  */             got_header:                                                       // 0.0
/*80  */ 		header = (s->inbuf[0] << 24) | (s->inbuf[1] << 16) |                        // 0.0
/*82  */ 		    (s->inbuf[2] << 8) | s->inbuf[3];                                       // 0.0
/*86  */                 ret = mpa_decode_header(avctx, header);                       // 0.0
/*88  */                 if (ret < 0) {                                                // 0.0
/*90  */ 		    /* no sync found : move by one byte (inefficient, but simple!) */       // 0.0
/*92  */ 		    memmove(s->inbuf, s->inbuf + 1, s->inbuf_ptr - s->inbuf - 1);           // 0.0
/*94  */ 		    s->inbuf_ptr--;                                                         // 0.0
/*96  */                     dprintf("skip %x\n", header);                             // 0.0
/*98  */                     /* reset free format frame size to give a chance          // 0.0
/*100 */                        to get a new bitrate */                                // 0.0
/*102 */                     s->free_format_frame_size = 0;                            // 0.0
/*104 */ 		} else {                                                                    // 0.0
/*106 */                     s->frame_size = ret;                                      // 0.0
/*108 */ #if 0                                                                         // 0.0
/*110 */                     /* free format: prepare to compute frame size */          // 0.0
/*112 */ 		    if (decode_header(s, header) == 1) {                                    // 0.0
/*114 */ 			s->frame_size = -1;                                                        // 0.0
/*116 */                     }                                                         // 0.0
/*118 */ #endif                                                                        // 0.0
/*120 */ 		}                                                                           // 0.0
/*122 */ 	    }                                                                        // 0.0
/*124 */         } else                                                                // 0.0
/*126 */ #if 0                                                                         // 0.0
/*128 */         if (s->frame_size == -1) {                                            // 0.0
/*130 */             /* free format : find next sync to compute frame size */          // 0.0
/*132 */ 	    len = MPA_MAX_CODED_FRAME_SIZE - len;                                    // 0.0
/*134 */ 	    if (len > buf_size)                                                      // 0.0
/*136 */ 		len = buf_size;                                                             // 0.0
/*138 */             if (len == 0) {                                                   // 0.0
/*140 */ 		/* frame too long: resync */                                                // 0.0
/*142 */                 s->frame_size = 0;                                            // 0.0
/*144 */ 		memmove(s->inbuf, s->inbuf + 1, s->inbuf_ptr - s->inbuf - 1);               // 0.0
/*146 */ 		s->inbuf_ptr--;                                                             // 0.0
/*148 */             } else {                                                          // 0.0
/*150 */                 uint8_t *p, *pend;                                            // 0.0
/*152 */                 uint32_t header1;                                             // 0.0
/*154 */                 int padding;                                                  // 0.0
/*158 */                 memcpy(s->inbuf_ptr, buf_ptr, len);                           // 0.0
/*160 */                 /* check for header */                                        // 0.0
/*162 */                 p = s->inbuf_ptr - 3;                                         // 0.0
/*164 */                 pend = s->inbuf_ptr + len - 4;                                // 0.0
/*166 */                 while (p <= pend) {                                           // 0.0
/*168 */                     header = (p[0] << 24) | (p[1] << 16) |                    // 0.0
/*170 */                         (p[2] << 8) | p[3];                                   // 0.0
/*172 */                     header1 = (s->inbuf[0] << 24) | (s->inbuf[1] << 16) |     // 0.0
/*174 */                         (s->inbuf[2] << 8) | s->inbuf[3];                     // 0.0
/*176 */                     /* check with high probability that we have a             // 0.0
/*178 */                        valid header */                                        // 0.0
/*180 */                     if ((header & SAME_HEADER_MASK) ==                        // 0.0
/*182 */                         (header1 & SAME_HEADER_MASK)) {                       // 0.0
/*184 */                         /* header found: update pointers */                   // 0.0
/*186 */                         len = (p + 4) - s->inbuf_ptr;                         // 0.0
/*188 */                         buf_ptr += len;                                       // 0.0
/*190 */                         buf_size -= len;                                      // 0.0
/*192 */                         s->inbuf_ptr = p;                                     // 0.0
/*194 */                         /* compute frame size */                              // 0.0
/*196 */                         s->free_format_next_header = header;                  // 0.0
/*198 */                         s->free_format_frame_size = s->inbuf_ptr - s->inbuf;  // 0.0
/*200 */                         padding = (header1 >> 9) & 1;                         // 0.0
/*202 */                         if (s->layer == 1)                                    // 0.0
/*204 */                             s->free_format_frame_size -= padding * 4;         // 0.0
/*206 */                         else                                                  // 0.0
/*208 */                             s->free_format_frame_size -= padding;             // 0.0
/*210 */                         dprintf("free frame size=%d padding=%d\n",            // 0.0
/*212 */                                 s->free_format_frame_size, padding);          // 0.0
/*214 */                         decode_header(s, header1);                            // 0.0
/*216 */                         goto next_data;                                       // 0.0
/*218 */                     }                                                         // 0.0
/*220 */                     p++;                                                      // 0.0
/*222 */                 }                                                             // 0.0
/*224 */                 /* not found: simply increase pointers */                     // 0.0
/*226 */                 buf_ptr += len;                                               // 0.0
/*228 */                 s->inbuf_ptr += len;                                          // 0.0
/*230 */                 buf_size -= len;                                              // 0.0
/*232 */             }                                                                 // 0.0
/*234 */ 	} else                                                                       // 0.0
/*236 */ #endif                                                                        // 0.0
/*238 */         if (len < s->frame_size) {                                            // 0.0
/*240 */             if (s->frame_size > MPA_MAX_CODED_FRAME_SIZE)                     // 0.0
/*242 */                 s->frame_size = MPA_MAX_CODED_FRAME_SIZE;                     // 0.0
/*244 */ 	    len = s->frame_size - len;                                               // 0.0
/*246 */ 	    if (len > buf_size)                                                      // 0.0
/*248 */ 		len = buf_size;                                                             // 0.0
/*250 */ 	    memcpy(s->inbuf_ptr, buf_ptr, len);                                      // 0.0
/*252 */ 	    buf_ptr += len;                                                          // 0.0
/*254 */ 	    s->inbuf_ptr += len;                                                     // 0.0
/*256 */ 	    buf_size -= len;                                                         // 0.0
/*258 */ 	}                                                                            // 0.0
/*260 */         //    next_data:                                                      // 0.0
/*262 */         if (s->frame_size > 0 &&                                              // 0.0
/*264 */             (s->inbuf_ptr - s->inbuf) >= s->frame_size) {                     // 0.0
/*266 */             *poutbuf = s->inbuf;                                              // 0.0
/*268 */             *poutbuf_size = s->inbuf_ptr - s->inbuf;                          // 0.0
/*270 */ 	    s->inbuf_ptr = s->inbuf;                                                 // 0.0
/*272 */ 	    s->frame_size = 0;                                                       // 0.0
/*274 */ 	    break;                                                                   // 0.0
/*276 */ 	}                                                                            // 0.0
/*278 */     }                                                                         // 0.0
/*280 */     return buf_ptr - buf;                                                     // 0.0
/*282 */ }                                                                             // 0.0
