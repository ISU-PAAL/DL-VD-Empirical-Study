// commit message FFmpeg@69e7336b8e (target=0, prob=0.10301287, correct=True): avstring: Expose the simple name match function
/*0  */ AVInputFormat *av_find_input_format(const char *short_name)  // (1) 0.1827
/*2  */ {                                                            // (6) 0.009615
/*4  */     AVInputFormat *fmt = NULL;                               // (4) 0.1154
/*6  */     while ((fmt = av_iformat_next(fmt)))                     // (2) 0.1731
/*8  */         if (match_format(short_name, fmt->name))             // (0) 0.2019
/*10 */             return fmt;                                      // (3) 0.1346
/*12 */     return NULL;                                             // (5) 0.05769
/*14 */ }                                                            // (7) 0.009615
