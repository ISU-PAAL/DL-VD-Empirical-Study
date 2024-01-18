// commit message FFmpeg@f907615f08 (target=1, prob=0.9990421, correct=True): parsers: initialize MpegEncContext.slice_context_count to 1
/*0  */ static av_cold int mpeg4video_parse_init(AVCodecParserContext *s)  // (0) 0.1964
/*2  */ {                                                                  // (7) 0.008929
/*4  */     ParseContext1 *pc = s->priv_data;                              // (2) 0.1429
/*8  */     pc->enc = av_mallocz(sizeof(MpegEncContext));                  // (1) 0.1875
/*10 */     if (!pc->enc)                                                  // (5) 0.08036
/*12 */         return -1;                                                 // (4) 0.09821
/*14 */     pc->first_picture = 1;                                         // (3) 0.09821
/*17 */     return 0;                                                      // (6) 0.05357
/*19 */ }                                                                  // (8) 0.008929
