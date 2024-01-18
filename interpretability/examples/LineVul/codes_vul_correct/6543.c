// commit message FFmpeg@fdbc544d29 (target=1, prob=0.67775375, correct=True): asfdec: prevent the memory leak while reading metadata
/*0  */ static int asf_read_ext_content(AVFormatContext *s, const GUIDParseTable *g)               // (2) 0.05567
/*2  */ {                                                                                          // (24) 0.002141
/*4  */     ASFContext *asf  = s->priv_data;                                                       // (14) 0.0364
/*6  */     AVIOContext *pb  = s->pb;                                                              // (17) 0.02998
/*8  */     uint64_t size    = avio_rl64(pb);                                                      // (6) 0.04283
/*10 */     uint16_t nb_desc = avio_rl16(pb);                                                      // (7) 0.04283
/*12 */     int i, ret;                                                                            // (21) 0.01713
/*16 */     for (i = 0; i < nb_desc; i++) {                                                        // (10) 0.04069
/*18 */         uint16_t name_len, type, val_len;                                                  // (4) 0.04497
/*20 */         uint8_t *name = NULL;                                                              // (15) 0.03426
/*24 */         name_len = avio_rl16(pb);                                                          // (11) 0.04069
/*26 */         if (!name_len)                                                                     // (19) 0.02784
/*28 */             return AVERROR_INVALIDDATA;                                                    // (5) 0.04497
/*30 */         name = av_malloc(name_len);                                                        // (13) 0.03854
/*32 */         if (!name)                                                                         // (20) 0.02355
/*34 */             return AVERROR(ENOMEM);                                                        // (8) 0.04283
/*36 */         avio_get_str16le(pb, name_len, name,                                               // (3) 0.05139
/*38 */                          name_len);                                                        // (1) 0.05996
/*40 */         type    = avio_rl16(pb);                                                           // (9) 0.04283
/*42 */         val_len = avio_rl16(pb);                                                           // (12) 0.04069
/*46 */         if ((ret = process_metadata(s, name, name_len, val_len, type, &s->metadata)) < 0)  // (0) 0.07923
/*48 */             return ret;                                                                    // (18) 0.02998
/*50 */     }                                                                                      // (23) 0.008565
/*54 */     align_position(pb, asf->offset, size);                                                 // (16) 0.03426
/*56 */     return 0;                                                                              // (22) 0.01285
/*58 */ }                                                                                          // (25) 0.002141
