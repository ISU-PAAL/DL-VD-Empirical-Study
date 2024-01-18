// commit message FFmpeg@b84a7330af (target=1, prob=0.8848276, correct=True): avformat/pjsdec: dont increase pointer when its already at the end in read_ts()
/*0  */ static int64_t read_ts(char **line, int *duration)                // (2) 0.1197
/*2  */ {                                                                 // (8) 0.007042
/*4  */     int64_t start, end;                                           // (5) 0.07746
/*8  */     if (sscanf(*line, "%"SCNd64",%"SCNd64, &start, &end) == 2) {  // (0) 0.2394
/*10 */         *line += strcspn(*line, "\"") + 1;                        // (1) 0.162
/*12 */         *duration = end - start;                                  // (3) 0.09859
/*14 */         return start;                                             // (6) 0.07042
/*16 */     }                                                             // (7) 0.02817
/*18 */     return AV_NOPTS_VALUE;                                        // (4) 0.08451
/*20 */ }                                                                 // (9) 0.007042
