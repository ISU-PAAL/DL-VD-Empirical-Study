// commit message FFmpeg@951e715ceb (target=1, prob=0.4013201, correct=False): avplay: Don't try to scale timestamps if the tb isn't set
/*0   */ static int video_thread(void *arg)                                                       // (19) 0.01953
/*2   */ {                                                                                        // (31) 0.001953
/*4   */     VideoState *is = arg;                                                                // (20) 0.01953
/*6   */     AVFrame *frame = avcodec_alloc_frame();                                              // (10) 0.03125
/*8   */     int64_t pts_int;                                                                     // (18) 0.02148
/*10  */     double pts;                                                                          // (27) 0.01172
/*12  */     int ret;                                                                             // (26) 0.01172
/*16  */ #if CONFIG_AVFILTER                                                                      // (24) 0.01367
/*18  */     AVFilterGraph *graph = avfilter_graph_alloc();                                       // (11) 0.03125
/*20  */     AVFilterContext *filt_out = NULL;                                                    // (14) 0.02734
/*22  */     int64_t pos;                                                                         // (21) 0.01758
/*24  */     int last_w = is->video_st->codec->width;                                             // (8) 0.03711
/*26  */     int last_h = is->video_st->codec->height;                                            // (7) 0.03711
/*30  */     if ((ret = configure_video_filters(graph, is, vfilters)) < 0)                        // (3) 0.04883
/*32  */         goto the_end;                                                                    // (17) 0.02344
/*34  */     filt_out = is->out_video_filter;                                                     // (12) 0.03125
/*36  */ #endif                                                                                   // (28) 0.003906
/*40  */     for (;;) {                                                                           // (23) 0.01563
/*42  */ #if !CONFIG_AVFILTER                                                                     // (22) 0.01758
/*44  */         AVPacket pkt;                                                                    // (15) 0.02539
/*46  */ #else                                                                                    // (30) 0.003906
/*48  */         AVFilterBufferRef *picref;                                                       // (13) 0.0293
/*50  */         AVRational tb;                                                                   // (16) 0.02539
/*52  */ #endif                                                                                   // (29) 0.003906
/*54  */         while (is->paused && !is->videoq.abort_request)                                  // (4) 0.04883
/*56  */             SDL_Delay(10);                                                               // (9) 0.03516
/*58  */ #if CONFIG_AVFILTER                                                                      // (25) 0.01367
/*60  */         if (   last_w != is->video_st->codec->width                                      // (5) 0.04883
/*62  */             || last_h != is->video_st->codec->height) {                                  // (2) 0.05469
/*64  */             av_dlog(NULL, "Changing size %dx%d -> %dx%d\n", last_w, last_h,              // (0) 0.08008
/*66  */                     is->video_st->codec->width, is->video_st->codec->height);            // (1) 0.08008
/*68  */             avfilter_graph_free(&graph);                                                 // (6) 0.03906
/*70  */             graph = avfilter_graph_alloc();                                              // 0.0
/*72  */             if ((ret = configure_video_filters(graph, is, vfilters)) < 0)                // 0.0
/*74  */                 goto the_end;                                                            // 0.0
/*76  */             filt_out = is->out_video_filter;                                             // 0.0
/*78  */             last_w = is->video_st->codec->width;                                         // 0.0
/*80  */             last_h = is->video_st->codec->height;                                        // 0.0
/*82  */         }                                                                                // 0.0
/*84  */         ret = get_filtered_video_frame(filt_out, frame, &picref, &tb);                   // 0.0
/*86  */         if (picref) {                                                                    // 0.0
/*88  */             pts_int = picref->pts;                                                       // 0.0
/*90  */             pos     = picref->pos;                                                       // 0.0
/*92  */             frame->opaque = picref;                                                      // 0.0
/*94  */         }                                                                                // 0.0
/*98  */         if (av_cmp_q(tb, is->video_st->time_base)) {                                     // 0.0
/*100 */             av_unused int64_t pts1 = pts_int;                                            // 0.0
/*102 */             pts_int = av_rescale_q(pts_int, tb, is->video_st->time_base);                // 0.0
/*104 */             av_dlog(NULL, "video_thread(): "                                             // 0.0
/*106 */                     "tb:%d/%d pts:%"PRId64" -> tb:%d/%d pts:%"PRId64"\n",                // 0.0
/*108 */                     tb.num, tb.den, pts1,                                                // 0.0
/*110 */                     is->video_st->time_base.num, is->video_st->time_base.den, pts_int);  // 0.0
/*112 */         }                                                                                // 0.0
/*114 */ #else                                                                                    // 0.0
/*116 */         ret = get_video_frame(is, frame, &pts_int, &pkt);                                // 0.0
/*118 */ #endif                                                                                   // 0.0
/*122 */         if (ret < 0)                                                                     // 0.0
/*124 */             goto the_end;                                                                // 0.0
/*128 */         if (!ret)                                                                        // 0.0
/*130 */             continue;                                                                    // 0.0
/*134 */         pts = pts_int * av_q2d(is->video_st->time_base);                                 // 0.0
/*138 */ #if CONFIG_AVFILTER                                                                      // 0.0
/*140 */         ret = output_picture2(is, frame, pts, pos);                                      // 0.0
/*142 */ #else                                                                                    // 0.0
/*144 */         ret = output_picture2(is, frame, pts,  pkt.pos);                                 // 0.0
/*146 */         av_free_packet(&pkt);                                                            // 0.0
/*148 */ #endif                                                                                   // 0.0
/*150 */         if (ret < 0)                                                                     // 0.0
/*152 */             goto the_end;                                                                // 0.0
/*156 */         if (step)                                                                        // 0.0
/*158 */             if (cur_stream)                                                              // 0.0
/*160 */                 stream_pause(cur_stream);                                                // 0.0
/*162 */     }                                                                                    // 0.0
/*164 */  the_end:                                                                                // 0.0
/*166 */ #if CONFIG_AVFILTER                                                                      // 0.0
/*168 */     avfilter_graph_free(&graph);                                                         // 0.0
/*170 */ #endif                                                                                   // 0.0
/*172 */     av_free(frame);                                                                      // 0.0
/*174 */     return 0;                                                                            // 0.0
/*176 */ }                                                                                        // 0.0
