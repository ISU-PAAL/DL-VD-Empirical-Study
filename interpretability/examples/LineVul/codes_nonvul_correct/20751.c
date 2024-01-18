// commit message qemu@1ea879e558 (target=0, prob=0.4550082, correct=True): Make audio violate POSIX less
/*0  */ static void audio_run_capture (AudioState *s)                                     // (16) 0.02734
/*2  */ {                                                                                 // (21) 0.001953
/*4  */     CaptureVoiceOut *cap;                                                         // (20) 0.01758
/*8  */     for (cap = s->cap_head.lh_first; cap; cap = cap->entries.le_next) {           // (2) 0.0625
/*10 */         int live, rpos, captured;                                                 // (15) 0.0293
/*12 */         HWVoiceOut *hw = &cap->hw;                                                // (12) 0.03516
/*14 */         SWVoiceOut *sw;                                                           // (17) 0.02539
/*18 */         captured = live = audio_pcm_hw_get_live_out (hw);                         // (6) 0.05078
/*20 */         rpos = hw->rpos;                                                          // (14) 0.03125
/*22 */         while (live) {                                                            // (18) 0.02344
/*24 */             int left = hw->samples - rpos;                                        // (9) 0.04492
/*26 */             int to_capture = audio_MIN (live, left);                              // (7) 0.04883
/*28 */             st_sample_t *src;                                                     // (11) 0.03711
/*30 */             struct capture_callback *cb;                                          // (13) 0.03516
/*34 */             src = hw->mix_buf + rpos;                                             // (8) 0.04492
/*36 */             hw->clip (cap->buf, src, to_capture);                                 // (5) 0.05273
/*38 */             mixeng_clear (src, to_capture);                                       // (10) 0.04492
/*42 */             for (cb = cap->cb_head.lh_first; cb; cb = cb->entries.le_next) {      // (1) 0.08398
/*44 */                 cb->ops.capture (cb->opaque, cap->buf,                            // (3) 0.0625
/*46 */                                  to_capture << hw->info.shift);                   // (0) 0.08594
/*48 */             }                                                                     // (19) 0.02344
/*50 */             rpos = (rpos + to_capture) % hw->samples;                             // (4) 0.05859
/*52 */             live -= to_capture;                                                   // 0.0
/*54 */         }                                                                         // 0.0
/*56 */         hw->rpos = rpos;                                                          // 0.0
/*60 */         for (sw = hw->sw_head.lh_first; sw; sw = sw->entries.le_next) {           // 0.0
/*62 */             if (!sw->active && sw->empty) {                                       // 0.0
/*64 */                 continue;                                                         // 0.0
/*66 */             }                                                                     // 0.0
/*70 */             if (audio_bug (AUDIO_FUNC, captured > sw->total_hw_samples_mixed)) {  // 0.0
/*72 */                 dolog ("captured=%d sw->total_hw_samples_mixed=%d\n",             // 0.0
/*74 */                        captured, sw->total_hw_samples_mixed);                     // 0.0
/*76 */                 captured = sw->total_hw_samples_mixed;                            // 0.0
/*78 */             }                                                                     // 0.0
/*82 */             sw->total_hw_samples_mixed -= captured;                               // 0.0
/*84 */             sw->empty = sw->total_hw_samples_mixed == 0;                          // 0.0
/*86 */         }                                                                         // 0.0
/*88 */     }                                                                             // 0.0
/*90 */ }                                                                                 // 0.0
