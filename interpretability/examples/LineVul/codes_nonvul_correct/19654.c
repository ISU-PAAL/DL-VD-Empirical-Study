// commit message FFmpeg@8f4020d8a4 (target=0, prob=0.3172681, correct=True): svq1dec: check return value of get_bits1() in more common way
/*0   */ static int svq1_decode_frame_header(GetBitContext *bitbuf, MpegEncContext *s)     // (6) 0.05274
/*2   */ {                                                                                 // (20) 0.001958
/*4   */     int frame_size_code;                                                          // (17) 0.01953
/*8   */     skip_bits(bitbuf, 8); /* temporal_reference */                                // (13) 0.0332
/*12  */     /* frame type */                                                              // (19) 0.01367
/*14  */     s->pict_type = get_bits(bitbuf, 2) + 1;                                       // (11) 0.04101
/*16  */     if (s->pict_type == 4)                                                        // (15) 0.02539
/*18  */         return AVERROR_INVALIDDATA;                                               // (14) 0.0332
/*22  */     if (s->pict_type == AV_PICTURE_TYPE_I) {                                      // (10) 0.04297
/*24  */         /* unknown fields */                                                      // (16) 0.02148
/*26  */         if (s->f_code == 0x50 || s->f_code == 0x60) {                             // (5) 0.05859
/*28  */             int csum = get_bits(bitbuf, 16);                                      // (9) 0.04687
/*32  */             csum = ff_svq1_packet_checksum(bitbuf->buffer,                        // (4) 0.06055
/*34  */                                            bitbuf->size_in_bits >> 3,             // (0) 0.1035
/*36  */                                            csum);                                 // (1) 0.08789
/*40  */             av_dlog(s->avctx, "%s checksum (%02x) for packet data\n",             // (3) 0.06836
/*42  */                     (csum == 0) ? "correct" : "incorrect", csum);                 // (2) 0.07226
/*44  */         }                                                                         // (18) 0.01562
/*48  */         if ((s->f_code ^ 0x10) >= 0x50) {                                         // (7) 0.04883
/*50  */             uint8_t msg[256];                                                     // (12) 0.03711
/*54  */             svq1_parse_string(bitbuf, msg);                                       // (8) 0.04687
/*58  */             av_log(s->avctx, AV_LOG_ERROR,                                        // 0.0
/*60  */                    "embedded message: \"%s\"\n", (char *)msg);                    // 0.0
/*62  */         }                                                                         // 0.0
/*66  */         skip_bits(bitbuf, 2);                                                     // 0.0
/*68  */         skip_bits(bitbuf, 2);                                                     // 0.0
/*70  */         skip_bits1(bitbuf);                                                       // 0.0
/*74  */         /* load frame size */                                                     // 0.0
/*76  */         frame_size_code = get_bits(bitbuf, 3);                                    // 0.0
/*80  */         if (frame_size_code == 7) {                                               // 0.0
/*82  */             /* load width, height (12 bits each) */                               // 0.0
/*84  */             s->width  = get_bits(bitbuf, 12);                                     // 0.0
/*86  */             s->height = get_bits(bitbuf, 12);                                     // 0.0
/*90  */             if (!s->width || !s->height)                                          // 0.0
/*92  */                 return AVERROR_INVALIDDATA;                                       // 0.0
/*94  */         } else {                                                                  // 0.0
/*96  */             /* get width, height from table */                                    // 0.0
/*98  */             s->width  = ff_svq1_frame_size_table[frame_size_code].width;          // 0.0
/*100 */             s->height = ff_svq1_frame_size_table[frame_size_code].height;         // 0.0
/*102 */         }                                                                         // 0.0
/*104 */     }                                                                             // 0.0
/*108 */     /* unknown fields */                                                          // 0.0
/*110 */     if (get_bits1(bitbuf) == 1) {                                                 // 0.0
/*112 */         skip_bits1(bitbuf);    /* use packet checksum if (1) */                   // 0.0
/*114 */         skip_bits1(bitbuf);    /* component checksums after image data if (1) */  // 0.0
/*118 */         if (get_bits(bitbuf, 2) != 0)                                             // 0.0
/*120 */             return AVERROR_INVALIDDATA;                                           // 0.0
/*122 */     }                                                                             // 0.0
/*126 */     if (get_bits1(bitbuf) == 1) {                                                 // 0.0
/*128 */         skip_bits1(bitbuf);                                                       // 0.0
/*130 */         skip_bits(bitbuf, 4);                                                     // 0.0
/*132 */         skip_bits1(bitbuf);                                                       // 0.0
/*134 */         skip_bits(bitbuf, 2);                                                     // 0.0
/*138 */         while (get_bits1(bitbuf) == 1)                                            // 0.0
/*140 */             skip_bits(bitbuf, 8);                                                 // 0.0
/*142 */     }                                                                             // 0.0
/*146 */     return 0;                                                                     // 0.0
/*148 */ }                                                                                 // 0.0
