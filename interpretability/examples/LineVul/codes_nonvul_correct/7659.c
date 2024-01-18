// commit message FFmpeg@a150bad406 (target=0, prob=0.38640982, correct=True): lavfi/avcodec: check avfilter_copy_frame_props() return code
/*0  */ AVFilterBufferRef *avfilter_get_video_buffer_ref_from_frame(const AVFrame *frame,       // (4) 0.08497
/*2  */                                                             int perms)                  // (0) 0.2059
/*4  */ {                                                                                       // (10) 0.003268
/*6  */     AVFilterBufferRef *picref =                                                         // (6) 0.03595
/*8  */         avfilter_get_video_buffer_ref_from_arrays(frame->data, frame->linesize, perms,  // (3) 0.1144
/*10 */                                                   frame->width, frame->height,          // (1) 0.1863
/*12 */                                                   frame->format);                       // (2) 0.1732
/*14 */     if (!picref)                                                                        // (8) 0.02614
/*16 */         return NULL;                                                                    // (7) 0.03268
/*18 */     avfilter_copy_frame_props(picref, frame);                                           // (5) 0.05882
/*20 */     return picref;                                                                      // (9) 0.02288
/*22 */ }                                                                                       // (11) 0.003268
