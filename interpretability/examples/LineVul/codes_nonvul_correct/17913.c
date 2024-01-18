// commit message FFmpeg@ac726a4f0c (target=0, prob=0.09155396, correct=True): lavfi/movie: flush decoder frames on EOF
/*0  */ static int movie_request_frame(AVFilterLink *outlink)    // (6) 0.06466
/*2  */ {                                                        // (15) 0.00431
/*4  */     AVFilterBufferRef *outpicref;                        // (8) 0.05172
/*6  */     MovieContext *movie = outlink->src->priv;            // (5) 0.06466
/*8  */     int ret;                                             // (13) 0.02586
/*12 */     if (movie->is_done)                                  // (10) 0.04741
/*14 */         return AVERROR_EOF;                              // (7) 0.06466
/*16 */     if ((ret = movie_get_frame(outlink)) < 0)            // (2) 0.0819
/*18 */         return ret;                                      // (11) 0.0431
/*22 */     outpicref = avfilter_ref_buffer(movie->picref, ~0);  // (0) 0.09483
/*24 */     ff_start_frame(outlink, outpicref);                  // (3) 0.06897
/*26 */     ff_draw_slice(outlink, 0, outlink->h, 1);            // (1) 0.09052
/*28 */     ff_end_frame(outlink);                               // (9) 0.05172
/*30 */     avfilter_unref_buffer(movie->picref);                // (4) 0.06897
/*32 */     movie->picref = NULL;                                // (12) 0.0431
/*36 */     return 0;                                            // (14) 0.02586
/*38 */ }                                                        // (16) 0.00431
