// commit message FFmpeg@0ebb523f07 (target=1, prob=0.47244257, correct=False): asfdec: check ff_get_guid() return values during seeking
/*0   */ static void asf_build_simple_index(AVFormatContext *s, int stream_index)                   // (5) 0.04297
/*2   */ {                                                                                          // (25) 0.001954
/*4   */     ff_asf_guid g;                                                                         // (20) 0.02344
/*6   */     ASFContext *asf     = s->priv_data;                                                    // (11) 0.03906
/*8   */     int64_t current_pos = avio_tell(s->pb);                                                // (13) 0.03906
/*10  */     int i;                                                                                 // (22) 0.01172
/*14  */     avio_seek(s->pb, asf->data_object_offset + asf->data_object_size, SEEK_SET);           // (0) 0.06836
/*16  */     ff_get_guid(s->pb, &g);                                                                // (16) 0.0332
/*20  */     /* the data object can be followed by other top-level objects,                         // (15) 0.0332
/*22  */      * skip them until the simple index object is reached */                               // (17) 0.0293
/*24  */     while (ff_guidcmp(&g, &index_guid)) {                                                  // (12) 0.03906
/*26  */         int64_t gsize = avio_rl64(s->pb);                                                  // (4) 0.04687
/*28  */         if (gsize < 24 || s->pb->eof_reached) {                                            // (3) 0.04883
/*30  */             avio_seek(s->pb, current_pos, SEEK_SET);                                       // (1) 0.05664
/*32  */             return;                                                                        // (19) 0.02539
/*34  */         }                                                                                  // (21) 0.01562
/*36  */         avio_skip(s->pb, gsize - 24);                                                      // (8) 0.04102
/*38  */         ff_get_guid(s->pb, &g);                                                            // (10) 0.04102
/*40  */     }                                                                                      // (23) 0.007812
/*44  */     {                                                                                      // (24) 0.007812
/*46  */         int64_t itime, last_pos = -1;                                                      // (7) 0.04102
/*48  */         int pct, ict;                                                                      // (18) 0.02734
/*50  */         int64_t av_unused gsize = avio_rl64(s->pb);                                        // (2) 0.05469
/*52  */         ff_get_guid(s->pb, &g);                                                            // (9) 0.04102
/*54  */         itime = avio_rl64(s->pb);                                                          // (14) 0.03906
/*56  */         pct   = avio_rl32(s->pb);                                                          // (6) 0.04297
/*58  */         ict   = avio_rl32(s->pb);                                                          // 0.0
/*60  */         av_log(s, AV_LOG_DEBUG,                                                            // 0.0
/*62  */                "itime:0x%"PRIx64", pct:%d, ict:%d\n", itime, pct, ict);                    // 0.0
/*66  */         for (i = 0; i < ict; i++) {                                                        // 0.0
/*68  */             int pktnum        = avio_rl32(s->pb);                                          // 0.0
/*70  */             int pktct         = avio_rl16(s->pb);                                          // 0.0
/*72  */             int64_t pos       = s->data_offset + s->packet_size * (int64_t)pktnum;         // 0.0
/*74  */             int64_t index_pts = FFMAX(av_rescale(itime, i, 10000) - asf->hdr.preroll, 0);  // 0.0
/*78  */             if (pos != last_pos) {                                                         // 0.0
/*80  */                 av_log(s, AV_LOG_DEBUG, "pktnum:%d, pktct:%d  pts: %"PRId64"\n",           // 0.0
/*82  */                        pktnum, pktct, index_pts);                                          // 0.0
/*84  */                 av_add_index_entry(s->streams[stream_index], pos, index_pts,               // 0.0
/*86  */                                    s->packet_size, 0, AVINDEX_KEYFRAME);                   // 0.0
/*88  */                 last_pos = pos;                                                            // 0.0
/*90  */             }                                                                              // 0.0
/*92  */         }                                                                                  // 0.0
/*94  */         asf->index_read = ict > 0;                                                         // 0.0
/*96  */     }                                                                                      // 0.0
/*98  */     avio_seek(s->pb, current_pos, SEEK_SET);                                               // 0.0
/*100 */ }                                                                                          // 0.0
