// commit message FFmpeg@a0c624e299 (target=1, prob=0.45638457, correct=False): avcodec: v4l2_m2m: fix races around freeing data on close
/*0  */ int ff_v4l2_m2m_codec_reinit(V4L2m2mContext* s)                                    // (4) 0.05664
/*2  */ {                                                                                  // (27) 0.001953
/*4  */     int ret;                                                                       // (23) 0.01172
/*8  */     av_log(s->avctx, AV_LOG_DEBUG, "reinit context\n");                            // (7) 0.04883
/*12 */     /* 1. streamoff */                                                             // (19) 0.01758
/*14 */     ret = ff_v4l2_context_set_status(&s->capture, VIDIOC_STREAMOFF);               // (2) 0.06055
/*16 */     if (ret)                                                                       // (22) 0.01367
/*18 */         av_log(s->avctx, AV_LOG_ERROR, "capture VIDIOC_STREAMOFF\n");              // (0) 0.06836
/*22 */     /* 2. unmap the capture buffers (v4l2 and ffmpeg):                             // (10) 0.03906
/*24 */      *    we must wait for all references to be released before being allowed      // (11) 0.03906
/*26 */      *    to queue new buffers.                                                    // (14) 0.02539
/*28 */      */                                                                            // (24) 0.009766
/*30 */     av_log(s->avctx, AV_LOG_DEBUG, "waiting for user to release AVBufferRefs\n");  // (1) 0.0625
/*32 */     if (atomic_load(&s->refcount))                                                 // (13) 0.02734
/*34 */         while(sem_wait(&s->refsync) == -1 && errno == EINTR);                      // (5) 0.05664
/*38 */     ff_v4l2_context_release(&s->capture);                                          // (12) 0.03711
/*42 */     /* 3. get the new capture format */                                            // (15) 0.02344
/*44 */     ret = ff_v4l2_context_get_format(&s->capture);                                 // (9) 0.04492
/*46 */     if (ret) {                                                                     // (20) 0.01562
/*48 */         av_log(s->avctx, AV_LOG_ERROR, "query the new capture format\n");          // (3) 0.06055
/*50 */         return ret;                                                                // (18) 0.01953
/*52 */     }                                                                              // (26) 0.007812
/*56 */     /* 4. set the capture format */                                                // (16) 0.02148
/*58 */     ret = ff_v4l2_context_set_format(&s->capture);                                 // (8) 0.04492
/*60 */     if (ret) {                                                                     // (21) 0.01562
/*62 */         av_log(s->avctx, AV_LOG_ERROR, "setting capture format\n");                // (6) 0.05664
/*64 */         return ret;                                                                // (17) 0.01953
/*66 */     }                                                                              // (25) 0.007812
/*70 */     /* 5. complete reinit */                                                       // 0.0
/*72 */     sem_destroy(&s->refsync);                                                      // 0.0
/*74 */     sem_init(&s->refsync, 0, 0);                                                   // 0.0
/*76 */     s->draining = 0;                                                               // 0.0
/*78 */     s->reinit = 0;                                                                 // 0.0
/*82 */     return 0;                                                                      // 0.0
/*84 */ }                                                                                  // 0.0
