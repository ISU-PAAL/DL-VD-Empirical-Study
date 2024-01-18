// commit message FFmpeg@5e53486545 (target=0, prob=0.6813212, correct=False): typo fix: inited --> initialized
/*0  */ static void qdm2_init(QDM2Context *q) {         // (2) 0.1039
/*2  */     static int inited = 0;                      // (5) 0.06494
/*6  */     if (inited != 0)                            // (6) 0.06494
/*8  */         return;                                 // (9) 0.05844
/*10 */     inited = 1;                                 // (10) 0.05195
/*14 */     qdm2_init_vlc();                            // (3) 0.07792
/*16 */     ff_mpa_synth_init(mpa_window);              // (1) 0.1169
/*18 */     softclip_table_init();                      // (7) 0.06493
/*20 */     rnd_table_init();                           // (8) 0.06493
/*22 */     init_noise_samples();                       // (4) 0.07143
/*26 */     av_log(NULL, AV_LOG_DEBUG, "init done\n");  // (0) 0.1364
/*28 */ }                                               // (11) 0.006494
