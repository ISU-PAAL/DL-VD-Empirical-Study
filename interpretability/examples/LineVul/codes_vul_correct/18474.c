// commit message FFmpeg@18ff4d2020 (target=1, prob=0.5889095, correct=True): avconv: simplify memory allocation in copy_chapters
/*0  */ static int copy_chapters(InputFile *ifile, OutputFile *ofile, int copy_metadata)                   // (7) 0.04688
/*2  */ {                                                                                                  // (19) 0.001953
/*4  */     AVFormatContext *is = ifile->ctx;                                                              // (13) 0.02734
/*6  */     AVFormatContext *os = ofile->ctx;                                                              // (14) 0.02734
/*8  */     int i;                                                                                         // (18) 0.01172
/*12 */     for (i = 0; i < is->nb_chapters; i++) {                                                        // (10) 0.04102
/*14 */         AVChapter *in_ch = is->chapters[i], *out_ch;                                               // (5) 0.05078
/*16 */         int64_t ts_off   = av_rescale_q(ofile->start_time - ifile->ts_offset,                      // (3) 0.07422
/*18 */                                        AV_TIME_BASE_Q, in_ch->time_base);                          // (1) 0.1074
/*20 */         int64_t rt       = (ofile->recording_time == INT64_MAX) ? INT64_MAX :                      // (2) 0.07812
/*22 */                            av_rescale_q(ofile->recording_time, AV_TIME_BASE_Q, in_ch->time_base);  // (0) 0.1133
/*28 */         if (in_ch->end < ts_off)                                                                   // (12) 0.03711
/*30 */             continue;                                                                              // (17) 0.02539
/*32 */         if (rt != INT64_MAX && in_ch->start > rt + ts_off)                                         // (4) 0.05664
/*34 */             break;                                                                                 // (16) 0.02539
/*38 */         out_ch = av_mallocz(sizeof(AVChapter));                                                    // (8) 0.04492
/*40 */         if (!out_ch)                                                                               // (15) 0.02539
/*42 */             return AVERROR(ENOMEM);                                                                // (11) 0.03906
/*46 */         out_ch->id        = in_ch->id;                                                             // (6) 0.05078
/*48 */         out_ch->time_base = in_ch->time_base;                                                      // (9) 0.04492
/*50 */         out_ch->start     = FFMAX(0,  in_ch->start - ts_off);                                      // 0.0
/*52 */         out_ch->end       = FFMIN(rt, in_ch->end   - ts_off);                                      // 0.0
/*56 */         if (copy_metadata)                                                                         // 0.0
/*58 */             av_dict_copy(&out_ch->metadata, in_ch->metadata, 0);                                   // 0.0
/*62 */         os->nb_chapters++;                                                                         // 0.0
/*64 */         os->chapters = av_realloc(os->chapters, sizeof(AVChapter) * os->nb_chapters);              // 0.0
/*66 */         if (!os->chapters)                                                                         // 0.0
/*68 */             return AVERROR(ENOMEM);                                                                // 0.0
/*70 */         os->chapters[os->nb_chapters - 1] = out_ch;                                                // 0.0
/*72 */     }                                                                                              // 0.0
/*74 */     return 0;                                                                                      // 0.0
/*76 */ }                                                                                                  // 0.0
