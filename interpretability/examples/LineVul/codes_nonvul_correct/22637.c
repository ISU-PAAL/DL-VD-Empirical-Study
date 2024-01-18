// commit message FFmpeg@36583d23bd (target=0, prob=0.4338905, correct=True): audio_frame_que: simplify
/*0   */ void ff_af_queue_remove(AudioFrameQueue *afq, int nb_samples, int64_t *pts,      // (3) 0.06055
/*2   */                         int *duration)                                           // (5) 0.05273
/*4   */ {                                                                                // (27) 0.001953
/*6   */     int64_t out_pts = AV_NOPTS_VALUE;                                            // (11) 0.03906
/*8   */     int removed_samples = 0;                                                     // (18) 0.02148
/*12  */ #ifdef DEBUG                                                                     // (22) 0.007813
/*14  */     ff_af_queue_log_state(afq);                                                  // (15) 0.03125
/*16  */ #endif                                                                           // (26) 0.003906
/*20  */     /* get output pts from the next frame or generated pts */                    // (16) 0.0293
/*22  */     if (afq->frame_queue) {                                                      // (17) 0.02539
/*24  */         if (afq->frame_queue->pts != AV_NOPTS_VALUE)                             // (4) 0.05273
/*26  */             out_pts = afq->frame_queue->pts - afq->remaining_delay;              // (1) 0.06641
/*28  */     } else {                                                                     // (21) 0.01172
/*30  */         if (afq->next_pts != AV_NOPTS_VALUE)                                     // (6) 0.04883
/*32  */             out_pts = afq->next_pts - afq->remaining_delay;                      // (2) 0.0625
/*34  */     }                                                                            // (23) 0.007812
/*36  */     if (pts) {                                                                   // (19) 0.01758
/*38  */         if (out_pts != AV_NOPTS_VALUE)                                           // (9) 0.04297
/*40  */             *pts = ff_samples_to_time_base(afq->avctx, out_pts);                 // (0) 0.07227
/*42  */         else                                                                     // (20) 0.01562
/*44  */             *pts = AV_NOPTS_VALUE;                                               // (7) 0.04492
/*46  */     }                                                                            // (24) 0.007812
/*50  */     /* if the delay is larger than the packet duration, we use up delay samples  // (13) 0.03711
/*52  */        for the output packet and leave all frames in the queue */                // (14) 0.03516
/*54  */     if (afq->remaining_delay >= nb_samples) {                                    // (12) 0.03906
/*56  */         removed_samples      += nb_samples;                                      // (8) 0.04492
/*58  */         afq->remaining_delay -= nb_samples;                                      // (10) 0.04102
/*60  */     }                                                                            // (25) 0.007812
/*62  */     /* remove frames from the queue until we have enough to cover the            // 0.0
/*64  */        requested number of samples or until the queue is empty */                // 0.0
/*66  */     while (removed_samples < nb_samples && afq->frame_queue) {                   // 0.0
/*68  */         removed_samples += afq->frame_queue->duration;                           // 0.0
/*70  */         delete_next_frame(afq);                                                  // 0.0
/*72  */     }                                                                            // 0.0
/*74  */     afq->remaining_samples -= removed_samples;                                   // 0.0
/*78  */     /* if there are no frames left and we have room for more samples, use        // 0.0
/*80  */        any remaining delay samples */                                            // 0.0
/*82  */     if (removed_samples < nb_samples && afq->remaining_samples > 0) {            // 0.0
/*84  */         int add_samples = FFMIN(afq->remaining_samples,                          // 0.0
/*86  */                                 nb_samples - removed_samples);                   // 0.0
/*88  */         removed_samples        += add_samples;                                   // 0.0
/*90  */         afq->remaining_samples -= add_samples;                                   // 0.0
/*92  */     }                                                                            // 0.0
/*94  */     if (removed_samples > nb_samples)                                            // 0.0
/*96  */         av_log(afq->avctx, AV_LOG_WARNING, "frame_size is too large\n");         // 0.0
/*98  */     if (duration)                                                                // 0.0
/*100 */         *duration = ff_samples_to_time_base(afq->avctx, removed_samples);        // 0.0
/*102 */ }                                                                                // 0.0
