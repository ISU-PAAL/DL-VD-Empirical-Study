// commit message FFmpeg@42f9132218 (target=0, prob=0.49844447, correct=True): mxf: Do not use int to check the seek position
/*0  */ static int mxf_read_seek(AVFormatContext *s, int stream_index, int64_t sample_time, int flags)                  // (2) 0.06055
/*2  */ {                                                                                                               // (26) 0.001953
/*4  */     AVStream *st = s->streams[stream_index];                                                                    // (12) 0.0332
/*6  */     int64_t seconds;                                                                                            // (23) 0.01758
/*8  */     MXFContext* mxf = s->priv_data;                                                                             // (14) 0.03125
/*10 */     int64_t seekpos;                                                                                            // (20) 0.01953
/*12 */     int ret;                                                                                                    // (24) 0.01172
/*14 */     MXFIndexTable *t;                                                                                           // (21) 0.01953
/*18 */     if (mxf->nb_index_tables <= 0) {                                                                            // (11) 0.03516
/*20 */     if (!s->bit_rate)                                                                                           // (18) 0.02148
/*22 */         return AVERROR_INVALIDDATA;                                                                             // (13) 0.0332
/*24 */     if (sample_time < 0)                                                                                        // (19) 0.02148
/*26 */         sample_time = 0;                                                                                        // (17) 0.02539
/*28 */     seconds = av_rescale(sample_time, st->time_base.num, st->time_base.den);                                    // (3) 0.05859
/*32 */     if ((ret = avio_seek(s->pb, (s->bit_rate * seconds) >> 3, SEEK_SET)) < 0)                                   // (1) 0.07031
/*34 */         return ret;                                                                                             // (22) 0.01953
/*36 */     ff_update_cur_dts(s, st, sample_time);                                                                      // (9) 0.03906
/*38 */     mxf->current_edit_unit = sample_time;                                                                       // (15) 0.03125
/*40 */     } else {                                                                                                    // (25) 0.01172
/*42 */         t = &mxf->index_tables[0];                                                                              // (6) 0.03906
/*46 */         /* clamp above zero, else ff_index_search_timestamp() returns negative                                  // (4) 0.04687
/*48 */          * this also means we allow seeking before the start */                                                 // (10) 0.03711
/*50 */         sample_time = FFMAX(sample_time, 0);                                                                    // (8) 0.03906
/*54 */         if (t->fake_index) {                                                                                    // (16) 0.03125
/*56 */             /* behave as if we have a proper index */                                                           // (5) 0.04102
/*58 */             if ((sample_time = ff_index_search_timestamp(t->fake_index, t->nb_ptses, sample_time, flags)) < 0)  // (0) 0.09375
/*60 */                 return sample_time;                                                                             // (7) 0.03906
/*62 */         } else {                                                                                                // 0.0
/*64 */             /* no IndexEntryArray (one or more CBR segments)                                                    // 0.0
/*66 */              * make sure we don't seek past the end */                                                          // 0.0
/*68 */             sample_time = FFMIN(sample_time, st->duration - 1);                                                 // 0.0
/*70 */         }                                                                                                       // 0.0
/*74 */         if ((ret = mxf_edit_unit_absolute_offset(mxf, t, sample_time, &sample_time, &seekpos, 1)) << 0)         // 0.0
/*76 */             return ret;                                                                                         // 0.0
/*80 */         ff_update_cur_dts(s, st, sample_time);                                                                  // 0.0
/*82 */         mxf->current_edit_unit = sample_time;                                                                   // 0.0
/*84 */         avio_seek(s->pb, seekpos, SEEK_SET);                                                                    // 0.0
/*86 */     }                                                                                                           // 0.0
/*88 */     return 0;                                                                                                   // 0.0
/*90 */ }                                                                                                               // 0.0
