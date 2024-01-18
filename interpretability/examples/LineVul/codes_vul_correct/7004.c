// commit message qemu@ea9ebc2ce6 (target=1, prob=0.77891546, correct=True): Do not use pa_simple PulseAudio API
/*0  */ static void qpa_fini_out (HWVoiceOut *hw)              // (4) 0.07359
/*2  */ {                                                      // (14) 0.004329
/*4  */     void *ret;                                         // (12) 0.0303
/*6  */     PAVoiceOut *pa = (PAVoiceOut *) hw;                // (5) 0.07359
/*10 */     audio_pt_lock (&pa->pt, AUDIO_FUNC);               // (3) 0.08225
/*12 */     pa->done = 1;                                      // (11) 0.03896
/*14 */     audio_pt_unlock_and_signal (&pa->pt, AUDIO_FUNC);  // (0) 0.1082
/*16 */     audio_pt_join (&pa->pt, &ret, AUDIO_FUNC);         // (1) 0.09524
/*20 */     if (pa->s) {                                       // (10) 0.04329
/*22 */         pa_simple_free (pa->s);                        // (6) 0.07359
/*24 */         pa->s = NULL;                                  // (8) 0.05628
/*26 */     }                                                  // (13) 0.01732
/*30 */     audio_pt_fini (&pa->pt, AUDIO_FUNC);               // (2) 0.08658
/*32 */     g_free (pa->pcm_buf);                              // (7) 0.06061
/*34 */     pa->pcm_buf = NULL;                                // (9) 0.05195
/*36 */ }                                                      // (15) 0.004329
