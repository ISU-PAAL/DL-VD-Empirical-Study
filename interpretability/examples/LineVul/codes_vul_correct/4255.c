// commit message FFmpeg@ec07efa700 (target=1, prob=0.65370315, correct=True): avformat/webmdashenc: Validate the 'streams' adaptation sets parameter
/*0  */ static int parse_adaptation_sets(AVFormatContext *s)                                         // (16) 0.0293
/*2  */ {                                                                                            // (24) 0.001956
/*4  */     WebMDashMuxContext *w = s->priv_data;                                                    // (11) 0.03516
/*6  */     char *p = w->adaptation_sets;                                                            // (17) 0.02734
/*8  */     char *q;                                                                                 // (22) 0.01367
/*10 */     enum { new_set, parsed_id, parsing_streams } state;                                      // (9) 0.03907
/*12 */     if (!w->adaptation_sets) {                                                               // (19) 0.02539
/*14 */         av_log(s, AV_LOG_ERROR, "The 'adaptation_sets' option must be set.\n");              // (1) 0.06836
/*16 */         return AVERROR(EINVAL);                                                              // (15) 0.03125
/*18 */     }                                                                                        // (23) 0.007812
/*20 */     // syntax id=0,streams=0,1,2 id=1,streams=3,4 and so on                                  // (2) 0.05859
/*22 */     state = new_set;                                                                         // (21) 0.01758
/*24 */     while (p < w->adaptation_sets + strlen(w->adaptation_sets)) {                            // (7) 0.04883
/*26 */         if (*p == ' ')                                                                       // (18) 0.02734
/*28 */             continue;                                                                        // (20) 0.02539
/*30 */         else if (state == new_set && !strncmp(p, "id=", 3)) {                                // (3) 0.05859
/*32 */             void *mem = av_realloc(w->as, sizeof(*w->as) * (w->nb_as + 1));                  // (0) 0.07812
/*34 */             if (mem == NULL)                                                                 // (14) 0.0332
/*36 */                 return AVERROR(ENOMEM);                                                      // (8) 0.04687
/*38 */             w->as = mem;                                                                     // (13) 0.0332
/*40 */             ++w->nb_as;                                                                      // (12) 0.03516
/*42 */             w->as[w->nb_as - 1].nb_streams = 0;                                              // (4) 0.05859
/*44 */             w->as[w->nb_as - 1].streams = NULL;                                              // (5) 0.05469
/*46 */             p += 3; // consume "id="                                                         // (10) 0.03906
/*48 */             q = w->as[w->nb_as - 1].id;                                                      // (6) 0.05273
/*50 */             while (*p != ',') *q++ = *p++;                                                   // 0.0
/*52 */             *q = 0;                                                                          // 0.0
/*54 */             p++;                                                                             // 0.0
/*56 */             state = parsed_id;                                                               // 0.0
/*58 */         } else if (state == parsed_id && !strncmp(p, "streams=", 8)) {                       // 0.0
/*60 */             p += 8; // consume "streams="                                                    // 0.0
/*62 */             state = parsing_streams;                                                         // 0.0
/*64 */         } else if (state == parsing_streams) {                                               // 0.0
/*66 */             struct AdaptationSet *as = &w->as[w->nb_as - 1];                                 // 0.0
/*68 */             q = p;                                                                           // 0.0
/*70 */             while (*q != '\0' && *q != ',' && *q != ' ') q++;                                // 0.0
/*72 */             as->streams = av_realloc(as->streams, sizeof(*as->streams) * ++as->nb_streams);  // 0.0
/*74 */             if (as->streams == NULL)                                                         // 0.0
/*76 */                 return AVERROR(ENOMEM);                                                      // 0.0
/*78 */             as->streams[as->nb_streams - 1] = to_integer(p, q - p + 1);                      // 0.0
/*80 */             if (as->streams[as->nb_streams - 1] < 0) return -1;                              // 0.0
/*82 */             if (*q == '\0') break;                                                           // 0.0
/*84 */             if (*q == ' ') state = new_set;                                                  // 0.0
/*86 */             p = ++q;                                                                         // 0.0
/*88 */         } else {                                                                             // 0.0
/*90 */             return -1;                                                                       // 0.0
/*92 */         }                                                                                    // 0.0
/*94 */     }                                                                                        // 0.0
/*96 */     return 0;                                                                                // 0.0
/*98 */ }                                                                                            // 0.0
