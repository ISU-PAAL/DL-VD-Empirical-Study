// commit message FFmpeg@ed9b2a5178 (target=1, prob=0.6978689, correct=True): mov: Rework the check for invalid indexes in stsc
/*0  */ static int mov_read_stsc(MOVContext *c, AVIOContext *pb, MOVAtom atom)                           // (3) 0.05083
/*2  */ {                                                                                                // (26) 0.001954
/*4  */     AVStream *st;                                                                                // (23) 0.01563
/*6  */     MOVStreamContext *sc;                                                                        // (21) 0.01758
/*8  */     unsigned int i, entries;                                                                     // (22) 0.01758
/*12 */     if (c->fc->nb_streams < 1)                                                                   // (13) 0.03125
/*14 */         return 0;                                                                                // (20) 0.01953
/*16 */     st = c->fc->streams[c->fc->nb_streams-1];                                                    // (8) 0.04492
/*18 */     sc = st->priv_data;                                                                          // (18) 0.02148
/*22 */     avio_r8(pb); /* version */                                                                   // (14) 0.02734
/*24 */     avio_rb24(pb); /* flags */                                                                   // (15) 0.02734
/*28 */     entries = avio_rb32(pb);                                                                     // (16) 0.02539
/*32 */     av_log(c->fc, AV_LOG_TRACE, "track[%i].stsc.entries = %i\n", c->fc->nb_streams-1, entries);  // (0) 0.09374
/*36 */     if (!entries)                                                                                // (24) 0.01562
/*38 */         return 0;                                                                                // (19) 0.01953
/*40 */     if (entries >= UINT_MAX / sizeof(*sc->stsc_data))                                            // (9) 0.04297
/*42 */         return AVERROR_INVALIDDATA;                                                              // (11) 0.0332
/*44 */     sc->stsc_data = av_malloc(entries * sizeof(*sc->stsc_data));                                 // (1) 0.05273
/*46 */     if (!sc->stsc_data)                                                                          // (17) 0.02344
/*48 */         return AVERROR(ENOMEM);                                                                  // (12) 0.03125
/*52 */     for (i = 0; i < entries && !pb->eof_reached; i++) {                                          // (7) 0.04883
/*54 */         sc->stsc_data[i].first = avio_rb32(pb);                                                  // (5) 0.05078
/*56 */         sc->stsc_data[i].count = avio_rb32(pb);                                                  // (4) 0.05078
/*58 */         sc->stsc_data[i].id = avio_rb32(pb);                                                     // (6) 0.05078
/*60 */         if (sc->stsc_data[i].id > sc->stsd_count)                                                // (2) 0.05273
/*62 */             return AVERROR_INVALIDDATA;                                                          // (10) 0.04101
/*64 */     }                                                                                            // (25) 0.007812
/*68 */     sc->stsc_count = i;                                                                          // 0.0
/*72 */     if (pb->eof_reached)                                                                         // 0.0
/*74 */         return AVERROR_EOF;                                                                      // 0.0
/*78 */     return 0;                                                                                    // 0.0
/*80 */ }                                                                                                // 0.0
