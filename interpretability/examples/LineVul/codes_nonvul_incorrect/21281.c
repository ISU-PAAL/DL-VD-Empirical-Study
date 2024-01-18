// commit message FFmpeg@2ac00d2d1d (target=0, prob=0.69537395, correct=False): mov: Validate the ID number
/*0  */ static int mov_read_stsc(MOVContext *c, AVIOContext *pb, MOVAtom atom)                           // (3) 0.05082
/*2  */ {                                                                                                // (24) 0.001953
/*4  */     AVStream *st;                                                                                // (22) 0.01563
/*6  */     MOVStreamContext *sc;                                                                        // (20) 0.01758
/*8  */     unsigned int i, entries;                                                                     // (21) 0.01758
/*12 */     if (c->fc->nb_streams < 1)                                                                   // (12) 0.03125
/*14 */         return 0;                                                                                // (19) 0.01953
/*16 */     st = c->fc->streams[c->fc->nb_streams-1];                                                    // (8) 0.04492
/*18 */     sc = st->priv_data;                                                                          // (17) 0.02148
/*22 */     avio_r8(pb); /* version */                                                                   // (13) 0.02734
/*24 */     avio_rb24(pb); /* flags */                                                                   // (14) 0.02734
/*28 */     entries = avio_rb32(pb);                                                                     // (15) 0.02539
/*32 */     av_log(c->fc, AV_LOG_TRACE, "track[%i].stsc.entries = %i\n", c->fc->nb_streams-1, entries);  // (0) 0.09375
/*36 */     if (!entries)                                                                                // (23) 0.01562
/*38 */         return 0;                                                                                // (18) 0.01953
/*40 */     if (entries >= UINT_MAX / sizeof(*sc->stsc_data))                                            // (9) 0.04297
/*42 */         return AVERROR_INVALIDDATA;                                                              // (10) 0.0332
/*44 */     sc->stsc_data = av_malloc(entries * sizeof(*sc->stsc_data));                                 // (2) 0.05273
/*46 */     if (!sc->stsc_data)                                                                          // (16) 0.02344
/*48 */         return AVERROR(ENOMEM);                                                                  // (11) 0.03125
/*52 */     for (i = 0; i < entries && !pb->eof_reached; i++) {                                          // (7) 0.04883
/*54 */         sc->stsc_data[i].first = avio_rb32(pb);                                                  // (5) 0.05078
/*56 */         sc->stsc_data[i].count = avio_rb32(pb);                                                  // (4) 0.05078
/*58 */         sc->stsc_data[i].id = avio_rb32(pb);                                                     // (6) 0.05078
/*60 */         if (sc->stsc_data[i].id < 0 || sc->stsc_data[i].id > sc->stsd_count) {                   // (1) 0.08007
/*62 */             sc->stsc_data[i].id = 0;                                                             // 0.0
/*64 */             if (c->fc->error_recognition & AV_EF_EXPLODE) {                                      // 0.0
/*66 */                 av_log(c->fc, AV_LOG_ERROR, "Invalid stsc index.\n");                            // 0.0
/*68 */                 return AVERROR_INVALIDDATA;                                                      // 0.0
/*70 */             }                                                                                    // 0.0
/*72 */         }                                                                                        // 0.0
/*74 */     }                                                                                            // 0.0
/*78 */     sc->stsc_count = i;                                                                          // 0.0
/*82 */     if (pb->eof_reached)                                                                         // 0.0
/*84 */         return AVERROR_EOF;                                                                      // 0.0
/*88 */     return 0;                                                                                    // 0.0
/*90 */ }                                                                                                // 0.0
